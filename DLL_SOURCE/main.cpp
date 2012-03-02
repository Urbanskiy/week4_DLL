#include "main.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


int DLL_EXPORT PrintField(int**  matr)  // print game field
{
    if(IsNullMatr(matr))        // check if ptr is not NULL
    {
        throw "\n Cannot Print Game Field";
    }
    int size = 3;
    for(int i = 0; i < size ; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if( matr[i][j] == -1)
            {
                cout << " O ";
            }
            else if(matr[i][j] == 1)
            {
                cout << " X ";
            }
            else  if(matr[i][j] == 0)
                cout << " _ ";
            else
                return -1;
        }
        cout << endl;
    }
    return 1;
}
//-----------------------------------------------------------
int DLL_EXPORT PlayerTurn(int ** matr,int number)
{
    if(IsNullMatr(matr))
    {
        throw "\n Cannot make player turn";
    }
    int i = 0 , j = 0, value;
    char k;
    if(number == 1)     // if PvP mod number = 2, if PvC nubmer = 1
    {
        value = 1;      // using to fill matrix acording to player #
    }else if(number == 2)
    {
        value = -1;
    }
    cout << "\n[Player #" << number << "]";

    do
    {
        k=getch();
        if(KeybdKeyToIJ(k,i,j))
        if(!matr[i][j] && IsOK_ij(i,j) )
        {
            matr[i][j] = value;
            break;
        }
    }while(1);
    return 1;
}
//---------------------------------------------------------------
int DLL_EXPORT ComputerTurn(int ** matr)
{
     if(IsNullMatr(matr))
    {
        throw "\n Cannot make computer turn";
    }
    int i = 0 , j = 0, value = -1;
    int randI = 0;
    int randJ = 0;
    srand(time(NULL));
    cout << "\n[Computer turn]";
    if(FindBestWay(matr,i,j))       // using func to make game more interesting (AI for comp =) )
    {
        matr[i][j] = value;     // if find good way to move - put zero
    }
    else                        // just random fill if no FindBestWay
    {
        do
        {
          randI = rand()%3;
          randJ = rand()%3;

        }while(matr[randI][randJ]);
         matr[randI][randJ] = value;

    }
}
//---------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
//-----------------------------------------------------------
bool KeybdKeyToIJ(char k,int&i,int &j)  // keybord key ---> coordinates
{
     switch(k)
    {
        case '1': i = 2;j = 0;break;
        case '2':i = 2;j = 1;break;
        case '3':i = 2;j = 2;break;
        case '4':i = 1;j = 0;break;
        case '5':i = 1;j = 1;break;
        case '6':i = 1;j = 2;break;
        case '7':i = 0;j = 0;break;
        case '8':i = 0;j = 1;break;
        case '9':i = 0;j = 2;break;
        default: return false;
    }
    return true;

}
//-----------------------------------------------------------
bool IsOK_ij(int & i , int & j)     // i, j = 0..2 check
{
    if ( ( i >= 0 && i < 3) && (j >=0 && j < 3) )
    {
        return true;
    }
    return false;
}
//-----------------------------------------------------------
bool FindBestWay(int** matr,int & k, int &l)    // some Indian to make computer make turn correctly as player did
{
    if(IsNullMatr(matr))
    {
        throw "\n Cannot find best way";
    }
    int compWinX[] = {-1,-1,-1,-1},compWinY[] = {-1,-1,-1,-1};
    int playWinX = -1,playWinY = -1;
    int i,j;
    int sumR = 0, sumC = 0, sumDmain = 0, sumDsec = 0;
    bool findWay = true;
    for( i = 0; i < 3 ; i++)
    {
        for( j = 0 ; j < 3; j++)
        {
            sumR += matr[i][j];
            if(matr[i][j] == 0) { compWinX[0] = i; compWinY[0] = j; }


            sumC += matr[j][i];
            if(matr[j][i] == 0){ compWinX[1] = j; compWinY[1] = i; }
        }
    //---------------------------------------------------------------
        sumDmain += matr[i][i];
        if(matr[i][i] == 0){ compWinX[2] = i; compWinY[2] = i; }
        sumDsec += matr[i][2-i];
        if(matr[i][2-i] == 0){ compWinX[3] = i; compWinY[3] = 2-i; }
    //---------------------------------------------------------------
        if(sumR == -2 )
        {k = compWinX[0];l = compWinY[0];return true;}
        if(sumC == -2 )
        {k = compWinX[1];l = compWinY[1];return true;}

        if(sumR == 2 && findWay )
        {playWinX = compWinX[0];playWinY = compWinY[0];findWay = false;}
        if(sumC == 2 && findWay)
        {playWinX= compWinX[1];playWinY = compWinY[1];findWay = false;}
    //------------------------------------------------------------------
        for(int a = 0; a < 2; a++)
        {
            compWinX[a] = -1;
            compWinY[a] = -1;
        }
        sumR = sumC = 0;
    }
    if(sumDmain == -2 )
    {k = compWinX[2];l = compWinY[2];return true;}
    if(sumDsec  == -2 )
    {k = compWinX[3];l = compWinY[3];return true;}

    if(sumDmain == 2 )
    {k = compWinX[2];l = compWinY[2];return true;}
    if(sumDsec  == 2 )
    {k = compWinX[3];l = compWinY[3];return true;}
    if(!findWay)
    {
        k = playWinX;
        l = playWinY;
        return true;
    }
    return false;
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
