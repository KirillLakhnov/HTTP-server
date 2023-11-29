#include "../include/http.hpp"

bool HTTP::is_method (std::string str)
{
    if ((str == "GET"    ) ||
        (str == "HEAD"   ) ||
        (str == "POST"   ) ||
        (str == "PUT"    ) || 
        (str == "DELETE" ) ||
        (str == "CONNECT") ||
        (str == "OPTIONS") ||
        (str == "TRACE"  ) ||
        (str == "PATCH"  ))     
    {
        return true;
    }  
    return false;
}

bool HTTP::is_HTTP(std::string str)
{
    if (str == "HTTP") {return true;}

    return false;
}