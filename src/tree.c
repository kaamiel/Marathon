#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"
#include "dlist.h"
#include "tree.h"
#include "constants.h"

#define max(a, b) ((a) > (b)) ? (a) : (b)

// if NDEBUG is not defined, the program may write some unnecessary stuff
#ifndef NDEBUG
#define NDEBUG
#endif

// static array of pointers
static Tree *users[MAX_USER_ID + 1];

// inicjalizuje dwukierunkową listę dzieci jako [-1, -1] (atrapy
// początku i końca listy), zwraca wskaźnik do początku utworzonej listy
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

bool addChild(int parentUserId, int userId) {
  if (parentUserId < 0 || MAX_USER_ID < parentUserId ||
    userId <= 0 || MAX_USER_ID < userId) {
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
  if (userId < 0 || MAX_USER_ID < userId)
    return false;
  Tree *user = users[userId];
  return !(user == NULL || user->firstChild->next == user->lastChild);
}

bool delChild(int userId) {
  if (userId <= 0 || MAX_USER_ID < userId) {
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
  if (userId < 0 || MAX_USER_ID < userId ||
    movieRating < 0 || MAX_MOVIE_RATING < movieRating) {
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
  if (userId < 0 || MAX_USER_ID < userId ||
    movieRating < 0 || MAX_MOVIE_RATING < movieRating) {
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

// wyznacza rekurencyjnie malejącą listę najlepszych filmów użytkownika userId
// i jego dzieci, na liście są tylko filmy o ocenie większej niż minRating
static void bestMovies(int userId, int minRating, List **acc, int k) {
  if (userId < 0 || MAX_USER_ID < userId || k <= 0)
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
  if (userId < 0 || MAX_USER_ID < userId ||
    k < 0 || MAX_MOVIE_RATING < k) {
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