// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "character.h"

#include "map.h"

extern char * map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // check to see if the Minotaur has caught the player
    // check if neither the x nor y coordinate is the same as the player
    // if there's a wall in between, they can't see
    // if one of them is the same, check if the path in between is clear
    return SEES_NOTHING;
}

int move_character(int * y, int * x, char direction, char character) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    // calculate the new coordinates to use on success (store in local variables)
    // check if the new coordinates point to a wallg
    // at this point, the move is known to be valid (OK direction and not a wall)
    // remove character from the old position and replace with EMPTY
    // set character in the new position in map
    // update the x/y coordinate pointers
    int yCoordsToCheck;
    int xCoordsToCheck;
    switch (direction) {
        case LEFT:
            yCoordsToCheck = *y;
            xCoordsToCheck = *x - 1;
            break;
        case RIGHT:
            yCoordsToCheck = *y;
            xCoordsToCheck = *x + 1;
            break;
        case UP:
            yCoordsToCheck = *y - 1;
            xCoordsToCheck = *x;
            break;
        case DOWN:
            yCoordsToCheck = *y + 1;
            xCoordsToCheck = *x;
            break;
        default:
            return MOVED_INVALID_DIRECTION;
            break;
    }
    if (map[yCoordsToCheck * width + xCoordsToCheck] == WALL) {
        return MOVED_WALL;
    } else if (yCoordsToCheck < 0 || yCoordsToCheck > height-1 || xCoordsToCheck < 0 || xCoordsToCheck > width-1) {
        return MOVED_WALL;
    } else {
        map[yCoordsToCheck * width + xCoordsToCheck] = character;
        map[*y * width + *x] = EMPTY;
        *y = yCoordsToCheck;
        *x = xCoordsToCheck;
        return MOVED_OKAY;
    }

}

int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    // calculate the new coordinates
    return MOVED_OKAY;
}
