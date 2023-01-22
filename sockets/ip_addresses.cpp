#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cassert>
#include <arpa/inet.h>
using namespace std;

int main() {
	struct sockaddr_in sa;
	struct sockaddr_in6 sa6;
	sa.sin_family = AF_INET, sa6.sin6_family = AF_INET6;

	if (inet_pton(AF_INET, "192.0.2.146", &sa.sin_addr) < 0) {
		perror("inet_pton");
	}
	if (inet_pton(AF_INET6, "2001:0db8:85a3:0000:0000:8a2e:0370:7334", &sa6.sin6_addr) < 0) {
		perror("inet_pton");
	}

	char ip4[INET_ADDRSTRLEN], ip6[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET, &sa.sin_addr, ip4, INET_ADDRSTRLEN);
	inet_ntop(AF_INET6, &sa6.sin6_addr, ip6, INET6_ADDRSTRLEN);
	cout << ip4 << endl;
	cout << ip6 << endl;
}