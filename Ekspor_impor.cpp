#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

// Forward declarations
class User;
struct Barang;
void menuEksportir(User* user, bool& isLoggedIn);
void menuImportir(User* user, bool& isLoggedIn);
void SinkronBarangUser(string nama);
void sortingJenis();

// User class definition (keeping linked list for users)
class User {
public:
    string nama;
    string username;
    string password;
    string role;
    string asalNegara;
    User* next;

    User(string nama, string username, string password, string role, string asalNegara)
        : nama(nama), username(username), password(password), role(role), asalNegara(asalNegara), next(nullptr) {}
};

// Barang structure definition (modified for array usage)
struct Barang {
    string namaBarang;
    string jenisBarang;
    string waktuTersedia;
    double harga;
    int item;
    string pemilik;
    string asal;
    Barang() {} // Default constructor for array initialization

    Barang(string namaBarang, string jenisBarang, string waktuTersedia, double harga, int item)
        : namaBarang(namaBarang), jenisBarang(jenisBarang), waktuTersedia(waktuTersedia), harga(harga), item(item) {}
};

struct Pesanan {
    Barang barang;
    int jumlahDipesan;
    string pemesan;
    string asal_pemesan;
    string status; // pending atau kirim
};

const int MAX_BARANG = 100;  // Kapasitas maksimum barang
Barang barangArray[MAX_BARANG]; // Array barang global
int jumlahBarang = 0;  // Jumlah barang yang tersedia saat ini

vector<Pesanan> daftarPesanan; // Vektor global untuk menyimpan pesanan
string userNow;
string asalNow;
vector<Barang> barangUser; // List barang personal untuk user eksportir
vector<Pesanan> pesananUser; //List barang personan untuk user importir

void pesanBarang() {
    cout << "\nPesan Barang\n======================\n";

    // Tampilkan daftar barang yang tersedia
    if (jumlahBarang == 0) {
        cout << "[INFO] Tidak ada barang yang tersedia saat ini.\n";
        return;
    }

    for (int i = 0; i < jumlahBarang; i++) {
        cout << i + 1 << ". (" << barangArray[i].jenisBarang << ") "
             << barangArray[i].namaBarang << " - "
             << barangArray[i].pemilik << " - "
             << barangArray[i].asal << endl;
    }

    int pilihan;
    cout << "\nBarang yang ingin dipesan (nomor): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahBarang) {
        cout << "\n[ERROR] Pilihan tidak valid!\n";
        return;
    }

    Barang barangDipilih = barangArray[pilihan - 1];

    cout << "\nDetail Barang:\n";
    cout << "Nama barang: " << barangDipilih.namaBarang << endl;
    cout << "Jenis barang: " << barangDipilih.jenisBarang << endl;
    cout << "Waktu tersedia: " << barangDipilih.waktuTersedia << endl;
    cout << "Harga: $" << barangDipilih.harga << endl;
    cout << "Item: " << barangDipilih.item << endl;
    pesanBarang:
    int jumlahDipesan;
    cout << "\nJumlah item yang ingin dipesan: ";
    cin >> jumlahDipesan;

    if (jumlahDipesan > barangDipilih.item || jumlahDipesan <= 0) {
        cout << "\n[ERROR] Jumlah tidak valid atau stok tidak mencukupi!\n";
        goto pesanBarang;
    }

    char konfirmasi;
    cout << "Apakah Anda yakin ingin memesan? (Y/N): ";
    cin >> konfirmasi;

    if (konfirmasi == 'Y' || konfirmasi == 'y') {
        barangArray[pilihan - 1].item -= jumlahDipesan; // Kurangi stok
        daftarPesanan.push_back({barangDipilih, jumlahDipesan, userNow, asalNow ,"pending"});
        pesananUser.push_back(daftarPesanan[daftarPesanan.size()-1]);
        cout << "\n[SUCCESS] Pesanan berhasil dibuat!\n";
    } else {
        cout << "\n[INFO] Pesanan dibatalkan.\n";
    }
}

void daftarPemesanan() {
    cout << "\nDaftar Pemesanan\n======================\n";

    if (pesananUser.empty()) {
        cout << "[INFO] Belum ada pesanan yang dibuat.\n";
        return;
    }

    for (size_t i = 0; i < pesananUser.size(); i++) {
        cout << i + 1 << ". (" << pesananUser[i].barang.jenisBarang << ") "
             << pesananUser[i].barang.namaBarang << " - "
             << pesananUser[i].barang.pemilik << " - "
             << pesananUser[i].barang.asal << " (" 
             << pesananUser[i].status << ")\n";
    }

    int pilihan;
    cout << "\nDetail pesanan (nomor): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > pesananUser.size()) {
        cout << "\n[ERROR] Pilihan tidak valid!\n";
        return;
    }

    Pesanan pesananDipilih = daftarPesanan[pilihan - 1];
    cout << "\nDetail Pesanan:\n";
    cout << "Eksportir: " << pesananDipilih.barang.pemilik << endl;
    cout << "Negara: " << pesananDipilih.barang.asal << endl;
    cout << "Status pengiriman: " << pesananDipilih.status << endl;
    cout << "Nama barang: " << pesananDipilih.barang.namaBarang << endl;
    cout << "Jenis barang: " << pesananDipilih.barang.jenisBarang << endl;
    cout << "Waktu tersedia: " << pesananDipilih.barang.waktuTersedia << endl;
    cout << "Harga: $" << pesananDipilih.barang.harga << endl;
    cout << "Jumlah item yang dipesan: " << pesananDipilih.jumlahDipesan << endl;
    cout << "\nTekan <Enter> untuk kembali "; getchar();
}


// User management functions (unchanged)
void registerUser(User*& head, string nama, string username, string password, string role, string asalNegara) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->username == username) {
            cout << "\n[ERROR] Username sudah terdaftar!" << endl;
            return;
        }
        temp = temp->next;
    }
    User* newUser = new User(nama, username, password, role, asalNegara);
    if (head == nullptr) {
        head = newUser;
    } else {
        User* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }
    cout << "\n[SUCCESS] Pengguna berhasil didaftarkan!" << endl;
}

User* findUser(User* head, string username) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->username == username) {
            userNow = temp->nama;
            asalNow = temp->asalNegara;
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void SinkronBarangUser(string nama){
    barangUser.clear();
    for(int i=0; i<jumlahBarang; i++){
        if(barangArray[i].pemilik == nama) barangUser.push_back(barangArray[i]);
    }
}

void SinkronPesananUser(string nama){
    pesananUser.clear();
    for(int i=0; i<daftarPesanan.size(); i++){
        if(daftarPesanan[i].pemesan == nama) pesananUser.push_back(daftarPesanan[i]);
    }
}

// Implementasi fungsi tambahBarang dengan array
void tambahBarang() {
    if (jumlahBarang >= MAX_BARANG) {
        cout << "\n[ERROR] Kapasitas penyimpanan barang penuh!" << endl;
        return;
    }

    char pilihan;
    do {
        system("cls");
        cout << "\nMenambah barang\n";
        cout << "=========================\n";
        
        // Display existing items
        sortingJenis();
        for (int i = 0; i < barangUser.size(); i++) {
            cout << (i + 1) << ". (" << barangUser[i].jenisBarang << ") " 
                 << barangUser[i].namaBarang << endl;
        }

        cout << "\nTambah barang baru:\n";
        cout << "nama barang: ";
        getline(cin, barangArray[jumlahBarang].namaBarang);
        cout << "Jenis barang: ";
        getline(cin, barangArray[jumlahBarang].jenisBarang);
        cout << "Waktu tersedia: ";
        getline(cin, barangArray[jumlahBarang].waktuTersedia);
        cout << "harga: $";
        cin >> barangArray[jumlahBarang].harga;
        cout << "Item: ";
        cin >> barangArray[jumlahBarang].item;
        cin.ignore();
        barangArray[jumlahBarang].pemilik = userNow;
        barangArray[jumlahBarang].asal = asalNow;
        barangUser.push_back(barangArray[jumlahBarang]);
        jumlahBarang++;

        cout << "\nTambah barang lagi (Y/N)? ";
        cin >> pilihan;
        cin.ignore();
    } while (toupper(pilihan) == 'Y' && jumlahBarang < MAX_BARANG);
}

// Implementasi fungsi ubahBarang dengan array
void ubahBarang() {
    if (jumlahBarang == 0) {
        cout << "\n[ERROR] Tidak ada barang yang tersedia untuk diubah.\n";
        return;
    }

    char pilihan;
    do {
        system("cls");
        cout << "\nMengubah Barang\n";
        cout << "=========================\n";
        sortingJenis();
        // Display all items
        for (int i = 0; i < barangUser.size(); i++) {
            cout << (i + 1) << ". (" << barangUser[i].jenisBarang << ") " 
                 << barangUser[i].namaBarang << endl;
        }
        int choice;
        cout << "\nData yang ingin diubah: ";
        cin >> choice;
        cin.ignore();

        if (choice < 1 || choice > jumlahBarang) {
            cout << "\n[ERROR] Pilihan tidak valid!\n";
            continue;
        }

        int index = choice - 1;

        // Display current data
        cout << "\nData saat ini:\n";
        cout << "nama barang: " << barangUser[index].namaBarang << endl;
        cout << "Jenis barang: " << barangUser[index].jenisBarang << endl;
        cout << "Waktu tersedia: " << barangUser[index].waktuTersedia << endl;
        cout << "harga: $" << barangUser[index].harga << endl;
        cout << "Item: " << barangUser[index].item << endl;

        // Input new data
        cout << "\nData baru:\n";
        cout << "nama barang: ";
        getline(cin, barangUser[index].namaBarang);
        cout << "Jenis barang: ";
        getline(cin, barangUser[index].jenisBarang);
        cout << "Waktu tersedia: ";
        getline(cin, barangUser[index].waktuTersedia);
        cout << "harga: $";
        cin >> barangUser[index].harga;
        cout << "Item: ";
        cin >> barangUser[index].item;
        cin.ignore();
        cout << "\nUbah data lagi? (Y/N) ";
        cin >> pilihan;
        cin.ignore();
    } while (toupper(pilihan) == 'Y');
}

void sortingJenis(){
    // Sort indices based on jenis barang
    sort(barangUser.begin(), barangUser.end(), [](const Barang &a, const Barang &b) {
        return a.jenisBarang < b.jenisBarang; // Sorting ascending berdasarkan jenisBarang
    });
}

// Implementasi fungsi lihatStokBarang dengan array
void lihatStokBarang() {
    if (jumlahBarang == 0) {
        cout << "\n[INFO] Tidak ada barang dalam stok.\n";
        return;
    }

    system("cls");
    sortingJenis();
    cout << "\nDaftar Stok Barang\n";
    cout << "=========================\n";
    for (int i = 0; i < barangUser.size(); i++) {
        //int idx = indices[i];
        cout << (i + 1) << ". (" << barangUser[i].jenisBarang << ") " 
             << barangUser[i].namaBarang << endl;
    }

    cout << "\nLihat detail data: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice > 0 && choice <= barangUser.size()) {
        int idx = choice-1;
        cout << "\nDetail barang:\n";
        cout << "nama barang: " << barangUser[idx].namaBarang << endl;
        cout << "Jenis barang: " << barangUser[idx].jenisBarang << endl;
        cout << "Waktu tersedia: " << barangUser[idx].waktuTersedia << endl;
        cout << "harga: $" << barangUser[idx].harga << endl;
        cout << "Item: " << barangUser[idx].item << endl;
    }
}

// Implementasi menuEksportir
void menuEksportir(User* user, bool& isLoggedIn) {
    int choice;
    while (isLoggedIn) {
        system("cls");
        cout << "\n" << user->nama << " (Eksportir)" << endl;
        cout << "======================" << endl;
        cout << "1. Menambah barang" << endl;
        cout << "2. Mengubah barang" << endl;
        cout << "3. Daftar stok barang (sorting)" << endl;
        cout << "4. Daftar Pesanan" << endl;
        cout << "5. Kirim pesanan (Queue)" << endl;
        cout << "6. Daftar Pengiriman" << endl;
        cout << "7. Logout" << endl;
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                tambahBarang();
                break;
            case 2:
                ubahBarang();
                break;
            case 3:
                lihatStokBarang();
                break;
            case 4:
                cout << "\n[Fitur daftar pesanan belum diimplementasikan]" << endl;
                break;
            case 5:
                cout << "\n[Fitur kirim pesanan belum diimplementasikan]" << endl;
                break;
            case 6:
                cout << "\n[Fitur daftar pengiriman belum diimplementasikan]" << endl;
                break;
            case 7:
                cout << "\n[INFO] Logout berhasil!" << endl;
                isLoggedIn = false;
                return;
            default:
                cout << "\n[ERROR] Pilihan tidak valid!" << endl;
        }
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
    }
}

// Menu Importir (unchanged)
void menuImportir(User* user, bool& isLoggedIn) {
    int choice;
    while (isLoggedIn) {
        system("cls");
        cout << "\n" << user->nama << " (Importir)" << endl;
        cout << "======================" << endl;
        cout << "1. Pesan Barang" << endl;
        cout << "2. Daftar pemesanan" << endl;
        cout << "3. Cek status pengiriman barang (Hash Table)" << endl;
        cout << "4. Logout" << endl;
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                pesanBarang();
                break;
            case 2:
                daftarPemesanan();
                break;
            case 3:
                cout << "\n[Fitur cek status pengiriman belum diimplementasikan]" << endl;
                break;
            case 4:
                cout << "\n[INFO] Logout berhasil!" << endl;
                isLoggedIn = false;
                return;
            default:
                cout << "\n[ERROR] Pilihan tidak valid!" << endl;
        }
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
    }
}

// Login function
bool login(User* head, string username, string password) {
    User* user = findUser(head, username);
    if (user != nullptr && user->password == password) {
        system("cls");
        bool isLoggedIn = true;
        if (user->role == "eksportir") {
            SinkronBarangUser(userNow);
            menuEksportir(user, isLoggedIn);
        } else {
            SinkronPesananUser(userNow);
            menuImportir(user, isLoggedIn);
        }
        return isLoggedIn;
    }
    cout << "\n[ERROR] Username atau password salah!" << endl;
    cout << "Tekan Enter untuk login ulang " << endl;
    cin.get();
    return false;
}

// Main function
int main() {
    User* head = nullptr;
    int choice;
    string nama, username, password, role, asalNegara;

    while (true) {
        system("cls");
        cout << "\n=================== SISTEM LOGIN ===================" << endl;
        cout << "1. Daftar (Linked List)" << endl;
        cout << "2. Login" << endl;
        cout << "3. Keluar" << endl;
        cout << "==================================================" << endl;
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();
        system("cls");

        switch (choice) {
            case 1:
                cout << "\n================ PENDAFTARAN =================" << endl;
                cout << "Masukkan nama      : ";
                getline(cin, nama);
                cout << "Username           : ";
                getline(cin, username);
                cout << "Password           : ";
                getline(cin, password);
                do {
                    cout << "Role (eksportir/importir) : ";
                    getline(cin, role);
                } while (role != "eksportir" && role != "importir");
                cout << "Asal negara        : ";
                getline(cin, asalNegara);
                registerUser(head, nama, username, password, role, asalNegara);
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.get();
                break;

            case 2:
                cout << "\n=================== LOGIN ====================" << endl;
                cout << "Username : ";
                getline(cin, username);
                cout << "Password : ";
                getline(cin, password);
                login(head, username, password);
                break;

            case 3:
                cout << "\n[INFO] Terima kasih telah menggunakan sistem ini!" << endl;
                // Clean up memory for user linked list
                while (head != nullptr) {
                    User* temp = head;
                    head = head->next;
                    delete temp;
                }
                return 0;

            default:
                cout << "\n[ERROR] Pilihan tidak valid!" << endl;
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.get();
        }
    }
    return 0;
}