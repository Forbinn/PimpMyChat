/*
** x2p.h for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:57 2013 vincent leroy
** Last update Sun Jun 16 00:56:36 2013 vincent leroy
*/

#ifndef X2P_H_
# define X2P_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <expat.h>

#include "string_utils.h"

#define BUFF_SIZE 4096

typedef enum e_state
{
  TYPE_AWAY	= 0,
  TYPE_CHAT	= 1,
  TYPE_DND	= 2,
  TYPE_XA	= 3
} t_state;

typedef struct s_notif
{
  int notif;
  char strNotif[BUFF_SIZE];
  char sender[BUFF_SIZE];
} t_notif;

typedef struct s_data
{
  char ip[20];
  int sockfd;
  char id[BUFF_SIZE];
  char *username;
  char *mdp;
  t_state state;
  t_notif notif;
} t_data;

/*
 * main.c
 */
void inter_sig(int signum);
/*
 * network.c
 */
int connect_to_server(char *ip, char *port);
void init_network(t_data *data);
void destroy_network();
int readSocket(t_data *data);
/*
 * ParseXML.c
 */
void XML_Start(void *userData, const XML_Char *name, const XML_Char **atts);
void XML_End(void *userData, const XML_Char *name);
void XML_Character(void *userData, const XML_Char *s, int len);
/*
 * identification.c
 */
void send_header(t_data *data);
void send_identifiant(t_data *data);
void send_password(t_data *data);
void send_deconnection(t_data *data);
void send_newstate(t_data *data, char *state);
void send_chatmessage(t_data *data, char *msg, char *dest);
void send_createaccount(t_data *data);
void send_removeaccount(t_data *data);

#endif /* !X2P_H_ */
