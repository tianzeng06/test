CC=g++
OBJS=main.o db.o
EXEC=main
CPPFLAGS=-std=c++11
LIB=-L/usr/lib64 -lmysqlclient
.PHONY:clean

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CPPFLAFS) $(LIB)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
