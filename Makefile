# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junylee <junylee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/15 14:44:26 by junylee           #+#    #+#              #
#    Updated: 2021/09/26 18:08:56 by junylee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================================================================
# Command Variables
# =============================================================================

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror
NAME				= pipex
RM					= rm -f

# =============================================================================
# File Variables
# =============================================================================

HEADER				= ./includes/
FOLDER				= ./srcs/
D_UT				= utils/

SHARED_SRC_LIST 	= $(D_UT)ft_split.c\
					  $(D_UT)ft_strdup.c\
					  $(D_UT)ft_strjoin.c\
					  $(D_UT)ft_strlen.c\
					  $(D_UT)ft_strncmp.c\
					  $(D_UT)ft_memset.c\
					  check.c\
					  excute.c\

SOURCES				= $(addprefix $(FOLDER), pipex.c)
BONUS				= $(addprefix $(FOLDER), pipex_bonus.c)
SHARED				= $(addprefix $(FOLDER), $(SHARED_SRC_LIST))

SRC_OBJECTS			= ${SOURCES:.c=.o}
BONUS_OBJECTS 		= ${BONUS:.c=.o}
SHARED_OBJECTS		= ${SHARED:.c=.o}

# =============================================================================
# Target Generating
# =============================================================================

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -I $(HEADER) -c $< -o $@

$(NAME): ${SRC_OBJECTS} ${SHARED_OBJECTS}
		${CC} ${CFLAGS} -I $(HEADER) -o $(NAME) ${SRC_OBJECTS} ${SHARED_OBJECTS}

bonus : ${BONUS_OBJECTS} ${SHARED_OBJECTS}
		${CC} ${CFLAGS} -I $(HEADER) -o $(NAME) ${BONUS_OBJECTS} ${SHARED_OBJECTS}

clean:
	${RM} ${SRC_OBJECTS} ${BONUS_OBJECTS} ${SHARED_OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re bonus
