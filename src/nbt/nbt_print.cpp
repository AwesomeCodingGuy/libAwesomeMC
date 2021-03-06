#include <AwesomeMC/nbt/nbt_print.hpp>

// AwesomeMC
#include <AwesomeMC/nbt/tags/tags.hpp>

// STL
#include <string>
#include <iomanip>
#include <sstream>

namespace amc
{

std::string printNbtData(const AbstractTag *root,
                         bool printArrayContent)
{
    std::stringstream sstr;

    if(root->getType() != TagType::End) {
        printNbtChildTag(root, sstr, Indent(), printArrayContent);
    }

    return sstr.str();
}

void printNbtChildTag(const AbstractTag *tag,
                      std::stringstream &sstr,
                      Indent indent,
                      bool printArrayContent)
{
    switch(tag->getType())
    {
        case TagType::End:
        {
            break;
        }
        case TagType::Byte:
        {
            const ByteTag &t = *tag_cast<const ByteTag*>(tag);
            sstr << indent << printTagName(t) << printTagValue(t);
            break;
        }
        case TagType::Short:
        {
            const ShortTag &t = *tag_cast<const ShortTag*>(tag);
            sstr << indent << printTagName(t) << printTagValue(t);
            break;
        }
        case TagType::Int:
        {
            const IntTag &t = *tag_cast<const IntTag*>(tag);
            sstr << indent << printTagName(t) << printTagValue(t);
            break;
        }
        case TagType::Long:
        {
            const LongTag &t = *tag_cast<const LongTag*>(tag);
            sstr << indent << printTagName(t) << printTagValue(t);
            break;
        }
        case TagType::Float:
        {
            const FloatTag &t = *tag_cast<const FloatTag*>(tag);
            sstr << indent << printTagName(t) << printTagValue(t);
            break;
        }
        case TagType::Double:
        {
            const DoubleTag &t = *tag_cast<const DoubleTag*>(tag);
            sstr << indent << printTagName(t) << printTagValue(t);
            break;
        }
        case TagType::ByteArray:
        {
            const ByteArrayTag &t = *tag_cast<const ByteArrayTag*>(tag);
            sstr << indent << printTagName(t);
            sstr << printTagValue(t, indent, printArrayContent);
            break;
        }
        case TagType::String:
        {
            const StringTag &t = *tag_cast<const StringTag*>(tag);
            sstr << indent << printTagName(t) << printTagValue(t);
            break;
        }
        case TagType::List:
        {
            const ListTag &t = *tag_cast<const ListTag*>(tag);
            sstr << indent << printTagName(t);
            sstr << "\n" << indent++ << "{\n";
            for(const AbstractTag *childTag : t) {
                printNbtChildTag(childTag, sstr, indent);
            }
            sstr << --indent << "}\n";
            break;
        }
        case TagType::Compound:
        {
            const CompoundTag &t = *tag_cast<const CompoundTag*>(tag);
            sstr << indent << printTagName(t);
            sstr << "\n" << indent++ << "{\n";
            for(const AbstractTag *childTag : t) {
                printNbtChildTag(childTag, sstr, indent);
            }
            sstr << --indent << "}\n";
            break;
        }
        case TagType::IntArray:
        {
            const IntArrayTag &t = *tag_cast<const IntArrayTag*>(tag);
            sstr << indent << printTagName(t);
            sstr << printTagValue(t, indent, printArrayContent);
            break;
        }
        case TagType::LongArray:
        {
            const LongArrayTag &t = *tag_cast<const LongArrayTag*>(tag);
            sstr << indent << printTagName(t);
            sstr << printTagValue(t, indent, printArrayContent);
            break;
        }
        default:
            break;
    }
}

} // namespace amc