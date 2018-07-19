#ifndef DLIST_H
#define DLIST_H

// dwukierunkowa lista intów
typedef struct DList {
  struct DList *next, *prev;
  int value;
} DList;

// wstawia element na początku listy, zwraca jego wskaźnik
extern DList* insertFrontDList(DList** beg, int k);

// wstawia element za pierwszym elementem listy, zwraca jego wskaźnik
extern DList* insertAfterFirstDList(DList** first, int k);

// usuwa element listy wskazywany przez toRemove
extern void removeDList(DList** toRemove);

// zastępuje element wskazywany przez toRemove listą o początku beg i końcu end
extern void replaceDList(DList** toRemove, DList** beg, DList** end);

// usuwa całą listę, zwalnia zaalokowaną pamięć
extern void delDList(DList** beg);

// wyświetla całą listę
extern void printDList(DList *beg);

#endif // DLIST_H