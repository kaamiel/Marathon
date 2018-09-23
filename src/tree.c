/** @file
 * Implementacja klasy drzewa użytkowników.
 *
 * @author Kamil Dubil <kd370826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 03.04.2018
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include "dlist.h"
#include "tree.h"
#include "constants.h"

/** @brief Wyznacza maksimum z dwóch liczb.
 * Oblicza funkcję max(@p a, @p b).
 */
#define max(a, b) ((a) > (b)) ? (a) : (b)

// if NDEBUG is not defined, the program may write some unnecessary stuff
#ifndef NDEBUG
#define NDEBUG
#endif

/**
 * Statyczna tablica wskaźników na użytkowników.
 */
static Tree *users[MAX_USER_ID + 1];

/** @brief Inicjalizuje listę potomków.
 * Tworzy świeżą dwukierunkową listę potomków: [DEFAULT_FIRST_LAST_CHILD,
 * DEFAULT_FIRST_LAST_CHILD] – atrapy początku i końca listy.
 * @return Wskaźnik na pierwszy element zaalokowanej listy.
 */
static DList *initFirstChild() {
  DList *ptr = (DList *)malloc(sizeof(DList));
  if (ptr == NULL) {
    delTree();
    exit(1);
  }
  ptr->prev = ptr->next = NULL;
  ptr->value = DEFAULT_FIRST_LAST_CHILD;
  ptr = insertFrontDList(&ptr, DEFAULT_FIRST_LAST_CHILD);
  return ptr;
}

void init() {
  size_t i;
  for (i = 0; i <= MAX_USER_ID; ++i) {
    users[i] = NULL;
  }
  Tree *root = (Tree *)malloc(sizeof(Tree));
  if (root == NULL) {
    delTree();
    exit(1);
  }
  users[0] = root;
  root->firstChild = initFirstChild();
  root->lastChild = root->firstChild->next;
  root->movies = NULL;
  root->pointerOnParentsChildrenList = NULL;
}

/** @brief Sprawdza, czy liczba jest poprawnym identyfikatorem użytkownika.
 * Sprawdza, czy liczba @p userId jest poprawnym identyfikatorem użytkownika.
 * @param[in] userId – Sprawdzana liczba.
 * @return Wartość @p true, jeśli liczba jest poprawnym identyfikatorem użytkownika.
 *         Wartość @p false, jeśli liczba nie jest poprawnym identyfikatorem
 *         użytkownika.
 */
static inline bool validUserId(int userId) {
  return 0 <= userId && userId <= MAX_USER_ID;
}

/** @brief Sprawdza, czy liczba jest poprawnym identyfikatorem/oceną filmu.
 * Sprawdza, czy liczba @p movieRating jest poprawnym identyfikatorem/oceną
 * filmu.
 * @param[in] movieRating – Sprawdzana liczba.
 * @return Wartość @p true, jeśli liczba jest poprawnym identyfikatorem/oceną
 *         filmu.
 *         Wartość @p false, jeśli liczba nie jest poprawnym identyfikatorem/oceną
 *         filmu.
 */
static inline bool validMovieRating(int movieRating) {
  return 0 <= movieRating && movieRating <= MAX_MOVIE_RATING;
}

bool addChild(int parentUserId, int userId) {
  if (!validUserId(parentUserId) || !validUserId(userId) || userId == 0) {
    return false;
  }
  if (users[parentUserId] == NULL || users[userId] != NULL) {
    return false;
  }
  else {
    Tree *newUser = (Tree *)malloc(sizeof(Tree));
    if (newUser == NULL) {
      delTree();
      exit(1);
    }
    users[userId] = newUser;
    newUser->firstChild = initFirstChild();
    newUser->lastChild = newUser->firstChild->next;
    newUser->movies = NULL;
    newUser->pointerOnParentsChildrenList =
      insertAfterFirstDList(&users[parentUserId]->firstChild, userId);
    return true;
  }
}

bool hasChildren(int userId) {
  if (!validUserId(userId)) {
    return false;
  }
  Tree *user = users[userId];
  return !(user == NULL || user->firstChild->next == user->lastChild);
}

bool delChild(int userId) {
  if (!validUserId(userId) || userId == 0) {
    return false;
  }
  if (users[userId] == NULL) {
    return false;
  }
  else {
    Tree *toDelete = users[userId];
    if (hasChildren(userId)) {
      replaceDList(
        &toDelete->pointerOnParentsChildrenList,
        &toDelete->firstChild->next,
        &toDelete->lastChild->prev);
      toDelete->firstChild->next = toDelete->lastChild;
    }
    else {
      // toDelete has no children
      removeDList(&toDelete->pointerOnParentsChildrenList);
    }
    // forgetting movies
    delList(&toDelete->movies);

    // frees
    delDList(&toDelete->firstChild);
    free(toDelete);

    users[userId] = NULL;
    return true;
  }
}

bool addMovie(int userId, int movieRating) {
  if (!validUserId(userId) || !validMovieRating(movieRating)) {
    return false;
  }
  if (users[userId] == NULL) {
    return false;
  }
  else {
    return insertSortedList(&users[userId]->movies, movieRating);
  }
}

bool delMovie(int userId, int movieRating) {
  if (!validUserId(userId) || !validMovieRating(movieRating)) {
    return false;
  }
  if (users[userId] == NULL) {
    return false;
  }
  return removeList(&users[userId]->movies, movieRating);
}

void delTree() {
  size_t i;
  for (i = 1; i <= MAX_USER_ID; ++i) {
    if (users[i] != NULL)
      delChild(i);
  }
  // forgetting root's movies
  delList(&users[0]->movies);

  delDList(&users[0]->firstChild);
  free(users[0]);
  users[0] = NULL;
}

void printUsers() {
  size_t i;
  printf("\n+----------------------------+\n|   Początek użytkowników.   |"
    "\n+----------------------------+\n");
  for (i = 0; i <= MAX_USER_ID; ++i) {
    if (users[i]) {
      printf(" > UserId:\t%zu\n > movies:\t", i);
      printList(users[i]->movies);
      printf(" > children:\t");
      printDList(users[i]->firstChild);
      printf(" > lastChild:\t");
      printDList(users[i]->lastChild);
      printf(" > onPList:\t");
      printDList(users[i]->pointerOnParentsChildrenList);
      printf("------------------------------\n");
    }
  }
  printf("|    Koniec użytkowników.    |\n+----------------------------+\n\n");
}

/** @brief Wyznacza listę najlepszych filmów.
 * Wyznacza rekurencyjnie malejącą listę najlepszych filmów użytkownika
 * @p userId i jego potomków. Na wynikowej liście są tylko filmy o ocenie
 * większej niż @p minRating.
 * @param[in] userId – Identyfikator użytkownika;
 * @param[in] minRating – Minimalna ocena filmów;
 * @param[in, out] acc – Akumulator wykorzystywany przy rekurencji;
 * @param[in] k – Maksymalna wyznaczona liczba filmów jednego użytkownika.
 */
static void bestMovies(int userId, int minRating, List **acc, int k) {
  if (!validUserId(userId) || k <= 0)
    return;

  List *listOfMovies = users[userId]->movies;
  DList *children = users[userId]->firstChild->next;
  int newMin =
    (listOfMovies != NULL) ? (max(listOfMovies->value, minRating)) : minRating;
  int added = 0;

  while (listOfMovies != NULL && added < k) {
    if (listOfMovies->value > minRating) {
      insertSortedList(acc, listOfMovies->value);
      ++added;
      listOfMovies = listOfMovies->next;
    }
    else {
      // there's no need to consider movies that are not better than minRating
      break;
    }
  }

  while (children) {
    bestMovies(children->value, newMin, acc, k);
    children = children->next;
  }
}

bool marathon(int userId, int k) {
  if (!validUserId(userId) || !validMovieRating(k)) {
    return false;
  }
  if (users[userId] == NULL) {
    return false;
  }
  if (k == 0) {
    printf("NONE\n");
    return true;
  }
  #ifndef NDEBUG
  printf("\n\033[1;33mwynik maratonu %d %d:\033[0m\n", userId, k);
  #endif
  List *l = NULL;
  bestMovies(userId, -1, &l, k);
  if (l != NULL) {
    printFirstkElementsList(l, k);
    delList(&l);
  }
  else {
    printf("NONE\n");
  }
  return true;
}