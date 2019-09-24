#ifndef REST_SERIALIZER_H
#define REST_SERIALIZER_H

#include <ara/rest/support_type.h>

namespace ara
{
namespace rest
{
namespace ogm
{
    class SerializerFactory;

    class Node;
    class Value;
    class Int;
    class Real;
    class String;
    class Array;
    class Object;
    class Field;

    class Serializer
    {
    public:
        friend SerializerFactory;
        friend Value;
        friend Int;
        friend Real;
        friend String;
        friend Array;
        friend Object;
        friend Field;

        static ara::rest::String Serialize(ogm::Node *node);

        static Pointer<Object> Deserialize(const ara::rest::String &string);

    protected:
        virtual ara::rest::String Serialize(ogm::Value &node) = 0;
        virtual ara::rest::String Serialize(ogm::Int &node) = 0;
        virtual ara::rest::String Serialize(ogm::Real &node) = 0;
        virtual ara::rest::String Serialize(ogm::String &node) = 0;
        virtual ara::rest::String Serialize(ogm::Array &node) = 0;
        virtual ara::rest::String Serialize(ogm::Object &node) = 0;
        virtual ara::rest::String Serialize(ogm::Field &node) = 0;

        virtual Pointer<Value> DeserializeToValue(const ara::rest::String &binary) = 0;
        virtual Pointer<Int> DeserializeToInt(const ara::rest::String &binary) = 0;
        virtual Pointer<Real> DeserializeToReal(const ara::rest::String &binary) = 0;
        virtual Pointer<String> DeserializeToString(const ara::rest::String &binary) = 0;
        virtual Pointer<Array> DeserializeToArray(const ara::rest::String &binary) = 0;
        virtual Pointer<Object> DeserializeToObject(const ara::rest::String &binary) = 0;
        virtual Pointer<Field> DeserializeToField(const ara::rest::String &binary) = 0;

    protected:
        Serializer() = default;
        virtual ~Serializer() = default;
    };

}
}
}

#endif //REST_SERIALIZER_H
