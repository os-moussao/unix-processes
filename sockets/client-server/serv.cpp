#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cassert>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 80

int main() {
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		perror("socket");
		exit(1);
	}

	sockaddr_in sa;
	bzero(&sa, sizeof sa);
	// setprotoent(sock_fd, )

	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_len = sizeof sa;

	// assigning an IP and a Port Number to the socket
	if (bind(sock_fd, (sockaddr*)&sa, sa.sin_len) < 0) {
		perror("bind");
		exit(1);
	}

	// telling the socket that it should be abe to accept connections
	if (listen(sock_fd, 1) < 0) {
		perror("listen");
		exit(1);
	}

	while (1) {
		socklen_t len;
		sockaddr_in client;

		// accept the first connection request on the queue of pending connections (set up in listen) 
		// and create a new socket for that connection
		int new_socket = accept(sock_fd, (sockaddr*)&client, &len);
		if (new_socket < 0) {
			perror("accept");
			exit(1);
		}


		char buff[1024];
		int sz;
		while ((sz = read(new_socket, buff, 1024)) > 0) {
			buff[sz] = 0;
			cout << buff;
		}

		string respons = "Hello World, from the server !";
		write(new_socket, respons.c_str(), respons.size());

		close(new_socket);
	}

	close(sock_fd);
}