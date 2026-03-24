// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "character.h"
#include "game.h"
char *map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

/* Tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// Tests for load_map
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

// Tests for is_wall

// Tests for locate_character
TEST_CASE("correctly returns character not found") {
    int charX;
    int charY;

    char testMap1[] = {
        EMPTY
    };
    width = 1;
    height = 1;
    map = testMap1;
    CHECK(locate_character(PLAYER,&charY,&charX) == CHARACTER_NOT_FOUND);

    char testMap2[] = {
        EMPTY,MINOTAUR,
        WALL,EMPTY
    };
    width = 2;
    height = 2;
    map = testMap2;
    CHECK(locate_character(PLAYER,&charY,&charX) == CHARACTER_NOT_FOUND);

    char testMap3[] = {
        EMPTY,WALL,WALL,
        WALL,EMPTY,PLAYER,
        EMPTY,EMPTY,WALL
    };
    width = 3;
    height = 3;
    map = testMap3;
    CHECK(locate_character(MINOTAUR,&charY,&charX) == CHARACTER_NOT_FOUND);

}
TEST_CASE("correctly returns character found with coordinates") {
    int charX;
    int charY;

    char testMap1[] = {
        PLAYER
    };
    width = 1;
    height = 1;
    map = testMap1;
    CHECK(locate_character(PLAYER,&charY,&charX) == FOUND_CHARACTER);
    CHECK(charY==0);
    CHECK(charX==0);

    char testMap2[] = {
        EMPTY,PLAYER,
        WALL,EMPTY
    };
    width = 2;
    height = 2;
    map = testMap2;
    CHECK(locate_character(PLAYER,&charY,&charX) == FOUND_CHARACTER);
    CHECK(charY==0);
    CHECK(charX==1);

    char testMap3[] = {
        EMPTY,PLAYER,WALL,
        WALL,EMPTY,WALL,
        EMPTY,EMPTY,MINOTAUR
    };
    width = 3;
    height = 3;
    map = testMap3;
    CHECK(locate_character(MINOTAUR,&charY,&charX) == FOUND_CHARACTER);
    CHECK(charY==2);
    CHECK(charX==2);
}

TEST_SUITE_END();

/* tests for character.c */
TEST_SUITE_BEGIN("Character tests");

// tests for sees_player
TEST_CASE("sees up") {
    char testMap[] = {
        EMPTY,PLAYER,EMPTY,
        EMPTY,EMPTY,EMPTY,
        EMPTY,EMPTY,EMPTY,
        EMPTY,EMPTY,EMPTY,
        EMPTY,EMPTY,EMPTY,
        EMPTY,MINOTAUR,EMPTY
    };
    map = testMap;
    width=3;
    height=6;
    int charY = 0;
    int charX = 1;
    int minoY = 5;
    int minoX = 1;

    CHECK(sees_player(charY, charX, minoY, minoX) == UP);
}
TEST_CASE("sees down") {
    char testMap[] = {
        EMPTY,MINOTAUR,EMPTY,
        EMPTY,EMPTY,EMPTY,
        EMPTY,EMPTY,EMPTY,
        EMPTY,EMPTY,EMPTY,
        EMPTY,EMPTY,EMPTY,
        EMPTY,PLAYER,EMPTY
    };
    map = testMap;
    width=3;
    height=6;
    int charY = 5;
    int charX = 1;
    int minoY = 0;
    int minoX = 1;

    CHECK(sees_player(charY, charX, minoY, minoX) == DOWN);
}
TEST_CASE("sees left") {
    char testMap[] = {
        EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
        PLAYER,EMPTY,EMPTY,EMPTY,MINOTAUR,
        EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
    };
    map = testMap;
    width=5;
    height=3;
    int charY = 1;
    int charX = 0;
    int minoY = 1;
    int minoX = 4;

    CHECK(sees_player(charY, charX, minoY, minoX) == LEFT);
}
TEST_CASE("sees right") {
    char testMap[] = {
        EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
        MINOTAUR,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,PLAYER,
        EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,
    };
    map = testMap;
    width=7;
    height=3;
    int charY = 1;
    int charX = 6;
    int minoY = 1;
    int minoX = 0;

    CHECK(sees_player(charY, charX, minoY, minoX) == RIGHT);
}
TEST_CASE("does not see through walls") {
    char testMap[] = {
        EMPTY,EMPTY,PLAYER,EMPTY,EMPTY,
        EMPTY,EMPTY,WALL,EMPTY,EMPTY,
        PLAYER,WALL,MINOTAUR,WALL,PLAYER,
        EMPTY,EMPTY,WALL,EMPTY,EMPTY,
        EMPTY,EMPTY,PLAYER,EMPTY,EMPTY
    };
    map = testMap;
    width=5;
    height=5;
    int charY = 0;
    int charX = 2;
    int minoY = 2;
    int minoX = 2;

    CHECK(sees_player(charY, charX, minoY, minoX) == SEES_NOTHING);
    CHECK(sees_player(2, 0, minoY, minoX) == SEES_NOTHING);
    CHECK(sees_player(2, 4, minoY, minoX) == SEES_NOTHING);
    CHECK(sees_player(4, 2, minoY, minoX) == SEES_NOTHING);
}

// tests for move_character
TEST_CASE("returns invalid movement on invalid input") {
    width=11;
    height=12;
    int charY = 5;
    int charX = 5;

    CHECK(move_character(&charY,&charX,'p',PLAYER) == MOVED_INVALID_DIRECTION);
}
TEST_CASE("returns valid movement on up") {
    char testMap[] = {
        EMPTY, EMPTY, EMPTY,
        EMPTY, PLAYER, EMPTY,
        EMPTY, EMPTY, EMPTY
        };
    map = testMap;
    width=3;
    height=3;
    int charY = 1;
    int charX = 1;

    CHECK(move_character(&charY,&charX,UP,PLAYER) == MOVED_OKAY);
    CHECK(charY == 0);
    CHECK(charX == 1);
    CHECK(map[charY*width+charX] == PLAYER);
    CHECK(map[1*width+1] == EMPTY);
}
TEST_CASE("returns valid movement on down") {
    char testMap[] = {
        EMPTY, EMPTY, EMPTY,
        EMPTY, PLAYER, EMPTY,
        EMPTY, EMPTY, EMPTY
        };
    map = testMap;
    width=3;
    height=3;
    int charY = 1;
    int charX = 1;

    CHECK(move_character(&charY,&charX,DOWN,PLAYER) == MOVED_OKAY);
    CHECK(charY == 2);
    CHECK(charX == 1);
    CHECK(map[charY*width+charX] == PLAYER);
    CHECK(map[1*width+1] == EMPTY);
}
TEST_CASE("returns valid movement on left") {
    char testMap[] = {
        EMPTY, EMPTY, EMPTY,
        EMPTY, PLAYER, EMPTY,
        EMPTY, EMPTY, EMPTY
        };
    map = testMap;
    width=3;
    height=3;
    int charY = 1;
    int charX = 1;

    CHECK(move_character(&charY,&charX,LEFT,PLAYER) == MOVED_OKAY);
    CHECK(charY == 1);
    CHECK(charX == 0);
    CHECK(map[charY*width+charX] == PLAYER);
    CHECK(map[1*width+1] == EMPTY);
}
TEST_CASE("returns valid movement on right") {
    char testMap[] = {
        EMPTY, EMPTY, EMPTY,
        EMPTY, PLAYER, EMPTY,
        EMPTY, EMPTY, EMPTY
        };
    map = testMap;
    width=3;
    height=3;
    int charY = 1;
    int charX = 1;

    CHECK(move_character(&charY,&charX,RIGHT,PLAYER) == MOVED_OKAY);
    CHECK(charY == 1);
    CHECK(charX == 2);
    CHECK(map[charY*width+charX] == PLAYER);
    CHECK(map[1*width+1] == EMPTY);
}
TEST_CASE("movement functions for minotaur") {
    char testMap[] = {
        EMPTY, EMPTY, EMPTY,
        EMPTY, MINOTAUR, EMPTY,
        EMPTY, EMPTY, EMPTY
        };
    map = testMap;
    width=3;
    height=3;
    int charY = 1;
    int charX = 1;

    CHECK(move_character(&charY,&charX,UP,MINOTAUR) == MOVED_OKAY);
    CHECK(charY == 0);
    CHECK(charX == 1);
    CHECK(map[charY*width+charX] == MINOTAUR);
    CHECK(map[1*width+1] == EMPTY);
}
TEST_CASE("prevents movement into wall") {
    char testMap[] = {
    WALL, WALL, WALL,
    WALL, PLAYER, WALL,
    WALL, WALL, WALL
    };
    map = testMap;
    width=3;
    height=3;
    int charY = 1;
    int charX = 1;

    CHECK(move_character(&charY,&charX,UP,PLAYER) == MOVED_WALL);
    CHECK(charY == 1);
    CHECK(charX == 1);
    CHECK(map[1*width+1] == PLAYER);
    CHECK(map[0*width+1] == WALL);

    CHECK(move_character(&charY,&charX,DOWN,PLAYER) == MOVED_WALL);
    CHECK(charY == 1);
    CHECK(charX == 1);
    CHECK(map[1*width+1] == PLAYER);
    CHECK(map[2*width+1] == WALL);

    CHECK(move_character(&charY,&charX,LEFT,PLAYER) == MOVED_WALL);
    CHECK(charY == 1);
    CHECK(charX == 1);
    CHECK(map[1*width+1] == PLAYER);
    CHECK(map[1*width+0] == WALL);

    CHECK(move_character(&charY,&charX,RIGHT,PLAYER) == MOVED_WALL);
    CHECK(charY == 1);
    CHECK(charX == 1);
    CHECK(map[1*width+1] == PLAYER);
    CHECK(map[1*width+2] == WALL);
}
TEST_CASE("prevents movement out of map") {
    char testMap[] = {
        PLAYER
        };
    map = testMap;
    width=1;
    height=1;
    int charY = 0;
    int charX = 0;

    CHECK(move_character(&charY,&charX,UP,PLAYER) == MOVED_WALL);
    CHECK(charY == 0);
    CHECK(charX == 0);
    CHECK(map[0*width+0] == PLAYER);

    CHECK(move_character(&charY,&charX,DOWN,PLAYER) == MOVED_WALL);
    CHECK(charY == 0);
    CHECK(charX == 0);
    CHECK(map[0*width+0] == PLAYER);

    CHECK(move_character(&charY,&charX,LEFT,PLAYER) == MOVED_WALL);
    CHECK(charY == 0);
    CHECK(charX == 0);
    CHECK(map[0*width+0] == PLAYER);

    CHECK(move_character(&charY,&charX,RIGHT,PLAYER) == MOVED_WALL);
    CHECK(charY == 0);
    CHECK(charX == 0);
    CHECK(map[0*width+0] == PLAYER);
}
// tests for charge_minotaur
TEST_CASE("minotaur catches player") {
    char testMap[] = {
        PLAYER, EMPTY, MINOTAUR
        };
    map = testMap;
    width=3;
    height=1;
    int charY = 0;
    int charX = 0;
    int minoY = 0;
    int minoX = 2;

    CHECK(charge_minotaur(&minoY, &minoX, charY, charX, LEFT) == CAUGHT_PLAYER);
    CHECK(minoY == 0);
    CHECK(minoX == 0);
    CHECK(map[0*width+0] == MINOTAUR);
    CHECK(map[0*width+2] == EMPTY);
}

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
TEST_CASE("player wins at bottom edge") {
    width=11;
    height=12;
    CHECK(check_win(height,1) == YOU_WIN);
    CHECK(check_win(height+10,1) == YOU_WIN);
}
TEST_CASE("player wins at right edge") {
    width=11;
    height=12;
    CHECK(check_win(1,width) == YOU_WIN);
    CHECK(check_win(1,width+10) == YOU_WIN);
}
TEST_CASE("player wins at top edge") {
    width=11;
    height=12;
    CHECK(check_win(0,1) == YOU_WIN);
    CHECK(check_win(-10,1) == YOU_WIN);
}
TEST_CASE("player wins at left edge") {
    width=11;
    height=12;
    CHECK(check_win(1,0) == YOU_WIN);
    CHECK(check_win(0,-10) == YOU_WIN);
}
TEST_CASE("player does not win while inside") {
    width=11;
    height=12;
    CHECK(check_win(1,1) == KEEP_GOING);
    CHECK(check_win(height-2,1) == KEEP_GOING);
    CHECK(check_win(1,width-2) == KEEP_GOING);
    CHECK(check_win(height-2,width-2) == KEEP_GOING);
}

// test for check_loss
TEST_CASE("player loses on minotaur") {
    CHECK(check_loss(1,1,1,1) == YOU_LOSE);
    CHECK(check_loss(1,2,1,2) == YOU_LOSE);
    CHECK(check_loss(5,5,5,5) == YOU_LOSE);
    CHECK(check_loss(0,0,0,0) == YOU_LOSE);
    CHECK(check_loss(10,10,10,10) == YOU_LOSE);
    CHECK(check_loss(9999,9999,9999,9999) == YOU_LOSE);
    CHECK(check_loss(-1,-1,-1,-1) == YOU_LOSE);

}
TEST_CASE("player does not lose when not on minotaur") {
    CHECK(check_loss(1,1,2,2) == KEEP_GOING);
    CHECK(check_loss(0,0,2,2) == KEEP_GOING);
    CHECK(check_loss(2,1,2,2) == KEEP_GOING);
    CHECK(check_loss(1,2,2,2) == KEEP_GOING);
    CHECK(check_loss(3,3,3,2) == KEEP_GOING);
    CHECK(check_loss(3,3,2,3) == KEEP_GOING);
    CHECK(check_loss(-1,-1,-1,1) == KEEP_GOING);

}
TEST_SUITE_END();