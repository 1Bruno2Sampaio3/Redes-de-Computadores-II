#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdio_ext.h>

#define PORTA 9999
#define IP "127.0.0.2" 
#define BUF 10000

int main(int argc, char *argv[])
{
	int meusocket;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int numbytes, porta;
	char msg[BUF], ip[16];
	socklen_t addr_size;

	printf("Digite o IP de destino \n");
	scanf("%s", ip);

	printf("Digite a porta de destino \n");
	scanf("%d", &porta);
	
	
	meusocket = socket (AF_INET, SOCK_DGRAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(porta);
	server_addr.sin_addr.s_addr = inet_addr(ip);
	bzero(&(server_addr.sin_zero), 8);

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(PORTA);
	client_addr.sin_addr.s_addr = inet_addr(IP);
	bzero(&(client_addr.sin_zero), 8);
	
	bind(meusocket, (struct sockaddr *) &client_addr, sizeof( struct sockaddr));
	
	while(1){

	printf("Digite a mensagem para o host remoto \n");
	fflush(stdin);
	scanf("%s", msg);
	numbytes = sendto(meusocket, msg, strlen(msg), 0, (struct sockaddr *) &server_addr, sizeof(struct sockaddr));
	

	printf("enviado %d bytes para %s \n", numbytes, inet_ntoa(server_addr.sin_addr));
	
	
	
	/* ***** recebendo msg do servidor ***** */
	
	printf("Aguardando mensagens atraves do IP: %s / Porta: %d \n", IP, PORTA);
	numbytes = recvfrom(meusocket,msg, sizeof(msg), 0, (struct sockaddr *)&server_addr, &addr_size);
	
	printf("recebendo pacotes de %s \n", inet_ntoa(server_addr.sin_addr));
	printf("o pacote tem %i bytes \n", numbytes);

	msg[numbytes] = '\0';
	printf("MSG: %s \n", msg);
	
	bzero(msg, strlen(msg));
	
	}
	
	close(meusocket);
	exit (0);
}
