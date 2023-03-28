#ifndef TYPE_H
#define TYPE_H
#define N 11
typedef struct Item{
    char *element;
}Item;
typedef struct KeySpace{
    Item *info;
    char *key;
    int busy;
    int release;

}KeySpace;
typedef struct Table{
    KeySpace *ks;
    int msize;
    int csize;
}Table;
#endif
