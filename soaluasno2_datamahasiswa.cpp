#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Mahasiswa {
  string NIM;
  string nama;
    float nilaiAkhir;
};

void tambahData(vector<Mahasiswa>& data) {
    int jumlah;
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlah;

    for (int i = 0; i < jumlah; ++i) {
        Mahasiswa mhs;
        cout << "\nMahasiswa ke-" << i + 1 << ":\n";
        cout << "NIM: ";
        cin >> mhs.NIM;
        cout << "Nama: ";
        cin.ignore();
        getline(cin, mhs.nama);
        cout << "Nilai Akhir: ";
        cin >> mhs.nilaiAkhir;
        data.push_back(mhs);
    }
}

void tampilkanData(const vector<Mahasiswa>& data) {
    cout << "\nData Mahasiswa:\n";
    cout << left <<setw(15) << "NIM" <<setw(25) << "Nama" << "Nilai Akhir" << "\n";
    cout << string(50, '-') << "\n";
    for (const auto& mhs : data) {
        cout << left << setw(15) << mhs.NIM << setw(25) << mhs.nama << mhs.nilaiAkhir << "\n";
    }
}

void cariData(const vector<Mahasiswa>& data) {
    string nim;
    cout << "Masukkan NIM yang dicari: ";
    cin >> nim;

    bool ditemukan = false;
    for (const auto& mhs : data) {
        if (mhs.NIM == nim) {
            cout << "\nData ditemukan:\n";
            cout << "NIM: " << mhs.NIM << "\n";
            cout << "Nama: " << mhs.nama << "\n";
            cout << "Nilai Akhir: " << mhs.nilaiAkhir << "\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nData dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

void urutkanData(vector<Mahasiswa>& data) {
    for (size_t i = 0; i < data.size() - 1; ++i) {
        for (size_t j = 0; j < data.size() - i - 1; ++j) {
            if (data[j].nilaiAkhir < data[j + 1].nilaiAkhir) {
                swap(data[j], data[j + 1]);
            }
        }
    }
   cout << "\nData berhasil diurutkan berdasarkan Nilai Akhir secara menurun.\n";
}

void simpanKeBerkas(const vector<Mahasiswa>& data, const string& namaBerkas) {
    ofstream file(namaBerkas);
    if (!file) {
        cerr << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }

    for (const auto& mhs : data) {
        file << mhs.NIM << "," << mhs.nama << "," << mhs.nilaiAkhir << "\n";
    }
    file.close();
    cout << "\nData berhasil disimpan ke dalam file \"" << namaBerkas << "\".\n";
}

void bacaDariBerkas(std::vector<Mahasiswa>& data, const string& namaBerkas) {
    ifstream file(namaBerkas);
    if (!file) {
        cerr << "Gagal membuka file untuk membaca data.\n";
        return;
    }

    data.clear();
    string line;
    while (getline(file, line)) {
        Mahasiswa mhs;
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');

        mhs.NIM = line.substr(0, pos1);
        mhs.nama = line.substr(pos1 + 1, pos2 - pos1 - 1);
        mhs.nilaiAkhir = stof(line.substr(pos2 + 1));

        data.push_back(mhs);
    }
    file.close();
    cout << "\nData berhasil dibaca dari file \"" << namaBerkas << "\".\n";
}

int main() {
    vector<Mahasiswa> dataMahasiswa;
    string namaBerkas = "data_mahasiswa.txt";
    int pilihan;

    do {
        cout << "\nMenu Utama:\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Cari Data Mahasiswa (berdasarkan NIM)\n";
        cout << "4. Urutkan Data (berdasarkan Nilai Akhir)\n";
        cout << "5. Simpan Data ke Berkas\n";
        cout << "6. Baca Data dari Berkas\n";
        cout << "7. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahData(dataMahasiswa);
                break;
            case 2:
                tampilkanData(dataMahasiswa);
                break;
            case 3:
                cariData(dataMahasiswa);
                break;
            case 4:
                urutkanData(dataMahasiswa);
                break;
            case 5:
                simpanKeBerkas(dataMahasiswa, namaBerkas);
                break;
            case 6:
                bacaDariBerkas(dataMahasiswa, namaBerkas);
                break;
            case 7:
                cout << "Keluar dari program.\n";
                break;
            default:
               cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 7);

    return 0;
}
