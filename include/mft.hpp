#include "utils/windows.hpp"

// std
#include <vector>

using namespace windows;

struct mft_entry {
   // raw byte buffer of full 1024 bytes MFT entry
  std::vector<uint8_t> raw_data;
  
  // get header details
  PFILE_RECORD_SEGMENT_HEADER header(); 
 
  // get attributes


};

