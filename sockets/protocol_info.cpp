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

// param examples: {"ip","icmp","ggp","tcp", "egp","pup","udp","hmp","xns-idp", "rdp","rvd"}
int main(int ac, char **av) {
	if (ac != 2) {
		cerr << "Usage: ./prog protocol-name" << endl;
		exit(1);
	}

	struct protoent *pinfo = getprotobyname(av[1]);
	if (!pinfo) {
		cerr << "invalid param" << endl;
		exit(1);
	}

	cout << "official name of protocol: " << pinfo->p_name << endl;
	cout << "alias list:" << endl;
	for (char **s = pinfo->p_aliases; *s; s++) {
		cout << *s << endl;
	}
	cout << "protocol number: " << pinfo->p_proto << endl;
}