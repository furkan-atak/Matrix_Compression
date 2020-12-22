/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Pc
 *
 * Created on 21 November 2020, 12:21
 */

#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#define M 6
#define N 6
/*
 * 
 */
int main(int argc, char** argv) {
   
    
    int **T = createNfill();
    puts("THE MATRIX: ");
    printMatrix(T);
    int i,j,numsCount = 0;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
         if(T[i][j] != 0){
             numsCount++;
         }   
        }     
    }  // A matrisinin 0 olmayan indis sayısı.
    
    int** IJ;
    int* nz_IJ;
    int* cols_IJ;
    int* rows_IJ;
    nz_IJ = (int*)malloc(sizeof(int)*(numsCount));
    rows_IJ = (int*)malloc(sizeof(int)*(numsCount));
    cols_IJ = (int*)malloc(sizeof(int)*(numsCount));
    compress_IJ(T,nz_IJ,cols_IJ,rows_IJ);
    IJ = decompress_IJ(nz_IJ,cols_IJ,rows_IJ);
    printf("\nIJ DECOMPRESS \n");
    printMatrix(IJ);
    
    int** CRS;
    int* nz_CRS;
    int* col_ind_CRS;
    int* rowPtr_CRS;
    nz_CRS = (int*)malloc(sizeof(int)*(numsCount));
    col_ind_CRS = (int*)malloc(sizeof(int)*(numsCount));
    rowPtr_CRS = (int*)malloc(sizeof(int)*(M+1));
    compress_CRS(T,nz_CRS,col_ind_CRS,rowPtr_CRS);
    CRS = decompress_CRS(nz_CRS,col_ind_CRS,rowPtr_CRS);
    printf("\nCRS DECOMPRESS \n");
    printMatrix(CRS);
    
    int **CCS;
    int* nz_CCS;
    int* row_ind_CCS;
    int* col_ptr_CCS;
    nz_CCS = (int*)malloc(sizeof(int)*(numsCount));
    row_ind_CCS = (int*)malloc(sizeof(int)*(numsCount));
    col_ptr_CCS = (int*)malloc(sizeof(int)*(numsCount));
    compress_CCS(T,nz_CCS,row_ind_CCS,col_ptr_CCS);
    CCS = decompress_CCS(nz_CCS,row_ind_CCS,col_ptr_CCS);
    printf("\nCCS DECOMPRESS \n");
    printMatrix(CCS);
    
    getchar();
    return (EXIT_SUCCESS);
}

