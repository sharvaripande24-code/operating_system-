// READER - WRITER USING MUTEX 
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t mutex1, wrt;
int readCount = 0;

void* reader(void* arg)
{
    int id = *((int*)arg);

    while (true)
    {
        pthread_mutex_lock(&mutex1);
        readCount++;

        if (readCount == 1)
            pthread_mutex_lock(&wrt);

        pthread_mutex_unlock(&mutex1);

        cout << "Reader " << id << " is reading" << endl;
        sleep(1);

        pthread_mutex_lock(&mutex1);
        readCount--;

        if (readCount == 0)
            pthread_mutex_unlock(&wrt);

        pthread_mutex_unlock(&mutex1);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg)
{
    int id = *((int*)arg);

    while (true)
    {
        pthread_mutex_lock(&wrt);

        cout << "Writer " << id << " is writing" << endl;
        sleep(2);

        pthread_mutex_unlock(&wrt);

        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&wrt, NULL);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    while (true)
        sleep(1);

    return 0;
}



//READER - WRITER USING SEMAPHORE
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t mutex1, wrt;
int readCount = 0;

void* reader(void* arg)
{
    int id = *((int*)arg);

    while (true)
    {
        sem_wait(&mutex1);
        readCount++;

        if (readCount == 1)
            sem_wait(&wrt);

        sem_post(&mutex1);

        cout << "Reader " << id << " is reading" << endl;
        sleep(1);

        sem_wait(&mutex1);
        readCount--;

        if (readCount == 0)
            sem_post(&wrt);

        sem_post(&mutex1);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg)
{
    int id = *((int*)arg);

    while (true)
    {
        sem_wait(&wrt);

        cout << "Writer " << id << " is writing" << endl;
        sleep(2);

        sem_post(&wrt);

        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    sem_init(&mutex1, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    while (true)
        sleep(1);

    return 0;
}


//PRODUCER CONSUMER USING SEMAPHORE
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

int buffer[5];
int in = 0, out = 0;

sem_t empty, full, mutex1;

void* producer(void* arg)
{
    int item = 1;

    while (true)
    {
        sem_wait(&empty);
        sem_wait(&mutex1);

        buffer[in] = item;
        cout << "Produced: " << item << endl;
        in = (in + 1) % 5;
        item++;

        sem_post(&mutex1);
        sem_post(&full);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg)
{
    while (true)
    {
        sem_wait(&full);
        sem_wait(&mutex1);

        int item = buffer[out];
        cout << "Consumed: " << item << endl;
        out = (out + 1) % 5;

        sem_post(&mutex1);
        sem_post(&empty);

        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t p1, c1;

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    sem_init(&mutex1, 0, 1);

    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&c1, NULL, consumer, NULL);

    while (true)
        sleep(1);

    return 0;
}


//PRODUCER CONSUMER USING MUTEX

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int buffer[5];
int in = 0, out = 0, count = 0;

pthread_mutex_t mutex1;

void* producer(void* arg)
{
    int item = 1;

    while (true)
    {
        pthread_mutex_lock(&mutex1);

        if (count < 5)
        {
            buffer[in] = item;
            cout << "Produced: " << item << endl;
            in = (in + 1) % 5;
            count++;
            item++;
        }

        pthread_mutex_unlock(&mutex1);

        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg)
{
    while (true)
    {
        pthread_mutex_lock(&mutex1);

        if (count > 0)
        {
            int item = buffer[out];
            cout << "Consumed: " << item << endl;
            out = (out + 1) % 5;
            count--;
        }

        pthread_mutex_unlock(&mutex1);

        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t p1, c1;

    pthread_mutex_init(&mutex1, NULL);

    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&c1, NULL, consumer, NULL);

    while (true)
        sleep(1);

    return 0;
}


//DINING PHILOSOPHER USING MUTEX 

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t chopstick[5];

void* philosopher(void* arg)
{
    int id = *((int*)arg);

    while (true)
    {
        cout << "Philosopher " << id << " is thinking" << endl;
        sleep(1);

        pthread_mutex_lock(&chopstick[id]);
        pthread_mutex_lock(&chopstick[(id + 1) % 5]);

        cout << "Philosopher " << id << " is eating" << endl;
        sleep(2);

        pthread_mutex_unlock(&chopstick[id]);
        pthread_mutex_unlock(&chopstick[(id + 1) % 5]);

        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t p[5];
    int id[5] = {0, 1, 2, 3, 4};

    for (int i = 0; i < 5; i++)
        pthread_mutex_init(&chopstick[i], NULL);

    for (int i = 0; i < 5; i++)
        pthread_create(&p[i], NULL, philosopher, &id[i]);

    while (true)
        sleep(1);

    return 0;
}



//DINING PHILOSOPHER USING SEMAPHORE 

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t chopstick[5];

void* philosopher(void* arg)
{
    int id = *((int*)arg);

    while (true)
    {
        cout << "Philosopher " << id << " is thinking" << endl;
        sleep(1);

        sem_wait(&chopstick[id]);
        sem_wait(&chopstick[(id + 1) % 5]);

        cout << "Philosopher " << id << " is eating" << endl;
        sleep(2);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % 5]);

        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t p[5];
    int id[5] = {0, 1, 2, 3, 4};

    for (int i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < 5; i++)
        pthread_create(&p[i], NULL, philosopher, &id[i]);

    while (true)
        sleep(1);

    return 0;
}


//