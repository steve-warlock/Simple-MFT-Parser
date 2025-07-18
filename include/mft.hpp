#include "utils/windows.hpp"
#include "utils/logger.hpp"
// std
#include <vector>

using namespace windows;
namespace mft {

class mft_entry {
private:
  // raw byte buffer of full 1024 bytes MFT entry
  std::vector<uint8_t> raw_data;
  // logs for debugging
  logger::Logger parserLogger;
public:
  mft_entry();
  ~mft_entry();
  
  void set_raw_data(const std::vector<uint8_t>& raw_data);
  std::vector<uint8_t>& getRawData();
  
  // get header details
  PFILE_RECORD_SEGMENT_HEADER header(); 
 
  // get attributes
  std::vector<PATTRIBUTE_RECORD_HEADER> getAttributes(); 

};

}
