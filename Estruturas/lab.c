#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "pilha.h"

typedef struct solution
{
    int x, y;
    Pilha *theWay;
} solution;

void print(int z, int maze[z][z]){
    system("clear || cls");
        for (int i = 0; i < z; i++)
        {
            for (int j = 0; j < z; j++)
            {
                if (maze[i][j] == 0)
                {
                    printf("  ");
                }

                if (maze[i][j] == 1)
                {
                    printf("# ");
                }

                if (maze[i][j] == 2)
                {
                    printf("o ");
                }

                if (maze[i][j] == 3)
                {
                    printf("@ ");
                }

                if(maze[i][j] == 4){
                    printf(". ");
                }
            }
            printf("\n");
        }
        system("sleep 1 || Start-Sleep -Seconds 1 || timeout /t 1 || sleep 1");
}

//backtracking para encontrar o caminho no labirinto
bool solveMaze(int z, solution solve, int maze[z][z], int x, int y, bool memo[z][z], Pilha *theWay){
    if (solve.x == x && solve.y == y)
    {
        return true;
    }

    if (memo[solve.x + 1][solve.y] == true && memo[solve.x][solve.y + 1] == true && memo[solve.x][solve.y - 1] == true && memo[solve.x - 1][solve.y] == true)
    {
        No *aux = pop(solve.theWay);
        maze[solve.x][solve.y] = 4;
        return solveMaze(z, solve, maze, x, y, memo, theWay);
    }

    if (maze[solve.x + 1][solve.y] == 0 && memo[solve.x + 1][solve.y] == false)
    {
        push(solve.theWay, solve.x, solve.y);
        maze[solve.x][solve.y] = 4;
        maze[solve.x + 1][solve.y] = 2;
        solve.x++;
        print(z, maze);
        return solveMaze(z, solve, maze, x, y, memo, theWay);
    }
    
    if (maze[solve.x][solve.y + 1] == 0 && memo[solve.x][solve.y + 1] == false)
    {
        push(solve.theWay, solve.x, solve.y);
        maze[solve.x][solve.y] = 4;
        maze[solve.x][solve.y + 1] = 2;
        solve.y++;
        print(z, maze);
        return solveMaze(z, solve, maze, x, y, memo, theWay);
    }

    if (maze[solve.x][solve.y - 1] == 0 && memo[solve.x][solve.y + 1] == false)
    {
        maze[solve.x][solve.y] = 4;
        maze[solve.x][solve.y - 1] = 2;
        solve.y--;
        print(z, maze);
        return solveMaze(z, solve, maze, x, y, memo, theWay);
    }

    if (maze[solve.x - 1][solve.y] == 0 && memo[solve.x - 1][solve.y] == false)
    {
        maze[solve.x][solve.y] = 4;
        maze[solve.x - 1][solve.y] = 2;
        solve.x--;
        print(z, maze);
        return solveMaze(z, solve, maze, x, y, memo, theWay);
    }

}

int main()
{
    solution solve;
    FILE *labirinto = fopen("labirinto.txt", "r");
    int z, x, y;
    fscanf(labirinto, "%d", &z);
    int maze[z][z];
    bool memo[z][z];
    Pilha *theWay = criaPilha();
    for (int i = 0; i < z; i++)
    {
        for (int j = 0; j < z; j++)
        {
            fscanf(labirinto, "%d", &maze[i][j]);
            if (maze[i][j] == 2){
                solve.x = i;
                solve.y = j;
            }

            if (maze[i][j] == 3){
                x = i;
                y = j;
            }
        }
    }

    
    solve.theWay = criaPilha();
    push(solve.theWay, solve.x, solve.y);
    memo[solve.x][solve.y] = true;
    bool kapa = solveMaze(z, solve, maze, x, y, memo, theWay);
    
    
    
    
    
}