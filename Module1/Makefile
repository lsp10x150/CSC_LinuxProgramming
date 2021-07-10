buildall: hello libHello.so

hello: main.c hello.h libHello.so
	gcc main.c -L. -ldl -o hello

libHello.so:
	gcc -shared hello.c -o libHello.so

clean:
	rm hello
	rm libHello.so
	rm *.o

