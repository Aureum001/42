#pragma once

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

enum {
	MAX_MSG_SIZE = 4096,
	MAX_CLIENTS = 1024,
	SEND_BUFFER_EXTRA = 50
};

typedef struct s_client
{
	int id;
	char msg[MAX_MSG_SIZE + 1];
}	t_client;

