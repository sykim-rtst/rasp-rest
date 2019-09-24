#include <ara/rest/ogm/serializer/serializer.h>

#include <ara/rest/ogm/value.h>
#include <ara/rest/ogm/int.h>
#include <ara/rest/ogm/real.h>
#include <ara/rest/ogm/string.h>
#include <ara/rest/ogm/array.h>
#include <ara/rest/ogm/object.h>
#include <ara/rest/ogm/field.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    ara::rest::String Serializer::Serialize(ogm::Node *node)
    {
        static auto serializer = SerializerFactory::CreateSerializer("application/json");

        ara::rest::String serializedString;
        if (node->IsInt())          serializedString = serializer->Serialize(dynamic_cast<Int&>(*node));
        else if (node->IsReal())    serializedString = serializer->Serialize(dynamic_cast<Real&>(*node));
        else if (node->IsString())  serializedString = serializer->Serialize(dynamic_cast<String&>(*node));
        else if (node->IsArray())   serializedString = serializer->Serialize(dynamic_cast<Array&>(*node));
        else if (node->IsObject())  serializedString = serializer->Serialize(dynamic_cast<Object&>(*node));
        else if (node->IsField())   serializedString = serializer->Serialize(dynamic_cast<Field&>(*node));

        return serializedString;
    }

    Pointer<Object> Serializer::Deserialize(const ara::rest::String &binary)
    {
        ara::rest::String dump(binary);
        dump.erase(remove_if(dump.begin(), dump.end(), [](auto &c) { return isspace(c) && c != ' ';} ), dump.end());
        static auto deserializer = SerializerFactory::CreateSerializer("application/json");

        return deserializer->DeserializeToObject(dump);
    }

}
}
}