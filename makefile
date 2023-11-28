http_server: server/server.cpp
	gcc server/server.cpp -o bin/http_server

http_client: client/client.c
	gcc client/client.c -o bin/http_client