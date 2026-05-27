#include "mini_serv.h"

t_client clients[MAX_CLIENTS];
int current_id = 0;
int maxfd = 0;
fd_set read_set;
fd_set write_set;
fd_set current;
char send_buffer[MAX_MSG_SIZE + 50];
char recv_buffer[MAX_MSG_SIZE];

static void putstr(int fd, char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

static void err(char *msg)
{
	if (!msg)
		putstr(2, "Fatal error\n");
	else
		putstr(2, msg);
	exit(1);
}

static void send_broadcast(int accepted)
{
	for (int fd = 0; fd <= maxfd; fd++)
	{
		if (FD_ISSET(fd, &write_set) && fd != accepted)
			if (send(fd, send_buffer, strlen(send_buffer), 0) == -1)
				err(NULL);
	}
}

static int init_server_socket(char *port)
{
	int			sockfd;
	struct		sockaddr_in	servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		err(NULL);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(port));
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
		err(NULL);
	if (listen(sockfd, 10) != 0)
		err(NULL);
	FD_ZERO(&current);
	FD_SET(sockfd, &current);
	maxfd = sockfd;
	return (sockfd);
}

static void accept_client(int sockfd)
{
	int			connfd;
	struct		sockaddr_in	cli;
	socklen_t 	len;

	len = sizeof(cli);
	memset(&cli, 0, len);
	connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	if (connfd < 0)
		err(NULL);
	if (connfd > maxfd)
		maxfd = connfd;
	clients[connfd].id = current_id++;
	clients[connfd].msg[0] = '\0';
	FD_SET(connfd, &current);
	sprintf(send_buffer, "server: client %d just arrived\n", clients[connfd].id);
	send_broadcast(connfd);
}

static void remove_client(int fd)
{
	sprintf(send_buffer, "server: client %d just left\n", clients[fd].id);
	send_broadcast(fd);
	FD_CLR(fd, &current);
	close(fd);
	clients[fd].msg[0] = '\0';
}

static void handle_client_message(int fd, int ret)
{
	int i;
	int j;

	j = strlen(clients[fd].msg);
	for (i = 0; i < ret; i++, j++)
	{
		clients[fd].msg[j] = recv_buffer[i];
		if (clients[fd].msg[j] == '\n')
		{
			clients[fd].msg[j] = '\0';
			sprintf(send_buffer, "client %d: %s\n", clients[fd].id, clients[fd].msg);
			send_broadcast(fd);
			clients[fd].msg[0] = '\0';
			j = -1;
		}
	}
}

static void handle_client_io(int fd)
{
	int ret;

	ret = recv(fd, recv_buffer, MAX_MSG_SIZE, 0);
	if (ret <= 0)
		remove_client(fd);
	else
		handle_client_message(fd, ret);
}

int main(int ac, char **av)
{
	if (ac != 2)
		err("Wrong number of arguments\n");

	int sockfd;
	sockfd = init_server_socket(av[1]);
	while (1)
	{
		read_set = write_set = current;
		if (select(maxfd + 1, &read_set, &write_set, NULL, NULL) == -1)
			err(NULL);
		for (int fd = 0; fd <= maxfd; fd++)
		{
			if (FD_ISSET(fd, &read_set))
			{
				if (fd == sockfd)
					accept_client(sockfd);
				else
					handle_client_io(fd);
			}
		}
	}
}