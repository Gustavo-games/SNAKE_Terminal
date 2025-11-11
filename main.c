#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

#define MAX 1000

int main();

// Global vars
// TODO: Move to struct
int WIDTH = 30;
int HEIGHT = 30;
int size;
bool gameOver;

// updates in a loop the game logic and mechanics
void update(Segment *snake)
{
    int in;
    int statusScrX = WIDTH + 5;

    WINDOW *win = newwin(HEIGHT, WIDTH,0,0);
    move(HEIGHT/2, WIDTH/2);

    Pellets pellets[MAX];
    for(int i = 0; i < MAX; i++){
        pellets[i].points = 0;
        pellets[i].type = "Empty";
    }

    refresh();
    
    int lastPressed;
    while (TRUE)
    {
        in = getch();   
        if(in == 'q' || in == 'Q'){
            break;
        }
        if(in == KEY_LEFT || in == KEY_RIGHT || in == KEY_UP || in == KEY_DOWN){
            lastPressed = in;
        }
       
        win = newwin(HEIGHT, WIDTH,0,0);
        box(win,0,0);
        
        // Game Over
        if(gameOver == TRUE){
            char *gameOverText = "GAME OVER";

            wmove(win, HEIGHT/2, (WIDTH/2) - 4);
            wprintw(win,"%s", gameOverText);

            move(3, statusScrX+1);
            printw("Press ENTER to restart");
            move(4, statusScrX+1);
            printw("Press Q to quit");
            
            wrefresh(win);

            nodelay(stdscr, FALSE);
            in = getch();   
            if (in == '\n' || in == KEY_ENTER) {
                clear();
                refresh();
                main();
            }else if(in == 'q' || in == 'Q'){
                break;
            }

        }else{
        // Game logic
        MoveSnakeHead(lastPressed, snake, win);
        
        spawnPellets(win, pellets);
        
        for(int i = 0; i < MAX; i++){
            if(pellets[i].type == "Normal"){
                wmove(win, pellets[i].y, pellets[i].x);
                wprintw(win, "0");
            }
            if(pellets[i].type == "Big"){
                wmove(win, pellets[i].y, pellets[i].x);
                wprintw(win, "B");
            }
        }
        
        // Score
        move(1, statusScrX);
        printw("SIZE: %d", size);

        move(3, statusScrX+1);
        printw("Press Q to quit");

        wrefresh(win);

        bool colided = CollisionCheck(win, snake[0],snake, pellets);
        if(colided) gameOver = true;
        }

        delwin(win);
        napms(60*2);
    
    }

    
    endwin();
}

int main(){

    size = 1;
    gameOver = false;

    srand(time(NULL));

    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    curs_set(0); 
    keypad(stdscr, TRUE);
    
    // TODO: type in size of the window

    refresh();

    Segment snake[MAX];
    snake[0].x = WIDTH/2;
    snake[0].y = HEIGHT/2;

    for(int i = 1; i < MAX; i++){
        snake[i].x = -100;
        snake[i].y = -100;
    }

    update(snake);
}