CC=gcc
CFLAGS=-Wall -lpthread
EXEC=main
OBJS=rwlock.o
.PHONY:clean

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

clean:
	rm -rf $(EXEC) $(OBJS)
