#include <iostream>
#include <string>
using namespace std;

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

// Fungsi global untuk menambah pengguna baru
void registerUser(User*& head, string nama, string username, string password, string role, string asalNegara) {
    // Validasi username unik
    User* temp = head;
    while (temp != nullptr) {
        if (temp->username == username) {
            cout << "\n[ERROR] Username sudah terdaftar!" << endl;
            return;
        }
        temp = temp->next;
    }
    // Tambah pengguna baru ke linked list
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

// Fungsi global untuk menemukan pengguna berdasarkan username
User* findUser(User* head, string username) {
    User* temp = head;
    while (temp != nullptr) {
        if (temp->username == username) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Fungsi menu eksportir
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

        switch (choice) {
            case 1:
                cout << "\n[Fitur menambah barang belum diimplementasikan]" << endl;
                break;
            case 2:
                cout << "\n[Fitur mengubah barang belum diimplementasikan]" << endl;
                break;
            case 3:
                cout << "\n[Fitur daftar stok barang belum diimplementasikan]" << endl;
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
                isLoggedIn = false; // Logout user
                return;
            default:
                cout << "\n[ERROR] Pilihan tidak valid!" << endl;
        }
    }
}

// Fungsi menu importir
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

        switch (choice) {
            case 1:
                cout << "\n[Fitur pesan barang belum diimplementasikan]" << endl;
                break;
            case 2:
                cout << "\n[Fitur daftar pemesanan belum diimplementasikan]" << endl;
                break;
            case 3:
                cout << "\n[Fitur cek status pengiriman belum diimplementasikan]" << endl;
                break;
            case 4:
                cout << "\n[INFO] Logout berhasil!" << endl;
                isLoggedIn = false; // Logout user
                return;
            default:
                cout << "\n[ERROR] Pilihan tidak valid!" << endl;
        }
    }
}

// Fungsi login
bool login(User* head, string username, string password) {
    User* user = findUser(head, username);
    if (user != nullptr && user->password == password) {
        // cout << "\n[SUCCESS] Login berhasil!" << endl;
        system("cls");
        bool isLoggedIn = true; // Flag untuk melacak status login
        if (user->role == "eksportir") {
            menuEksportir(user, isLoggedIn);
        } else {
            menuImportir(user, isLoggedIn);
        }
        return isLoggedIn; // Logout mengubah flag ini menjadi false
    }
    cout << "\n[ERROR] Username atau password salah!" << endl; 
    cout << "Tekan Enter untuk login ulang " << endl; getchar();
    return false;
}

// Fungsi utama
int main() {
    User* head = nullptr; // Linked list pengguna
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
                return 0;

            default:
                cout << "\n[ERROR] Pilihan tidak valid!" << endl;
        }
    }
    return 0;
}
