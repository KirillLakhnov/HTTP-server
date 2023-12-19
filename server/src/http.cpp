#include "../include/http.hpp"
HTTP::request::request(char* request_buf) : request_buf_(std::string(request_buf)), 
                                            content_type_("application/x-www-form-urlencoded"),
                                            status_code_(CONTINUE)
{
    parser();
}

void HTTP::request::parser()
{
    status_code_ = ACCEPTED;

    std::stringstream buffer;
    buffer << request_buf_;
    assert(std::cout.good());

    buffer >> method_;
    assert(std::cin.good());
    if (is_method(method_) == false)
    {
        status_code_ = NOT_IMPLEMENTED;
        std::cout << "Error: invalid HTTP request method." << std::endl;
        return;
    }

    buffer >> URI_; 
    assert(std::cin.good());

    std::string protocol_name_version;
    buffer >> protocol_name_version;
    assert(std::cin.good());

    size_t slash_find = protocol_name_version.find('/');
    if (slash_find == std::string::npos)
    {
        status_code_ = NOT_IMPLEMENTED;
        std::cout << "Error: incorrect protocol and version input format." << std::endl;
        dump();
        return;
    }
    protocol_ = protocol_name_version.substr(0, slash_find);
    if (is_HTTP(protocol_) == false)
    {
        status_code_ = NOT_IMPLEMENTED;
        std::cout << "Error: invalid protocol." << std::endl;
        dump();
        return;
    }
    protocol_version_ = stod(protocol_name_version.substr(slash_find + 1, 
                             protocol_name_version.size()));
    if (protocol_version_ < HTTP_VERSION_)
    {
        status_code_ = HTTP_VERSION_NOT_SUPPORTED;
        std::cout << "Error: the HTTP protocol version" << protocol_version_ 
                  << " is not supported." << std::endl;
        dump();
        return;
    }

    std::string request_header_field;
    while (buffer.tellg() != -1) // Проверка на достижение конца буфера
    {
        buffer >> request_header_field;
        if (request_header_field[request_header_field.length() - 1] == ':')
        {
            request_header_field.erase(request_header_field.length() - 1, 1);
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
            body_ = request_header_field;
        }
    } 
}

void HTTP::request::dump() const
{
#ifdef DEBUG
    std::cout << "\e[31mmethod_: \e[0m" << method_ << std::endl;
    std::cout << "\e[31mURI_: \e[0m" << URI_ << std::endl;
    std::cout << "\e[31mprotocol_: \e[0m" << protocol_ << std::endl;
    std::cout << "\e[31mprotocol_version_: \e[0m" << protocol_version_ << std::endl << std::endl;

    std::cout << "\e[31maccept_: \e[0m" << accept_ << std::endl;
    std::cout << "\e[31maccept_charset_: \e[0m" << accept_charset_ << std::endl;
    std::cout << "\e[31maccept_language_: \e[0m" << accept_language_ << std::endl;
    std::cout << "\e[31mauthorization_: \e[0m" << authorization_ << std::endl;
    std::cout << "\e[31mfrom_: \e[0m" << from_ << std::endl;
    std::cout << "\e[31mhost_: \e[0m" << host_ << std::endl;
    std::cout << "\e[31mif_modified_since_: \e[0m" << if_modified_since_ << std::endl;
    std::cout << "\e[31mif_match_: \e[0m" << if_match_ << std::endl;
    std::cout << "\e[31mif_none_match_: \e[0m" << if_none_match_ << std::endl;
    std::cout << "\e[31mif_range_ \e[0m" << if_range_ << std::endl;
    std::cout << "\e[31mif_unmodified_since_: \e[0m" << if_unmodified_since_ << std::endl;
    std::cout << "\e[31mmax_forwards_: \e[0m" << max_forwards_ << std::endl;
    std::cout << "\e[31mproxy_authorization_: \e[0m" << proxy_authorization_ << std::endl;
    std::cout << "\e[31mrange_: \e[0m" << range_ << std::endl;
    std::cout << "\e[31mreferer_: \e[0m" << referer_ << std::endl;
    std::cout << "\e[31muser_agent_: \e[0m" << user_agent_ << std::endl << std::endl;

    std::cout << "\e[31mcontent_type_: \e[0m" << content_type_ << std::endl;
    std::cout << "\e[31mbody_: \e[0m" << body_ << std::endl << std::endl;

    std::cout << "\e[31mstatus_code_: \e[0m" << status_code_ << std::endl << std::endl;
#endif
}

void HTTP::request::answer()
{
    answer_buf_ += (protocol_ + '/');
    answer_buf_ += (protocol_version_ + ' ');

    answer_buf_ += (status_code_ + '\n'); //TODO: добавить вывод имени статуса состояния

    std::cout << std::endl << std::endl << answer_buf_ << std::endl;
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