#include <iostream>
#include <string.h>
using namespace std;

const int MAX_USER = 100;
const int MAX_DONASI = 100;
const int MAX_KATEGORI = 10;

struct User {
    char username[20];
    char password[20];
    char role[10]; // "admin" atau "user"
};

struct Donasi {
    char nama[20];
    char kategori[30];
    int nominal;
    char status[20]; // pending/dikonfirmasi
};

User users[MAX_USER] = {
    {"admin", "admin", "admin"}
};
Donasi donasis[MAX_DONASI];
char kategoriDonasi[MAX_KATEGORI][30] = {"Kesehatan", "Bencana Alam", "Kecelakaan", "Panti", "Pendidikan"};
int userCount = 1; // 1 untuk admin default
int donasiCount = 0;
int kategoriCount = 5;

void registrasi() {
    if (userCount >= MAX_USER) {
        cout << "User sudah penuh.\n";
        return;
    }
    cout << "\n=== Registrasi ===\n";
    cout << "Username: "; cin >> users[userCount].username;
    cout << "Password: "; cin >> users[userCount].password;
    strcpy(users[userCount].role, "user");
    userCount++;
    cout << "Registrasi berhasil!\n";
}

int login() {
    char user[20], pass[20];
    cout << "\n--- Login ---\n";
    cout << "Username: "; cin >> user;
    cout << "Password: "; cin >> pass;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, user) == 0 && strcmp(users[i].password, pass) == 0) {
            return i;
        }
    }
    return -1;
}

void tampilKategori() {
    for (int i = 0; i < kategoriCount; i++) {
        cout << i+1 << ". " << kategoriDonasi[i] << endl;
    }
}

void tambahDonasi(int userIdx) {
    if (donasiCount >= MAX_DONASI) {
        cout << "Donasi penuh.\n";
        return;
    }
    cout << "\n--- Donasi ---\n";
    tampilKategori();
    int pilih;
    cout << "Pilih kategori (1-" << kategoriCount << "): "; cin >> pilih;
    if (pilih < 1 || pilih > kategoriCount) {
        cout << "Pilihan tidak valid.\n";
        return;
    }
    strcpy(donasis[donasiCount].kategori, kategoriDonasi[pilih-1]);
    cout << "Masukkan nominal donasi: "; cin >> donasis[donasiCount].nominal;
    strcpy(donasis[donasiCount].nama, users[userIdx].username);
    strcpy(donasis[donasiCount].status, "Pending");
    donasiCount++;
    cout << "Donasi berhasil disimpan!\n";
}

void lihatRiwayat(int userIdx) {
    cout << "\n--- Riwayat Donasi ---\n";
    for (int i = 0; i < donasiCount; i++) {
        if (strcmp(donasis[i].nama, users[userIdx].username) == 0) {
            cout << i+1 << ". " << donasis[i].kategori << " - Rp." << donasis[i].nominal << " - " << donasis[i].status << endl;
        }
    }
}

void tambahKategori() {
    if (kategoriCount >= MAX_KATEGORI) {
        cout << "Kategori penuh.\n";
        return;
    }
    cout << "Masukkan nama kategori baru: ";
    cin.ignore(); cin.getline(kategoriDonasi[kategoriCount], 30);
    kategoriCount++;
    cout << "Kategori berhasil ditambahkan!\n";
}

void hapusKategori() {
    tampilKategori();
    int pilih;
    cout << "Pilih kategori yang ingin dihapus: "; cin >> pilih;
    if (pilih < 1 || pilih > kategoriCount) {
        cout << "Pilihan tidak valid.\n";
        return;
    }
    for (int i = pilih-1; i < kategoriCount-1; i++) {
        strcpy(kategoriDonasi[i], kategoriDonasi[i+1]);
    }
    kategoriCount--;
    cout << "Kategori berhasil dihapus.\n";
}

void updateStatus() {
    for (int i = 0; i < donasiCount; i++) {
        cout << i+1 << ". " << donasis[i].nama << " - " << donasis[i].kategori << " - Rp." << donasis[i].nominal << " - " << donasis[i].status << endl;
    }
    int pilih;
    cout << "Pilih nomor donasi yang ingin diupdate: "; cin >> pilih;
    if (pilih < 1 || pilih > donasiCount) {
        cout << "Pilihan tidak valid.\n";
        return;
    }
    cout << "\n=== Konfirmasi Status Donasi ===\n";
    cout << "1. Terima\n2. Kembali\n";
    cout << "Pilihan : ";
    int konfirmasi;
    cin >> konfirmasi;
    if (konfirmasi == 1) {
        strcpy(donasis[pilih-1].status, "Terima");
        cout << "Status donasi berhasil diperbarui!\n";
    }
}

void sortDonasiAZ() {
    for (int i = 0; i < donasiCount-1; i++) {
        for (int j = i+1; j < donasiCount; j++) {
            if (strcmp(donasis[i].nama, donasis[j].nama) > 0) {
                swap(donasis[i], donasis[j]);
            }
        }
    }
}

void sortDonasiZA() {
    for (int i = 0; i < donasiCount-1; i++) {
        for (int j = i+1; j < donasiCount; j++) {
            if (strcmp(donasis[i].nama, donasis[j].nama) < 0) {
                swap(donasis[i], donasis[j]);
            }
        }
    }
}

void sortNominalTinggi() {
    for (int i = 0; i < donasiCount-1; i++) {
        for (int j = i+1; j < donasiCount; j++) {
            if (donasis[i].nominal < donasis[j].nominal) {
                swap(donasis[i], donasis[j]);
            }
        }
    }
}

void cariDonatur() {
    char nama[20];
    cout << "Masukkan nama donatur: "; cin >> nama;
    bool ketemu = false;
    for (int i = 0; i < donasiCount; i++) {
        if (strcmp(donasis[i].nama, nama) == 0) {
            cout << donasis[i].kategori << " - Rp." << donasis[i].nominal << " - " << donasis[i].status << endl;
            ketemu = true;
        }
    }
    if (!ketemu) cout << "Donatur tidak ditemukan.\n";
}

void lihatDonasi() {
    int pilih;
    do {
        cout << "\n1. Lihat donasi (A-Z)\n2. Lihat donasi (Z-A)\n3. Nominal tertinggi-terendah\n4. Cari donatur\n5. Kembali\nPilihan: ";
        cin >> pilih;
        switch (pilih) {
            case 1: sortDonasiAZ(); break;
            case 2: sortDonasiZA(); break;
            case 3: sortNominalTinggi(); break;
            case 4: cariDonatur(); continue;
            case 5: return;
            default: cout << "Pilihan tidak valid.\n"; continue;
        }
        for (int i = 0; i < donasiCount; i++) {
            cout << donasis[i].nama << " - " << donasis[i].kategori << " - Rp." << donasis[i].nominal << " - " << donasis[i].status << endl;
        }
    } while (pilih != 5);
}

void menuUser(int idx) {
    int pilih;
    do {
        cout << "\n--- Menu Donatur ---\n1. Donasi\n2. Lihat Riwayat\n3. Logout\nPilihan: "; cin >> pilih;
        if (pilih == 1) tambahDonasi(idx);
        else if (pilih == 2) lihatRiwayat(idx);
    } while (pilih != 3);
}

void menuAdmin() {
    int pilih;
    do {
        cout << "\n--- Menu Admin ---\n1. Lihat Donasi\n2. Tambah Kategori\n3. Hapus Kategori\n4. Update Status Donasi\n5. Logout\nPilihan: "; cin >> pilih;
        if (pilih == 1) lihatDonasi();
        else if (pilih == 2) tambahKategori();
        else if (pilih == 3) hapusKategori();
        else if (pilih == 4) updateStatus();
    } while (pilih != 5);
}

int main() {
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin");
    strcpy(users[0].role, "admin");
    int pilihan;
    do {
        cout << "\n--- Sistem Donasi ---\n1. Register\n2. Login\n3. Keluar\nPilihan: "; cin >> pilihan;
        if (pilihan == 1) registrasi();
        else if (pilihan == 2) {
            int idx = login();
            if (idx == -1) cout << "Login gagal.\n";
            else if (strcmp(users[idx].role, "admin") == 0) menuAdmin();
            else menuUser(idx);
        }
    } while (pilihan != 3);
    return 0;
}