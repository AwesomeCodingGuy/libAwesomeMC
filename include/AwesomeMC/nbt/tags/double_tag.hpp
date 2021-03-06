#ifndef AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP
#define AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP

// AwesomeMC
#include <AwesomeMC/nbt/tags/value_tag.hpp>
#include <AwesomeMC/util/floating_point.hpp>

namespace amc
{

template<>
inline bool ValueTag<double, TagType::Double>::isEqual(const AbstractTag &other) const
{
    const ValueTag<double, TagType::Double> &otherTag = static_cast<const ValueTag<double, TagType::Double>&>(other);

    return m_name == otherTag.m_name
        && getType() == otherTag.getType()
        && almostEqualUlps(m_value, otherTag.m_value, static_cast<int64_t>(10));
}

using DoubleTag = ValueTag<double, TagType::Double>;

} // namespace amc

#endif // AWESOMEMC_NBT_TAGS_DOUBLE_TAG_HPP