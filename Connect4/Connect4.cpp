// Connect4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include<string.h>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

vector<vector<int>> testBoard = { {9,9,9,9,9,9,9,9,9},
                                  {9,8,8,8,8,8,8,8,9},
                                  {9,8,8,8,8,8,8,8,9},
                                  {9,8,8,8,8,1,0,8,9},
                                  {9,8,8,8,1,8,0,8,9},
                                  {9,8,8,1,8,8,0,8,9},
                                  {9,8,8,8,8,8,8,8,9},
                                  {9,9,9,9,9,9,9,9,9}};
const vector<vector<int>> key = { 
                {-1,-1},
                {-1,0},
                {-1,1},
                {0,-1},
                {0,1},
                {1,-1},
                {1,0},
                {1,1}};

vector <int> testPos = { 6,2 };


vector<int> initMove = {1,1};
vector<int> * lastMove = &initMove;

int emptySpace = 8;
int border = 9;
int boardW = 7+2; //TO ACCOUNT FOR BORDERS
int boardH = 6+2; //TO ACCOUNT FOR BORDERS


bool turn = true; //HUMAN = TRUE


int human = 22;
int ai = 22;

bool CheckWin(vector<int> lastMove, vector<vector<int>> *const board, bool* turn) {
    vector <int> win(8, 0);

    //FOR EACH DIRECTION KEY
    for (auto &i : key) {
        
        //GRAB KEY INDEX
        int index = &i - &key[0];    

        //MULTIPLY DIRECTION KEY BY NUMBER OF TIMES THERE IS A VALUE IN THAT DIRECTION FOR PREVIOUS TURN
        while((*board)[(lastMove[0]) + i[0]*(win[index]+1)][(lastMove[1]) + i[1]*(win[index]+1)] == !(*turn) 
            && (*board)[(lastMove[0]) + i[0] * (win[index]+1)][(lastMove[1]) + i[1] * (win[index]+1)] != 9) {
            win[index]++;
        }
    }

 
 // //PREVIEW WIN VECTOR  
 //   for (auto& j : win) {
 //       int index2 = &j - &win[0];
 //       cout << j;
 //       if ( index2 == 2) { cout << endl; }
 //       if (index2 == 4) { cout << endl; }
 //   } cout << endl;

    //CHECK IF BLOCK AND OPPOSITE BLOCK CONNECT 4
    for (int i = 0; i < win.size(); i++) {

        if (win[i] + win[7 - i] > 2) {
            return true;
        }
    }
    return false;
 }

void DisplayBoard(const vector<vector<int>>* const pBoard) {
    
    int H = (*pBoard).size();
    int W = (*pBoard)[0].size();

    for (int i = 1; i < H-1; i++) {
        cout << "|";
        for (int j = 1; j < W-1; j++) {
            if ((*pBoard)[i][j] == 8) { cout << " " << "|"; } else
            cout << (*pBoard)[i][j] << "|";
        }
        cout << endl;
       
    } cout << endl;
}

bool Move(int column, bool *turn, vector<vector<int>>* const pBoard, vector<int> * lastMove){
    int row=0;

    //IF NOT FULL   
    if ((*pBoard)[1][column]==8 ) {

        //increment animation here?

        //GO DOWN UNTIL YOU HIT THE BOTTOM
        while ((*pBoard)[row + 1][column] != 1 && (*pBoard)[row+1][column] != 0 && (*pBoard)[row+1][column] != 9) {
            row++;
        }
        if (*turn) {

            (*pBoard)[row][column] = 1;
        }
        else {
            (*pBoard)[row][column] = 0;
        }
        (*lastMove)[0] = row;
        (*lastMove)[1] = column;

        //CHANGE TURN MOVE
        *turn = !(*turn);
        return true;
    }
    else {
        return false;
    }
}



int main()
{
    int move;
    
    //CREATE BOARD
    vector<vector<int>> board(boardH, vector<int>(boardW, emptySpace));
    for (int i = 0; i < boardH; i++) {
        for (int j = 0; j < boardW; j++) {
            if (j == 0 || i == 0 || i == boardH - 1 || j == boardW - 1) {
                board[i][j] = border;
            }
        }
    }
   
    DisplayBoard(&board);
    while (!(CheckWin((*lastMove), &board, &turn))) {

      cout << "Enter an integer between 1 and 7:";
      cin >> move;

      while (!cin || move <= 1 || move >= 7) {
          cin.clear();    // Restore input stream to working state
          cin.ignore(100, '\n');    // Get rid of any garbage that user might have entered
          cout << "I said enter an integer between 1 and 7, Dumbass.\n"<< "Try again: ";
          cin >> move;
        }

        Move(move, &turn, &board, lastMove);
        DisplayBoard(&board);
    }
    
    if (!(*(&turn))) { //BECAUSE THE TURN IS SWAPPED EACH MOVE WE HAVE TO TAKE THE PREVIOUS TURN
        cout << "HUMAN WINRAR";
    }
    else {
        cout << "CPU WINRAR";
    }
  
}

//TODO IMPLEMENT AI

//TODO CONVERT CHARACTERS INTO FUN SYMBOLS
//TODO ADD DROPPING ANIMATION
//TODO CLEAR THE SCREEN EVERY MOVE
//FUN WIN TEXT

