#include <stdio.h>
#include <stdlib.h>


void hitungRasio(float* pendapatan, Rasio* rasio, int bulan){
    for(int i = 0; i < bulan; i++){
        rasio[i].kebutuhan = pendapatan[i] * 0.5;
        rasio[i].keinginan = pendapatan[i] * 0.3;
        rasio[i].tabungan = pendapatan[i] * 0.2;
    }
}

int main(){
    int dewasa, anak, bulan;
    do{
        printf("Masukkan banyaknya bulan: ");
        scanf("%d", &bulan);
        if(bulan <= 0){
            printf("Mohon maaf! Masukkan tidak sah.\n");
        }
    }while(bulan <= 0);
    
    do{
        printf("Masukkan banyaknya anggota keluarga dengan usia di atas 14 tahun: ");
        scanf("%d", &dewasa);
        if(dewasa <= 0){
            printf("Mohon maaf! Masukkan tidak sah.\n");
        }
    }while(dewasa <= 0);
    do{
        printf("Masukkan banyak anggota keluarga usia dibawah 14 tahun: ");
        scanf("%d", &anak);
        if(anak < 0){
            printf("Input tidak valid\n");
        }
    }while(anak < 0);
    
    Rasio* rasio = (Rasio*) malloc(bulan * sizeof(Rasio));
    Alokasi* alokasi = (Alokasi*) malloc(bulan * sizeof(Alokasi));
    float pendapatan[bulan], pengeluaran[bulan], tabungan[bulan];
    printf("\nMasukkan Pendapatan: \n");
    for(int i = 0; i < bulan; i++){
        do{
            printf("Bulan %d: ", i + 1);
            scanf("%f", &pendapatan[i]);
            if(pendapatan[i] < 0){
                printf("Input tidak valid\n");
            }
        }while(pendapatan[i] < 0);
    }
    printf("\nMasukkan Pengeluaran\n");
    for(int i = 0; i < bulan; i++){
        do{
            printf("Bulan %d: ", i + 1);
            scanf("%f", &pengeluaran[i]);
            if(pengeluaran[i] < 0){
                printf("Input tidak valid\n");
            }
        }while(pengeluaran[i] < 0);
    }

    for(int i = 0; i < bulan; i++){
        tabungan[i] = pendapatan[i] - pengeluaran[i];
    }
    hitungRasio(pendapatan, rasio, bulan);
    hitungAlokasi(pendapatan, alokasi, bulan, dewasa, anak);

    float max = pendapatan[0];
    for(int i = 1; i < bulan; i++){
        if(max < pendapatan[i]){
            max = pendapatan[i];
        }
    }
    float total = 0, rata;
    for(int i = 0; i < bulan; i++){
        total += pengeluaran[i];
    }
    rata = total / bulan;

    float temp[bulan];
    printf("\n\nPemasukan dan Pengeluaran: \n\n");
    printf("\nRingkasan Pendapatan: \n");
    grafik(pendapatan, bulan, max);
    printf("\nRingkasan Pengeluaran: \n");
    grafik(pengeluaran, bulan, max);
    printf("\nRingkasan Tabungan: \n");
    grafik(tabungan, bulan, max);
    if(rata <= 641443){
        printf("\nGolongan: Miskin\n");
    }
    else if(rata > 641443 && rata < 962164){
        printf("\nGolongan: Rentan Miskin");
    }
    else if(rata > 962164 && rata < 2245050){
        printf("\nGolongan: Menuju Kelas Menengah\n");
    }
    else if(rata > 2245050 && rata < 10904531){
        printf("\nGolongan: Kelas Menengah\n");
    }
    else if(rata >= 10904531){
        printf("\nGolongan: Kelas Atas\n");
    }

    printf("\n\nAlokasi dana berdasarkan prioritas pengeluaran (Aturan 50/30/20): \n\n");
    printf("\nRingkasan saran pengeluaran untuk kebutuhan: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = rasio[i].kebutuhan;
    }
    grafik(temp, bulan, max);

    printf("\nRingkasan saran pengeluaran untuk keinginan: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = rasio[i].keinginan;
    }
    grafik(temp, bulan, max);

    printf("\nRingkasan saran pengeluaran untuk tabungan: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = rasio[i].tabungan;
    }
    grafik(temp, bulan, max);

    printf("\n\nAlokasi dana berdasarkan usia anggota keluarga (Skala Ekuivalensi OECD): \n\n");
    printf("\nRingkasan saran pengeluaran bagi kepala keluarga dan kebutuhan rumah: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = alokasi[i].utama;
    }
    grafik(temp, bulan, max);

    printf("\nRingkasan saran pengeluaran bagi setiap dewasa selain kepala keluarga: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = alokasi[i].dewasa;
    }
    grafik(temp, bulan, max);

    printf("\nRingkasan saran pengeluaran bagi setiap anak: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = alokasi[i].anak;
    }
    grafik(temp, bulan, max);

    free(rasio);
    free(alokasi);
    
    return 0;
}
