# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elerika <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/15 00:08:49 by elerika           #+#    #+#              #
#    Updated: 2022/01/15 00:08:52 by elerika          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
HEADER = pipex.h
SRCS = pipex.c	ft_split.c	sources.c\

OBJS = ${SRCS:%.c=%.o}
FLAGS = -Wall -Wextra -Werror

.PHONY : all clean fclean re hello

all : ${NAME} hello

${NAME} : ${HEADER} ${OBJS}
	@gcc ${FLAGS} ${OBJS} -o ${NAME}
	@echo "$(NAME) Created!" $(EOC)

%.o : %.c ${HEADER}
	@gcc ${FLAGS} -c $< -o $@

clean :
	@rm -rf $(OBJS) $(HEADER:%.h=%.h.gch)

fclean : clean
	@rm -rf $(NAME)
	@echo "$(NAME) make fclean!"

re : fclean all