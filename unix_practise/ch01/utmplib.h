#include <utmp.h>
#include <fcntl.h>
#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

int utmp_open(char *filename);

int utmp_reload();

struct utmp *utmp_next();

int utmp_seek(off_t offset, int whence);

void utmp_close();
