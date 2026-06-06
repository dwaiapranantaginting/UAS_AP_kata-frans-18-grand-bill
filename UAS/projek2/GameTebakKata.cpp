#include "Tebakkata.h"
#include <ctime>
#include <cstdlib>

string bankkata[15] =
{
    "komputer",
    "program",
    "algoritma",
    "pointer",
    "struktur",
    "database",
    "internet",
    "compiler",
    "keyboard",
    "monitor",
    "processor",
    "jaringan",
    "linux",
    "windows",
    "variabel"
};

string ambilKataAcak(){
    int index=rand()%15;
    return bankkata[index];
}

void pilihKesulitan(KataGame *game)
{
    int pilihan;

    cout << "===== PILIH KESULITAN =====\n";
    cout << "1. Easy (8 nyawa)"<<endl;;
    cout << "2. Medium (6 nyawa)"<<endl;
    cout << "3. Hard (4 nyawa)"<<endl;
    cout << "Pilihan : ";
    cin >> pilihan;

    if(pilihan == 1){
        game->nyawa = 8;
    }
    else if(pilihan == 2){
        game->nyawa = 6;
    }
    else{
        game->nyawa = 4;
    }
}

void inisialisasiGame(KataGame *game){
    game->kataAsli = ambilKataAcak();
    game->statusTebakan = "";

    for(int i = 0; i < game->kataAsli.length(); i++){
        game->statusTebakan += '_';
    }
}

void tampilkanGame(
    KataGame game,
    char tebakanSalah[],
    int jumlahSalah
){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    cout<< "===== GAME TEBAK KATA =====\n"<<endl;
    cout<< "Kata : ";

    for(int i = 0; i < game.statusTebakan.length(); i++){
        cout<<game.statusTebakan[i]<< " ";
    }

    cout<<"\n";
    cout<<"Nyawa : "<<game.nyawa<<endl;
    cout<<"Huruf Salah : ";

    for(int i = 0; i < jumlahSalah; i++){
        cout<< tebakanSalah[i] << " ";
    }
    cout<<"\n\n";
}

bool sudahPernahDitebak(
    char huruf,
    KataGame game,
    char tebakanSalah[],
    int jumlahSalah
){
    for(int i = 0; i < game.statusTebakan.length(); i++){ 
        if(game.statusTebakan[i] == huruf){
            return true;
        }
    }

    for(int i = 0; i < jumlahSalah; i++){
        if(tebakanSalah[i] == huruf){
            return true;
        }
    }return false;
}

void prosesTebakan(
    KataGame *game,
    char huruf,
    char tebakanSalah[],
    int *jumlahSalah
){
    bool ditemukan = false;
    for(int i = 0; i < game->kataAsli.length(); i++){
        if(game->kataAsli[i] == huruf){
            game->statusTebakan[i] = huruf;
            ditemukan = true;
        }
    }

    if(!ditemukan){
        tebakanSalah[*jumlahSalah] = huruf;
        (*jumlahSalah)++;
        game->nyawa--;
    }
}

bool cekMenang(KataGame game){
    return game.kataAsli == game.statusTebakan;
}

void gunakanHint(KataGame *game){
    if(game->nyawa > 1){
        game->statusTebakan[0] =
        game->kataAsli[0];
        game->nyawa--;
        cout << "\nHint digunakan! (-1 nyawa)\n";
    }
}