# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/21 10:20:33 by vfrolich          #+#    #+#              #
#    Updated: 2017/04/05 14:36:33 by vfrolich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
NAME			=	ft_ls
FLAGS           =	-Wall -Wextra -Werror
LIB_PATH		=	libft
LIB				=   $(LIB_PATH)/libft.a
LIB_LINK		=	-Llibft -lft
SRC				=	main.c create_lst.c data_handle.c display.c padding.c\
					padding_size.c sort.c arg_handle.c leaks_handle.c\
					sort_time.c display_2.c maj_min_handle.c vanilla_ls.c\
					display_3.c time_handle.c
HEADER			=	ft_ls.h
OBJS			=	$(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@make -C $(LIB_PATH)
	@$(CC) $(FLAGS) -c $(SRC)
	@$(CC) $(OBJS) $(LIB_LINK) -o $(NAME)

clean :
	@rm -f $(OBJS)
	@make -C $(LIB_PATH) clean

fclean : clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean

re : fclean all