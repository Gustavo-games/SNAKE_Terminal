#include <ncurses.h>
#include <stdlib.h>

typedef struct{
    int x, y;
    char *type;
    int points;
}Pellets;

extern WIDTH;
extern HEIGHT;

// Spawns random pellets at random locations with different points
void spawnPellets(WINDOW *win, Pellets *pellets){
    
    // Just one pellet currently | *Maybe* more later
    
    if(pellets[0].type != "Empty") return;

    int randSpawn = rand() % (100 + 1);
    
    if(randSpawn <= 10){
        int randNumX = (rand() % (WIDTH-2)) + 1;
        int randNumY = (rand() % (HEIGHT-2)) + 1;

        pellets[0].type = "Normal";
        pellets[0].x = randNumX;
        pellets[0].y = randNumY;
        pellets[0].points = 1;
    }
    else if(randSpawn <= 20){
        int randNumX = (rand() % (WIDTH-2)) + 1;
        int randNumY = (rand() % (HEIGHT-2)) + 1;

        pellets[0].type = "Big";
        pellets[0].x = randNumX;
        pellets[0].y = randNumY;
        pellets[0].points = 2;
        
    }
}
