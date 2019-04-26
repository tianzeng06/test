CC=g++
CPPFLAGS=-Wall -lpthread -std=c++11 #-g -rdynamic
EXEC=main
OBJS=main.o threadpool.o cond.o mutex.o task.o
.PHONY:clean

$(EXEC):$(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(CPPFLAGS)

clean:
	rm -rf $(EXEC)
	rm -rf $(OBJS)

