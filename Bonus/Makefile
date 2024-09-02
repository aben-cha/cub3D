CC = cc 
NAME = cub3D_bonus
MLX = libmlx42.a
CFLAGS = -g -fsanitize=address  -g -O2#-Wall -Wextra -Werror  -g -O2
CFLAGS += -Ofast
LDFLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib" -L. -lmlx42 -framework OpenGL -framework AppKit
RM = rm -f
OBJ_DIR = obj
SRC_DIR = src
SRC = $(SRC_DIR)/main_bonus.c $(SRC_DIR)/ft_player_bonus.c $(SRC_DIR)/draw_env_bonus.c $(SRC_DIR)/update_env_bonus.c $(SRC_DIR)/ft_map_bonus.c $(SRC_DIR)/raycasting_bonus.c $(SRC_DIR)/projection3d_bonus.c $(SRC_DIR)/utils_raycasting_bonus.c  $(SRC_DIR)/utils_projection3d_bonus.c $(SRC_DIR)/utils1_projection3d_bonus.c \
	  $(SRC_DIR)/animation_bonus.c $(SRC_DIR)/load_png_bonus.c \
      $(SRC_DIR)/parse/first_parse_bonus.c $(SRC_DIR)/parse/check_map_bonus.c $(SRC_DIR)/parse/get_elements_bonus.c $(SRC_DIR)/parse/free_data_bonus.c $(SRC_DIR)/parse/utils_bonus.c \
      $(SRC_DIR)/get_next_line/get_next_line.c $(SRC_DIR)/get_next_line/get_next_line_utils.c $(SRC_DIR)/parse/linked_list_bonus.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:$(SRC_DIR)/%.c=%.o))
LIBFT = src/libft/libft.a

all: $(NAME) 

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC)  $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(LIBFT)
$(LIBFT):
	@$(MAKE) -C src/libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)/subdirs
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	$(cd src/libft && make)
	
$(OBJ_DIR)/subdirs:
	@mkdir -p $(OBJ_DIR)/src/parse
	@mkdir -p $(OBJ_DIR)/src/get_next_line
clean:
	$(RM) -r $(OBJ_DIR)
	@(cd src/libft && make clean)

fclean: clean
	$(RM) $(NAME)
	@(cd src/libft && make fclean)

re: fclean all
