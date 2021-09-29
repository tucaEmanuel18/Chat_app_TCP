HEADERS= ../tcp_utils.h
SOURCES= client_tcp.cpp ../tcp_utils.cpp

client: ${SOURCES} ${HEADERS}
	g++ -pthread -std=c++11 ${SOURCES} -o client

clean:
	rm *.o