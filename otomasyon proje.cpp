#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Ogrenci {
    int id;
    char ad[50];
    char soyad[50];
    char sinif[10];
    char servisSaat[10];
};

void menuGoster();
void ogrenciEkle();
void ogrenciAra();
void ogrenciGuncelle();
void ogrenciSil();
void ogrencileriListele();
void dosyaKontrol();

int main() {
    setlocale(LC_ALL, "Turkish");
    dosyaKontrol();

    int secim;
    do {
        menuGoster();
        cout << "\nSeçiminiz: ";
        cin >> secim;

        switch (secim) {
            case 1:
                ogrenciEkle();
                break;
            case 2:
                ogrenciAra();
                break;
            case 3:
                ogrenciGuncelle();
                break;
            case 4:
                ogrenciSil();
                break;
            case 5:
                ogrencileriListele();
                break;
            case 0:
                cout << "Program sonlandýrýlýyor...\n";
                break;
            default:
                cout << "Geçersiz seçim!\n";
        }
    } while (secim != 0);

    return 0;
}

void menuGoster() {
    cout << "\n=== ÖÐRENCÝ SERVÝSÝ OTOMASYONU ===\n";
    cout << "1. Öðrenci Ekle\n";
    cout << "2. Öðrenci Ara\n";
    cout << "3. Öðrenci Güncelle\n";
    cout << "4. Öðrenci Sil\n";
    cout << "5. Öðrencileri Listele\n";
    cout << "0. Çýkýþ\n";
}

void dosyaKontrol() {
    ifstream dosya("ogrenciler.dat", ios::binary);
    if (!dosya) {
        ofstream yeniDosya("ogrenciler.dat", ios::binary);
        yeniDosya.close();
    }
    dosya.close();
}

void ogrenciEkle() {
    Ogrenci yeniOgrenci;
    ofstream dosya("ogrenciler.dat", ios::binary | ios::app);

    cout << "\nÖðrenci ID: ";
    cin >> yeniOgrenci.id;
    cin.ignore();

    cout << "Ad: ";
    cin.getline(yeniOgrenci.ad, 50);

    cout << "Soyad: ";
    cin.getline(yeniOgrenci.soyad, 50);

    cout << "Sýnýf: ";
    cin.getline(yeniOgrenci.sinif, 10);

    cout << "Servis Saati: ";
    cin.getline(yeniOgrenci.servisSaat, 10);

    dosya.write(reinterpret_cast<char*>(&yeniOgrenci), sizeof(Ogrenci));
    dosya.close();

    cout << "\nÖðrenci baþarýyla eklendi!\n";
}

void ogrenciAra() {
    int arananId;
    bool bulundu = false;
    Ogrenci ogrenci;

    cout << "\nAranacak Öðrenci ID: ";
    cin >> arananId;

    ifstream dosya("ogrenciler.dat", ios::binary);

    while (dosya.read(reinterpret_cast<char*>(&ogrenci), sizeof(Ogrenci))) {
        if (ogrenci.id == arananId) {
            cout << "\nÖðrenci Bulundu:\n";
            cout << "ID: " << ogrenci.id << endl;
            cout << "Ad: " << ogrenci.ad << endl;
            cout << "Soyad: " << ogrenci.soyad << endl;
            cout << "Sýnýf: " << ogrenci.sinif << endl;
            cout << "Servis Saati: " << ogrenci.servisSaat << endl;
            bulundu = true;
            break;
        }
    }

    if (!bulundu) {
        cout << "\nÖðrenci bulunamadý!\n";
    }

    dosya.close();
}

void ogrenciGuncelle() {
    int guncellenecekId;
    bool bulundu = false;
    Ogrenci ogrenci;

    cout << "\nGüncellenecek Öðrenci ID: ";
    cin >> guncellenecekId;

    fstream dosya("ogrenciler.dat", ios::binary | ios::in | ios::out);

    while (dosya.read(reinterpret_cast<char*>(&ogrenci), sizeof(Ogrenci))) {
        if (ogrenci.id == guncellenecekId) {
            cout << "\nMevcut Bilgiler:\n";
            cout << "Ad: " << ogrenci.ad << endl;
            cout << "Soyad: " << ogrenci.soyad << endl;
            cout << "Sýnýf: " << ogrenci.sinif << endl;
            cout << "Servis Saati: " << ogrenci.servisSaat << endl;

            cout << "\nYeni Bilgileri Giriniz:\n";
            cin.ignore();

            cout << "Ad: ";
            cin.getline(ogrenci.ad, 50);

            cout << "Soyad: ";
            cin.getline(ogrenci.soyad, 50);

            cout << "Sýnýf: ";
            cin.getline(ogrenci.sinif, 10);

            cout << "Servis Saati: ";
            cin.getline(ogrenci.servisSaat, 10);

            dosya.seekp(-sizeof(Ogrenci), ios::cur);
            dosya.write(reinterpret_cast<char*>(&ogrenci), sizeof(Ogrenci));

            bulundu = true;
            cout << "\nÖðrenci baþarýyla güncellendi!\n";
            break;
        }
    }

    if (!bulundu) {
        cout << "\nÖðrenci bulunamadý!\n";
    }

    dosya.close();
}

void ogrenciSil() {
    int silinecekId;
    bool bulundu = false;

    cout << "\nSilinecek Öðrenci ID: ";
    cin >> silinecekId;

    ifstream eskiDosya("ogrenciler.dat", ios::binary);
    ofstream yeniDosya("temp.dat", ios::binary);

    Ogrenci ogrenci;

    while (eskiDosya.read(reinterpret_cast<char*>(&ogrenci), sizeof(Ogrenci))) {
        if (ogrenci.id != silinecekId) {
            yeniDosya.write(reinterpret_cast<char*>(&ogrenci), sizeof(Ogrenci));
        } else {
            bulundu = true;
        }
    }

    eskiDosya.close();
    yeniDosya.close();

    remove("ogrenciler.dat");
    rename("temp.dat", "ogrenciler.dat");

    if (bulundu) {
        cout << "\nÖðrenci baþarýyla silindi!\n";
    } else {
        cout << "\nÖðrenci bulunamadý!\n";
    }
}

/*void ogrencileriListele() {
    Ogrenci ogrenci;
    bool kayitVar = false;
}
    ifstream dosya*/
    void ogrencileriListele() {
    Ogrenci ogrenci;
    bool kayitVar = false;

    ifstream dosya("ogrenciler.dat", ios::binary);
    if (!dosya) {
        cout << "\nKayýtlý öðrenci bulunmamaktadýr!\n";
        return;
    }

    cout << "\n=== ÖÐRENCÝ LÝSTESÝ ===\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "Ad"
         << setw(20) << "Soyad"
         << setw(15) << "Sýnýf"
         << setw(15) << "Servis Saati" << endl;

    while (dosya.read(reinterpret_cast<char*>(&ogrenci), sizeof(Ogrenci))) {
        cout << left << setw(10) << ogrenci.id
             << setw(20) << ogrenci.ad
             << setw(20) << ogrenci.soyad
             << setw(15) << ogrenci.sinif
             << setw(15) << ogrenci.servisSaat << endl;
        kayitVar = true;
    }

    if (!kayitVar) {
        cout << "\nKayýtlý öðrenci bulunmamaktadýr!\n";
    }

    dosya.close();
}


