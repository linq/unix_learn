#include "cd_data.h"
#include "cliserv.h"

static int server_fd = -1;
static pid_t mypid = 0;
static char client_pipe_name[PATH_MAX + 1] = {'\0'};
static int client_fd = -1;
static int client_write_fd = -1;

int server_starting(void ) {
  #ifdef DEBUG_TRACK
    printf("%d : - Server_starting()\n", getpid());
  #endif

    unlink(SERVER_PIPE);
    if (mkfifo(SERVER_PIPE, 0777) == -1) {
      fprintf(stderr, "Server startup error, no FIFO created\n");
      return 0;
    }

    if ((server_fd = open(SERVER_PIPE, O_RDONLY)) == -1) {
      if (errno == EINTR)
        return 0;
      fprintf(stderr, "Server startup error, no FIFO opened\n");
      return 0;
    }

    return 1;
}

void server_ending(void) {
  #ifdef DEBUG_TRACK
    printf("%d : - server_ending()\n");
  #endif

    close(server_fd);
    unlink(SERVER_PIPE);
}

int read_request_from_client(message_db_t *rec_ptr) {
  int return_code = 0;
  int read_bytes;

  #ifdef DEBUG_TRACK
    printf("%d : - read_request_from_client()\n", getpid());
  #endif

    if (server_fd != -1) {
      read_bytes = read(server_fd, rec_ptr, sizeof(rec_ptr));

      if (read_bytes == 0) {
        close(server_fd);
        if (server_fd = open(SERVER_PIPE, O_RDONLY) == -1) {
          fprintf(stderr, "Server error, FIFO open failed\n");
          return 0;
        }
        read_bytes = read(server_fd, rec_ptr, sizeof(rec_ptr));
      }
      if (read_bytes == sizeof(*rec_ptr))
        return_code = 1;
    }

    return return_code;
}
