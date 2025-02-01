/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 05:51:29 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 05:51:29 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>
#include <fcntl.h>
#include <mlx.h>
#include "libft.h"
#include "anim_path.h"

typedef struct s_point {
	size_t	x;
	size_t	y;
}	t_point;

typedef enum e_player_animate {
	UP,
	DOWN,
	LEFT,
	RIGHT ,
}	t_direction;

typedef struct s_monster {
    size_t            x;
    size_t            y;
    t_direction    dir;
}    t_element;

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
	size_t		height;
	size_t		width;
	t_element		player;
    int			frame;
    int 		player_speed;
	size_t		collectible;
	t_point		*collectibles;
	size_t		monster_counter;
	size_t 		monster_speed;
	t_element		*monsters;
	int		monster_frame;
	size_t		valid_path_number;
	t_point		*valid_path;
	size_t	steps;
	t_element	exit;
	void		*wall_img;
	void		*exit_img[2][5];
	void		*collectible_img;
	void		*floor_img;
	void		*player_img[4][5];
	void		*monster_img[4][5];
	    int         anim_counter;
    int         anim_frame;
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
size_t	count_entities(char **map,char c, size_t h, size_t w);
void	ft_put_steps(t_game *g, size_t steps);
void ft_draw_player(t_game *g, int dir, int frame);
void set_player_images(char *player_images[], int dir);
void ft_draw_player_right(char *player_images[]);
void ft_draw_player_left(char *player_images[]);
void ft_draw_player_down(char *player_images[]);
void ft_draw_player_up(char *player_images[]);
void ft_draw_monster_right(char *monster_images[]);
void ft_draw_monster_left(char *monster_images[]);
void ft_draw_monster_down(char *monster_images[]);
void ft_draw_monster_up(char *monster_images[]);
void bfs_to_catch_player(t_game *g);
t_point *reverse_path(t_point *path);
int monster_ai(t_game *g);
void	calculate_path_length(t_game *g);
void	generate_path(t_game *g);
void ft_draw_exit(char *exit_image[], int open);
void set_element_images(char *element_images[], int dir);
int	ft_animation_player(t_game *g);
int animation_loop(t_game *g);
void    move_monsters(t_game *g);
void render_monsters(t_game *g);	
void set_element_images(char *element_images[], int dir);
void load_monster_images(t_game *g);
void game_over(t_game *g);
#endif