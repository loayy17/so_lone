#include "so_long.h"

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
		if (line[0] != '\n' && ++count)
			free(line);
	}
	return (count);
}

int	main(int ac, char **av)
{
	t_game	g;
	int		fd;

	ft_memset(&g, 0, sizeof(t_game));
	if (ac != 2 || !validate_name_map(av[1]))
		exit_err("Usage: ./so_long <map.ber>", NULL, NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || (g.height = count_lines(fd)) < 5)
		exit_err("Invalid map file", NULL, &fd);
	close(fd);
	if (!(g.map = malloc((g.height + 1) * sizeof(char *))) || !read_map(av[1], g.map, g.height))
		exit_err("Map initialization failed", &g, NULL);
	g.width = ft_strlen(g.map[0]);
	if (validate_dimension(g.map, &g.width, &g.height)
		|| validate_wall(g.map, g.width, g.height)
		|| validate_elements(&g)
		|| validate_solution(&g))
		exit_err("Invalid map configuration", &g, NULL);
	start_game(&g);
	game_free(&g, NULL, g.height);
	return (0);
}
