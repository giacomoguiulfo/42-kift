/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 00:57:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/12 03:03:00 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER 1024
int main()
{
	static int				fileno;
	int						welcomeSocket;
	int						count;
	int						newSocket;
	char					buffer[BUFFER];
	int						file_size;
	struct sockaddr_in		serverAddr;
	struct sockaddr_storage	serverStorage;
	socklen_t				addr_size;

	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	/*---- Configure settings of the server address struct ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number, using htons function to use proper byte order */
	serverAddr.sin_port = htons(3000);
	/* Set IP address to localhost */
	serverAddr.sin_addr.s_addr = inet_addr("localhost");
	/* Set all bits of the padding field to 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	/*---- Bind the address struct to the socket ----*/
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*---- Listen on the socket, with 5 max connection requests queued ----*/
	if (listen(welcomeSocket, 5) == 0)
		printf("Listening\n");
	else
		printf("Error\n");

	/*---- Accept call creates a new socket for the incoming connection ----*/
	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

	/*---- Read the message from the server into the buffer ----*/
	recv(newSocket, buffer, 1024, 0);
	int fd = open("out.wav", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR);
	printf("Testing: %s\n", buffer);
	return (0);
}
//
// 	/*---- Print the received message ----*/
// 	file_size = atoi(buffer);
// 	count = 0;
// 	printf("Recieved File_Size: %d", file_size);
// 	bzero(buffer, BUFFER);
// 	while(1)
// 	{
// 		recv(newSocket, buffer, 1024, 0);
// 		count += write(fd, buffer, BUFFER);
// 		if (count >= file_size)
// 			break;
// 	}
// 	return 0;
// }
