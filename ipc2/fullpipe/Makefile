CC=gcc
CFLAGs=-Wall
OBJS=fullpipe.o
EXEC=main
.PHONY:clean

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

clean:
	rm -rf $(EXEC) $(OBJS)

