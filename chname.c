/* chname.c - chname */

#include <xinu.h>                      // Header utama sistem Xinu (berisi definisi proses, syscall, dll)

/*------------------------------------------------------
 * chname - Dummy syscall
 *------------------------------------------------------ 
 */

pri16 chname(                        // Fungsi chname mengembalikan nilai bertipe pri16 (priority 16-bit)
    pid32 pid,                       // pid: ID dari proses yang ingin diubah
    pri16 newprio                    // newprio: prioritas baru untuk proses tersebut
)
{
    intmask mask;                    // Variabel untuk menyimpan status interrupt sebelum dinonaktifkan
    struct procent *prptr;           // Pointer ke entri proses di tabel proses (proctab)
    pri16 oldprio;                   // Variabel untuk menyimpan prioritas lama proses

    mask = disable();                // Nonaktifkan interrupt, masuk ke critical section agar data kernel aman

    if (isbadpid(pid)) {             // Cek apakah PID yang diberikan valid atau tidak
        restore(mask);               // Kalau PID tidak valid, pulihkan interrupt
        return (pri16) SYSERR;       // Kembalikan nilai SYSERR sebagai tanda error
    }

    prptr = &proctab[pid];           // Ambil alamat entri proses yang sesuai dari tabel proses
    oldprio = prptr->prprio;         // Simpan prioritas lama ke variabel oldprio
    prptr->prprio = newprio;         // Ubah prioritas proses menjadi nilai baru (newprio)

    kprintf("\n\nNew Syscall is easy\n\n");  // Tampilkan pesan di layar (hanya untuk menandai bahwa syscall berhasil)

    restore(mask);                   // Aktifkan kembali interrupt (keluar dari critical section)
    return oldprio;                  // Kembalikan prioritas lama kepada pemanggil syscall
}
