#include "Tebakkata.h"
#include <ctime>
#include <cstdlib>

int main(){
    srand(time(0));
    char mainLagi;

    do{
        KataGame game;
        pilihKesulitan(&game);
        inisialisasiGame(&game);
        char tebakanSalah[26];
        int jumlahSalah = 0;

        while(game.nyawa > 0 &&!cekMenang(game)){
            tampilkanGame(
                game,
                tebakanSalah,
                jumlahSalah
            );
            cout<<"Ketik ? untuk hint\n\n";
            char huruf;
            cout<<"Masukkan huruf : ";
            cin>>huruf;

            if(huruf == '?'){
                gunakanHint(&game);
                cout<<"Tekan Enter...";
                cin.ignore();
                cin.get();

                continue;
            }

            if(
                sudahPernahDitebak(
                    huruf,
                    game,
                    tebakanSalah,
                    jumlahSalah)
                ){
                cout<<"\nHuruf sudah pernah ditebak!\n";

                cout<<"Tekan Enter...";
                cin.ignore();
                cin.get();

                continue;
            }

            prosesTebakan(
                &game,
                huruf,
                tebakanSalah,
                &jumlahSalah
            );
        }

        tampilkanGame(
            game,
            tebakanSalah,
            jumlahSalah
        );

        if(cekMenang(game)){
            cout << "ANDA MENANG!\n";
        }
        else{
            cout<<"ANDA KALAH!\n";

            cout<<"Kata yang benar adalah : "<< game.kataAsli<< endl;
        }
        cout<<"\nMain lagi? (Y/N) : ";
        cin>>mainLagi;

    }
    while(mainLagi == 'Y' ||mainLagi == 'y');

    return 0;
}