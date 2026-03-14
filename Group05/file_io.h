#ifndef FILE_IO_H
#define FILE_IO_H
#include "member.h"
#include "trainer.h"

void loadBinaryFile();
int inputLoadFile();
void loadTextFile();
void saveDataBinary(struct memberProfile * members, int total);
void saveDataToFile( struct memberProfile * members, int total);
void autoLoadFile(struct memberProfile **members, int *total,
    struct trainerProfile *trainers, int numberOfTrainer);
void autoSaveFile(struct memberProfile * members, int total);
void buildBinaryFileName(char inputName[], char finalName[], int size);
void buildFileName(char inputName[], char finalName[], int size);

#endif