/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:40:17 by jecolmou          #+#    #+#             */
/*   Updated: 2022/07/01 19:49:02 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
# define MLX_ERROR 1

//////////STRUCTURE//////////

typedef struct s_map		t_map;

struct s_map
{
	char	*x;
	int		garbage;
	int		is_good;
	t_map	*next;
};

typedef struct s_coor		t_coor;

struct	s_coor
{
	int	x;
	int	y;
};

typedef struct s_player		t_player;

struct	s_player
{
	int		dir;
	t_coor	coord;
};

typedef struct s_data		t_data;

struct	s_data
{
	int			file;
	char		*str;
	int			len;
	int			len_x;
	int			len_y;
	int			count_p;
	int			count_e;
	int			count_c;
	t_map		*map;
	void		*texture[5];
	void		*mlx_ptr;
	void		*win_ptr;
	char		**dtab;
	int			item_count;
	t_player	player;
	int			move_count;
	int			pos[2];
	int			ri;
};

enum	e_axis
{
	X,
	Y,
};

enum	e_texture
{
	WALL,
	GROUND,
	EXIT,
	CHARAC,
	COLLECTIBLE,
};

typedef struct s_key_value	t_key_value;

struct s_key_value
{
	char const				c;
	enum e_texture const	index;
	int const				offset[2];
};

static t_key_value const	g_lookup[] = {
{'1', WALL, {0, 0}},
{'0', GROUND, {0, 0}},
{'E', EXIT, {0, 64}},
{'P', CHARAC, {0, 0}},
{'C', COLLECTIBLE, {0, 0}},
{'J', -1, {0, 0}},
};

//////////LINKED LISTS//////////
t_map	*ft_add_back(t_map *a_list, char *value);
int		ft_lstsize(t_map **lst);
void	ft_lstclear(t_map **tab);

//////////GET_NEXT_LINE//////////
int		ft_strlen_gnl(char *str);
int		ft_read_buffer(int fd, char *buf);
int		ft_is_a_line(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_next_line(int fd, int reset);
char	*ft_read_text(int fd, char *final);
char	*ft_extract_line(char *s1);
char	*ft_save_line(char *str);

//////////PARSING//////////
int		ft_check_args(int argc, char **argv);
int		ft_open_map(char **argv, t_data *x);
int		ft_read_infile(char *infile);
int		ft_return_count_p(t_data *x);
int		ft_return_count_e(t_data *x);
int		ft_return_count_c(t_data *x);
int		ft_check(t_map **liste);
int		ft_check_doublons_p(t_map **liste);
int		ft_parsing_map_e(t_map **tab, t_data *x, char *c);
int		ft_parsing_map_p(t_map **map, t_data *x, char *c);
int		ft_parsing_map_c(t_map **tab, t_data *x, char *c);
int		ft_is_rectangle(t_map **tab);
int		ft_is_wall_first(t_map **first);
int		ft_is_wall_last(t_map **tab);
int		ft_is_wall_first_case(t_map **tab);
int		ft_is_wall_last_case(t_map **tab);
int		ft_execution_parsing_items(t_map **tab, t_data *x);
int		ft_execution_rectangle(t_map **tab);
int		ft_execution_wall(t_map **tab);
int		ft_open_file(char	**argv, t_data *x);

//////////SO_LONG//////////
void	ft_free_args(char	**args);
int		render(t_data *data);
void	display_map(t_data *data, int i, int j);
int		ft_get_images(t_data *data);
int		ft_get_images_annex(t_data *data, int height, int width);
t_data	*create(t_data *data);
void	ft_len_x(t_map **map, t_data *data);
void	ft_len_y(t_map **map, t_data *data);
void	ft_len_xy(t_map **tab, t_data *x);
int		ft_convert_in_char(t_map **tab, t_data *data);
void	ft_index(t_data *x);
void	player_move(t_data *world, int dir, int y, int x);
int		ft_exit_game(t_data *data);
int		ft_un_alloc(t_data *data);
int		is_accessible(t_data *data, char c, int x, int y);
int		deal_key(int key, t_data *data);
int		refresh(t_data *data);
void	ft_elsif_key_a(t_data *data);
void	ft_elsif_key_s(t_data *data);
void	ft_elsif_key_d(t_data *data);
void	ft_elsif_key_w(t_data *data);
void	ft_display_move(t_data *data);

#endif
