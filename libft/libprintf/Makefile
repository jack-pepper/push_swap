# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmalie <mmalie@student.42nice.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 09:35:38 by mmalie            #+#    #+#              #
#    Updated: 2024/12/29 01:46:34 by mmalie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################################################
### Name of the file obtained after compilation ###
###################################################

NAME = libprintf.a

############################
### Compilation settings ###
############################

CC=cc
CFLAGS=-Wall -Wextra -Werror

AR=ar
ARFLAGS=-rcs

####################
### Dependencies ###
####################

DEPS_LIBFT = ../libft.h
DEPS = libprintf.h

####################
### Source files ###
####################

LIBPRINTF = ${SRC_DIR_LIBPRINTF}ft_printf.c \
	    ${SRC_DIR_LIBPRINTF}ft_spec_conv.c \
	    ${SRC_DIR_LIBPRINTF}ft_putchar_fd_count.c \
	    ${SRC_DIR_LIBPRINTF}ft_putstr_fd_count.c \
	    ${SRC_DIR_LIBPRINTF}ft_putnbr_fd_count.c \
	    ${SRC_DIR_LIBPRINTF}ft_put_ui_fd_count.c \
	    ${SRC_DIR_LIBPRINTF}ft_itohex.c \

SRC = ${LIBPRINTF}

####################
### Object files ###
####################

OBJ = $(SRC:.c=.o)

### Default rules (compile the executable)
all: $(NAME)
	$(info )
	$(info   L       III  BBBBB   PPPP   RRRR   III  N   N  TTTTT  FFFFF   )
	$(info   L        I   B   B   P   P  R   R   I   NN  N    T    F       )
	$(info   L        I   BBBB    PPPP   RRRR    I   N N N    T    FFFF    )
	$(info   L        I   B   B   P      R  R    I   N  NN    T    F       )
	$(info   LLLLL   III  BBBBB   P      R   R  III  N   N    T    F       )
	$(info )
	$(info ================================================================)
	$(info       L I B P R I N T F   C O M P I L E D!                      )
	$(info ================================================================)
	$(info )

### Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

###############################
### Create a static library ###
###############################

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	ranlib $(NAME)

#########################
### Cleaning-up rules ###
#########################

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

# Rule to recompile everything (execute fclean, then re)
re: fclean all

#########################
### .PHONY Exceptions ###
#########################

.PHONY: all clean fclean re bonus
