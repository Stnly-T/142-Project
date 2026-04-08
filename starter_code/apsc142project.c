// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// Don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and character.h contain prototypes of functions you must implement
#include <string.h>

#include "map.h"
#include "game.h"
#include "character.h"

void update_minotaur(int player_y, int player_x, int *minotaur_y, int *minotaur_x, char *charge_direction);
// void print_map();
// int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x);
// int check_win(int player_y, int player_x);
// int move_character(int * y, int * x, char direction, char character_symbol);
// int locate_character(char character, int * character_y, int * character_x);
// int charge_minotaur(int * minotaur_y, int * minotaur_x, int player_y, int player_x, char charge_direction);
// char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x);
// char * load_map(char * filename, int * map_height, int * map_width);
// void print_revealed_map(int player_y, int player_x);

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
char *map = NULL;
// width and height store the width and height of map
int width, height;

// You are NOT allowed to add more global variables!
// The globals that are included in the starter code provide a convenient way to share information
// between the many functions that all need access to the same data, but all other data must be
// passed using function arguments.  If you add new globals, the autograder tests will fail to run
// and you will not receive a good mark.

/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PLAYER when no player is found on the map
 *   ERR_NO_MINOTAUR when no Minotaur is found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    // This ensures that printf writes to the console immediately, instead of buffering
    // If you remove this, you will not be able to rely on printf to work if your program crashes
    setbuf(stdout, NULL);

    // The Minotaur's current charge direction. When this is equal to SEES_NOTHING, the Minotaur
    // should randomly move around 1 tile per turn
    char charge_direction = SEES_NOTHING;

    // Load map from map file "map.txt". Throws error if no map can be loaded.
    map = load_map("map.txt", &height, &width);
    if (map == NULL) {
        return ERR_NO_MAP;
    }

    // Locate player in map file and set position variables accordingly
    // Throws error if no player is found
    int player_y;
    int player_x;
    if (locate_character(PLAYER, &player_y, &player_x) == CHARACTER_NOT_FOUND) {
        return ERR_NO_PLAYER;
    }

    // Locate minotaur in map file and set position variables accordingly
    // Throws error if no minotaur is found
    int minotaur_y;
    int minotaur_x;
    if (locate_character(MINOTAUR, &minotaur_y, &minotaur_x) == CHARACTER_NOT_FOUND) {
        return ERR_NO_MINOTAUR;
    }

    char input = 0;     // input holds the user input
    int debugFlag = 0;  // debugFlag indicates if debugMode is on (1) or off (0)

    // Loop until we hit the end of input
    while (input != EOF && input != 4) {

        // Print the map
        if (debugFlag == 1) {
            // if debug mode is on, print full map
            print_map();
        } else {
            // otherwise, print area around player
            print_revealed_map(player_y,player_x);
        }

        // Get a character - blocks until one is input
        input = getch();

        // only execute game updates if 'g' is not the input. If 'g' is the input,
        // turn on debug mode and loop execution
        if (input != 'g') {

            // update the minotaur
            update_minotaur(player_y, player_x, &minotaur_y, &minotaur_x, &charge_direction);

            // move the player only if they haven't been caught
            if (check_loss(player_y, player_x, minotaur_y, minotaur_x) == KEEP_GOING) {
                move_character(&player_y, &player_x, input, PLAYER);
            } else {
                // if check_loss() did not return KEEP_GOING, the player has been
                // caught and the game is lost
                printf("Sorry, you lose.");
                // break out of main execution loop
                break;
            }

            // check if the player has won
            if (check_win(player_y, player_x) == YOU_WIN) {
                printf("Congratulations! You win!");
                // break out of main execution loop
                break;
            }
        } else {
            // change the state of debug mode if 'g' was the input
            debugFlag = !debugFlag;
        }

    } // quit if we hit the end of input

    // free the memory set aside for the map
    free(map);

    // You must return the correct error code from defines.h from main depending on what happened
    return NO_ERROR;
}

void update_minotaur(int player_y, int player_x, int *minotaur_y, int *minotaur_x, char *charge_direction) {

    // If a charge is not in progress, see if the Minotaur can see the player
    if (*charge_direction == SEES_NOTHING) {
        char sight_direction = sees_player(player_y, player_x, *minotaur_y, *minotaur_x);
        if (sight_direction == CAUGHT_PLAYER) {
            return;
        }

        // If the Minotaur cannot see the player, move randomly
        if (sight_direction == SEES_NOTHING) {
            // get a random direction, keeping track of if we already tried it
            char tried_directions[] = {0, 0, 0, 0};
            char direction_map[] = {UP, LEFT, DOWN, RIGHT};
            int move_result;
            do {
                // get a random direction
                int direction_int = rand() % 4;
                // set that we tried the direction
                tried_directions[direction_int] = 1;
                // get the input direction to move
                char direction = direction_map[direction_int];
                // try it!
                move_result = move_character(minotaur_y, minotaur_x, direction, MINOTAUR);
                // if we try all the directions, bail out - we can't move
            } while (move_result != MOVED_OKAY &&
                     (!tried_directions[0] || !tried_directions[1] || !tried_directions[2] || !tried_directions[3]));
        } else {
            // The Minotaur sees the player, so initiate a charge
            *charge_direction = sight_direction;
        }
    }
    // If the Minotaur sees the player and hasn't caught them, we call the charge function
    if (!(*charge_direction == SEES_NOTHING || *charge_direction == CAUGHT_PLAYER)) {
        // Once the Minotaur hits a wall, the charge is ended. This is indicated by charge_minotaur returning
        // a MOVED_WALL return value
        int move_result = charge_minotaur(minotaur_y, minotaur_x, player_y, player_x, *charge_direction);
        if (move_result == MOVED_WALL) {
            *charge_direction = SEES_NOTHING;
        }
    }
}
