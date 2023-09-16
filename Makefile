CC = gcc
CFLAGS = -g	

all: getip

%: %.c 
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.dSYM getip