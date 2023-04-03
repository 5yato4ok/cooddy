/// Copyright (C) 2020-2023 Huawei Technologies Co., Ltd.
///
/// This file is part of Cooddy, distributed under the GNU GPL version 3 with a Linking Exception.
/// For full terms see https://github.com/program-analysis-team/cooddy/blob/master/LICENSE.txt.
#ifndef COODDY_ANALYZER_SOURCE_PARSER_FILEENTRIESCACHE_H_
#define COODDY_ANALYZER_SOURCE_PARSER_FILEENTRIESCACHE_H_

#include <utils/IOStream.h>
#include <utils/UniqueId.h>

#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace HCXX {

struct FileEntry {
    std::string filePath;
    uint32_t fileSize = 0;
    std::vector<uint32_t> lineOffsets;
    std::string fileSource;
    UniqueId hash;
    bool isLoaded = false;
    bool isFakeSource = false;
};

class FileEntriesCache {
public:
    static FileEntriesCache& GetInstance();
    FileEntry* GetFileEntry(const std::string& sourcePath,
                            const std::function<bool(std::string&)>& sourceProvider = nullptr);

    void RemoveEntry(const std::string& sourcePath);

    void Serialize(IOStream& stream);

private:
    std::mutex myMutex;
    std::unordered_map<std::string, HCXX::FileEntry> myEntries;
};

};  // namespace HCXX

#endif  // COODDY_ANALYZER_SOURCE_PARSER_FILEENTRIESCACHE_H_
