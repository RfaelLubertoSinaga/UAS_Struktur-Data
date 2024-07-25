#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    int year;
    bool isAvailable;
};

vector<Book> books;
vector<pair<string, string>> admins;
vector<pair<string, string>> users; 

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int findBookById(int id) {
    for (int i = 0; i < books.size(); ++i) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addBook() {
    Book newBook;
    cout << "\n:Tambah Buku:\n";
    cout << "ID Buku: ";
    while (!(cin >> newBook.id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    cout << "Judul Buku: ";
    getline(cin, newBook.title);
    cout << "Pengarang Buku: ";
    getline(cin, newBook.author);
    cout << "Tahun Terbit: ";
    while (!(cin >> newBook.year)) {
        cout << "Tahun harus berupa angka. Masukkan lagi: ";
        clearInputBuffer();
    }
    newBook.isAvailable = true;
    books.push_back(newBook);
    cout << "Buku berhasil ditambahkan!\n";
}

void readBooks() {
    cout << "\n    Lihat Buku    \n";
    if (books.empty()) {
        cout << "Tidak ada buku yang tersedia.\n";
    } else {
        for (const auto& book : books) {
            cout << "ID: " << book.id << "\n";
            cout << "Judul: " << book.title << "\n";
            cout << "Pengarang: " << book.author << "\n";
            cout << "Tahun Terbit: " << book.year << "\n";
            cout << "Status: " << (book.isAvailable ? "Tersedia" : "Tidak Tersedia") << "\n";
            cout << "------------------------\n";
        }
    }
}

void updateBook() {
    int id;
    cout << "\nUbah Buku:\n";
    cout << "Masukkan ID buku yang akan diubah: ";
    while (!(cin >> id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        clearInputBuffer();
    }
    int index = findBookById(id);
    if (index != -1) {
        Book& book = books[index];
        cout << "Judul Baru (kosongkan jika tidak ingin mengubah): ";
        clearInputBuffer();
        string newTitle;
        getline(cin, newTitle);
        if (!newTitle.empty()) {
            book.title = newTitle;
        }
        cout << "Pengarang Baru (kosongkan jika tidak ingin mengubah): ";
        string newAuthor;
        getline(cin, newAuthor);
        if (!newAuthor.empty()) {
            book.author = newAuthor;
        }
        cout << "Tahun Terbit Baru (0 jika tidak ingin mengubah): ";
        int newYear;
        if (cin >> newYear && newYear != 0) {
            book.year = newYear;
        }
        cout << "Buku berhasil diubah!\n";
    } else {
        cout << "Buku dengan ID tersebut tidak ditemukan.\n";
    }
}

void deleteBook() {
    int id;
    cout << "\nHapus Buku:\n";
    cout << "Masukkan ID buku yang akan dihapus: ";
    while (!(cin >> id)) {
        cout << "ID harus berupa angka. Masukkan lagi: ";
        clearInputBuffer();
    }
    int index = findBookById(id);
    if (index != -1) {
        books.erase(books.begin() + index);
        cout << "Buku berhasil dihapus!\n";
    } else {
        cout << "Buku dengan ID tersebut tidak ditemukan.\n";
    }
}

void login(bool& isLoggedIn, bool& isAdmin) {
    string username, password;
    cout << "\nLogin:\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (const auto& admin : admins) {
                if (admin.first == username && admin.second == password) {
            cout << "Login berhasil sebagai admin!\n" << endl;
            isLoggedIn = true;
            isAdmin = true;
            return;
        }
    }
    for (const auto& user : users) {
        if (user.first == username && user.second == password) {
            cout << "Login berhasil sebagai user!\n" << endl;
            isLoggedIn = true;
            isAdmin = false;
            return;
        }
    }
    cout << "Login gagal. Periksa username dan password.\n" << endl;
    isLoggedIn = false;
}

void registerUser() {
    string username, password;
    cout << "\nRegister:\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    users.push_back({username, password});
    cout << "Register berhasil!\n" << endl;
}

int main() {
    int choice;
    bool isLoggedIn = false;
    bool isAdmin = false;

    admins.push_back({"Rafael", "1234"});  

    do {
       
        cout << "\nMenu Utama:\n";
        if (!isLoggedIn) {
            cout << "1. Login\n";
            cout << "2. Register\n";
        } else {
            cout << "1. Lihat Buku\n";
            cout << "2. Tambah Buku\n";
            cout << "3. Ubah Buku\n";
            cout << "4. Hapus Buku\n";
            cout << "5. Logout\n";
            if (isAdmin) {
                cout << "\nInformasi Admin:\n";
                cout << "Anda memiliki akses untuk menambah, mengubah, dan menghapus buku.\n";
            }
        }
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        while (!(cin >> choice)) {
            cout << "Pilihan harus berupa angka. Masukkan lagi: ";
            clearInputBuffer();
        }

        switch (choice) {
            case 1:
                if (!isLoggedIn) {
                    login(isLoggedIn, isAdmin);
                } else {
                    readBooks();
                }
                break;
            case 2:
                if (!isLoggedIn) {
                    registerUser();
                } else {
                    if (isAdmin) {
                        addBook();
                    } else {
                        cout << "Akses ditolak. Hanya admin yang dapat menambah buku.\n";
                    }
                }
                break;
            case 3:
                if (isLoggedIn) {
                    if (isAdmin) {
                        updateBook();
                    } else {
                        cout << "Akses ditolak. Hanya admin yang dapat mengubah buku.\n";
                    }
                } else {
                    cout << "Anda harus login terlebih dahulu.\n";
                }
                break;
            case 4:
                if (isLoggedIn) {
                    if (isAdmin) {
                        deleteBook();
                    } else {
                        cout << "Akses anda ditolak. Hanya admin yang dapat menghapus buku.\n";
                    }
                } else {
                    cout << "Anda harus login untuk menghapus buku.\n";
                }
                break;
            case 5:
                if (isLoggedIn) {
                    isLoggedIn = false;
                    isAdmin = false;
                    cout << "Logout berhasil.\n" << endl;
                } else {
                    cout << "Anda belum login.\n" << endl;
                }
                break;
            case 0:
                cout << "Keluar dari program.\n" << endl;
                break;
            default:
                cout << "Pilihan tidak valid.\n" << endl;
        }
    } while (choice != 0);

    return 0;
}