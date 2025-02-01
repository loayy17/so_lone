/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 06:15:39 by lalhindi          #+#    #+#             */
/*   Updated: 2025/02/01 06:41:52 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_name_map(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return (len > 4 && !ft_strncmp(str + len - 4, ".ber", 4));
}

int	validate_dimension(char **map, size_t *w, size_t *h)
{
	size_t	width;
	size_t	i;

	i = 0;
	while (i < *h)
	{
		width = ft_strlen(map[i]);
		if (i++ > 0 && width != *w)
			return (1);
		*w = width;
	}
	return (0);
}

static int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			exit_err("Error\nMap has empty lines\n", NULL, &fd);
		}
		++count;
		free(line);
	}
	return (count);
}

int	main(int ac, char **av)
{
	t_game	g;
	int		fd;

	ft_bzero(&g, sizeof(t_game));
	if (ac != 2 || !validate_name_map(av[1]))
		exit_err("Usage: ./so_long <map.ber>", NULL, NULL);
	fd = open(av[1], O_RDONLY);
	g.height = count_lines(fd);
	if (fd < 0 || g.height < 3)
		exit_err("Invalid map file", NULL, &fd);
	close(fd);
	g.map = malloc((g.height + 1) * sizeof(char *));
	if (!g.map || !read_map(av[1], g.map, g.height))
		exit_err("Map initialization failed", &g, NULL);
	g.width = ft_strlen(g.map[0]);
	if (validate_dimension(g.map, &g.width, &g.height) || validate_wall(g.map,
			g.width, g.height) || validate_elements(&g)
		|| validate_solution(&g))
		exit_err("Invalid map configuration", &g, NULL);
	start_game(&g);
	game_free(&g, NULL, g.height);
	return (0);
}
