#include "Controller.h"
#include "Client.h"
#include <stdio.h>
#include <unistd.h>

void Controller::send(const char *msg){

	//Init client
	Client *client = new Client();
	char ip[50] = "193.226.12.217";
	int port = 20232;

	//Make sure the message has null byte
	char buffer[256];
	sprintf(buffer, "%s", msg);

	for(int i = 0; buffer[i]; i++){
		char sendString[2];
		sprintf(sendString, "%c", buffer[i]);
		client->send(ip, port, sendString);
		sleep(1);
	}
}
