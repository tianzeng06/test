CC=gcc
CFLAGS=-Wall
OBJS=fifo.o
EXEC=main
.PHONY:clean

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

clean:
	rm -rf $(OBJS) $(EXEC)
