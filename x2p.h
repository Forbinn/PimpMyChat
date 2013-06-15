/*
** x2p.h for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:57 2013 vincent leroy
** Last update Sat Jun 15 10:43:43 2013 vincent leroy
*/

#ifndef X2P_H_
# define X2P_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define BUFF_SIZE 4096

/*
 * network.c
 */
int connect_to_server(char *ip, char *port);
pthread_t start_network(int *sockfd);
void stop_network(pthread_t thread);
void* run_network(void *data);

#endif /* !X2P_H_ */
