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

        if (request_header_fields == "Host")
        {
            buffer >> host_;
        }
        else if (request_header_fields == "Content-Type")
        {
            buffer >> content_type_;
        }
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