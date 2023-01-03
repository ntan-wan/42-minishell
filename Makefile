NAME = minishell
UNAME = $(shell uname)

#text_color
COLOR_OFF =\033[0m
RED =\033[0;31m
GREEN =\033[0;32m
YELLOW =\033[0;33m
CYAN =\033[1;36m
MAGNETA =\033[95m 

ifeq ($(UNAME), Linux)
	EXTRA_LIBS = -lreadline -lncurses
endif

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft2/
LIBFT_LIB = $(addprefix $(LIBFT_DIR), libft.a)

HEADER_DIR =  $(shell find . -name "includes" -type d)
HEADER = $(addprefix "-I", $(HEADER_DIR))

DIRS = $(shell find srcs -type d)
SRCS = $(wildcard $(foreach fd, $(DIRS), $(fd)/*.c))
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:c=o))

all : $(NAME)

$(LIBFT_LIB) :
	@make bonus -C $(LIBFT_DIR)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "$(MAGNETA)Compiling: $<$(COLOR_OFF)\n"
	@$(CC) -o $@  -c $< $(HEADER)

$(NAME) : $(LIBFT_LIB) $(OBJS)
	@$(CC) $(OBJS) $(HEADER) $(LIBFT_LIB) $(EXTRA_LIBS) -o $(NAME)
	@echo "$(CYAN)$(NAME) done !$(COLOR_OFF)"

bonus : all

fclean :
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR) $(NAME)
	@echo "$(RED)Removed : obj files ($(NAME))$(COLOR_OFF)"
	@echo "$(RED)Removed : $(NAME)$(COLOR_OFF)"

re : fclean all

kill :
	@killall -9 $(NAME)

.PHONY : clean fclean all re
