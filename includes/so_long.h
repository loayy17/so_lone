#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_Q 113
# define TILE_SIZE 64


#define WALL_IMAGE "images/wall/wall.xpm"
#define FLOOR_IMAGE "images/wall/floor.xpm"
#define PLAYER_IMAGE "images/player/down/down_1.xpm"
#define EXIT_IMAGE "images/exit/exit_open.xpm"
#define COLLECTIBLE_IMAGE "images/colectible/burger_2.xpm"

typedef struct s_point {
	size_t	x;
	size_t	y;
}	t_point;

typedef struct s_game {
	void		*mlx;
	void		*win;
	char		**map;
	size_t		height;
	size_t		width;
	size_t		collectible;
	t_point		player;
	int			player_on_exit;
	t_point		exit;
	t_point		*collectibles;
	void		*wall_img;
	void		*exit_img;
	void		*collectible_img;
	void		*floor_img;
	void		*player_img;
}	t_game;

// Validation
int		validate_name_map(char *str);
int		validate_dimension(char **map, size_t *w, size_t *h);
int		validate_wall(char **map, size_t w, size_t h);
int		validate_elements(t_game *g);
int		validate_solution(t_game *g);

// Game Init
void	fill_map_row(char **map, char *line, size_t row);
int		read_map(char *file, char **map, int lines);
void	start_game(t_game *g);

// Rendering
void	draw_map(t_game *g);
void	load_images(t_game *g);

// Input
int		handle_input(int key, t_game *g);
int		close_window(t_game *g);

// Memory
void	game_free(t_game *g, int *fd, int h);
void	exit_err(char *msg, t_game *g, int *fd);
void	destroy_images(t_game *g);

// Path Validation
void	flood_fill(t_game *g, size_t x, size_t y, t_point *check);
void	restore_map(t_game *g);
size_t	calculate_collectibles(char **map);

#endif