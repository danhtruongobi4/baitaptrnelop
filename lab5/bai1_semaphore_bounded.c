#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

/* Thay N bang: 2 so cuoi cua MSSV + 10 */
#define N 25

sem_t full, empty;
int sells = 0, products = 0;

void* processA(void* arg) {
    while (1) {
        sem_wait(&full);        /* cho neu chua co hang de ban */
        sells++;
        printf("[A - ban hang] sells=%d products=%d\n", sells, products);
        sem_post(&empty);       /* bao da ban, tao them cho trong de lam hang */
        usleep(rand() % 300000);
    }
    return NULL;
}

void* processB(void* arg) {
    while (1) {
        sem_wait(&empty);       /* cho neu da lam du qua N so voi sells */
        products++;
        printf("[B - tao hang] sells=%d products=%d\n", sells, products);
        sem_post(&full);        /* bao da co hang moi de ban */
        usleep(rand() % 300000);
    }
    return NULL;
}

int main() {
    pthread_t tA, tB;
    srand(time(NULL));

    sem_init(&full, 0, 0);   /* so hang dang co san = 0 luc dau */
    sem_init(&empty, 0, N);  /* con duoc lam toi da N hang truoc khi ban kip */

    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}
