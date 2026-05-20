#include <stdio.h>
#include <stdlib.h>

typedef struct{
    float kebutuhan; float keinginan; float tabungan;
}Rasio;

typedef struct{
    float utama; float dewasa; float anak;
}Alokasi;

void hitungRasio(float* pendapatan, Rasio* rasio, int bulan){
    for(int i = 0; i < bulan; i++){
        rasio[i].kebutuhan = pendapatan[i] * 0.5;
        rasio[i].keinginan = pendapatan[i] * 0.3;
        rasio[i].tabungan = pendapatan[i] * 0.2;
    }
}

void hitungAlokasi(float* pendapatan, Alokasi* alokasi, int bulan, int dewasa, int anak){
    for(int i = 0; i < bulan; i++){
        alokasi[i].utama = pendapatan[i] * 1 / (1 + 0.5 * (dewasa - 1) + 0.3 * anak);
        alokasi[i].dewasa = pendapatan[i] * 0.5 / (1 + 0.5 * (dewasa - 1) + 0.3 * anak);
        alokasi[i].anak = pendapatan[i] * 0.3 / (1 + 0.5 * (dewasa - 1) + 0.3 * anak);
    }
}


void grafik(float* skala, int bulan, int max){
    for(int pencacah = 0; pencacah < bulan; pencacah++){
        printf("Bulan ke-%d | ", pencacah + 1);
        for(int pencacah_lain = 0; pencacah_lain < (int)(70 * skala[pencacah]/max); pencacah_lain++){
            printf("#");
        }
        printf("  (Rp%.2f)", skala[pencacah]);
        if(skala[pencacah] < 0){
            printf("  (Pengeluaran yang berlebihan pada bulan ke-%d)", pencacah);
        }
    printf("\n");
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
        printf("Masukkan banyaknya anggota keluarga dengan usia di bawah 14 tahun: ");
        scanf("%d", &anak);
        if(anak < 0){
            printf("Mohon maaf! Masukkan tidak sah.\n");
        }
    }while(anak < 0);
    
    Rasio* rasio = (Rasio*) malloc(bulan * sizeof(Rasio));
    Alokasi* alokasi = (Alokasi*) malloc(bulan * sizeof(Alokasi));
    float pendapatan[bulan], pengeluaran[bulan], tabungan[bulan];
    printf("\nMasukkan pendapatan Anda setelah baris ini.\n");
    for(int i = 0; i < bulan; i++){
        do{
            printf("Bulan ke-%d: ", i + 1);
            scanf("%f", &pendapatan[i]);
            if(pendapatan[i] < 0){
                printf("Mohon maaf! Masukkan tidak sah.\n");
            }
        }while(pendapatan[i] < 0);
    }
    printf("\nMasukkan pengeluaran Anda setelah baris ini.\n");
    for(int i = 0; i < bulan; i++){
        do{
            printf("Bulan ke-%d: ", i + 1);
            scanf("%f", &pengeluaran[i]);
            if(pengeluaran[i] < 0){
                printf("Mohon maaf! Masukkan tidak sah.\n");
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
    printf("\nRINGKASAN PEMASUKAN DAN PENDAPATAN");
    printf("\nPendapatan:\n");
    grafik(pendapatan, bulan, max);
    printf("\nPengeluaran:\n");
    grafik(pengeluaran, bulan, max);
    printf("\nTabungan: \n");
    grafik(tabungan, bulan, max);
    if(rata <= 641443){
        printf("\nGolongan ekonomi: Miskin\n");
    }
    else if(rata > 641443 && rata < 962164){
        printf("\nGolongan ekonomi: Rentan miskin\n");
    }
    else if(rata > 962164 && rata < 2245050){
        printf("\nGolongan ekonomi: Menuju kelas menengah\n");
    }
    else if(rata > 2245050 && rata < 10904531){
        printf("\nGolongan ekonomi: Kelas menengah\n");
    }
    else if(rata >= 10904531){
        printf("\nGolongan ekonomi: Kelas atas\n");
    }

    printf("\nALOKASI DANA MENURUT PRIORITAS PENGELUARAN (ATURAN 50/30/20):");
    printf("\nSaran pengeluaran kebutuhan: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = rasio[i].kebutuhan;
    }
    grafik(temp, bulan, max);

    printf("\nSaran pengeluaran keinginan: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = rasio[i].keinginan;
    }
    grafik(temp, bulan, max);

    printf("\nSaran pengeluaran tabungan: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = rasio[i].tabungan;
    }
    grafik(temp, bulan, max);

    printf("\nALOKASI DANA MENURUT USIA ANGGOTA KELUARGA (SKALA EKUIVALENSI OECD):");
    printf("\nSaran pengeluaran untuk kepala keluarga dan kebutuhan rumah: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = alokasi[i].utama;
    }
    grafik(temp, bulan, max);

    printf("\nSaran pengeluaran untuk setiap orang dewasa selain kepala keluarga: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = alokasi[i].dewasa;
    }
    grafik(temp, bulan, max);

    printf("\nSaran pengeluaran untuk setiap anak: \n");
    for(int i = 0; i < bulan; i++){
        temp[i] = alokasi[i].anak;
    }
    grafik(temp, bulan, max);

    free(rasio);
    free(alokasi);
    
    return 0;
}
