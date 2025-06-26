#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include <algorithm>

int rows = 9;
int columns = 9;
std::vector<std::vector<int>> board(rows, std::vector<int>(columns,0));
std::vector<std::vector<int>> answerBoard(rows, std::vector<int>(columns,0));

using OptionsMap = std::unordered_map<int, std::unordered_map<int, std::vector<int>>>;

void initializeOptions(OptionsMap& cellOptions)
{
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            cellOptions[row][col] = {1,2,3,4,5,6,7,8,9};
        }
    }
}

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

void prepareBoard()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0,1.0);

    double r = 0.0;

    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            r = dist(gen);
            if(r < 0.85)
            {
                board[i][j] = 0;
            }
        }
    }
}

void printBoard(std::vector<std::vector<int>> board)
{
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void solveSudoku(std::vector<std::vector<int>> board, OptionsMap& cellOptions)
{
    /*
     * for i in columns
     *  for j in rows
     *      if(board[i][j] is 0
     *          then we need to find it
     *          check the rest of row at column i
     *          check row and column for 
     *          what numbers can it be
     *          what if we had a map with board[i][j] as the key
     *          at that map we had list of numbers it can be.
     *          it starts our full and then we start popping numbers off
     *          as we check the row, column and square that it is in.
     *          I know how to check the row, and column but don't know how to do square rn
     *
     */
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            if(board[i][j] == 0)
            {
                for(int k = 0; k < rows; k++)
                {
                    if(board[k][j] != 0)
                    {
                        auto& options = cellOptions[i][j];
                        options.erase(std::remove(options.begin(), options.end(), board[k][j]), options.end());
                    }
                }

                for(int k = 0; k < columns; k++)
                {
                    if(board[i][k] != 0)
                    {
                        auto& options = cellOptions[i][j];
                        options.erase(std::remove(options.begin(), options.end(), board[i][k]), options.end());
                    }
                }

                std::cout << "Options left at (" << i << ", " << j << "): ";
                for (int val : cellOptions[i][j]) {
                    std::cout << val << " ";
                }
                std::cout << std::endl;
                
            }
            else
            {
                cellOptions[i][j] = {board[i][j]};
            }
        }
    }
}

int main()
{
    OptionsMap cellOptions;

    initializeOptions(cellOptions);
    populateBoard();
    answerBoard = board;
    printBoard(board);
    printBoard(answerBoard);

    prepareBoard();
    printBoard(board);
    printBoard(answerBoard);

    solveSudoku(board, cellOptions);

    return 0;
}
