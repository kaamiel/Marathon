#ifndef LIST_H
#define LIST_H

// jednokierunkowa lista intów
typedef struct List {
  struct List *next;
  int value;
} List;

// wstawia element, lista ze wstawionym elementem jest malejąca, zwraca czy wstawił
extern bool insertSortedList(List** l, int k);

// usuwa element, lista po usunięciu elementu pozostaje malejąca, zwraca czy usunął
extern bool removeList(List** l, int k);

// usuwa całą listę, zwalnia zaalokowaną pamięć
extern void delList(List** l);

// wyświetla całą listę
extern void printList (List *l);

// wyświetla pierwsze k elementów listy
extern void printFirstkElementsList (List *l, int k);

#endif // LIST_H