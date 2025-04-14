CC = gcc -std=gnu99
FLAGS = -ggdb

run: signal_reciever signal_sender

signal_reciever: signal_reciever.c
	$(CC) $(FLAGS) $< -o $@

signal_sender: signal_sender.c
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -f signal_sender signal_reciever