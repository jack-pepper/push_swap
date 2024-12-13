# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmalie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 09:35:38 by mmalie            #+#    #+#              #
#    Updated: 2024/11/14 09:35:45 by mmalie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################################################
### Name of the file obtained after compilation ###
###################################################

NAME = push_swap

############################
### Compilation settings ###
############################

CC=cc
CFLAGS=-Wall -Wextra -Werror

####################
### Dependencies ###
####################

DEPS = push_swap.h
DEPS_LIBFT = ./libft/libft.h
LIBFT = ./libft/libft.a

####################
### Source files ###
####################

SRC = push_swap.c \
      args_parser.c \
      swapper.c \
      pusher.c \
      rotater.c \
      reverse_rotater.c

### Object files
OBJ = $(SRC:.c=.o)

##############################################
### Default rules (compile the executable) ###
##############################################

all: $(LIBFT) $(NAME)

$(LIBFT):
	cd libft && make

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -Llibft -lft -o $(NAME)

######################################
### Compile .c files into .o files ###
######################################

$(OBJ): %.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

#########################
### Cleaning-up rules ###
#########################

clean:
	cd libft && make clean
	rm -f $(OBJ)

fclean: clean
	cd libft && make fclean
	rm -f $(NAME)

re: fclean all

#########################
### .PHONY Exceptions ###
#########################

.PHONY: all clean fclean re bonus
