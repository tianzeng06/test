CC=g++
OBJS=main.o file_download.o
EXEC=main
CPPFLAGS=-std=c++11
.PHONY:clean

$(EXEC):$(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CPPFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
