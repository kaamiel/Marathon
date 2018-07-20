# Marathon

Individual programming project, mimuw

Partly in Polish.




## Zadanie maraton filmowy

Celem zadania jest napisanie programu umożliwiającego grupom fanów kina wybieranie filmów do maratonu filmowego. Każdy kinomaniak (użytkownik) może wprowadzać preferowane filmy, które chciałby obejrzeć w trakcie maratonu, może je także usuwać. Użytkownik identyfikowany jest za pomocą identyfikatora liczbowego. Identyfikatory użytkowników są unikalne. Film identyfikowany jest za pomocą identyfikatora liczbowego. Identyfikatory filmów są unikalne. Użytkownicy tworzą drzewo. Każdy już zapisany użytkownik może dopisywać nowych użytkowników, jako potomków swojego wierzchołka drzewa. Na początku istnieje użytkownik o identyfikatorze 0 (korzeń drzewa), niemający żadnych preferencji filmowych. Każdy użytkownik z wyjątkiem użytkownika o identyfikatorze 0 może siebie wypisać. Identyfikator filmu jest też jego arbitralnie ustaloną oceną.

Rozwiązanie powinno korzystać z dynamicznie alokowanych struktur danych. Implementacja powinna być jak najbardziej efektywna. Należy unikać zbędnego alokowania pamięci i kopiowania danych. Przykładowe dane dla programu znajdują się w załączonym pliku.

## Operacje

Program ma wykonywać następujące operacje:

* `addUser <parentUserId> <userId>` -- Użytkownik o identyfikatorze `parentUserId` dodaje użytkownika o identyfikatorze `userId`. Operacja ma się wykonywać w czasie stałym.

* `delUser <userId>` -- Użytkownik o identyfikatorze `userId` wypisuje się. Dodane przez niego preferencje filmowe są zapominane. Użytkownicy uprzednio dodani przez użytkownika `userId` stają się potomkami rodzica użytkownika `userId`. Usunięcie użytkownika ma się wykonywać w czasie stałym. Zapominanie preferencji filmowych ma się wykonywać w czasie liniowym względem liczby preferencji usuwanego użytkownika.

* `addMovie <userId> <movieRating>` -- Użytkownik o identyfikatorze `userId` dodaje film o identyfikatorze `movieRating` do swoich preferencji filmowych. Operacja ma się wykonywać w czasie co najwyżej liniowym względem liczby preferencji użytkownika, który dodaje film.

* `delMovie <userId> <movieRating>` -- Użytkownik o identyfikatorze `userId` usuwa film o identyfikatorze `movieRating` ze swoich preferencji filmowych. Operacja ma się wykonywać w czasie co najwyżej liniowym względem liczby preferencji użytkownika, który usuwa film.

* `marathon <userId> <k>` -- Wyznacza co najwyżej `k` identyfikatorów filmów o najwyższych ocenach spośród:

  * własnych preferencji filmowych użytkownika o identyfikatorze `userId`;

  * preferencji filmowych wyodrębnionych w wyniku przeprowadzenia operacji `marathon` dla każdego z potomków użytkownika `userId`, przy czym w wynikowej grupie `k` filmów znajdą się tylko takie, które mają ocenę większą od maksymalnej oceny filmu spośród preferencji użytkownika `userId`.

Operacja ma się wykonywać w czasie liniowym względem iloczynu parametru `k` i liczby użytkowników, dla których rekurencyjnie wyliczana jest ta operacja.

## Dane wejściowe

Program powinien czytać ze standardowego wejścia. Można przyjąć następujące założenia o danych wejściowych:

* Parametry `<userID>` i `<parentUserID>` są liczbami całkowitymi z przedziału od 0 do 65535.
* Parametry `<movieRating>` oraz `<k>` są liczbami całkowitymi z przedziału od 0 do 2147483647.
* Nazwa polecenia i liczby są oddzielone pojedynczą spacją, a każdy wiersz wejścia kończy się linuksowym znakiem końca linii (znak `\n` w C, kod ASCII 10). Są to jedyne białe znaki występujące w danych wejściowych.

## Informacje wypisywane przez program

Program wypisuje na standardowe wyjście:

* Dla każdej operacji innej niż `marathon` wiersz ze słowem `OK`.
* Dla operacji `marathon` wiersz zawierający posortowane malejąco wyznaczone oceny, a w przypadku braku filmów spełniających warunki maratonu wiersz zawierający jedynie słowo `NONE`. Oceny powinny być oddzielone pojedynczą spacją. Na końcu wiersza nie może być spacji.
* Każdy wiersz wyjścia powinien kończyć się linuksowym znakiem końca linii (znak `\n` w C, kod ASCII 10).

## Obsługa błędów

Program wypisuje informacje o błędach na standardowe wyjście diagnostyczne.

* Puste wiersze należy ignorować.
* Wiersze rozpoczynające się znakiem `#` należy ignorować.
* Dla każdego błędnego wiersza i dla każdej operacji, która nie może być wykonana np. z powodu błędnej wartości parametru, należy wypisać wiersz ze słowem `ERROR`, zakończony linuksowym znakiem końca linii (znak `\n` w C, kod ASCII 10).

## Zakończenie programu

Program kończy się po przetworzeniu wszystkich operacji z wejścia i powinien wtedy zakończyć się kodem 0. Awaryjne zakończenie programu, np. na skutek niemożliwości zaalokowania potrzebnej pamięci, powinno być sygnalizowane kodem 1. Przed zakończeniem program powinien zwolnić całą zaalokowaną pamięć.

## Makefile

Częścią zadania jest napisanie pliku `makefile`. W wyniku wywołania polecenia `make` powinien powstać program wykonywalny `main`. Jeśli któryś z plików źródłowych ulegnie zmianie, ponowne wpisanie `make` powinno na nowo stworzyć plik wykonywalny. Plik `makefile` powinien działać w następujący sposób:

* osobno kompiluje każdy plik `.c`,
* osobno linkuje wszystkie pliki `.o`,
* przy zmianie w pliku `.c` lub `.h` wykonuje tylko niezbędne akcje,
* wywołanie `make clean` usuwa plik wykonywalny i dodatkowe pliki powstałe podczas kompilowania.

Pliki należy kompilować z opcjami:

```
-Wall -Wextra -std=c11 -O2
```

## Skrypt testujący

Osobną częścią zadania jest napisanie skryptu `test.sh`. Po wywołaniu

```
./test.sh <prog> <dir>
```

skrypt powinien uruchomić program `<prog>` dla wszystkich plików wejściowych postaci `<dir>/*.in`, porównać wyniki z odpowiadającymi im plikami `<dir>/*.out` i `<dir>/*.err`, a następnie wypisać, które testy zakończyły się powodzeniem, a które niepowodzeniem. Do wykrywania problemów z zarządzaniem pamięcią należy użyć programu `valgrind`.

## Podział na pliki

Rozwiązanie powinno zawierać następujące pliki:

* `main.c` -- Główny plik programu, w którym wczytuje się dane wejście, wywołuje operacje na strukturach danych i wypisuje wyniki działania programu. Plik ten nie powinien znać szczegółów definicji i implementacji użytych struktur danych.
* `x.c`, `x.h` -- Implementacja modułu (struktury danych) `x`. Plik `x.h` zawiera deklaracje operacji modułu `x`, a plik `x.c` -- ich implementację. Jako `x` należy użyć stosownej nazwy modułu (struktury danych), np. `tree` itp. Powinno być tyle par plików `x.c`, `x.h`, ile jest w rozwiązaniu modułów (struktur danych).
* `makefile` -- Patrz punkt ,,makefile".
* `test.sh` -- Patrz punkt ,,skrypt testujący".

Rozwiązanie należy oddać jako archiwum skompresowane programem `zip` lub parą programów `tar` i `gz`.

## Punktacja

Za w pełni poprawne rozwiązanie zadania implementujące wszystkie funkcjonalności można zdobyć maksymalnie 20 punktów. Rozwiązanie niekompilujące się lub nie oparte na dynamicznie alokowanych strukturach danych będzie ocenione na 0 punktów. Możliwe są punkty karne za poniższe uchybienia:

* Za każdy test, którego program nie przejdzie, traci się 1 punkt.
* Za problemy z zarządzaniem pamięcią można stracić do 6 punktów.
* Za niezgodną ze specyfikacją strukturę plików w rozwiązaniu można stracić do 4 punktów.
* Za złą złożoność operacji można stracić do 4 punktów.
* Za błędy stylu kodowania można stracić do 4 punktów.
* Za brak lub źle działający `makefile` można stracić do 2 punktów.
* Za brak skryptu testującego lub błędy w skrypcie testującym można stracić do 2 punktów.

