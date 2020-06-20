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
                                printf("-");
                        }
                        else if (board[j][i] == 1){
                                printf("o");
                        }
                        //printf("%d", num_neighbours(board, j, i));
                }
                printf("\n");
        } 
}


int main(){
        int BOARD[BOARD_HEIGHT][BOARD_WIDTH] = {0};
        int num_houses;
        printf("Enter number of houses: ");
        scanf("%d", &num_houses);
        int x_temp, y_temp;
        for (int i = 0; i < num_houses; i++){
                printf("Enter x coordinate of %d house[0, %d]: ", i, BOARD_WIDTH);
                scanf("%d", &x_temp);
                printf("Enter y coordinate of %d house[0, %d]: ", i, BOARD_HEIGHT);
                scanf("%d", &y_temp);
                BOARD[y_temp][x_temp] = 1;
        }
        while(1){
                print_board(BOARD);
                usleep(100000);
                fflush(stdout);
                advance_board(BOARD);
        }
        return 0;
}
