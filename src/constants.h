/** @file
 * Plik zawierający definicje stałych wykorzystywanych w innych modułach.
 *
 * @author Kamil Dubil <kd370826@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 03.04.2018
 */

/**
 * Maksymalny identyfikator użytkownika
 */
#define MAX_USER_ID 65535
/**
 * Maksymalna ocena filmu
 */
#define MAX_MOVIE_RATING 2147483647
/**
 * Maksymalna długość udentyfikatora użytkownika
 */
#define MAX_USER_ID_LENGTH 5
/**
 * Maksymalna długość oceny filmu
 */
#define MAX_MOVIE_RATING_LENGTH 10

/**
 * Maksymalna długość wczytywanej ze standardowego wejścia linii
 */
#define MAX_LINE_SIZE 200

/**
 * Długość napisu `addUser`
 */
#define ADD_USER_LENGTH 7
/**
 * Długość napisu `delUser`
 */
#define DEL_USER_LENGTH 7
/**
 * Długość napisu `addMovie`
 */
#define ADD_MOVIE_LENGTH 8
/**
 * Długość napisu `delMovie`
 */
#define DEL_MOVIE_LENGTH 8
/**
 * Długość napisu `marathon`
 */
#define MARATHON_LENGTH 8

/**
 * Domyślny identyfikator pierwszego i ostatniego potomka na liście
 */
#define DEFAULT_FIRST_LAST_CHILD -1