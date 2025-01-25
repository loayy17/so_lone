#include "includes/so_long.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
void game_free(t_game *game,int *fd,int height)
{
    int index = 0;
    while(index < height)
    {
        if (game->map[index])
            free(game->map[index]);
        index++;
    }
    free(game->map);
    close(*fd);
}
int validate_name_map(char *str)
{
    size_t len;
    len = strlen(str);
    return (len > 4 && ft_strncmp(str + len - 4, ".ber",4) == 0); 
}

void fill_map_row(char **map, char *line, size_t col)
{
    size_t i = 0;
    map[col] = (char *)malloc((strlen(line) + 1) * sizeof(char));
    if (!map[col])
        exit(0);
    while(line[i] && line[i] != '\n')
    {
        map[col][i] = line[i];
        i++;
    }
    map[col][i] = '\0';
}

int validate_dimention(char **map, size_t *old_width, size_t *height)
{
    size_t width = 0;
    size_t height_2 = 0;
    while(height_2 < *height)
    {
        while(map[height_2][width])
            width++;
        if (width != *old_width)
            return(1);
        *old_width = width;     
        height_2++;    
    }
    return 0;
}

int validate_wall(char **map, size_t width, size_t height)
{
    size_t i = 0;
    size_t j = 0;
    while(i <width)
    {
        if(map[0][i] != '1' || map[height - 1][i] != '1')
            return 1;
        i++;
    }
    while(j < height)
    {
        if(map[j][0] != '1' || map[j][width - 1] != '1')
            return 1;
        j++;
    } 
    return 0;       
}
size_t calculate_collectibles(char **map)
{
    size_t i = 0;
    size_t collectible = 0;
    size_t j;
    while(map[i] != NULL)
    {
        j = 0;
        while(map[i][j] != '\0')
        {
            if(map[i][j] == 'C')
                collectible++;
            j++;   
        } 
        i++;
    }
    return collectible;
}
int validate_elements(t_game *game)
{
    size_t exit = 0;
    size_t player = 0;
    size_t i = 0;
    size_t j;
    game->collectible = calculate_collectibles(game->map);
    game->collectibles = malloc((game->collectible) * sizeof(t_point));
    if (game->collectibles == NULL) {
        return 1;
    }
    game->collectible = 0;
    while(game->map[i] != NULL)
    {
        j = 0;
        while(game->map[i][j]  != '\0')
        {
            if(game->map[i][j] == 'C')
            {
                game->collectibles[game->collectible].x = j;
                game->collectibles[game->collectible].y = i;
                game->collectible++;
            }
            else if(game->map[i][j] == 'P')
            {
                game->player.x = j;
                game->player.y = i;
                player++;
            }
            else if(game->map[i][j] == 'E')
            {
                game->exit.x = j;
                game->exit.y = i;
                exit++;
            }
            else if (game->map[i][j] != '0' && game->map[i][j] != '1') {
                free(game->collectibles);
                return 1;
            }
            j++;   
        } 
        i++;
    }
    game->collectibles = malloc((game->collectible) * sizeof(t_point));
    if(player != 1 || exit != 1 || game->collectible < 1)
    {
        free(game->collectibles);
        return 1;
    }
    return 0;   
}
void flood_fill(t_game *game, size_t x, size_t y, t_point *check) {
    if (x >= game->width || y >= game->height || 
        game->map[y][x] == '1' || game->map[y][x] == 'F') {
        return;
    }
    char original = game->map[y][x];
    game->map[y][x] = 'F';

    if (original == 'C') {
        check->x++;
    } else if (original == 'E') {
        check->y++;
    }
    flood_fill(game, x + 1, y, check);
    flood_fill(game, x - 1, y, check);
    flood_fill(game, x, y + 1, check);
    flood_fill(game, x, y - 1, check);
}

int validate_solution(t_game *game) {
    t_point check = {0, 0};
    t_point c;
    size_t i = 0;
    flood_fill(game, game->player.x, game->player.y, &check);
    game->map[game->exit.y][game->exit.x] = 'E';
    game->map[game->player.y][game->player.x] = 'P';
    while(i <= check.x) 
    {
        c = game->collectibles[i];
        printf("x: %zu y: %zu\n",c.x,c.y);
        game->map[c.y][c.x] = 'C';
        i++;
    }

    free(game->collectibles);
    return (check.x == game->collectible && check.y >= 1);
}

int main(int ac, char **av)
{
    int fd;
    char *line;
    size_t col = 0;
    t_game game;
    if(ac != 2)
    {
        ft_printf("Usage: %s <path-for-map>\n", av[0]);
        return 1;
    }
    if(!validate_name_map(av[1]))
        return 1;
    fd = open(av[1], O_RDONLY);
    if(fd == -1)
    {
        close(fd);
        return 1;
    }
    ft_bzero(&game, sizeof(t_game));    
    while((line = get_next_line(fd)))
    {
        if(line[0] == '\n')
        {
            free(line);
            continue;  
        }
        col++;
        free(line);
    }
    close(fd);
    game.map = (char **)malloc((col + 1)  * sizeof(char *));
    game.height = col;
    col = 0;
    fd = open(av[1], O_RDONLY);
    while((line = get_next_line(fd)))
    {
        if(line[0]  == '\n')
        {
            free(line);
            continue;
        }
        fill_map_row(game.map, line, col++); 
        free(line);       
    }
    game.map[col] = NULL; 
    game.width = ft_strlen(game.map[0]);
    if(validate_dimention(game.map, &game.width, &game.height) 
            || validate_wall(game.map, game.width, game.height) || validate_elements(&game) || validate_solution(&game))
            {    
                size_t i = 0;
                while(i < game.height)
                {
                    ft_printf("%s\n",game.map[i]);
                    i++;
                }
                game_free(&game, &fd,game.height);
              return 1;  
            }
    size_t i = 0;
    while(i < game.height)
    {
        ft_printf("%s\n",game.map[i]);
        i++;
    }
    game_free(&game,&fd,game.height);
        return 0;
    // start_game();
}