#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    int n;
    cout<<"\nenter the number of disk request:";
    cin>>n;

    int request[20];
    cout<<"enter the disk request queue: ";
    for(int i=0;i<n;i++){
        cin>>request[i];
    }

    int head;
    cout<<"\nenter the disk head: ";
    cin>>head;

    cout<<"\n=========FIFO==================";
    int current=head;
    int totalmemory=0;
    cout<<"\nhead movement:";

    for(int i=0;i<n;i++){
        cout<<current<<"->"<<request[i]<<endl;

        if(current>request[i]){
            totalmemory=totalmemory+(current-request[i]);
        }
        else{
            totalmemory=totalmemory+(current-request[i]);
        }
        current=request[i];
    }

    cout<<"\ntotal head movement: "<<totalmemory<<endl;

    cout<<"\n============SSTF===============";
    int visited[50]={0};
    current=head;
    totalmemory=0;
            cout<<"\nhead movement:";

    for(int i=0;i<n;i++){
        int mindistance=9999;
        int index=-1;
        for(int j=0;j<n;j++){
            if(visited[j]==0){
                int distance;
                if(current>request[j]){
                    distance=current-request[j];
                }
                else{
                    distance=current-request[j];
                }
                if(distance<mindistance){
                    mindistance=distance;
                    index=j;
                }
            }
        }
        visited[index]=1;
        cout<<current<<"->"<<request[index]<<endl;
        if(current>request[index]){
            totalmemory=totalmemory+(current-request[index]);
        }
        else{
            totalmemory=totalmemory+(current-request[index]);
        }

        current=request[index];
    }
        cout<<"\ntotal head movement: "<<totalmemory<<endl;

    cout<<"\n==============scan================";
    int scan[20];
    current=head;
    totalmemory=0;
            cout<<"\nhead movement:";

    for(int i=0;i<n;i++){
        scan[i]=request[i];
    }
    sort(scan,scan+n);

    int pos;
    for(pos=0;pos<n;pos++){
        if(scan[pos]>=head){
            break;
        }
    }
    //right shift
    for(int i=pos;i<n;i++){
        cout<<current<<"->"<<scan[i]<<endl;

        if(current>scan[i]){
            totalmemory=totalmemory+(current-scan[i]);
        }
        else{
            totalmemory=totalmemory+(scan[i]-current);
        }
        current=scan[i];
    }
    //left side
    for(int i=pos-1;i>=0;i--){
        cout<<current<<"->"<<scan[i]<<endl;

        if(current>scan[i]){
            totalmemory=totalmemory+(current-scan[i]);
        }
        else{
            totalmemory=totalmemory+(scan[i]-current);
        }
        current=scan[i];
    }
        cout<<"\ntotal head movement: "<<totalmemory<<endl;


    cout<<"\n=================cscan===================";
    int cscan[20];
            cout<<"\nhead movement:";

    for(int i=0;i<n;i++){
        cscan[i]=request[i];
    }
    sort(cscan,cscan+n);
    current=head;
    totalmemory=0;

    for(pos=0;pos<n;pos++){
        if(cscan[pos]>=head) break;
    }

    //rigth side
    for(int i=pos;i<n;i++){
        cout<<current<<"->"<<cscan[i]<<endl;

        if(current>cscan[i]){
            totalmemory=totalmemory+(current-cscan[i]);
        }
        else{
            totalmemory=totalmemory+(cscan[i]-current);
        }
        current=cscan[i];
    }
    if(pos>0){
        cout<<current<<"->"<<cscan[0];

        if(current>cscan[0]){
            totalmemory=totalmemory+(current-cscan[0]);
        }
        else{
            totalmemory=totalmemory+(cscan[0]-current);
        }
        current=cscan[0];
    }
    //complete the remaining request
    for(int i=0;i<pos;i++){
        cout<<current<<"->"<<cscan[i];
         if(current>cscan[i]){
            totalmemory=totalmemory+(current-cscan[i]);
        }
        else{
            totalmemory=totalmemory+(cscan[i]-current);
        }
        current=cscan[i];

    }

            cout<<"\ntotal head movement: "<<totalmemory<<endl;

            return 0;
    
}