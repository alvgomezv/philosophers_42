# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvgomez <alvgomez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 15:07:14 by alvgomez          #+#    #+#              #
#    Updated: 2023/02/27 17:01:02 by alvgomez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo/philo
BONUS = philo_bonus/philo_bonus

#HEADERS
INCL_DIR = philo/includes
INCL = $(wildcard $(INCL_DIR)/*.h)
#HEADERS BONUS
INCL_DIR_BONUS = philo_bonus/includes_bonus
INCL_BONUS = $(wildcard $(INCL_DIR_BONUS)/*.h)

#SOURCES
SRC_DIR = philo/sources
SRC = $(wildcard $(SRC_DIR)/*.c)
#SOURCES BONUS
SRC_DIR_BONUS = philo_bonus/sources_bonus
SRC_BONUS = $(wildcard $(SRC_DIR_BONUS)/*.c)

# OBJECTS
OBJ_DIR = philo/objects
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
# OBJECTS BONUS
OBJ_DIR_BONUS = philo_bonus/objects_bonus
OBJ_BONUS = $(patsubst $(SRC_DIR_BONUS)/%.c,$(OBJ_DIR_BONUS)/%.o,$(SRC_BONUS))

CC = gcc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

all:	${NAME}

bonus: 	${BONUS}
		 
${NAME}:	$(OBJ_DIR) ${OBJ}
		${CC} ${FLAGS} ${OBJ} -lpthread -o ${NAME}

${BONUS}:	$(OBJ_DIR_BONUS) ${OBJ_BONUS}
		${CC} ${FLAGS} ${OBJ_BONUS} -lpthread -o ${BONUS}

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR_BONUS):
		@mkdir -p $(OBJ_DIR_BONUS)
		
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCL)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c $(INCL_BONUS)
	$(CC) $(CFLAGS) -I$(INCL_DIR_BONUS) -c $< -o $@

clean:	
		@rm -f ${OBJ}
		@rm -f ${OBJ_BONUS}

fclean:	clean
		@rm -f ${NAME}
		@rm -f ${BONUS}
		@rm -rf $(OBJ_DIR)
		@rm -rf $(OBJ_DIR_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus