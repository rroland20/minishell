# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rroland <rroland@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/31 17:04:02 by rroland           #+#    #+#              #
#    Updated: 2021/09/27 19:20:37 by rroland          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror 

SOURCE = minishell.c dop_func.c dop_func2.c signal.c split_parser.c parser.c \
execve.c split_argv.c split_org.c substr_memcpy.c cmd_env.c clear.c lexis.c \
pipe.c cmd_export.c ft_itoa.c cmd_cd_pwd.c shlvl_shell.c cmd_export_2.c \
cmd_unset_echo.c cmd_exit.c func_execve.c dop_func3.c split_parser2.c

OBJECTS = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@gcc $(SOURCE) -o $(NAME) -g -lreadline -ltermcap


# добавь $(FLAGS) фикс либы readline
%.o:%.c
	@export CPATH=/Users/rroland/.brew/opt/readline/include ; gcc -c  $(SOURCE)

clean:
	@rm -rf $(OBJECTS)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
