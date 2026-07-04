#include <stdio.h>
#include <pthread.h>

int x = 0;

void* processA(void* arg) {
    while (1) {
        x = x + 1;
        if (x == 20) x = 0;
        printf("[A] x = %d\n", x);
    }
    return NULL;
}

void* processB(void* arg) {
    while (1) {
        x = x + 1;
        if (x == 20) x = 0;
        printf("[B] x = %d\n", x);
    }
    return NULL;
}

int main() {
    pthread_t tA, tB;

    pthread_create(&tA, NULL, processA, NULL);
    pthread_create(&tB, NULL, processB, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    return 0;
}

/*
 NHAN XET:
 Vi doan lenh "x = x + 1; if (x == 20) x = 0; print(x);" khong phai
 la mot khoi thao tac nguyen tu (atomic), 2 thread A va B co the doc/ghi
 xen ke nhau vao bien chia se x. Ket qua quan sat duoc: gia tri x in ra
 co the nhay coc, lap lai, hoac vuot qua 20 - day la hau qua cua
 tranh chap (race condition) tren bien dung chung khong duoc bao ve.
*/
