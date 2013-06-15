/*
** x2p.h for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:57 2013 vincent leroy
** Last update Sat Jun 15 12:29:15 2013 vincent leroy
*/

#ifndef X2P_H_
# define X2P_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>

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
int run(int sockfd);
int check_readfs(fd_set *readfs, int sockfd);

#endif /* !X2P_H_ */
