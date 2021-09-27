# server: server.o 
# 	g++ server.o -o server

# server.o: server.cpp chat_server.o
# 	g++ -c server.cpp chat_server.h

# chat_server.o: chat_server.cpp abstract_server.o
# 	g++ -c server.cpp abstract_server.h

# abstract_server.o: abstract_server.cpp tcp_utils.o
# 	g++ -c tcp_utils.h abstract_server.cpp

# tcp_utils.o: tcp_utils.cpp
# 	g++ -c tcp_utils.cpp
HEADERS=abstract_server.h chat_server.h tcp_utils.h
SOURCES=server.cpp abstract_server.cpp chat_server.cpp tcp_utils.cpp

server: ${SOURCES} ${HEADERS}
	g++ -pthread -std=c++11 ${SOURCES} -o server

clean:
	rm *.o