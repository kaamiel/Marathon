/** @file
 * Implementacja klasy róznowartościowych, posortowanych list liczb całkowitych.
 *
 * @author Kamil Dubil <kd370826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 03.04.2018
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

// if NDEBUG is not defined, the program may write some unnecessary stuff
#define NDEBUG

bool insertSortedList(List** l, int k) {
  if (*l == NULL || (*l)->value < k) {
    List *newElem = (List *)malloc(sizeof(List));
    if (newElem == NULL) {
      exit(1);
    }
    newElem->value = k;
    newElem->next = *l;
    *l = newElem;
    return true;
  }
  else if ((*l)->value > k) {
    return insertSortedList(&((*l)->next), k);
  }
  // last possibility: (*l)->value == k
  return false;
}

bool removeList(List** l, int k) {
  if (*l == NULL || (*l)->value < k) {
    return false;
  }
  else if ((*l)->value == k) {
    List *tmp = *l;
    *l = (*l)->next;
    free(tmp);
    return true;
  }
  else {
    return removeList(&((*l)->next), k);
  }
}

void delList(List** l) {
  while (*l) {
    List *tmp = *l;
    *l = (*l)->next;
    free(tmp);
    tmp = NULL;
  }
}

void printList(List *l) {
  if (l == NULL) {
    printf("\033[0;31mpusta\033[0m\n");
    return;
  }
  printf("\033[1;36mpoczątek\033[0m -> ");
  while (l) {
    printf("%d -> ", l->value);
    l = l->next;
  }
  printf("\033[1;36mkoniec.\033[0m\n");
}

void printFirstkElementsList (List *l, int k) {
  if (l == NULL || k <= 0) {
    #ifndef NDEBUG
    printf("\033[0;31mbrak elementów do wypisania\033[0m\n");
    #endif
    printf("\n");
    return;
  }
  #ifndef NDEBUG
  printf("\033[1;36mpierwsze %d elementów:\033[0m", k);
  #endif
  int i = 0;
  while (l != NULL && i < k) {
    printf("%d", l->value);
    if (l->next != NULL && ++i < k ) {
      printf(" ");
    }
    l = l->next;
  }
  #ifndef NDEBUG
  printf("\033[1;36m koniec.\033[0m\n");
  #endif
  printf("\n");
}