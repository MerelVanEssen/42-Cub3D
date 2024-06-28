NAME = cub3D
NAME_BONUS = cub3D_bonus

LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FULL = $(LIBFT_DIR)/$(LIBFT)

LIBMLX = libmlx42.a
MLX_DIR = MLX42
MLX_FULL = $(MLX_DIR)/build/$(LIBMLX)

HEADERS	:= -I $(MLX_DIR)/include/MLX42 -I $(LIBFT_DIR)
LIBS	:= $(LIBFT_FULL) $(MLX_FULL) -ldl -lglfw -pthread -lm

OBJ_DIR = obj
SRC_DIRS = src src/parser

SOURCES = main.c game.c math.c keys.c \
		  file_parsing.c map_attributes.c map_parsing.c parser_utils.c \
		  player_init.c validators.c

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

# bonus
BONUS_OBJ_DIR = bonus/obj
BONUS_DIRS = bonus/src bonus/src/parser bonus/src/sprites

ifeq ($(MAKECMDGOALS), bonus)
	vpath %.c $(BONUS_DIRS)
	vpath %.h $(BONUS_DIRS) $(LIBFT_DIR) $(MLX_DIR)
else
	vpath %.c $(SRC_DIRS)
	vpath %.h $(SRC_DIRS) $(LIBFT_DIR) $(MLX_DIR)
endif

BONUS_SOURCES = main.c game.c math.c minimap.c keys.c utils.c doors.c\
		  		file_parsing.c map_attributes.c map_parsing.c parser_utils.c \
		  		player_init.c validators.c validation_bonus.c keys_bonus.c \
				sprites_draw.c sprites_init.c sprites_sort.c sprites_textures.c \
				delete.c color.c
BONUS_OBJECTS = $(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_SOURCES:.c=.o))

CFLAGS += -Wall -Wextra -Werror -Ofast

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT_FULL):
	make -C $(LIBFT_DIR)

$(MLX_FULL):
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(NAME): $(OBJECTS) $(LIBFT_FULL) $(MLX_FULL)
	cc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS) $(HEADERS)

bonus: $(NAME_BONUS)

$(BONUS_OBJ_DIR)/%.o: %.c
	@mkdir -p $(BONUS_OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME_BONUS): $(BONUS_OBJECTS) $(LIBFT_FULL) $(MLX_FULL)
	cc $(CFLAGS) -o $(NAME_BONUS) $(BONUS_OBJECTS) $(LIBS) $(HEADERS)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BONUS_OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	# make fclean -C $(LIBFT_DIR)
	# rm -rf $(MLX_DIR)/build

re: fclean all

.PHONY: all clean fclean re bonus
