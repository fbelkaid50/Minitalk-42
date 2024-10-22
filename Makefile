# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbelkaid <fbelkaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/26 07:38:41 by fbelkaid          #+#    #+#              #
#    Updated: 2024/10/22 11:08:38 by fbelkaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror 
READ = -lreadline -L ~/goinfre/homebrew/opt/readline/lib -I ~/goinfre/homebrew/opt/readline/include 
LDFLAGS = -lreadline
RM = rm -f
P_SRC= ./manda/main.c  ./manda/utils.c ./manda/handle_signals.c ./manda/check_syntax.c ./manda/tokenizing_inputs.c ./manda/parcing.c ./manda/parcing_utils.c ./manda/parcing_Wredir.c
# EXEC_SRC=	./execution/execute_builtin.c \
# 			./execution/execute_line.c \
# 		./execution/execution_utils.c\
# 			./execution/execution_utils2.c \
# 			./execution/pipes.c \
# 			./execution/redirections.c \
# 			./execution/safe_functions.c

# BUILTIN_SRCS=	./builtins/cd.c \
# 				./builtins/echo.c \
# 				./builtins/env_utils.c \
# 				./builtins/env.c \
# 				./builtins/exit.c \
# 				./builtins/export.c \
# 				./builtins/pwd.c \
# 				./builtins/unset.c
# LIBF=./libft/libftprintf.a

OBJ= $(P_SRC:.c=.o) $(EXEC_SRC:.c=.o) $(BUILTIN_SRCS:.c=.o) 
	# $(CC) $(CFLAGS) $(READ) -c ./manda/handle_signals.c -o handle_signals.o
%.o: %.c
	$(CC) $(CFLAGS) -I ~/goinfre/homebrew/opt/readline/include  -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBF) $(READ) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
