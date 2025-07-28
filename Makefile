GREEN   = \033[1;32m
WHITE	= \033[0m
CLEAR	= \r\033[K

NAME	= philo

CC		= gcc -g3 -fsanitize=address

FLAGS	= -Wall -Wextra -Werror

SRCS	= main.c			\
			init_data.c		\
			init_philos.c	\
			simulation.c	\
			actions.c		\
			free_data.c		\
			utils.c			\

$(NAME) :
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	rm -rf $(NAME)

clean :
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
