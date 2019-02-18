prog=tasking

src=$(wildcard *.c)
obj=$(src:.c=.o)

LDFLAGS=

$(prog): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(prog)

install:$(prog)
	mkdir -p ~/.local/bin
	cp tasking ~/.local/bin
