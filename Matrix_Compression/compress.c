#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#include <time.h>
#define M 6
#define N 6


int **createNfill(){   // malloc ile matris oluşturup random değer atama.
    int **A = (int**)malloc(sizeof(int*)*M);
    int i,j;
    for (i = 0; i < N; i++) {
        A[i] = (int*)malloc(sizeof(int)*N);
    }
    srand(time(NULL));
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if(i == j || j-i == rand()%((M/2)+1)){  // matristeki 0 olan indisleri arttırma
                A[i][j] = 0;
            }else{
                A[i][j] = rand() % 10;
            }
        }
    }
    return A;
}
void printMatrix(int **A){  // Matrisleri yazdırma
    int i,j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ",A[i][j]);
        }
        puts("");
    }
}

void compress_IJ(int **A, int *nz, int *rows, int *cols){
    int i,j,nzIndx = 0;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if(A[i][j] != 0){   // eğer indis 0 değil ise
                nz[nzIndx] = A[i][j];  // nz ye ekle
                rows[nzIndx] = i;   // satır indislerini ve
                cols[nzIndx] = j;   // sutun indislerini dizilerde sakla
                nzIndx++;   // yeni oluşan dizilerin indisi arttır.
            }
        }
    }
}
int **decompress_IJ(int *nz, int *rows, int *cols){
    int **A = (int**)malloc(sizeof(int*)*M);  // decompress için yeni matris
    int i,j,indx=0;
    for (i = 0; i < N; i++) {
        A[i] = (int*)malloc(sizeof(int)*N);
    }
    for (i = 0; i < M; i++) {            
        for (j = 0; j < N; j++) {        
            if(i*N+j == rows[indx]*N+cols[indx]){  // eğer satır ve sütun doğru indise geldiyse
               A[i][j]=nz[indx];   // yeni matrise nz dizisinden atama yap
               indx++;
            }else{
                A[i][j] = 0;  // indisler kaydedilen listedekiler değilse 0 ata.
            }
        }
    }
    return A;
}
void compress_CRS(int **A, int *nz, int *col_ind, int *row_ptr){
    int i,j;
    int nzIndx = 0,rptrInd=0;
    for (i = 0; i < M; i++) {
        int ilkMi = 1;      // satırın ilk 0 olmayanı kontrolu
        for (j = 0; j < N; j++) {
            if(A[i][j] != 0){  // matristeki 0 olmayan indisleri
                nz[nzIndx] = A[i][j]; // nz ye ata.
                col_ind[nzIndx] = j;  // atanan indisin sutun indisini kaydet
                if(ilkMi == 1){   
                    row_ptr[rptrInd] = nzIndx;  // eğer satırın ilk 0 olmayanı ise row_ptr ye nz deki indisi ata.
                    rptrInd++;
                    ilkMi = 0;
                }
                nzIndx++;
            }
        }
    }
    row_ptr[rptrInd] = nzIndx; //nz nin size ını row_ptr nin son indise ata.

}
int **decompress_CRS(int *nz, int *col_ind, int *row_ptr){
    int **A = (int**)malloc(sizeof(int*)*M);    // decompress için yeni matris
    int i,j,index=0,rptrIndx=0;
    for (i = 0; i < N; i++) {
         A[i] = (int*)malloc(sizeof(int*)*N);   
    }
    
    for (i = 0; i < M; i++) {;
        for (j = 0; j < N; j++) {
            if(col_ind[index] == j && index != row_ptr[rptrIndx+1]){  // eğer sütun indisi kaydedilen col_ind deki ile eşitse
                A[i][j] = nz[index];                                // index row_ptr de tutulan ilk elemana gidene kadar 
                index++;                                            // atama yap eşitse bu demek ki yeni satır i nin artmasını bekle.
            }else{
                A[i][j] = 0;
            }
        }
        rptrIndx++;
    }
    return A;
}
void compress_CCS(int **A, int *nz, int *row_ind, int *col_ptr){
    
    int i,j;
    int nzIndx = 0,cptrIndx=0;
    for (i = 0; i < M; i++) {
        int ilkMi = 1;      // ilk 0 olmayan sütun kontrolu
        for (j = 0; j < N; j++) {
            if(A[j][i] != 0){         // CRS deki benzer mantık bu sefer row-major değil column-major sutun indisi üzerinden ilerle
                nz[nzIndx] = A[j][i]; 
                row_ind[nzIndx] = j;
                if(ilkMi == 1){
                    col_ptr[cptrIndx] = nzIndx;  //ilk 0 olmayan stunun nz'deki indisini ata.
                    cptrIndx++;
                    ilkMi=0;
                }
                nzIndx++;
            }
        }
    }
    col_ptr[cptrIndx] = nzIndx;

}
int **decompress_CCS(int *nz, int *row_ind, int *col_ptr){
    int **A = (int**)malloc(sizeof(int*)*M);
    int i,j,index = 0,cptrIndx=0;
    for (i = 0; i < N; i++) {
        A[i] = (int*)malloc(sizeof(int)*N);
    }
    
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if(row_ind[index] == j && index != col_ptr[cptrIndx+1]){  // yine CRS ye benzer mantık fakat bu sefer yeni sutuna kadar ilerle 
                A[j][i] = nz[index];                                  // yeni sutunun ilk elemana geldiğinde anla ki yeni sütun o satıra 
                index++;                                              // o sutundaki indisi ekleme 
            }else{
                A[j][i] = 0;
            }
        }
        cptrIndx++;
    }
    return A;
}