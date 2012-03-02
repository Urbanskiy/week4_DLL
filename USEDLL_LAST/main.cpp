#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define N 3

using namespace std;

int (*PrintField)(int** matr);       // for import
int (*ComputerTurn)(int ** matr);           // for import
int (*PlayerTurn)(int ** matr, int number); // for import


bool IsGameOver( int**  matr);
bool CheckRow(int ** matr, size_t size);
bool CheckColl(int ** matr, size_t size);
bool CheckDiags(int ** matr, size_t size);

int IsNullMatr(int** matr);             // check if pointer to game field is NULL
int InitializeGameField(int** matr);    // init game field with 0
int ChoseOponent();                     // chose PvP or PvC
int StartGame(int** matr, int oponent); // Start game func until GameOver
void DeAllocateMemory(int** matr);      // free mem

int main()
{

    int i;
    int **matr;
    //-------------------- Load DLL and get handle -----------------
    HINSTANCE mydll;
    mydll = LoadLibrary("TASK_5_DLL.dll");  // load our dll
    if(mydll)
        cout << "Our DLL loaded successful " << endl;
    else
    {
        cout << "Cannot load DLL file TASK_5_DLL.dll" << endl;
        return 1;
    }
    //-------------------- Initialize funcs pointers ---------------
    PrintField =(int (*)(int**const matr)) GetProcAddress(mydll, "PrintField"); // import funcs from DLL
    ComputerTurn =(int(*)(int **)) GetProcAddress(mydll, "ComputerTurn");    // import funcs from DLL
    PlayerTurn = (int(*)(int**, int))GetProcAddress(mydll, "PlayerTurn");    // import funcs from DLL

    //-------------------- Check for loaded functions --------------
    if(PrintField && ComputerTurn && PlayerTurn)
        cout << "Functions from DLL loaded successful " << endl;
    else
    {
        cout << "Cannot load some functions from DLL" << endl;
        return 1;
    }
    //---------------------------------------------------------------

    try
    {
        matr = new int*[N];
        for(i = 0 ; i < N ; i++)
            matr[i] = new int[N];

    }
    catch(bad_alloc)
    {
        cout << "Unable to allocate memory for Game field" << endl;
        return 1;
    }
    //----------------------------------------------------------------
    try
    {
        do
        {
            InitializeGameField(matr);      // initialize game field with zero
            system("CLS");                  // clear screen
            StartGame(matr,ChoseOponent()); // start game and chose oponent ( comp or human)
            cout << "\n To finish game press ESC" << endl;
        }while(getch() != 27);      // play while not escape

        DeAllocateMemory(matr);     // dealocate memory for game field
    }
    catch(const char * exc)
    {
        cout << exc << endl;        // cout catched exceptions
    }
    system("pause");
    return 0;
}
//-------------------- Check for game over------------------------
bool IsGameOver( int** matr)

{
    if ( IsNullMatr(matr) )
    {
        throw "\n Cannot finish game, couse Game field become NULL";
    }
    return (CheckColl(matr,3) || CheckRow(matr,3) || CheckDiags(matr,3));
}
//----------------- Check Rows for game over------------------------
bool CheckRow(int ** matr, size_t size)
{
     if ( !IsNullMatr(matr) )
    {
        for(size_t i = 0; i < size; i++)
        {
            if( (matr[i][0] == matr[i][1] && matr[i][0] == matr[i][2] ) && matr[i][0])
                    return true;
        }
        return false;
    }
}
//------------------Check Cols for gameover-----------------------
bool CheckColl(int ** matr, size_t size)
{
     if ( !IsNullMatr(matr) )
    {
        for(size_t i = 0; i < size; i++)
        {
            if( (matr[0][i] == matr[1][i] && matr[0][i] == matr[2][i] ) && matr[0][i])
                return true;
        }
        return false;
    }
}
//---------------------Check Diags for gameover-------------------------
bool CheckDiags(int ** matr, size_t size)
{
    if ( !IsNullMatr(matr) )
    {
        bool mainD = true,secD = true;
        for(size_t i = 0 ; i < size-1 ; i++)
        {
            if( !matr[i][i]             || (matr[i][i] != matr[i+1][i+1] )) mainD = false;
            if( !matr[i][size - i - 1]  || (matr[i][size - i - 1] != matr[i+1][size - i - 2])) secD = false;
        }
        return (mainD || secD);
    }
}
//------------------------- Check if pointer is NULL ----------------------------
int IsNullMatr(int** matr)
{
    if(matr == NULL)
    {
        cout << "Game field was not created, or is NULL" << endl;
        return 1;
    }
    return 0;
}
//------------------- Init game field in zero ----------------------
int InitializeGameField(int** matr)
{
    if ( IsNullMatr(matr) )
        throw "\n Cannot initialize Game field";

    for(int i = 0 ; i < 3 ; i++)
        for(int j = 0 ; j < 3 ; j++)
            matr[i][j] = 0;
    return 1;
}
//--------------- Start Game until GameOver-----------------------
int StartGame(int** matr, int oponent)
{
    int players = oponent;
    int steps = 0;
    int whoWin = -1;
    if(IsNullMatr(matr))
        throw "\n Cannot start the game";
    do
    {
        system("CLS");
        PrintField(matr);
        PlayerTurn(matr,1);
        steps++;

        if(IsGameOver(matr) && steps >= 5) {whoWin = 1; break;}
        if(steps == 9) {whoWin = 0; break;}

        system("CLS");
        PrintField(matr);
        if(!players)
        {
            ComputerTurn(matr);
            Sleep(1000);        // computer is thinking dont hurry him
        }
        else
            PlayerTurn(matr,2);
        steps++;


    }while(! IsGameOver(matr));
    system("CLS");
    PrintField(matr);

    if(players)
        if(whoWin == 1) cout << "\n PLAYER 1 WIN";
        else if(whoWin == -1) cout << "\n PLAYER 2 WIN";
        else cout << "\n NOBODY WIN" ;
    else
        if(whoWin == 1) cout << "\n PLAYER 1 WIN";
        else if(whoWin == -1) cout << "\n COMPUTER WIN";
        else cout << "\n NOBODY WIN" ;

    return 1;
}
//-------------------- Chose oponent before game --------------------
int ChoseOponent()
{
    int players = 0;
    do
    {
         cout << "Who you wanna play with ( Player VS player - 1, Player VS Comp - 0) ??" <<endl;
         cin >> players;

    }while( !(players >= 0 && players <=1 ));
    return players;
}
//----------------- Deallocate memory of ptr---------------------
void DeAllocateMemory(int** matr)
{
    if(IsNullMatr(matr))
        throw "\n Cannot deallocate memory";
    for(int i = 0; i < 3; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;
    matr = NULL;
}
//---------------------------------------------------------
