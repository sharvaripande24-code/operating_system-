// Implement Disk Scheduling Algorithms
// FCFS, SSTF, SCAN and C-SCAN

#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
    int n;

    cout << "Enter Number of Disk Requests: ";
    cin >> n;

    int request[50];

    cout << "\nEnter Disk Request Queue:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> request[i];
    }

    int head;

    cout << "\nEnter Initial Head Position: ";
    cin >> head;

    // =====================================================
    // FCFS DISK SCHEDULING
    // =====================================================

    cout << "\n\n===== FCFS Disk Scheduling =====\n";

    int current = head;
    int totalMovement = 0;

    cout << "\nHead Movement:\n";

    for(int i = 0; i < n; i++)
    {
        cout << current
             << " -> "
             << request[i]
             << endl;

        // calculate movement
        if(current > request[i])
        {
            totalMovement =
            totalMovement +
            (current - request[i]);
        }
        else
        {
            totalMovement =
            totalMovement +
            (request[i] - current);
        }

        current = request[i];
    }

    cout << "\nTotal Head Movement = "
         << totalMovement;

    // =====================================================
    // SSTF DISK SCHEDULING
    // =====================================================

    cout << "\n\n===== SSTF Disk Scheduling =====\n";

    int visited[50] = {0};

    current = head;

    totalMovement = 0;

    cout << "\nHead Movement:\n";

    for(int i = 0; i < n; i++)
    {
        int minDistance = 9999;
        int index = -1;

        // find nearest request
        for(int j = 0; j < n; j++)
        {
            if(visited[j] == 0)
            {
                int distance;

                if(current > request[j])
                {
                    distance =
                    current - request[j];
                }
                else
                {
                    distance =
                    request[j] - current;
                }

                if(distance < minDistance)
                {
                    minDistance = distance;

                    index = j;
                }
            }
        }

        visited[index] = 1;

        cout << current
             << " -> "
             << request[index]
             << endl;

        // calculate movement
        if(current > request[index])
        {
            totalMovement =
            totalMovement +
            (current - request[index]);
        }
        else
        {
            totalMovement =
            totalMovement +
            (request[index] - current);
        }

        current = request[index];
    }

    cout << "\nTotal Head Movement = "
         << totalMovement;

    // =====================================================
    // SCAN DISK SCHEDULING
    // =====================================================

    cout << "\n\n===== SCAN Disk Scheduling =====\n";

    int scan[50];

    for(int i = 0; i < n; i++)
    {
        scan[i] = request[i];
    }

    sort(scan, scan + n);

    current = head;

    totalMovement = 0;

    cout << "\nHead Movement:\n";

    int pos;

    // find position
    for(pos = 0; pos < n; pos++)
    {
        if(scan[pos] >= head)
        {
            break;
        }
    }

    // move right
    for(int i = pos; i < n; i++)
    {
        cout << current
             << " -> "
             << scan[i]
             << endl;

        if(current > scan[i])
        {
            totalMovement =
            totalMovement +
            (current - scan[i]);
        }
        else
        {
            totalMovement =
            totalMovement +
            (scan[i] - current);
        }

        current = scan[i];
    }

    // move left
    for(int i = pos - 1; i >= 0; i--)
    {
        cout << current
             << " -> "
             << scan[i]
             << endl;

        if(current > scan[i])
        {
            totalMovement =
            totalMovement +
            (current - scan[i]);
        }
        else
        {
            totalMovement =
            totalMovement +
            (scan[i] - current);
        }

        current = scan[i];
    }

    cout << "\nTotal Head Movement = "
         << totalMovement;

    // =====================================================
    // C-SCAN DISK SCHEDULING
    // =====================================================

    cout << "\n\n===== C-SCAN Disk Scheduling =====\n";

    int cscan[50];

    for(int i = 0; i < n; i++)
    {
        cscan[i] = request[i];
    }

    sort(cscan, cscan + n);

    current = head;

    totalMovement = 0;

    cout << "\nHead Movement:\n";

    // find position
    for(pos = 0; pos < n; pos++)
    {
        if(cscan[pos] >= head)
        {
            break;
        }
    }

    // move right
    for(int i = pos; i < n; i++)
    {
        cout << current
             << " -> "
             << cscan[i]
             << endl;

        if(current > cscan[i])
        {
            totalMovement =
            totalMovement +
            (current - cscan[i]);
        }
        else
        {
            totalMovement =
            totalMovement +
            (cscan[i] - current);
        }

        current = cscan[i];
    }

    // jump to beginning
    if(pos > 0)
    {
        cout << current
             << " -> "
             << cscan[0]
             << " (Jump)"
             << endl;

        if(current > cscan[0])
        {
            totalMovement =
            totalMovement +
            (current - cscan[0]);
        }
        else
        {
            totalMovement =
            totalMovement +
            (cscan[0] - current);
        }

        current = cscan[0];
    }

    // continue remaining requests
    for(int i = 0; i < pos; i++)
    {
        cout << current
             << " -> "
             << cscan[i]
             << endl;

        if(current > cscan[i])
        {
            totalMovement =
            totalMovement +
            (current - cscan[i]);
        }
        else
        {
            totalMovement =
            totalMovement +
            (cscan[i] - current);
        }

        current = cscan[i];
    }

    cout << "\nTotal Head Movement = "
         << totalMovement;

    return 0;
}

//Head Movement=∣Current Position−Requested Track∣