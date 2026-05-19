// Producer Consumer Problem


#include<iostream>
#include<queue>

using namespace std;

#define Buffer_Size 5

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

    int getValue()
    {
        return value;
    }
};

// ---------------- Binary Semaphore (Mutex) ----------------

class Mutex
{
    int value;

    public:

    Mutex()
    {
        value = 1;
    }

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

    void unlock()
    {
        value = 1;
    }
};

// ---------------- Shared Resources ----------------

queue<int> buffer;

Semaphore emptySlots(Buffer_Size);

Semaphore fullSlots(0);

Mutex mutexLock;

int item = 1;

// ---------------- Producer ----------------

void producer()
{
    emptySlots.wait();

    mutexLock.lock();

    if(buffer.size() < Buffer_Size)
    {
        buffer.push(item);

        cout << "\nProducer Produced Item: "
             << item;

        item++;
    }

    mutexLock.unlock();

    fullSlots.signal();
}

// ---------------- Consumer ----------------

void consumer()
{
    fullSlots.wait();

    mutexLock.lock();

    if(!buffer.empty())
    {
        int consumedItem = buffer.front();

        buffer.pop();

        cout << "\nConsumer Consumed Item: "
             << consumedItem;
    }

    mutexLock.unlock();

    emptySlots.signal();
}

// ---------------- Main Function ----------------

int main()
{
    int choice;

    while(true)
    {
        cout << "\n\n1. Produce";
        cout << "\n2. Consume";
        cout << "\n3. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                producer();
                break;

            case 2:
                consumer();
                break;

            case 3:
                return 0;

            default:
                cout << "\nInvalid Choice";
        }

        // display buffer
        cout << "\nCurrent Buffer Size: "
             << buffer.size();
    }

    return 0;
}