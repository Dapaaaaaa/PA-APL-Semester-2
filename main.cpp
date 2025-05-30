#include <iostream>
#include <string.h>
#include <cstdlib>
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
Donasi donasi[MAX_DONASI];
char kategoriDonasi[MAX_KATEGORI][30] = {"Kesehatan", "Bencana Alam", "Kecelakaan", "Panti", "Pendidikan"};
int userCount = 1; // 1 untuk admin default
int donasiCount = 0;
int kategoriCount = 5;

bool cekUsername(const char* uname) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, uname) == 0) {
            return true; // Username sudah ada
        }
    }
    return false; // Username tersedia
}

void registrasi() {
    system("clear || cls");
    if (userCount >= MAX_USER) {
        cout << "User sudah penuh.\n";
        cout << "ENTER....." << endl;
        cin.get();
        system("clear || cls");
        return;
    }

    cout << "\n=== Registrasi ===\n";
    cin.ignore();
    char uname[20], pass[20];

    do {
    cout << "Username: ";
    cin.getline(uname, 20);
    if (strlen(uname) == 0) cout << "Username tidak boleh kosong!\n";
    } while (strlen(uname) == 0);

    // Cek apakah username sudah digunakan
    if (cekUsername(uname)) {
        cout << "Username sudah digunakan. Coba yang lain.\n";
        cout << "ENTER....." << endl;
        cin.get();
        system("clear || cls");
        return;
    }

    do {
    cout << "Password: ";
    cin.getline(pass, 20);
    if (strlen(pass) == 0) cout << "Password tidak boleh kosong!\n";
    } while (strlen(pass) == 0);

    // Simpan user baru
    strcpy(users[userCount].username, uname);
    strcpy(users[userCount].password, pass);
    strcpy(users[userCount].role, "user");

    userCount++;
    cout << "Registrasi berhasil!\n";
    cout << "ENTER....." << endl;
    cin.get();
    system("clear || cls");
}

int login() {
    system("clear || cls");
    char user[20], pass[20];
    cout << "\n--- Login ---\n";
    cout << "Username: "; cin.ignore(); cin.getline(user, 20);
    cout << "Password: "; cin.getline(pass, 20);
    system("clear || cls");
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

void tambahDonasi(int userid) {
    if (donasiCount >= MAX_DONASI) {
        cout << "Donasi penuh.\n";
        cout << "ENTER....." << endl;
        cin.get();
        system("clear || cls");
        return;
    }
    cout << "\n--- Donasi ---\n";
    tampilKategori();
    int pilih;
    cout << "Pilih kategori (1-" << kategoriCount << "): ";
    if (!(cin >> pilih)) {
        cout << "Input tidak valid (harus angka).\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cin.get();
        system("clear || cls");
        return;
    }

    if (pilih < 1 || pilih > kategoriCount) {
        cout << "Pilihan tidak valid.\n";
        cin.ignore();
        cin.get();
        system("clear || cls");
        return;
    }
    strcpy(donasi[donasiCount].kategori, kategoriDonasi[pilih-1]);

    cout << "Masukkan nominal donasi: "; 
    if (!(cin >> donasi[donasiCount].nominal)) {
        cout << "Input nominal tidak valid.\n";
        cin.clear(); cin.ignore(10000, '\n');
        cin.get(); system("clear || cls");
        return;
    }

    if (donasi[donasiCount].nominal < 1000) {
        cout << "Minimal donasi adalah Rp. 1000\n";
        cin.ignore();
        cin.get();
        system("clear || cls");
        return;
    }

    cin.ignore(); // agar tidak loncat get()
    strcpy(donasi[donasiCount].nama, users[userid].username);
    strcpy(donasi[donasiCount].kategori, kategoriDonasi[pilih - 1]);
    strcpy(donasi[donasiCount].status, "Pending");
    donasiCount++;

    cout << "\nDonasi berhasil disimpan!";
    cout << "\nTerima kasih atas kebaikan Anda!\n";
    cin.get();
    system("clear || cls");
}

void lihatRiwayat(int userid) {
    bool adaRiwayat = false;
    cout << "\n--- Riwayat Donasi ---\n";
    int nomor = 1;
    for (int i = 0; i < donasiCount; i++) {
        if (strcmp(donasi[i].nama, users[userid].username) == 0) {
            cout << nomor << ". " << donasi[i].kategori << " - Rp." << donasi[i].nominal << " - " << donasi[i].status << endl;
            adaRiwayat = true;
            nomor++;
        }
    }if (!adaRiwayat) {
        cout << "Belum memiliki riwayat donasi";
    }
    cout << "\nTekan ENTER untuk kembali ke menu user...";
    cin.get();   
    system("clear || cls");
}

void tambahKategori() {
    system("clear || cls");
    if (kategoriCount >= MAX_KATEGORI) {
        cout << "Kategori penuh.\n";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "Masukkan nama kategori baru: ";
    cin.ignore(); cin.getline(kategoriDonasi[kategoriCount], 30);
    kategoriCount++;
    cout << "Kategori berhasil ditambahkan!\n";
    cout << "ENTER....." << endl;
    cin.get();
    system("clear || cls");
}

void hapusKategori() {
    system("clear || cls");
    tampilKategori();
    int pilih;
    cout << "Pilih kategori yang ingin dihapus: "; cin >> pilih; cin.ignore();
    
    if (pilih < 1 || pilih > kategoriCount) {
        cout << "Pilihan tidak valid.\n";
        cin.get();
        system("clear || cls");
        return;
    }

    cin.ignore();

    if (pilih < 1 || pilih > kategoriCount) {
        cout << "Pilihan tidak valid.\n";
        cin.get();
        system("clear || cls");
        return;
    }

    for (int i = pilih-1; i < kategoriCount-1; i++) {
        strcpy(kategoriDonasi[i], kategoriDonasi[i+1]);
    }
    kategoriCount--;
    cout << "Kategori berhasil dihapus.\n";
    cout << "ENTER....." << endl;
    cin.get();
    system("clear || cls");
}

void updateStatus() {
    system("clear || cls");
    for (int i = 0; i < donasiCount; i++) {
        cout << i+1 << ". " << donasi[i].nama << " - " << donasi[i].kategori << " - Rp." << donasi[i].nominal << " - " << donasi[i].status << endl;
    }
    int pilih;
    cout << "Pilih nomor donasi yang ingin diupdate: "; 

    if (!(cin >> pilih)) {
    cout << "Input tidak valid (harus angka).\n";
    cin.clear();
    cin.ignore(10000, '\n');
    cin.get();
    system("clear || cls");
    return;
    }

    if (pilih < 1 || pilih > donasiCount) {
    cout << "Nomor donasi tidak valid.\n";
    cin.get();
    system("clear || cls");
    return;
}

cin.ignore();

    cout << "\n=== Konfirmasi Status Donasi ===\n";
    cout << "Terima donasi ini? (y/n): ";
    char konfirmasi;
    cin >> konfirmasi;
    cin.ignore();

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        strcpy(donasi[pilih-1].status, "Terima");
        cout << "Status donasi berhasil diperbarui!\n";
    } else {
        cout << "Status tidak diubah.\n";
    }
    cout << "ENTER....." << endl;
    cin.get();
    system("clear || cls");
}

void sortDonasiAZ() {
    for (int i = 0; i < donasiCount-1; i++) {
        for (int j = i+1; j < donasiCount; j++) {
            if (strcmp(donasi[i].nama, donasi[j].nama) > 0) {
                swap(donasi[i], donasi[j]);
            }
        }
    }
}

void sortDonasiZA() {
    for (int i = 0; i < donasiCount-1; i++) {
        for (int j = i+1; j < donasiCount; j++) {
            if (strcmp(donasi[i].nama, donasi[j].nama) < 0) {
                swap(donasi[i], donasi[j]);
            }
        }
    }
}

void sortNominalTinggi() {
    for (int i = 0; i < donasiCount-1; i++) {
        for (int j = i+1; j < donasiCount; j++) {
            if (donasi[i].nominal < donasi[j].nominal) {
                swap(donasi[i], donasi[j]);
            }
        }
    }
}

void cariDonatur() {
    char nama[20];
    cout << "Masukkan nama donatur: "; 
    cin.ignore();
    cin.getline(nama, 20);
    bool ketemu = false;
    for (int i = 0; i < donasiCount; i++) {
        if (strcmp(donasi[i].nama, nama) == 0) {
            cout << donasi[i].kategori << " - Rp." << donasi[i].nominal << " - " << donasi[i].status << endl;
            ketemu = true;
        }
    }
    if (!ketemu) cout << "Donatur tidak ditemukan.\n";
}

void lihatDonasi() {
    system("clear || cls");
    int pilih;
    do {
        cout << "\n1. Lihat donasi (A-Z)\n2. Lihat donasi (Z-A)\n3. Nominal tertinggi-terendah\n4. Cari donatur\n5. Kembali\nPilihan: ";
        if (!(cin >> pilih)) {
        cout << "Input harus berupa angka.\n";
        cin.clear();             
        cin.ignore(10000, '\n');
        cin.get();
        system("clear || cls");
        continue;
        }
        
        system("clear || cls");
        switch (pilih) {
            case 1: sortDonasiAZ(); break;
            case 2: sortDonasiZA(); break;
            case 3: sortNominalTinggi(); break;
            case 4: cariDonatur(); continue;
            case 5: return;
            default: cout << "Pilihan tidak valid.\n";
                cin.get();
                system("clear || cls");
                continue;
        }
        for (int i = 0; i < donasiCount; i++) {
            cout << donasi[i].nama << " - " << donasi[i].kategori << " - Rp." << donasi[i].nominal << " - " << donasi[i].status << endl;
        }if (pilih != 5) {
        cout << "\nTekan enter untuk kembali...";
        cin.get();
        system("clear || cls");
        }
    } while (pilih != 5);
}

void lihatKategori() {
    system("clear || cls");
    cout << "\n=== Kategori Donasi ===\n";
    for (int i = 0; i < kategoriCount; i++) {
        cout << i+1 << ". " << kategoriDonasi[i] << endl;
    }
    cout << "\nTekan enter untuk kembali...";
    cin.get();
    system("clear || cls");
}

void menuUser(int id) {
    system("clear || cls");
    int pilih;
    do {
        cout << "_____________________________\n";
        cout << "|   Selamat Datang Donatur  |\n";
        cout << "|---------------------------|\n";
        cout << "|      1. Donasi            |\n";
        cout << "|      2. Lihat Riwayat     |\n";
        cout << "|      3. Logout            |\n";
        cout << "|___________________________|\n";
        cout << "Pilihan: ";

        if (!(cin >> pilih)) {
            cout << "Input harus berupa angka.\n";
            cin.clear();             
            cin.ignore(10000, '\n');
            cin.get();
            system("clear || cls");
            continue;
        }
        cin.ignore();
        system("clear || cls");

        if (pilih == 1) tambahDonasi(id);
        else if (pilih == 2) lihatRiwayat(id);
        else if (pilih != 3) {
            cout << "Pilihan tidak valid\n";
            cin.get();
        }
    } while (pilih != 3);
}

void menuAdmin() {
    system("clear || cls");
    int pilih;
    do {
        cout << "________________________________\n";
        cout << "|     Selamat Datang Admin     |\n";
        cout << "|------------------------------|\n";
        cout << "|     1. Lihat Donasi          |\n";
        cout << "|     2. Lihat Kategori        |\n";
        cout << "|     3. Tambah Kategori       |\n";
        cout << "|     4. Hapus Kategori        |\n";
        cout << "|     5. Update Status Donasi  |\n";
        cout << "|     6. Logout                |\n";
        cout << "|______________________________|\n";
        cout << "Pilihan: ";
        
        if (!(cin >> pilih)) {
            cout << "Input harus berupa angka.\n";
            cin.clear();             
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();
        system("clear || cls");
        if (pilih == 1) lihatDonasi();
        if (pilih == 2) lihatKategori();
        else if (pilih == 3) tambahKategori();
        else if (pilih == 4) hapusKategori();
        else if (pilih == 5) updateStatus();
        else if (pilih == 6) break;
    } while (pilih != 5);
}


int main() {
    system("clear || cls");
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin");
    strcpy(users[0].role, "admin");
    int pilihan;
    do {
        cout << "_______________________\n";
        cout << "|    Sistem Donasi    |\n";
        cout << "|---------------------|\n";
        cout << "|     1. Register     |\n";
        cout << "|     2. Login        |\n";
        cout << "|     3. Keluar       |\n";
        cout << "|_____________________|\n";
        cout << "Pilihan: ";
        
        if (!(cin >> pilihan)) {
            cout << "Input harus berupa angka.\n";
            cin.clear();              // Reset error state
            cin.ignore(10000, '\n');  // Buang semua karakter sampai newline
            cin.get();
            system("clear || cls");
            continue;  // Kembali ke awal loop
        }

        if (pilihan == 1) registrasi();
        else if (pilihan == 2) {
            int id = login();
            if (id == -1) {cout << "Login gagal.\nEnter.....";
                cin.get();
                system("clear || cls");
            }
            else if (strcmp(users[id].role, "admin") == 0) menuAdmin();
            else menuUser(id);
        }else if (pilihan != 3){
            cout << "Pilihan tidak valid\n";
            cin.ignore();
            cin.get();
            system("cls || clear");
        }else if (pilihan == 3){
            cout << "Terimakasih telah menggunakan program kami";
        }
    } while (pilihan != 3);
    return 0;
}