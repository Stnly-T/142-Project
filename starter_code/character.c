// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "character.h"

#include <stdio.h>

#include "game.h"
#include "map.h"

extern char * map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x) {

    // check to see if the Minotaur has caught the player
    if (player_x == minotaur_x && player_y == minotaur_y) {
        // minotaur has caught player, return corresponding code
        return CAUGHT_PLAYER;
    }

    // check if neither the x nor y coordinate is the same as the player
    if (player_x != minotaur_x && player_y != minotaur_y) {
        // minotaur is not in line with player in any direction and can not see player, return corresponding code
        return SEES_NOTHING;
    }

    // at this point, player is in line with minotaur along exactly one direction

    // check if player is in the same column (same x position)
    if (player_x == minotaur_x) {
        // check if player is below minotaur
        if (player_y > minotaur_y) {
            // starting from the minotaur's position, check tiles between minotaur and player for walls
            for (int y = minotaur_y; y < player_y; y++) {
                if (map[y * width + minotaur_x] == WALL) {
                    // wall exists between minotaur and player, vision blocked
                    return SEES_NOTHING;
                }
            }
            // no obstructions, minotaur sees player below
            return DOWN;
        }

        // player is not below minotaur, must be above
        else {
            // starting from the minotaur's position, check tiles between minotaur and player for walls
            for (int y = minotaur_y; y > player_y; y--) {
                if (map[y * width + minotaur_x] == WALL) {
                    // wall exists between minotaur and player, vision blocked
                    return SEES_NOTHING;
                }
            }
            // no obstructions, minotaur sees player above
            return UP;
        }
    }

    // check if player is in the same row (same y position)
    if (player_y == minotaur_y) {
        // check if player is right of minotaur
        if (player_x > minotaur_x) {
            // starting from the minotaur's position, check tiles between minotaur and player for walls
            for (int x = minotaur_x; x < player_x; x++) {
                if (map[minotaur_y * width + x] == WALL) {
                    // wall exists between minotaur and player, vision blocked
                    return SEES_NOTHING;
                }
            }
            // no obstructions, minotaur sees player to the right
            return RIGHT;
        }

        // player is not right of minotaur, must be left
        else {
            // starting from the minotaur's position, check tiles between minotaur and player for walls
            for (int x = minotaur_x; x > player_x; x--) {
                if (map[minotaur_y * width + x] == WALL) {
                    // wall exists between minotaur and player, vision blocked
                    return SEES_NOTHING;
                }
            }
            // no obstructions, minotaur sees player to the left
            return LEFT;
        }
    }
}

int move_character(int * y, int * x, char direction, char character) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    // calculate the new coordinates to use on success (store in local variables)
    // check if the new coordinates point to a wallg
    // at this point, the move is known to be valid (OK direction and not a wall)
    // remove character from the old position and replace with EMPTY
    // set character in the new position in map
    // update the x/y coordinate pointers

    // x and y coordinates of the desired position to move to
    int yCoordsToCheck,xCoordsToCheck;
    switch (direction) {
        case LEFT:
            // set desired position to the left of current position
            yCoordsToCheck = *y;
            xCoordsToCheck = *x - 1;
            break;
        case RIGHT:
            // set desired position to the right of current position
            yCoordsToCheck = *y;
            xCoordsToCheck = *x + 1;
            break;
        case UP:
            // set desired position to above current position
            yCoordsToCheck = *y - 1;
            xCoordsToCheck = *x;
            break;
        case DOWN:
            // set desired position to below current position
            yCoordsToCheck = *y + 1;
            xCoordsToCheck = *x;
            break;
        default:
            // direction supplied was invalid
            return MOVED_INVALID_DIRECTION;
            break;
    }

    // check if the desired position is a wall or outside the map. return MOVED_WALL
    // and prevent movement if this is the case.
    if (map[yCoordsToCheck * width + xCoordsToCheck] == WALL) {
        return MOVED_WALL;
    } else if (yCoordsToCheck < 0 || yCoordsToCheck > height-1 || xCoordsToCheck < 0 || xCoordsToCheck > width-1) {
        return MOVED_WALL;
    } else {
        // move is valid, replace desired position with moved character and replace old position with empty space
        map[yCoordsToCheck * width + xCoordsToCheck] = character;
        map[*y * width + *x] = EMPTY;

        // update values at passed-in position addresses
        *y = yCoordsToCheck;
        *x = xCoordsToCheck;
        return MOVED_OKAY;
    }

}

int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    // calculate the new coordinates

    // check for valid charge direction
    if (charge_direction != UP && charge_direction != DOWN && charge_direction != LEFT && charge_direction != RIGHT) {
        return MOVED_INVALID_DIRECTION;
    }

    // loop minotaur movement code twice to move two tiles in one tick
    for (int loopNum = 0; loopNum < 2; loopNum++) {
        // move minotaur once in the direction of the charge
        int moveStatus = move_character(y, x, charge_direction, MINOTAUR);

        switch (moveStatus) {
            // if movement was valid:
            case MOVED_OKAY:
                // check if player was caught
                if (check_loss(player_y, player_x,*y,*x) == YOU_LOSE) {
                    return CAUGHT_PLAYER;
                }
                break;

            // if moved into wall:
            case MOVED_WALL:
                // determine position of wall the minotaur charged into
                int yCoordsOfWall, xCoordsOfWall;
                switch (charge_direction) {
                    case LEFT:
                        yCoordsOfWall = *y;
                        xCoordsOfWall = *x - 1;
                        break;
                    case RIGHT:
                        yCoordsOfWall = *y;
                        xCoordsOfWall = *x + 1;
                        break;
                    case UP:
                        yCoordsOfWall = *y - 1;
                        xCoordsOfWall = *x;
                        break;
                    case DOWN:
                        yCoordsOfWall = *y + 1;
                        xCoordsOfWall = *x;
                        break;
                }
                // destroy the wall being charged into
                map[yCoordsOfWall * width + xCoordsOfWall] = EMPTY;
                // re-execute move since the previous move failed
                move_character(y, x, charge_direction, MINOTAUR);
                // stop execution of loop and return MOVED_WALL, even if this was the first movement
                return MOVED_WALL;
        }
    }
    // code will only reach this point if it has looped twice without running into a wall or catching the player.
    // in this case, return MOVED_OKAY
    return MOVED_OKAY;
}
