# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmalie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 09:35:38 by mmalie            #+#    #+#              #
#    Updated: 2024/11/19 11:02:25 by mmalie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Name of the file obtained after compilation
NAME = push_swap

### Compilation settings
CC=cc
CFLAGS=-Wall -Wextra -Werror -I ./libft
AR=ar
ARFLAGS=-rcs

### Dependencies
DEPS_SRC = push_swap.h \

LIBFT_PATH = ./libft
LIBFT = ./libft/libft.a

### Source files
SRC = push_swap.c \

### Object files
OBJ = $(SRC:.c=.o)
##ALL_SRC = ${SRC} ${BONUS_SRC}
##ALL_OBJ = $(ALL_SRC:.c=.o)

### Default rule (compile the executable)
all: $(NAME)

### Main rule
$(NAME): $(OBJ)
	cd libft && make
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft

### Compile .c files into .o files
# $< = current source file ; $@ = matching object file
# The -c flag asks the compiler not to link the files
# and to produce only the object file.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Make bonus rule
#bonus: $(ALL_OBJ)
#	cd libft && make
#	cp $(LIBFT) $(NAME)
#	$(AR) $(ARFLAGS) $(NAME) $(ALL_OBJ)

# Rule to clean (remove) the object files
clean:
	cd libft && make clean
	rm -f $(OBJ) $(ALL_OBJ)

# Rule to clean (remove) the object files and the executable
fclean: clean
	cd libft && make fclean
	rm -f $(NAME)

# Rule to recompile everything (execute fclean, then re)
re: fclean all

# Shows that those targets are not files but commands
.PHONY: all clean fclean re bonus
