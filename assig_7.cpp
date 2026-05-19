#include<iostream>
using namespace std;

int main() {
    int n, m, i, j, k;

    cout<<"Enter the number of process : ";
    cin>>n;

    cout<<"Enter the number of resources : ";
    cin>>m;

    int allocation[100][100], max[100][100];
    int available[100], need[100][100];

    cout<<"\nEnter the value of allocation\n";
    for(i=0;i<n;i++) {
        cout<<"Process "<<i<<" : ";
        for(j=0;j<m;j++) {
            cin>>allocation[i][j];
        }
    }

    cout<<"\nEnter the value of max"<<endl;
    for(i=0;i<n;i++) {
        cout<<"Process "<<i<<" : ";
        for(j=0;j<m;j++) {
            cin>>max[i][j];
        }
    }

    cout<<endl;

    for(i=0;i<n;i++) {
        for(j=0;j<m;j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    cout<<"Enter the value of available : ";
    for(j=0;j<m;j++) {
        cin>>available[j];
    }

    cout<<"\nProcess\t\tAllocation\tMax\t\tNeed\n";
    for(i=0;i<n;i++) {
        cout<<"P"<<i<<"\t\t";
        for(j=0;j<m;j++) {
            cout<<allocation[i][j]<<" ";
        }
        cout<<"\t\t";
        for(j=0;j<m;j++) {
            cout<<max[i][j]<<" ";
        }
        cout<<"\t\t";
        for(j=0;j<m;j++) {
            cout<<need[i][j];
        }
        cout<<endl;
    }

    int count = 0, safesequence[100];
    bool finish[100] = {false};

    while(count < n) {
        bool found = false;

        for(i=0; i<n; i++) {
            if(finish[i] == false) {
                for(j=0; j<m; j++) {
                    if(need[i][j] > available[j]) {
                        break;
                    }
                }

                if(j == m) {
                    cout<<"\nP"<<i<<" executes";
                    for(k=0;k<m;k++) {
                        available[k] += allocation[i][k];
                    }
                    cout<<"\nUpdated available : ";
                    for(k=0;k<m;k++) {
                        cout<<available[k]<<" ";
                    }
                    cout<<endl;

                    safesequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }           
        if(!found) {
            cout<<"\n\nSystem is NOT in safe state(Deadlock Possible)\n";
            return 0;
        }
    }

    cout<<"\n\nSystem is in safe state\nSafe sequence : ";
    for(int i=0;i<n;i++) {
        cout<<"P"<<safesequence[i];
        if(i != n-1) cout<<" -> ";
    }
    cout<<endl;
    return 0;
}