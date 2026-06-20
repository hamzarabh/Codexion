NAME = codexion

CFLAGS = -Wall -Wextra -Werror -pthread

CC = cc

SRC = coders/main.c coders/monitor.c coders/init.c coders/heap_sort.c \
		coders/creator.c coders/parsing.c coders/scheduler.c \
		coders/simulation.c coders/utils.c coders/queue.c

HEADER = coders/coders.h

OBJC = $(SRC:%.c=%.o)



all: $(NAME)

$(NAME): $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJC) 

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: clean 