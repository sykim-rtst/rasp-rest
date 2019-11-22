#ifndef REST_JSON_SERIALIZER_H
#define REST_JSON_SERIALIZER_H

#include <ara/rest/ogm/serializer/serializer.h>

namespace ara
{
namespace rest
{
namespace ogm
{

    class JsonSerializer : public Serializer
    {
    public:
        using Serializer::Serializer;

        ara::rest::String Serialize(ogm::Value &node) override;
        ara::rest::String Serialize(ogm::Int &node) override;
        ara::rest::String Serialize(ogm::Real &node) override;
        ara::rest::String Serialize(ogm::String &node) override;
        ara::rest::String Serialize(ogm::Array &node) override;
        ara::rest::String Serialize(ogm::Object &node) override;
        ara::rest::String Serialize(ogm::Field &node) override;

    protected:
        Pointer<Value> DeserializeToValue(const ara::rest::String &binary) override;
        Pointer<Int> DeserializeToInt(const ara::rest::String &binary) override;
        Pointer<Real> DeserializeToReal(const ara::rest::String &binary) override;
        Pointer<String> DeserializeToString(const ara::rest::String &binary) override;
        Pointer<ara::rest::ogm::Array> DeserializeToArray(const ara::rest::String &binary) override;
        Pointer<ara::rest::ogm::Object> DeserializeToObject(const ara::rest::String &binary) override;
        Pointer<ara::rest::ogm::Field> DeserializeToField(const ara::rest::String &binary) override;

    private:
        friend SerializerFactory;
        JsonSerializer() = default;

        bool IsInt(const ara::rest::String &jsonString);
        bool IsReal(const ara::rest::String &jsonString);
        bool IsArray(const ara::rest::String &jsonString);
        bool IsObject(const ara::rest::String &jsonString);
    };

}
}
}

#endif //REST_JSON_SERIALIZER_H
