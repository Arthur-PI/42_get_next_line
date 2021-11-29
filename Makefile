BUFF_SIZE	=	15

SRCS	=	get_next_line.c \
			get_next_line_utils.c \
			main.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	get_next_line

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra -D BUFFER_SIZE=$(BUFF_SIZE) -g3 -fsanitize=address

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		rm -rf *.o

fclean:		clean
		rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
