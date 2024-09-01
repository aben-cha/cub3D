#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h> /////
#include "../src/libft/libft.h"
#include "../src/get_next_line/get_next_line.h"

#include "MLX42.h"
#define NUM_IMAGES_WAIT 6
#define NUM_IMAGES_SHOT 14
#define NUM_IMAGES_LOAD 37
#define NUM_IMAGES_VIEW 67
// #define TILE_SIZE 64//
#define TILE_MAP 250
#define TILE_SIZE 1024// 32 tile size just fo map
#define NBR_RAYS 1500
#define WINDOW_WHIDTH 1500 ///
#define WINDOW_HEIGHT 900 ///
#define FOV_ANGLE (60 * (M_PI / 180))

/// ////
typedef struct s_player
{
    float  x;
    float  y;
    int  radius;
    char isFacing;
    int  view_player;
    int     turnDirection;
    int     walkDirection;
    float   rotationAngle;
    float   moveSpeed;
    mlx_image_t *img_player;
    // uint32_t *walltexteur;
    float rotationSpeed;

}   t_player;

typedef struct s_animaction
{
    mlx_image_t *image;
    int current_frame;
    int frame_delay;
    int delay_counter;
    mlx_texture_t *textures_wait[NUM_IMAGES_WAIT];
    mlx_texture_t *textures_shot[NUM_IMAGES_SHOT];
    mlx_texture_t *textures_load[NUM_IMAGES_LOAD];
    mlx_texture_t *textures_view[NUM_IMAGES_VIEW];

}   t_animation;

typedef struct s_texture
{
    char *north_texture;
    char *south_texture;
    char *east_texture;
    char *west_texture;
    mlx_texture_t*walltexteur_n; //// 
    mlx_texture_t*walltexteur_s; //// 
    mlx_texture_t*walltexteur_w; //// 
    mlx_texture_t*walltexteur_e; //// 
}           t_texture;


typedef struct s_map
{
    // int fd;
    int width;
    int height;
    mlx_image_t *img_map;
    char **arr_map;
    // char        **map;
}   t_map;
typedef struct s_color
{
    int red;
    int green;
    int blue;
}           t_color;

typedef struct s_element
{
    char    *color_path;
    t_color floor_color;
    t_color ceiling_color;
}           t_element;

typedef struct s_ray
{
    float  dx;
    float  dy;
    float   x_intercept;
    float   y_intercept;
    bool    ray_is_up;
    bool    ray_is_down;
    bool    ray_is_left;
    bool    ray_is_right;
    float   ray_angle;
}   t_ray;

typedef struct s_data
{
    int		    j;
    int 	    i;
    int		    size;
    int         fd;
    char        *string;
    t_texture   *texture;
    t_list      *texturel;
    t_list      *list;
    t_element   element;
    mlx_t   *mlx;
    t_map *map;
    t_animation *animation;//
    t_player *player;
    t_ray   *ray;
}   t_data;

typedef struct s_con_var
{
	uint8_t		*pixels;
	uint32_t	i;
	uint8_t		a;
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;

} t_con_var;

void load_images_texteurs(t_data *data);
void load_images(t_data *data);
void ft_wait_move_animation(void  *d);





int    ft_color(int r, int g, int b, int a);
void ft_player(t_data *data);
void init_data(t_data   *data,t_map *map, t_player *player);
void    draw_circle(t_data *data,int color);
int ft_check_wall(t_data *data, float x,float y);
void ft_update_env(void  *d);
int ft_update_position_player(t_data *data);
void rest_image(mlx_image_t *image);
void draw_line(t_data *data, float x0, float y0, float x1, float y1, int color);
void    ft_map(t_data *data);
void    draw_rect(t_data *data,float size_x,float size_y , int color);
void    ft_cast_all_rays(t_data *data,int color);

void    ft_minimap(t_data *data);
float ft_normalizeangle(float rayangle);
t_ray ft_rays_horizontal(t_data *data, t_ray *ray,float ray_angle);
t_ray ft_rays_vertical(t_data *data, t_ray *ray, float ray_angle);
float  ft_intrecetion(t_data *data, float rayangle,int color);
///part test 
void rays(t_data *data, float ray_angle,int color);////

void    ft_projection3D(t_data *data,float d,int sig , t_ray *ray, float raydistance);
int ft_check_wall_intersection(t_data *data ,float x , float y);
// void ft_rays_horizontal(t_data *data, float ray_angle);

//minimap  
void view_player(t_data *data, int color);
void    ft_direction_map(t_data *data);
void    ft_border_map(t_data *data);

// void draw_wall(t_data *data, int x, int y, int width, int height, double raydistance);


//first_parse.c
void    inite_data_player(t_data *data);
void    read_data(int *fd, char *av);
void    fill_list(t_data *data, char *av);
int     check_char(char *s);
int     element_exist(t_list *head, char *d);
int     all_element_exist(t_data *data);

//check_map.c
int     map(t_list *ptr, t_data *data);
int     set_map(t_list *ptr, t_data *data, int end);
int     position_of_player(t_data *data);
int     is_valid_map(t_data * data);

//get-element.c
int     set_color(t_color *color, char *color_path, int i);
void    set_element(t_data *data, char *s, int *size, char c);
void    get_element(t_data *data, char *s, int *size, int *i);
int     get_color(t_element *element, char *color, char type);
// void    setup_textures_colors(t_data *data);
void    setup_colors(t_data *data);
t_list  *get_map(t_data *data);

//free_data.c
void    free_array(char **array);
void    print_error(char *str);
void    free_data(t_data *data, int flag);
void    free_structs(t_data *data);

//utils.c
void    handle_space(char *s, int *i, int *j);
int     check_wall(char *s, char c);
int     another_char(char *s, char *ptr);
int     is_adjacent(t_data *data, char **map, char space, char c);

//linked_list.c
t_list	*ft_lstnew(void *content, char c);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
int     ft_lstsize(t_list *lst);

#endif