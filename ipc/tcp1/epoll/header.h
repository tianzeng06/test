#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <lsit>
#include <string.h>

#define BUFFER_SIZE 1024
#define EPOLL_RUN_TIMEOUT -1
#define EPOLL_SIZE 100000

int setnonblock(int sockfd);
int handle_message(int new_fd);

