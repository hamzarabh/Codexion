NAME = codexion

CFLAGS = -Wall -Wextra -Werror

CC = cc

SRC = main.c monitor.c init.c heap_sort.c \
		creator.c parsing.c scheduler.c \
		simulation.c utils.c queue.c

OBJC = $(SRC:%.c=%.o)



all:

$(NAME): OBJC
	$(CC) $(CFLAGS)

%.o:%.c:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJC) 

fclean:

re:

.PHONY: clean 