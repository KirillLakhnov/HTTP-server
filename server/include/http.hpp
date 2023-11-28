#ifndef HTTP_HPP
#define HTTP_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

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

    std::string host_;

    std::string content_type_;
    std::string body_;

    /**
     * @brief Создание нового объекта request.
     * 
     * @param request_buf буфер запроса.
     */
    request(char* request_buf) : request_buf_(std::string(request_buf))
    {

    }

    void parser ();

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