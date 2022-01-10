#include <stdio.h>
#include <string.h>
#include "ttt.h"

#define TEST(fn) { fn, #fn }
#define SUCCESS 1
#define FAIL 0

int test_create() {
    Position pos = create_pos();
    if (strcmp(pos.board, "         ") != 0) {
        printf("-->[%s] is not correct\n", pos.board);
        return FAIL;
    }
    if (pos.turn != 'x') {
        printf("--> turn is %c\n", pos.turn);
        return FAIL;
    }
    return SUCCESS;
}

int test_move() {
    Position pos = create_pos();
    pos = move(pos, 1);
    char *expected = " x       ";
    if (strcmp(pos.board, expected) != 0) {
        printf("--> actual [%s] != expected [%s]\n", pos.board, expected);
        return FAIL;
    }
    if (pos.turn != 'o') {
        printf("--> actual [%c], expected turn to be o", pos.turn);
        return FAIL;
    }
    return SUCCESS;
}

int test_win() {
    Position test_positions[] = {
        { "xxx      ", 'o'},
        { "ooo      ", 'x'},
        { "x  x  x  ", 'o'},
        { "o  o  o  ", 'x'},
        { "x   x   x", 'o'},
        { "o   o   o", 'x'},
        { "  x x x  ", 'o'},
        { "  o o o  ", 'x'},
    };
    int len = sizeof(test_positions)/sizeof(Position);
    for (int i = 0; i < len; i++) {
        Position pos = test_positions[i];
        if(!win(pos)) {
            printf("--> acutal [%s] didn't win\n", pos.board);
            return FAIL;
        }
    }
    return SUCCESS;
}

int test_value() {
    struct {
        Position pos;
        int expected;
    } test_items[] = {
        {{ "xxx      ", 'o'}, 10},
        {{ "ooo      ", 'x'}, -10},
        {{ "xoxxoxoxo", 'o'}, 0},
        {{ "xx       ", 'x'}, 9},
        {{ "oo       ", 'o'}, -9},
    };
    int len = sizeof(test_items) / sizeof(test_items[0]);
    for (int i = 0; i < len; i++) {
        Position pos = test_items[i].pos;
        int expected = test_items[i].expected;
        int val = value(pos);
        if (val != expected) {
            printf("--> [%s], actual %d, expected %d\n", pos.board, val, expected);
            return FAIL;
        }
    }
    return SUCCESS;
}

int test_best_move() {
    struct {
        Position pos;
        int expected;
    } test_items[] = {
        {{ "xx       ", 'x'}, 2},
        {{ "xx       ", 'o'}, 2},
        {{ "oo       ", 'o'}, 2},
        {{ "oo       ", 'x'}, 2},
        {{ "x  x     ", 'x'}, 6},
        {{ "x  x     ", 'o'}, 6},
        {{ "o  o     ", 'x'}, 6},
        {{ "o  o     ", 'o'}, 6},
    };
    int len = sizeof(test_items) / sizeof(test_items[0]);
    for (int i = 0; i < len; i++) {
        Position pos = test_items[i].pos;
        int expected = test_items[i].expected;
        int m = best_move(pos);
        if (m != expected) {
            printf("--> [%s], actual %d, expected %d\n", pos.board, m, expected);
            return FAIL;
        }
    }
    return SUCCESS;
}

int test_draw() {
    Position pos = { "xoxxoxoxo", 'o'};
    if (!draw(pos)) {
        printf("--> [%s] is not draw\n", pos.board);
        return FAIL;
    }
    return SUCCESS;
}

typedef struct {
    int (*fn)();
    char *name;
} Test;

Test suite[] = {
    TEST(test_create),
    TEST(test_move),
    TEST(test_win),
    TEST(test_value),
    TEST(test_best_move),
    TEST(test_draw),
};

int main() {
    int len = sizeof(suite) / sizeof(Test);
    for (int i = 0; i < len; i++) {
        Test test = suite[i];
        int passed = (*test.fn)();
        if (passed) {
            printf("%s passed\n", test.name);
        } else {
            printf("%s failed\n", test.name);
        }
    }
}
