#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_ROWS 65536
#define MARGIN 2

void render(WINDOW *work_field, char ** rows, int * lengths, int frow, int fcolumn, int rows_num, int scw, int sch)
{
    int row, col;
    for (int x = 0; x < sch; x++)
    {
        row = x + frow;
        if (row >= rows_num)
            break;
        for (int y = 0; y < scw; y++)
        {
            col = y + fcolumn;
            if (col >= lengths[row])
                break;
            mvwaddch(work_field, x+MARGIN, y+MARGIN, rows[row][col]);
        }
    }
}

int next_move(WINDOW *work_field, int * curr_x, int * curr_y, int max_rows, int max_cols)
{
    // i don't like switch-case :porosad:
    int button = wgetch(work_field);
    if (button == 32 || button == 258) // down 
        if (*curr_x < max_rows)
            *curr_x = *curr_x + 1;
    if (button == 259) // up
        if (*curr_x > 0)
            *curr_x = *curr_x - 1;
    if (button == 261) // right
        if (*curr_y < max_cols)
            *curr_y = *curr_y + 1;
    if (button == 260) // left
        if (*curr_y > 0)
            *curr_y = *curr_y - 1;
    if (button == 27) // escape
        return 0;
    return 1;
}

int main(int argc, char ** argv)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char ** rows = (char **)malloc(sizeof(char*)*MAX_ROWS);
    int lengths[MAX_ROWS];
    int rows_num = 0, all_size = 0, max_len = 0;
    int curr_x = 0, curr_y = 0, step = 1;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        rows[rows_num] = (char *)malloc(sizeof(char)*read);
        memcpy(rows[rows_num], line, read); // i don't treat this obj as string actually
        lengths[rows_num] = (int)read;
        if (max_len < lengths[rows_num])
            max_len = lengths[rows_num];
        all_size += lengths[rows_num];
        rows_num++;
    }

    rows_num++;

    initscr(); 
    noecho(); 
    cbreak();
    printw("Name file: %s, length: %d", argv[1], all_size);
    refresh();

    int screen_height = LINES-MARGIN-MARGIN, screen_width = COLS-MARGIN-MARGIN;
    WINDOW *work_field = newwin(screen_height, screen_width, MARGIN, MARGIN);
    keypad(work_field, TRUE);
    scrollok(work_field, TRUE);

    
    while (step) 
    {
        werase(work_field);
        render(work_field, rows, lengths, curr_x, curr_y, rows_num, screen_width, screen_height);
        box(work_field, 0, 0);
        wrefresh(work_field);
        step = next_move(work_field, &curr_x, &curr_y, rows_num-screen_height+2, max_len-2);
    }
    
    werase(work_field); 
    endwin();

    for (int i = 0; i < rows_num; i++)
    {
        free(rows[i]);
    }
    free(rows);

    fclose(fp);
    if (line)
        free(line);
    
    return 0;
}