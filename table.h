#ifndef TABLE_H
#define TABLE_H
int init(Table *board);
int count_rel(Table *board, char *key);
int hash1(char *str, Table *board);
int hash2(char *str, Table *board);
int Add(Table *board);
int Find(Table *board);
int Delete(Table *board);
int CleanShow(Table *board);
int DirtyShow(Table *board);
int Reorg(Table *board);
void clear(Table *board);
#endif
