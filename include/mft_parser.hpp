// std
#include <string>

// json library
#include <nlohmann/json.hpp>

#include "utils/logger.hpp"
#include "mft.hpp"

using json = nlohmann::json;
namespace parser {

class MFTParser {
private:
  const static std::size_t chunkSize = 1024;
  std::string filePath;
  std::string outputPath;
  logger::Logger parserLogger;
  mft::mft_entry* entry;
  std::fstream read;
  std::fstream write;
  std::size_t EntryID = 1;
  json MFTEntry;
  void readEntry(std::fstream& read, bool& stop_reading);
  void getHeaderInfo(mft::mft_entry& entry, json& entryJson);
  inline bool checkValidityHeader(mft::mft_entry& entry) { 
    return memcmp(entry.header() -> MultiSectorHeader.Signature, "FILE", 4) == 0;
  };
  std::size_t getEntryID();
  void incrementEntryID();
  public:
  MFTParser(std::string& filePath, std::string& outputPath);
  ~MFTParser();
  void parse(); 
 };

}
