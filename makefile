http_server: server/server.c
	gcc server/server.c -o http_server
	./http_server

http_client: client/client.c
	gcc client/client.c -o http_client
	./http_client