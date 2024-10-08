/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:23:02 by aben-cha          #+#    #+#             */
/*   Updated: 2024/09/10 15:08:01 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "const_and_struct.h"

void			parsing(t_data *data, char *av);
void			ft_cub3d(t_data *data);
int				ft_check_wall_intersection(t_data *data, float px, float py);
int				ft_check_wall(t_data *data, float x, float y);
int				ft_update_position_player(t_data *data);
void			ft_player(t_data *data);
void			convert_abgr_to_rgba(t_data *data, mlx_texture_t *texture);
int				load_png(t_data *data, mlx_texture_t **mlx_texture, char *path,
					char c);
void			load_textures(t_data *data, t_list *head);
int				ft_init_offset(t_data *data, t_ray *ray, int sig);
void			ft_prepare_projection(t_data *data, float x, float raydis,
					t_pos *t1);
void			ft_draw_projection(t_data *data, t_pos t1, int sig, t_ray *ray);
void			ft_projection3d(t_data *data, float x, int sig, t_ray *ray);
void			ft_cast_all_rays(t_data *data);
float			ft_normalizeangle(float rayangle);
t_ray			ft_rays_horizontal(t_data *data, t_ray *ray, float rangle);
t_ray			ft_rays_vertical(t_data *data, t_ray *ray, float rangle);
void			key_release(t_data *data);
void			wasd_keys(t_data *data);
void			left_right_keys(t_data *data);
void			ft_update_env(void *d);
void			rest_image(mlx_image_t *image);
int				ft_check_arr(t_data *data, t_pos *p1, t_pos *point);
int				ft_color(int r, int g, int b, int a);
void			ft_floor(t_data *data, int x, int start_y);
void			ft_ceil(t_data *data, int x, int end_y);
uint32_t		get_pixel_color(mlx_texture_t *texture, int x, int y);
void			ft_rays_where_is_facing(t_ray *ray, float rayangle);
void			ft_which_ray_used(t_data *data, t_ray *ver, t_ray *hor, int i);
void			ft_find_wall_ver(t_data *data, t_pos *new, t_pos *step,
					t_ray *ray);
void			ft_find_wall_hor(t_data *data, t_pos *new, t_pos *step,
					t_ray *ray);
void			ft_set_texteur(t_data *data, float wallheight, t_pos *t1,
					int offset_x);
float			ft_init_wallheight(t_data *data, float raydistance);
mlx_texture_t	*ft_texteur_valid(t_data *data);
int				map(t_list *ptr, t_data *data);
void			allocate_new_map(t_data *data);
void			join_space(t_data *data, int size, int *i);
int				set_map(t_list *ptr, t_data *data, int size);
int				is_valid_map(t_data *data);
void			read_data(int *fd, char *av);
void			fill_list(t_data *data, char *av);
int				check_char(char *s);
int				element_exist(t_list *head, char *d);
int				all_element_exist(t_data *data);
void			free_array(char **array);
void			free_structs(t_data *data);
void			print_error(char *str);
void			free_data(t_data *data, int flag);
void			free_data_mlx(t_data *data, int flag);
int				set_color(t_color *color, char *color_path, int i);
void			get_element(t_data *data, char *s, int *size);
int				get_color(t_element *element, char *color, char type);
void			setup_colors(t_data *data);
t_list			*get_map(t_data *data);
void			init_variables(t_data *data);
void			data_init(t_data *data);
int				position_of_player(t_data *data, char **map);
void			init_data_player(t_data *data);
t_list			*ft_lstnew(void *content, char c);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst);
int				ft_lstsize(t_list *lst);
void			handle_space(char *s, int *i, int *j);
int				check_wall(char *s, char c);
int				another_char(char *s, char *ptr);
int				is_adjacent(t_data *data, char **map);
void			set_element(t_data *data, char *s, int *size, char c);

#endif