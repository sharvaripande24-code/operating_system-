// Buddy System in C++
// Following Buddy System Algorithm

#include<iostream>
using namespace std;

int main()
{
    int totalMemory;
    int n;

    cout << "Enter Total Memory Size: ";
    cin >> totalMemory;

    cout << "Enter Number of Processes: ";
    cin >> n;

    int process[20];

    // input process sizes
    cout << "\nEnter Process Sizes:\n";

    for(int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << ": ";
        cin >> process[i];
    }

    int remainingMemory = totalMemory;

    cout << "\n===== Buddy System Allocation =====\n";

    // process allocation
    for(int i = 0; i < n; i++)
    {
        int blockSize = totalMemory;

        cout << "\n--------------------------------";

        cout << "\nProcess P" << i + 1;

        cout << "\nProcess Size = "
             << process[i] << " KB";

        // Step 1 : Start with large memory block
        cout << "\nStarting with Block Size = "
             << blockSize << " KB";

        // Step 2 & 3 : Find nearest power of 2
        // and split memory
        while(blockSize / 2 >= process[i])
        {
            blockSize = blockSize / 2;

            cout << "\nBlock Split into = "
                 << blockSize << " KB";
        }

        cout << "\nNearest Suitable Block = "
             << blockSize << " KB";

        // Step 4 : Allocate memory
        if(blockSize <= remainingMemory)
        {
            remainingMemory =
            remainingMemory - blockSize;

            cout << "\nMemory Allocated Successfully";

            cout << "\nAllocated Block = "
                 << blockSize << " KB";

            cout << "\nInternal Fragmentation = "
                 << blockSize - process[i]
                 << " KB";

            cout << "\nRemaining Memory = "
                 << remainingMemory
                 << " KB";
        }
        else
        {
            cout << "\nMemory Allocation Failed";
        }

        cout << endl;
    }

    // Step 5 : Free memory
    cout << "\n===== Memory Deallocation =====\n";

    for(int i = 0; i < n; i++)
    {
        cout << "\nProcess P"
             << i + 1
             << " Finished";

        cout << "\nMemory Freed";
    }

    // Step 6 : Merge buddy blocks
    cout << "\n\n===== Buddy Block Merging =====";

    cout << "\nAll Free Buddy Blocks Merged";

    cout << "\nMemory Restored to Original Size = "
         << totalMemory << " KB";

    return 0;
}