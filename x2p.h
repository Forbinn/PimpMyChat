/*
** x2p.h for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:57 2013 vincent leroy
** Last update Sat Jun 15 13:31:14 2013 vincent leroy
*/

#ifndef X2P_H_
# define X2P_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <expat.h>

#include "stdlist.h"

#define BUFF_SIZE 4096

typedef struct s_msg
{
  char msg[BUFF_SIZE];
} t_msg;

/*
 * main.c
 */
void inter_sig(int signum);
/*
 * network.c
 */
int connect_to_server(char *ip, char *port);
void stop();
int run(int sockfd, char *ip);
int check_readfs(fd_set *readfs, int sockfd, XML_Parser p);
/*
 * ParseXML.c
 */
void XML_Start(void *userData, const XML_Char *name, const XML_Char **atts);
void XML_End(void *userData, const XML_Char *name);
void XML_Character(void *userData, const XML_Char *s, int len);
/*
 * identification.c
 */
void send_msg(int fd, char *msg);
char* make_msg(char *format, ...);
void send_header(char *ip, int sockfd);

#endif /* !X2P_H_ */
