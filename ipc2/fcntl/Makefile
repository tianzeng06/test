CC=gcc
CLFAGS=-Wall
EXEC=main
OBJS=fcntl.o
.PHONY:clean

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

clean:
	rm -rf $(OBJS) $(EXEC)
