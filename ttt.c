#include <stdio.h>
#include <string.h>
#include "ttt.h"

Position create_pos() {
    Position pos = { "         ", 'x'};
    return pos;
}

Position move(Position pos, int i) {
    Position new_pos = create_pos();
    strcpy(new_pos.board, pos.board);
    new_pos.turn = pos.turn == 'x' ? 'o' : 'x';
    new_pos.board[i] = pos.turn;
    return new_pos;
}

int win(Position pos) {
    char *winrow = pos.turn == 'x' ? "ooo" : "xxx";
    char buf[4];
    buf[3] = '\0';
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            buf[x] = pos.board[y*3 + x];
        }
        if (strcmp(buf, winrow) == 0) {
            return 1;
        }
        for (int x = 0; x < 3; x++) {
            buf[x] = pos.board[x*3 + y];
        }
        if (strcmp(buf, winrow) == 0) {
            return 1;
        }
    }
    for (int i = 0, j=0; i < 9; i += 4, j++) {
        buf[j] = pos.board[i];
    }
    if (strcmp(buf, winrow) == 0) {
        return 1;
    }
    for (int i = 2, j=0; i < 8; i += 2, j++) {
        buf[j] = pos.board[i];
    }
    if (strcmp(buf, winrow) == 0) {
        return 1;
    }
    return 0;
}

int value(Position pos) {
    if (win(pos)) {
        return pos.turn == 'x' ? -10 : 10;
    }
    if (strchr(pos.board, ' ') == 0) {
        return 0;
    }
    int cur;
    int init = 0;
    for (int i = 0; i < 9; i++) {
        if (pos.board[i] != ' ') continue;
        int val = value(move(pos, i));
        if (!init) {
            cur = val;
            init = 1;
        } else {
            if (pos.turn == 'x' && cur < val) {
                cur = val;
            } else if (pos.turn == 'o' && val < cur) {
                cur = val;
            }
        }
    }
    if (0 < cur) {
        return cur - 1;
    } else if (cur <  0) {
        return cur + 1;
    }
    return cur;
}

int best_move(Position pos) {
    int cur;
    int cur_i;
    int init = 0;
    for (int i = 0; i < 9; i++) {
        if (pos.board[i] != ' ') continue;
        int val = value(move(pos, i));
        if (!init) {
            init = 1;
            cur = val;
            cur_i = i;
        } else {
            if (pos.turn == 'x' && cur < val) {
                cur = val;
                cur_i = i;
            } else if (pos.turn == 'o' && val < cur) {
                cur = val;
                cur_i = i;
            }
        }
    }
    return cur_i;
}

int draw(Position pos) {
    return strchr(pos.board, ' ') == 0;
}

void print_pos(Position pos) {
    char *ysep = "";
    for (int y = 0; y < 3; y++) {
        char *xsep = "";
        printf("%s\n", ysep);
        printf(" ");
        for(int x = 0; x < 3; x++) {
            int i = y*3 + x;
            int c = pos.board[i];
            printf("%s%c", xsep, c == ' ' ? ('0' + i) : c);
            xsep = " | ";
        }
        printf("\n");
        ysep = "-----------";
    }
}
