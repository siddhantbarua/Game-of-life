#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BOARD_WIDTH 200
#define BOARD_HEIGHT 50 

int num_neighbours(int board[BOARD_HEIGHT][BOARD_WIDTH], int y_pos, int x_pos){
        int neighbours = 0;
        for (int j = y_pos-1; j <= y_pos+1; j++){
                for (int i = x_pos-1; i <= x_pos+1; i++){
                        if (!(j == y_pos && i == x_pos) && (board[(j + BOARD_HEIGHT)%BOARD_HEIGHT][(i + BOARD_WIDTH)%BOARD_WIDTH] == 1)){
                                neighbours++;
                        }
                }
        }
        return neighbours;
}

void advance_board(int board[BOARD_HEIGHT][BOARD_WIDTH]){
        int neighbours; 
        int new_board[BOARD_HEIGHT][BOARD_WIDTH];
        for (int j = 0; j < BOARD_HEIGHT; j++){
               for (int i = 0; i < BOARD_WIDTH; i++){
                        neighbours = num_neighbours(board, j, i);
                        new_board[j][i] = (neighbours == 3 || ( board[j][i] && neighbours == 2));
                }
        }
        for (int j = 0; j < BOARD_HEIGHT; j++){
                for (int i = 0; i < BOARD_WIDTH; i++){
                        board[j][i] = new_board[j][i];
                }
        }
}


void print_board(int board[BOARD_HEIGHT][BOARD_WIDTH]){
        for (int j = 0; j < BOARD_HEIGHT; j++){
                for (int i = 0; i < BOARD_WIDTH; i++){
                        if (board[j][i] == 0){
                                printf(" ");
                        }
                        else if (board[j][i] == 1){
                                printf("o");
                        }
                        //printf("%d", num_neighbours(board, j, i));
                }
                printf("\n");
        } 
}

void default_board(int board[BOARD_HEIGHT][BOARD_WIDTH]){
        board[12][49] = board[12][48] = board[11][49] = board[13][49] = board[11][50] = 1;
        board[37][49] = board[37][48] = board[36][49] = board[38][49] = board[36][50] = 1;
        board[12][149] = board[12][148] = board[11][149] = board[13][149] = board[11][150] = 1;
        board[37][149] = board[37][148] = board[36][149] = board[38][149] = board[36][150] = 1;

        board[26][101] = board [27][102] = board[28][102] = board[28][101] = board[28][100] = 1;
        board[23][98] = board [22][97] = board[21][97] = board[21][98] = board[21][99] = 1;
}


int main(){
        int BOARD[BOARD_HEIGHT][BOARD_WIDTH] = {0};
        int num_houses;
        printf("Enter number of houses(Enter 0 for default board): ");
        scanf("%d", &num_houses);
        
        if (num_houses == 0){
                default_board(BOARD);
        }
        else {
                int x_temp, y_temp;
                for (int i = 0; i < num_houses; i++){
                        printf("Enter x coordinate of %d house[0, %d]: ", i, BOARD_WIDTH);
                        scanf("%d", &x_temp);
                        printf("Enter y coordinate of %d house[0, %d]: ", i, BOARD_HEIGHT);
                        scanf("%d", &y_temp);
                        BOARD[y_temp][x_temp] = 1;
                }
        }
        print_board(BOARD);
        sleep(2);
        while(1){
                print_board(BOARD);
                usleep(50000);
                fflush(stdout);
                advance_board(BOARD);
        }
        return 0;
}
