debug = -DDEBUG

http_server: server/server.cpp server/src/http.cpp
	g++ server/server.cpp server/src/http.cpp ${debug} -o bin/http_server

http_client: client/client.c
	gcc client/client.c -o bin/http_client