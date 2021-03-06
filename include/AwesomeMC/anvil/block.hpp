#ifndef AWESOMEMC_ANVIL_BLOCK_HPP
#define AWESOMEMC_ANVIL_BLOCK_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/compound_tag.hpp>

// STL
#include <string>

namespace amc
{

class Block
{
public:
    Block();
    Block(const Block &other);
    Block(Block &&other) noexcept;
    Block(int x, int y, int z, const std::string &name);
    Block(int x, int y, int z, const std::string &name, const CompoundTag &properties);
    ~Block();

    Block& operator=(const Block &other);
    Block& operator=(Block &&other) noexcept;

    bool operator==(const Block &other);
    bool operator!=(const Block &other);

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    int getZ() const;
    void setZ(int z);

    void setXYZ(int x, int y, int z);

    std::string getName() const;
    void setName(const std::string &name);

    CompoundTag getProperties() const;
    void setProperties(const CompoundTag &properties);

private:
    int m_x;
    int m_y;
    int m_z;
    std::string m_name;
    CompoundTag m_properties;
};

} // namespace amc

#endif // AWESOMEMC_ANVIL_BLOCK_HPP
