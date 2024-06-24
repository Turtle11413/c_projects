#include <stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define GAME_END 21

#define START_PLAYER_POS FIELD_HEIGHT / 2
#define START_BALL_Y FIELD_HEIGHT / 2
#define START_BALL_X FIELD_WIDTH / 2

void draw(int player1y, int player2y, int ballx, int bally, int count_points_of_player1,
          int count_points_of_player2);
int make_new_coord_player1(int coord);
int make_new_coord_player2(int coord);
int move_ballx(int ballx, int move_flag);
int move_bally(int bally, int move_flag);
int ball_collision(int move_flag, int player1y, int player2y, int ballx, int bally);
int end_game_collision(int move_flag, int ballx);
void clear();

// Нельзя пользоваться указателями :(
// НЕ ЖМАТЬ ТУДА, КУДА НЕНУЖНО!!!!!!!!!!!!!!!!!

int main() {
    int count_points_of_player1 = 0, count_points_of_player2 = 0;
    int player1y = FIELD_HEIGHT / 2, player2y = FIELD_HEIGHT / 2, bally = FIELD_HEIGHT / 2,
        ballx = FIELD_WIDTH / 2;
    int move_flag = 1;
    while ((count_points_of_player1 != GAME_END) && (count_points_of_player2 != GAME_END)) {
        clear();
        draw(player1y, player2y, ballx, bally, count_points_of_player1, count_points_of_player2);

        player1y = make_new_coord_player1(player1y);
        player2y = make_new_coord_player2(player2y);

        ballx = move_ballx(ballx, move_flag);
        bally = move_bally(bally, move_flag);

        move_flag = ball_collision(move_flag, player1y, player2y, ballx, bally);
        int game_status = end_game_collision(move_flag, ballx);
        if (game_status == 1 || game_status == 2) {
            player1y = START_PLAYER_POS;
            player2y = START_PLAYER_POS;
            ballx = START_BALL_X;
            bally = START_BALL_Y;
            if (game_status == 1) {
                count_points_of_player2++;
                move_flag = count_points_of_player2 % 2 == 0 ? 2 : -2;
            } else {
                count_points_of_player1++;
                move_flag = count_points_of_player1 % 2 == 0 ? 1 : -1;
            }
        }
    }
    clear();
    printf("%d:%d\n", count_points_of_player1, count_points_of_player2);
    printf("Player %d won!\n", (count_points_of_player2 > count_points_of_player1) + 1);
    return 0;
}

void clear() {
    printf("\e[1;1H\e[2J");  // clears the screen (it's cringe)
}

void draw(int player1y, int player2y, int ballx, int bally, int count_points_of_player1,
          int count_points_of_player2) {
    printf("                                       %d : %d\n", count_points_of_player1,
           count_points_of_player2);

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if ((y == 0) || (y == FIELD_HEIGHT - 1)) {
                printf("_");
            } else if ((x == 0) && ((y == player1y - 1) || (y == player1y) || (y == player1y + 1))) {
                printf("|");
            } else if ((x == FIELD_WIDTH - 1) &&
                       ((y == player2y - 1) || (y == player2y) || (y == player2y + 1))) {
                printf("|");
            } else if ((y == bally) && (x == ballx))
                printf("o");
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int make_new_coord_player1(int coord) {
    char space, player1_input;
    printf("Игрок 1(A - Вверх; Z - Вниз): ");
    player1_input = getchar();
    space = getchar();

    if ((((player1_input == 'A') || (player1_input == 'a')) && (space == '\n')) ||
        (((space == 'A') || (space == 'a')) && (player1_input == '\n'))) {
        if (coord > 2) coord -= 1;
    } else if ((((player1_input == 'Z') || (player1_input == 'z')) && (space == '\n')) ||
               (((space == 'Z') || (space == 'z')) && (player1_input == '\n'))) {
        if (coord < FIELD_HEIGHT - 3) coord += 1;
    }

    else if (player1_input == ' ')
        return coord;

    return coord;
}

int make_new_coord_player2(int coord) {
    char space, player2_input;
    printf("Игрок 2(K - Вверх; M - Вниз): ");
    player2_input = getchar();
    space = getchar();

    if ((((player2_input == 'K') || (player2_input == 'k')) && (space == '\n')) ||
        (((space == 'K') || (space == 'k')) && (player2_input == '\n'))) {
        if (coord > 2) coord -= 1;
    } else if ((((player2_input == 'M') || (player2_input == 'm')) && (space == '\n')) ||
               (((space == 'M') || (space == 'm')) && (player2_input == '\n'))) {
        if (coord < FIELD_HEIGHT - 3) coord += 1;
    }

    else if (player2_input == ' ')
        return coord;

    return coord;
}

int move_ballx(int ballx, int move_flag) {
    int new_ballx = ballx;
    switch (move_flag) {
        case 1:
            new_ballx--;
            break;
        case -1:
            new_ballx--;
            break;
        case 2:
            new_ballx++;
            break;
        case -2:
            new_ballx++;
            break;
    }
    return new_ballx;
}

int move_bally(int bally, int move_flag) {
    int new_bally = bally;
    switch (move_flag) {
        case 1:
            new_bally--;
            break;
        case -1:
            new_bally++;
            break;
        case 2:
            new_bally--;
            break;
        case -2:
            new_bally++;
            break;
    }
    return new_bally;
}

int ball_collision(int move_flag, int player1y, int player2y, int ballx, int bally) {
    // wall collision
    if ((bally == 1) || (bally == FIELD_HEIGHT - 2)) {
        move_flag *= -1;
    }

    // player collision
    if (move_flag == 1 || move_flag == -1) {
        if (ballx == 1 && player1y - 1 <= bally && bally <= player1y + 1) {
            if (move_flag == 1)
                move_flag = 2;
            else
                move_flag = -2;
        }
    } else {
        if (ballx == FIELD_WIDTH - 2 && player2y - 1 <= bally && bally <= player2y + 1) {
            if (move_flag == 2)
                move_flag = 1;
            else
                move_flag = -1;
        }
    }
    return move_flag;
}

int end_game_collision(int move_flag, int ballx) {
    if ((move_flag == 1 || move_flag == -1) && ballx == 0) {
        return 1;
    } else if ((move_flag == 2 || move_flag == -2) && ballx == FIELD_WIDTH - 1) {
        return 2;
    }

    return 0;
}
