/** @file
 * Interfejs klasy dwukierunkowych list liczb całkowitych.
 *
 * @author Kamil Dubil <kd370826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 03.04.2018
 */

#ifndef DLIST_H
#define DLIST_H

/**
 * Struktura dwukierunkowej listy liczb całkowitych typu int.
 */
typedef struct DList {
  struct DList *next; ///< wskaźnik na kolejny element listy
  struct DList *prev; ///< wskaźnik na poprzedni element listy
  int value; ///< liczba przechowywana w elemencie listy
} DList;

/** @brief Wstawia nowy element na początku listy.
 * Wstawia liczbę @p k na początku listy.
 * @param[in, out] beg – wskaźnik na wskaźnik na pierwszy element listy;
 * @param[in] k – wstawiana liczba.
 * @return Wskaźnik na pierwszy element wynikowej listy.
 */
extern DList* insertFrontDList(DList** beg, int k);

/** @brief Wstawia nowy element za pierwszym elementem listy.
 * Wstawia liczbę @p k za pierwszym elementem listy.
 * @param[in, out] first – wskaźnik na wskaźnik na pierwszy element listy;
 * @param[in] k – wstawiana liczba.
 * @return Wskaźnik na wstawiony element, czyli drugi element wynikowej listy.
 */
extern DList* insertAfterFirstDList(DList** first, int k);

/** @brief Usuwa element z listy.
 * Usuwa element listy wskazywany przez @p toRemove.
 * @param[in, out] toRemove – wskaźnik na wskaźnik na usuwany element listy.
 */
extern void removeDList(DList** toRemove);

/** @brief Zastępuje element listy inną listą.
 * Zastępuje element listy wskazywany przez @p toRemove listą o początku @p beg
 * i końcu @p end.
 * @param[in, out] toRemove – wskaźnik na wskaźnik na zastępowany element listy;
 * @param[in, out] beg – wskaźnik na wskaźnik na pierwszy element dołączanej listy;
 * @param[in, out] end – wskaźnik na wskaźnik na ostatni element dołączanej listy.
 */
extern void replaceDList(DList** toRemove, DList** beg, DList** end);

/** @brief Usuwa listę.
 * Usuwa listę wskazywaną przez @p beg, zwalnia zaalokowaną pamięć.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] beg – wskaźnik na wskaźnik na pierwszy element usuwanej listy.
 */
extern void delDList(DList** beg);

/** @brief Wyświetla listę.
 * Wypisuje na standardowe wyjście listę wskazywaną przez @p beg.
 * @param[in] beg – wskaźnik na pierwszy element wyświetlanej listy.
 */
extern void printDList(DList *beg);

#endif // DLIST_H