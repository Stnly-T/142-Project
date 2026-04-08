// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

#define BUFFER_SIZE 10


extern char *map;
extern int width, height;

/**
 * You should use this function to print out individual characters
 * in the colours used in the demo.
 * @param c
 */
static void printc(char c) {
    switch (c) {
        case WALL:
            change_text_colour(BLUE);
            break;
        case MINOTAUR:
            change_text_colour(MAGENTA);
            break;
        case PLAYER:
            change_text_colour(YELLOW);
            break;
        default:
            change_text_colour(WHITE);
    }
    printf("%c", c);
}

void print_map(void) {

    // iterate through rows
    for (int y = 0; y < height; y++) {
        // iterate through columns in each row
        for (int x = 0; x < width; x++) {
            // print the character at the given x and y position
            printc(map[y * width + x]);
            // then print a space between characters if it isn't the final character in the row
            if (x!=width-1) {
                printf(" ");
            }
        }
        // print a new line character at the end of each row
        printf("\n");
    }
}

void print_revealed_map(int player_y, int player_x) {

    // iterate through rows
    for (int y = 0; y < height; y++) {
        // iterate through columns in each row
        for (int x = 0; x < width; x++) {
            // print the character at the given x and y position if it is within vision distance
            // i.e. the absolute difference between the position to be printed and the player is <= 2 for both x and y
            if (abs(player_y-y) <= PLAYER_VISION_DISTANCE && abs(player_x-x) <= PLAYER_VISION_DISTANCE) {
                printc(map[y * width + x]);
            }
            // otherwise, print an empty space
            else {
                printc(EMPTY);
            }

            // print a space between characters if it isn't the final character in the row
            if (x!=width-1) {
                printc(' ');
            }
        }
        // print a new line character at the end of each row
        printf("\n");
    }
}

int locate_character(char character, int* character_y, int* character_x) {

    // iterate through rows
    for (int y = 0; y < height; y++) {
        // iterate through columns in each row
        for (int x = 0; x < width; x++) {
            // check if the character at that position is the character being searched for
            if (map[y * width + x] == character) {
                // character has been found, set values at passed-in addresses and return FOUND_CHARACTER
                *character_y = y;
                *character_x = x;
                return FOUND_CHARACTER;
            }
        }
    }
    // entire map has been iterated through and character was not found, return CHARACTER_NOT_FOUND
    return CHARACTER_NOT_FOUND;
}


char *load_map(char *filename, int *map_height, int *map_width) {
    // open map file to read. if file cannot be opened, return NULL
    FILE *fpMap = fopen(filename, "r");
    if (fpMap == NULL) {
        return NULL;
    }
    // get the first character in file. if file is empty, return NULL
    char characterToCheck = getc(fpMap);
    if (characterToCheck == EOF) {
        return NULL;
    }

    int widthSetFlag = 0;   // flag for whether the width has been determined yet
    int i = 0;              // number of loops

    // address to the map character array
    char *mapArray = (char*)malloc(1*sizeof(char));

    // loop through the file until the end is reached
    while (characterToCheck != EOF) {

        // increase the size of the map array to fit the number of characters to store
        mapArray = realloc(mapArray,(i+1)*sizeof(char));

        // check if realloc failed
        if (mapArray == NULL) {
            return NULL;
        }

        // set the next position in the map array to the character found in the file
        mapArray[i] = characterToCheck;

        // get the next character in file
        characterToCheck = getc(fpMap);

        // since there are spaces and new line characters in the file,
        // they must be skipped over

        // check if the next character was not a new line
        if (characterToCheck != '\n') {
            // character is a space, not a new line. skip 2 characters
            // to reach the next character to store
            characterToCheck = getc(fpMap);
            characterToCheck = getc(fpMap);
        } else {
            // character was a new line. skip 1 character to reach the
            // next character to store
            characterToCheck = getc(fpMap);

            // since a new line indicates the end of a row, width is the
            // i value at the end of the first row + 1
            if (!widthSetFlag) {
                *map_width = i+1;
                widthSetFlag = 1;
            }
        }

        // increment loop counter
        i++;
    }
    // at this point, i is the number of elements in the map array.
    // set height by dividing i by width
    *map_height = i / *map_width;

    // close map file
    fclose(fpMap);

    //return address to the completed map character array
    return mapArray;
}
