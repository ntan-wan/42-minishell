NAME		:=	minishell
EXTRA_LIBS	:=	-lreadline -lncurses
UNUSED_SET	:=	-Wno-unused-parameter -Wno-unused-function -Wno-unused-variable
CC			:=	gcc
# CFLAGS		:=	-Wall -Wextra -Werror
CFLAGS		:=	-Wall -Werror
CFLAGS		+=	${UNUSED_SET}
# CFLAGS		+=	-fsanitize=address -g
LIBFT_DIR	:=	libft/
LIBFT		:=	${LIBFT_DIR}libft.a
LIBFT_MAKE	:=	make -C ${LIBFT_DIR}

SRC_DIR		:=	srcs
SRCS		:=	$(shell find ${SRC_DIR} -name "*.c")

HEADER		:=	$(shell find ${SRC_DIR} -name "*.h")
INCLUDE		:=	$(addprefix -I, $(dir ${HEADER}) ${LIBFT_DIR}include/)

OBJ_DIR		:=	objs
OBJS		:=	$(patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRCS})
RM			:=	rm -rf
#text_color
DEFAULT		:=	\033[0m
RED			:=	\033[0;31m
GREEN		:=	\033[0;32m
YELLOW		:=	\033[0;33m
CYAN		:=	\033[1;36m
MAGENTA 	:=	\033[95m

all: ${NAME}

${OBJ_DIR} :
	mkdir $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${HEADER} | ${OBJ_DIR}
	@mkdir -p ${@D}
	@printf "${MAGENTA}Compiling: $<${DEFAULT}\n"
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

${NAME}: ${OBJS}
	@${LIBFT_MAKE} \
		&& ${CC} ${CFLAGS} $^ ${LIBFT} ${EXTRA_LIBS} -o $@ \
		&& echo "$(CYAN)${NAME} done !$(DEFAULT)"

san: ${SRCS}
	@${LIBFT_MAKE} \
		&& @${CC} ${CFLAGS} -fsanitize=address -g ${INCLUDE} $^ ${LIBFT} ${EXTRA_LIBS} -o ${NAME}

clean:
	@${LIBFT_MAKE} clean
	${RM} ${OBJ_DIR}

fclean: clean
	@${LIBFT_MAKE} fclean
	${RM} ${NAME}

re: fclean all

kill :
	@killall -9 ${NAME}

valgrind :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME}

norm:
	norminette ${HEADER} ${SRCS}

.PHONY: clean fclean all re ${LIBFT}
