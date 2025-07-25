NAME	= philo

CC		= gcc -g3 -fsanitize=address 

FLAGS	= -Wall -Wextra -Werror

SRCS	= main.c			\
			init_data.c		\
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
