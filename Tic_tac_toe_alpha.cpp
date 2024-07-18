#include<iostream>
#include<limits.h>
using namespace std;

char board[3][3];
int counter = 0;

void display_board(char board[3][3])
{
    cout << "-------------\n";
    cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |" << endl;
    cout << "-------------\n";
    cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |" << endl;
    cout << "-------------\n";
    cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |" << endl;
    cout << "-------------\n";
}

int check_win()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-')
            return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '-')
            return true;
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-')
        return true;

    return false;
}

int minimax(char board[3][3], int depth, bool state, int turn, int alpha, int beta)
{
    int score = 0;
    int bestScore = 0;
    if (check_win())
    {
        if (state == true)
            return -1;
        if (state == false)
            return +1;
    }
    else
    {
        if (depth <= 9)
        {
            if (state == true)
            {
                bestScore = INT_MIN;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (board[i][j] == '-')
                        {
                            if(turn % 2 == 1)
                                board[i][j] = 'X';
                            else
                                board[i][j] = 'O';
                            score = minimax(board, depth + 1, false, turn, alpha, beta);
                            counter++;
                            board[i][j] = '-';
                            bestScore = max(score, bestScore);
                            alpha = max(alpha, bestScore);
                            if (beta <= alpha)
                                break;
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = INT_MAX;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (board[i][j] == '-')
                        {
                            if(turn % 2 == 1)
                                board[i][j] = 'O';
                            else
                                board[i][j] = 'X';
                            score = minimax(board, depth + 1, true, turn, alpha, beta);
                            counter++;
                            board[i][j] = '-';
                            bestScore = min(score, bestScore);
                            beta = min(beta, bestScore);
                            if (beta <= alpha)
                                break;
                        }
                    }
                }
                return bestScore;
            }
        }
        else
            return 0;
    }
}

void comp_move(int turn, int move)
{   
    int n;
    cout << "Turn : " << turn << "\nComputer's move." <<endl;
    int x = -1, y = -1;
    int score = 0, bestScore = INT_MIN;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
            {
                if(turn % 2 == 1)
                    board[i][j] = 'X';
                else
                    board[i][j] = 'O';
                score = minimax(board, move + 1, false, turn, INT_MIN, INT_MAX);
                counter++;
                board[i][j] = '-';
                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    if(board[x][y] == '-')
    {
        if(turn % 2 == 1)
            board[x][y] = 'X';
        else
            board[x][y] = 'O';
    }
}

void user_move(int turn)
{
    int i, j, pos;
    cout << "Turn : " << turn << "\nYour move." <<endl;
    cout << "Enter a position : ";
    cin >> pos;
    i = (pos - 1) / 3;
    j = (pos - 1) % 3;
    if(0 <= i && i <= 2 && 0 <= j && j <= 2)
    {
        if(board[i][j] == '-')
        {
            if(turn % 2 == 1)
                board[i][j] = 'X';
            else
                board[i][j] = 'O';
        }
        else
        {
            cout << "Position already filled!!" << endl;
            user_move(turn);
        }
    }
    else
    {
        cout << "Enter a valid position!!" << endl;
        user_move(turn);
    }
}

int main()
{
    int turn = 1, move = 1;
    for(int i = 0; i < 3 ; i++)
    {
        for(int j = 0; j < 3 ; j++)
        {
            board[i][j] = '-';
        }
    }
    display_board(board);
    char play = 'n';
    cout << "Do you want to play first?"<<endl;
    cout << "Enter Y to play first : ";
    cin >> play;
    cout << "\n";
    if(play == 'y' || play == 'Y')
    {
        while(turn <= 9)
        {
            user_move(turn);
            display_board(board);
            if(turn % 2 == 1 && check_win())
            {
                cout<<"Congratulations, YOU WON!!"<<endl;
                break;
            }
            turn++, move++;
            if(turn > 9)
                break;
            comp_move(turn, move);
            display_board(board);
            if(turn % 2 == 0 && check_win())
            {
                cout<<"Computer is the winner!! \nBetter luck next time"<<endl;
                break;
            }
            turn++, move++;
        }
    }
    else
    {
        while(turn <= 9)
        {
            comp_move(turn, move);
            display_board(board);
            if(turn % 2 == 1 && check_win())
            {
                cout<<"Computer is the winner!! \nBetter luck next time"<<endl;
                break;
            }
            turn++, move++;
            if(turn > 9)
                break;
            user_move(turn);
            display_board(board);
            if(turn % 2 == 0 && check_win())
            {
                cout<<"Congratulations, YOU WON!!"<<endl;
                break;
            }
            turn++, move++;
        }
    }
    cout<<"GAME OVER!!\n";
    if(!check_win())
        cout<<"It's a DRAW!!\n";
    cout<<"The minmax algorithm was called "<<counter<<" number of times."<<endl;
    // getch();
}