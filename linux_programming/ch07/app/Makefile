all: application

CC=clang
INCLUDE=/usr/include/gdbm
LIBS=gdbm_compat -lgdbm
CFLAGS=-W

app_ui.o: app_ui.c cd_data.h
	$(CC) $(CFLAGS) -c app_ui.c

access.o: access.c cd_data.h
	$(CC) $(CFLAGS) -I$(INCLUDE) -c access.c

application: app_ui.o access.o
	$(CC) $(CFLAGS) -o application app_ui.o access.o -l$(LIBS)

clean:
	rm -f application *.o

nodmfiles:
	rm -f *.dir *.pag
