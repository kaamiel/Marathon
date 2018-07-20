#ifndef TREE_H
#define TREE_H

// drzewo użytkowników
typedef struct Tree {
  DList *firstChild, *lastChild;
  DList *pointerOnParentsChildrenList;
  List *movies;
} Tree;

// inicjalizuje strukturę
extern void init();

// dodaje syna, zwraca czy dodał
extern bool addChild(int parentUserId, int userId);

// sprawdza, czy użytkownik ma potomków
extern bool hasChildren(int userId);

// usuwa syna, zwraca czy usunął
extern bool delChild(int userId);

// dodaje film, zwraca czy dodał
extern bool addMovie(int userId, int movieRating);

// usuwa film, zwraca czy usunął
extern bool delMovie(int userId, int movieRating);

// wypisuje na ekran wynik operacji marathon, zwraca czy wypisał
extern bool marathon(int userId, int k);

// usuwa całe drzewo, zwalnia zaalokowaną pamięć
extern void delTree();

// wyświetla wszystkich użytkowników
extern void printUsers();

#endif // TREE_H