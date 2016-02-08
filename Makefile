CC=			cc

CD=			cd

MV=			mv -f

RM=			rm -f

SRCS=			client_repertory/main.c

SRCS2=			server_repertory/main.c

OBJS=			$(SRCS:.c=.o)

OBJS2=			$(SRCS2:.c=.o)

NAME=			client

NAME2=			server

PATH1=			client_repertory/

PATH2=			server_repertory/

PATH3=			..

all:			$(NAME) $(NAME2)

$(NAME):		$(PATH1)$(CLIENT)

$(PATH1)$(CLIENT):	$(OBJS)
			$(CC) -o $(NAME) $(SRCS)
			$(MV) $(NAME) $(PATH1)

$(NAME2):		$(PATH2)$(SERVER)

$(PATH2)$(SERVER):	$(OBJS2)
			$(CC) -o $(NAME2) $(SRCS2)
			$(MV) $(NAME2) $(PATH2);

clean:
			$(RM) $(OBJS)
			$(RM) $(OBJS2)

fclean:			clean
			$(CD) $(PATH1) ; $(RM) $(NAME)
			$(CD) $(PATH2) ; $(RM) $(NAME2)

re:			fclean all

.PHONY:			re fclean clean all
