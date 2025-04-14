CC = gcc
CCFLAGS = -g
TARGET = add2pb findphone

all: $(TARGET)

add2pb: add2PB.c
	$(CC) $(CCFLAGS) $^ -o $@

findphone: findPhone.c
	$(CC) $(CCFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f $(TARGET)