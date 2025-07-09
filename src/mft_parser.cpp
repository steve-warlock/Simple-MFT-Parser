#include "../include/mft_parser.hpp"
#include <cstdint>
#include <ios>

namespace parser {
  MFTParser::MFTParser(
                      std::string& filePath, 
                      std::string& outputPath
                      ) : filePath(filePath), outputPath(outputPath), parserLogger("mft.log") {
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
      std::fstream createOnly;
      createOnly.open(this->outputPath, std::ios::out);
      createOnly.close();
      this -> parserLogger.log("[DEBUG] (MFTParser::MFTParser) Output path " 
                               + this -> outputPath
                               + " has been created successfully!");
    }
    
    this -> parserLogger.log("[DEBUG] (MFTParser::MFTParser) Initiating opening $MFT file sequence!"); 
    this -> read.open(filePath, std::ios::in | std::ios::binary);
    // is it open?
    if(!this -> read.is_open()) {
      this -> parserLogger.log("[ERROR] (MFTParser::MFTParser) The $MFT file "
                               + filePath 
                               + " couldn't be opened!");
    return;
    }
    this -> parserLogger.log("[DEBUG] (MFTParser::MFTParser) Successfully Initiated opening $MFT file sequence!");   

    this -> parserLogger.log("[DEBUG] (MFTParser::MFTParser) Initiating opening output file sequence!"); 
    this -> write.open(outputPath, std::ios::out);
    // is it open?
    if(!this -> write.is_open()) {
      this -> parserLogger.log("[ERROR] (MFTParser::MFTParser) The output file "
                               + outputPath 
                               + " couldn't be opened!");
    return;
    }
    this -> parserLogger.log("[DEBUG] (MFTParser::MFTParser) Successfully Initiated opening output file sequence!");
    
    this -> parserLogger.log("[DEBUG] (MFTParser::MFTParser) Constructor successfully initialized!");
  }
  
  MFTParser::~MFTParser() {
    this -> parserLogger.log("[DEBUG] (MFTParser::~MFTParser) Closing read stream!");
    this -> read.close();
    this -> parserLogger.log("[DEBUG] (MFTParser::~MFTParser) Closing write stream!");
    this -> write.close();
    this -> parserLogger.log("[DEBUG] (MFTParser::~MFTParser) Destructor successfully called!");
  }
  
  void MFTParser::readEntry(std::fstream& file_read)
  {
    // the size of a mft entry is usually 1024 bytes
    std::vector<uint8_t> raw_data(this -> chunkSize);
    file_read.read(reinterpret_cast<char*>(raw_data.data()), this -> chunkSize);
    std::streamsize bytesRead = file_read.gcount(); // it may be less than 1024 
    raw_data.resize(bytesRead);
    this -> entry -> set_raw_data(raw_data);
  }

  void MFTParser::parse() {
    // the parsing is done on_demand in the mft_entry
    // this function will create a json with the mft_entry
  }   

}


