all:
	gcc main.c linked_list.c -o main.o -g

clean:
	-rm -rf *.o *.exe
