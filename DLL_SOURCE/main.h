#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif


int DLL_EXPORT ComputerTurn(int**);
int DLL_EXPORT PlayerTurn(int** , int );
int DLL_EXPORT PrintField(int** matr);

bool FindBestWay(int** ,int & , int &);
bool KeybdKeyToIJ(char ,int&,int &);
bool IsOK_ij(int &  , int & );
int IsNullMatr(int**);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
