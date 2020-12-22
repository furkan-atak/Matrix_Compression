/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   compress.h
 * Author: Pc
 *
 * Created on 21 November 2020, 12:20
 */

#ifndef COMPRESS_H
#define COMPRESS_H

void compress_IJ(int**, int*, int*, int*);
int **decompress_IJ(int*, int*, int*);
void compress_CRS(int**, int*, int*, int*);
int **decompress_CRS(int*, int*, int*);
void compress_CCS(int**, int*, int*, int*);
int **decompress_CCS(int*, int*, int*);
int **createNfill();
void printMatrix(int**);




#endif /* COMPRESS_H */

