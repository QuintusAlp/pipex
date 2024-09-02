SRCS = 	./srcs/pipex.c ./srcs/execute.c ./srcs/ft_error.c

SRCS_BONNUS = ./srcs/pipex_bonus.c ./srcs/execute_bonus.c ./srcs/ft_child_bonus.c \
			./srcs/ft_error.c ./srcs/ft_child_utils_bonus.c

OBJDIR = objets
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONNUS = $(SRCS_BONNUS:%.c=$(OBJDIR)/%.o)
LIB = make -C ./my_libft
INCS = includes
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror 
NAME = pipex
BONUS_NAME = pipex_bonus

GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[1;34m
NC = \033[0m

all: titre ${NAME}


$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR) $(OBJDIR)/srcs
	@${CC} ${CFLAGS} -I ${INCS} -c $< -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR) $(OBJDIR)/srcs
	@${CC} ${CFLAGS} -I ${INCS} -c $< -o $@

bonus: titre ${OBJS_BONNUS}
		@${LIB}
		@echo "${GREEN}compiling pipex bonus...${NC}"
		@${CC} ${CFLAGS} ${OBJS_BONNUS} -L./my_libft -lft -o ${BONUS_NAME}
		@printf "\r${YELLOW}Compiling: [${GREEN}%-50s${YELLOW}] %d/%d${NC}" $$(printf "#%.0s" $$(seq 1 $$(expr $$(find $(OBJDIR) -type f -name '*.o' | wc -l) \* \
	 	50 / $(words $(SRCS))))) $$(find $(OBJDIR) -type f -name '*.o' | wc -l) $(words $(SRCS))
		@echo "\n${BLUE} ./pipex_bonus [parametters] ready to use ${NC}"

${NAME}: ${OBJS}
	@${LIB}
	@echo "${GREEN}compiling pipex...${NC}"
	@${CC} ${CFLAGS} ${OBJS} -L./my_libft -lft -o ${NAME}
	@printf "\r${YELLOW}Compiling: [${GREEN}%-50s${YELLOW}] %d/%d${NC}" $$(printf "#%.0s" $$(seq 1 $$(expr $$(find $(OBJDIR) -type f -name '*.o' | wc -l) \* \
	 50 / $(words $(SRCS))))) $$(find $(OBJDIR) -type f -name '*.o' | wc -l) $(words $(SRCS))
	@echo "\n${BLUE} ./pipex [parametters] ready to use ${NC}"


titre:
	@echo "\n"
	@echo "${BLUE}      ___                     ___         ___           ___      "
	@echo "     /\  \                   /\  \       /\__\         /|  |     "
	@echo "    /::\  \     ___         /::\  \     /:/ _/_       |:|  |     "
	@echo "   /:/\:\__\   /\__\       /:/\:\__\   /:/ /\__\      |:|  |     "
	@echo "  /:/ /:/  /  /:/__/      /:/ /:/  /  /:/ /:/ _/_   __|:|__|     "
	@echo " /:/_/:/  /  /::\  \     /:/_/:/  /  /:/_/:/ /\__\ /::::\__\_____"
	@echo " \:\/:/  /   \/\:\  \__  \:\/:/  /   \:\/:/ /:/  / ~~~~\::::/___/"
	@echo "  \::/__/     ~~\:\/\__\  \::/__/     \::/_/:/  /      |:|~~|    "
	@echo "   \:\  \        \::/  /   \:\  \      \:\/:/  /       |:|  |    "
	@echo "    \:\__\       /:/  /     \:\__\      \::/  /        |:|__|    "
	@echo "     \/__/       \/__/       \/__/       \/__/         |/__/     "
	@echo "\n \n"

clean:
	@${RM} -r ${OBJDIR}
	@make clean -C ./my_libft

fclean: clean
	@${RM} ${NAME}
	@${RM} ${BONUS_NAME}
	@make fclean -C ./my_libft

re: fclean all

.PHONY: all clean fclean re