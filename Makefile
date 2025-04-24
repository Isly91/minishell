#Makefile for the Minishell project

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline
RM = rm -rf

NAME = minishell
HEADER = minishell.h

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libftprintf.a

ODIR = obj

SOURCE = main.c \
		commands.c \
		initialize.c \
		compare.c \
		printing.c \
		length.c \
		expander.c \
		freeing.c \
		clear.c \
		signal_handling.c \
		env_manipulation.c \
		execution_utils.c \
		env_manipulation2.c \
		other_commands.c \
		env_command.c \
		exit_command.c \
		unset_command.c \
		export_command.c \
		echo_command.c \
		chdir_command.c \
		pwd_command.c \
		here_doc.c \
		input_red.c \
		output_red.c \
		parse_str.c \
		parse_quotes_vars.c \
		parse_utils.c \
		error_message.c \
		parser_start.c \
		pipe_list.c \
		redirection_list.c \
		commands1.c \
		signal_handling1.c

OBJECT = $(addprefix $(ODIR)/,$(SOURCE:.c=.o))

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    CFLAGS += -I/opt/homebrew/opt/readline/include
    LFLAGS += -L/opt/homebrew/opt/readline/lib
else
    CFLAGS += -I/usr/include/readline
    LFLAGS += -L/usr/lib -lreadline
endif

all: $(LIBFT) $(NAME)

$(NAME): $(OBJECT) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

$(ODIR):
	@mkdir -p $@

$(ODIR)/%.o: %.c $(HEADER) | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if [ -d "$(ODIR)" ]; then \
		$(RM) $(ODIR); \
	fi
	@$(MAKE) clean -sC $(LIBFT_DIR)

fclean: clean
	@if [ -x "$(NAME)" ]; then \
		$(RM) $(NAME); \
	fi
	@$(MAKE) fclean -sC $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
