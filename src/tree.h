/** @file
 * Interfejs klasy drzewa użytkowników.
 *
 * @author Kamil Dubil <kd370826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 03.04.2018
 */

#ifndef TREE_H
#define TREE_H

/**
 * Struktura drzewa użytkowników.
 */
typedef struct Tree {
  DList *firstChild; ///< wskaźnik na pierwszego potomka na dwukierunkowej liście
  DList *lastChild; ///< wskaźnik na ostatniego potomka na dwukierunkowej liście
  DList *pointerOnParentsChildrenList; ///< wskaźnik na liście potomków ojca
  List *movies; ///< lista preferencji filmowych
} Tree;

/** @brief Inicjalizuje strukturę.
 * Inicjalizuje globalną tablicę – drzewo użytkowników.
 */
extern void init();

/** @brief Dodaje potomka.
 * Dodaje do wierzchołka użytkownika o identyfikatorze @p parentUserId
 * potomka o identyfikatorze @p userId.
 * @param[in] parentUserId – Identyfikator ojca;
 * @param[in] userId – Identyfikator dodawanego potomka.
 * @return Wartość @p true, jeśli potomek został dodany.
 *         Wartość @p false, jeśli potomek nie został dodany.
 */
extern bool addChild(int parentUserId, int userId);

/** @brief Sprawdza, czy użytkownik ma potomków.
 * Sprawdza, czy użytkownik o identyfikatorze @p userId ma potomków.
 * @param[in] userId – Identyfikator sprawdzanego użytkownika.
 * @return Wartość @p true, jeśli użytkownik ma potomków.
 *         Wartość @p false, jeśli użytkownik nie ma potomków.
 */
extern bool hasChildren(int userId);

/** @brief Usuwa użytkownika.
 * Usuwa użytkownika o identyfikatorze @p userId.
 * @param[in] userId – Identyfikator usuwanego użytkownika.
 * @return Wartość @p true, jeśli użytkownik został usunięty.
 *         Wartość @p false, jeśli użytkownik nie został usunięty.
 */
extern bool delChild(int userId);

/** @brief Dodaje film.
 * Dodaje do wierzchołka użytkownika o identyfikatorze @p userId preferencję
 * filmową o identyfikatorze i ocenie @p movieRating.
 * @param[in] userId – Identyfikator użytkownika;
 * @param[in] movieRating – Identyfikator i ocena dodawanego filmu.
 * @return Wartość @p true, jeśli preferencja filmowa została dodana.
 *         Wartość @p false, jeśli preferencja filmowa nie została dodana.
 */
extern bool addMovie(int userId, int movieRating);

/** @brief Usuwa film.
 * Usuwa z wierzchołka użytkownika o identyfikatorze @p userId preferencję
 * filmową o identyfikatorze i ocenie @p movieRating.
 * @param[in] userId – Identyfikator użytkownika;
 * @param[in] movieRating – Identyfikator i ocena usuwanego filmu.
 * @return Wartość @p true, jeśli preferencja filmowa została usunięta.
 *         Wartość @p false, jeśli preferencja filmowa nie została usunięta.
 */
extern bool delMovie(int userId, int movieRating);

/** @brief Wyznacza wynik operacji marathon.
 * Wypisuje na standardowe wyjście wynik wykonania operacji marathon
 * dla parametrów @p userId i @p k.
 * @param[in] userId – Identyfikator użytkownika;
 * @param[in] k – Maksymalna liczba filmów w wyniku.
 * @return Wartość @p true, jeśli operacja została wykonana poprawnie.
 *         Wartość @p false, jeśli operacja nie została wykonana poprawnie,
           z powodu błędnych parametrów.
 */
extern bool marathon(int userId, int k);

/** @brief Usuwa drzewo.
 * Usuwa drzewo użytkowników, zwalnia zaalokowaną pamięć.
 */
extern void delTree();

/** @brief Wyświetla użytkowników.
 * Wypisuje na standardowe wyjście wszystkich użytkowników.
 */
extern void printUsers();

#endif // TREE_H