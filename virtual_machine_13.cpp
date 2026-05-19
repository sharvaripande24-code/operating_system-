/*
Consider the virtual machine with one general purpose register
of 4 bytes, instruction register of 4 bytes, instruction counter
of 2 bytes and toggle register of 1 bit.

The instruction set consists of 7 instructions:
GD, PD, LR, SR, CR, BT and H.

Consider the main memory of 200 words.

Add any arithmetic instruction in the given instruction set.
Write a program using the new instruction.

Write the OS code demonstrating execution of this program.
[Assume the program is already loaded in the main memory]
*/

#include<iostream>

using namespace std;

char M[200][4];

char IR[4];

char R[4];

int IC;

int value1=5;
int value2=3;

void LOAD()
{
    char program[][4]={
        {'G','D','1','0'},
        {'G','D','2','0'},
        {'L','R','1','0'},
        {'A','D','2','0'},
        {'S','R','3','0'},
        {'P','D','3','0'},
        {'H',' ',' ',' '}
    };

    for(int i=0;i<7;i++)
    {
        for(int j=0;j<4;j++)
        {
            M[i][j]=program[i][j];
        }
    }
}

void MOS()
{
    M[10][0]=value1+'0';

    M[20][0]=value2+'0';
}

void EXECUTE()
{
    IC=0;

    while(true)
    {
        for(int i=0;i<4;i++)
        {
            IR[i]=M[IC][i];
        }

        IC++;

        if(IR[0]=='G' && IR[1]=='D')
        {
            continue;
        }

        else if(IR[0]=='L' && IR[1]=='R')
        {
            int addr=(IR[2]-'0')*10+(IR[3]-'0');

            for(int i=0;i<4;i++)
            {
                R[i]=M[addr][i];
            }
        }

        else if(IR[0]=='A' && IR[1]=='D')
        {
            int addr=(IR[2]-'0')*10+(IR[3]-'0');

            int x=R[0]-'0';

            int y=M[addr][0]-'0';

            int sum=x+y;

            R[0]=sum+'0';
        }

        else if(IR[0]=='S' && IR[1]=='R')
        {
            int addr=(IR[2]-'0')*10+(IR[3]-'0');

            for(int i=0;i<4;i++)
            {
                M[addr][i]=R[i];
            }
        }

        else if(IR[0]=='P' && IR[1]=='D')
        {
            int addr=(IR[2]-'0')*10+(IR[3]-'0');

            for(int i=0;i<4;i++)
            {
                cout<<M[addr][i];
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

    MOS();

    EXECUTE();

    return 0;
}
