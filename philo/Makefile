NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -fsanitize=thread 
INCLUDE = inc/
FOLDER = srcs/
OBJFOLDER = obj/
SRCS = main.c actions.c checks.c clean.c dinner.c init.c monitoring.c time.c utils.c

OBJS = $(SRCS:%.c=$(OBJFOLDER)%.o)

$(OBJFOLDER)%.o: $(FOLDER)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all: $(NAME)

clean:
	@rm -rf $(OBJFOLDER)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re