/** @file
 * Implementacja klasy dwukierunkowych list liczb całkowitych.
 *
 * @author Kamil Dubil <kd370826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 03.04.2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dlist.h"

DList* insertFrontDList(DList** beg, int k) {
  DList *newElem = (DList *)malloc(sizeof(DList));
  if (newElem == NULL) {
    exit(1);
  }
  newElem->value = k;
  newElem->next = *beg;
  if (*beg != NULL) {
    (*beg)->prev = newElem;
  }
  newElem->prev = NULL;
  *beg = newElem;
  return newElem;
}

DList* insertAfterFirstDList(DList** first, int k) {
  assert(*first != NULL);
  DList *newElem = (DList *)malloc(sizeof(DList));
  if (newElem == NULL) {
    exit(1);
  }
  DList *snd = (*first)->next;
  newElem->value = k;
  newElem->next = snd;
  (*first)->next = newElem;
  newElem->prev = (*first);
  if (snd != NULL) {
    snd->prev = newElem;
  }
  return newElem;
}

void removeDList(DList** toRemove) {
  if ((*toRemove)->prev != NULL) {
    (*toRemove)->prev->next = (*toRemove)->next;
  }
  if ((*toRemove)->next != NULL) {
    (*toRemove)->next->prev = (*toRemove)->prev;
  }
  free(*toRemove);
  *toRemove = NULL;
}

void replaceDList(DList** toRemove, DList** beg, DList** end) {
  assert(*toRemove != NULL);
  if (*beg == NULL) {
    assert(*end == NULL);
    removeDList(toRemove);
    return;
  }
  if ((*toRemove)->prev != NULL) {
    (*toRemove)->prev->next = *beg;
  }
  (*beg)->prev = (*toRemove)->prev;

  if ((*toRemove)->next != NULL) {
    (*toRemove)->next->prev = *end;
  }
  (*end)->next = (*toRemove)->next;
  free(*toRemove);
}

void delDList(DList** beg) {
  while (*beg) {
    DList *tmp = *beg;
    *beg = (*beg)->next;
    free(tmp);
  }
}

void printDList(DList *beg) {
  if (beg == NULL) {
    printf("\033[0;31mpusta\033[0m\n");
    return;
  }
  printf("\033[1;36mpocz \033[0m");
  while (beg) {
    if (beg->prev == NULL && beg->next == NULL) {
      printf("[_ \033[0;32m%d\033[0m _]", beg->value);
    }
    else if (beg->prev == NULL) {
      printf("[_ \033[0;32m%d\033[0m %d]", beg->value, beg->next->value);
    }
    else if (beg->next == NULL) {
      printf("[%d \033[0;32m%d\033[0m _]", beg->prev->value, beg->value);
    }
    else {
      printf("[%d \033[0;32m%d\033[0m %d]",
        beg->prev->value, beg->value, beg->next->value);
    }
    beg = beg->next;
  }
  printf(" \033[1;36mkon\033[0m\n");
}