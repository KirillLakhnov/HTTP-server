#ifndef HTTP_HPP
#define HTTP_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#define IS_THIS_REQUEST_HEADER_FIELD(name, name_field) if(request_header_fields == name){buffer >> name_field;}

const size_t MAX_LEN_REQUEST_BUF = 1024;
const size_t MAX_LEN_METHOD_NAME = 10;

/* enum REQUEST_METHOD {
    NOT_DEFINED = 0,
    GET         = 1,
    HEAD        = 2,
    POST        = 3,
    PUT         = 4,
    DELETE      = 5,
    CONNECT     = 6,
    OPTIONS     = 7,
    TRACE       = 8,
    PATCH       = 9,
}; */

namespace HTTP {
class request {
private:
    std::string request_buf_;

    std::string method_;
    std::string URI_;
    std::string http_version_; // TODO: переделать под double, добавить проверку на верность протокола

    //Поля заголовка запроса
    std::string accept_;
    std::string accept_charset_;
    std::string accept_language_;
    std::string authorization_;
    std::string from_;
    std::string host_;
    std::string if_modified_since_;
    std::string if_match_;
    std::string if_none_match_;
    std::string if_range_;
    std::string if_unmodified_since_;
    std::string max_forwards_;
    std::string proxy_authorization_;
    std::string range_;
    std::string referer_;
    std::string user_agent_;

    std::string content_type_;
    std::string body_;

public:
    /**
     * @brief Создание нового объекта request.
     * 
     * @param request_buf буфер запроса.
     */
    request(char* request_buf) : request_buf_(std::string(request_buf)), 
                                 content_type_("application/x-www-form-urlencoded")
    {
        parser();
    }

    void dump ();

private:
    /**
     * @brief Парсер буфера запроса.
     */
    void parser();

    /**
     * @brief GET запрашивает представление ресурса. 
     * Запросы с использованием этого метода могут только извлекать данные.
     */
    void GET();

    /**
     * @brief HEAD запрашивает ресурс так же, как и метод GET, но без тела ответа.
     */
    void HEAD(); 

    /**
     * @brief POST используется для отправки сущностей к определённому ресурсу. 
     * Часто вызывает изменение состояния или какие-то побочные эффекты на сервере.
     */
    void POST();

    /**
     * @brief PUT заменяет все текущие представления ресурса данными запроса.
     */
    void PUT();

    /**
     * @brief DELETE удаляет указанный ресурс.
     */
    void DELETE();

    /**
     * @brief CONNECT устанавливает "туннель" к серверу, определённому по ресурсу.
     */
    void CONNECT();

    /**
     * @brief OPTIONS используется для описания параметров соединения с ресурсом.
     */
    void OPTIONS();

    /**
     * @brief TRACE выполняет вызов возвращаемого тестового сообщения с ресурса.
     */
    void TRACE();

    /**
     * @brief PATCH используется для частичного изменения ресурса.
     */
    void PATCH();
};
}; //namespace HTTP
#endif //HTTP_HPP