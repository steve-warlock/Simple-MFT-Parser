#pragma once
#include <cstdint>

using UCHAR    = uint8_t;
using USHORT   = uint16_t;
using ULONG    = uint32_t;
using WCHAR    = uint16_t;
using LONGLONG = int64_t;
using ULONGLONG = uint64_t;
using ATTRIBUTE_TYPE_CODE = ULONG;
using VCN = LONGLONG;

#pragma pack(push, 1)
namespace windows {

// -- MFT file record sector header
typedef struct _MULTI_SECTOR_HEADER {
    UCHAR  Signature[4];         // "FILE"
    USHORT UpdateSequenceOffset;
    USHORT UpdateSequenceSize;
} MULTI_SECTOR_HEADER, *PMULTI_SECTOR_HEADER;

// -- Used in MFT file record reference fields
typedef struct _MFT_SEGMENT_REFERENCE {
    ULONG  SegmentNumberLowPart;
    USHORT SegmentNumberHighPart;
    USHORT SequenceNumber;
} MFT_SEGMENT_REFERENCE, *PMFT_SEGMENT_REFERENCE;

typedef MFT_SEGMENT_REFERENCE FILE_REFERENCE, *PFILE_REFERENCE;
typedef USHORT UPDATE_SEQUENCE_NUMBER;
typedef UPDATE_SEQUENCE_NUMBER UPDATE_SEQUENCE_ARRAY[1];

// -- Core MFT file record header
typedef struct _FILE_RECORD_SEGMENT_HEADER {
    MULTI_SECTOR_HEADER   MultiSectorHeader;
    ULONGLONG             Reserved1;
    USHORT                SequenceNumber;
    USHORT                Reserved2;
    USHORT                FirstAttributeOffset;
    USHORT                Flags;
    ULONG                 Reserved3[2];
    FILE_REFERENCE        BaseFileRecordSegment;
    USHORT                Reserved4;
    UPDATE_SEQUENCE_ARRAY UpdateSequenceArray;
} FILE_RECORD_SEGMENT_HEADER, *PFILE_RECORD_SEGMENT_HEADER;

// -- Header for any attribute (e.g., $STANDARD_INFORMATION, $FILE_NAME, $DATA)
typedef struct _ATTRIBUTE_RECORD_HEADER {
    ATTRIBUTE_TYPE_CODE   TypeCode;
    ULONG                 RecordLength;
    UCHAR                 FormCode;          // 0 = resident, 1 = non-resident
    UCHAR                 NameLength;
    USHORT                NameOffset;
    USHORT                Flags;
    USHORT                Instance;

    union {
        struct {
            ULONG  ValueLength;
            USHORT ValueOffset;
            UCHAR  Reserved[2];
        } Resident;

        struct {
            VCN       LowestVCN;
            VCN       HighestVCN;
            USHORT    MappingPairsOffset;
            UCHAR     Reserved[6];
            LONGLONG  AllocatedLength;
            LONGLONG  FileSize;
            LONGLONG  ValidDataLength;
            LONGLONG  TotalAllocated;  // Optional
        } NonResident;
    };
} ATTRIBUTE_RECORD_HEADER, *PATTRIBUTE_RECORD_HEADER;

// -- $STANDARD_INFORMATION attribute (type 0x10)
typedef struct _STANDARD_INFORMATION {
    LONGLONG  CreationTime;
    LONGLONG  FileAlteredTime;
    ULONGLONG MFTChangedTime;
    ULONGLONG FileReadTime;
    ULONG     FileAttributes;
    ULONG     MaximumVersions;
    ULONG     VersionNumber;
    ULONG     ClassId;
    // Optionally more fields in NTFS 3.0+
} STANDARD_INFORMATION, *PSTANDARD_INFORMATION;

// -- $FILE_NAME attribute (type 0x30)
typedef struct _FILE_NAME_ATTRIBUTE {
    MFT_SEGMENT_REFERENCE ParentDirectory;
    ULONGLONG CreationTime;
    ULONGLONG FileAlteredTime;
    ULONGLONG MFTChangedTime;
    ULONGLONG FileReadTime;
    ULONGLONG AllocatedSize;
    ULONGLONG RealSize;
    ULONG     Flags;
    ULONG     Reparse;
    UCHAR     FilenameLength;     // In WCHARs
    UCHAR     FilenameNamespace;
    WCHAR     Filename[1];        // Variable-length UTF-16LE
} FILE_NAME_ATTRIBUTE, *PFILE_NAME_ATTRIBUTE;

// -- Marks end of attribute list
inline constexpr ULONG ATTRIBUTE_TYPE_END = 0xFFFFFFFF;

}
#pragma pack(pop)

