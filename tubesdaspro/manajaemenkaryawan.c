#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

struct Karyawan {
    int id;
    char nama[50];
    char jabatan[30];
    float gaji;
};

struct Karyawan data[MAX];
int jumlah = 0;

void loadData();
void saveData();
float convertGaji(char *str);

void tambah();
void tampil();
void cari();
void update();
void hapus();


int main() {
    int pilihan;
    loadData();

    while(1) {
        printf(CYAN "\n========== PROGRAM MANAJEMEN KARYAWAN  ==========\n" RESET);
        printf(YELLOW "1. Tambah Karyawan\n" RESET);
        printf(YELLOW "2. Tampilkan Semua Data\n" RESET);
        printf(YELLOW "3. Cari Karyawan\n" RESET);
        printf(YELLOW "4. Update Data\n" RESET);
        printf(YELLOW "5. Hapus Data\n" RESET);
        printf(YELLOW "6. Keluar\n" RESET);
        printf(CYAN "Pilih menu: " RESET);

        scanf("%d", &pilihan);

        if (pilihan == 1) tambah();
        else if (pilihan == 2) tampil();
        else if (pilihan == 3) cari();
        else if (pilihan == 4) update();
        else if (pilihan == 5) hapus();
        else if (pilihan == 6) {
            printf(GREEN "\nProgram selesai!\n" RESET);
            break;
        } else {
            printf(RED "\nPilihan tidak valid!\n" RESET);
        }
    }
    return 0;
}


void loadData() {
    FILE *file = fopen("data_karyawan.txt", "r");
    if (!file) return;

    jumlah = 0;
    while (fscanf(file, "%d|%49[^|]|%29[^|]|%f\n",
                  &data[jumlah].id,
                  data[jumlah].nama,
                  data[jumlah].jabatan,
                  &data[jumlah].gaji) == 4) {
        jumlah++;
    }
    fclose(file);
}


void saveData() {
    FILE *file = fopen("data_karyawan.txt", "w");

    for (int i = 0; i < jumlah; i++) {
        fprintf(file, "%d|%s|%s|%.2f\n",
                data[i].id,
                data[i].nama,
                data[i].jabatan,
                data[i].gaji);
    }
    fclose(file);
}


float convertGaji(char *str) {
    char clean[50];
    int j = 0;

    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] != '.') clean[j++] = str[i];
    }
    clean[j] = '\0';

    return atof(clean);
}


void tambah() {
    if (jumlah >= MAX) {
        printf(RED "\nData penuh!\n" RESET);
        return;
    }

    char gajiStr[50];

    printf(CYAN "\nMasukkan ID: " RESET);
    scanf("%d", &data[jumlah].id);

    printf(CYAN "Masukkan Nama: " RESET);
    scanf(" %[^\n]", data[jumlah].nama);

    printf(CYAN "Masukkan Jabatan: " RESET);
    scanf(" %[^\n]", data[jumlah].jabatan);

    printf(CYAN "Masukkan Gaji (contoh 3.000.000): " RESET);
    scanf(" %[^\n]", gajiStr);

    data[jumlah].gaji = convertGaji(gajiStr);

    jumlah++;
    saveData();

    printf(GREEN "\nData berhasil ditambahkan!\n" RESET);
}


void tampil() {
    if (jumlah == 0) {
        printf(RED "\nBelum ada data.\n" RESET);
        return;
    }

    printf(CYAN "\n=========== DATA KARYAWAN ===========\n" RESET);

    for(int i = 0; i < jumlah; i++) {
        printf(GREEN "\nID      : %d" RESET, data[i].id);
        printf(BLUE  "\nNama    : %s" RESET, data[i].nama);
        printf(YELLOW"\nJabatan : %s" RESET, data[i].jabatan);
        printf(CYAN  "\nGaji    : %.2f\n" RESET, data[i].gaji);
    }
}


void cari() {
    int cariID;

    printf(CYAN "\nMasukkan ID yang dicari: " RESET);
    scanf("%d", &cariID);

    for(int i = 0; i < jumlah; i++) {
        if (data[i].id == cariID) {
            printf(GREEN "\nData ditemukan!\n" RESET);
            printf("ID: %d\nNama: %s\nJabatan: %s\nGaji: %.2f\n",
                   data[i].id, data[i].nama, data[i].jabatan, data[i].gaji);
            return;
        }
    }
    printf(RED "\nID tidak ditemukan!\n" RESET);
}


void update() {
    int cariID;
    char gajiStr[50];

    printf(CYAN "\nMasukkan ID yang akan diupdate: " RESET);
    scanf("%d", &cariID);

    for(int i = 0; i < jumlah; i++) {
        if (data[i].id == cariID) {

            printf(CYAN "Nama baru: " RESET);
            scanf(" %[^\n]", data[i].nama);

            printf(CYAN "Jabatan baru: " RESET);
            scanf(" %[^\n]", data[i].jabatan);

            printf(CYAN "Gaji baru: " RESET);
            scanf(" %[^\n]", gajiStr);

            data[i].gaji = convertGaji(gajiStr);

            saveData();
            printf(GREEN "\nData berhasil diperbarui!\n" RESET);
            return;
        }
    }
    printf(RED "\nID tidak ditemukan!\n" RESET);
}

void hapus() {
    int hapusID;

    printf(CYAN "\nMasukkan ID yang akan dihapus: " RESET);
    scanf("%d", &hapusID);

    for(int i = 0; i < jumlah; i++) {
        if(data[i].id == hapusID) {

            for(int j = i; j < jumlah - 1; j++)
                data[j] = data[j + 1];

            jumlah--;
            saveData();

            printf(GREEN "\nData berhasil dihapus!\n" RESET);
            return;
        }
    }
    printf(RED "\nID tidak ditemukan!\n" RESET);
}


