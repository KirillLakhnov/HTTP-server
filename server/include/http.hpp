//#define DEBUG

#ifndef HTTP_HPP
#define HTTP_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#define IS_THIS_REQUEST_HEADER_FIELD(name, name_field) if(request_header_field == name){buffer >> name_field;}

const size_t MAX_LEN_REQUEST_BUF = 1024;
const size_t MAX_LEN_METHOD_NAME = 10;

/**
 * @brief список кодов статуса HTTP-сервера.
 * 
 */
enum STATUS_CODE {
    CONTINUE            = 100, //говорит о том, что запрос получен, но находится в процессе обработки.
    SWITCHING_PROTOCOLS = 101, //говорит о том, что сервер переключает протокол.

    OK                            = 200, //говорит клиенту о том, что его запрос удачно выполнен.
    CREATED                       = 201, //сообщает нам о том, что новый ресурс был создан успешно.
    ACCEPTED                      = 202, //сообщает клиенту о том, что HTTP запрос успешно принят на обработку, но обработка еще не завершена, в этом случае сервер может отказать в обслуживание запроса клиента.
    NON_AUTHORITATIVE_INFORMATION = 203, //сообщает клиенту о том, что возвращенная в заголовке HTTP объекта информация – это не оригинал, который есть на первоначальном сервере, а документ, собранный из локальных копий или копий третьей стороны, возможно даже, что данный документ — это кэш HTTP сервера.
    NO_CONTENT                    = 204, //говорит клиенту о том, что в ответном HTTP сообщении нет тела .
    RESET_CONTENT                 = 205, //Если браузер получит код состояния 205, то он должен очистить форму, чтобы дать пользователю ввести дополнительные данные.
    PARTIAL_CONTENT               = 206, //говорит браузеру о том, что HTTP сервер выполнил частичный GET запрос клиента.

    MULTIPLE_CHOICES   = 300, //говорит клиенту о том, что запрошенный ресурс имеет несколько представлений и клиент в праве выбрать одно из предлагаемых представлений. 
    MOVED_PERMANENTLY  = 301, //говорит клиенту о том, что запрашиваемая страница была перенесена на новый адрес, обычно браузер автоматически переходит по новому адресу.
    FOUND              = 302, //говорит клиенту о том, что запрашиваемый ресурс был временно перемещен на новый адрес.
    SEE_OTHER          = 303, //говорит клиенту о том, что ответ на запрос может быть найден по другому URI.
    NOT_MODIFIED       = 304, //говорит клиенту о том, что сервер выполнил условный GET запрос, но документ никак не изменился.
    USE_PROXY          = 305, //говорит клиенту о том, что запрошенный URL должен быть доступен через прокси, который указан в поле заголовка Location.
    UNUSED             = 306, //неиспользуется, но зарезервирован.
    TEMPORARY_REDIRECT = 307, //говорит клиенту о том, что запрашиваемая страница временно переехала на новый адрес.

    INTERNAL_SERVER_ERROR      = 500, //говорит о любой внутренней ошибке HTTP сервера, которая не входит в рамки других ошибок, в том числе и ошибок, описанных в других классах. 
    NOT_IMPLEMENTED            = 501, //означает, что сервер не может выполнить HTTP сообщение, полученное от клиента, из-за ограниченного функционала.
    BAD_GATEWAY                = 502, //означает, что HTTP сервер действует в качестве шлюза или прокси-сервера и при этом он получил недопустимый ответ от следующего в цепочке запросов сервера, к которому обращался при попытке выполнить запрос.
    SERVICE_UNAVAILABLE        = 503, //означает, что в настоящее время сервер недоступен из-за его перегрузки или он находится на техническом обслуживание
    GATEWAY_TIMEOUT            = 504, //возникает в том случае, когда HTTP сервер действует в роли прокси-сервера или шлюза и не получил своевременного ответа от следующего сервера, к которому он обращался, чтобы выполнить запрос.
    HTTP_VERSION_NOT_SUPPORTED = 505, //означает, что сервер не поддерживает или отказывается поддерживать версию HTTP протокола, указанную в запросе.
};

namespace HTTP {

const double HTTP_VERSION_ = 1.1;

class request {
private:
    std::string request_buf_;
    std::string answer_buf_;

    std::string method_;
    std::string URI_; //TODO: нписать проверку на верность введенного URI

    std::string protocol_;
    double protocol_version_;

    //TODO: Сделать кодогенерацию для полей заголовка ответа и запроса.
    //Поля заголовка запроса
    std::string accept_; //используется, чтобы определить тип информации, который должен содержаться в ответе HTTP сервера.
    std::string accept_charset_; //указывает на кодировку, которая должна быть в ответе сервера.
    std::string accept_language_; //указывает серверу приемлемые языки.
    std::string authorization_; //используется для отправки данных авторизации на сервер.
    std::string from_; //служит для передачи серверу адреса электронной почты клиента.
    std::string host_; //используется для указания доменного имени и порта запрашиваемого ресурса.
    std::string if_modified_since_; //указывает на то, что сервер должен отправить объект, если он изменился с даты, указанной в заголовке.
    std::string if_match_; //используется клиентом для эффективного обновления кэшируемой информации. 
    std::string if_none_match_; //выполняется клиентом, у которого есть один или более объектов, ранее полученных из ресурса, может проверить, что ни один из тех объектов не является текущим, включая список их связанных тэгов объекта в поле заголовка If-None-Match.
    std::string if_range_; //используется клиентом в том случае, когда он имеет частичную копию объекта в его кэше, и желает иметь современную копию всего объекта.
    std::string if_unmodified_since_; //используется клиентом если если запрошенный ресурс не был изменен со времени, указанного в этом поле.
    std::string max_forwards_; //используется HTTP методом TRACE, чтобы ограничить число прокси-серверов, иначе может получиться бесконечный цикл.
    std::string proxy_authorization_; //содержит в себе информацию для авторизации на прокси-сервере.
    std::string range_; //указывает байтовый диапазон фрагмента ресурса, который требуется клиенту, чтобы не тянуть весь ресурс целиком.
    std::string referer_; //содержит в себе URI ресурса, с которого клиент перешел на данный ресурс.
    std::string user_agent_; //содержит в себе полную информацию о клиенте пользователя, например, о браузере.

    std::string content_type_; //используется для указания медиа типа данных в теле сообщения.
    std::string body_;

    size_t status_code_;

    //Поля заголовка ответа
    double age_; //время, которое объект находился в кеше прокси в секундах.
    std::string location_; //используется в перенаправлении или при создании нового ресурса.
    std::string proxy_authenticate_; //запрос аутентификации для доступа к прокси.
    std::string public_;
    std::string retry_after_; //Если объект временно недоступен, это указывает клиенту повторить попытку позже. Значение может быть указанным периодом времени (в секундах) или датой HTTP.
    std::string server_; //Имя для сервера.
    std::string vary_;
    std::string warning_; //Общее предупреждение о возможных проблемах с телом объекта.
    std::string www_authenticate_; //Указывает схему аутентификации, которую следует использовать для доступа к запрошенному объекту.

public:
    /**
     * @brief Создание нового объекта request.
     * 
     * @param request_buf буфер запроса.
     */
    request(char* request_buf);

    /**
     * @brief Данные о состояние запроса.
     */
    void dump () const;

    /**
     * @brief ответ сервера на запрос. 
     */
    void answer();

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

//=====================================================

bool is_method(std::string str);

bool is_HTTP(std::string str);

}; //namespace HTTP
#endif //HTTP_HPP