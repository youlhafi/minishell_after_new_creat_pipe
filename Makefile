# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhabib-a <mhabib-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/22 08:49:24 by mhabib-a          #+#    #+#              #
#    Updated: 2023/07/22 11:33:40 by mhabib-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
PARS  = main.c tools.c tools2.c tokenize.c env.c ft_lex.c parse_input.c ft_quotes.c ft_free.c env_tools.c tokenize_tools.c ft_quotes_tools.c parse_input_tools.c trim_quotes.c parse_quote.c signals.c
EXC =  minishell.c ft_split.c utils.c ft_cd.c ft_echo.c ft_env.c ft_export.c check_pipe.c exec.c open_file.c multiple_pipe.c here_doc.c get_next_line_utils.c error.c ft_unset.c ft_export2.c  dup_fd.c ft_free2.c single_cmd.c builtins.c export_help.c init.c
SRC = $(PARS) $(EXC)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
CPPFLAGS=  ${shell brew --prefix}/opt/readline/include
LDFLAGS= ${shell brew --prefix}/opt/readline/lib
RFLAG = -lreadline
VAR = $(CPPFLAGS) $(LDFLAGS)
CC = cc 
RM = rm -f
LIB = minishell.h
LIBFTLIB = libft/libft.a

all :  $(NAME)

$(NAME) : $(OBJ)
	$(CC) -L $(LDFLAGS) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFTLIB) $(RFLAG)

%.o : %.c $(LIB)
	make -C libft/
	$(CC) $(CFLAGS) -I $(CPPFLAGS) -c $<

clean:
	make clean -C libft/
	$(RM) $(OBJ)

fclean : clean
	make fclean -C libft/
	$(RM) $(NAME)

re : fclean all