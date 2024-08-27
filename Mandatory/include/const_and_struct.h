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

#define WIDTH_TEXTUER 1024
#define HEIGHT_TEXTUER 1024
#define TILE_SIZE 1024
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
    float rotationSpeed;

}   t_player;

typedef struct s_texture
{
    char    *north_texture;
    char    *south_texture;
    char    *east_texture;
    char    *west_texture;
    mlx_texture_t   *walltexteur_n; //// 
    mlx_texture_t   *walltexteur_s; //// 
    mlx_texture_t   *walltexteur_w; //// 
    mlx_texture_t   *walltexteur_e; //// 
}           t_texture;

typedef struct s_map
{
    int width;
    int height;
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

#endif