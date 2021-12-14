#include "anvil/region_header.hpp"

// STL
#include <stdexcept>
#include <utility>
#include <string>

namespace anvil
{

RegionHeader::RegionHeader()
{
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        m_chunkInfo[i] = ChunkInfo();
    }
}

RegionHeader::RegionHeader(const RegionHeader &other)
{
    *this = other;
}

RegionHeader::RegionHeader(RegionHeader &&other) noexcept
{
    *this = std::move(other);
}

RegionHeader::RegionHeader(const std::array<ChunkInfo, ChunkCount> &info)
{
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        m_chunkInfo[i] = info[i];
    }
}

RegionHeader::~RegionHeader()
{

}

RegionHeader& RegionHeader::operator=(const RegionHeader &other)
{
    if(this != &other) {
        for(unsigned int i = 0; i < ChunkCount; ++i) {
            m_chunkInfo[i] = other.m_chunkInfo[i];
        }
    }
    return *this;
}

RegionHeader& RegionHeader::operator=(RegionHeader &&other) noexcept
{
    if(this != &other) {
        for(unsigned int i = 0; i < ChunkCount; ++i) {
            m_chunkInfo[i] = std::move(other.m_chunkInfo[i]);
        }
    }
    return *this;
}

bool RegionHeader::operator==(const RegionHeader &other)
{
    if(this == &other) {
        return true;
    }

    for(unsigned int i = 0; i < ChunkCount; ++i) {
        if(m_chunkInfo[i] != other.m_chunkInfo[i]) {
            return false;
        }
    }
    return true;
}

bool RegionHeader::operator!=(const RegionHeader &other)
{
    return !(*this == other);
}

unsigned int RegionHeader::getRegionCount() const
{
    unsigned int count{0};

    for(unsigned int i = 0; i < ChunkCount; ++i) {
        if(!m_chunkInfo[i].isEmpty()) {
            ++count;
        }
    }
    return count;
}

std::vector<char> RegionHeader::getRegionData() const
{
    // TODO
    return std::vector<char>();
}

const std::array<ChunkInfo, ChunkCount>& RegionHeader::getChunkInfo() const
{
    return m_chunkInfo;
}

ChunkInfo& RegionHeader::getChunkInfoAt(unsigned int index)
{
    if(index >= ChunkCount) {
        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
    }
    return m_chunkInfo[index];
}

const ChunkInfo& RegionHeader::getChunkInfoAt(unsigned int index) const
{
    if(index >= ChunkCount) {
        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
    }
    return m_chunkInfo[index];
}

void RegionHeader::setChunkInfo(const std::array<ChunkInfo, ChunkCount> &info)
{
    for(unsigned int i = 0; i < ChunkCount; ++i) {
        m_chunkInfo[i] = info[i];
    }
}

void RegionHeader::setChunkInfoAt(unsigned int index, const ChunkInfo &info)
{
    if(index >= ChunkCount) {
        throw std::out_of_range("Index out_of_range: " + std::to_string(index));
    }
    m_chunkInfo[index] = info;
}

} // namespace anvil