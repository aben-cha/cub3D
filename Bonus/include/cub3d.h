#ifndef CUB3D_H
#define CUB3D_H

#include "const_and_struct.h"

void	mouse(void *param);
void load_images(t_data *data);
void ft_wait_move_animation(void  *d);
void ft_load_move_animation(void *d);
void ft_shoot_move_animation(void *d);

void	ft_rays_where_is_facing(t_ray *ray, float rayangle);

void ft_player(t_data *data);
void init_data(t_data   *data,t_map *map, t_player *player);
void    draw_circle(t_data *data,int color);
int ft_check_wall(t_data *data, float x,float y);
void ft_update_env(void  *d);
int ft_update_position_player(t_data *data);
void rest_image(mlx_image_t *image);
void	draw_line(t_data *data, t_pos *p1, t_pos *p2, int color);
void    ft_map(t_data *data);
void    ft_cast_all_rays(t_data *data);

void    ft_minimap(t_data *data);
float ft_normalizeangle(float rayangle);
void	ft_which_ray_used(t_data *data, t_ray *ver, t_ray *hor, int i);
int	ft_find_wall_vertical(t_data *data, t_pos *new, t_pos *step, t_ray *ray);
int	ft_find_wall_horizontal(t_data *data, t_pos *new, t_pos *step, t_ray *ray);
t_ray	ft_rays_horizontal(t_data *data, t_ray *ray, float rangle);
t_ray	ft_rays_vertical(t_data *data, t_ray *ray, float rangle);

void ft_projection3d(t_data *data, float x, int sig, t_ray *ray);
int    ft_color(int r, int g, int b, int a);
void	ft_floor(t_data *data, int x, int start_y);
void	ft_ceil(t_data *data, int x, int end_y);
uint32_t	get_pixel_color(mlx_texture_t *texture, int x, int y);
void	ft_set_texteur(t_data *data, float wallheight, t_pos *t1, int offset_x);
int ft_check_wall_intersection(t_data *data ,float x, float y);
float	ft_init_wallheight(t_data *data, float raydistance);
mlx_texture_t	*ft_texteur_valid(t_data *data);
int	ft_init_offset(t_ray *ray, int sig);
void	ft_prepare_projection(t_data *data, float x, float raydis, t_pos *t1);
void	ft_draw_projection(t_data *data, t_pos t1, int sig, t_ray *ray);
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