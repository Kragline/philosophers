NAME = philo

CC = cc
CCFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3

HEADER_DIR = include/
SRC_DIR = src/
OBJS_DIR = objs/

GREEN = \033[1;32m
PURPLE = \033[1;35m
WHITE = \033[0;37m

FILENAMES = main utils validation allocation destroy philo monitoring
SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILENAMES)))
OBJS = $(addsuffix .o, $(addprefix $(OBJS_DIR), $(FILENAMES)))

all: $(NAME)

$(NAME): $(OBJS) $(HEADER_DIR)philosophers.h $(SRCS)
	@echo "Making objects directory..."
	@sleep 0.2
	@echo "Making object files..."
	@sleep 0.2
	@echo "Compiling executable..."
	@$(CC) $(CCFLAGS) -I$(HEADER_DIR) $(SRCS) -o $(NAME)
	@echo "$(GREEN)Done!"

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) -c $(CCFLAGS) -I$(HEADER_DIR) $< -o $@

clean:
	@echo "Working on it..."
	@sleep 0.2
	@rm -rf $(OBJS_DIR)
	@echo "Cleaned object files!"

fclean: clean
	@rm -f $(NAME)
	@sleep 0.2
	@echo "$(PURPLE)Cleaned up everything!$(WHITE)"

re: fclean all

.PHONY: all clean fclean re