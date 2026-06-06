#ifndef TEBAKKATA_H
#define TEBAKKATA_H

#include <iostream>
#include <string>

using namespace std;

struct KataGame{
    string kataAsli;
    string statusTebakan;
    int nyawa;
};

extern string bankKata[15];
string ambilKataAcak();
void pilihKesulitan(KataGame *game);
void inisialisasiGame(KataGame *game);
void tampilkanGame(
    KataGame game,
    char tebakanSalah[],
    int jumlahSalah
);

bool sudahPernahDitebak(
    char huruf,
    KataGame game,
    char tebakanSalah[],
    int jumlahSalah
);

void prosesTebakan(
    KataGame *game,
    char huruf,
    char tebakanSalah[],
    int *jumlahSalah
);

bool cekMenang(KataGame game);

void gunakanHint(KataGame *game);

#endif