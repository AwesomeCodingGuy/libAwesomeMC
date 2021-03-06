#ifndef AWESOMEMC_ANVIL_CHUNK_HPP
#define AWESOMEMC_ANVIL_CHUNK_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/compound_tag.hpp>
#include <AwesomeMC/anvil/block.hpp>
#include <AwesomeMC/anvil/heightmap.hpp>

// STL
#include <vector>
#include <memory>

namespace amc
{

class Chunk
{
public:
    Chunk();
    Chunk(const Chunk &other);
    Chunk(Chunk &&other) noexcept;
    virtual ~Chunk();

    Chunk& operator=(const Chunk &other);
    Chunk& operator=(Chunk &&other) noexcept;

    bool operator==(const Chunk &other);
    bool operator!=(const Chunk &other);

    void clear();
    bool isEmpty() const;

    // !!! The Chunk keeps the ownership, but the Tag can be edited. !!!
    CompoundTag* getRootTag();
    // !!! Transfers ownership to Chunk. root will be moved to chunk internal !!!
    void setRootTag(std::unique_ptr<CompoundTag> root);
    // !!! Transfers ownership to Chunk. Data will be moved to chunk internal !!!
    void setRootTag(CompoundTag *root);

    // !!! Do not delete or reuse the item - the chunk keeps the ownership !!!
    std::vector<AbstractTag*> getSubTagsByName(const std::string &name) const;

    std::vector<int32_t> getBiomes() const;
    int32_t getBiomeAt(int blockX, int blockY, int blockZ) const;

    Block getBlockAt(const int blockX, const int blockY, const int blockZ) const;

    HeightMap getHeightMap(HeightMap::MapType mapType = HeightMap::MapType::WorldSurface) const;

protected:
    void getSubTagsByName(const std::string &name,
                          AbstractTag *currentSubTag,
                          std::vector<AbstractTag*> &subTags) const;

private:
    std::unique_ptr<CompoundTag> m_data;
};

} // namespace amc

#endif // AWESOMEMC_ANVIL_CHUNK_HPP