NAME = codexion

CFLAGS = -Wall -Wextra -Werror -pthread

CC = cc

SRC = main.c monitor.c init.c heap_sort.c \
		creator.c parsing.c scheduler.c \
		simulation.c utils.c queue.c

HEADER = coders.h

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