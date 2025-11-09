#include <xinu.h>

void sndA(sid32 s1, sid32 s3); 
void sndB(sid32 s2, sid32 s1); 
void sndC(sid32 s3, sid32 s2);

process main(void) { 
    sid32 s1, s2, s3;
    
    // Inisialisasi semaphore
    s1 = semcreate(1); // Proses A langsung bisa jalan 
    s2 = semcreate(0); // Proses B menunggu
    s3 = semcreate(0); // Proses C menunggu

    // Jalankan ketiga proses
    resume(create(sndA, 1024, 20, "Proses A", 2, s1, s3));
    resume(create(sndB, 1024, 20, "Proses B", 2, s2, s1));
    resume(create(sndC, 1024, 20, "Proses C", 2, s3, s2));
return OK;
}

// Proses A
void sndA(sid32 s1, sid32 s3) { 
    while (1) {
        wait(s1); 
        printf("Hai A\n"); 
        sleepms(300);
        signal(s3); // Giliran C
    }
}

// Proses B
void sndB(sid32 s2, sid32 s1) { 
    while (1) {
        wait(s2); 
        printf("Hai B\n"); 
        sleepms(300);
        signal(s1); // Giliran A
    }
}

// Proses C
void sndC(sid32 s3, sid32 s2) { 
    while (1) {
        wait(s3); 
        printf("Hai C\n"); 
        sleepms(300);
        signal(s2); // Giliran B
    }
}