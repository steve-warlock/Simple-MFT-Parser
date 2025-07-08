#include "../include/mft.hpp"

namespace mft {

mft_entry::mft_entry(std::vector<uint8_t>& raw_data) : raw_data(raw_data) {}

mft_entry::~mft_entry() {
  this -> raw_data.clear();
}

std::vector<uint8_t>& mft_entry::getRawData() {
  return this -> raw_data;
}

PFILE_RECORD_SEGMENT_HEADER mft_entry::header() {return reinterpret_cast<PFILE_RECORD_SEGMENT_HEADER>(getRawData().data()); }

 std::vector<PATTRIBUTE_RECORD_HEADER> mft_entry::getAttributes() {
    std::vector<PATTRIBUTE_RECORD_HEADER> result;
    auto hdr = header();
    auto attrOffset = hdr->FirstAttributeOffset;
    
    while(attrOffset + sizeof(ATTRIBUTE_RECORD_HEADER) <= this -> raw_data.size()) {
        
        auto attr = reinterpret_cast<PATTRIBUTE_RECORD_HEADER>(this -> raw_data.data() + attrOffset);
        if(attr->TypeCode == ATTRIBUTE_TYPE_END) {
            break;
        }
        
        result.push_back(attr);
        attrOffset += attr -> RecordLength; 
    }
    return result; 
}

}
