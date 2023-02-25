# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 15:07:14 by alvgomez          #+#    #+#              #
#    Updated: 2023/02/25 11:52:39 by alvgomez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

#HEADERS
INCL_DIR = includes
INCL = $(wildcard $(INCL_DIR)/*.h)

#SOURCES
SRC_DIR = sources
SRC = $(wildcard $(SRC_DIR)/*.c)

# OBJECTS
OBJ_DIR = objects
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

CC = gcc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

all:	${NAME}
		 
${NAME}:	$(OBJ_DIR) ${OBJ}
		${CC} ${FLAGS} ${OBJ} -lpthread -o ${NAME}

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)
		
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCL)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c $< -o $@

clean:	
		@rm -f ${OBJ}

fclean:	clean
		@rm -f ${NAME}
		@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re