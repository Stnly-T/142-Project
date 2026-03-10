// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

#include <stdio.h>

extern char * map;
extern int height;
extern int width;

int check_win(int player_y, int player_x) {
    // The player wins if they escape the map boundaries (i.e., they are in a place an outer wall tile should be).
    if ((player_y >= height) || (player_y <= 0) || (player_x >= width) || (player_x <= 0)) {
        printf("%d %d %d %d", player_y, player_x, height, width);
        return YOU_WIN;
    } else {
        return KEEP_GOING;
    }
}

int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // The player loses if they are caught by the Minotaur
    if (minotaur_y == player_y && minotaur_x == player_x) {
        return YOU_LOSE;
    } else {
        return KEEP_GOING;
    }

}

