all: client server

client: client.cc common.h
	g++ -pthread -O3 -g -o client client.cc

server: server.cc common.h
	g++ -pthread -O3 -g -o server server.cc

a.out: main.cc
	g++ main.cc -lgtest -pthread -DFOO -Wall -Wextra -Werror -std=c++17 -Wno-unused-variable -Wno-unused-parameter


clean:
	rm -f *.o a.out core
