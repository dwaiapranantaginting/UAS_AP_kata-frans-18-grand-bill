#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class permainan {
private:
    int ukuran;
    int jumlahbom;
    int papan[10][10];
    char tampilan[10][10];
    bool selesai;
    bool kalah;
    time_t waktumulai;
    time_t waktuselesai;

public:
    void menu() {
        int pilih;

        do {
            cout << endl;
            cout << "==============================" << endl;
            cout << "        minesweeper++" << endl;
            cout << "==============================" << endl;
            cout << "1. mulai permainan baru" << endl;
            cout << "2. keluar" << endl;
            cout << "pilih menu: ";
            cin >> pilih;

            if (pilih == 1) {
                mulai();
            } else if (pilih == 2) {
                cout << "program selesai." << endl;
            } else {
                cout << "pilihan tidak valid." << endl;
            }

        } while (pilih != 2);
    }

    void mulai() {
        inputawal();
        buatpapan();
        tanambom();
        hitungangka();

        selesai = false;
        kalah = false;
        waktumulai = time(0);

        while (selesai == false) {
            int aksi;
            int baris;
            int kolom;

            tampilkanpapan();

            cout << endl;
            cout << "aksi pemain:" << endl;
            cout << "1. buka kotak" << endl;
            cout << "2. tandai / hapus tanda" << endl;
            cout << "3. menyerah" << endl;
            cout << "pilih aksi: ";
            cin >> aksi;

            if (aksi == 1) {
                cout << "masukkan baris: ";
                cin >> baris;
                cout << "masukkan kolom: ";
                cin >> kolom;

                baris = baris - 1;
                kolom = kolom - 1;

                if (cekkoordinat(baris, kolom) == true) {
                    bukakotak(baris, kolom);
                    cekmenang();
                } else {
                    cout << "koordinat tidak valid." << endl;
                }

            } else if (aksi == 2) {
                cout << "masukkan baris: ";
                cin >> baris;
                cout << "masukkan kolom: ";
                cin >> kolom;

                baris = baris - 1;
                kolom = kolom - 1;

                if (cekkoordinat(baris, kolom) == true) {
                    tandaikotak(baris, kolom);
                    cekmenang();
                } else {
                    cout << "koordinat tidak valid." << endl;
                }

            } else if (aksi == 3) {
                selesai = true;
                kalah = true;
            } else {
                cout << "aksi tidak valid." << endl;
            }
        }

        waktuselesai = time(0);
        tampilkanakhir();

        cout << endl;
        cout << "kembali ke menu utama..." << endl;
    }

    void inputawal() {
        do {
            cout << endl;
            cout << "masukkan ukuran papan 4 sampai 10: ";
            cin >> ukuran;

            if (ukuran < 4 || ukuran > 10) {
                cout << "ukuran harus antara 4 sampai 10." << endl;
            }

        } while (ukuran < 4 || ukuran > 10);

        do {
            cout << "masukkan jumlah bom: ";
            cin >> jumlahbom;

            if (jumlahbom < 1 || jumlahbom >= ukuran * ukuran) {
                cout << "jumlah bom harus lebih dari 0 dan kurang dari jumlah kotak." << endl;
            }

        } while (jumlahbom < 1 || jumlahbom >= ukuran * ukuran);
    }

    void buatpapan() {
        int i;
        int j;

        for (i = 0; i < ukuran; i++) {
            for (j = 0; j < ukuran; j++) {
                papan[i][j] = 0;
                tampilan[i][j] = '#';
            }
        }
    }

    void tanambom() {
        int bom;
        int baris;
        int kolom;

        srand(time(0));
        bom = 0;

        while (bom < jumlahbom) {
            baris = rand() % ukuran;
            kolom = rand() % ukuran;

            if (papan[baris][kolom] != -1) {
                papan[baris][kolom] = -1;
                bom++;
            }
        }
    }

    void hitungangka() {
        int baris;
        int kolom;
        int i;
        int j;
        int jumlah;

        for (baris = 0; baris < ukuran; baris++) {
            for (kolom = 0; kolom < ukuran; kolom++) {
                if (papan[baris][kolom] != -1) {
                    jumlah = 0;

                    for (i = -1; i <= 1; i++) {
                        for (j = -1; j <= 1; j++) {
                            if (cekkoordinat(baris + i, kolom + j) == true) {
                                if (papan[baris + i][kolom + j] == -1) {
                                    jumlah++;
                                }
                            }
                        }
                    }

                    papan[baris][kolom] = jumlah;
                }
            }
        }
    }

    void tampilkanpapan() {
        int i;
        int j;
        int belumtanda;
        time_t waktusekarang;

        waktusekarang = time(0);
        belumtanda = hitungbelumtanda();

        cout << endl;
        cout << "waktu berjalan: " << waktusekarang - waktumulai << " detik" << endl;
        cout << "bom belum ditandai: " << belumtanda << endl;
        cout << endl;

        cout << "    ";
        for (i = 1; i <= ukuran; i++) {
            cout << i << " ";
        }
        cout << endl;

        cout << "   ";
        for (i = 1; i <= ukuran; i++) {
            cout << "--";
        }
        cout << endl;

        for (i = 0; i < ukuran; i++) {
            if (i + 1 < 10) {
                cout << i + 1 << " | ";
            } else {
                cout << i + 1 << "| ";
            }

            for (j = 0; j < ukuran; j++) {
                cout << tampilan[i][j] << " ";
            }

            cout << endl;
        }
    }

    void bukakotak(int baris, int kolom) {
        if (tampilan[baris][kolom] == 'x') {
            cout << "kotak ini sedang ditandai." << endl;
            return;
        }

        if (tampilan[baris][kolom] != '#') {
            cout << "kotak ini sudah dibuka." << endl;
            return;
        }

        if (papan[baris][kolom] == -1) {
            tampilan[baris][kolom] = '*';
            selesai = true;
            kalah = true;
            return;
        }

        if (papan[baris][kolom] == 0) {
            bukakosong(baris, kolom);
        } else {
            tampilan[baris][kolom] = char(papan[baris][kolom] + '0');
        }
    }

    void bukakosong(int baris, int kolom) {
        int i;
        int j;

        if (cekkoordinat(baris, kolom) == false) {
            return;
        }

        if (tampilan[baris][kolom] != '#') {
            return;
        }

        if (papan[baris][kolom] == -1) {
            return;
        }

        if (papan[baris][kolom] > 0) {
            tampilan[baris][kolom] = char(papan[baris][kolom] + '0');
            return;
        }

        tampilan[baris][kolom] = '0';

        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    bukakosong(baris + i, kolom + j);
                }
            }
        }
    }

    void tandaikotak(int baris, int kolom) {
        if (tampilan[baris][kolom] == '#') {
            tampilan[baris][kolom] = 'x';
        } else if (tampilan[baris][kolom] == 'x') {
            tampilan[baris][kolom] = '#';
        } else {
            cout << "kotak yang sudah dibuka tidak bisa ditandai." << endl;
        }
    }

    void cekmenang() {
        int i;
        int j;
        int tandabenar;
        bool salah;

        tandabenar = 0;
        salah = false;

        for (i = 0; i < ukuran; i++) {
            for (j = 0; j < ukuran; j++) {
                if (tampilan[i][j] == 'x') {
                    if (papan[i][j] == -1) {
                        tandabenar++;
                    } else {
                        salah = true;
                    }
                }
            }
        }

        if (tandabenar == jumlahbom && salah == false) {
            selesai = true;
            kalah = false;
        }
    }

    bool cekkoordinat(int baris, int kolom) {
        if (baris >= 0 && baris < ukuran && kolom >= 0 && kolom < ukuran) {
            return true;
        } else {
            return false;
        }
    }

    int hitungbelumtanda() {
        int i;
        int j;
        int tanda;

        tanda = 0;

        for (i = 0; i < ukuran; i++) {
            for (j = 0; j < ukuran; j++) {
                if (tampilan[i][j] == 'x') {
                    tanda++;
                }
            }
        }

        return jumlahbom - tanda;
    }

    void tampilkanakhir() {
        int i;
        int j;

        cout << endl;
        cout << "papan akhir:" << endl;
        cout << endl;

        cout << "    ";
        for (i = 1; i <= ukuran; i++) {
            cout << i << " ";
        }
        cout << endl;

        cout << "   ";
        for (i = 1; i <= ukuran; i++) {
            cout << "--";
        }
        cout << endl;

        for (i = 0; i < ukuran; i++) {
            if (i + 1 < 10) {
                cout << i + 1 << " | ";
            } else {
                cout << i + 1 << "| ";
            }

            for (j = 0; j < ukuran; j++) {
                if (papan[i][j] == -1) {
                    cout << "* ";
                } else {
                    cout << papan[i][j] << " ";
                }
            }

            cout << endl;
        }

        cout << endl;

        if (kalah == true) {
            cout << "game over, kamu kalah." << endl;
        } else {
            cout << "selamat, kamu menang!" << endl;
        }

        cout << "waktu permainan: " << waktuselesai - waktumulai << " detik" << endl;
    }
};

int main() {
    permainan game;
    game.menu();

}