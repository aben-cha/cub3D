#ifndef CONST_AND_STRUCT_H
#define CONST_AND_STRUCT_H


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
#define TILE_SIZE 1024//
#define TILE_SIZE_MAP 32// 32 tile size just fo map
#define TILE_MAP 250
#define NBR_RAYS 1500
#define WINDOW_WHIDTH 1500
#define WINDOW_HEIGHT 900
#define FOV_ANGLE (60 * (M_PI / 180))

typedef struct s_player
{
    float  x;
    float  y;
    int  radius;
    char isFacing;
    double  view_player;
    int     turnDirection;
    int     walkDirection;
    float   rotationAngle;
    float   moveSpeed;
    mlx_image_t *img_player;
    mlx_texture_t*walltexteur_n; //// 
    mlx_texture_t*walltexteur_s; //// 
    mlx_texture_t*walltexteur_w; //// 
    mlx_texture_t*walltexteur_e; //// 
    mlx_texture_t*walltexteur_d; //// 
    float rotationSpeed;

}   t_player;

typedef struct s_animaction
{
    mlx_image_t *image;
    int current_frame_wait;
    int frame_delay_wait;
    int delay_counter_wait;
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
    int     flag;
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
    float       x_door;
    float       y_door;
    t_texture   *texture;
    t_list      *texturel;
    t_list      *list;
    t_element   element;
    mlx_t   *mlx;
    t_map *map;
    t_animation *animation;//
    t_player *player;
    t_ray   *ray;
    int store_x;
}   t_data;




#endif