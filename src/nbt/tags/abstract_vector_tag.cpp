#include <AwesomeMC/nbt/tags/abstract_vector_tag.hpp>

// STL
#include <cassert>
#include <utility>
#include <stdexcept>

namespace nbt
{

AbstractVectorTag::AbstractVectorTag()
    : AbstractTag()
    , m_value{}
{

}

AbstractVectorTag::AbstractVectorTag(const AbstractVectorTag &other)
    : AbstractTag(other.m_name)
{
    copy(other.m_value);
}

AbstractVectorTag::AbstractVectorTag(AbstractVectorTag &&other) noexcept
    : AbstractTag(std::move(other.m_name))
    , m_value{std::move(other.m_value)}
{

}

AbstractVectorTag::AbstractVectorTag(const std::string &name)
    : AbstractTag(name)
    , m_value{}
{

}

AbstractVectorTag::~AbstractVectorTag()
{
    clear();
}

AbstractVectorTag& AbstractVectorTag::operator=(const AbstractVectorTag &other)
{
    if(this != &other) {
        m_name = other.m_name;
        copy(other.m_value);
    }
    return *this;
}

AbstractVectorTag& AbstractVectorTag::operator=(AbstractVectorTag &&other) noexcept
{
    if(this != &other) {
        m_name = std::move(other.m_name);

        // Delete old data before adding new data
        clear();
        m_value = std::move(other.m_value);
    }
    return *this;
}

void AbstractVectorTag::setValue(std::vector<AbstractTag*> &value)
{
    copy(value);
}

std::vector<AbstractTag*>& AbstractVectorTag::getValue()
{
    return m_value;
}

const std::vector<AbstractTag*>& AbstractVectorTag::getValue() const
{
    return m_value;
}

std::vector<AbstractTag*> AbstractVectorTag::getValueCopy() const
{
    std::vector<AbstractTag*> valueCopy(m_value.size(), nullptr);
    for(size_t i = 0; i < m_value.size(); ++i) {
        valueCopy[i] = m_value[i]->clone();
    }

    return valueCopy;
}

void AbstractVectorTag::clear()
{
    // Delete all objects stored in the container
    for(auto ptr : m_value) {
        // Check that ptr is not nullptr (we never know)
        if(ptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
    m_value.clear();
}

bool AbstractVectorTag::isEqual(const AbstractTag &other) const
{
    const AbstractVectorTag &otherTag = static_cast<const AbstractVectorTag&>(other);

    if(m_name != otherTag.m_name
       || getType() != otherTag.getType()
       || m_value.size() != otherTag.m_value.size()) {
        return false;
    }

    for(size_t i = 0; i < m_value.size(); ++i) {
        if(*m_value[i] != *otherTag.m_value[i]) {
            return false;
        }
    }
    return true;
}

void AbstractVectorTag::copy(const std::vector<AbstractTag*> &otherValue)
{
    clear();

    // Resize container to other size
    m_value.resize(otherValue.size());

    // Clone other data elements
    for(size_t i = 0; i < otherValue.size(); ++i) {
        m_value[i] = otherValue[i]->clone();
    }
}

bool AbstractVectorTag::erase(size_t index)
{
    if(index >= m_value.size()) {
        return false;
    } else {
        if(m_value[index] != nullptr) {
            delete m_value[index];
        }
        m_value.erase(m_value.begin() + index);
        return true;
    }
}

AbstractTag* AbstractVectorTag::takeAt(size_t index)
{
    AbstractTag *tag = at(index);
    m_value.erase(m_value.begin() + index);
    return tag;
}

AbstractTag* AbstractVectorTag::at(size_t index)
{
    if(index >= m_value.size()) {
        throw std::out_of_range("Index out of range!");
    }
    return m_value.at(index);
}

const AbstractTag* AbstractVectorTag::at(size_t index) const
{
    if(index >= m_value.size()) {
        throw std::out_of_range("Index out of range!");
    }
    return m_value.at(index);
}

AbstractTag* AbstractVectorTag::operator[](const size_t index)
{
    assert(index <= m_value.size());
    return m_value[index];
}

const AbstractTag* AbstractVectorTag::operator[](const size_t index) const
{
    assert(index <= m_value.size());
    return m_value[index];
}

bool AbstractVectorTag::insert(size_t index, AbstractTag *value)
{
    if(!value || index > m_value.size()) {
        return false;
    } else {
        m_value.insert(m_value.begin() + index, value);
        return true;
    }
}

bool AbstractVectorTag::pushBack(AbstractTag* value)
{
    if(!value) {
        return false;
    } else {
        m_value.push_back(value);
        return true;
    }
}

} // namespace nbt