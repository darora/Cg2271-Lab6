all: clean build
	echo "All done"
clean:
	rm -f 1
build:
	clang -pthread lab6_1.c -o 1
