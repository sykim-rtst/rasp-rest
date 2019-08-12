#include <ara/rest/uri.h>
#include <sstream>
#include <iostream>

namespace ara
{
namespace rest
{
    /**
     * ara::rest::Uri Constructors
     */
    Uri::Uri(const Uri &other)
    {
        if (other.scheme_) scheme_ = std::make_unique<String>(other.GetScheme());
        if (other.userInfo_) userInfo_ = std::make_unique<String>(other.GetUserInfo());
        if (other.host_) host_ = std::make_unique<String>(other.GetHost());
        if (other.port_) port_ = std::make_unique<int>(other.GetPort());
        if (other.path_) path_ = std::make_unique<Uri::Path>(other.GetPath());
        if (other.query_) query_ = std::make_unique<Uri::Query>(other.GetQuery());
        if (other.fragment_) fragment_ = std::make_unique<String>(other.GetFragmentAs());
    }

    Uri &Uri::operator=(const Uri &other)
    {
        if (other.scheme_) scheme_ = std::make_unique<String>(other.GetScheme());
        if (other.userInfo_) userInfo_ = std::make_unique<String>(other.GetUserInfo());
        if (other.host_) host_ = std::make_unique<String>(other.GetHost());
        if (other.port_) port_ = std::make_unique<int>(other.GetPort());
        if (other.path_) path_ = std::make_unique<Uri::Path>(other.GetPath());
        if (other.query_) query_ = std::make_unique<Uri::Query>(other.GetQuery());
        if (other.fragment_) fragment_ = std::make_unique<String>(other.GetFragmentAs());

        return *this;
    }

    Uri::Uri(Uri &&other)
    {
        scheme_ = std::move(other.scheme_);
        userInfo_ = std::move(other.userInfo_);
        host_ = std::move(other.host_);
        port_ = std::move(other.port_);
        path_ = std::move(other.path_);
        query_ = std::move(other.query_);
        fragment_ = std::move(other.fragment_);
    }

    Uri &Uri::operator=(Uri &&other)
    {
        scheme_ = std::move(other.scheme_);
        userInfo_ = std::move(other.userInfo_);
        host_ = std::move(other.host_);
        port_ = std::move(other.port_);
        path_ = std::move(other.path_);
        query_ = std::move(other.query_);
        fragment_ = std::move(other.fragment_);

        return *this;
    }

    /**
     * ara::rest::Uri Member Functions
     */
    bool Uri::HasScheme() const noexcept
    {
        return (scheme_ != nullptr);
    }

    String Uri::GetScheme() const noexcept
    {
        return (scheme_) ? *scheme_ : "";
    }

    bool Uri::HasUserInfo() const noexcept
    {
        return (userInfo_ != nullptr);
    }

    String Uri::GetUserInfo() const noexcept
    {
        return (userInfo_) ? *userInfo_ : "";
    }

    bool Uri::HasHost() const noexcept
    {
        return (host_ != nullptr);
    }

    String Uri::GetHost() const noexcept
    {
        return (host_) ? *host_ : "";
    }

    bool Uri::HasPort() const noexcept
    {
        return (port_ != nullptr);
    }

    int Uri::GetPort() const noexcept
    {
        return (port_) ? *port_ : 0;
    }

    bool Uri::HasPath() const noexcept
    {
        return (path_ != nullptr);
    }

    const Uri::Path &Uri::GetPath() const noexcept
    {
        return *path_;
    }

    bool Uri::HasQuery() const noexcept
    {
        return (query_ != nullptr);
    }

    const Uri::Query &Uri::GetQuery() const noexcept
    {
        return *query_;
    }

    bool Uri::HasFragment() const noexcept
    {
        return (fragment_ != nullptr);
    }

    String Uri::GetFragmentAs() const noexcept
    {
        return (fragment_) ? *fragment_ : "";
    }

    template<typename T>
    T Uri::GetFragmentAs(T &&def) const
    {
        return nullptr;
    }

    bool Uri::IsEmpty() const noexcept
    {
        return !(HasFragment() || HasHost() || HasPath() || HasPort() || HasScheme() || HasUserInfo() || HasQuery());
    }

    bool Uri::IsRelative() const noexcept
    {
        return !HasScheme();
    }

    bool Uri::IsOpaque() const noexcept
    {
        return HasScheme() /* && does not begin with a slash character (’/’) */;
    }

    bool Uri::IsHierarchical() const noexcept
    {
        return IsRelative() || !IsOpaque();
    }

    /**
     * ara::rest::Uri::Builder Constructors
     */
    Uri::Builder::Builder() : uri_(std::make_unique<Uri>())
    {

    }

    Uri::Builder::Builder(String uri)
    {
        uri_ = std::make_unique<Uri>();

        std::istringstream uriStream(uri);

        String token;
        std::getline(uriStream, token, ':');

        Scheme(token);

        if (uri.find("//") != String::npos)
        {
            uriStream.ignore(2);

            if (uri.find("@") != String::npos)
            {
                std::getline(uriStream, token, '@');
                UserInfo(token);
            }

            if (uri.find(":") != uri.rfind(":"))
            {
                std::getline(uriStream, token, ':');
                Host(token);

                std::getline(uriStream, token, '/');
                Port(token);
            }
            else
            {
                std::getline(uriStream, token, '/');
                Host(token);
            }
        }

        if (uri.find('?') != String::npos)
        {
            std::getline(uriStream, token, '?');
            Path("/" + token);

            std::getline(uriStream, token, '#');
            Query(token);

            if (!uriStream.eof()) {
                std::getline(uriStream, token);
                Fragment(token);
            }
        }
        else if (uri.find('#') != String::npos)
        {
            std::getline(uriStream, token, '#');
            Path("/" + token);

            std::getline(uriStream, token);
            Fragment(token);
        }
        else
        {
            std::getline(uriStream, token);
            Path("/" + token);
        }
    }

    Uri::Builder::Builder(const Uri &uri) : uri_(std::make_unique<Uri>(uri))
    {

    }

    Uri::Builder::Builder(Uri &&uri) : uri_(std::make_unique<Uri>(uri))
    {

    }

    /**
     * ara::rest::Uri::Builder Member Functions
     */
    Uri::Builder &Uri::Builder::Scheme(const String &value)
    {
        if (uri_->HasScheme())
        {
            uri_->scheme_.reset();
        }

        uri_->scheme_ = std::make_unique<std::string>(value);

        return *this;
    }

    Uri::Builder &Uri::Builder::UserInfo(const String &value)
    {
        if (uri_->HasUserInfo())
        {
            uri_->userInfo_.reset();
        }

        uri_->userInfo_ = std::make_unique<std::string>(value);

        return *this;
    }

    Uri::Builder &Uri::Builder::Host(const String &value)
    {
        if (uri_->HasHost())
        {
            uri_->host_.reset();
        }

        uri_->host_ = std::make_unique<std::string>(value);

        return *this;
    }

    Uri::Builder &Uri::Builder::Port(const String &value)
    {
        if (uri_->HasPort())
        {
            uri_->port_.reset();
        }

        char *str_end;
        auto portNumber = std::strtol(value.data(), &str_end, 10);
        if (portNumber > 0)
        {
            uri_->port_ = std::make_unique<int>(portNumber);
        }

        return *this;
    }

    Uri::Builder &Uri::Builder::Port(const int value)
    {
        if (uri_->HasPort())
        {
            uri_->port_.reset();
        }

        if (value > 0)
        {
            uri_->port_ = std::make_unique<int>(value);
        }

        return *this;
    }

    Uri::Builder &Uri::Builder::Path(const String &value)
    {
        if (uri_->HasPath())
        {
            uri_->path_.reset();
        }

        uri_->path_ = std::make_unique<Uri::Path>(value);

        return *this;
    }

    Uri::Builder &Uri::Builder::PathSegment(const String &value)
    {
        return *this;
    }

    Uri::Builder &Uri::Builder::PathSegments(const String &values, ...)
    {
        return *this;
    }

    Uri::Builder &Uri::Builder::Query(const String &value)
    {
        if (uri_->HasQuery())
        {
            uri_->query_.reset();
        }

        uri_->query_ = std::make_unique<Uri::Query>(value);

        return *this;
    }

    Uri::Builder &Uri::Builder::QueryParameter(const String &key, const String &value)
    {
        return *this;
    }

    Uri::Builder &Uri::Builder::QueryParameterAt(const String &key, const String &newValue)
    {
        return *this;
    }

    Uri::Builder &Uri::Builder::Fragment(const String &value)
    {
        if (uri_->HasFragment())
        {
            uri_->fragment_.reset();
        }

        uri_->fragment_ = std::make_unique<std::string>(value);

        return *this;
    }

    Uri Uri::Builder::ToUri() const
    {
        return *uri_;
    }

    Uri::Path Uri::Builder::ToPath() const
    {
        return *(uri_->path_);
    }

    Uri::Query Uri::Builder::ToQuery() const
    {
        return *(uri_->query_);
    }

    /**
     * ara::rest::Uri::Path Constructors
     */
    Uri::Path::Path(const String &path)
            : segments_({})
    {
        std::istringstream pathStream(path);

        String segment;
        while (std::getline(pathStream, segment, '/'))
        {
            if (segment.length() > 0)
            {
                segments_.emplace_back(segment);
            }
        }
    }

    /**
     * ara::rest::Uri::Path Member Functions
     */
    std::size_t Uri::Path::NumSegments() const
    {
        return segments_.size();
    }

    Uri::Path::IteratorRange Uri::Path::GetSegments() const
    {
        return ara::rest::Uri::Path::IteratorRange(segments_.begin(), segments_.end());
    }

    /**
     * ara::rest::Uri::Query Constructors
     */
    Uri::Query::Query(const String &query)
            : parameters_({})
    {
        std::istringstream queryStream(query);

        String parameter;
        while (std::getline(queryStream, parameter, '&'))
        {
            if (parameter.length() > 0)
            {
                parameters_.emplace_back(parameter);
            }
        }

    }

    /**
     * ara::rest::Uri::Query Member Functions
     */
    std::size_t Uri::Query::NumParameters() const
    {
        return parameters_.size();
    }

    const Uri::Query::Parameter &Uri::Query::GetParameter(std::size_t index) const
    {
        return parameters_.at(index);
    }

    Uri::Query::IteratorRange::Iterator Uri::Query::Find(String key) const
    {
        return std::find_if(parameters_.begin(), parameters_.end(),
                            [&](const Parameter &parameter) { return key == parameter.GetKey(); });
    }

    bool Uri::Query::HasKey(String key)
    {
        return std::any_of(parameters_.begin(), parameters_.end(),
                           [&](const Parameter &parameter) { return key == parameter.GetKey(); });
    }

    Uri::Query::IteratorRange Uri::Query::GetParameters() const
    {
        return ara::rest::Uri::Query::IteratorRange(parameters_.begin(), parameters_.end());
    }

    /**
     * ara::rest::Uri::Path::Segment Constructors
     */

    Uri::Path::Segment::Segment(const String &segment)
            : segment_()
    {
        if (segment.length() > 0)
        {
            segment_ = segment;
        }
    }

    /**
     * ara::rest::Uri::Path::Segment Member Functions
     */
    String Uri::Path::Segment::Get() const
    {
        return segment_;
    }

    template<typename T>
    T Uri::Path::Segment::GetAs(T &&def) const
    {
        return static_cast<T>(segment_);
    }

    /**
     * ara::rest::Uri::Query::Parameter Constructors
     */
    Uri::Query::Parameter::Parameter(const String &parameter)
            : key_(), value_()
    {
        if (parameter.length() > 0)
        {
            std::size_t delimiterPosition = parameter.find_first_of("=");
            if (delimiterPosition != std::string::npos)
            {
                key_ = parameter.substr(0, delimiterPosition);
                value_ = parameter.substr(delimiterPosition + 1);
            }
        }
    }

    /**
     * ara::rest::Uri::Query::Parameter Member Functions
     */
    String Uri::Query::Parameter::GetKey() const
    {
        return key_;
    }

    template<typename T>
    T Uri::Query::Parameter::GetKeyAs(T &&def) const
    {
        return static_cast<T>(key_);
    }

    bool Uri::Query::Parameter::HasValue() const
    {
        return (value_.length() > 0);
    }

    String Uri::Query::Parameter::GetValue() const
    {
        return value_;
    }

    template<typename T>
    T Uri::Query::Parameter::GetValueAs(T &&def) const
    {
        return static_cast<T>(value_);
    }

}
}