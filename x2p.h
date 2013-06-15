/*
** x2p.h for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:57 2013 vincent leroy
** Last update Sat Jun 15 14:42:57 2013 vincent leroy
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
#include "gui.h"
#include "string_utils.h"

#define BUFF_SIZE 4096

typedef struct s_msg
{
  char msg[BUFF_SIZE];
} t_msg;

typedef enum e_state
{
  TYPE_AWAY	= 0,
  TYPE_CHAT	= 1,
  TYPE_DND	= 2,
  TYPE_XA	= 3
} t_state;

typedef struct s_data
{
  char *ip;
  int sockfd;
  char id[BUFF_SIZE];
  char *username;
  char *mdp;
  t_state state;
} t_data;

/*
 * main.c
 */
void inter_sig(int signum);
/*
 * network.c
 */
int connect_to_server(char *ip, char *port);
void stop();
int run(t_data *data);
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
void send_header(t_data *data);
void send_identifiant(t_data *data);
void send_password(t_data *data);
void send_deconnection(t_data *data);
void send_newstate(t_data *data, char *state);
void send_chatmessage(t_data *data, char *msg, char *dest);
void send_normalmessage(t_data *data, char *subject, char *msg, char *dest);

#endif /* !X2P_H_ */
