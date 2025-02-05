#==================================FLAGS======================================#

NAME = philo_bonus
CC = cc
C_FLAGS = -Wall -Wextra -Werror -g3
LIBS = -pthread

#=================================COLORS======================================#

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
YELLOW = \033[0;33m

#=================================SOURCES=====================================#

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

#=================================HEADERS=====================================#

INC_DIR = includes
INC = $(INC_DIR)/philo_bonus.h

#=================================COMPILING====================================#

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	@$(CC) $(C_FLAGS) -o $(NAME) $(OBJ) $(LIBS)
	@echo "$(GREEN)$(NAME) has been compiled!$(RESET)"

%.o: %.c $(INC)
	@$(CC) $(C_FLAGS) -I $(INC_DIR) -c $< -o $@

#=================================LEAK========================================#

ARGS=" "

leak:
	@echo "ARG1=number_of_philosophers"
	@echo "ARG2=time_to_die"
	@echo "ARG3=time_to_eat"
	@echo "ARG4=time_to_sleep"
	@echo "ARG5=number_of_times_each_philosopher_must_eat"
	@echo "$(GREEN)Checking leaks...$(RESET)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

#=================================NORM========================================#

norm:
	@echo "$(YELLOW)Checking norminette...$(RESET)"
	norminette $(SRC) $(INC)

#=================================GDB=========================================#

gdb:
	@echo "$(YELLOW)ARG1=number_of_philosophers"
	@echo "ARG2=time_to_die"
	@echo "ARG3=time_to_eat"
	@echo "ARG4=time_to_sleep"
	@echo "[ARG5=number_of_times_each_philosopher_must_eat]$(RESET)"
	@echo "$(GREEN)Starting gdb...$(RESET)"
	gdb --tui --args ./$(NAME) $(ARGS)

#=================================RULES=======================================#

run:
	@echo "$(YELLOW)ARG1=number_of_philosophers"
	@echo "ARG2=time_to_die"
	@echo "ARG3=time_to_eat"
	@echo "ARG4=time_to_sleep"
	@echo "[ARG5=number_of_times_each_philosopher_must_eat]$(RESET)"
	@echo "$(GREEN)Running $(NAME)...$(RESET)"
	@./$(NAME) $(ARGS)

clean:
	@echo "$(RED)Deleting objects...$(RESET)"
	@rm -f $(OBJ)

fclean: clean
	@echo "$(RED)Deleting $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re