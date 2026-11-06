
NAME := libasm.a
TEST_BIN := tests

# ============================================================================ #
#        Compiler, flags and args                                              #
# ============================================================================ #

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INC_DIR) -g

NASM := nasm
NASMFLAGS := -f elf64

# ============================================================================ #
#        Directories                                                           #
# ============================================================================ #

INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj

# ============================================================================ #
#        Sources and objects                                                   #
# ============================================================================ #

ASM_SRC := $(wildcard $(SRC_DIR)/*.asm)
ASM_OBJ := $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.o, $(ASM_SRC))

MAIN_SRC := $(SRC_DIR)/main.c
MAIN_OBJ := $(OBJ_DIR)/main.o

# ============================================================================ #
#        Main rules                                                            #
# ============================================================================ #

all: $(NAME) $(TEST_BIN)

$(NAME): $(ASM_OBJ)
	ar rcs $@ $^

$(TEST_BIN): $(NAME) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(MAIN_OBJ) -L. -lasm -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================================================ #
#        Cleaning rules                                                        #
# ============================================================================ #

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(TEST_BIN)

re: fclean all

.PHONY: all clean fclean re
