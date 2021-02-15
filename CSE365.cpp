#include <bits/stdc++.h>
#include <cstdlib>
#include <cmath>
#include <ctime>
#define size 8

using namespace std;

void simulated_annealing(int current[8][8]); //function to apply the simulated annealing algorithm
void gen_successor(int present[8][8],int neighbor[8][8]); //function to generate successor
int attacking_pairs(int board[8][8]); //function to calculate # of attacking pairs queen
void assign_board(int present[8][8], int target[8][8]); //function to assign a board to another
void print_board(int board[8][8]); //function to print a board

int main()
{
    int a,b,i,j;

    int random_board[8][8]={
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0}
};

/*    int** random_board= (int**)malloc((size+1)*sizeof(int*)); //allocating memory row-wise
    for(int i=1; i<=size; ++i)
        random_board[i]= (int*)malloc((size+1)*sizeof(int)); //allocating memory column-wise

    for(int i=1; i<=size; ++i) //initializing the board to be empty
        for(int j=1; j<=size; ++j)
            random_board[i][j]=0;
*/
    for(int i=1; i<=8; ++i) //to place 8-queens randomly
    {
        a= rand() %8 +1;
        b= rand() %8 +1;
        if(random_board[a][b]==1)
            i--;
        random_board[a][b]=1;
    }

    cout<<"\nThe random board is: "<<endl;
    print_board(random_board);
    cout<<endl<<"\tAttacking pairs: "<<attacking_pairs(random_board)<<endl;

    simulated_annealing(random_board); //applying simulated annealing algorithm to the random board

    return 0;
}

void simulated_annealing(int current[8][8])
{
    double T= 100.0;
    double dE;
    double pro;
    double ran;
    int currAttPairs;
    int nextAttPairs;


   int next[8][8]=
 {
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0, 0, 0, 0}
};
  /*
    int** next;
    next= (int**)malloc((size+1)*sizeof(int*)); //allocating memory row-wise
    for(int i=1; i<=size; ++i)
        next[i]= (int*)malloc((size+1)*sizeof(int)); //allocating memory column-wise       */

    while(true)
    {
                cout<<"T         "<<T<<endl<<endl;

        if(T<0)         //--------------------change was made here
            break;
        gen_successor(current,next); //generating a successor //another neighbour random_board generate
        currAttPairs= attacking_pairs(current); // return count how?
        nextAttPairs= attacking_pairs(next);
        if(currAttPairs==0)
        {//cout<<"Iteration Needed:"<<100-T<<endl;
       break;
        }
        dE= currAttPairs-nextAttPairs;    //difference between current and next // attracking pair jar kom se valo
        if(dE>=0)
           {
          assign_board(next,current); //make next state as a current state
           }
        else
        {
            pro= exp(dE/T);
            //ran= rand_ZeroToOne(); //generating a random number between 0 and 1
            if(0.80<pro)     //if less than 50% do nothing
                assign_board(next,current);
        }
        T-=0.5;  // decrement by 0.5
    }

    cout<<endl<<"The corrected board: "<<endl<<endl;
    print_board(current);
    cout<<"\tAttacking pairs: "<<currAttPairs<<endl;
}

void gen_successor(int present[8][8], int neighbor[8][8])
{
    assign_board(present,neighbor); //assigning present board to neighbor
    int x= rand() %8 +1; //random generation of position
    int y= rand() %8 +1;
    if(neighbor[x][y]==0) //condition to identify if the position contains a queen
    {
        gen_successor(present, neighbor); //recursive call of the function
        return; //recursive 1 bar execute hoyer por return.
    }
    else
    {
        int x1= (x%8) +1; //like [1][1] hav queen so [x1][y1]=[2][2]
        int y1= (y%8) +1; //calculating position to find successor
        if(neighbor[x1][y1]==1)
        {
            gen_successor(present, neighbor); //recursive call of the function
            return;
        }
        else //condition to generate a successor
        {   neighbor[x1][y1]=1;
            neighbor[x][y]=0;
        }
    }
}

int attacking_pairs(int board[8][8])
{
    int count=0;
    for(int j=1; j<=8; ++j)
    {
        for(int i=1; i<=8; ++i)
        {
            if(board[i][j]==1) //condition to find queen in a position
            {
                for(int k=i+1; k<=size; ++k) //to check pairs row-wise
                {
                    if(board[k][j]==1)
                    {
                        count++;
                        break;
                    }
                }
                for(int k=j+1; k<=size; ++k) //to check pairs column-wise
                {
                    if(board[i][k]==1)
                    {
                        count++;
                        break;
                    }
                }
                for(int m=i+1,n=j+1; m<=size && n<=size; ++m,++n) //to check pairs upper diagonally//[3][3] pos [4][4]
                {
                    if(board[m][n]==1)
                    {
                        count++;
                        break;
                    }
                }
                for(int m=i-1,n=j+1; m>=1 && n<=size; --m,++n) //to check pairs lower diagonally// [3][3] pos [2][4]
                {
                    if(board[m][n]==1)
                    {
                        count++;
                        break;
                    }
                }
            }
        }
    }
    return count;
}

void assign_board(int present[8][8],int target[8][8]) // (next,current)
{
    for(int i=1; i<=size; ++i)
        for(int j=1; j<=size; ++j)
            target[i][j]= present[i][j]; // current[i][j]=next[i][j]
}



void print_board(int board[8][8])
{
    cout<<"\n";
    for(int i=1;i<=size;++i)
    {
        cout<<"\t";
        for(int j=1;j<=size;++j)
            cout<<board[i][j]<<"   ";
        cout<<endl<<endl;
    }
}
