# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 09:05:38 by mpellegr          #+#    #+#              #
#    Updated: 2024/11/14 09:56:02 by omartela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = cub3D
SRC_DIR         = src
INC_DIR         = inc
MLX42_DIR		= ./MLX42
LIBFT_DIR		= ./libft

SRC             = $(SRC_DIR)/main.c $(SRC_DIR)/init.c $(SRC_DIR)/keyboard.c $(SRC_DIR)/read_map.c
OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MLX42_LIB       = $(MLX42_DIR)/build/libmlx42.a

RM              = rm -f
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Wunreachable-code -g \
					-I$(INC_DIR) \
					-I$(MLX42_DIR)/include
LDFLAGS         = -ldl -lglfw -pthread -lm

all:	$(MLX42_LIB) $(NAME)

$(MLX42_LIB):
	@if [ ! -d $(MLX42_DIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git \
		$(MLX42_DIR); \
	fi
	@if [ ! -d "$(MLX42_DIR)/build" ]; then \
		mkdir -p $(MLX42_DIR)/build; \
	fi
	@cd $(MLX42_DIR)/build && \
		if [ ! -f CMakeCache.txt ]; then \
			cmake .. -D CMAKE_OSX_ARCHITECTURES=arm64; \
		fi && \
		cmake --build .

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42_LIB) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
