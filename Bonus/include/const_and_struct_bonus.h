#ifndef CONST_AND_STRUCT_BONUS_H
#define CONST_AND_STRUCT_BONUS_H


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h> /////
#include "../src/libft/libft.h"
#include "../src/get_next_line/get_next_line.h"
#include "MLX42.h"

#define N_IMAGES_WAIT 6
#define N_IMAGES_SHOT 14
#define N_IMAGES_LOAD 37
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
    char isfacing;
    double  view_player;
    int     turndir;
    int     walkdirection;
    float   rotangle;
    float   movespeed;
    float   rotspeed;
    mlx_image_t *img_player;

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
    int frame_delay_load;
    int delay_counter_load;
    mlx_texture_t *textures_wait[N_IMAGES_WAIT];
    mlx_texture_t *textures_shot[N_IMAGES_SHOT];
    mlx_texture_t *textures_load[N_IMAGES_LOAD];
    mlx_texture_t *textures_view[NUM_IMAGES_VIEW];

}   t_animation;

typedef struct s_texture
{
    mlx_texture_t   *walltexteur_n; //// 
    mlx_texture_t   *walltexteur_s; //// 
    mlx_texture_t   *walltexteur_w; //// 
    mlx_texture_t   *walltexteur_e; //// 
    mlx_texture_t   *walltexteur_d; //// 
}           t_texture;


typedef struct s_map
{
    int width;
    int height;
    mlx_image_t *img_map;
    char **arr_map;
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
    float       rayangle;
    int         flagdoor;
    int         n;
    float   distance;
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
    int store_x;
    int counter;
    int key_hand;
}   t_data;

typedef struct s_position
{
    float   x;
    float   y;
}   t_pos;

typedef struct s_con_var
{
	uint8_t		*pixels;
	uint32_t	i;
	uint8_t		a;
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;

} t_con_var;

#endif