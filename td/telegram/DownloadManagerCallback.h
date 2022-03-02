//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2022
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/DownloadManager.h"
#include "td/telegram/files/FileId.h"
#include "td/telegram/files/FileSourceId.h"
#include "td/telegram/td_api.h"

#include "td/actor/actor.h"

#include "td/utils/common.h"

namespace td {

class Td;

class DownloadManagerCallback final : public DownloadManager::Callback {
 public:
  DownloadManagerCallback(Td *td, ActorShared<> parent) : td_(td), parent_(std::move(parent)) {
  }

  void update_counters(DownloadManager::Counters counters) final;

  void update_file_removed(FileId file_id) final;

  void start_file(FileId file_id, int8 priority, ActorShared<DownloadManager> download_manager) final;

  void pause_file(FileId file_id) final;

  void delete_file(FileId file_id) final;

  FileId dup_file_id(FileId file_id) final;

  FileView get_file_view(FileId file_id) final;

  td_api::object_ptr<td_api::fileDownload> get_file_download_object(FileId file_id, FileSourceId file_source_id,
                                                                    int32 add_date, int32 complete_date,
                                                                    bool is_paused);

 private:
  Td *td_;
  ActorShared<> parent_;

  static std::shared_ptr<FileManager::DownloadCallback> make_download_file_callback(
      Td *td, ActorShared<DownloadManager> download_manager);
};

}  // namespace td