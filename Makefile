NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = cc
BUILD_DIR = build

HEADER_LIBFT = libft/libft.h libft/GNL/gnl.h

SRC_LIBFT =	libft/ft_atoi.c \
		libft/ft_itoa.c \
		libft/ft_putendl_fd.c \
		libft/ft_strlcat.c \
		libft/ft_substr.c \
		libft/ft_bzero.c \
		libft/ft_putnbr_fd.c \
		libft/ft_strlcpy.c \
		libft/ft_tolower.c \
		libft/ft_calloc.c \
		libft/ft_memchr.c \
		libft/ft_putstr_fd.c \
		libft/ft_strlen.c \
		libft/ft_toupper.c \
		libft/ft_isalnum.c \
		libft/ft_memcmp.c \
		libft/ft_split.c \
		libft/ft_strmapi.c \
		libft/ft_isalpha.c \
		libft/ft_memcpy.c \
		libft/ft_strchr.c \
		libft/ft_strncmp.c \
		libft/ft_isascii.c \
		libft/ft_memmove.c \
		libft/ft_strdup.c \
		libft/ft_strnstr.c \
		libft/ft_isdigit.c \
		libft/ft_memset.c \
		libft/ft_striteri.c \
		libft/ft_strrchr.c \
		libft/ft_isprint.c \
		libft/ft_putchar_fd.c \
		libft/ft_strjoin.c \
		libft/ft_strtrim.c \
		libft/printf/ft_printf.c \
		libft/printf/ft_printf_utils.c \
		libft/ft_lstnew_bonus.c \
		libft/ft_lstadd_back_bonus.c \
		libft/ft_lstsize_bonus.c \
		libft/ft_lstadd_front_bonus.c \
		libft/ft_lstclear_bonus.c \
		libft/ft_lstdelone_bonus.c \
		libft/ft_lstiter_bonus.c \
		libft/ft_lstlast_bonus.c \
		libft/ft_lstmap_bonus.c \
		libft/GNL/gnl.c \
		libft/GNL/gnlu.c 

SRC = code/error/error_msg.c \
	  code/exec/child.c \
	  code/exec/child_utils.c \
	  code/exec/command.c \
	  code/exec/error.c \
	  code/exec/exec.c \
	  code/exec/free.c \
	  code/exec/here_doc.c \
	  code/exec/list.c \
	  code/exec/multiple_command.c \
	  code/exec/parentheses.c \
	  code/exec/parse_args.c \
	  code/exec/parse_ex.c \
	  code/exec/parse_infile.c \
	  code/exec/parse_outfile.c \
	  code/exec/pipex.c \
	  code/exec/utils.c \
	  code/exec/utils_dup.c \
	  code/prompt/prompt.c \
	  code/split_command/ascii_sort.c \
	  code/split_command/env_utils.c \
	  code/split_command/pattern_matching.c \
	  code/split_command/pattern_matching_utils.c \
	  code/split_command/quote_removal.c \
	  code/split_command/utils.c \
	  code/split_command/variables_env_search.c \
	  code/split_command/wildcard.c \
	  code/split_line/check_syntax.c \
	  code/split_line/check_syntax_split.c \
	  code/split_line/word_spliting.c \
	  code/split_line/word_spliting_utils.c \
	  builtins/cd/cd.c \
	  builtins/cd/cd_env.c \
	  builtins/echo/echo.c \
	  builtins/env/default_env.c \
	  builtins/env/env.c \
	  builtins/env/env_utils.c \
	  builtins/env/init_env.c \
	  builtins/exit/exit.c \
	  builtins/exit/free.c \
	  builtins/export/export.c \
	  builtins/pwd/pwd.c \
	  builtins/unset/unset.c \
	  builtins/history/history.c 


LIBFT = libft/libft.a
LIB_PATH = libft
HEADER_PATH = code/header

OBJECTS = $(SRC:%.c=$(BUILD_DIR)/%.o)
HEADER = code/header/minishell.h \
		 code/header/struct.h \
		 code/header/child.h \
		 code/header/minishell.h \
		 code/header/parthing.h \
		 code/header/pipex.h \
		 code/header/struct.h \
		 code/header/var_global.h 


all: $(NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/code
	mkdir -p $(BUILD_DIR)/bonus
	mkdir -p $(BUILD_DIR)/builtins
	mkdir -p $(BUILD_DIR)/builtins/echo
	mkdir -p $(BUILD_DIR)/builtins/cd
	mkdir -p $(BUILD_DIR)/builtins/pwd
	mkdir -p $(BUILD_DIR)/builtins/export
	mkdir -p $(BUILD_DIR)/builtins/unset
	mkdir -p $(BUILD_DIR)/builtins/env
	mkdir -p $(BUILD_DIR)/builtins/exit
	mkdir -p $(BUILD_DIR)/builtins/history
	mkdir -p $(BUILD_DIR)/code/split_line
	mkdir -p $(BUILD_DIR)/code/split_command
	mkdir -p $(BUILD_DIR)/code/error
	mkdir -p $(BUILD_DIR)/code/prompt
	mkdir -p $(BUILD_DIR)/code/prompt
	mkdir -p $(BUILD_DIR)/code/exec


$(NAME): $(BUILD_DIR) $(LIBFT) $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBFT) -lreadline -lncurses

$(BUILD_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_PATH) -I$(LIB_PATH)

$(LIBFT): $(SRC_LIBFT) $(HEADER_LIBFT)
	$(MAKE) -C $(LIB_PATH) 

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIB_PATH) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re  bonus
