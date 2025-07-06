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
  std::string filePath;
  std::string outputPath;
  logger::Logger parserLogger;
  json mftEntry;
public:
  MFTParser(std::string& filePath, std::string& outputPath);
  ~MFTParser();
  void parse();  
 };

}
