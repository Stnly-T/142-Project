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
    // check if neither the x nor y coordinate is the same as the player
    // if there's a wall in between, they can't see
    // if one of them is the same, check if the path in between is clear
    if (player_x == minotaur_x && player_y == minotaur_y) {
        return CAUGHT_PLAYER;
    }

    if (player_x != minotaur_x && player_y != minotaur_y) {
        return SEES_NOTHING;
    }

    if (player_x == minotaur_x) {
        if (player_y > minotaur_y) {
            for (int y = minotaur_y; y < player_y; y++) {
                // printf("%d %c \n", y, map[y * width + minotaur_x]);
                if (map[y * width + minotaur_x] == WALL) {
                    // printf("\n");
                    return SEES_NOTHING;
                }
            }
            printf("a\n");
            return DOWN;
        } else {
            for (int y = minotaur_y; y > player_y; y--) {
                // printf("%d %c \n", y, map[y * width + minotaur_x]);
                if (map[y * width + minotaur_x] == WALL) {
                    // printf("\n");
                    return SEES_NOTHING;
                }
            }
            printf("b\n");

            return UP;
        }
    }

    if (player_y == minotaur_y) {
        if (player_x > minotaur_x) {
            for (int x = minotaur_x; x < player_x; x++) {
                // printf("%d %c\n", x, map[minotaur_y * width + x]);
                if (map[minotaur_y * width + x] == WALL) {
                    // printf("\n");
                    return SEES_NOTHING;
                }
            }
            printf("c\n");

            return RIGHT;
        } else {
            for (int x = minotaur_x; x > player_x; x--) {
                // printf("%d %c %d\n", x, map[minotaur_y * width + x], player_x);
                if (map[minotaur_y * width + x] == WALL) {
                    // printf("\n");
                    return SEES_NOTHING;
                }
            }
            printf("d\n");

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
    if (charge_direction != UP && charge_direction != DOWN && charge_direction != LEFT && charge_direction != RIGHT) {
        return MOVED_INVALID_DIRECTION;
    }

    int moveStatus;
    for (int loopFlag = 0; loopFlag < 2; loopFlag++) {
        moveStatus = move_character(y, x, charge_direction, MINOTAUR);
        // printf("%d %d %d %d %d %d %d \n", moveStatus, *y, *x, player_y, player_x, charge_direction, loopFlag);
        switch (moveStatus) {
            case MOVED_OKAY:
                if (check_loss(player_y, player_x,*y,*x) == YOU_LOSE) {
                    printf("a\n");
                    return CAUGHT_PLAYER;
                }
                if (loopFlag == 1) {
                    printf("b\n");
                    return MOVED_OKAY;
                }
                break;
            case MOVED_WALL:
                printf("wall");
                int yCoordsToCheck;
                int xCoordsToCheck;
                switch (charge_direction) {
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
                }
                map[yCoordsToCheck * width + xCoordsToCheck] = EMPTY;
                move_character(y, x, charge_direction, MINOTAUR);
                // print_map();
                return MOVED_WALL;
        }
    }

    return MOVED_OKAY;
}
