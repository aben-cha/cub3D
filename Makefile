CC = cc
NAME = cub3D
NAMEB = cub3D_bonus
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Ofast
LDFLAGS = -lglfw -lmlx42
RM = rm -f
SRC_DIR_MANDATORY = Mandatory/src
SRC_DIR_BONUS = Bonus/src

SRC = $(SRC_DIR_MANDATORY)/cub3D.c \
	  $(SRC_DIR_MANDATORY)/ft_player.c \
	  $(SRC_DIR_MANDATORY)/utils_player.c \
	  $(SRC_DIR_MANDATORY)/update_env.c \
	  $(SRC_DIR_MANDATORY)/raycasting.c \
	  $(SRC_DIR_MANDATORY)/load_textures.c \
	  $(SRC_DIR_MANDATORY)/utils_raycasting.c \
	  $(SRC_DIR_MANDATORY)/projection3d.c \
	  $(SRC_DIR_MANDATORY)/utils_projection3d.c \
	  $(SRC_DIR_MANDATORY)/utils1_projection3d.c \
	  $(SRC_DIR_MANDATORY)/parse/first_parse.c \
	  $(SRC_DIR_MANDATORY)/parse/check_map.c \
	  $(SRC_DIR_MANDATORY)/parse/get_elements.c \
	  $(SRC_DIR_MANDATORY)/parse/free_data.c \
	  $(SRC_DIR_MANDATORY)/parse/utils.c \
	  $(SRC_DIR_MANDATORY)/parse/init_data.c \
	  $(SRC_DIR_MANDATORY)/get_next_line/get_next_line.c \
	  $(SRC_DIR_MANDATORY)/get_next_line/get_next_line_utils.c \
	  $(SRC_DIR_MANDATORY)/parse/linked_list.c

BONUS = $(SRC_DIR_BONUS)/cub3D_bonus.c \
		$(SRC_DIR_BONUS)/ft_player_bonus.c \
		$(SRC_DIR_BONUS)/draw_env_bonus.c \
		$(SRC_DIR_BONUS)/update_env_bonus.c \
		$(SRC_DIR_BONUS)/ft_map_bonus.c \
		$(SRC_DIR_BONUS)/raycasting_bonus.c \
		$(SRC_DIR_BONUS)/projection3d_bonus.c \
		$(SRC_DIR_BONUS)/utils_raycasting_bonus.c \
		$(SRC_DIR_BONUS)/utils_projection3d_bonus.c \
		$(SRC_DIR_BONUS)/utils1_projection3d_bonus.c \
		$(SRC_DIR_BONUS)/animation_bonus.c \
		$(SRC_DIR_BONUS)/load_png_bonus.c \
		$(SRC_DIR_BONUS)/load_textures_bonus.c \
		$(SRC_DIR_BONUS)/parse/first_parse_bonus.c \
		$(SRC_DIR_BONUS)/parse/check_map_bonus.c \
		$(SRC_DIR_BONUS)/parse/get_elements_bonus.c \
		$(SRC_DIR_BONUS)/parse/free_data_bonus.c \
		$(SRC_DIR_BONUS)/parse/utils_bonus.c \
		$(SRC_DIR_BONUS)/get_next_line/get_next_line.c \
		$(SRC_DIR_BONUS)/get_next_line/get_next_line_utils.c \
		$(SRC_DIR_BONUS)/parse/linked_list_bonus.c \
		$(SRC_DIR_BONUS)/parse/init_data_bonus.c

LIBFT = $(SRC_DIR_MANDATORY)/libft/libft.a
LIBFTB = $(SRC_DIR_BONUS)/libft/libft.a

OBJ_MANDATORY = $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_MANDATORY) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_MANDATORY) $(LIBFT) -o $(NAME) $(LDFLAGS)

bonus: $(OBJ_BONUS) $(LIBFTB)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFTB) -o $(NAMEB) $(LDFLAGS)

$(LIBFT): $(SRC_DIR_MANDATORY)/libft/libft.h
	$(MAKE) -C $(SRC_DIR_MANDATORY)/libft

$(LIBFTB): $(SRC_DIR_BONUS)/libft/libft.h
	$(MAKE) -C $(SRC_DIR_BONUS)/libft

$(SRC_DIR_MANDATORY)/%.o: $(SRC_DIR_MANDATORY)/%.c Mandatory/include/cub3d.h Mandatory/include/const_and_struct.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c Bonus/include/cub3d_bonus.h Bonus/include/const_and_struct_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_MANDATORY) $(OBJ_BONUS)
	$(MAKE) -C $(SRC_DIR_MANDATORY)/libft clean
	$(MAKE) -C $(SRC_DIR_BONUS)/libft clean

fclean: clean
	$(RM) $(NAME) $(NAMEB)
	$(MAKE) -C $(SRC_DIR_MANDATORY)/libft fclean
	$(MAKE) -C $(SRC_DIR_BONUS)/libft fclean

re: fclean all
