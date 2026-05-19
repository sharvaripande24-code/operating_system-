// Implement First Fit, Best Fit, Next Fit and Worst Fit

#include<iostream>
using namespace std;

int main()
{
    int nb, np;

    cout << "Enter number of memory blocks: ";
    cin >> nb;

    cout << "Enter number of processes: ";
    cin >> np;

    int block[20];
    int process[20];

    int i, j;

    // Input memory blocks
    cout << "\nEnter memory block sizes:\n";

    for(i = 0; i < nb; i++)
    {
        cin >> block[i];
    }

    // Input process sizes
    cout << "\nEnter process sizes:\n";

    for(i = 0; i < np; i++)
    {
        cin >> process[i];
    }

    // ---------------- FIRST FIT ----------------

    cout << "\n===== FIRST FIT =====\n";

    int firstBlock[20];

    for(i = 0; i < nb; i++)
    {
        // Copy original blocks
        firstBlock[i] = block[i];
    }

    for(i = 0; i < np; i++)
    {
        int allocated = 0;

        for(j = 0; j < nb; j++)
        {
            if(firstBlock[j] >= process[i])
            {
                cout << "Process " << i+1
                     << " allocated to Block "
                     << j+1 << endl;

                firstBlock[j] =
                firstBlock[j] - process[i];

                allocated = 1;

                break;
            }
        }

        if(allocated == 0)
        {
            cout << "Process " << i+1
                 << " not allocated\n";
        }
    }

    // Updated block size
    cout << "\nUpdated block size :\n";

    for(i = 0; i < nb; i++)
    {
        cout << "Block " << i+1
             << " = "
             << firstBlock[i] << endl;
    }

    // ---------------- BEST FIT ----------------

    cout << "\n===== BEST FIT =====\n";

    int bestBlock[20];

    for(i = 0; i < nb; i++)
    {
        bestBlock[i] = block[i];
    }

    for(i = 0; i < np; i++)
    {
        int best = -1;

        for(j = 0; j < nb; j++)
        {
            if(bestBlock[j] >= process[i])
            {
                if(best == -1 ||
                   bestBlock[j] < bestBlock[best])
                {
                    best = j;
                }
            }
        }

        if(best != -1)
        {
            cout << "Process " << i+1
                 << " allocated to Block "
                 << best+1 << endl;

            bestBlock[best] =
            bestBlock[best] - process[i];
        }
        else
        {
            cout << "Process " << i+1
                 << " not allocated\n";
        }
    }

    // Updated block size
    cout << "\nUpdated block size :\n";

    for(i = 0; i < nb; i++)
    {
        cout << "Block " << i+1
             << " = "
             << bestBlock[i] << endl;
    }

    // ---------------- NEXT FIT ----------------

    cout << "\n===== NEXT FIT =====\n";

    int nextBlock[20];

    for(i = 0; i < nb; i++)
    {
        nextBlock[i] = block[i];
    }

    int last = 0;

    for(i = 0; i < np; i++)
    {
        int allocated = 0;

        for(j = 0; j < nb; j++)
        {
            int index = (last + j) % nb;

            if(nextBlock[index] >= process[i])
            {
                cout << "Process " << i+1
                     << " allocated to Block "
                     << index+1 << endl;

                nextBlock[index] =
                nextBlock[index] - process[i];

                last = index;

                allocated = 1;

                break;
            }
        }

        if(allocated == 0)
        {
            cout << "Process " << i+1
                 << " not allocated\n";
        }
    }

    // Updated block size
    cout << "\nUpdated block size :\n";

    for(i = 0; i < nb; i++)
    {
        cout << "Block " << i+1
             << " = "
             << nextBlock[i] << endl;
    }

    // ---------------- WORST FIT ----------------

    cout << "\n===== WORST FIT =====\n";

    int worstBlock[20];

    for(i = 0; i < nb; i++)
    {
        worstBlock[i] = block[i];
    }

    for(i = 0; i < np; i++)
    {
        int worst = -1;

        for(j = 0; j < nb; j++)
        {
            if(worstBlock[j] >= process[i])
            {
                if(worst == -1 ||
                   worstBlock[j] > worstBlock[worst])
                {
                    worst = j;
                }
            }
        }

        if(worst != -1)
        {
            cout << "Process " << i+1
                 << " allocated to Block "
                 << worst+1 << endl;

            worstBlock[worst] =
            worstBlock[worst] - process[i];
        }
        else
        {
            cout << "Process " << i+1
                 << " not allocated\n";
        }
    }

    // Updated block size
    cout << "\nUpdated block size :\n";

    for(i = 0; i < nb; i++)
    {
        cout << "Block " << i+1
             << " = "
             << worstBlock[i] << endl;
    }

    return 0;
}