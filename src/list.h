/** @file
 * Interfejs klasy różnowartościowych, posortowanych list liczb całkowitych.
 *
 * @author Kamil Dubil <kd370826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 03.04.2018
 */

#ifndef LIST_H
#define LIST_H

/**
 * Struktura jednokierunkowej, posortowanej malejąco, różnowartościowej listy
 * liczb całkowitych typu int.
 */
typedef struct List {
  struct List *next; ///< wskaźnik na kolejny element listy
  int value; ///< liczba przechowywana w elemencie listy
} List;

/** @brief Wstawia nowy element do listy, wynikowa lista jest malejąca.
 * Wstawia liczbę @p k do listy @p l.
 * @param[in, out] l – wskaźnik na wskaźnik na pierwszy element listy;
 * @param[in] k – wstawiana liczba.
 * @return Wartość @p true, jeśli element został dodany.
 *         Wartość @p false, jeśli element nie został dodany, gdyż lista
 *         zawierała już liczbę @p k.
 */
extern bool insertSortedList(List** l, int k);

/** @brief Usuwa element z listy.
 * Usuwa liczbę @p k z listy @p l, lista po usunięciu elementu pozostaje malejąca.
 * @param[in, out] l – wskaźnik na wskaźnik na pierwszy element listy;
 * @param[in] k – usuwana liczba.
 * @return Wartość @p true, jeśli element został usunięty.
 *         Wartość @p false, jeśli lista nie zawierała liczby @p k.
 */
extern bool removeList(List** l, int k);

/** @brief Usuwa listę.
 * Usuwa listę wskazywaną przez @p l, zwalnia zaalokowaną pamięć.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] l – wskaźnik na wskaźnik na pierwszy element usuwanej listy.
 */
extern void delList(List** l);

/** @brief Wyświetla listę.
 * Wypisuje na standardowe wyjście listę wskazywaną przez @p l.
 * @param[in] l – wskaźnik na pierwszy element wyświetlanej listy.
 */
extern void printList (List *l);

/** @brief Wyświetla początkowe k elementów listy.
 * Wypisuje na standardowe wyjście początkowe @p k elementów listy wskazywanej
 * przez @p l.
 * @param[in] l – wskaźnik na pierwszy element wyświetlanej listy;
 * @param[in] k – liczba wyświetlanych elementów. 
 */
extern void printFirstkElementsList (List *l, int k);

#endif // LIST_H