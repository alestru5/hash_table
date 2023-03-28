#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "input.h"
#include "table.h"
int init(Table *board){
    printf("Введите максимальный размер таблицы\n");
    int k = getInt();
    if (k == 0){
	return 0;
    }
    int len = prost(k);
    printf("Выделено памяти на %d элементов.\n", len);
    board->ks = calloc(len, sizeof(KeySpace));
    board->msize = len;
    /*for (int i = 0; i < board->msize; i++){
	board->ks[i].info = malloc(sizeof(Item));
        board->ks[i].info->element = (sizeof(char*));*/
    return 1;
}
/*int count_rel(Table *board, char *key){
    for (int i = board->csize-1; i >= 0; i--){
        if (strcmp(board->ks[i].key, key) == 0 && board->ks[i].busy != 0){
            return board->ks[i].release;
        }
    }
    return 0;
}*/
int hash1(char *str, Table *board){
    int i = 0;
    for (int j = 0; str[j]; j++){
	i += str[j];
    }
    return i % board->msize;
}
int hash2(char *str, Table *board) {
    int i = 0;
    for (int j = 0; str[j]; j++){
        i += str[j];
    }
    return prost(i % board->msize)%board->msize;
}
int Add(Table *board){
    printf("Введите ключ элемента:\n");
    char *key = getStr();
    printf("Введите элемент:\n");
    char *el = getStr();
    int i = 0;
    int r = 1;
    while (i < board->msize){
	int h = hash1(key, board) + i * hash2(key, board);
	if (board->ks[h].busy == 0){
	    board->ks[h].info = malloc(sizeof(Item));
            board->ks[h].info->element = el;
            board->ks[h].key=key;
	    board->ks[h].release = r;
            board->ks[h].busy=1;
            return 1;
        }
        if ((board->ks[h].busy==1)&&strcmp(board->ks[h].key, key)==0){
            r += 1;
        }
        i++;
    }
    printf("Таблица заполнена.\n");
    free(key);
    free(el);
    return 1;
}/*
int Find(Table *board){
    printf("Введите элемент, который хотите увидеть:\n");
    char *el = getStr();
    char *h1 = hash1(el);
    char *h2 = hash2(h1);
    int f = 1;
    for (int i = 0; i < board->csize; i++){
        if ((strcmp(board->ks[i].key, h1) == 0 || strcmp(board->ks[i].key, h2) == 0) && board->ks[i].busy != 0){
            printf("busy: %d key: %s release: %d element: %s\n", board->ks[i].busy, board->ks[i].key,
                   board->ks[i].release, board->ks[i].info->element);
            f = 0;
        }
    }
    if (f){
        printf("Такого ключа не существует.\n");
    }
    free(el);
    free(h1);
    free(h2);
    return 1;
}
int Delete(Table *board){
    printf("Введите удаляемый элемент:\n");
    char *el = getStr();
    char *h1 = hash1(el);
    char *h2 = hash2(h1);
    int rel = count_rel(board, h1), n;
    if (rel == 0){
        printf("Ошибка: Такого элемента не существует.\n");
        free(el);
	free(h1);
	free(h2);
        return 1;
    }
    for (int i = 0; i < board->csize; i++){
        if ((strcmp(board->ks[i].key, h1) == 0 || strcmp(board->ks[i].key, h2) == 0) && board->ks[i].busy == 1) {
            board->ks[i].busy = 0;
        }
    }
    free(el);
    free(h1);
    free(h2);
    return 1;
}*/
int CleanShow(Table *board){
    int f = 1;
    for (int i = 0; i < board->msize; i++){
        if (board->ks[i].busy != 0) {
            f = 0;
            printf("ind: %d busy: %d key: %s release: %d element: %s\n", i, board->ks[i].busy, board->ks[i].key,
                   board->ks[i].release, board->ks[i].info->element);
        }
    }
    if (f){
        printf("Таблица пустая.\n");
    }
    return 1;
}/*
int DirtyShow(Table *board){
    if (board->csize == 0){
        printf("Таблица пустая.\n");
        return 1;
    }
    for (int i = 0; i < board->csize; i++){
        printf("busy: %d key: %s release: %d element: %s\n", board->ks[i].busy, board->ks[i].key,
               board->ks[i].release, board->ks[i].info->element);
    }
    return 1;
}
int Reorg(Table *board){
    int i = 0;
    while (i < board->csize){
        if (board->ks[i].busy == 0) {
	    free(board->ks[i].info->element); 
            free(board->ks[i].key);
            for (int j = i; j < board->csize - 1; j++) {
                board->ks[j].busy = board->ks[j + 1].busy;
                board->ks[j].key = board->ks[j + 1].key;
                board->ks[j].info->element = board->ks[j + 1].info->element;
                board->ks[j].release = board->ks[j + 1].release;
            }
            board->csize -= 1;
            free(board->ks[board->csize].info);
            board->ks = realloc(board->ks, sizeof(KeySpace) * board->csize);
            i -= 1;
        }
        i += 1;
    }
    return 1;
}*/
void clear(Table *board){
    for (int i = 0; i < board->msize; i++){
	if (board->ks[i].info && board->ks[i].info->element)
	    free(board->ks[i].info->element);
            free(board->ks[i].info);
        free(board->ks[i].key);
    }
    free(board->ks);
}
