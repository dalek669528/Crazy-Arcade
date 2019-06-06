#ifndef __SOCKOP_H__
#define __SOCKOP_H__

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define errexit(format, arg...) exit(printf(format, ##arg))

int passivesock(const char *service, const char *transport, int qlen);
int connectsock(const char *host, const char *service, const char *transport);

#endif /* __SOCKOP_H__ */
