# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 18:35:35 by fpereira          #+#    #+#              #
#    Updated: 2023/02/22 16:22:51 by fpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f
MKD			=	mkdir
INC			=	-I ./includes

NAME		=	minitalk
SERVER		=	server
CLIENT		=	client

OBJ_PATH	=	obj

SRC_LIBFT	=	./srcs/libft
LIBFT		=	./srcs/libft/libft.a

SRC_PRINTF	=	./srcs/printf
FT_PRINTF	=	./srcs/printf/ft_printf.a

SRC_NAME	=	client.c	\
				server.c

SRC_PATH	=	.

all: $(NAME)

$(LIBFT): $(shell make -C $(SRC_LIBFT) -q libft.a)
	make -C $(SRC_LIBFT)

$(FT_PRINTF): $(shell make -C $(SRC_PRINTF) -q ft_printf.a)
	make -C $(SRC_PRINTF)

$(SERVER) : $(OBJ_PATH)/server.o
	$(CC) $(CFLAGS) $(OBJ_PATH)/server.o $(INC) $(LIBFT) $(FT_PRINTF) -o $(SERVER)

$(CLIENT) : $(OBJ_PATH)/client.o
	$(CC) $(CFLAGS) $(OBJ_PATH)/client.o $(INC) $(LIBFT) $(FT_PRINTF) -o $(CLIENT)

$(NAME) : $(LIBFT) $(FT_PRINTF) $(CLIENT) $(SERVER)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@


clean:
	$(RM) $(OBJ_PATH)/*.o
	make fclean -C $(SRC_LIBFT)
	make fclean -C $(SRC_PRINTF)

fclean: clean
		make fclean -C $(SRC_LIBFT)
		make fclean -C $(SRC_PRINTF)
		$(RM) $(NAME)
		$(RM) $(CLIENT)
		$(RM) $(SERVER)
		if [ -d $(OBJ_PATH) ]; then rmdir $(OBJ_PATH); fi

re: fclean all