#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <utmp.h>
#include "utmplib.h"

#define NEW(type) (type *)malloc(sizeof (type))

struct user_list {
  struct user_list *next;
  char name[sizeof((struct utmp*)0)->ut_user];
  time_t secs;
};

struct utmp_list{
  struct utmp_list *next;
  struct utmp usr;
};

static time_t Total = 0;
static struct user_list *Users = NULL;

struct user_list *update_user(struct user_list *, char *, time_t);
struct utmp_list *log_in(struct utmp*, struct utmp_list *);
struct utmp_list *log_out(struct utmp*, struct utmp_list *);

int  main(int argc, char *argv[]) {
  struct utmp_list *lp, *head = NULL;
  struct utmp *utp;

  if (utmp_open(WTMP_FILENAME) == -1) {
    fprintf(stderr, "open file %s error", WTMP_FILENAME);
    exit(EXIT_FAILURE);
  }

  while ((utp = utmp_next()) != NULL) {
    if (utp->ut_type == USER_PROCESS) {
      head = log_in(utp, head);
    } else if (utp->ut_type == DEAD_PROCESS) {
      head = log_out(utp, head);
    }
  }

  utmp_close();

  printf("total %ld\n", Total/3600);

  return 0;
}  // main

struct utmp_list *log_in(struct utmp* up, struct utmp_list * head) {
  struct utmp_list *lp = NEW(struct utmp_list);
  lp->next = head;
  head = lp;
  memmove(&lp->usr, up, sizeof *up);
  return head;
}


struct utmp_list *log_out(struct utmp* up, struct utmp_list * head) {
  time_t secs;
  struct utmp_list *lp, *lp2, *tlp;
  for (lp = head, lp2 = NULL; lp != NULL;) {
    if (memcmp(lp->usr.ut_id, up->ut_id, sizeof up->ut_id) == 0) {
      secs = up->ut_tv.tv_sec - lp->usr.ut_tv.tv_sec;
      update_user(Users, lp->usr.ut_user, secs);
      tlp = lp;
      lp = lp->next;
      if (tlp == head)
        head = lp;
      else if (lp2 != NULL)
        lp2->next = lp;
      free(tlp);
    } else {
      lp2 = lp; 
      lp = lp->next;
    }
  }  

  return head;
}

struct user_list *update_user(struct user_list *head, char *name, time_t secs) {
  struct user_list *up;

  for (up = head; up != NULL; up = up->next) {
    if (strcmp(up->name, name) == 0) {
      up->secs += secs;
      Total += secs;
      return head;
    }
  }

  if ((up = NEW(struct user_list)) == NULL) {
    fprintf(stderr, "crate user_list error");
    exit(EXIT_FAILURE);
  }
  up->next = head;
  strncpy(up->name, name, sizeof(up->name));
  up->secs = secs;
  Total += secs;

  return up;
}
