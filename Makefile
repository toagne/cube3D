# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 09:05:38 by mpellegr          #+#    #+#              #
#    Updated: 2024/12/11 16:33:12 by mpellegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = cub3D
SRC_DIR         = src
INC_DIR         = inc
MLX42_DIR		= ./MLX42
LIBFT_DIR		= ./libft

SRC             = $(SRC_DIR)/main.c $(SRC_DIR)/init.c $(SRC_DIR)/keyboard.c $(SRC_DIR)/read_map.c $(SRC_DIR)/validate_map.c $(SRC_DIR)/error.c \
					$(SRC_DIR)/load_images.c $(SRC_DIR)/utils.c $(SRC_DIR)/read_file.c $(SRC_DIR)/free.c \
					$(SRC_DIR)/minimap.c $(SRC_DIR)/raycasting.c $(SRC_DIR)/player_texture.c \
					$(SRC_DIR)/sprites.c $(SRC_DIR)/drawing_utils.c $(SRC_DIR)/walls_check.c \
					$(SRC_DIR)/walls_texture.c $(SRC_DIR)/sprites_utils.c $(SRC_DIR)/mainmenu.c \
					$(SRC_DIR)/create_doors.c $(SRC_DIR)/game_state_images.c $(SRC_DIR)/mouse.c \
					$(SRC_DIR)/movement.c $(SRC_DIR)/collisions.c $(SRC_DIR)/kill_sprite.c  \
					$(SRC_DIR)/utils_1.c
OBJ_DIR         = obj
OBJ             = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MLX42_LIB       = $(MLX42_DIR)/build/libmlx42.a
LIBFT           = $(LIBFT_DIR)/libft.a

RM              = rm -f
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Wunreachable-code -g\
					-I$(INC_DIR) \
					-I$(MLX42_DIR)/include
LDFLAGS         = -ldl -lglfw -pthread -lm

all:	$(LIBFT) $(MLX42_LIB) $(NAME)

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
			cmake ..; \
		fi && \
		cmake --build .

#for macOS add -D CMAKE_OSX_ARCHITECTURES=(check uname -m) after cmake ..

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42_LIB) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re