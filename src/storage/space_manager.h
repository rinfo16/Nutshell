#ifndef SRC_STORAGE_SPACE_MANAGER_H_
#define SRC_STORAGE_SPACE_MANAGER_H_

#include "buffer_manager.h"
#include "storage_define.h"

namespace storage {

class SpaceManager {
 public:
  SpaceManager(BufferManager *buffer_manager);
  virtual ~SpaceManager();

  bool InitDB();

  bool CreateFile(fileno_t fileno);

  bool CreateDataFile(fileno_t *fileno);

  bool CreateSegment(PageID *segment_header_page);

  bool CreateExtent(Page*segment_header_file_page, Page* segment_header_page,
                    PageID *extent_header_page_id);

  bool CreateDataPage(Page *seg_file_header_page, Page *segment_header_page,
                      PageID *new_page_id /*OUT*/);

  bool CreateDataPage(Page *extent_header_page, PageID *new_page_id);

  bool FindSpace(PageID segment_header_page, size_t length, PageID *data_page_);

 private:
  bool CreateExtentInFile(Page *segment_page, fileno_t data_file_no,
                          PageID *extent_header_page_id);
  std::vector<pageno_t> data_file_;
  BufferManager *buffer_manager_;
};

}  // namespace storage

#endif // SRC_STORAGE_SPACE_MANAGER_H_
