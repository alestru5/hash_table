#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "input.h"
#include "table.h"
int count_rel(Table *board, char *key){
    for (int i = board->csize-1; i >= 0; i--){
        if (strcmp(board->ks[i].key, key) == 0 && board->ks[i].busy != 0){
            return board->ks[i].release;
        }
    }
    return 0;
}
char *hash1(char *str){
    int l = strlen(str);
    char *ans = malloc(sizeof(char) * (l + 1));
    for (int i = 0; i < l/3; i ++){
	ans[i] = str[i] + l/6;
    }
    for (int i = 0; i < l/3 * 2; i++){
	ans[i] = str[i] + l/3;
    }
    for (int i = 0; i < l; i++){
	ans[i] = str[i] + l / 2;
    }
    ans[l] = '\0';
    return ans;
}
char *hash2(char *str) {
    int l = strlen(str);
    char *ans = malloc(sizeof(char) * (l + 1));
    for (int i = 0; i < l/2; i ++){
        ans[i] = str[i] + l/4;
    }
    for (int i = 0; i < l/3 * 2; i++){
        ans[i] = str[i] + l/3;
    }
    for (int i = 0; i < l; i++){
        ans[i] = str[i] + l / 2;
    }
    ans[l] = '\0';
    return ans;
}
int Add(Table *board){
    printf("Введите элемент:\n");
    char *el = getStr();
    int rel = -1, f = 0;
    char *h1 = hash1(el);
    for (int i = 0; i < board->csize; i++){
	if (strcmp(board->ks[i].key, h1) == 0 && board->ks[i].busy != 0){
	    f = 1;
	    break;
	}
    }
    if (f == 1){
	char *h2 = hash2(h1);
	for (int i = 0; i < board->csize; i++){
            if (strcmp(board->ks[i].key, h2) == 0 && board->ks[i].busy != 0){
                int j = i + 1;
		while ((j % board->csize) != i){
		    if (board->ks[j%board->csize].busy == 0){
			board->ks[j%board->csize].busy = 1;
			board->ks[j%board->csize].key = h2;
			board->ks[j%board->csize].release = count_rel(board, h2) + 1;
			board->ks[j%board->csize].info->element = el;
			f = 0;
			break;
		   }
		   j += 1;
		}
	    }
	}
	if (f == 1){
	    if (board->csize == board->msize) {
        	printf("Ошибка: Переполнение. Попробуйте Reorganization.\n");
		free(h1);
		free(h2);
		free(el);
        	return 1;
    	    }
	    board->ks = realloc(board->ks, sizeof(KeySpace) * (board->csize + 1));
            board->ks[board->csize].info = malloc(sizeof(Item));
            board->ks[board->csize].busy = 1;
            board->ks[board->csize].key = h2;
            board->ks[board->csize].release = count_rel(board, h2) + 1;
            board->ks[board->csize].info->element = el;
            board->csize += 1;
	}
	free(h1);
    }
    else{
	for (int i = 0; i < board->csize; i++){
	    if (board->ks[i].busy == 0){
		free(board->ks[i].info->element);
            	free(board->ks[i].key);
            	board->ks[i].busy = 1;
            	board->ks[i].key = h1;
            	board->ks[i].release = 1;
            	board->ks[i].info->element = el;
            	f = 1;
		break;
	    }
	}
	if (f == 0){
	    if (board->csize == board->msize) {
        	printf("Ошибка: Переполнение. Попробуйте Reorganization.\n");
		free(h1);
                free(el);
        	return 1;
    	    }
            board->ks = realloc(board->ks, sizeof(KeySpace) * (board->csize + 1));
            board->ks[board->csize].info = malloc(sizeof(Item));
            board->ks[board->csize].busy = 1;
            board->ks[board->csize].key = h1;
            board->ks[board->csize].release = 1;
            board->ks[board->csize].info->element = el;
            board->csize += 1;
        }
    }
     return 1;
}
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
}
int CleanShow(Table *board){
    int f = 1;
    if (board->csize == 0){
        printf("Таблица пустая.\n");
        return 1;
    }
    for (int i = 0; i < board->csize; i++){
        if (board->ks[i].busy != 0) {
            f = 0;
            printf("busy: %d key: %s release: %d element: %s\n", board->ks[i].busy, board->ks[i].key,
                   board->ks[i].release, board->ks[i].info->element);
        }
    }
    if (f){
        printf("Таблица пустая.\n");
    }
    return 1;
}
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
}
void clear(Table *board){
    for (int i = 0; i < board->csize; i++){
	free(board->ks[i].info->element);
        free(board->ks[i].info);
        free(board->ks[i].key);
    }
    free(board->ks);
}
