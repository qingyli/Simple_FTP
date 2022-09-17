#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <thread>
#include <iostream>
#include <string.h>
#include <unistd.h>


//using namespace std;
char buf[100];

int send_FTP(char* file_name, int socket){
	//send to client
	int n = send(socket, file_name, sizeof(file_name), 0);
	if(n<0){
		printf("Server failed to connect client");
	}
	close(socket);
	return 0;
}

int clientHandle(int client_socket){

	//char client_buffer[BUFSIZ];
	//char server_buffer[BUFSIZ];
	char file_name[BUFSIZ];

	while(1){
		//bzero(client_buffer, sizeof(client_buffer));
		//bzero(server_buffer, sizeof(client_buffer));
		bzero(file_name, sizeof(file_name));
		

		if(buf[0] == 'g' && buf[0] == 'e' && buf[0] == 't'){
			char *p = strchr(buf, ' ');
			
			strcpy(file_name, p);
			send_FTP(file_name, client_socket);
		}
		pthread_exit(NULL);
	}

	return 0;
}


int main(int argc, char const *argv[])
{
	int myPort = 99999;
	int server_socket, client_socket;

	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	

	socklen_t server_length;
	socklen_t client_length;
	int isError;

	
	//open server socket
	server_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(server_socket < 0){
		printf("Failed to open socket");
		return -1;
	}

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(myPort);

	//bind socket to server_address
	server_length = sizeof(server_address);
	isError = bind(server_socket, (struct sockaddr *)&server_address,server_length);
	if(isError<0){
		printf("Failed to bind socket to address");
		return -1;
	}


	client_length = sizeof(client_address);
	while(isError = recvfrom(server_socket, buf, 99, 0, (struct sockaddr *)&client_address, &client_length))
		{

		std::thread client_thread(clientHandle, client_socket);

		client_thread.join();
	}

	if(client_socket<0){
		printf("Failed to accept from client");
		return -1;
	}
	close(server_socket);

	return 0;
}




