typedef struct {
    char board[10];
    char turn;
} Position;

extern Position create_pos();
extern Position move(Position, int);
extern int win(Position);
extern int value(Position);
extern int best_move(Position);
extern int draw(Position);
extern void print_pos(Position);
