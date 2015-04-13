.PHONY: clean

build/main: build/main.o build/charbuf.o
	gcc -g -o $@ $^

build/%.o: %.c
	@mkdir -p build
	gcc -g -std=c11 -c -o $@ -Wall -Wextra $<

clean:
	rm -r build
