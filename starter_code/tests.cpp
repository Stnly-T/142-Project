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

TEST_SUITE_END();

/* tests for character.c */
TEST_SUITE_BEGIN("Character tests");

// tests for sees_player

// tests for move_character

// tests for charge_minotaur

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
TEST_CASE("player wins at bottom edge") {
    CHECK(check_win(height,1) == YOU_WIN);
}
TEST_CASE("player wins at right edge") {
    CHECK(check_win(1,width) == YOU_WIN);
}
TEST_CASE("player wins at top edge") {
    CHECK(check_win(0,1) == YOU_WIN);
}
TEST_CASE("player wins at left edge") {
    CHECK(check_win(1,0) == YOU_WIN);
}
TEST_CASE("player does not win while inside") {
    int width=11, height=12;
    CHECK(check_win(1,1) == KEEP_GOING);
    CHECK(check_win(height-1,1) == KEEP_GOING);
    CHECK(check_win(1,width-1) == KEEP_GOING);
    CHECK(check_win(height-1,width-1) == KEEP_GOING);
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