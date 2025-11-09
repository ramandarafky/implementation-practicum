#include <xinu.h>

void lebah(sid32 mutex, sid32 sem1, sid32 sem2); 
void madu(sid32 mutex, sid32 sem1, sid32 sem2);

int32 n = 0; // variabel global (shared resource)

process main(void) {
    sid32 mutex, sem1, sem2;
    
    mutex = semcreate(1); // Mutex: kunci akses variabel n 
    sem1 = semcreate(1); // Lebah bisa mulai dulu
    sem2 = semcreate(0); // Madu menunggu lebah
    
    resume(create(lebah, 1024, 20, "Lebah", 3, mutex, sem1, sem2));
    resume(create(madu, 1024, 20, "Madu", 3, mutex, sem1, sem2));
    
    return OK;
}

void lebah(sid32 mutex, sid32 sem1, sid32 sem2) {
    int i;
    for (i = 0; i < 10; i++) {
        wait(sem1);
        wait(mutex); // masuk critical section
        n++; // tambah madu
        printf("Lebah membuat madu ke-%d\n", n);
        signal(mutex); // keluar dari critical section 
        signal(sem2); // beri giliran ke proses madu
    }
}

void madu(sid32 mutex, sid32 sem1, sid32 sem2) { 
    int i;
    for (i = 0; i < 10; i++) {
        wait(sem2);
        wait(mutex); // masuk critical section
        printf("Madu tersedia sebanyak %d buah\n", n);
        signal(mutex);
        signal(sem1); // beri giliran ke lebah
    }
}