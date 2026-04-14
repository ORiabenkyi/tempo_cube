MLX_DIR	= libs/MLX42
MLX_LIB	= $(MLX_DIR)/build/libmlx42.a

LIBFT_DIR = libs/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

BONUS_DIR  = bonus
BONUS_NAME = cub3d_bonus

INC		 = -I./libs/libft/ -I./inc -I./libs/MLX42/include

NAME	 = cub3d
CC		 = cc
CFLAGS	 = -Wall -Wextra -Werror -g3
MLXFLAGS = -ldl -lglfw -pthread -lm
RM		 = rm -rf

CFILES =	src/cube3d.c \
			src/parse/parse.c \
			src/parse/check_extension.c \
			src/parse/parse_io.c \
			src/parse/parse_header.c \
			src/parse/parse_feel_1u.c \
			src/parse/parse_feel_2u.c \
			src/parse/validate_map.c \
			src/parse/parse_grid.c \
			src/parse/parse_utils.c \
			src/game/game_init.c \
			src/game/cleanup.c \
			src/game/init_player.c \
			src/game/game_loop.c \
			src/game/can_move.c \
			src/game/handle_keys.c \
			src/game/raycast.c \
			src/game/init_ray.c \
			src/game/dda.c \
			src/game/calc_wall.c \
			src/game/move.c \
			src/game/find_door.c \
			src/game/interact_door.c \
			src/game/update_doors.c \
	        src/game/player_in_door.c \
			src/game/minimap.c \
			src/game/minimap_utils.c \
			src/game/draw_info_line.c \
			src/game/player_info.c

OFILES = $(CFILES:.c=.o)

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME) 

# -----------------------
# take from codam MLX42 repo
# -----------------------
$(MLX_LIB):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) || true
	cmake -B $(MLX_DIR)/build $(MLX_DIR)
	cmake --build $(MLX_DIR)/build -j4

# -----------------------
# Create libft part of the project
# -----------------------	
$(LIBFT_LIB):
	git clone git@github.com:ORiabenkyi/codam-libft.git $(LIBFT_DIR) || true
	make -C $(LIBFT_DIR)	
# -----------------------
# Create main part of the project
# -----------------------
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(BOBUS_FLAG) $(OFILES) $(LIBFT_LIB) $(MLX_LIB) $(MLXFLAGS) -o $(NAME)

mlx: $(MLX_LIB)

bonus:
	$(MAKE) -C $(BONUS_DIR)
	cp $(BONUS_DIR)/$(BONUS_NAME) .

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	$(RM) $(MLX_DIR)
	$(RM) $(LIBFT_DIR)
	$(MAKE) -C $(BONUS_DIR) fclean

re: fclean all

full: fclean all