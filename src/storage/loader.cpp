#include "storage/loader.h"
#include "common/minicsv.h"
#include "common/config.h"
#include "common/datetime.h"
#include "storage_service.h"

namespace storage {

Loader::Loader(const std::string & path, const std::string & rel_name)
    : batch_(NULL),
      csv_(path),
      rel_name_(rel_name),
      is_(path.c_str()) {
  tuple_ = memory::CreateTuple(config::Setting::instance().page_size_);
}

Loader::~Loader() {
  storage::Storage::instance().DeleteIOObject(batch_);
}

bool Loader::Prepare() {
  return true;
}

bool Loader::Load() {
  is_.set_delimiter(',', "$$");
  is_.enable_trim_quote_on_str(true, '\"');
  if (!is_.is_open()) {
    return false;
  }
  MetaDataManagerInterface *meta_data = storage::Storage::instance()
      .GetMetaDataManager();
  Relation *rel = meta_data->GetRelationByName(rel_name_);
  if (rel == NULL) {
    return false;
  }
  RowDesc desc = rel->ToDesc();
  batch_ = storage::Storage::instance().NewWriteBatch(rel_name_);
  if (batch_ == NULL) {
    return false;
  }

  int32_t columns = desc.GetColumnCount();
  //desc.mapping_.resize(attributes_.size(), 0);

  int i = 0;
  uint32_t slot_length = sizeof(Slot) * desc.GetColumnCount();
  while (is_.read_line()) {
    try {
      uint32_t off = slot_length;
      union DataValue value;
      std::string str;
      for (int i = 0; i < desc.GetColumnCount(); i++) {
        Slot *slot = tuple_->GetSlot(i);
        switch (desc.GetColumnDesc(i).data_type_) {
          case kDTInteger:
            is_ >> value.integer_;
            slot->offset_ = off;
            slot->length_ = sizeof(value.integer_);
            tuple_->SetValue(off, &value.integer_, sizeof(value.integer_));
            off += sizeof(value.integer_);
            break;
          case kDTFloat:
            is_ >> value.float_;
            slot->offset_ = off;
            slot->length_ = sizeof(value.float_);
            tuple_->SetValue(off, &value.float_, sizeof(value.float_));
            off += sizeof(value.float_);
            break;
          case kDTVarchar:
            is_ >> str;
            slot->offset_ = off;
            slot->length_ = str.size();
            tuple_->SetValue(off, str.c_str(), str.size());
            off += str.size();
            break;
          case kDTDate: {
            is_ >> str;
            value.date_ = DateSimpleString2Subsec(str);
            slot->length_ = sizeof(value.date_);
            slot->offset_ = off;
            tuple_->SetValue(off, &value.date_, sizeof(value.date_));
            off += sizeof(value.date_);
          }
            break;
          default:
            assert(false);
            break;
        }
      }
      assert(off > 0);
      TupleWarpper t(tuple_->Data(), off);
      batch_->Put(&t);
#if OUTPUT
      std::string tuple_string((const char*)t.Data() + slot_length, t.Size() - slot_length);
      BOOST_LOG_TRIVIAL(debug) << tuple_string;
#endif
      if (i != 0 && i % 10000 == 0) {
        BOOST_LOG_TRIVIAL(debug) << "write " << i << " rows ...";
      }

      i++;
    } catch (std::runtime_error& e) {
      BOOST_LOG_TRIVIAL(error) << e.what();
      return false;
    }
  }
  return true;
}

}  // namespace storage
