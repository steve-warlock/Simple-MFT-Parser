#include "../include/mft_parser.hpp"

namespace parser {
  MFTParser::MFTParser(std::string& filePath, std::string& outputPath) : filePath(filePath), outputPath(outputPath), parserLogger("./mft.log") {
    if(!fs::exists(this -> filePath)) { 
      this -> parserLogger.log("[ERROR] (MFTParser::MFTParser) The file path " 
                               + this -> filePath 
                               + " does not exists!");
      return;
    } else if(!fs::is_regular_file(this -> filePath)) {
      this -> parserLogger.log("[ERROR] (MFTParser::MFTParser) The file at the path " 
                               + this -> filePath 
                               + " is not a file!");
      return;
    }
  
    if(!fs::exists(this -> outputPath)) {
      this -> parserLogger.log("[WARN] (MFTParser::MFTParser) the output path " 
                               + this -> outputPath 
                               + " does not exists. Creating it now!");
      std::fstream createOnly(this->outputPath, std::ios::out);
      createOnly.close();
      this -> parserLogger.log("[DEBUG] (MFTParser::MFTParser) Output path " 
                               + this -> outputPath
                               + " has been created successfully!");
    }
    this -> parserLogger.log("[DEBUG] (MFTParser::MFTParser) Constructor successfully initialized!");
  }
  
  MFTParser::~MFTParser() {
    this -> parserLogger.log("[DEBUG] (MFTParser::~MFTParser) Destructor successfully called!");
  }
  
  void MFTParser::parse() {
    // the parsing is done on_demand in the mft_entry
    // this function will create a json with the mft_entry
  }   

}


