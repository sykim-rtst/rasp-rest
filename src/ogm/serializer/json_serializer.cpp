#include <ara/rest/ogm/serializer/json_serializer.h>

#include <sstream>

#include <ara/rest/ogm/value.h>
#include <ara/rest/ogm/int.h>
#include <ara/rest/ogm/real.h>
#include <ara/rest/ogm/string.h>
#include <ara/rest/ogm/array.h>
#include <ara/rest/ogm/object.h>
#include <ara/rest/ogm/field.h>
#include <iostream>

namespace ara
{
namespace rest
{
namespace ogm
{

    ara::rest::String JsonSerializer::Serialize(ogm::Value &node)
    {
        ara::rest::String serializedString;
        if (node.IsInt())          serializedString = Serialize(dynamic_cast<Int&>(node));
        else if (node.IsReal())    serializedString = Serialize(dynamic_cast<Real&>(node));
        else if (node.IsString())  serializedString = Serialize(dynamic_cast<String&>(node));
        else if (node.IsArray())   serializedString = Serialize(dynamic_cast<Array&>(node));
        else if (node.IsObject())  serializedString = Serialize(dynamic_cast<Object&>(node));

        return serializedString;
    }

    ara::rest::String JsonSerializer::Serialize(ogm::Int &node)
    {
        return std::to_string(node.GetValue());
    }

    ara::rest::String JsonSerializer::Serialize(ogm::Real &node)
    {
        return std::to_string(node.GetValue());
    }

    ara::rest::String JsonSerializer::Serialize(ogm::String &node)
    {
        std::ostringstream out;
        out << "\"" << node.GetValue() << "\"";

        return out.str();
    }

    ara::rest::String JsonSerializer::Serialize(ogm::Array &node)
    {
        std::ostringstream out;
        out << "[ ";

        if (!node.IsEmpty())
        {
            auto valueIterator = node.GetValues();
            std::for_each(valueIterator.Begin(), valueIterator.End(), [this, &out](const Pointer<ogm::Value> &value)
            {
                out << Serialize(*value) << ", ";
            });
            out.seekp(-2, std::ios_base::cur);
        }
        out << " ]";

        return out.str();
    }

    ara::rest::String JsonSerializer::Serialize(ogm::Object &node)
    {
        std::ostringstream out;
        out << "{ ";

        if (!node.IsEmpty())
        {
            auto fieldIterator = node.GetFields();
            std::for_each(fieldIterator.Begin(), fieldIterator.End(), [this, &out](const Pointer<ogm::Field> &field)
            {
                out << Serialize(*field) << ", ";
            });
            out.seekp(-2, std::ios_base::cur);
        }
        out << " }";

        return out.str();
    }

    ara::rest::String JsonSerializer::Serialize(ogm::Field &node)
    {
        std::ostringstream out;
        out << "\"" << node.GetName() << "\" : " << Serialize(node.GetValue());

        return out.str();
    }

    Pointer<Value> JsonSerializer::DeserializeToValue(const ara::rest::String &binary)
    {
        if( IsArray(binary) )           return DeserializeToArray(binary);
        else if( IsObject(binary) )     return DeserializeToObject(binary);
        else if( IsInt(binary) )        return DeserializeToInt(binary);
        else if( IsReal(binary) )       return DeserializeToReal(binary);
        else                            return DeserializeToString(binary);
    }

    Pointer<Int> JsonSerializer::DeserializeToInt(const ara::rest::String &binary)
    {
        return Int::Make(std::stoll(binary));
    }

    Pointer<Real> JsonSerializer::DeserializeToReal(const ara::rest::String &binary)
    {
        return Real::Make(std::stold(binary));
    }

    Pointer<String> JsonSerializer::DeserializeToString(const ara::rest::String &binary)
    {
        return String::Make(binary.substr(1, binary.size() - 2));
    }

    Pointer<Array> JsonSerializer::DeserializeToArray(const ara::rest::String &binary)
    {
        auto array = Array::Make();

        std::stringstream token;
        int depth = 0; bool isString = false;
        std::for_each(binary.begin() + 1, binary.end(), [this, &token, &depth, &array, &isString](auto &c)
        {
            switch (c)
            {
                case ',':
                    if (depth == 0)
                    {
                        array->Append(DeserializeToValue(token.str()));
                        token.str("");
                    }
                    else token << c;
                    break;
                case '[':
                case '{':
                    token << c; depth++;
                    break;
                case ']':
                    depth--;
                    if (depth < 0) array->Append(DeserializeToValue(token.str()));
                    else token << c;
                    break;
                case '}':
                    token << c; depth--;
                    break;
                case ' ':
                    if (isString) token << c;
                    break;
                case '"':
                    isString = !isString;
                default:
                    token << c;
            }
        });

        return array;
    }

    Pointer<Object> JsonSerializer::DeserializeToObject(const ara::rest::String &binary)
    {
        auto object = Object::Make();

        std::stringstream token;
        int depth = 0; bool isString = false;
        std::for_each(binary.begin() + 1, binary.end(), [this, &token, &depth, &isString, &object](auto &c)
        {
            switch (c)
            {
                case ',':
                    if (depth == 0)
                    {
                        object->Insert(DeserializeToField(token.str()));
                        token.str("");
                    }
                    else if (!isString)
                    {
                        token << c;
                    }
                    break;
                case '[':
                case '{':
                    token << c; depth++;
                    break;
                case ']':
                    token << c; depth--;
                    break;
                case '}':
                    depth--;
                    if (depth < 0) object->Insert(DeserializeToField(token.str()));
                    else token << c;
                    break;
                case ' ':
                    if (isString) token << c;
                    break;
                case '"':
                    isString = !isString;
                default:
                    token << c;
            }
        });

        return object;
    }

    Pointer<Field> JsonSerializer::DeserializeToField(const ara::rest::String &binary)
    {
        auto key = binary.substr(1, binary.find(":") - 2);
        auto value = DeserializeToValue(binary.substr(binary.find(":") + 1));

        return Field::Make(key, std::move(value));
    }

    bool JsonSerializer::IsInt(const ara::rest::String &jsonString)
    {
        bool result = true;

        try
        {
            std::stoll(jsonString);
        }
        catch (const std::invalid_argument& e)
        {
            result = false;
        }

        return result;
    }

    bool JsonSerializer::IsReal(const ara::rest::String &jsonString)
    {
        bool result = true;

        try
        {
            std::stold(jsonString);
        }
        catch (const std::invalid_argument& e)
        {
            result = false;
        }

        return result;
    }

    bool JsonSerializer::IsArray(const ara::rest::String &jsonString)
    {
        return jsonString[0] == '[';
    }

    bool JsonSerializer::IsObject(const ara::rest::String &jsonString)
    {
        return jsonString[0] == '{';
    }

}
}
}