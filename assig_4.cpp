// Readers Writers Problem
// Using User Defined Semaphore and Mutex
// WITHOUT thread library

#include<iostream>

using namespace std;

// ---------------- Semaphore Class ----------------

class Semaphore
{
    int value;

    public:

    Semaphore(int val)
    {
        value = val;
    }

    // wait operation
    void wait()
    {
        if(value > 0)
        {
            value--;
        }
        else
        {
            cout << "Process Waiting...\n";
        }
    }

    // signal operation
    void signal()
    {
        value++;
    }
};

// ---------------- Mutex Class ----------------

class Mutex
{
    int value;

    public:

    Mutex()
    {
        value = 1;
    }

    // lock operation
    void lock()
    {
        if(value == 1)
        {
            value = 0;
        }
        else
        {
            cout << "Critical Section Busy\n";
        }
    }

    // unlock operation
    void unlock()
    {
        value = 1;
    }
};

// ---------------- Shared Variables ----------------

// shared data
int data = 100;

// number of readers currently reading
int readCount = 0;

// semaphore for writer
Semaphore wrt(1);

// mutex for readCount
Mutex mutexLock;

// ---------------- Reader Function ----------------

void reader(int id)
{
    // protect readCount variable
    mutexLock.lock();

    readCount++;//Increment count of active readers

    // if first reader then block writer
    if(readCount == 1)
    {
        wrt.wait();
    }

    mutexLock.unlock();//release the read count 

    // Reading Section
    cout << "\nReader "
         << id
         << " is Reading Data = "
         << data;

    // Reader finished reading
    mutexLock.lock();

    readCount--;

    // if last reader then allow writer
    if(readCount == 0)
    {
        wrt.signal();
    }

    mutexLock.unlock();
}

// ---------------- Writer Function ----------------

void writer(int id)
{
    // writer enters
    wrt.wait();

    // Writing Section
    data = data + 10;

    cout << "\nWriter "
         << id
         << " updated Data = "
         << data;

    // writer leaves
    wrt.signal();
}

// ---------------- Main Function ----------------

int main()
{
    int choice;
    int id;

    while(true)
    {
        cout << "\n\n===== Readers Writers Problem =====";

        cout << "\n1. Reader";
        cout << "\n2. Writer";
        cout << "\n3. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:

                cout << "\nEnter Reader ID: ";
                cin >> id;

                reader(id);

                break;

            case 2:

                cout << "\nEnter Writer ID: ";
                cin >> id;

                writer(id);

                break;

            case 3:

                return 0;

            default:

                cout << "\nInvalid Choice";
        }
    }

    return 0;
}