#include "nbt/nbt_read.hpp"

// gtest
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// STL
#include <stdexcept>

const std::string testFolder = "../../../test/testdata/nbt/";

TEST(nbt_read, loadNbtData_error)
{
    std::vector<unsigned char> data;

    EXPECT_THROW({
        try {
            data = nbt::loadNbtData("fakeFileName.someExt", false);
        } catch(const std::runtime_error &err)
        {
            EXPECT_STREQ("Could not open file for reading: fakeFileName.someExt", 
                         err.what());
            throw;
        }
    }, std::runtime_error);
}

TEST(nbt_read, loadNbtData_uncompressed)
{
    std::vector<unsigned char> data = nbt::loadNbtData(testFolder + "hello_world.nbt", false);
    EXPECT_EQ(33, data.size());

    unsigned char rawData[33] = {
        0x0A, 0x00, 0x0B, 0x68, 0x65, 0x6C, 0x6C, 0x6F,
        0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x08, 0x00,
        0x04, 0x6E, 0x61, 0x6D, 0x65, 0x00, 0x09, 0x42,
        0x61, 0x6E, 0x61, 0x6E, 0x72, 0x61, 0x6D, 0x61,
        0x00
    };
    
    ASSERT_THAT(data, ::testing::ElementsAreArray(rawData, 33));
}

TEST(nbt_read, loadNbtData_compressed)
{
    std::vector<unsigned char> data = nbt::loadNbtData(testFolder + "bigtest.nbt", true);
    EXPECT_EQ(1544, data.size());

    unsigned char rawData[1544] = {
        0x0A, 0x00, 0x05, 0x4C, 0x65, 0x76, 0x65, 0x6C, 0x04, 0x00, 0x08, 0x6C, 0x6F, 0x6E, 0x67, 0x54,
        0x65, 0x73, 0x74, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x00, 0x09, 0x73, 0x68,
        0x6F, 0x72, 0x74, 0x54, 0x65, 0x73, 0x74, 0x7F, 0xFF, 0x08, 0x00, 0x0A, 0x73, 0x74, 0x72, 0x69,
        0x6E, 0x67, 0x54, 0x65, 0x73, 0x74, 0x00, 0x29, 0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x20, 0x57, 0x4F,
        0x52, 0x4C, 0x44, 0x20, 0x54, 0x48, 0x49, 0x53, 0x20, 0x49, 0x53, 0x20, 0x41, 0x20, 0x54, 0x45,
        0x53, 0x54, 0x20, 0x53, 0x54, 0x52, 0x49, 0x4E, 0x47, 0x20, 0xC3, 0x85, 0xC3, 0x84, 0xC3, 0x96,
        0x21, 0x05, 0x00, 0x09, 0x66, 0x6C, 0x6F, 0x61, 0x74, 0x54, 0x65, 0x73, 0x74, 0x3E, 0xFF, 0x18,
        0x32, 0x03, 0x00, 0x07, 0x69, 0x6E, 0x74, 0x54, 0x65, 0x73, 0x74, 0x7F, 0xFF, 0xFF, 0xFF, 0x0A,
        0x00, 0x14, 0x6E, 0x65, 0x73, 0x74, 0x65, 0x64, 0x20, 0x63, 0x6F, 0x6D, 0x70, 0x6F, 0x75, 0x6E,
        0x64, 0x20, 0x74, 0x65, 0x73, 0x74, 0x0A, 0x00, 0x03, 0x68, 0x61, 0x6D, 0x08, 0x00, 0x04, 0x6E,
        0x61, 0x6D, 0x65, 0x00, 0x06, 0x48, 0x61, 0x6D, 0x70, 0x75, 0x73, 0x05, 0x00, 0x05, 0x76, 0x61,
        0x6C, 0x75, 0x65, 0x3F, 0x40, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x03, 0x65, 0x67, 0x67, 0x08, 0x00,
        0x04, 0x6E, 0x61, 0x6D, 0x65, 0x00, 0x07, 0x45, 0x67, 0x67, 0x62, 0x65, 0x72, 0x74, 0x05, 0x00,
        0x05, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x0F, 0x6C,
        0x69, 0x73, 0x74, 0x54, 0x65, 0x73, 0x74, 0x20, 0x28, 0x6C, 0x6F, 0x6E, 0x67, 0x29, 0x04, 0x00,
        0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x09, 0x00, 0x13, 0x6C, 0x69,
        0x73, 0x74, 0x54, 0x65, 0x73, 0x74, 0x20, 0x28, 0x63, 0x6F, 0x6D, 0x70, 0x6F, 0x75, 0x6E, 0x64,
        0x29, 0x0A, 0x00, 0x00, 0x00, 0x02, 0x08, 0x00,
        0x04, 0x6E, 0x61, 0x6D, 0x65, 0x00, 0x0F, 0x43, 0x6F, 0x6D, 0x70, 0x6F, 0x75, 0x6E, 0x64, 0x20,
        0x74, 0x61, 0x67, 0x20, 0x23, 0x30, 0x04, 0x00, 0x0A, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64,
        0x2D, 0x6F, 0x6E, 0x00, 0x00, 0x01, 0x26, 0x52, 0x37, 0xD5, 0x8D, 0x00, 0x08, 0x00, 0x04, 0x6E,
        0x61, 0x6D, 0x65, 0x00, 0x0F, 0x43, 0x6F, 0x6D, 0x70, 0x6F, 0x75, 0x6E, 0x64, 0x20, 0x74, 0x61,
        0x67, 0x20, 0x23, 0x31, 0x04, 0x00, 0x0A, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 0x2D, 0x6F,
        0x6E, 0x00, 0x00, 0x01, 0x26, 0x52, 0x37, 0xD5, 0x8D, 0x00, 0x01, 0x00, 0x08, 0x62, 0x79, 0x74,
        0x65, 0x54, 0x65, 0x73, 0x74, 0x7F, 0x07, 0x00, 0x65, 0x62, 0x79, 0x74, 0x65, 0x41, 0x72, 0x72,
        0x61, 0x79, 0x54, 0x65, 0x73, 0x74, 0x20, 0x28, 0x74, 0x68, 0x65, 0x20, 0x66, 0x69, 0x72, 0x73,
        0x74, 0x20, 0x31, 0x30, 0x30, 0x30, 0x20, 0x76, 0x61, 0x6C, 0x75, 0x65, 0x73, 0x20, 0x6F, 0x66,
        0x20, 0x28, 0x6E, 0x2A, 0x6E, 0x2A, 0x32, 0x35, 0x35, 0x2B, 0x6E, 0x2A, 0x37, 0x29, 0x25, 0x31,
        0x30, 0x30, 0x2C, 0x20, 0x73, 0x74, 0x61, 0x72, 0x74, 0x69, 0x6E, 0x67, 0x20, 0x77, 0x69, 0x74,
        0x68, 0x20, 0x6E, 0x3D, 0x30, 0x20, 0x28, 0x30, 0x2C, 0x20, 0x36, 0x32, 0x2C, 0x20, 0x33, 0x34,
        0x2C, 0x20, 0x31, 0x36, 0x2C, 0x20, 0x38, 0x2C, 0x20, 0x2E, 0x2E, 0x2E, 0x29, 0x29, 0x00, 0x00,
        0x03, 0xE8, 0x00, 0x3E, 0x22, 0x10, 0x08, 0x0A, 0x16, 0x2C, 0x4C, 0x12, 0x46, 0x20, 0x04, 0x56,
        0x4E, 0x50, 0x5C, 0x0E, 0x2E, 0x58, 0x28, 0x02, 0x4A, 0x38, 0x30, 0x32, 0x3E, 0x54, 0x10, 0x3A,
        0x0A, 0x48, 0x2C, 0x1A, 0x12, 0x14, 0x20, 0x36, 0x56, 0x1C, 0x50, 0x2A, 0x0E, 0x60, 0x58, 0x5A,
        0x02, 0x18, 0x38, 0x62, 0x32, 0x0C, 0x54, 0x42, 0x3A, 0x3C, 0x48, 0x5E, 0x1A, 0x44, 0x14, 0x52,
        0x36, 0x24, 0x1C, 0x1E, 0x2A, 0x40, 0x60, 0x26, 0x5A, 0x34, 0x18, 0x06, 0x62, 0x00, 0x0C, 0x22,
        0x42, 0x08, 0x3C, 0x16, 0x5E, 0x4C, 0x44, 0x46, 0x52, 0x04, 0x24, 0x4E, 0x1E, 0x5C, 0x40, 0x2E,
        0x26, 0x28, 0x34, 0x4A, 0x06, 0x30, 0x00, 0x3E, 0x22, 0x10, 0x08, 0x0A, 0x16, 0x2C, 0x4C, 0x12,
        0x46, 0x20, 0x04, 0x56, 0x4E, 0x50, 0x5C, 0x0E, 0x2E, 0x58, 0x28, 0x02, 0x4A, 0x38, 0x30, 0x32,
        0x3E, 0x54, 0x10, 0x3A, 0x0A, 0x48, 0x2C, 0x1A, 0x12, 0x14, 0x20, 0x36, 0x56, 0x1C, 0x50, 0x2A,
        0x0E, 0x60, 0x58, 0x5A, 0x02, 0x18, 0x38, 0x62, 0x32, 0x0C, 0x54, 0x42, 0x3A, 0x3C, 0x48, 0x5E,
        0x1A, 0x44, 0x14, 0x52, 0x36, 0x24, 0x1C, 0x1E, 0x2A, 0x40, 0x60, 0x26, 0x5A, 0x34, 0x18, 0x06,
        0x62, 0x00, 0x0C, 0x22, 0x42, 0x08, 0x3C, 0x16, 0x5E, 0x4C, 0x44, 0x46, 0x52, 0x04, 0x24, 0x4E,
        0x1E, 0x5C, 0x40, 0x2E, 0x26, 0x28, 0x34, 0x4A, 0x06, 0x30, 0x00, 0x3E, 0x22, 0x10, 0x08, 0x0A,
        0x16, 0x2C, 0x4C, 0x12, 0x46, 0x20, 0x04, 0x56, 0x4E, 0x50, 0x5C, 0x0E, 0x2E, 0x58, 0x28, 0x02,
        0x4A, 0x38, 0x30, 0x32, 0x3E, 0x54, 0x10, 0x3A, 0x0A, 0x48, 0x2C, 0x1A, 0x12, 0x14, 0x20, 0x36,
        0x56, 0x1C, 0x50, 0x2A, 0x0E, 0x60, 0x58, 0x5A, 0x02, 0x18, 0x38, 0x62, 0x32, 0x0C, 0x54, 0x42,
        0x3A, 0x3C, 0x48, 0x5E, 0x1A, 0x44, 0x14, 0x52, 0x36, 0x24, 0x1C, 0x1E, 0x2A, 0x40, 0x60, 0x26,
        0x5A, 0x34, 0x18, 0x06, 0x62, 0x00, 0x0C, 0x22, 0x42, 0x08, 0x3C, 0x16, 0x5E, 0x4C, 0x44, 0x46,
        0x52, 0x04, 0x24, 0x4E, 0x1E, 0x5C, 0x40, 0x2E, 0x26, 0x28, 0x34, 0x4A, 0x06, 0x30, 0x00, 0x3E,
        0x22, 0x10, 0x08, 0x0A, 0x16, 0x2C, 0x4C, 0x12, 0x46, 0x20, 0x04, 0x56, 0x4E, 0x50, 0x5C, 0x0E,
        0x2E, 0x58, 0x28, 0x02, 0x4A, 0x38, 0x30, 0x32, 0x3E, 0x54, 0x10, 0x3A, 0x0A, 0x48, 0x2C, 0x1A,
        0x12, 0x14, 0x20, 0x36, 0x56, 0x1C, 0x50, 0x2A, 0x0E, 0x60, 0x58, 0x5A, 0x02, 0x18, 0x38, 0x62,
        0x32, 0x0C, 0x54, 0x42, 0x3A, 0x3C, 0x48, 0x5E, 0x1A, 0x44, 0x14, 0x52, 0x36, 0x24, 0x1C, 0x1E,
        0x2A, 0x40, 0x60, 0x26, 0x5A, 0x34, 0x18, 0x06, 0x62, 0x00, 0x0C, 0x22, 0x42, 0x08, 0x3C, 0x16,
        0x5E, 0x4C, 0x44, 0x46, 0x52, 0x04, 0x24, 0x4E, 0x1E, 0x5C, 0x40, 0x2E, 0x26, 0x28, 0x34, 0x4A,
        0x06, 0x30, 0x00, 0x3E, 0x22, 0x10, 0x08, 0x0A, 0x16, 0x2C, 0x4C, 0x12, 0x46, 0x20, 0x04, 0x56,
        0x4E, 0x50, 0x5C, 0x0E, 0x2E, 0x58, 0x28, 0x02, 0x4A, 0x38, 0x30, 0x32, 0x3E, 0x54, 0x10, 0x3A,
        0x0A, 0x48, 0x2C, 0x1A, 0x12, 0x14, 0x20, 0x36, 0x56, 0x1C, 0x50, 0x2A, 0x0E, 0x60, 0x58, 0x5A,
        0x02, 0x18, 0x38, 0x62, 0x32, 0x0C, 0x54, 0x42, 0x3A, 0x3C, 0x48, 0x5E, 0x1A, 0x44, 0x14, 0x52,
        0x36, 0x24, 0x1C, 0x1E, 0x2A, 0x40, 0x60, 0x26, 0x5A, 0x34, 0x18, 0x06, 0x62, 0x00, 0x0C, 0x22,
        0x42, 0x08, 0x3C, 0x16, 0x5E, 0x4C, 0x44, 0x46, 0x52, 0x04, 0x24, 0x4E, 0x1E, 0x5C, 0x40, 0x2E,
        0x26, 0x28, 0x34, 0x4A, 0x06, 0x30, 0x00, 0x3E, 0x22, 0x10, 0x08, 0x0A, 0x16, 0x2C, 0x4C, 0x12,
        0x46, 0x20, 0x04, 0x56, 0x4E, 0x50, 0x5C, 0x0E, 0x2E, 0x58, 0x28, 0x02, 0x4A, 0x38, 0x30, 0x32,
        0x3E, 0x54, 0x10, 0x3A, 0x0A, 0x48, 0x2C, 0x1A, 0x12, 0x14, 0x20, 0x36, 0x56, 0x1C, 0x50, 0x2A,
        0x0E, 0x60, 0x58, 0x5A, 0x02, 0x18, 0x38, 0x62, 0x32, 0x0C, 0x54, 0x42, 0x3A, 0x3C, 0x48, 0x5E,
        0x1A, 0x44, 0x14, 0x52, 0x36, 0x24, 0x1C, 0x1E, 0x2A, 0x40, 0x60, 0x26, 0x5A, 0x34, 0x18, 0x06,
        0x62, 0x00, 0x0C, 0x22, 0x42, 0x08, 0x3C, 0x16, 0x5E, 0x4C, 0x44, 0x46, 0x52, 0x04, 0x24, 0x4E,
        0x1E, 0x5C, 0x40, 0x2E, 0x26, 0x28, 0x34, 0x4A, 0x06, 0x30, 0x00, 0x3E, 0x22, 0x10, 0x08, 0x0A,
        0x16, 0x2C, 0x4C, 0x12, 0x46, 0x20, 0x04, 0x56, 0x4E, 0x50, 0x5C, 0x0E, 0x2E, 0x58, 0x28, 0x02,
        0x4A, 0x38, 0x30, 0x32, 0x3E, 0x54, 0x10, 0x3A, 0x0A, 0x48, 0x2C, 0x1A, 0x12, 0x14, 0x20, 0x36,
        0x56, 0x1C, 0x50, 0x2A, 0x0E, 0x60, 0x58, 0x5A, 0x02, 0x18, 0x38, 0x62, 0x32, 0x0C, 0x54, 0x42,
        0x3A, 0x3C, 0x48, 0x5E, 0x1A, 0x44, 0x14, 0x52, 0x36, 0x24, 0x1C, 0x1E, 0x2A, 0x40, 0x60, 0x26,
        0x5A, 0x34, 0x18, 0x06, 0x62, 0x00, 0x0C, 0x22, 0x42, 0x08, 0x3C, 0x16, 0x5E, 0x4C, 0x44, 0x46,
        0x52, 0x04, 0x24, 0x4E, 0x1E, 0x5C, 0x40, 0x2E, 0x26, 0x28, 0x34, 0x4A, 0x06, 0x30, 0x00, 0x3E,
        0x22, 0x10, 0x08, 0x0A, 0x16, 0x2C, 0x4C, 0x12, 0x46, 0x20, 0x04, 0x56, 0x4E, 0x50, 0x5C, 0x0E,
        0x2E, 0x58, 0x28, 0x02, 0x4A, 0x38, 0x30, 0x32, 0x3E, 0x54, 0x10, 0x3A, 0x0A, 0x48, 0x2C, 0x1A,
        0x12, 0x14, 0x20, 0x36, 0x56, 0x1C, 0x50, 0x2A, 0x0E, 0x60, 0x58, 0x5A, 0x02, 0x18, 0x38, 0x62,
        0x32, 0x0C, 0x54, 0x42, 0x3A, 0x3C, 0x48, 0x5E, 0x1A, 0x44, 0x14, 0x52, 0x36, 0x24, 0x1C, 0x1E,
        0x2A, 0x40, 0x60, 0x26, 0x5A, 0x34, 0x18, 0x06, 0x62, 0x00, 0x0C, 0x22, 0x42, 0x08, 0x3C, 0x16,
        0x5E, 0x4C, 0x44, 0x46, 0x52, 0x04, 0x24, 0x4E, 0x1E, 0x5C, 0x40, 0x2E, 0x26, 0x28, 0x34, 0x4A,
        0x06, 0x30, 0x00, 0x3E, 0x22, 0x10, 0x08, 0x0A, 0x16, 0x2C, 0x4C, 0x12, 0x46, 0x20, 0x04, 0x56,
        0x4E, 0x50, 0x5C, 0x0E, 0x2E, 0x58, 0x28, 0x02, 0x4A, 0x38, 0x30, 0x32, 0x3E, 0x54, 0x10, 0x3A,
        0x0A, 0x48, 0x2C, 0x1A, 0x12, 0x14, 0x20, 0x36, 0x56, 0x1C, 0x50, 0x2A, 0x0E, 0x60, 0x58, 0x5A,
        0x02, 0x18, 0x38, 0x62, 0x32, 0x0C, 0x54, 0x42, 0x3A, 0x3C, 0x48, 0x5E, 0x1A, 0x44, 0x14, 0x52,
        0x36, 0x24, 0x1C, 0x1E, 0x2A, 0x40, 0x60, 0x26, 0x5A, 0x34, 0x18, 0x06, 0x62, 0x00, 0x0C, 0x22,
        0x42, 0x08, 0x3C, 0x16, 0x5E, 0x4C, 0x44, 0x46, 0x52, 0x04, 0x24, 0x4E, 0x1E, 0x5C, 0x40, 0x2E,
        0x26, 0x28, 0x34, 0x4A, 0x06, 0x30, 0x00, 0x3E, 0x22, 0x10, 0x08, 0x0A, 0x16, 0x2C, 0x4C, 0x12,
        0x46, 0x20, 0x04, 0x56, 0x4E, 0x50, 0x5C, 0x0E, 0x2E, 0x58, 0x28, 0x02, 0x4A, 0x38, 0x30, 0x32,
        0x3E, 0x54, 0x10, 0x3A, 0x0A, 0x48, 0x2C, 0x1A, 0x12, 0x14, 0x20, 0x36, 0x56, 0x1C, 0x50, 0x2A,
        0x0E, 0x60, 0x58, 0x5A, 0x02, 0x18, 0x38, 0x62, 0x32, 0x0C, 0x54, 0x42, 0x3A, 0x3C, 0x48, 0x5E,
        0x1A, 0x44, 0x14, 0x52, 0x36, 0x24, 0x1C, 0x1E, 0x2A, 0x40, 0x60, 0x26, 0x5A, 0x34, 0x18, 0x06,
        0x62, 0x00, 0x0C, 0x22, 0x42, 0x08, 0x3C, 0x16, 0x5E, 0x4C, 0x44, 0x46, 0x52, 0x04, 0x24, 0x4E,
        0x1E, 0x5C, 0x40, 0x2E, 0x26, 0x28, 0x34, 0x4A, 0x06, 0x30, 0x06, 0x00, 0x0A, 0x64, 0x6F, 0x75,
        0x62, 0x6C, 0x65, 0x54, 0x65, 0x73, 0x74, 0x3F, 0xDF, 0x8F, 0x6B, 0xBB, 0xFF, 0x6A, 0x5E, 0x00
    };

    ASSERT_THAT(data, ::testing::ElementsAreArray(rawData, 1544));
}