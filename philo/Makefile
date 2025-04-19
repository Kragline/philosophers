NAME = philo

CC = cc
CCFLAGS = -Wall -Wextra -Werror

HEADER_DIR = include/
SRC_DIR = src/
OBJS_DIR = objs/

FILENAMES = main utils validation allocation destroy philo monitoring
SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILENAMES)))
OBJS = $(addsuffix .o, $(addprefix $(OBJS_DIR), $(FILENAMES)))

all: $(NAME)

$(NAME): $(OBJS) $(HEADER_DIR)philosophers.h $(SRCS)
	@$(CC) $(CCFLAGS) -I$(HEADER_DIR) $(SRCS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) -c $(CCFLAGS) -I$(HEADER_DIR) $< -o $@

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re