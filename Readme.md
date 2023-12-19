# HTTP сервер на С

**Сетевой протокол** - это набор соглашений, которым должны соответствовать обе стороны компьютера связи. Например, как установить соединение, как идентифицировать друг друга. Только следуя этому соглашению, компьютеры могут общаться друг с другом, точно так же, как язык, на котором взаимодействуют два компьютера.

**HyperText Transfer Protocol(HTTP)** является наиболее широко используемым сетевым протоколом в Интернете. Он в основном используется для передачи информации между веб-браузером и веб-сервером. HTTP - это протокол прикладного уровня, основанный на протоколе TCP/IP. Порт 80 используется по умолчанию. Последняя версия HTTP 2.0, и в настоящее время наиболее широко используется HTTP 1.1.

Протокол HTTP работает на архитектуре клиент-сервер. Браузер действует как HTTP-клиент и отправляет все запросы на HTTP-сервер или веб-сервер через URL-адрес. Веб-сервер отправляет ответное сообщение клиенту после получения запроса.

# Первые проблемы

По умолчанию сокет - блокирующийся, то есть когда мы вызываем функцию ``recv`` и просим n-байт, то сокет блокируется до того момента, пока не получит те самые n-байт, или же пока не закроется.

Мы можем сделать сокет неблокирующимся, что разрешит получать ему байтов меньше, чем запрошено.

К тому же, в самой базовой версии сервера мы постоянно проверяем сокет. Для уменьшения затрат производительность можно сделать так, что сокет будет проверяться только того, когда в него приходит минформация.

Для этого можно использовать либо ``select``, либо ``poll``, а лучше ``epoll``, так как сложность его алгоритмов O(1), а не O(n), что увеличивает скорость работы для большого числа соединений.

Так как моей основной системой является MacOS, в которой ``epoll`` не пддерживается, то реализуем поддержку как ``poll`` для MacOS, так и ``epoll`` для Linux.


(Пример сервера с использованием epoll.)[https://github.com/onestraw/epoll-example/blob/master/epoll.c]
(Информация.)[https://russianblogs.com/article/14501617425/]
(Информация.)[https://code-live.ru/post/cpp-http-server-over-sockets/]
(Информация.)[https://habr.com/ru/companies/infopulse/articles/415259/]
(Спецификация протокола HTTP.)[http://www.lib.ru/WEBMASTER/rfc2068/]
(Определение операционной системы.)[https://www.geeksforgeeks.org/how-to-detect-operating-system-through-a-c-program/]
