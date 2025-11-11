#include <ncurses.h>
#include "pellets.h"
// Structs
typedef struct{
    int x,y;
}Segment;

extern size;

// Checks collisions from every collideable object
bool CollisionCheck(WINDOW* win, Segment cabeça, Segment *corpo, Pellets *pellet){
    int win_x, win_y;
    int h, w;

    // Check collision with pellets
    if(cabeça.x == pellet[0].x && cabeça.y == pellet[0].y){
        if(pellet[0].type != "Empty"){
            size += pellet[0].points;
            pellet[0].type = "Empty";
        }
    }

    // Check colisions with the rest of the body
    for(int i = 2; i <= size; i++){
        if(cabeça.x == corpo[i].x && cabeça.y == corpo[i].y){
            return true;
        }
    }

    getbegyx(win, win_y, win_x);
    getmaxyx(win, h,w);

    // Just one pellet for now
    if(cabeça.x > w-2) return true;
    if(cabeça.x < win_x+1) return true;
    if(cabeça.y > h-2) return true;
    if(cabeça.y < win_y+1) return true;
    return false;

}

// Moves snake's head to the direction that it is pressed by the arrow keys
void MoveSnakeHead(int lastPressed, Segment *snake, WINDOW *win)
{
    int prevy = snake[0].y;
    int prevx = snake[0].x;

    // Move head of the snake
    wmove(win, snake[0].y,snake[0].x);
    switch (lastPressed)
    {
    case KEY_UP:
        snake[0].y -= 1;
        break;
    case KEY_DOWN:
        snake[0].y += 1;
        break;
    case KEY_RIGHT:
        snake[0].x += 1;
        break;
    case KEY_LEFT:
        snake[0].x -= 1;
        break;
    }

    // Move the rest of the snake
    int aux;
    for(int i = 1; i <= size; i++){
        aux = snake[i].x;
        snake[i].x = prevx;
        prevx = aux;

        aux = snake[i].y;
        snake[i].y = prevy;
        prevy = aux;
        wmove(win, snake[i].y,snake[i].x);
        wprintw(win,"O");
        
    }
}