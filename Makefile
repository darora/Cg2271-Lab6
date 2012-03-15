all: clean build
	echo "All done"
clean:
	rm -f 1
	rm -f 2
build:
	clang -pthread lab6_1.c -o 1
	clang -pthread lab6_2.c -o 2
