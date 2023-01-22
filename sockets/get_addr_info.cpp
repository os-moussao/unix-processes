#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cassert>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main(int ac, char **av) {
	if (ac != 2) {
		cerr << "Usage: ./prog hostname" << endl;
		exit(1);
	}

	int status;
	struct addrinfo hints;
	struct addrinfo *servinfo; 

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(av[1], NULL, &hints, &servinfo)) != 0) {
		cerr << "getaddrinfo: " << gai_strerror(status) << endl;
		exit(1);
	}

	for (struct addrinfo *p = servinfo; p; p = p->ai_next) {
		if (p->ai_family == AF_INET) {
			struct sockaddr_in *sa = (struct sockaddr_in *)(p->ai_addr);
			char ipv4[INET_ADDRSTRLEN];
			inet_ntop(p->ai_family, &(sa->sin_addr), ipv4, INET_ADDRSTRLEN);
			cout << ipv4 << endl;
		} else {
			struct sockaddr_in6 *sa = (struct sockaddr_in6 *)p->ai_addr;
			char ipv6[INET6_ADDRSTRLEN];
			inet_ntop(p->ai_family, &(sa->sin6_addr), ipv6, INET6_ADDRSTRLEN);
			cout << ipv6 << endl;
		}
	}

	freeaddrinfo(servinfo); // free the linked-list
}
