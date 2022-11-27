#include <bits/stdc++.h>
using namespace std;

bool isValidSudoku(vector<vector<char>>&);
bool isFull(vector<vector<char>>&);
void print(vector<vector<char>>&);
bool solve(vector<vector<char>>&);
void solveSudoku(vector<vector<char>>&grid){
  solve(grid);
}

int main(){

vector<vector<char>>grid = 
{{'5','3','.','.','7','.','.','.','.'}
,{'6','.','.','1','9','5','.','.','.'}
,{'.','9','8','.','.','.','.','6','.'}
,{'8','.','.','.','6','.','.','.','3'}
,{'4','.','.','8','.','3','.','.','1'}
,{'7','.','.','.','2','.','.','.','6'}
,{'.','6','.','.','.','.','2','8','.'}
,{'.','.','.','4','1','9','.','.','5'}
,{'.','.','.','.','8','.','.','7','9'}};
vector<vector<char>>grid_c(grid);

  cout<<"\nHEY THERE WELCOME TO SUDOKU GAME LETS PLAY :-> \n";
  while (!(isFull(grid))){
     cout<<"\nJUST TYPE THE ROW AND COLUMN WHERE YOU WANT TO ADD A NEW NUMBER\n";
     char first,second,number;
     cout<<"ENTER THE ROW FROM (1-9):";
     cin>>first;
     getchar();
     cout<<"ENTER THE COLUMN FROM (1-9):";
     cin>>second;
     getchar();
     cout<<"ENTER THE NUMBER BETWEEN 1 TO 9 THAT YOU WANT TO ADD :";
     cin>>number;
     getchar();
     if(number<'1'||number>'9'||first<'1'||first>'9'||second<'1'||second>'9'){
     cout<<"THERE IS SOME ERROR IN YOUR INPUT PLEASE CHECK AGAIN \n";
      continue;
     }
     int f = first-48;
     int s = second-48;
     if(grid[f-1][s-1]=='.'){
        grid[f-1][s-1]=number;
        if(isValidSudoku(grid)){
          cout<<"CONGRATS YOUR INPUT WAS SUCCESSFULL\n";
        }else{
           cout<<"ACTUALLY THE NUMBER YOU ENTERED IS AGAINST THE RULES OF SUDOKU\n";
           cout<<"DO YOU WANT TO ENTER THE NUMBER AUTOMATICALLY PRESS Y OR N\n";
           char a;
           cin>>a;
           getchar();
           if(a=='y'||a=='Y'){
            bool check = false;
            for (int i = 1; i <= 9; i++){
              grid[f-1][s-1]=char(i+48);
              if(isValidSudoku(grid)){
                check = true;
                cout<<"SO THE NUMBER INSERTED IS : "<<i<<"\n";
                break;
              }
            }
            if(check==false){
              cout<<"IT SEEMS LIKE YOU MESSED UP IN THE PAST DO YOU WANT COMPUTER TO SOLVE";
              cout<< "THE SUDOKU FOR YOU Y OR N \n";
              char chk;
              cin>>chk;
              getchar();
              if(chk=='Y'||chk=='y'){
                solveSudoku(grid_c);
                print(grid_c);
                cout<<"NOW TRY AGAIN AS YOU KNOW THE SOLUTION :)\n";
                exit(0);
              }
              else {
                cout<<"GAME OVER\n";
                exit(0);
              }
            }
           }
           else continue;
        }
     }
     else{
        cout<<"\nSORRY BUT SOME NUMBER IS ALREADY PRESENT IN THE GIVEN COORDINATES \n";
        print(grid);
        continue;
     }
      print(grid);
  }
  cout<<"\nCONGRATS YOU DID IT :)\n";
}

/***********************function to check whether the input is valid or not*******************************/

bool check(int a, int b, vector<vector<char>> &board){
  unordered_map<char, int> arr;
  for (int i = a; i < a + 3; i++){
    for (int j = b; j < b + 3; j++){
      if (board[i][j] < '1' || board[i][j] > '9')continue;
      if (arr[board[i][j]] == 0)arr[board[i][j]]++;
      else return false;
    }
  }
  return true;
}

bool isValidSudoku(vector<vector<char>> &board){
  for (int i = 0; i < 9; i++){
    unordered_map<char, int> arr;
    for (int j = 0; j < 9; j++){
      if (board[i][j] < '1' || board[i][j] > '9')continue;
      if (arr[board[i][j]] == 0)arr[board[i][j]]++;
      else return false;
    }
  }

  for (int j = 0; j < 9; j++){
    unordered_map<char, int> arr;
    for (int i = 0; i < 9; i++){
      if (board[i][j] < '1' || board[i][j] > '9')continue;
      if (arr[board[i][j]] == 0)arr[board[i][j]]++;
      else return false;
    }
  }

  for (int i = 0; i <= 6; i += 3){
    for (int j = 0; j <= 6; j += 3){
      if (!check(i, j, board))
        return false;
    }
  }
  return true;
}

/**************************check if the grid is full or not***************************/

bool isFull(vector<vector<char>>&board){
  int cnt = 0;
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if(board[i][j]>='1'&&board[i][j]<='9')cnt++;
    }
  }
  if(cnt==81)return true;
  return false;
}

/******************************printing the sudoku grid**********************************/

void print(vector<vector<char>>&board){
  for (int i = 0; i < 13; i++)cout<<"##";
  cout<<"\n";
  for (int i = 0; i < 9; i++){
    cout<<"#|";
    for (int j = 0; j < 9; j++){
      cout<<board[i][j]<<" ";
       if(j==2||j==5)cout<<"| ";
    }
    cout<<"|#\n";
    if(i==2||i==5){
      cout<<"#|";
      for (int i = 0; i < 11; i++)cout<<"--";
      cout<<"|#\n";
    }
  }
   for (int i = 0; i < 13; i++)cout<<"##";
   cout<<"\n";
}

/******************************Automatic solver*********************************/
bool isValid(vector<vector<char>>& board , int row , int col , char c) {
   for (int i = 0; i < 9; i++){
      if(board[row][i]==c)return false;
      if(board[i][col]==c)return false;
      if(board[3*(row/3)+i/3][3*(col/3)+i%3]==c)return false;
   }
   return true;
}

bool solve(vector<vector<char>>& board){
   for (int i = 0; i < board.size(); i++){
      for (int j = 0; j < board[0].size(); j++){
         if(board[i][j]=='.'){
            for (char c = '1'; c <='9'; c++){
                 if(isValid(board,i,j,c)){
                  board[i][j] = c;
                  if(solve(board)==true)return true;
                  else board[i][j] = '.';
                 }
            }
            return false;            
         }
      } 
   }
   return true;
}

/******************************some documentation*********************************/

/*vector<char>is used because vector<int> is restricted to numeric digits only

if you want then you can also use the automatic number inserter which is unlocked
only when you enter any invalid number on any row,column

i haven't set any condition to get rid off loop so if you want to exit the code
just close the terminal

you have two options either take the empty vector or either partially filled 
but insert only char value that is  'x' in the vector that you are initiallizing

just take care about the error handling in this.... as i didn't pay that much 
attention to error handling

i haven't tried to make this time efficient as the loop runs only for 81 times
that is 9 X 9 times so it doesn't effect the time complexity of the code

just ignore the spelling mistakes and correct it if you can and if there is 
any other line you can write instead what i have written you can write it by
your self 

vector<vector<char>>grid = 
{{'5','3','.','.','7','.','.','.','.'}
,{'6','.','.','1','9','5','.','.','.'}
,{'.','9','8','.','.','.','.','6','.'}
,{'8','.','.','.','6','.','.','.','3'}
,{'4','.','.','8','.','3','.','.','1'}
,{'7','.','.','.','2','.','.','.','6'}
,{'.','6','.','.','.','.','2','8','.'}
,{'.','.','.','4','1','9','.','.','5'}
,{'.','.','.','.','8','.','.','7','9'}};

if you want intialized input then you can use the above table instead of
vector<vector<char>> grid(9, vector<char>(9,'.'));

here in the automatic sudoku solver recursion is used :)
*/
