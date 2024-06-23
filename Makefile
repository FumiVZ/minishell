NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g  
CC = cc
BUILD_DIR = build

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


LIBFT = libft/libft.a
LIB_PATH = libft
HEADER_PATH = code/header

OBJECTS = $(SRC:%.c=$(BUILD_DIR)/%.o)
HEADER = code/header/minishell.h \
		 code/header/struct.h \
		 code/header/child.h \
		 code/header/error.h \
		 code/header/minishell.h \
		 code/header/parthing.h \
		 code/header/pipex.h \
		 code/header/struct.h \
		 code/header/var_global.h 


all: $(BUILD_DIR) $(LIBFT) $(NAME)

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


$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIBFT) -lreadline -lncurses

$(BUILD_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER_PATH) -I$(LIB_PATH)

$(LIBFT):
	$(MAKE) -C $(LIB_PATH) 

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIB_PATH) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_PATH) fclean

re: fclean all

.PHONY: all clean fclean re $(LIBFT)
