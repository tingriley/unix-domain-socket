all: client server

client: client.cpp
	g++ -o client client.cpp


server: server.cpp
	g++ -o server server.cpp

clean:
	rm -rf client server