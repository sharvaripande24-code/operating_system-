#include<iostream>
using namespace std;

void paging() {
    int pagesize, logicaladdress;

    cout<<"Enter the size of page : ";
    cin>>pagesize;
    cout<<"Enter logical address : ";
    cin>>logicaladdress;

    int pagenumber = logicaladdress / pagesize;
    int offset = logicaladdress % pagesize;

    int frametable[100];
    cout<<"Enter the frame of pagenumber "<<pagenumber<<" : ";
    cin>>frametable[pagenumber];

    int physicaladdress = frametable[pagenumber] * pagesize + offset;

    cout<<"\nPage number = "<<pagenumber<<endl;
    cout<<"Offset = "<<offset<<endl;
    cout<<"Physical address = "<<physicaladdress<<endl;
}

void segmentation() {
    int baseaddress[100], limit[100];
    int n;
    cout<<"Enter the number of segments : ";
    cin>>n;

    cout<<"\nEnter base address and limit\n";
    for(int i=0;i<n;i++) {
        cout<<"Enter base address of Segment "<<i<<" : ";
        cin>>baseaddress[i];
        cout<<"Enter limit of segment "<<i<<" : ";
        cin>>limit[i];
    }

    int offset, segmentnumber;
    cout<<"\nEnter the segment number : ";
    cin>>segmentnumber;
    cout<<"Enter offset : ";
    cin>>offset;

    if(offset < limit[segmentnumber]) {
        int physicaladdress = baseaddress[segmentnumber] + offset;
        cout<<"\nPhysical address : "<<physicaladdress<<endl;
    }              
    else {
        cout<<"Offset not correct"<<endl;
    }
}

int main() {

    cout<<"\nPhysican Address using paging\n";
    paging();

    cout<<"\n\nPhysican Address using segmentation\n\n";
    segmentation();

    return 0;
}