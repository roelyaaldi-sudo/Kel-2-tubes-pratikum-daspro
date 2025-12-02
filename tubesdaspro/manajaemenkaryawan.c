#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

FILE *file;

float convertGaji(char *str) {
    char clean[50];
    int j = 0;

    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] != '.') {
            clean[j++] = str[i];
        }
    }
    clean[j] = '\0';

    return atof(clean);
}


void tambah();
void tampil();
void cari();
void update();
void hapus();

int main() {
    int pilihan;

    while(1) {
        printf(CYAN "\n=========== PROGRAM MANAJEMEN KARYAWAN ===========" RESET);
        printf(YELLOW "\n1. Tambah Karyawan" RESET);
        printf(YELLOW "\n2. Tampilkan Semua Data" RESET);
        printf(YELLOW "\n3. Cari Karyawan" RESET);
        printf(YELLOW "\n4. Update Data" RESET);
        printf(YELLOW "\n5. Hapus Data" RESET);
        printf(YELLOW "\n6. Keluar\n" RESET);
        printf(CYAN "Pilih menu: " RESET);

        scanf("%d", &pilihan);

        if(pilihan == 1) tambah();
        else if(pilihan == 2) tampil();
        else if(pilihan == 3) cari();
        else if(pilihan == 4) update();
        else if(pilihan == 5) hapus();
        else if(pilihan == 6) {
            printf(GREEN "\nProgram selesai!\n" RESET);
            break;
        }
        else printf(RED "\nPilihan tidak valid!\n" RESET);
    }
}


void tambah() {
    int id;
    char nama[50];
    char jabatan[30];
    char gajiStr[50];
    float gaji;

    file = fopen("data_karyawan.dat", "ab");

    printf("\nMasukkan ID: ");
    scanf("%d", &id);

    printf("Masukkan Nama: ");
    scanf(" %[^\n]", nama);

    printf("Masukkan Jabatan: ");
    scanf(" %[^\n]", jabatan);

    printf("Masukkan Gaji (contoh 80.000.000): ");
    scanf(" %[^\n]", gajiStr);

    gaji = convertGaji(gajiStr);

    fwrite(&id, sizeof(int), 1, file);
    fwrite(nama, sizeof(nama), 1, file);
    fwrite(jabatan, sizeof(jabatan), 1, file);
    fwrite(&gaji, sizeof(float), 1, file);

    fclose(file);

    printf(GREEN "\nData berhasil ditambahkan!\n" RESET);
}


void tampil() {
    int id;
    char nama[50];
    char jabatan[30];
    float gaji;

    file = fopen("data_karyawan.dat", "rb");
    if(!file) {
        printf(RED "\nTidak ada data!\n" RESET);
        return;
    }

    printf(CYAN "\n==== DATA KARYAWAN ====\n" RESET);

    while( fread(&id, sizeof(int), 1, file) ) {
        fread(nama, sizeof(nama), 1, file);
        fread(jabatan, sizeof(jabatan), 1, file);
        fread(&gaji, sizeof(float), 1, file);

        printf(GREEN "\nID: %d\nNama: %s\nJabatan: %s\nGaji: %.2f\n" RESET,
               id, nama, jabatan, gaji);
    }

    fclose(file);
}

void cari() {
    int id, cariID, ketemu = 0;
    char nama[50];
    char jabatan[30];
    float gaji;

    printf("\nMasukkan ID yang dicari: ");
    scanf("%d", &cariID);

    file = fopen("data_karyawan.dat", "rb");

    while(fread(&id, sizeof(int), 1, file)) {
        fread(nama, sizeof(nama), 1, file);
        fread(jabatan, sizeof(jabatan), 1, file);
        fread(&gaji, sizeof(float), 1, file);

        if(id == cariID) {
            printf(GREEN "\nData ditemukan!\n" RESET);
            printf("ID: %d\nNama: %s\nJabatan: %s\nGaji: %.2f\n",
                   id, nama, jabatan, gaji);
            ketemu = 1;
            break;
        }
    }

    fclose(file);

    if(!ketemu)
        printf(RED "\nID tidak ditemukan!\n" RESET);
}


void update() {
    int id, cariID, ketemu = 0;
    char nama[50], jabatan[30], gajiStr[50];
    float gaji;

    printf("\nMasukkan ID yang diupdate: ");
    scanf("%d", &cariID);

    file = fopen("data_karyawan.dat", "rb+");

    while(fread(&id, sizeof(int), 1, file)) {
        fread(nama, sizeof(nama), 1, file);
        fread(jabatan, sizeof(jabatan), 1, file);
        fread(&gaji, sizeof(float), 1, file);

        if(id == cariID) {
            printf("Nama baru: ");
            scanf(" %[^\n]", nama);

            printf("Jabatan baru: ");
            scanf(" %[^\n]", jabatan);

            printf("Gaji baru (contoh 80.000.000): ");
            scanf(" %[^\n]", gajiStr);
            gaji = convertGaji(gajiStr);

            fseek(file, -(sizeof(int) + sizeof(nama) + sizeof(jabatan) + sizeof(float)), SEEK_CUR);

            fwrite(&id, sizeof(int), 1, file);
            fwrite(nama, sizeof(nama), 1, file);
            fwrite(jabatan, sizeof(jabatan), 1, file);
            fwrite(&gaji, sizeof(float), 1, file);

            printf(GREEN "\nData berhasil diperbarui!\n" RESET);
            ketemu = 1;
            break;
        }
    }

    fclose(file);

    if(!ketemu)
        printf(RED "\nID tidak ditemukan!\n" RESET);
}


void hapus() {
    int id, hapusID, ketemu = 0;
    char nama[50];
    char jabatan[30];
    float gaji;

    printf("\nMasukkan ID yang akan dihapus: ");
    scanf("%d", &hapusID);

    FILE *temp;

    file = fopen("data_karyawan.dat", "rb");
    temp = fopen("temp.dat", "wb");

    while(fread(&id, sizeof(int), 1, file)) {
        fread(nama, sizeof(nama), 1, file);
        fread(jabatan, sizeof(jabatan), 1, file);
        fread(&gaji, sizeof(float), 1, file);

        if(id != hapusID) {
            fwrite(&id, sizeof(int), 1, temp);
            fwrite(nama, sizeof(nama), 1, temp);
            fwrite(jabatan, sizeof(jabatan), 1, temp);
            fwrite(&gaji, sizeof(float), 1, temp);
        } else {
            ketemu = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("data_karyawan.dat");
    rename("temp.dat", "data_karyawan.dat");

    if(ketemu)
        printf(GREEN "\nData berhasil dihapus!\n" RESET);
    else
        printf(RED "\nID tidak ditemukan!\n" RESET);
}
