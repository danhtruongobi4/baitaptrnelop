#include <stdio.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t mutex;

void* processA(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20) x = 0;
        printf("[A] x = %d\n", x);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* processB(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        x = x + 1;
        if (x == 20) x = 0;
        printf("[B] x = %d\n", x);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t tA, tB;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}

/*
 NHAN XET:
 Sau khi bao ve vung tranh chap (doc, sua, in x) bang mutex,
 tai 1 thoi diem chi co 1 thread duoc phep thuc hien khoi lenh nay.
 Ket qua: gia tri x tang deu tu 0 den 19 roi quay lai 0, khong con
 hien tuong nhay coc hay vuot nguong nhu o bai 3.
*/
