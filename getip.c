#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main(int ac, char **av)
{
	const char *hostname = av[1];
	struct addrinfo	hint;
	struct addrinfo	*result;

	if (ac != 2)
	{
		printf("Usage: %s <hostname>\n", av[0]);
		return (EXIT_FAILURE);
	}

	memset(&hint, 0, sizeof(hint));
	//hint.ai_family = AF_INET;
	//hint.ai_family = AF_INET6;
	hint.ai_family = AF_UNSPEC;
	//hint.ai_socktype = SOCK_DGRAM;

	int status = getaddrinfo(hostname, NULL, &hint, &result);
	if (status)
	{
		printf("getaddrinfo failed!");
		return (EXIT_FAILURE);
	}

	struct addrinfo *tmp = result;
	while (tmp != NULL)
	{
		printf("Entry:\n");
		printf("\tType: %i\n", tmp->ai_socktype);
		printf("\tFamily: %i\n", tmp->ai_family);

		char address_string[INET6_ADDRSTRLEN];
		void *addr;
		if (tmp->ai_family == AF_INET)
		{
			//v4
			addr = &(((struct sockaddr_in *)tmp->ai_addr)->sin_addr);
		}
		else
		{
			//v6
			addr = &(((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr);
		}

		inet_ntop(tmp->ai_family, addr, address_string, INET6_ADDRSTRLEN);

		printf("\tAddress: %s\n", address_string);
		tmp = tmp->ai_next;
	}

	freeaddrinfo(result);

	return (EXIT_SUCCESS);
}