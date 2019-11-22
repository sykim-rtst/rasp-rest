#ifndef REST_URI_H
#define REST_URI_H

#include <cstdint>
#include <type_traits>
#include <string>
#include <vector>

#include <ara/rest/support_type.h>
#include <ara/rest/iterator.h>

namespace ara
{
namespace rest
{

    class Uri
    {
    public:
        /**
         * \brief   Used to specify a subset of a URI.
         *
         * \satisfy [SWS_REST_02308] Syntax Requirement for ara::rest::Uri::Part.
         */
        enum class Part : std::uint32_t
        {
            kScheme = 1 << 1,
            kUserInfo = 1 << 2,
            kHost = 1 << 3,
            kPort = 1 << 4,
            kPath = 1 << 5,
            kQuery = 1 << 6,
            kFragment = 1 << 7,
            kPathAndQuery = Part::kPath | Part::kQuery,
            kPathEtc = Part::kPath | Part::kQuery | Part::kFragment,
            kAll = ~std::underlying_type<Part>::type{0}
        };

        /**
         * \brief   The maximum length of a URI.
         *
         * \satisfy [SWS_REST_02309] Syntax Requirement for ara::rest::Uri::LENGTH_MAX.
         */
        static constexpr std::size_t LENGTH_MAX = 2048;

        class Builder;

        class Path;

        class Query;

    public:
        /**
         * \brief   Constructs a default URI. A default-constructed URI is empty.
         *
         * \satisfy [SWS_REST_02311] Syntax Requirement for Constructor.
         */
        Uri() = default;

        Uri(const Uri &other);
        Uri &operator=(const Uri &other);

        Uri(Uri &&other);
        Uri &operator=(Uri &&other);

        /**
         * \brief   Has scheme.
         *
         * \satisfy [SWS_REST_02312] Syntax Requirement for ara::rest::Uri::HasScheme.
         */
        bool HasScheme() const noexcept;

        /**
         * \brief   Gets scheme.
         *
         * \satisfy [SWS_REST_02313] Syntax Requirement for ara::rest::Uri::GetScheme.
         */
        String GetScheme() const noexcept;

        /**
         * \brief   Has user info.
         *
         * \satisfy [SWS_REST_02314] Syntax Requirement for ara::rest::Uri::HasUserInfo.
         */
        bool HasUserInfo() const noexcept;

        /**
         * \brief   Gets user info.
         *
         * \satisfy [SWS_REST_02315] Syntax Requirement for ara::rest::Uri::GetUserInfo.
         */
        String GetUserInfo() const noexcept;

        /**
         * \brief   Has host.
         *
         * \satisfy [SWS_REST_02316] Syntax Requirement for ara::rest::Uri::HasHost.
         */
        bool HasHost() const noexcept;

        /**
         * \brief   Gets host.
         *
         * \satisfy [SWS_REST_02317] Syntax Requirement for ara::rest::Uri::GetHost.
         */
        String GetHost() const noexcept;

        /**
         * \brief   Has port.
         *
         * \satisfy [SWS_REST_02318] Syntax Requirement for ara::rest::Uri::HasPort.
         */
        bool HasPort() const noexcept;

        /**
         * \brief   Gets port.
         *
         * \satisfy [SWS_REST_02319] Syntax Requirement for ara::rest::Uri::GetPort.
         */
        int GetPort() const noexcept;

        /**
         * \brief   Has path.
         *
         * \satisfy [SWS_REST_02320] Syntax Requirement for ara::rest::Uri::HasPath.
         */
        bool HasPath() const noexcept;

        /**
         * \brief   Gets path.
         *
         * \satisfy [SWS_REST_02321] Syntax Requirement for ara::rest::Uri::GetPath.
         */
        const Path & GetPath() const noexcept;

        /**
         * \brief   Has query.
         *
         * \satisfy [SWS_REST_02322] Syntax Requirement for ara::rest::Uri::HasQuery.
         */
        bool HasQuery() const noexcept;

        /**
         * \brief   Get query.
         *
         * \satisfy [SWS_REST_02323] Syntax Requirement for ara::rest::Uri::GetQuery.
         */
        const Query & GetQuery() const noexcept;

        /**
         * \brief   Has fragment.
         *
         * \satisfy [SWS_REST_02324] Syntax Requirement for ara::rest::Uri::HasFragment.
         */
        bool HasFragment() const noexcept;

        /**
         * \brief   Get fragment as string.
         *
         * \satisfy [SWS_REST_02325] Syntax Requirement for ara::rest::Uri::GetFragment.
         */
        String GetFragmentAs() const noexcept;

        /**
         * \brief   Converts a URI fragment part to a given type.
         *
         * \satisfy [SWS_REST_02326] Syntax Requirement for ara::rest::Uri::GetFragmentAs.
         */
        template <typename T>
        T GetFragmentAs(T &&def = {}) const;

        /**
         * \brief   Is URI empty.
         *
         * \satisfy [SWS_REST_02327] Syntax Requirement for ara::rest::Uri::IsEmpty.
         */
        bool IsEmpty() const noexcept;

        /**
         * \brief   Is URI relative. An URI is relative if it does not starts with a scheme.
         *
         * \satisfy [SWS_REST_02328] Syntax Requirement for ara::rest::Uri::IsRelative.
         */
        bool IsRelative() const noexcept;

        /**
         * \brief   Denotes whether the URI is opaque.
         *
         * \satisfy [SWS_REST_02329] Syntax Requirement for ara::rest::Uri::IsOpaque.
         */
        bool IsOpaque() const noexcept;

        /**
         * \brief   Denotes wether this URI is hierarchical.
         *
         * \satisfy [SWS_REST_02330] Syntax Requirement for ara::rest::Uri::IsHierarchical.
         */
        bool IsHierarchical() const noexcept;

    private:
        Pointer<String> scheme_;
        Pointer<String> userInfo_;
        Pointer<String> host_;
        Pointer<int> port_;
        Pointer<Path> path_;
        Pointer<Query> query_;
        Pointer<String> fragment_;
    };

    class Uri::Builder
    {
        /**
         * \unsatisfy   [SWS_REST_02269]
         *              [SWS_REST_02271]
         *              [SWS_REST_02426]
         *              [SWS_REST_02427]
         *              [SWS_REST_02273]
         *              [SWS_REST_02275]
         *              [SWS_REST_02276]
         *              [SWS_REST_02279]
         */

    public:
        /**
         * \brief   Default-constructs a builder.
         *
         * \satisfy [SWS_REST_02260] Syntax Requirement for Constructor.
         */
        Builder( /* Allocator *alloc=GetDefaultAllocator() */ );

        /**
         * \brief   Parses a URI in string format.
         *
         * \satisfy [SWS_REST_02261] Syntax Requirement for Constructor.
         */
        Builder(String uri /* , Allocator *alloc=GetDefaultAllocator() */);

        /**
         * \brief   Parses a URI in string format.
         *
         * \satisfy [SWS_REST_02262] Syntax Requirement for Constructor.
         */
        Builder(const Uri &uri /* , Allocator *alloc=GetDefaultAllocator() */);

        /**
         * \brief   Initializes this builder with an existing Uri.
         *
         * \satisfy [SWS_REST_02263] Syntax Requirement for Constructor.
         */
        Builder(Uri &&uri /* , Allocator *alloc=GetDefaultAllocator() */);

    public:
        /**
         * \brief   Set scheme by parsing the given argument.
         *
         * \satisfy [SWS_REST_02264] Syntax Requirement for ara::rest::Uri::Builder::Scheme.
         */
        Builder & Scheme(const String &value);

        /**
         * \brief   Set user info by parsing the given argument.
         *
         * \satisfy [SWS_REST_02265] Syntax Requirement for ara::rest::Uri::Builder::UserInfo.
         */
        Builder & UserInfo(const String &value);

        /**
         * \brief   Set host by parsing the given argument.
         *
         * \satisfy [SWS_REST_02266] Syntax Requirement for ara::rest::Uri::Builder::Host.
         */
        Builder & Host(const String &value);

        /**
         * \brief   Sets the the Uri port from the given argument.
         *
         * \satisfy [SWS_REST_02267] Syntax Requirement for ara::rest::Uri::Builder::Port.
         */
        Builder & Port(const String &value);

        /**
         * \brief   Sets the the Uri port from the given argument.
         */
        Builder & Port(const int value);

        /**
         * \brief   Sets the URI path by parsing the given argument.
         *
         * \satisfy [SWS_REST_02268] Syntax Requirement for ara::rest::Uri::Builder::Path.
         */
        Builder & Path(const String &value);

        /**
         * \brief   Inserts a path segment to the end of the path.
         *
         * \satisfy [SWS_REST_02425] Syntax Requirement for ara::rest::Uri::Builder::PathSegment.
         */
        Builder & PathSegment(const String &value);

        /**
         * \brief   Constructs a path from the given function arguments.
         *
         * \satisfy [SWS_REST_02270] Syntax Requirement for ara::rest::Uri::Builder::PathSegments.
         */
        Builder & PathSegments(const String &values...);

        /**
         * \brief   Sets the URI query by parsing the given argument.
         *
         * \satisfy [SWS_REST_02272] Syntax Requirement for ara::rest::Uri::Builder::Query.
         */
        Builder & Query(const String &value);

        /**
         * \brief   Inserts a query parameter (key and value).
         *
         * \satisfy [SWS_REST_02474] Syntax Requirement for ara::rest::Uri::Builder::QueryParameter.
         */
        Builder & QueryParameter(const String &key, const String &value);

        /**
         * \brief   Replaces an existing paramater.
         *
         * \satisfy [SWS_REST_02277] Syntax Requirement for ara::rest::Uri::Builder::QueryParameterAt.
         */
        Builder & QueryParameterAt(const String &key, const String &newValue);

        /**
         * \brief   Sets the fragment component of a URI.
         *
         * \satisfy [SWS_REST_02278] Syntax Requirement for ara::rest::Uri::Builder::Fragment.
         */
        Builder & Fragment(const String &value);

        /**
         * \brief   Returns a Uri.
         *
         * \satisfy [SWS_REST_02280] Syntax Requirement for ara::rest::Uri::Builder::ToUri.
         */
        Uri ToUri() const;

        /**
         * \brief   Returns a Uri path.
         *
         * \satisfy [SWS_REST_02422] Syntax Requirement for ara::rest::Uri::Builder::ToPath.
         */
        Uri::Path ToPath() const;

        /**
         * \brief   Returns a Uri query.
         *
         * \satisfy [SWS_REST_02424] Syntax Requirement for ara::rest::Uri::Builder::ToQuery.
         */
        Uri::Query ToQuery() const;

    private:
        Pointer<Uri> uri_;
    };

    class Uri::Path
    {
    public:
        class Segment;

        using IteratorRange = ara::rest::IteratorRange<std::vector<Segment>::const_iterator>;

    public:
        /**
         * \brief   Constructor for ara::rest::Uri::Path
         */
        explicit Path(const String &path);

        /**
         * \brief   Returns the number of path segments.
         *
         * \satisfy [SWS_REST_02289] Syntax Requirement for ara::rest::Uri::Builder::Path::NumSegments.
         */
        std::size_t NumSegments() const;

        /**
         * \brief   Returns a range of path segments.
         *
         * \satisfy [SWS_REST_02290] Syntax Requirement for ara::rest::Uri::Builder::Path::GetSegments.
         */
        Uri::Path::IteratorRange GetSegments() const;

    private:
        std::vector<Segment> segments_;
    };

    /**
     * \brief   Tests two paths for equality.
     *
     * \satisfy [SWS_REST_02291] Syntax Requirement for Relational Operators.
     */
    inline bool operator==(const Uri::Path &lvalue, const Uri::Path &rvalue) noexcept;

    /**
     * \brief   Tests two paths for inequality.
     *
     * \satisfy [SWS_REST_02292] Syntax Requirement for Relational Operators.
     */
    inline bool operator!=(const Uri::Path &lvalue, const Uri::Path &rvalue) noexcept;

    /**
     * \brief   Relates two paths according to their lexicographical order.
     *
     * \satisfy [SWS_REST_02293] Syntax Requirement for Relational Operators.
     */
    inline bool operator<(const Uri::Path &lvalue, const Uri::Path &rvalue) noexcept;

    class Uri::Query
    {
    public:
        class Parameter;

        using IteratorRange = ara::rest::IteratorRange<std::vector<Uri::Query::Parameter>::const_iterator>;

    public:
        /**
         * \brief   Constructor for ara::rest::Uri::Query
         */
        explicit Query(const String &query);

        /**
         * \brief   Returns the number of query parameters.
         *
         * \satisfy [SWS_REST_02302] Syntax Requirement for ara::rest::Uri::Builder::Query::NumParameters.
         */
        std::size_t NumParameters() const;

        /**
         * \brief   Returns the range of all query parameters.
         *
         * \satisfy [SWS_REST_02303] Syntax Requirement for ara::rest::Uri::Builder::Query::GetParameters.
         */
        Uri::Query::IteratorRange GetParameters() const;

        /**
         * \brief   Returns a specific query parameter by index.
         *
         * \satisfy [SWS_REST_02304] Syntax Requirement for ara::rest::Uri::Builder::Query::GetParameter.
         */
        const Parameter & GetParameter(std::size_t index) const;

        /**
         * \brief   Searches for a query parameter by key.
         *
         * \satisfy [SWS_REST_02305] Syntax Requirement for ara::rest::Uri::Builder::Query::Find.
         */
        Uri::Query::IteratorRange::Iterator Find(String key) const;

        /**
         * \brief   Tests whether a query parameter of a given key exists.
         *
         * \satisfy [SWS_REST_02306] Syntax Requirement for ara::rest::Uri::Builder::Query::HasKey.
         */
        bool HasKey(String key);

    private:
        std::vector<Uri::Query::Parameter> parameters_;
    };

    class Uri::Path::Segment
    {
    public:
        /**
         * \brief   Constructor for ara::rest::Uri::Path::Segment
         */
        explicit Segment(const String &segment);

        /**
         * \brief   Returns a string representation of this path segment.
         *
         * \satisfy [SWS_REST_02282] Syntax Requirement for ara::rest::Uri::Builder::Path::Segment::Get.
         */
        String Get() const;

        /**
         * \brief   Returns this segment converted to a user-defined type.
         *
         * \satisfy [SWS_REST_02282] Syntax Requirement for ara::rest::Uri::Builder::Path::Segment::GetAs.
         */
        template <typename T>
        T GetAs(T &&def = {}) const;

    private:
        std::string segment_;
    };

    /**
     * \brief   Tests two segments for equality.
     *
     * \satisfy [SWS_REST_02284] Syntax Requirement for Relational Operators.
     */
    inline bool operator==(const Uri::Path::Segment &lvalue, const Uri::Path::Segment &rvalue) noexcept;

    /**
     * \brief   Tests two segments for inequality.
     *
     * \satisfy [SWS_REST_02285] Syntax Requirement for Relational Operators.
     */
    inline bool operator!=(const Uri::Path::Segment &lvalue, const Uri::Path::Segment &rvalue) noexcept;

    /**
     * \brief   Compares two path segments according to their lexicographical order.
     *
     * \satisfy [SWS_REST_02286] Syntax Requirement for Relational Operators.
     */
    inline bool operator<(const Uri::Path::Segment &lvalue, const Uri::Path::Segment &rvalue) noexcept;

    class Uri::Query::Parameter
    {
    public:
        /**
         * \brief   Constructor for ara::rest::Uri::Query::Parameter
         */
        explicit Parameter(const String &parameter);

        /**
         * \brief   Returns a string representation of the parameter key
         *
         * \satisfy [SWS_REST_02295] Syntax Requirement for ara::rest::Uri::Builder::Query::Parameter::GetKey.
         */
        String GetKey() const;

        /**
         * \brief   Converts a query parameter key to the specified type.
         *
         * \satisfy [SWS_REST_02296] Syntax Requirement for ara::rest::Uri::Builder::Query::Parameter::GetKeyAs.
         */
        template <typename T>
        T GetKeyAs(T &&def = {}) const;

        /**
         * \brief   Tests whether the parameter value exists.
         *
         * \satisfy [SWS_REST_02297] Syntax Requirement for ara::rest::Uri::Builder::Query::Parameter::HasValue.
         */
        bool HasValue() const;

        /**
         * \brief   Returns a string representation of the parameter value.
         *
         * \satisfy [SWS_REST_02298] Syntax Requirement for ara::rest::Uri::Builder::Query::Parameter::GetValue.
         */
        String GetValue() const;

        /**
         * \brief   Converts a query parameter value to the specified type.
         *
         * \satisfy [SWS_REST_02299] Syntax Requirement for ara::rest::Uri::Builder::Query::Parameter::GetValueAs.
         */
        template <typename T>
        T GetValueAs(T &&def = {}) const;

    private:
        std::string key_;
        std::string value_;
    };

}
}

#endif //REST_URI_H
