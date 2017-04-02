file = libbootp.o
CFLAGS = -Wall

libboot.so: $(file)
	gcc --share $(file) -o libboot.so

bootpc: bootpc.c bootp.h libbootp.h libboot.so libbootp.c
	gcc bootpc.c -lboot -I. -L. -lm -o bootpc
	
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.so *.out *.c~ *.h~ bootpc

