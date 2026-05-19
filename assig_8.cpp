#include<iostream>
using namespace std;

int main() {
    int n, m;

    cout<<"Enter number of processes: ";
    cin>>n;

    cout<<"Enter number of resources: ";
    cin>>m;

    int allocation[100][100], request[100][100];
    int available[100];
    bool finish[100];

    cout<<"\nEnter Allocation Matrix:\n";
    for(int i=0;i<n;i++) {
        cout<<"Process "<<i<<": ";
        for(int j=0;j<m;j++) {
            cin>>allocation[i][j];
        }
    }

    cout<<"\nEnter Request Matrix:\n";
    for(int i=0;i<n;i++) {
        cout<<"Process "<<i<<": ";
        for(int j=0;j<m;j++) {
            cin>>request[i][j];
        }
    }

    cout<<"\nEnter Available Resources: ";
    for(int j=0;j<m;j++) {
        cin>>available[j];
    }

    // Initialize Finish array
    for(int i=0;i<n;i++) {
        bool flag = true;
        for(int j=0;j<m;j++) {
            if(allocation[i][j] != 0) {
                flag = false;
                break;
            }
        }
        finish[i] = flag;
    }

    // Deadlock Detection Logic
    while(true) {
        bool found = false;

        for(int i=0;i<n;i++) {
            if(!finish[i]) {
                int j;
                for(j=0;j<m;j++) {
                    if(request[i][j] > available[j])
                        break;
                }

                if(j == m) {
                    cout << "\nProcess P" << i << " can execute\n";
                    for(int k=0;k<m;k++)
                        available[k] += allocation[i][k];

                    // Print updated resources
    cout << "Updated Work Resources: ";
    for(int k=0;k<m;k++) {
        cout << available[k] << " ";
    }
    cout << endl;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found)
            break;
    }

    bool deadlock = false;

    cout<<"\nDeadlocked Processes: ";
    for(int i=0;i<n;i++) {
        if(!finish[i]) {
            cout<<"P"<<i<<" ";
            deadlock = true;
        }
    }

    if(!deadlock)
        cout<<"None (System is not in deadlock)";

    return 0;
}