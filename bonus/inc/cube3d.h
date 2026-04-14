/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oriabenk <oriabenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:53:52 by oriabenk          #+#    #+#             */
/*   Updated: 2026/04/12 16:37:10 by oriabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../libs/libft/libft.h"
# include "MLX42/MLX42.h"

/* ---------- Window ---------- */
# define SCREEN_W        1280
# define SCREEN_H        720
# define FULLSCREEN      true

/* ---------- Player ---------- */
# define MOVE_SPEED      0.05
# define ROT_SPEED       0.03
# define MOUSE_SENS      0.001
# define INTERACT_DIST   1.5
# define PLAYER_MARGIN   0.25

/* ---------- Doors ---------- */
# define DOOR_CLOSE_TIME 30.0

/* ---------- Minimap ---------- */
# define MINI_CELL   6
# define MINI_MARGIN 10
# define MINI_MAX    240
# define MINI_VIEW   20

/* ---------- Player info overlay ---------- */
# define INFO_LINES  3
# define INFO_X      10
# define INFO_Y      10
# define CHAR_W   10
# define CHAR_H   20
# define INFO_W   260

/*INFO_IMG_H  = INFO_LINES * CHAR_H */

# define INFO_IMG_H 60

/* ---------- Texture indices ---------- */
# define TEX_NO     0
# define TEX_SO     1
# define TEX_WE     2
# define TEX_EA     3

/* ---------- Error messages ---------- */
# define ERR_ARGS    "Usage: ./cub3d <map.cub>"
# define ERR_EXT     "Map file must have .cub extension"
# define ERR_OPEN    "Cannot open map file"
# define ERR_FIELD   "Unknown or duplicate identifier"
# define ERR_COLOR   "Invalid color value (must be 0-255, format: R,G,B)"
# define ERR_MAP     "Missing map"
# define ERR_PLAYER  "Map must have exactly one player spawn (N/S/E/W)"
# define ERR_CLOSED  "Map is not surrounded by walls"
# define ERR_CHAR    "Invalid character in map (use 0, 1, D, N, S, E, W, space)"
# define ERR_MISS    "Missing required identifier (NO/SO/WE/EA/F/C)"
# define ERR_AFTER   "Content not allowed after map"
# define ERR_MEM     "Memory allocation failed"
# define ERR_TEX     "Failed to load texture"

/* ---------- Door ---------- */

typedef enum e_door_state
{
	DOOR_CLOSED	= 0,
	DOOR_OPEN	= 1,
}	t_door_state;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
	double			timer;
}	t_door;

/* ---------- Map ---------- */

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_wcol
{
	int				x;
	double			step;
	double			*tex_pos;
	mlx_texture_t	*tex;
}	t_wcol;

typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_color		floor;
	t_color		ceiling;
	uint32_t	ceil_col;
	uint32_t	floor_col;
	int			has_floor;
	int			has_ceiling;
	char		**grid;
	int			rows;
	int			cols;
	int			player_x;
	int			player_y;
	char		player_dir;
	t_door		*doors;
	int			door_count;
	int			map_count;
	int			map_cap;
	int			in_map;
	int			total;
}	t_map;

typedef struct s_mctx
{
	int	ox;
	int	oy;
	int	cz;
	int	px;
	int	py;
	int	ex;
	int	ey;

}	t_mctx;

/* ---------- Player ---------- */

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* ---------- Ray (per-column raycast state) ---------- */

typedef struct s_ray
{
	double	cam_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	ddist_x;
	double	ddist_y;
	double	sdist_x;
	double	sdist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_dist;
	int		tex_idx;
	int		tex_x;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		is_door;
}	t_ray;

/* ---------- Game ---------- */

typedef struct s_game
{
	t_map			map;
	t_player		player;
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*tex[4];
	int				key_e_prev;
	int				key_m_prev;
	int				key_i_prev;
	int				key_tab_prev;
	int				show_minimap;
	int				minimap_full;
	int				show_info;
	int				mouse_x;
	int				mouse_ready;
	mlx_image_t		*info_img;
}	t_game;

/* ---------- Prototypes ---------- */

/* utils */
int			ft_error(char *msg);
void		free_array(char **arr);
void		free_map(t_map *map);
int			is_empty_line(char *line);
int			is_map_line(char *line);

/* parser utils*/
int			parse_feel_north(t_map *map, char *line);
int			parse_feel_south(t_map *map, char *line);
int			parse_feel_east(t_map *map, char *line);
int			parse_feel_west(t_map *map, char *line);
int			parse_feel_ceiling(t_map *map, char *line);
int			parse_feel_floor(t_map *map, char *line);

/* parser */
int			check_extension(char *path);
char		**read_all_lines(int fd, int *count);
int			check_no_content_after(char **all_lines, int total, int from);
int			parse_header_line(t_map *map, char *line);
int			headers_complete(t_map *map);
int			parse_color(char *str, t_color *c);
int			append_map_line(char ***lines, int *count, int *map_cap, char *str);
int			build_map_grid(t_map *map, char **lines, int count);
int			collect_doors(t_map *map);
int			validate_map(t_map *map);
int			parse_file(t_game *game, char *path);

/* game init*/
int			init_game(t_game *game);
void		init_player(t_game *game);
void		cleanup(t_game *game);

/* game loop */
void		game_loop(void *param);
void		handle_keys(t_game *game);

/* raycast_dda.c */
void		init_ray(t_game *game, t_ray *ray, int x);
void		dda(t_game *game, t_ray *ray);
void		calc_wall(t_game *game, t_ray *ray);

/* raycast.c */
void		render_frame(t_game *game);

/* move*/
int			can_move(t_game *game, double new_x, double new_y);
void		move_forward(t_game *game, double speed);
void		strafe(t_game *game, double speed);
void		rotate(t_game *game, double angle);

/* doors */

void		update_doors(t_game *game);
int			player_in_door(t_game *game, t_door *door);
t_door		*find_door(t_map *map, int x, int y);
void		interact_door(t_game *game);

/* minimap_utils.c */
void		draw_rect(t_game *game, int px, int py, t_mctx *c);
void		draw_mini_player(t_game *game, int px, int py, uint32_t col);
uint32_t	cell_color(t_game *game, int mx, int my);

/* minimap.c */
void		draw_minimap(t_game *game);

/* player_info */
void		draw_player_info(t_game *game);
void		dil(mlx_image_t *i, const mlx_texture_t *f, const char *s, int r);

#endif
