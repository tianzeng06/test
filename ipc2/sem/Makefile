CC=gcc
CFLAGS=-lpthread -Wall
EXEC=main
OBJS=sem.o
.PHONY:clean

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

clean:
	rm -rf $(OBJS) $(EXEC)
