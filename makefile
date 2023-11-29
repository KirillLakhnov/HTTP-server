debug = -DDEBUG

http_server: server/server.cpp server/src/http.cpp server/src/check_error_http.cpp
	g++ server/server.cpp server/src/http.cpp server/src/check_error_http.cpp ${debug} -o bin/http_server

http_client: client/client.c
	gcc client/client.c -o bin/http_client