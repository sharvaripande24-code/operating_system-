/*
Consider the virtual machine with one general purpose register
of 4 bytes, instruction register of 4 bytes,
instruction counter of 2 bytes and toggle register of 1 bit.

The instruction set consists of 7 instructions:
GD, PD, LR, SR, CR, BT and H.

Consider the main memory of 400 words.

Write a program to print welcome message in the input file.

Write the OS code which will load this program
from the input device into the main memory using paging.

Consider the page size as 10 words.
*/

#include<iostream>
#include<cstdlib>

using namespace std;

char M[400][4];

char IR[4];

char R[4];

int IC;

int PTR;

int pageTable[10];

void allocate()
{
    for(int i=0;i<10;i++)
    {
        pageTable[i]=rand()%30;
    }
}

int addressMap(int VA)
{
    int p=VA/10;

    int d=VA%10;

    int frame=pageTable[p];

    return frame*10+d;
}

void LOAD()
{
    char program[][4]={
        {'G','D','1','0'},
        {'P','D','2','0'},
        {'H',' ',' ',' '}
    };

    allocate();

    for(int i=0;i<3;i++)
    {
        int RA=addressMap(i);

        for(int j=0;j<4;j++)
        {
            M[RA][j]=program[i][j];
        }
    }

    int dataAddr=addressMap(20);

    M[dataAddr][0]='W';
    M[dataAddr][1]='E';
    M[dataAddr][2]='L';
    M[dataAddr][3]='C';

    M[dataAddr+1][0]='O';
    M[dataAddr+1][1]='M';
    M[dataAddr+1][2]='E';
    M[dataAddr+1][3]=' ';
}

void EXECUTE()
{
    IC=0;

    while(true)
    {
        int RA=addressMap(IC);

        for(int i=0;i<4;i++)
        {
            IR[i]=M[RA][i];
        }

        IC++;

        if(IR[0]=='G' && IR[1]=='D')
        {
            continue;
        }

        else if(IR[0]=='P' && IR[1]=='D')
        {
            int addr=(IR[2]-'0')*10+(IR[3]-'0');

            int realAddr=addressMap(addr);

            for(int i=0;i<2;i++)
            {
                for(int j=0;j<4;j++)
                {
                    cout<<M[realAddr+i][j];
                }
            }

            cout<<endl;
        }

        else if(IR[0]=='H')
        {
            break;
        }
    }
}

int main()
{
    LOAD();

    EXECUTE();

    return 0;
}
