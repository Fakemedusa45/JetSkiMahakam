#include <iostream>
#include <limits>
#include <windows.h>
#include <chrono>
#include <thread>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;
using namespace chrono;
using namespace this_thread;

//kode warna :
//    3 = tabel
//    10 = tulisan (kecuali eror)
//    6 = inputan
//    4 = eror
//    7 = loading

struct jetski {
    int id;
    string merk;
    long harga;
    string status;
};

struct penyewa {
    string nama;
    string no_hp;
    string alamat;
    string paket;
    int durasi;
    string hari;
    string jam;
    string merk;
};

struct nodejetski {
    jetski ski;
    nodejetski* next;
    nodejetski* prev;
};

struct nodepenyewa {
    penyewa user;
    nodepenyewa* next;
    nodepenyewa* prev;
};

struct nodejetski* head = NULL;
struct nodejetski* last = NULL;
struct nodepenyewa* headpenyewa = NULL;
struct nodepenyewa* lastpenyewa = NULL;

bool kosong() {
    return head == NULL;
}

int length(nodejetski* head) {
    int count = 0;
    nodejetski* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int min(int x, int y) { return (x <= y) ? x : y; }

// Prosedur untuk memberikan warna pada output
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void lihatData() {
    setColor(3);
    cout << "========================================" << endl;
    setColor(10);
    cout << "               DATA JETSKI              " << endl;
    setColor(3);
    cout << "========================================" << endl;
    if (kosong()) {
        setColor(4);
        cout << "Data kosong, tidak ada yang bisa ditampilkan" << endl;
        setColor(3);
        cout << "========================================" << endl;
        return;
    } else {
        int hitung = 1;
        nodejetski* temp = head;
        while (temp != NULL) {
                setColor(10);
                cout << "data ke-"; setColor(6); cout << hitung << endl;
                setColor(10);
                cout << "id jetski : "; setColor(6); cout << temp->ski.id << endl;
                setColor(10);
                cout << "Merk JetSki : "; setColor(6); cout << temp->ski.merk << endl;
                setColor(10);
                cout << "Harga Jetski : "; setColor(6); cout << "Rp " << temp->ski.harga << endl;
                setColor(10);
                cout << "Status jetSki : "; setColor(6); cout << temp->ski.status << endl;
                setColor(3);
                cout << "========================================" << endl;
                hitung += 1;
            temp = temp->next;
        }
    }
}

int tambahJetSki(jetski ski, int& nextId) {
    setColor(3);
    cout << "========================================" << endl;
    setColor(10);
    cout << "           TAMBAH DATA JETSKI            " << endl;
    setColor(3);
    cout << "========================================" << endl;
    setColor(10);
    cout << "Masukkan merk jetski : ";
    setColor(6);
    getline(cin, ski.merk);
    setColor(10);
    cout << "Masukkan harga jetski : ";
    setColor(6);    cin >> ski.harga;
    cin.clear();

    //set status jetski secara statis
    ski.status = "Tidak Disewa";
    //set id jetski
    ski.id = nextId++;

    nodejetski* baru = new nodejetski;
    baru->ski = ski;
    baru->next = NULL;

    if (kosong()) {
        baru->prev = NULL;
        head = baru;
        last = baru;
    } else {
        baru->prev = last;
        last->next = baru;
        last = baru;
    }
    cin.ignore();
    return 0;
}

void hapusjetSki(nodejetski*& head) {
    system("cls");
    int id_temp;
    lihatData();
    nodejetski* temp = head;

    if (kosong()){
        sleep_for(milliseconds(1000));
        return;
    }

    setColor(3);
    cout << "========================================" << endl;
    setColor(10);
    cout << "            HAPUS DATA JETSKI            " << endl;
    setColor(3);
    cout << "========================================" << endl;
    setColor(10);
    cout << "Masukkan merk jetski yang ingin dihapus : ";
    setColor(6);    cin >> id_temp;

    if (temp->ski.id == id_temp) {
        head = temp->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        cout << "Data dengan id " << id_temp << " berhasil dihapus." << endl;
        return;
    }

    while (temp != nullptr && temp->ski.id != id_temp) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        setColor(3);
        cout << "========================================" << endl;
        setColor(4);
        cout << "          Data tidak ditemukan          " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "\n Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }

    delete temp;
    cout << "Data dengan id " << id_temp << " berhasil dihapus." << endl;
}

void ubahJetSki(nodejetski* head) {
    int ubah;
    lihatData();
    nodejetski* temp = head;

    if (kosong()){
        sleep_for(milliseconds(1000));
        return;
    }

    setColor(3);
    cout << "========================================" << endl;
    setColor(10);    cout << "            UBAH DATA JETSKI            " << endl;
    setColor(3);
    cout << "========================================" << endl;

    setColor(10);
    cout << "Masukkan id jetski yang ingin diubah : ";
    setColor(6);
    cin >> ubah;
    cin.ignore();
    cout << endl;

    while (temp != nullptr && temp->ski.id != ubah) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        setColor(3);
        cout << "========================================" << endl;
        setColor(4);
        cout << "          Data tidak ditemukan          " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "\n Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    setColor(10);
    cout << "Masukkan merk jetski baru: ";
    setColor(6);
    getline(cin, temp->ski.merk);
    setColor(10);
    cout << "Masukkan harga jetski baru: ";
    setColor(6);
    cin >> temp->ski.harga;
    cin.ignore();

    cout << "\nData dengan id " << ubah << " berhasil diubah." << endl;
}

// Fibonacci Search
int fibMonaccianSearch(nodejetski* head, int x, int n) {
    nodejetski* temp = head;
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        temp = head;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }
        if (temp->ski.id < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (temp->ski.id > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }
    temp = head;
    for (int j = 0; j < offset + 1; j++) {
        temp = temp->next;
    }
    if (fibMMm1 && temp->ski.id == x) {
        return offset + 1;
    }
    return -1;
}

// Jump Search
int findnode(nodejetski* head, int idx) {
    for (int i = 0; i < idx; i++) {
        head = head->next;
    }
    return head->ski.harga;
}

int jumpSearch(nodejetski* head, int x, int n) {
    int step = sqrt(n);
    int prev = 0;

    int idx = min(step, n) - 1;
    while (findnode(head, idx) < x) {
        prev = step;
        step += sqrt(n);
        idx = min(step, n) - 1;
        if (prev >= n) {
            return -1;
        }
    }
    while (findnode(head, prev) < x) {
        prev++;
    }
    if (findnode(head, prev) == x) {
        return prev;
    }
    return -1;
}

// Boyer-Moore
const int NO_OF_CHARS = 256;
void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badChar[(int)str[i]] = i;
    }
}

void search(nodejetski* head, string pat) {
    int m = pat.size();
    nodejetski* temp = head;
    while (temp != NULL) {
        int n = temp->ski.merk.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);
        int s = 0;

        while (s <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && pat[j] == temp->ski.merk[s + j]) {
                j--;
            }
            if (j < 0) {
                cout << temp->ski.merk << endl;
                break;
            } else {
                s += max(1, j - (s + j < n ? badChar[(unsigned char)temp->ski.merk[s + j]] : -1));
            }
        }
        temp = temp->next;
    }
}

void menuSearch() {
    int x, idx;
    string xs;
    int pilih;

    while (true) {
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "               CARI DATA                " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << " 1. Id JetSki (Fibonacci Search)        " << endl;
        cout << " 2. Harga JetSki (Jump Search)          " << endl;
        cout << " 3. Merk JetSki (Boyer-Moore Search)    " << endl;
        cout << " 0. Kembali                             " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(3);
        cout << "Masukkan pilihan anda : ";
        setColor(6);

        if (cin >> noskipws >> pilih && pilih >= 0 && pilih <= 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter yang tersisa dalam buffer
            system("cls");
            setColor(4);
            cout << "========================================" << endl;
            cout << "           PILIHAN TIDAK VALID          " << endl;
            cout << "========================================" << endl;
            sleep_for(milliseconds(1000));
            system("cls");
        }
    }

    switch (pilih) {
        case 1:
            if (kosong()) {
                setColor(3);
                cout << "========================================" << endl;
                setColor(4);
                cout << "Data kosong, tidak ada yang bisa dicari " << endl;
                setColor(3);
                cout << "========================================" << endl;
                setColor(10);
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                return;
            }

            lihatData();
            cout << "Cari Harga JetSki: ";
            cin >> x;

            idx = fibMonaccianSearch(head, x, length(head));
            if (idx >= 0) {
                cout << "Found at index: " << idx << endl;
                nodejetski* current = head;
                for (int i = 0; i < idx; i++) {
                    current = current->next;
                }

                cout << "========================================" << endl;
                cout << "Merk JetSki : " << current->ski.merk << endl;
                cout << "Harga JetSki : " << current->ski.harga << endl;
                cout << "Status JetSki : " << current->ski.status << endl;
                cout << "========================================" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                cin.ignore();
                break;
            } else {
                cout << x << " isn't present in the array" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                break;
            }
        case 2:
            if (kosong()) {
                cout << "Data jetski kosong, tidak ada yang bisa dicari" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                return;
            }

            lihatData();
            cout << "Cari data stok drone : ";
            cin >> x;

            idx = jumpSearch(head, x, length(head));
            if (idx >= 0) {
                cout << "Found at index: " << idx << endl;
                nodejetski* current = head;
                for (int i = 0; i < idx; i++) {
                    current = current->next;
                }

                cout << "========================================" << endl;
                cout << "Merk JetSki : " << current->ski.merk << endl;
                cout << "Harga JetSki : " << current->ski.harga << endl;
                cout << "Status JetSki : " << current->ski.status << endl;
                cout << "========================================" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                cin.ignore();
                break;
            } else {
                cout << x << " isn't present in the array" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                break;
            }
        case 3:
            if (kosong()) {
                cout << "Data drone kosong, tidak ada yang bisa dicari" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                return;
            }

            lihatData();
            cout << "Cari string: ";
            cin >> xs;

            search(head, xs);
            cout << "\n Tekan Enter untuk melanjutkan...";
            cin.get();
            break;
        case 0:
            system("cls");
            setColor(7);
            cout << "Loading..." << endl;
            sleep_for(milliseconds(1000));
            system("cls");
            break;
        default:
            cout << "INPUT INVALID!" << endl;
            cout << "\n Tekan Enter untuk melanjutkan...";
            cin.get();
    }
}

void swapJetSki(jetski& a, jetski& b) {
    jetski temp = a;
    a = b;
    b = temp;
}

//QUICK SORT
nodejetski* partition(nodejetski* low, nodejetski* high) {
    long pivot = high->ski.harga;
    nodejetski* i = low->prev;

    for (nodejetski* j = low; j != high; j = j->next) {
        if (j->ski.harga >= pivot) {
            i = (i == nullptr) ? low : i->next;
            swapJetSki(i->ski, j->ski);
        }
    }
    i = (i == nullptr) ? low : i->next;
    swapJetSki(i->ski, high->ski);
    return i;
}

void quickSort(nodejetski* low, nodejetski* high) {
    if (high != nullptr && low != high && low != high->next) {
        nodejetski* pi = partition(low, high);
        quickSort(low, pi->prev);
        quickSort(pi->next, high);
    }
}

void quickSortDesc() {
    if (head == nullptr) return;
    quickSort(head, last);
}

//SHELL SORT
void shellSort(nodejetski* head) {
    int n = 0;
    nodejetski* temp = head;

    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    jetski* arr = new jetski[n];
    temp = head;
    for (int i = 0; i < n; i++) {
        arr[i] = temp->ski;
        temp = temp->next;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            jetski temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].id > temp.id; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }

    temp = head;
    for (int i = 0; i < n; i++) {
        temp->ski = arr[i];
        temp = temp->next;
    }

    delete[] arr;
}

void menuSorting() {
    int pilih;

    while (true) {
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "               LIHAT DATA               " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << " 1. id JetSki (Shell Sort)              " << endl;
        cout << " 2. Harga JetSki (Quick Sort)           " << endl;
        cout << " 0. Kembali                             " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "Masukkan pilihan anda : ";
        setColor(6);

        if (cin >> noskipws >> pilih && pilih >= 0 && pilih <= 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter yang tersisa dalam buffer
            system("cls");
            setColor(4);
            cout << "========================================" << endl;
            cout << "           PILIHAN TIDAK VALID          " << endl;
            cout << "========================================" << endl;
            sleep_for(milliseconds(1000));
            system("cls");
        }
    }

    switch (pilih) {
        case 1:
            system("cls");
            setColor(7);
            cout << "Loading..." << endl;
            sleep_for(milliseconds(1000));
            system("cls");
            shellSort(head);
            lihatData();
            setColor(10);
            cout << "\n Tekan Enter untuk melanjutkan...";
            cin.get();
            break;
        case 2:
            system("cls");
            setColor(7);
            cout << "Loading..." << endl;
            sleep_for(milliseconds(1000));
            system("cls");
            quickSortDesc();
            lihatData();
            setColor(10);
            cout << "\n Tekan Enter untuk melanjutkan...";
            cin.get();
            break;
        case 0:
            system("cls");
            setColor(7);
            cout << "Loading..." << endl;
            sleep_for(milliseconds(1000));
            system("cls");
            break;
    }
}

void lihatKetersediaanJetski(); // Deklarasi fungsi

void bookingJetski() {
    system("cls");
    penyewa user; // Struktur untuk menyimpan data penyewa
    setColor(3);    
    cout << "========================================" << endl;
    setColor(10);
    cout << "           BOOKING JETSKI               " << endl;
    setColor(3);
    cout << "========================================" << endl;

    if (kosong()) {
        setColor(3);
        cout << "========================================" << endl;
        setColor(4);
        cout << "    Data kosong, tidak bisa booking     " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "\n Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    // Tampilkan data jetski untuk dipilih
    lihatKetersediaanJetski(); // Menampilkan semua jetski yang tersedia
    int id_jetski; // Variabel untuk menyimpan ID jetski yang dipilih
    setColor(10);
    cout << "Masukkan ID Jetski yang ingin dipesan: ";
    setColor(6);
    cin >> id_jetski;
    cin.ignore(); // Mengabaikan newline setelah input

    // Mencari jetski berdasarkan ID
    nodejetski* temp = head;
    while (temp != nullptr) {
        if (temp->ski.id == id_jetski) {
            // Cek apakah jetski sudah disewa
            if (temp->ski.status == "Disewa") {
                setColor(4);
                cout << "Jetski dengan ID " << id_jetski << " sudah disewa." << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                return;
            }
            // Jika jetski ditemukan dan tidak disewa, ubah statusnya menjadi "Disewa"
            temp->ski.status = "Disewa";
            break;
        }
        temp = temp->next;
    }

    if (temp == nullptr) {
        setColor(4);
        cout << "ID Jetski tidak ditemukan." << endl;
        cout << "\n Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    // Input data diri pengguna
    cout << "Masukkan nama: ";
    getline(cin, user.nama);
    cout << "Masukkan nomor HP: ";
    while (true) {
        getline(cin, user.no_hp);
        // Cek apakah input hanya terdiri dari angka
        if (all_of(user.no_hp.begin(), user.no_hp.end(), ::isdigit)) {
            break;
        } else {
            cout << "Input tidak valid. Masukkan hanya angka: ";
        }
    }
    cout << "Masukkan alamat: ";
    getline(cin, user.alamat);

    // Tambahkan input untuk hari dan jam booking
    string hari, jam;
    cout << "Masukkan hari booking : ";
    while (true) {
        getline(cin, hari);
        // Cek apakah input adalah salah satu hari yang valid
        if (hari == "senin" || hari == "selasa" || hari == "rabu" ||
            hari == "kamis" || hari == "jumat" || hari == "sabtu") {
            break;
        } else {
            cout << "Input tidak valid. Masukkan hari yang valid: ";
        }
    }

    cout << "Masukkan jam booking (format 24 jam): ";
    while (true) {
        getline(cin, jam);
        // Cek apakah input hanya terdiri dari angka
        if (all_of(jam.begin(), jam.end(), ::isdigit)) {
            break;
        } else {
            cout << "Input tidak valid. Masukkan hanya angka: ";
        }
    }

    // Simpan hari dan jam ke dalam struktur penyewa
    user.hari = hari; // Simpan hari
    user.jam = jam;   // Simpan jam

    // Pilihan paket
    cout << "Pilih paket yang tersedia:" << endl;
    cout << "1. Paket Regular (30 menit)" << endl;
    cout << "2. Paket Premium (60 menit)" << endl;
    cout << "Masukkan pilihan paket (1/2): ";
    int pilihanPaket;
    cin >> pilihanPaket;

    // Set paket berdasarkan pilihan
    if (pilihanPaket == 1) {
        user.paket = "Regular (30 menit)";
        user.durasi = 30; // durasi dalam menit
    } else if (pilihanPaket == 2) {
        user.paket = "Premium (60 menit)";
        user.durasi = 60; // durasi dalam menit
    } else {
        cout << "Pilihan tidak valid." << endl;
        return;
    }

    // Tampilkan konfirmasi booking
    cout << "Booking berhasil!" << endl;
    cout << "Nama: " << user.nama << endl;
    cout << "Nomor HP: " << user.no_hp << endl;
    cout << "Alamat: " << user.alamat << endl;
    cout << "Hari Booking: " << hari << endl;
    cout << "Jam Booking: " << jam << endl;
    cout << "Paket: " << user.paket << endl;
    cout << "Durasi: " << user.durasi << " menit" << endl;
    cout << "========================================" << endl;
    cout << "\n Tekan Enter untuk melanjutkan...";
    cin.get();

    // Menyimpan data penyewa ke dalam antrian
    nodepenyewa* baru = new nodepenyewa;
    baru->user = user;
    baru->next = nullptr;
    baru->prev = nullptr;

    if (headpenyewa == nullptr) {
        headpenyewa = baru; // Jika antrian kosong, set head
        lastpenyewa = baru; // Set last juga
    } else {
        lastpenyewa->next = baru; // Tambahkan ke akhir antrian
        baru->prev = lastpenyewa;
        lastpenyewa = baru; // Update last
    }
}

// Definisi fungsi lihatKetersediaanJetski
void lihatKetersediaanJetski() {
    setColor(3);
    cout << "========================================" << endl;
    setColor(10);
    cout << "               DATA JETSKI              " << endl;
    setColor(3);
    cout << "========================================" << endl;
    if (kosong()) {
        system("cls");
        setColor(3);
        cout << "========================================" << endl;
        setColor(4);
        cout << "Data kosong, tidak ada yang bisa ditampilkan" << endl;
        setColor(3);
        cout << "========================================" << endl;
        cout << "\n Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    } else {
        int hitung = 1;
        nodejetski* temp = head;
        while (temp != NULL) {
            // Menampilkan hanya jetski yang statusnya "Tidak Disewa"
            if (temp->ski.status == "Tidak Disewa") {
                cout << "data ke-" << hitung << endl;
                cout << "id jetski : " << temp->ski.id << endl;
                cout << "Merk JetSki : " << temp->ski.merk << endl;
                cout << "Harga Jetski : " << temp->ski.harga << endl;
                cout << "Status jetSki : " << temp->ski.status << endl;
                cout << "========================================" << endl;
                hitung += 1;
            }
            temp = temp->next;
        }
    }
}

void lihatAntrian() {
    system("cls");
    // Menampilkan antrian booking yang sudah ada
    cout << "========================================" << endl;
    cout << "           LIHAT ANTRIAN               " << endl;
    cout << "========================================" << endl;

    // Cek apakah ada antrian
    if (headpenyewa == nullptr) {
        system("cls");
        setColor(3);
        cout << "========================================" << endl;
        setColor(4);
        cout << "           Tidak ada antrian            " << endl;
        setColor(3);
        cout << "========================================" << endl;
    } else {
        nodepenyewa* temp = headpenyewa;
        int hitung = 1;
        while (temp != nullptr) {
            cout << "Antrian ke-" << hitung << endl;
            cout << "Nama Penyewa: " << temp->user.nama << endl;
            cout << "Nomor HP: " << temp->user.no_hp << endl;
            cout << "Alamat: " << temp->user.alamat << endl;
            cout << "Paket: " << temp->user.paket << endl;
            cout << "Durasi: " << temp->user.durasi << " menit" << endl;
            cout << "Hari: " << temp->user.hari << endl;
            cout << "Jam: " << temp->user.jam << endl;
            cout << "========================================" << endl;

            temp = temp->next;
            hitung++;
        }
    }
    setColor(10);
    cout << "\n Tekan Enter untuk melanjutkan...";
    cin.get();
}

int user() {
    int pilih;

    while (true) {
        system("cls");
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "               MENU USER               " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "  1. Booking Jetski                    " << endl;
        cout << "  2. Lihat Antrian                     " << endl;
        cout << "  3. Lihat Ketersediaan Jetski         " << endl;
        cout << "  0. Keluar                            " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "Enter > ";
        setColor(6);

        if (cin >> noskipws >> pilih && pilih >= 0 && pilih <= 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (pilih) {
                case 1:
                    bookingJetski();
                    break;
                case 2:
                    lihatAntrian();
                    break;
                case 3:
                    lihatKetersediaanJetski();
                    break;
                case 0:
                    return 0;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter yang tersisa dalam buffer
            system("cls");
            setColor(4);
            cout << "========================================" << endl;
            cout << "           PILIHAN TIDAK VALID          " << endl;
            cout << "========================================" << endl;
            sleep_for(milliseconds(1000));
            system("cls");
        }
    }
}

void konfirmasiPengembalian(); // Deklarasi fungsi

int admin() {
    int pilih;
    jetski ski;
    int nextId = 1;

    while (true) {
        system("cls");
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "               MENU ADMIN               " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "  1. Tambah JetSki                      " << endl;
        cout << "  2. Lihat Jetski                       " << endl;
        cout << "  3. Ubah JetSki                        " << endl;
        cout << "  4. Hapus JetSki                       " << endl;
        cout << "  5. Cari JetSki                        " << endl;
        cout << "  6. Lihat Antrian JetSki               " << endl;
        cout << "  7. Layani Antrian JetSki              " << endl;
        cout << "  0. Keluar                             " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "Enter > ";
        setColor(6);

        if (cin >> noskipws >> pilih && pilih >= 0 && pilih <= 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (pilih) {
                case 1:
                    system("cls");
                    setColor(7);
                    cout << "Loading..." << endl;
                    sleep_for(milliseconds(1000));
                    system("cls");
                    tambahJetSki(ski, nextId);
                    break;
                case 2:
                    system("cls");
                    setColor(7);
                    cout << "Loading..." << endl;
                    sleep_for(milliseconds(1000));
                    system("cls");
                    menuSorting();
                    break;
                case 3:
                    system("cls");
                    setColor(7);
                    cout << "Loading..." << endl;
                    sleep_for(milliseconds(1000));
                    system("cls");
                    ubahJetSki(head);
                    break;
                case 4:
                    system("cls");
                    setColor(7);
                    cout << "Loading..." << endl;
                    sleep_for(seconds(2));
                    system("cls");
                    hapusjetSki(head);
                    break;
                case 5:
                    system("cls");
                    setColor(7);
                    cout << "Loading..." << endl;
                    sleep_for(seconds(2));
                    system("cls");
                    menuSearch();
                    break;
                case 6:
                    system("cls");
                    setColor(7);
                    cout << "Loading..." << endl;
                    sleep_for(seconds(2));
                    system("cls");
                    lihatAntrian();
                    break;
                case 7:
                    system("cls");
                    setColor(7);
                    cout << "Loading..." << endl;
                    sleep_for(seconds(2));
                    system("cls");
                    konfirmasiPengembalian();
                    break;
                case 0:
                    system("cls");
                    setColor(7);
                    cout << "Kembali..." << endl;
                    sleep_for(seconds(2));
                    system("cls");
                    setColor(3);
                    cout << "========================================" << endl;
                    setColor(10);
                    cout << "              TERIMA KASIH              " << endl;
                    setColor(3);
                    cout << "========================================" << endl;
                    return 0;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter yang tersisa dalam buffer
            system("cls");
            setColor(4);
            cout << "========================================" << endl;
            cout << "           PILIHAN TIDAK VALID          " << endl;
            cout << "========================================" << endl;
            sleep_for(milliseconds(1000));
            system("cls");
        }
    }
}

void konfirmasiPengembalian() {
    if (headpenyewa == nullptr) {
        setColor(4);
        cout << "Tidak ada antrian untuk dilayani." << endl;
        cout << "\n Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    // Ambil penyewa dari head antrian
    nodepenyewa* temp = headpenyewa;

    // Mencari jetski yang statusnya perlu diubah
    nodejetski* jetskiTemp = head;
    while (jetskiTemp != nullptr) {
        if (jetskiTemp->ski.merk == temp->user.merk) { // Asumsi merk digunakan untuk mencocokkan
            jetskiTemp->ski.status = "Tidak Disewa"; // Ubah status jetski menjadi "Tidak Disewa"
            break;
        }
        jetskiTemp = jetskiTemp->next;
    }

    // Menghapus head dari antrian
    headpenyewa = headpenyewa->next;
    if (headpenyewa != nullptr) {
        headpenyewa->prev = nullptr; // Update prev dari head baru
    } else {
        lastpenyewa = nullptr; // Jika antrian kosong, set last menjadi nullptr
    }

    // Menghapus node penyewa yang sudah dilayani
    delete temp;

    setColor(10);
    cout << "Penyewa berhasil dilayani dan status jetski diubah menjadi 'Tidak Disewa'." << endl;
    cout << "\n Tekan Enter untuk melanjutkan...";
    cin.get();
}

int main() {
    int pilih;
    while (true) {
        system("cls");
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "               MENU UTAMA               " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "  1. Admin                              " << endl;
        cout << "  2. User                               " << endl;
        cout << "  0. Keluar                             " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "Enter > ";
        setColor(6);

        if (cin >> noskipws >> pilih && pilih >= 0 && pilih <= 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (pilih) {
                case 1:
                    admin(); // Panggil fungsi admin
                    break;
                case 2:
                    user(); // Panggil fungsi user
                    break;
                case 0:
                    cout << "Keluar dari program..." << endl;
                    return 0;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter yang tersisa dalam buffer
            system("cls");
            setColor(4);
            cout << "========================================" << endl;
            cout << "           PILIHAN TIDAK VALID          " << endl;
            cout << "========================================" << endl;
            sleep_for(milliseconds(1000));
            system("cls");
        }
    }
}