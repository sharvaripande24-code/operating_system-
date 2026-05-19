#include <iostream>
using namespace std;

void fcfsmethod(int n, int at[], int bt[], int pid[])
{
    int tat[50], wt[50], ct[50];
    int currtime = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(pid[i], pid[j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (currtime < at[i])
        {
            currtime = at[i];
        }

        ct[i] = currtime + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        currtime = ct[i];
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {
        cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";

        total_tat += tat[i];
        total_wt += wt[i];
    }

    cout << "\nAverage TAT = " << total_tat / n;
    cout << "\nAverage WT = " << total_wt / n << endl;
}

void sjfnonpreemptive(int n, int at[], int bt[], int pid[])
{
    int tat[50], wt[50], ct[50];
    bool completed[50] = {false};

    int currtime = 0, completedcount = 0;

    while (completedcount < n)
    {
        int idx = -1;
        int minBT = 9999;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currtime && !completed[i])
            {
                if (bt[i] < minBT)
                {
                    minBT = bt[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            currtime++;
        }
        else
        {
            ct[idx] = currtime + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            currtime = ct[idx];
            completed[idx] = true;
            completedcount++;
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {
        cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;

        total_tat += tat[i];
        total_wt += wt[i];
    }

    cout << "\nAverage TAT = " << total_tat / n;
    cout << "\nAverage WT = " << total_wt / n << endl;
}

void sjfpreemptive(int n, int at[], int bt[], int pid[])
{
    int wt[50], tat[50], rt[50], ct[50];

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int currtime = 0, completedcount = 0;

    while (completedcount < n)
    {
        int idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currtime && rt[i] > 0)
            {
                if (idx == -1 || rt[i] < rt[idx])
                {
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            currtime++;
        }
        else
        {
            rt[idx]--;
            currtime++;

            if (rt[idx] == 0)
            {
                ct[idx] = currtime;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completedcount++;
            }
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {
        cout << pid[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;

        total_tat += tat[i];
        total_wt += wt[i];
    }

    cout << "\nAverage TAT = " << total_tat / n;
    cout << "\nAverage WT = " << total_wt / n << endl;
}

void roundRobin(int n, int at[], int bt[], int pid[], int tq)
{
    int rt[50], ct[50], tat[50], wt[50];

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int currTime = 0, completed = 0;

    while (completed < n)
    {
        bool executed = false;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currTime && rt[i] > 0)
            {
                executed = true;

                if (rt[i] > tq)
                {
                    currTime += tq;
                    rt[i] -= tq;
                }
                else
                {
                    currTime += rt[i];
                    ct[i] = currTime;

                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    rt[i] = 0;
                    completed++;
                }
            }
        }

        if (!executed)
            currTime++;
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++)
    {
        cout << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;

        totalTAT += tat[i];
        totalWT += wt[i];
    }

    cout << "\nAverage Turnaround Time = " << totalTAT / n;
    cout << "\nAverage Waiting Time = " << totalWT / n << endl;
}

void priorityScheduling(int n, int at[], int bt[], int pid[], int pr[])
{
    int ct[50], tat[50], wt[50];
    bool completed[50] = {false};

    int currTime = 0;
    int done = 0;

    while (done < n)
    {
        int idx = -1;
        int highestPriority = 999;

        for (int i = 0; i < n; i++)
        {
            if (at[i] <= currTime && !completed[i])
            {
                if (pr[i] < highestPriority)
                {
                    highestPriority = pr[i];
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            currTime += bt[idx];
            ct[idx] = currTime;

            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            completed[idx] = true;
            done++;
        }
        else
        {
            currTime++;
        }
    }

    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++)
    {
        cout << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;

        totalTAT += tat[i];
        totalWT += wt[i];
    }

    cout << "\nAverage Turnaround Time = " << totalTAT / n;
    cout << "\nAverage Waiting Time = " << totalWT / n << endl;
}

int main()
{
    int n, tq;

    cout << "\nEnter number of processes: ";
    cin >> n;

    int at[50], bt[50], pid[50], pr[50];

    for (int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        cout << "Enter AT and BT for P" << i + 1 << ": ";
        cin >> at[i] >> bt[i];
    }

    cout << "\n===== FCFS =====\n";
    fcfsmethod(n, at, bt, pid);

    cout << "\n===== SJF Non Preemptive =====\n";
    sjfnonpreemptive(n, at, bt, pid);

    cout << "\n===== SJF Preemptive =====\n";
    sjfpreemptive(n, at, bt, pid);

    cout << "\n===== Round Robin =====\n";
    cout << "Enter Time Quantum: ";
    cin >> tq;
    roundRobin(n, at, bt, pid, tq);

    cout << "\n===== Priority Non Preemptive =====\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Enter priority for P" << pid[i] << ": ";
        cin >> pr[i];
    }

    priorityScheduling(n, at, bt, pid, pr);

    return 0;
}