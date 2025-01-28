#include "so_long.h"
#include "anim_path.h"

void ft_draw_player(t_game *g, int dir, int frame)
{
    int width, height;
    char *player_images[ANIMATION_FRAMES];

    set_player_images(player_images, dir);
    if (g->player_img)
        mlx_destroy_image(g->mlx, g->player_img);
    g->player_img = mlx_xpm_file_to_image(g->mlx, player_images[frame], &width, &height);
    if (g->player_img == NULL)
        exit_err("Error\nPlayer image not found\n", g, NULL);
    mlx_put_image_to_window(g->mlx, g->win, g->player_img, g->player.x * 50, g->player.y * 50);
}

void set_player_images(char *player_images[], int dir)
{
    if (dir == 0) 
        ft_draw_player_up(player_images);
    else if (dir == 1)
    {
        ft_draw_player_down(player_images);
    }
    else if (dir == 2)
    {
        ft_draw_player_left(player_images);
    }
    else if (dir == 3)
    {
        ft_draw_player_right(player_images);
    }
}

int ft_animation_player(t_game *g)
{
    ft_draw_player(g, g->frame_count, g->frame);
    g->frame = (g->frame + 1) % ANIMATION_FRAMES;
    usleep(ANIMATION_DELAY * 100);
    return (0);
}

void ft_put_background(t_game *g,int width)
{
    int i = 10;
    int j = 0;
    while(i < 35)
    {
        j = 0;
        while(j < 100)
        {
            mlx_pixel_put(g->mlx, g->win, (width + j) - 10, i, 0x4F77B4CF);
            j++;
        }
        i++;
    }
}

void ft_put_steps(t_game *g,size_t steps)
{
    int width;
    int height;
    unsigned int color = 0x000000;
    char *message;
    char *steps_counter;

    steps_counter = ft_itoa(steps);
    height = 25;
    width = (g->width * 50 / 2) - 50;
    message =ft_strjoin("Steps ==> ", steps_counter);
    if(!steps_counter)
    {
        free(steps_counter);
        exit_err("Error\nFailed to allocate memory\n", g, NULL);
    }
    if(!message)
    {
        free(message);
        exit_err("Error\nFailed to allocate memory\n", g, NULL);
    }
    ft_put_background(g,width);
    mlx_string_put(g->mlx, g->win, width, height, color, message);
    free(steps_counter);
    free(message);
}

void ft_win_game(t_game *g)
{
    
    ft_printf("\033[1;36m");
    ft_printf("**************************************************************\n");
    ft_printf("**************************************************************\n");
    ft_printf("**************************************************************\n");
    ft_printf("*******              شغل نظيف نظيف                     *******\n");
    ft_printf("*******                                                *******\n");
    ft_printf("*******              مرفوضة مرفوضة                     *******\n");
    ft_printf("*******                                                *******\n");
    ft_printf("*******           \033[1;33mYOU WIN\033[1;36m                              *******\n");
    ft_printf("*******           \033[1;33mGO TO SLEEP\033[1;36m                          *******\n");
    ft_printf("*******                                                *******\n");
    ft_printf("*******      \033[0;36mcreated by lalhindi\033[1;36m                       *******\n");
    ft_printf("*******                                                *******\n");
    ft_printf("**************************************************************\n");
    ft_printf("**************************************************************\n");
    ft_printf("**************************************************************\n");
    ft_printf("\033[0m");
    close_window(g);
}

void ft_show_exit_open(t_game *g)
{
    int width;
    int height;
    
    mlx_destroy_image(g->mlx, g->exit_img);
    g->exit_img = mlx_xpm_file_to_image(g->mlx, EXIT_IMAGE_OPEN, &width, &height);
    if (g->exit_img == NULL)
        exit_err("Error\nExit image not found\n", g,NULL);
    mlx_put_image_to_window(g->mlx, g->win, g->exit_img, g->exit.x * 50, g->exit.y * 50);
}

void ft_move_player(t_game *g, int x, int y)
{
    char next_pos;

    next_pos = g->map[g->player.y + y][g->player.x + x];
    if (next_pos == '1')
        return;
    if (next_pos == 'C')
        g->collectible--;
    if(g->collectible == 0)
    {
        ft_show_exit_open(g);
    }    
    if (next_pos == 'E' && g->collectible == 0)
        ft_win_game(g);
    g->map[g->player.y][g->player.x] = '0';
    ft_animation_player(g);
    g->player.x += x;
    g->player.y += y;
    g->map[g->player.y][g->player.x] = 'P';
    if(!(g->player.y == g->exit.y) || !(g->player.x == g->exit.x))
        g->map[g->exit.y][g->exit.x] = 'E';
    draw_map(g);
}

int handle_input(int key, t_game *g)
{
    if (key == KEY_ESC || key == KEY_Q) close_window(g);
    else if (key == KEY_UP || key == KEY_W || key == KEY_8) {
        g->frame_count = 0;
        ft_move_player(g, 0, -1);
    }
    else if (key == KEY_DOWN || key == KEY_S || key == KEY_5) {
        g->frame_count = 1;
        ft_move_player(g, 0, 1);
    }
    else if (key == KEY_LEFT || key == KEY_A || key == KEY_4) {
        g->frame_count = 2;
        ft_move_player(g, -1, 0);
    }
    else if (key == KEY_RIGHT || key == KEY_D || key == KEY_6) {
        g->frame_count = 3;
        ft_move_player(g, 1, 0);
    }
    return (0);
}

int	close_window(t_game *g)
{
    game_free(g, NULL, g->height);
    exit(0);
}