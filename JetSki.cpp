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
    string password;
    string merk;
};

struct nodejetski {
    jetski ski;
    nodejetski*next;
    nodejetski*prev;
};

struct nodepenyewa {
    penyewa user;
    nodepenyewa*next;
    nodepenyewa*prev;
};

struct nodejetski*head=NULL;
struct nodejetski*last=NULL;

struct nodepenyewa*headpenyewa;
struct nodepenyewa*lastpenyewa;


bool kosong(){
    return head==NULL;
}


bool isQueueEmpty() {
    return headpenyewa == nullptr;
}

int length(nodejetski *head)
{
    int count = 0;
    nodejetski*temp = head;
    while (temp != NULL)
    {
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

void lihatData(){
    setColor(3);
    cout << "========================================" << endl;
    setColor(10);    cout << "               DATA DRONE               " << endl;
    setColor(3);
    cout << "========================================" << endl;
    if(kosong()){
        setColor(4);
        cout << "Data kosong, tidak ada yang bisa ditampilkan"<<endl;
        setColor(3);
        cout << "========================================" << endl;
        cout << "\n Tekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }
    else{
        int hitung = 1;
        nodejetski*temp=head;
        while (temp != NULL) {
            cout << "data ke-" << hitung << endl;
            cout << "data ke-" << temp->ski.id << endl;
            cout << "Merk JetSki : " << temp->ski.merk << endl;
            cout << "Harga Jetski : " << temp->ski.harga << endl;
            cout << "Status jetSki : " << temp->ski.status << endl;
            cout << "========================================" << endl;


            temp = temp->next;
            hitung += 1;
        }
    }
}

int tambahJetSki(jetski ski, int& nextId){

    cout << "========================================" << endl;
    cout << "           TAMBAH DATA DRONE            " << endl;
    cout << "========================================" << endl;
    cout << "Masukkan merk JetSki : ";
    getline (cin, ski.merk);
    cout << "Masukkan harga JetSki : ";
    cin >> ski.harga;

    //set status jetski secara statis
    ski.status = "Tidak Disewa";
    //set id jetski
    ski.id = nextId++;

    if (kosong()) {
        nodejetski*baru=new nodejetski;
        baru->ski=ski;
        baru->next=NULL;
        baru->prev=NULL;
        head=baru;
        last=baru;
    } else{
    nodejetski*baru=new nodejetski;
    baru->ski=ski;
    baru->prev=last;
    last->next=baru;
    baru->next=NULL;
    last=baru;
    }

    return 0;
}

void hapusjetSki (nodejetski *&head) {
    string merk;
    lihatData();
    nodejetski *temp = head;

    if (temp == nullptr) {
        cout << "Data tidak ditemukan..." << endl;
        cout << "========================================" << endl;
        return;
    }

    cout << "========================================" << endl;
    cout << "            HAPUS DATA DRONE            " << endl;
    cout << "========================================" << endl;
    cout << "Masukkan merk drone yang ingin dihapus : ";
    getline(cin, merk);

    if (temp->ski.merk == merk) {
        head = temp->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        cout << "Data dengan merk " << merk << " berhasil dihapus." << endl;
        return;
    }

    while (temp != nullptr && temp->ski.merk != merk) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Data tidak ditemukan..." << endl;
        return;
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }

    delete temp;
    cout << "Data dengan merk " << merk << " berhasil dihapus." << endl;
}

void ubahJetSki (nodejetski *head){
    int ubah;
    lihatData();
    nodejetski *temp = head;

    if (temp == nullptr) {
        return;
    }

    cout << "========================================" << endl;
    cout << "            UBAH DATA JETSKI            " << endl;
    cout << "========================================" << endl;
    cout << "Masukkan id jetski yang ingin diubah : ";
    cin >> ubah;
    cout << endl;

    while(temp != nullptr && temp->ski.id != ubah){
        temp = temp->next;
    }

    if (temp == nullptr){
        cout << "Data tidak ditemukan..." << endl;
        cout << "========================================" << endl;
        return;
    }


    cout << "Masukkan merk drone baru: ";
    getline(cin, temp->ski.merk);
    cout << "Masukkan harga drone baru: ";
    cin >> temp->ski.harga;

    cout << "\nData dengan id " << ubah << " berhasil diubah." << endl;
}

// Fibonacci Search
int fibMonaccianSearch(nodejetski *head, int x, int n)
{
    nodejetski *temp = head;
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }
    int offset = -1;
    while (fibM > 1)
    {
        int i = min(offset + fibMMm2, n - 1);

        temp = head;
        for (int j = 0; j < i; j++)
        {
            temp = temp->next;
        }
        if (temp->ski.id < x)
        {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (temp->ski.id > x)
        {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else
            return i;
    }
    temp = head;
    for (int j = 0; j < offset + 1; j++)
    {
        temp = temp->next;
    }
    if (fibMMm1 && temp->ski.id == x)
        return offset + 1;
    return -1;
}

// Jump Search
int findnode(nodejetski *head, int idx)
{
    for (int i = 0; i < idx; i++)
    {
        head = head->next;
    }
    return head->ski.harga;
}

int jumpSearch(nodejetski *head, int x, int n)
{
    int step = sqrt(n);
    int prev = 0;

    int idx = min(step, n) - 1;
    while (findnode(head, idx) < x)
    {
        prev = step;
        step += sqrt(n);
        idx = min(step, n) - 1;
        if (prev >= n)
        {
            return -1;
        }
    }
    while (findnode(head, prev) < x)
    {
        prev++;
    }
    if (findnode(head, prev) == x)
    {
        return prev;
    }
    return -1;
}

// Boyer-Moore
const int NO_OF_CHARS = 256;
void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
    {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++)
    {
        badChar[(int)str[i]] = i;
    }
}

void search(nodejetski*head, string pat)
{
    int m = pat.size();
    nodejetski *temp = head;
    while (temp != NULL)
    {
        int n = temp->ski.merk.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badChar);
        int s = 0;

        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && pat[j] == temp->ski.merk[s + j])
            {
                j--;
            }
            if (j < 0)
            {
                cout << temp->ski.merk << endl;
                break;
            }
            else
            {
                s += max(1, j - badChar[temp->ski.merk[s + j]]);
            }
        }
        temp = temp->next;
    }
}

void menuSearch(){
    int c, x, idx;
    string xs;

    int pilih;
    cout << "========================================" << endl;
    cout << "               CARI DATA                " << endl;
    cout << "========================================" << endl;
    cout << " 1. Harga JetSki (Fibonacci Search)     " << endl;
    cout << " 2. Harga JetSki (Jump Search)          " << endl;
    cout << " 3. Merk JetSki (Boyer-Moore Search)    " << endl;
    cout << " 0. Kembali                             " << endl;
    cout << "========================================" << endl;
    cout << "Masukkan pilihan anda : ";
    cin >> pilih;
    cin.ignore();

    switch (pilih){
        case 1:

            if (kosong()) {
                cout << "Data JetSki kosong, tidak ada yang bisa dicari" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                return;
            }

            lihatData();
            cout << "Cari Harga JetSki: ";
            cin >> x;

            idx = fibMonaccianSearch(head, x, length(head));
            if (idx >= 0)
            {
                cout << "Found at index: " << idx << endl;
                nodejetski *current = head;
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
            }
            else
            {
                cout << x << " isn't present in the array" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                break;
            }
        case 2:

            if (kosong()) {
                cout << "Data drone kosong, tidak ada yang bisa dicari" << endl;
                cout << "\n Tekan Enter untuk melanjutkan...";
                cin.get();
                return;
            }

            lihatData();
            cout << "Cari data stok drone : ";
            cin >> x;

            idx = jumpSearch(head, x, length(head));
            if (idx >= 0)
            {
                cout << "Found at index: " << idx << endl;
                nodejetski*current = head;
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
            }
            else
            {
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
            sleep_for(seconds(2));
            system("cls");
            break;
        default:
            cout << "INPUT INVALID!" << endl;
            cout << "\n Tekan Enter untuk melanjutkan...";
            cin.get();
    }
}

int main() {
    int pilih;
    jetski ski;
    int nextId = 1;

    while (true) {
        while (true) {
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
        cout << "  4. Hapus JetSki                      " << endl;
        cout << "  5. Cari JetSki                        " << endl;
        cout << "  6. Lihat Antrian JetSki               " << endl;
        cout << "  7. Layani Antrian JetSki              " << endl;
        cout << "  0. Keluar                             " << endl;
        setColor(3);
        cout << "========================================" << endl;
        setColor(10);
        cout << "Enter > ";
        setColor(6);


         if (cin >> noskipws >> pilih && pilih >= 0 && pilih <= 8){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
         }else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan karakter yang tersisa dalam buffer
            system("cls");
            setColor(4);
            cout << "========================================" << endl;
            cout << "           PILIHAN TIDAK VALID          " << endl;
            cout << "========================================" << endl;
            sleep_for(seconds(2));
            system("cls");
            }
        }

        switch (pilih)
        {
        case 1:
            system("cls");
            setColor(7);
            cout << "Loading..." << endl;
            sleep_for(seconds(2));
            system("cls");
            tambahJetSki(ski, nextId);
            break;
        case 2:
            system("cls");
            setColor(7);
            cout << "Loading..." << endl;
            sleep_for(seconds(2));
            system("cls");
            lihatData();
            break;
        case 3:
            system("cls");
            setColor(7);
            cout << "Loading..." << endl;
            sleep_for(seconds(2));
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
            cout << "nanti ada menu disini" << endl;
            break;
        case 7:
            system("cls");
            setColor(7);
            cout << "Loading..." << endl;
            sleep_for(seconds(2));
            system("cls");
            cout << "nanti ada menu disini" << endl;
            break;
        case 0:
            system("cls");
            setColor(7);
            cout << "Keluar dari program..." << endl;
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
    }
}
