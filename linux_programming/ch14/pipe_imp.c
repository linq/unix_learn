#include "cd_data.h"
#include "cliserv.h"

#include <sys/msg.h>

#define SERVER_MQUENE 1234
#define CLIENT_MQUENE 4321

struct msg_passed {
  long int msg_key;
  message_db_t real_message;
}

static int serv_qid = -1;
static int cli_qid = -1;

int server_starting() {
  #ifdef DEBUG_TRACE
    printf("%d :- server_starting()\n", getpid());
  #endif

    serv_qid = msgget((key_t)SERVER_MQUENE, 0666 | IPC_CREAT);
    if (serv_qid == -1) return 0;

    cli_qid = msgget((key_t)CLIENT_MQUENE, 0666 | IPC_CREAT);
    if (cli_qid == -1) return 0;

    return 1;
}

void server_ending() {
  #ifdef DEBUG_TRACE
    printf("%d :- server_ending()\n", getpid());
  #endif

    msgctl(serv_qid, IPC_RMID, 0);
    msgctl(cli_qid, IPC_RMID, 0);

    serv_qid = -1;
    cli_qid = -1;
}

int read_request_from_client(message_db_t *rec_ptr) {
  struct msg_passed my_msg;
  #ifdef DEBUG_TRACE
    printf("%d :- read_request_from_client()\n", getpid());
  #endif

    if (msgrcv(serv_qid, (void *)&my_msg, sizeof(*rec_ptr), 0, 0) == -1)
      return 0;

    *rec_ptr = my_msg.real_message;

    return 1;
}

int send_resp_to_client(const message_db_t mess_to_send) {
  struct msg_passed my_msg;
  #ifdef DEBUG_TRACE
    printf("%d :- send_resp_to_client()\n", getpid());
  #endif

    my_msg.real_message = mess_to_send;
    my_msg.msg_key = mess_to_send.client_pid;

    if (msgsnd(cli_qid, (void *)&my_msg, sizeof(mess_to_send), 0) == -1)
      return 0;

    return 1;
}

int client_starting() {
  #ifdef DEBUG_TRACE
    printf("%d :- client_starting()\n", getpid());
  #endif

    serv_qid = msgget((key_t)SERVER_MQUENE, 0666);
    if (serv_qid == -1)  return 0;

    return 1;
}

void client_ending() {
  #ifdef DEBUG_TRACE
    printf("%d :- client_ending()\n", getpid());
  #endif

    serv_qid = -1;
    cli_qid = -1;
}

int send_mess_to_server(message_db_t mess_to_send) {
  struct msg_passed my_msg;
  #ifdef DEBUG_TRACE
    printf("%d :- send_mess_to_server()\n", getpid());
  #endif

    my_msg.real_message = mess_to_send;
    my_msg.msg_key = mess_to_send.client_pid;
    if (msgsnd(serv_qid, (void *)&my_msg, sizeof(mess_to_send), 0) == -1) {
      perror("Message send failed");
      return 0;
    }

    return 1;
}

int read_resp_from_server(message_db_t *rec_ptr) {
  struct msg_passed my_msg;
  #ifdef DEBUG_TRACE
    printf("%d :- read_resp_from_server()\n", getpid());
  #endif

    if (msgrcv(cli_qid, (void *)&my_msg, sizeof(*rec_ptr), getpid(), 0) == -1)
      return 0;

    return 1;
}

int start_resp_to_client(const message_db_t mess_to_send) {
  return 1;
}

void send_resp_to_client(void) {
}

int start_resp_from_server(void) {
  return 1;
}

void end_resp_from_server(void) {
}
