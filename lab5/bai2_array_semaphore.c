#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define MAXN 100

int a[MAXN];
int n = 0;          /* so phan tu hien co trong mang a */
sem_t mutex;

/* Thread sinh so nguyen ngau nhien va them vao mang a */
void* producer(void* arg) {
    while (1) {
        int value = rand() % 1000;

        sem_wait(&mutex);
        if (n < MAXN) {
            a[n] = value;
            n++;
            printf("[Producer] them %d -> so phan tu: %d\n", value, n);
        } else {
            printf("[Producer] mang day, khong them duoc\n");
        }
        sem_post(&mutex);

        usleep(rand() % 500000);
    }
    return NULL;
}

/* Thread lay ra 1 phan tu bat ky trong mang a */
void* consumer(void* arg) {
    while (1) {
        sem_wait(&mutex);
        if (n > 0) {
            int value = a[n - 1];   /* lay phan tu cuoi, co the doi cach lay khac */
            n--;
            printf("[Consumer] lay ra %d -> so phan tu: %d\n", value, n);
        } else {
            printf("Nothing in array a\n");
        }
        sem_post(&mutex);

        usleep(rand() % 500000);
    }
    return NULL;
}

int main() {
    pthread_t tp, tc;
    srand(time(NULL));

    sem_init(&mutex, 0, 1);  /* mutex: chi 1 thread duoc vao vung tranh chap */

    pthread_create(&tp, NULL, producer, NULL);
    pthread_create(&tc, NULL, consumer, NULL);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);

    sem_destroy(&mutex);
    return 0;
}

/*
 GHI CHU:
 - De tai tao loi (chua dong bo), chi can BO 4 dong sem_wait/sem_post
   trong producer() va consumer(), roi bien dich va chay lai.
 - Khi do se thay hien tuong: so phan tu in ra khong khop thuc te,
   mat mat phan tu, hoac doc gia tri sai do 2 thread cung truy xuat
   dong thoi vao bien n va mang a (race condition).
*/
