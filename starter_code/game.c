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

    // check if the player is on or somehow past the bottom edge (y position height-1),
    // top edge (y position 0), right edge (x position width-1), or left edge (x position 0)
    if ((player_y >= height-1) || (player_y <= 0) || (player_x >= width-1) || (player_x <= 0)) {
        // player is on the edge, they have won
        return YOU_WIN;
    } else {
        // player is not on the edge, continue game
        return KEEP_GOING;
    }
}

int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // The player loses if they are caught by the Minotaur

    // check if the coordinates of the minotaur and the player are the same. If they
    // are, the minotaur has caught the player and they lose
    if (minotaur_y == player_y && minotaur_x == player_x) {
        // minotaur has caught player, they lose
        return YOU_LOSE;
    } else {
        // minotaur has not yet caught player, continue game
        return KEEP_GOING;
    }

}

