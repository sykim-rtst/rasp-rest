#ifndef REST_SERIALIZER_FACTORY_H
#define REST_SERIALIZER_FACTORY_H

#include <ara/rest/ogm/serializer/serializer.h>
#include <ara/rest/ogm/serializer/json_serializer.h>

namespace ara
{
namespace rest
{
namespace ogm
{
    class SerializerFactory
    {
    public:
        static Serializer *CreateSerializer(const ara::rest::String &contentType)
        {
            if (contentType.compare("application/json") == 0)
            {
                return new JsonSerializer();
            }
            else
            {
                return new JsonSerializer();
            }
        }
    };

}
}
}

#endif //REST_SERIALIZER_FACTORY_H