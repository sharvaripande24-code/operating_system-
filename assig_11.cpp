// Implement FIFO, LRU and Optimal Page Replacement Algorithm

#include<iostream>
using namespace std;

int main()
{
    int n;

    cout << "Enter Length of Page Reference String: ";
    cin >> n;

    int pages[50];

    cout << "\nEnter Page Reference String:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }

    int frames;

    cout << "\nEnter Number of Frames: ";
    cin >> frames;

    // =====================================================
    // FIFO PAGE REPLACEMENT
    // =====================================================

    cout << "\n\n===== FIFO PAGE REPLACEMENT =====\n";

    int fifo[20];

    for(int i = 0; i < frames; i++)
    {
        fifo[i] = -1;
    }

    int fifoFault = 0;
    int fifoHit = 0;

    int index = 0;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        // check page hit
        for(int j = 0; j < frames; j++)
        {
            if(fifo[j] == pages[i])
            {
                found = 1;
                fifoHit++;

                break;
            }
        }

        // page fault
        if(found == 0)
        {
            fifo[index] = pages[i];

            index = (index + 1) % frames;

            fifoFault++;

            cout << "\nPF ";
        }
        else
        {
            cout << "\nHit ";
        }

        // display frames
        cout << " -> ";

        for(int j = 0; j < frames; j++)
        {
            if(fifo[j] != -1)
            {
                cout << fifo[j] << " ";
            }
        }
    }

    cout << "\n\nTotal Page Faults = "
         << fifoFault;

    cout << "\nTotal Hits = "
         << fifoHit;

    cout << "\nHit Ratio = "
         << (float)fifoHit / n;

    // =====================================================
    // LRU PAGE REPLACEMENT
    // =====================================================

    cout << "\n\n===== LRU PAGE REPLACEMENT =====\n";

    int lru[20];
    int recent[20];

    for(int i = 0; i < frames; i++)
    {
        lru[i] = -1;
    }

    int lruFault = 0;
    int lruHit = 0;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        // check hit
        for(int j = 0; j < frames; j++)
        {
            if(lru[j] == pages[i])
            {
                found = 1;

                lruHit++;

                recent[j] = i;

                break;
            }
        }

        // page fault
        if(found == 0)
        {
            int empty = -1;

            // find empty frame
            for(int j = 0; j < frames; j++)
            {
                if(lru[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            // empty frame available
            if(empty != -1)
            {
                lru[empty] = pages[i];

                recent[empty] = i;
            }
            else
            {
                // replace least recently used
                int least = 0;

                for(int j = 1; j < frames; j++)
                {
                    if(recent[j] < recent[least])
                    {
                        least = j;
                    }
                }

                lru[least] = pages[i];

                recent[least] = i;
            }

            lruFault++;

            cout << "\nPF ";
        }
        else
        {
            cout << "\nHit ";
        }

        // display frames
        cout << " -> ";

        for(int j = 0; j < frames; j++)
        {
            if(lru[j] != -1)
            {
                cout << lru[j] << " ";
            }
        }
    }

    cout << "\n\nTotal Page Faults = "
         << lruFault;

    cout << "\nTotal Hits = "
         << lruHit;

    cout << "\nHit Ratio = "
         << (float)lruHit / n;

    // =====================================================
    // OPTIMAL PAGE REPLACEMENT
    // =====================================================

    cout << "\n\n===== OPTIMAL PAGE REPLACEMENT =====\n";

    int optimal[20];

    for(int i = 0; i < frames; i++)
    {
        optimal[i] = -1;
    }

    int optimalFault = 0;
    int optimalHit = 0;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        // check hit
        for(int j = 0; j < frames; j++)
        {
            if(optimal[j] == pages[i])
            {
                found = 1;

                optimalHit++;

                break;
            }
        }

        // page fault
        if(found == 0)
        {
            int empty = -1;

            // find empty frame
            for(int j = 0; j < frames; j++)
            {
                if(optimal[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            // empty frame
            if(empty != -1)
            {
                optimal[empty] = pages[i];
            }
            else
            {
                int farthest = -1;
                int replaceIndex = -1;

                // check future use
                for(int j = 0; j < frames; j++)
                {
                    int k;

                    for(k = i + 1; k < n; k++)
                    {
                        if(optimal[j] == pages[k])
                        {
                            if(k > farthest)
                            {
                                farthest = k;

                                replaceIndex = j;
                            }

                            break;
                        }
                    }

                    // page never used again
                    if(k == n)
                    {
                        replaceIndex = j;

                        break;
                    }
                }

                optimal[replaceIndex] = pages[i];
            }

            optimalFault++;

            cout << "\nPF ";
        }
        else
        {
            cout << "\nHit ";
        }

        // display frames
        cout << " -> ";

        for(int j = 0; j < frames; j++)
        {
            if(optimal[j] != -1)
            {
                cout << optimal[j] << " ";
            }
        }
    }

    cout << "\n\nTotal Page Faults = "
         << optimalFault;

    cout << "\nTotal Hits = "
         << optimalHit;

    cout << "\nHit Ratio = "
         << (float)optimalHit / n;

    return 0;
}