#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>

#define PORTA 9999
#define IP "127.0.0.1" 
#define BUF 10000

int main (int argc, char *argv[])
{
	int meusocket;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int numbytes;
	socklen_t addr_size;
	char buffer[BUF];


	meusocket = socket(AF_INET, SOCK_DGRAM, 0); 

	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(PORTA); 
	server_addr.sin_addr.s_addr = inet_addr(IP); 
	bzero(&(server_addr.sin_zero),8); 

	client_addr.sin_family = AF_INET; 
	client_addr.sin_port = htons(PORTA); 
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.2"); 
	bzero(&(server_addr.sin_zero),8); 

	bzero(buffer, strlen(buffer));

	bind(meusocket, (struct sockaddr *) &server_addr, sizeof( struct sockaddr));

	addr_size = sizeof(struct sockaddr);
	
	while(1){
	
	printf("Aguardando mensagens atraves do IP: %s / Porta: %d \n", IP, PORTA);
	numbytes = recvfrom(meusocket,buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_size);
	
	printf("recebendo pacotes de %s \n", inet_ntoa(client_addr.sin_addr));
	printf("o pacote tem %i bytes \n", numbytes);

	buffer[numbytes] = '\0';
	printf("MSG: %s \n", buffer);
	
	/* ***** enviando msg para o client ***** */
	
	bzero(buffer, strlen(buffer));
	
	printf("Digite a mensagem para o host remoto \n");
	fflush(stdin);
	scanf("%s", buffer);

	numbytes = sendto(meusocket, buffer, strlen(buffer), 0, (struct sockaddr *) &client_addr, sizeof(struct sockaddr));
	
	bzero(buffer, strlen(buffer));
	
	}
	
	close(meusocket);
	
	exit(EXIT_SUCCESS);
}
