all:
	gcc main.c linked_list.c -o main.o

clean:
	-rm -rf *.o *.exe
