#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"
# include <./X11/X.h>

# define PRESS 2
# define RELEASE 3 
# define TILE_SIZE 50
# define DESTROY_WINDOW 17
#define WALL_IMAGE "images/wall/wall.xpm"
#define FLOOR_IMAGE "images/wall/lava.xpm"
#define PLAYER_IMAGE_DOWN "images/fireboy/down/down_2.xpm"
#define PLAYER_IMAGE_UP "images/fireboy/up/up_1.xpm"
#define PLAYER_IMAGE_LEFT "images/fireboy/left/left_1.xpm"
#define PLAYER_IMAGE_RIGHT "images/fireboy/right/right_1.xpm"
#define EXIT_IMAGE_OPEN "images/exit/exit_open.xpm"
#define EXIT_IMAGE_CLOSE "images/exit/exit_close.xpm"
#define COLLECTIBLE_IMAGE "images/colectible/jewel.xpm"

typedef struct s_point {
	size_t	x;
	size_t	y;
}	t_point;

typedef enum e_player_animate {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3,
}	t_player_animate;

typedef enum e_key {
	KEY_ESC = 65307,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_ATTACK = 32,
	KEY_Q = 113,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_8 = 65431,
	KEY_5 = 65437,
	KEY_4 = 65430,
	KEY_6 = 65432,
}	t_key;

typedef struct s_game {
	void		*mlx;
	void		*win;
	char		**map;
	void *fire_sheet;
    int frame;
    int frame_count;
	size_t		height;
	size_t		width;
	size_t		collectible;
	t_point		player;
	size_t	steps;
	t_point		exit;
	t_point		*collectibles;
	void		*wall_img;
	void		*exit_img;
	void		*collectible_img;
	void		*floor_img;
	void		*player_img;
}	t_game;

int animate_fire(t_game *game);
int		validate_name_map(char *str);
int		validate_dimension(char **map, size_t *w, size_t *h);
int		validate_wall(char **map, size_t w, size_t h);
int		validate_elements(t_game *g);
int		validate_solution(t_game *g);
void	fill_map_row(char **map, char *line, size_t row);
int		read_map(char *file, char **map, int lines);
void	start_game(t_game *g);
void	draw_map(t_game *g);
void	load_images(t_game *g);
int		handle_input(int key, t_game *g);
int		close_window(t_game *g);
void	game_free(t_game *g, int *fd, int h);
void	exit_err(char *msg, t_game *g, int *fd);
void	destroy_images(t_game *g);
void	flood_fill(t_game *g, size_t x, size_t y, t_point *check);
void	restore_map(t_game *g);
size_t	calculate_collectibles(char **map);
int	ft_animation_player(t_game *g);
void	ft_put_steps(t_game *g, size_t steps);
#endif