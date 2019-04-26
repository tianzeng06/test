CC=gcc
CFLAGS=-Wall -lpthread
EXEC=main
OBJS=syn1.o
.HPONY:clean

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

clean:
	rm -rf $(OBJS) $(EXEC)
