#if defined(__GUN_LIBRARY__) && !defined(__SEM_SEMUN_UNDEFINED)
#else
union semun {
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;
};
#endif
