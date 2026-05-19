// Dining Philosophers Problem
// Using User Defined Semaphore and Mutex
// WITHOUT thread library

#include<iostream>

using namespace std;

#define N 5

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
            cout << "Resource Not Available\n";
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

// ---------------- Chopsticks ----------------

// each chopstick is a binary semaphore
Semaphore chopstick[N] =
{
    Semaphore(1),
    Semaphore(1),
    Semaphore(1),
    Semaphore(1),
    Semaphore(1)
};

// ---------------- Philosopher Function ----------------

void philosopher(int id)
{
    int left = id;

    int right = (id + 1) % N;

    cout << "\nPhilosopher "
         << id
         << " is Thinking";

    // take left chopstick
    chopstick[left].wait();

    cout << "\nPhilosopher "
         << id
         << " picked Left Chopstick "
         << left;

    // take right chopstick
    chopstick[right].wait();

    cout << "\nPhilosopher "
         << id
         << " picked Right Chopstick "
         << right;

    // eating
    cout << "\nPhilosopher "
         << id
         << " is Eating";

    // release left chopstick
    chopstick[left].signal();

    cout << "\nPhilosopher "
         << id
         << " released Left Chopstick "
         << left;

    // release right chopstick
    chopstick[right].signal();

    cout << "\nPhilosopher "
         << id
         << " released Right Chopstick "
         << right;

    cout << "\nPhilosopher "
         << id
         << " Finished Eating\n";
}

// ---------------- Main Function ----------------

int main()
{
    int choice;
    int id;

    while(true)
    {
        cout << "\n\n===== Dining Philosophers Problem =====";

        cout << "\n1. Philosopher Wants to Eat";
        cout << "\n2. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:

                cout << "\nEnter Philosopher Number (0-4): ";
                cin >> id;

                if(id >= 0 && id < N)
                {
                    philosopher(id);
                }
                else
                {
                    cout << "\nInvalid Philosopher Number";
                }

                break;

            case 2:

                return 0;

            default:

                cout << "\nInvalid Choice";
        }
    }

    return 0;
}