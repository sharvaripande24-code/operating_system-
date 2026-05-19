/*
Consider the virtual machine with one general purpose register
of 4 bytes, instruction register of 4 bytes, instruction counter
of 2 bytes and toggle register of 1 bit.

The instruction set consists of 7 instructions:
GD, PD, LR, SR, CR, BT and H.

Consider the main memory of 200 words.

Write a program to compare two strings and print whether
the strings are same or not in the input file.

Write the OS code which will load this program from the
input device into the main memory.

Consider block size as 10 words.
*/

#include<iostream>
#include<cstring>

using namespace std;

char M[200][4];
char IR[4];
char R[4];

int IC;

bool C;

char str1[40],str2[40];

void LOAD()
{
    int m=0;

    char program[][4]={
        {'G','D','1','0'},
        {'G','D','2','0'},
        {'L','R','1','0'},
        {'C','R','2','0'},
        {'B','T','0','7'},
        {'P','D','3','0'},
        {'H',' ',' ',' '},
        {'P','D','4','0'},
        {'H',' ',' ',' '}
    };

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<4;j++)
        {
            M[m][j]=program[i][j];
        }

        m++;
    }
}

void MOS(string s1,string s2)
{
    for(int i=0;i<4;i++)
    {
        M[10][i]=s1[i];

        M[20][i]=s2[i];
    }

    M[30][0]='N';
    M[30][1]='O';

    M[40][0]='S';
    M[40][1]='A';
    M[40][2]='M';
    M[40][3]='E';
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

        else if(IR[0]=='C' && IR[1]=='R')
        {
            int addr=(IR[2]-'0')*10+(IR[3]-'0');

            C=true;

            for(int i=0;i<4;i++)
            {
                if(R[i]!=M[addr][i])
                {
                    C=false;

                    break;
                }
            }
        }

        else if(IR[0]=='B' && IR[1]=='T')
        {
            int addr=(IR[2]-'0')*10+(IR[3]-'0');

            if(C)
            {
                IC=addr;
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
    cout<<"Enter First String: ";
    cin>>str1;

    cout<<"Enter Second String: ";
    cin>>str2;

    LOAD();

    MOS(str1,str2);

    EXECUTE();

    return 0;
}
