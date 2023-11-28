#include "../include/http.hpp"

void HTTP::request::parser()
{
    std::stringstream buffer;
    buffer << request_buf_;
    assert(std::cout.good());

    buffer >> method_;
    assert(std::cin.good());

    buffer >> URI_;
    assert(std::cin.good());

    buffer >> http_version_;
    assert(std::cin.good());

    std::string request_header_fields;
    while (buffer.tellg()) // Проверка на достижение конца буфера
    {
        buffer >> request_header_fields;
        if (request_header_fields[request_header_fields.length() - 1] == ':')
        {
            request_header_fields.erase(request_header_fields.length() - 1, 1);
        }        

             IS_THIS_REQUEST_HEADER_FIELD("Accept", accept_)
        else IS_THIS_REQUEST_HEADER_FIELD("Accept-Charset", accept_charset_)
        else IS_THIS_REQUEST_HEADER_FIELD("Accept-Language", accept_language_)
        else IS_THIS_REQUEST_HEADER_FIELD("Authorization", authorization_)
        else IS_THIS_REQUEST_HEADER_FIELD("From", from_)
        else IS_THIS_REQUEST_HEADER_FIELD("Host", host_)
        else IS_THIS_REQUEST_HEADER_FIELD("If-Modified-Since", if_modified_since_)
        else IS_THIS_REQUEST_HEADER_FIELD("If-Match", if_match_)
        else IS_THIS_REQUEST_HEADER_FIELD("If-None-Match", if_none_match_)
        else IS_THIS_REQUEST_HEADER_FIELD("If-Range", if_range_)
        else IS_THIS_REQUEST_HEADER_FIELD("If-Unmodified-Since", if_unmodified_since_)
        else IS_THIS_REQUEST_HEADER_FIELD("Max-Forwards", max_forwards_)
        else IS_THIS_REQUEST_HEADER_FIELD("Proxy-Authorization", proxy_authorization_)
        else IS_THIS_REQUEST_HEADER_FIELD("Range", range_)
        else IS_THIS_REQUEST_HEADER_FIELD("Referer", referer_)
        else IS_THIS_REQUEST_HEADER_FIELD("User-Agent", user_agent_)
        else IS_THIS_REQUEST_HEADER_FIELD("Content-Type", content_type_)
        else
        {
            buffer >> body_;
        }
    } 
}

void HTTP::request::GET()
{

}

void HTTP::request::HEAD()
{
    
}

void HTTP::request::POST()
{
    
}

void HTTP::request::PUT()
{
    
}

void HTTP::request::DELETE()
{
    
}

void HTTP::request::CONNECT()
{
    
}

void HTTP::request::OPTIONS()
{
    
}

void HTTP::request::TRACE()
{
    
}

void HTTP::request::PATCH()
{
    
}