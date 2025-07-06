#pragma once
#include <cstdint>

using UCHAR     = uint8_t;
using USHORT    = uint16_t;
using ULONG     = uint32_t;
using ULONGLONG = uint64_t;
using WCHAR     = uint16_t;

#pragma pack(push, 1)
namespace windows {

// ------------------------------------------------------------
// MULTI_SECTOR_HEADER (Part of FILE_RECORD_SEGMENT_HEADER)
typedef struct MULTI_SECTOR_HEADER {
    UCHAR  Signature[4];         // "FILE"
    USHORT UpdateSequenceOffset;
    USHORT UpdateSequenceSize;
} MULTI_SECTOR_HEADER, *PMULTI_SECTOR_HEADER;

// ------------------------------------------------------------
// MFT_SEGMENT_REFERENCE
typedef struct MFT_SEGMENT_REFERENCE {
    ULONG  SegmentNumberLowPart;
    USHORT SegmentNumberHighPart;
    USHORT SequenceNumber;
} MFT_SEGMENT_REFERENCE, *PMFT_SEGMENT_REFERENCE;

// ------------------------------------------------------------
// FILE_RECORD_SEGMENT_HEADER
typedef struct FILE_RECORD_SEGMENT_HEADER {
    MULTI_SECTOR_HEADER MultiSectorHeader;

    ULONGLONG LogFileSequenceNumber;
    USHORT SequenceNumber;
    USHORT HardLinkCount;
    USHORT FirstAttributeOffset;
    USHORT Flags;
    ULONG  UsedSizeOfTheMFTEntry;
    ULONG  AllocatedSizeOfTheMFTEntry;
    MFT_SEGMENT_REFERENCE BaseFileRecordSegment;
    USHORT NextAttributeId;
    USHORT Padding;           // Alignment padding
    ULONG  MFTRecordNumber;
    // Followed by Update Sequence Array
} FILE_RECORD_SEGMENT_HEADER, *PFILE_RECORD_SEGMENT_HEADER;

// ------------------------------------------------------------
// ATTRIBUTE_RECORD_HEADER (Header for all attributes)
typedef struct ATTRIBUTE_RECORD_HEADER {
    ULONG  TypeCode;
    ULONG  RecordLength;
    UCHAR  FormCode;          // 0 = resident, 1 = non-resident
    UCHAR  NameLength;
    USHORT NameOffset;
    USHORT Flags;             // e.g., 0x0001 = compressed
    USHORT Instance;

    union {
        // Resident attribute
        struct {
            ULONG  ValueLength;
            USHORT ValueOffset;
            UCHAR  ResidentFlags;
            UCHAR  Reserved;
        } Resident;

        // Non-resident attribute
        struct {
            ULONGLONG LowestVCN;
            ULONGLONG HighestVCN;
            USHORT MappingPairsOffset;
            UCHAR  CompressionUnit;
            UCHAR  Reserved[5];
            ULONGLONG AllocatedLength;
            ULONGLONG FileSize;
            ULONGLONG ValidDataLength;
            ULONGLONG TotalAllocated;  // Optional
        } NonResident;
    };
} ATTRIBUTE_RECORD_HEADER, *PATTRIBUTE_RECORD_HEADER;

// ------------------------------------------------------------
// STANDARD_INFORMATION (Attribute Type 0x10)
typedef struct STANDARD_INFORMATION {
    ULONGLONG CreationTime;
    ULONGLONG FileAlteredTime;
    ULONGLONG MFTChangedTime;
    ULONGLONG FileReadTime;
    ULONG     FileAttributes;
    ULONG     MaximumVersions;
    ULONG     VersionNumber;
    ULONG     ClassId;
    // Fields in NTFS 3.0+: OwnerId, SecurityId, QuotaCharged, USN...
} STANDARD_INFORMATION, *PSTANDARD_INFORMATION;

// ------------------------------------------------------------
// FILE_NAME (Attribute Type 0x30)
typedef struct FILE_NAME_ATTRIBUTE {
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
    UCHAR     FilenameNamespace;  // 0 = POSIX, 1 = Win32, etc.
    WCHAR     Filename[1];        // Variable-length UTF-16LE
} FILE_NAME_ATTRIBUTE, *PFILE_NAME_ATTRIBUTE;

// ------------------------------------------------------------
// ATTRIBUTE_LIST_ENTRY (Optional for overflown attributes)
typedef struct ATTRIBUTE_LIST_ENTRY {
    ULONG  AttributeTypeCode;
    USHORT RecordLength;
    UCHAR  NameLength;
    UCHAR  NameOffset;
    ULONGLONG LowestVCN;
    MFT_SEGMENT_REFERENCE SegmentReference;
    USHORT Instance;
    WCHAR  Name[1];               // Variable-length
} ATTRIBUTE_LIST_ENTRY, *PATTRIBUTE_LIST_ENTRY;

// ------------------------------------------------------------
// ATTRIBUTE TYPE END MARKER
inline constexpr ULONG ATTRIBUTE_TYPE_END = 0xFFFFFFFF;

} 
#pragma pack(pop)

