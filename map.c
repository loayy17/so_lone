#include "includes/so_long.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int validate_name_map(char *str)
{
    size_t len;
    len = strlen(str);
    if(str[len - 4] == '.' && str[len - 3] == 'b' && str[len - 2] == 'e' && str[len - 1] == 'r')
        return 1;
    return 0;
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
    while(map[*height])
    {
        while(map[*height][width])
            width++;
        if (width != *old_width)
            return(1);
        *old_width = width;     
        (*height)++;    
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
        ft_printf("i ==> %c\n",map[0][i]);
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

int validate_elements(char **map, size_t *collectible)
{
    size_t exit = 0;
    size_t player = 0;
    size_t i = 1;
    size_t j = 1;

    while(map[i])
    {
        while(map[i][j])
        {
            if(map[i][j] == 'C')
                (*collectible)++;
            else if(map[i][j] == 'P')
                player++;
            else if(map[i][j] == 'E')
                exit++;
            else if(map[i][j] == '0');
            else if(map[i][j] == '1');
            else return 1;
            j++;    
        } 
        i++;
        j = 0;
    }
    if(player != 1 || exit != 1 || *collectible < 1)
        return 1;
    ft_printf("validate_dimention true");    
    return 0;   
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
        return 1;
    ft_bzero(&game, sizeof(t_game));    
    while((line = get_next_line(fd)))
    {
        if(line[0] == '\n')
        {
            free(line);
            continue;  
        }
        col++;
        // ft_printf("NUMBER OF COL ==> %d",col);
        free(line);
    }
    game.map = (char **)malloc((col + 1)  * sizeof(char *));
    col = 0;
    close(fd);
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
    game.width = ft_strlen(game.map[0]);
    if(validate_dimention(game.map, &game.width, &game.height) 
            || validate_wall(game.map, game.width, game.height) || validate_elements(game.map, &game.collectible))
            {
            ft_printf("NOT valid MAp Fuck you \n");
              return 1;  
            }
    int index = 0;
    while(game.map[index])
    {
        if (game.map[index])
            free(game.map[index]);
        index++;
    }
    free(game.map);
    ft_printf("OMAR");
        return 0;
    // start_game();
}