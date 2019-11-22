#ifndef REST_NODE_H
#define REST_NODE_H

#include <ara/rest/support_type.h>
#include <ara/rest/ogm/util.h>
#include <ara/rest/ogm/serializer/serializer.h>
#include <ara/rest/ogm/serializer/serializer_factory.h>

namespace ara
{
namespace rest
{
namespace ogm
{
    enum class NodeType : std::uint8_t
    {
        Undefined,
        Field,
        Int,
        Real,
        String,
        Bool,
        Array,
        Object
    };

    class Node
    {
    public:
        /**
         * \brief   Type of this OGM node.
         *
         * \satisfy [SWS_REST_02090] Syntax Requirement for ara::rest::ogm::Node::SelfType.
         */
        using SelfType = Node;

        /**
         * \brief   Type of its parent in the OGM type hierarchy.
         *
         * \satisfy [SWS_REST_02091] Syntax Requirement for ara::rest::ogm::Node::ParentType.
         */
        using ParentType = void;

    public:
        /**
         * \brief   Non-copyable Constructor & Assignment Operator.
         *
         * \satisfy [SWS_REST_01403] ara::rest::Client shall not be copyable.
         * \satisfy [SWS_REST_02010] Syntax Requirement for Constructor.
         * \satisfy [SWS_REST_02011] Syntax Requirement for Assignment Operator.
         */
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;

        /**
         * \brief   Default Move Constructor & Assignment Operator.
         */
        Node(Node&&) = default;
        Node&operator=(Node&&) = default;

        virtual ~Node() = default;

    public:
        /**
         * \brief   Returns a (strongly-typed) pointer to its parent node.
         *
         * \satisfy [SWS_REST_02092] Syntax Requirement for ara::rest::ogm::Node::GetParent.
         */
        ParentType *GetParent() noexcept;

        /**
         * \brief   Returns a (strongly-typed) pointer to its parent node.
         *
         * \satisfy [SWS_REST_02093] Syntax Requirement for ara::rest::ogm::Node::GetParent.
         */
        const ParentType *GetParent() const noexcept;

        /**
         * \brief   Denotes whether this node has a structural parent.
         *
         * \satisfy [SWS_REST_02094] Syntax Requirement for ara::rest::ogm::Node::HasParent.
         */
        bool HasParent() const;

        bool IsInt() const      { return type_ == NodeType::Int; }
        bool IsReal() const     { return type_ == NodeType::Real; }
        bool IsString() const   { return type_ == NodeType::String; }
        bool IsBool() const     { return type_ == NodeType::Bool; }
        bool IsArray() const    { return type_ == NodeType::Array; }
        bool IsObject() const   { return type_ == NodeType::Object; }
        bool IsField() const    { return type_ == NodeType::Field; }

        ara::rest::String Serialize()
        {
            return Serializer::Serialize(this);
        }

    protected:
        /**
         * \brief   Constructs a node. Inaccessible to the user.
         *
         * \satisfy [SWS_REST_02100] Syntax Requirement for Constructor.
         */
        Node(NodeType type = NodeType::Undefined) : type_(type) {}

    private:
        ParentType *parant_;
        NodeType type_;
    };

}
}
}

#endif //REST_NODE_H
