#include <stdio.h>
#include "ttt.h"

int main() {
    Position pos = create_pos();
    int i;

    while (!draw(pos)) {
        print_pos(pos);
        if (pos.turn == 'x') {
            printf("move: ");
            scanf("%d", &i);
            pos = move(pos, i);
            if (win(pos)) {
                printf("You win!\n");
                break;
            }
        } else {
            i = best_move(pos);
            pos = move(pos, i);
            if (win(pos)) {
                printf("Computer wins!\n");
                break;
            }
        }
    }
    print_pos(pos);
    if (draw(pos)) {
        printf("draw!\n");
    }

    return 0;
}
