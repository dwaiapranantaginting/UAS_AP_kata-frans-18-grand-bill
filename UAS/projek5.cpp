#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cctype>

// konversi string ke lowercase
std::string toLower(std::string str) {
    for (char& c : str)
        c = tolower(c);
    return str;
}

// generate hint (sembunyiin sekitar setengah huruf acak (keep spaces visible))
std::string generateHint(const std::string& word) {
    std::string hint = word;
    int len = word.length();

    // hitung karakter yang bukan spasi
    std::vector<int> letterPositions;
    for (int i = 0; i < len; i++) {
        if (word[i] != ' ')
            letterPositions.push_back(i);
    }

    // acak posisi dan sembunyiin sekitar setengahnya
    int totalLetters = letterPositions.size();
    int hideCount = totalLetters / 2;

    // acak pakai rand
    for (int i = (int)letterPositions.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        std::swap(letterPositions[i], letterPositions[j]);
    }

    // sembunyikan hideCount posisi pertama dari list yang sudah diacak
    for (int i = 0; i < hideCount; i++) {
        hint[letterPositions[i]] = '_';
    }

    return hint;
}

int main() {
    // daftar negara
    std::vector<std::string> daftarNegara = {
        "norway",
        "oman",
        "slovakia",
        "brunei",
        "indonesia",
        "malaysia",
        "singapura",
        "thailand",
        "vietnam",
        "filipina",
        "kamboja",
        "myanmar",
        "laos",
        "timor leste",
        "jepang",
        "korea selatan",
        "korea utara",
        "china",
        "india",
        "pakistan",
        "bangladesh",
        "nepal",
        "sri lanka",
        "afghanistan",
        "iran",
        "irak",
        "suriah",
        "yordania",
        "arab saudi",
        "uni emirat arab",
        "qatar",
        "kuwait",
        "bahrain",
        "yaman",
        "turki",
        "mesir",
        "libya",
        "aljazair",
        "maroko",
        "nigeria",
        "kenya",
        "ethiopia",
        "tanzania",
        "ghana",
        "kamerun",
        "mozambik",
        "zambia",
        "zimbabwe",
        "angola",
        "kongo",
        "jerman",
        "prancis",
        "italia",
        "spanyol",
        "portugal",
        "belanda",
        "belgia",
        "swiss",
        "austria",
        "polandia",
        "swedia",
        "denmark",
        "finlandia",
        "norwegia",
        "islandia",
        "yunani",
        "rumania",
        "hungaria",
        "ceko",
        "kroasia",
        "serbia",
        "ukraina",
        "rusia",
        "kanada",
        "meksiko",
        "kuba",
        "brazil",
        "argentina",
        "chile",
        "kolombia",
        "venezuela",
        "peru",
        "bolivia",
        "ekuador",
        "uruguay",
        "australia",
        "selandia baru",
        "fiji",
        "papua nugini"
    };

    // seed random
    srand(static_cast<unsigned int>(time(nullptr)));

    int skor = 0;
    char mainLagi = 'y';

    std::cout << "==============================\n";
    std::cout << "   GAME MENEBAK NAMA NEGARA   \n";
    std::cout << "==============================\n\n";

    while (mainLagi == 'y' || mainLagi == 'Y') {
        // pilih negara secara acak
        int index = rand() % daftarNegara.size();
        std::string negara = daftarNegara[index];
        std::string hint   = generateHint(negara);

        std::cout << "Tebak negara: " << hint << "\n";
        std::cout << "Negara apakah yang dimaksud? ";

        std::string jawaban;
        std::getline(std::cin, jawaban);

        // bandingkan case-insensitive
        if (toLower(jawaban) == toLower(negara)) {
            skor++;
            std::cout << "Selamat! Anda benar.\n";
        } else {
            std::cout << "Maaf, jawaban Anda salah. Coba lagi.\n";
            std::cout << "Jawaban yang benar adalah: " << negara << "\n";
        }

        std::cout << "Skor Anda: " << skor << "\n";
        std::cout << "Ingin bermain lagi? (y/n): ";
        std::cin >> mainLagi;
        std::cin.ignore();
        std::cout << "\n";
    }

    std::cout << "Game Selesai :D\n";
    std::cout << "Skor akhir Anda: " << skor << "\n";

    return 0;
}