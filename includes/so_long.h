#ifndef SO_LONG_H
#define SO_LONG_H
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TILE_SIZE 60
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libraries/Libft/libft.h"
typedef struct s_game 
{
    char **map;
    size_t height;
    size_t width;
    size_t collectible;
} t_game;
#endif