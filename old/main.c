#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define TILE_SIZE 100
#define ANIM_FRAMES 9
#define ANIM_DELAY 100000
#define DIRECTIONS 4

enum e_direction {UP, DOWN, LEFT, RIGHT};

char map[10][10] = {
    {'1','1','1','1','1','1','1','1','1','1'},
    {'1','0','0','C','0','1','0','0','0','1'},
    {'1','0','1','1','0','1','0','1','0','1'},
    {'1','0','0','0','0','1','0','1','0','1'},
    {'1','0','1','1','0','1','1','1','0','1'},
    {'1','C','0','0','0','0','0','C','0','1'},
    {'1','0','1','1','1','1','1','1','0','1'},
    {'1','0','0','0','0','0','0','0','0','1'},
    {'1','C','0','0','0','C','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','1'}
};

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *wall;
    void    *floor;
    void    *collect;
    void    *player[DIRECTIONS][ANIM_FRAMES];
    int     x;
    int     y;
    int     width;
    int     height;
    int     frame;
    void    **anim;
    int     animating;  
    struct timeval last_frame;
} t_data;

/* Window Management */
int close_game(t_data *d) {
    mlx_destroy_window(d->mlx, d->win);
    exit(0);
}

/* Initialization */
void set_resolution(t_data *d) {
    d->width = 10 * TILE_SIZE;
    d->height = 10 * TILE_SIZE;
}

/* Drawing Helpers */
void put_tile(t_data *d, int x, int y, void *img) {
    mlx_put_image_to_window(d->mlx, d->win, img, x*TILE_SIZE, y*TILE_SIZE);
}

void draw_collectables(t_data *d) {
    int y = 0;
    while (y < 10) {
        int x = 0;
        while (x < 10) {
            if (map[y][x] == 'C') put_tile(d, x, y, d->collect);
            x++;
        }
        y++;
    }
}

// Modified draw_map function
void draw_map(t_data *d) {
    // Draw floor background
    int y = -1;
    while (++y < 10)
    {
        int x = -1;
        while (++x < 10)
            put_tile(d, x, y, d->floor);
    }

    // Draw walls and collectibles
    y = -1;
    while (++y < 10)
    {
        int x = -1;
        while (++x < 10)
        {
            if (map[y][x] == '1')
                put_tile(d, x, y, d->wall);
            else if (map[y][x] == 'C')
                put_tile(d, x, y, d->collect);
        }
    }

    // Draw player (transparency handled by XPM "None" color)
    put_tile(d, d->x, d->y, d->anim[d->frame]);
}

void update_frame(t_data *d) {
    if (!d->animating) return;

    struct timeval now;
    long elapsed;

    gettimeofday(&now, NULL);
    elapsed = (now.tv_sec - d->last_frame.tv_sec) * 1000000 + 
             (now.tv_usec - d->last_frame.tv_usec);
    
    if (elapsed >= ANIM_DELAY) {
        d->frame++;
        if (d->frame >= ANIM_FRAMES) {
            d->frame = ANIM_FRAMES - 1; // Stay on last frame
            d->animating = 0;           // Stop animation
        }
        else {
            d->last_frame = now; // Only update time if continuing
        }
        draw_map(d);
    }
}

void try_move(t_data *d, int dx, int dy, enum e_direction dir) {
    if (map[d->y + dy][d->x + dx] != '1') {
        // Reset animation for new movement
        d->anim = d->player[dir];
        d->animating = 1;
        d->frame = 0;
        gettimeofday(&d->last_frame, NULL);

        d->x += dx;
        d->y += dy;

        // Handle collectibles
        if (map[d->y][d->x] == 'C') {
            map[d->y][d->x] = '0';
        }
    }
}

int handle_input(int key, t_data *d) {
    if (key == 65307 || key == 113) close_game(d);
    else if (key == 65361 || key == 97) try_move(d, -1, 0, LEFT);
    else if (key == 65362 || key == 119) try_move(d, 0, -1, UP);
    else if (key == 65363 || key == 100) try_move(d, 1, 0, RIGHT);
    else if (key == 65364 || key == 115) try_move(d, 0, 1, DOWN);
    return 0;
}

/* Asset Loading */
const char *g_dirs[4] = {"up", "down", "left", "right"};
const char *g_nums[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

void load_assets(t_data *d) {
    d->wall = mlx_xpm_file_to_image(d->mlx, "images/wall.xpm", &d->width, &d->height);
    d->floor = mlx_xpm_file_to_image(d->mlx, "images/floor.xpm", &d->width, &d->height);
    d->collect = mlx_xpm_file_to_image(d->mlx, "images/Princess.xpm", &d->width, &d->height);

    int dir = 0;
    while (dir < DIRECTIONS) {
        int frame = 0;
        while (frame < ANIM_FRAMES) {
            char path[256];
            strcpy(path, "images/");
            strcat(path, g_dirs[dir]);
            strcat(path, "/");
            strcat(path, g_dirs[dir]);
            strcat(path, "_");
            strcat(path, g_nums[frame]);
            strcat(path, ".xpm");
            d->player[dir][frame] = mlx_xpm_file_to_image(d->mlx, path, &d->width, &d->height);
            frame++;
        }
        dir++;
    }
}

/* Main */
int game_loop(t_data *d) {
    update_frame(d);
    return 0;
}

int main() {
    t_data d;

    d.mlx = mlx_init();
    set_resolution(&d);
    d.animating = 0;
    d.win = mlx_new_window(d.mlx, d.width, d.height, "so_long");
    
    load_assets(&d);
    d.x = 1;
    d.y = 1;
    d.anim = d.player[DOWN];
    d.frame = 0;
    gettimeofday(&d.last_frame, NULL);
    
    draw_map(&d);
    mlx_key_hook(d.win, handle_input, &d);
    mlx_hook(d.win, 17, 0, close_game, &d);
    mlx_loop_hook(d.mlx, game_loop, &d);
    mlx_loop(d.mlx);
}