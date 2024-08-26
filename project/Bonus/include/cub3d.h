#ifndef CUB3D_H
#define CUB3D_H

#include "const_and_struct.h"

void load_images(t_data *data);
void ft_wait_move_animation(void  *d);



void ft_shoot_move_animation(t_data *data);

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
void    set_map(t_list *ptr, t_data *data);
int     position_of_player(t_data *data);
int     is_valid_Map(t_data * data);

//get-element.c
int     set_color(t_color *color, char *color_path);
void    set_element(t_data *data, char *s, int *size, char c);
void    get_element(t_data *data, char *s, int *size, int *i);
int     get_color(t_element *element, char *color, char type);
void    setup_textures_colors(t_data *data);
t_list  *get_map(t_data *data);

//free_data.c
void    free_array(char **array);
void    print_error(char *str);
void    free_data(t_data *data, int flag);


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