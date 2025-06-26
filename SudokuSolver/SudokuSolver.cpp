#include <iostream>
#include <vector>

int rows = 9;
int columns = 9;
std::vector<std::vector<int>> board(rows, std::vector<int>(columns,0));

/*
std::vector<std::vector<int>> populateBoard()
{
    std::vector<std::vector<int>> result;
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            board[i][j] = j + 1;
        }
    }
}
*/

//for testing
void populateBoard()
{
    int offset = 0;
    bool flag = false;
    for(int i = 0; i < columns; i++)
    {
        if(i == 3) offset += 1;
        if(i == 6) offset += 2;

        for(int j = 0; j < rows; j++)
        {
            board[i][j] = j + 1 + offset;
            //std::cout << board[i][j] << " ";
                
            if(board[i][j] >= 10)
            {
                board[i][j] = board[i][j] - 9;
            }
        }
        offset = offset + 3;
        if(offset >= 9)
        {
            offset = 0;
        }
    }
}

void printBoard()
{
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    populateBoard();
    printBoard();
    return 0;
}
