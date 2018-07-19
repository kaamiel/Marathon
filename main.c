#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dlist.h"
#include "tree.h"
#include "constants.h"

// if NDEBUG is not defined, the program will write some unnecessary stuff
#define NDEBUG

// sprawdza, czy napis (zakończony znakiem '\n') o maksymalnej
// długości maxLength jest liczbą
static bool isNumberOnlyBeg(char *beg, unsigned maxLength) {
  if (beg == NULL || strlen(beg) > maxLength + 1) {
    return false;
  }
  size_t i;
  for (i = 0; i < strlen(beg) - 1; ++i) {
    if (beg[i] < '0' || beg[i] > '9') {
      return false;
    }
  }
  return true;
}

// sprawdza, czy napis pomiędzy beg i end jest liczbą
static bool isNumberBegEnd(char *beg, char *end, unsigned maxLength) {
  if (beg == NULL || end == NULL || beg == end ||
    strlen(beg) - strlen(end) > maxLength + 1) {
    return false;
  }
  size_t i;
  for (i = 0; i < strlen(beg) - strlen(end); ++i) {
    if (beg[i] < '0' || beg[i] > '9') {
      return false;
    }
  }
  return true;
}


int main() {
  init();

  size_t len;
  bool f = true;

  char *line = (char *)malloc(sizeof(char) * MAX_LINE_SIZE);
  if (line == NULL) {
    delTree();
    exit(1);
  }
  while (fgets(line, MAX_LINE_SIZE, stdin) != NULL) {

    #ifndef NDEBUG
    if (f) {
      printUsers();
    }
    printf(line);
    #endif

    len = strlen(line);

    // nothing to do
    if (len <= 1 || line[0] == '#') {
      continue;
    }

    // addUser
    else if (line == strstr(line, "addUser")) {
      char *firstSpace = strstr(line, " ");
      if (line + ADD_USER_LENGTH == firstSpace) {
        char *secondSpace = strstr(firstSpace + 1, " ");
        if (secondSpace != NULL) {
          if (isNumberBegEnd(firstSpace + 1, secondSpace, MAX_USER_ID_LENGTH) &&
            isNumberOnlyBeg(secondSpace + 1, MAX_USER_ID_LENGTH)) {
            long parentUserId = atol(firstSpace);
            long userId = atol(secondSpace);
            if (parentUserId < 0 || MAX_USER_ID < parentUserId ||
              userId <= 0 || MAX_USER_ID < userId) {
              f = false;
            }
            else {
              f = addChild((int)parentUserId, (int)userId);
            }
            f ? printf("OK\n") : fprintf(stderr, "ERROR\n");
            continue;
          }
        }
      }
      fprintf(stderr, "ERROR\n");
    }

    // delUser
    else if (line == strstr(line, "delUser")) {
      char *firstSpace = strstr(line, " ");
      if (line + DEL_USER_LENGTH == firstSpace) {
        if (isNumberOnlyBeg(firstSpace + 1, MAX_USER_ID_LENGTH)) {
          long userId = atol(firstSpace);
          if (userId <= 0 || MAX_USER_ID < userId) {
            f = false;
          }
          else {
            f = delChild((int)userId);
          }
          f ? printf("OK\n") : fprintf(stderr, "ERROR\n");
          continue;
        }
      }
      fprintf(stderr, "ERROR\n");
    }

    // addMovie
    else if (line == strstr(line, "addMovie")) {
      char *firstSpace = strstr(line, " ");
      if (line + ADD_MOVIE_LENGTH == firstSpace) {
        char *secondSpace = strstr(firstSpace + 1, " ");
        if (secondSpace != NULL) {
          if (isNumberBegEnd(firstSpace + 1, secondSpace, MAX_USER_ID_LENGTH) &&
            isNumberOnlyBeg(secondSpace + 1, MAX_MOVIE_RATING_LENGTH)) {
            long userId = atol(firstSpace);
            long movieRating = atol(secondSpace);
            if (userId < 0 || MAX_USER_ID < userId ||
              movieRating < 0 || MAX_MOVIE_RATING < movieRating) {
              f = false;
            }
            else {
              f = addMovie((int)userId, (int)movieRating);
            }
            f ? printf("OK\n") : fprintf(stderr, "ERROR\n");
            continue;
          }
        }
      }
      fprintf(stderr, "ERROR\n");
    }

    // delMovie
    else if (line == strstr(line, "delMovie")) {
      char *firstSpace = strstr(line, " ");
      if (line + DEL_MOVIE_LENGTH == firstSpace) {
        char *secondSpace = strstr(firstSpace + 1, " ");
        if (secondSpace != NULL) {
          if (isNumberBegEnd(firstSpace + 1, secondSpace, MAX_USER_ID_LENGTH) &&
              isNumberOnlyBeg(secondSpace + 1, MAX_MOVIE_RATING_LENGTH)) {
            long userId = atol(firstSpace);
            long movieRating = atol(secondSpace);
            if (userId < 0 || MAX_USER_ID < userId ||
              movieRating < 0 || MAX_MOVIE_RATING < movieRating) {
              f = false;
            }
            else {
              f = delMovie((int)userId, (int)movieRating);
            }
            f ? printf("OK\n") : fprintf(stderr, "ERROR\n");
            continue;
          }
        }
      }
      fprintf(stderr, "ERROR\n");
    }

    // marathon
    else if (line == strstr(line, "marathon")) {
      char *firstSpace = strstr(line, " ");
      if (line + MARATHON_LENGTH == firstSpace) {
        char *secondSpace = strstr(firstSpace + 1, " ");
        if (secondSpace != NULL) {
          if (isNumberBegEnd(firstSpace + 1, secondSpace, MAX_USER_ID_LENGTH) &&
            isNumberOnlyBeg(secondSpace + 1, MAX_MOVIE_RATING_LENGTH)) {
            long userId = atol(firstSpace);
            long k = atol(secondSpace);
            if (userId < 0 || MAX_USER_ID < userId ||
              k < 0 || MAX_MOVIE_RATING < k) {
              f = false;
            }
            else {
              f = marathon((int)userId, (int)k);
            }
            // if f == true, the answer has been written to stdout
            if (!f) {
              fprintf(stderr, "ERROR\n");
            }
            continue;
          }
        }
      }
      fprintf(stderr, "ERROR\n");
    }

    // error
    else {
      fprintf(stderr, "ERROR");
      #ifndef NDEBUG
      fprintf(stderr, " (błąd składni)");
      #endif
      fprintf(stderr, "\n");
    }

  }

  free(line);
  delTree();
  
  return 0;
}