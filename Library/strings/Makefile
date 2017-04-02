file = libcmp.o libmisc.o libsrh.o libsplit.o
CFLAGS = -Wall
libstr.so: $(file)
	gcc --share $(file) -o libstr.so

#libcmp.o:libcmp.c
#	gcc -c libcmp.c -o libcmp.o

main.o:main.c
	gcc main.c -lstr -I/. -L/. -o main
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.so
 
