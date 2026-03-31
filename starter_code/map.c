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
    // Print the map given in the global map variable
    // printc(map[1]);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printc(map[y * width + x]);
            if (x!=width-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    // printc('P');
}

void print_revealed_map(int player_y, int player_x) {
    // Only the map within PLAYER_VISION_DISTANCE of the player (including diagonals) should be printed
}

int locate_character(char character, int* character_y, int* character_x) {
    // Attempt to find the character in the map and return a status code indicating
    // if they were present
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y * width + x] == character) {
                *character_y = y;
                *character_x = x;
                return FOUND_CHARACTER;
            }
        }
    }
    return CHARACTER_NOT_FOUND;
}


char *load_map(char *filename, int *map_height, int *map_width) {
    FILE *fpMap = fopen(filename, "r");
    char characterToCheck = getc(fpMap);
    if (characterToCheck == EOF) {
        return NULL;
    }

    int i = 0;
    char *map = (char*)malloc(1*sizeof(char));

    while (characterToCheck != EOF) {

        map = realloc(map,sizeof(map)+sizeof(char));
        switch (characterToCheck) {
            case WALL:
                map[i] = WALL;
                break;

            case EMPTY:
                map[i] = EMPTY;
                break;

            case MINOTAUR:
                map[i] = MINOTAUR;
                break;

            case PLAYER:
                map[i] = PLAYER;
                break;
        }
        i++;
        characterToCheck = getc(fpMap);
    }
    return map;





}
