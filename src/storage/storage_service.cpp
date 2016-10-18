#include "storage_service.h"
#include "relation_handler.h"
namespace storage {

StorageService::StorageService() {
  buffer_manager_ = new BufferManager();
  space_manager_ = new SpaceManager(buffer_manager_);
}

StorageService::~StorageService() {
  delete space_manager_;
  delete buffer_manager_;
}
bool StorageService::Start() {
  return buffer_manager_->Start();
}

RelationHandlerInterface * StorageService::OpenHandler(relationid_t rel,
                                                       OpenMode mode) {
  RelationHandler *handler = new RelationHandler(rel, mode, buffer_manager_,
                                                 space_manager_);
  return handler;
}

void StorageService::CloseHandler(RelationHandlerInterface* handler) {
  delete handler;
}

void StorageService::InitDB() {
  space_manager_->InitDB();
}

void StorageService::FlushAll() {
  buffer_manager_->FlushAll();
}

void StorageService::Stop() {
  buffer_manager_->Stop();
}
}  // namespace storage
