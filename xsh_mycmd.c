/* xsh_mycnd.c - xsh_mycnd */   // Nama file dan fungsi shell

#include <xinu.h>               // Header utama sistem Xinu
#include <stdio.h>              // Untuk printf, fprintf
#include <string.h>             // Untuk fungsi string (strncmp)

// deklarasi nama fungsi
static void printMemUse(void);  // Deklarasi fungsi lokal printMemUse

shellcmd xsh_mycnd(int nargs, char *args[]) {   // Fungsi command shell Xinu

    /* For argument '--help', emit help about the 'ping' command */
    // Jika user memasukkan: mycmd --help
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {   // Cek apakah argumen kedua adalah --help
        printf("Use: %s argumen1id argumen2\n", args[0]);      // args[0] adalah nama perintah
        printf("Description:\n");                             // Label deskripsi
        printf("My own command with 2 argument\n");           // Deskripsi fungsi command
        printf("Options:\n");                                // Label opsi
        printf("    --help\t display this help and exit\n"); // Penjelasan opsi help
        return 0;                                              // Keluar fungsi jika help ditampilkan
    }

    /* Check for valid number of arguments */
    // Jumlah argumen harus 3 (nama_perintah, arg1, arg2)
    if (nargs != 3) {                                           // Jika argumen tidak 3
        fprintf(stderr, "%s: jumlah argumen tidak cocok\n", args[0]);  // Cetak error ke stderr
        fprintf(stderr, "Try '%s --help' for more information\n", args[0]); // Saran melihat help
        return 1;                                               // Return error
    }

    printMemUse();                                              // Panggil fungsi untuk menampilkan info memori

    printf("Nama perintah adalah: %s\n", args[0]);            // Tampilkan nama perintah yang dipanggil
    printf("Argumen pertama adalah: %s\n", args[1]);          // Cetak argumen pertama
    printf("Argumen kedua adalah: %s\n", args[2]);            // Cetak argumen kedua

    return 0;                                                   // Sukses
}

/* ------------------------------------------------------------------------------
 * printMemUse - Print statistics about memory use
 * ------------------------------------------------------------------------------
 */
void printMemUse(void){                    // Fungsi untuk menampilkan penggunaan memori (dummy)
    printf("My memory usage is xxxx\n");  // Placeholder, nanti bisa diganti info memori asli Xinu
}