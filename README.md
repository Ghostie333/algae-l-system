# Program do Symulacji Rozrostu Glonów z użyciem L-Systemu

## 1. Definicja problemu badawczego

### Opis badanego zjawiska
Rozrost glonów w środowisku naturalnym jest zjawiskiem złożonym i zależnym od wielu czynników. Aby lepiej zrozumieć mechanizmy tego procesu, możemy wykorzystać modelowanie komputerowe. W naszym projekcie skupiamy się na symulacji wzrostu glonów przy użyciu L-systemów (systemów Lindenmayera), które są formalnymi gramatykami stosowanymi do modelowania wzrostu roślinnych struktur.

### Cel badania
Dowiedzieć się, jak różne parametry L-systemu wpływają na wzorce wzrostu glonów. Celem jest stworzenie programu, który pozwoli na wizualizację i analizę tych wzorców poprzez symulacje komputerowe.

## 2. Rozwiązanie problemu

### Trafne rozwiązanie techniczne

#### Pomysł na program
Program został zbudowany w języku C. Jego głównym celem jest odczytanie parametrów symulacji z pliku konfiguracyjnego `config.txt`, a następnie symulacja rozrostu glonów przy użyciu L-systemu. Wyniki symulacji są wizualizowane oraz zapisywane do pliku `txt`, co pozwala na analizę wzorców wzrostu.

#### Funkcjonalności programu
- **Odczyt parametrów z pliku konfiguracyjnego**: Program odczytuje parametry z pliku `config.txt`.
- **Symulacja L-systemu**: Na podstawie odczytanych parametrów, program generuje kolejne iteracje L-systemu.
- **Wizualizacja**: Program tworzy wizualizację wygenerowanych struktur, umożliwiając użytkownikowi obserwację wzorców wzrostu.

#### Parametry do kontroli
Użytkownik może kontrolować następujące parametry:
- Liczba iteracji symulacji.
- Szerokość pliku wyjściowego.
- Wysokość pliku wyjściowego.
- Rozmiar kroku rysowania.

#### Niezawodność
Program został zaprojektowany z myślą o niezawodności, poprzez:
- Walidację danych wejściowych.
- Obsługę błędów i wyjątków.
- Testy na różnych zestawach danych konfiguracyjnych.

#### Przyjazność w użytkowaniu i atrakcyjność wizualna
Interfejs użytkownika jest prosty i intuicyjny. Wizualizacje są generowane w sposób estetyczny, z użyciem kolorów, które ułatwiają interpretację wyników symulacji.

## 3. Przykład użycia

### Przykładowy plik `config.txt`
```txt
# Liczba iteracji
iter=10
# Szerokość pliku wyjściowego bmp (0 automatycznie dostosuje szerokość pliku do długości glonów)
width=0
# Wysokość pliku wyjściowego bmp
height=100
# Rozmiar kroku rysowania
step=20
```

### Kroki działania programu
1. **Odczyt pliku konfiguracyjnego**: Program zczytuje zawartość `config.txt`.
2. **Generowanie L-systemu**: Na podstawie aksjomatu i reguł produkcji, program generuje kolejne iteracje L-systemu.
```txt
# Aksjom początkowy:
A
# Zasady symulacji:
(A → AB), (B → A)
```
4. **Wizualizacja**: Program tworzy wizualizację wyników w formie graficznej.

### Rzuty ekranu
#### Początkowy stan (Aksjomat)
![Początkowy stan](glonyImg/glony_0_1.png)

n = 0: A

#### Po pierwszej iteracji
![Pierwsza iteracja](glonyImg/glony_1_2.png)

n = 1: AB

#### Po czwartej iteracji
![Czwarta iteracja](glonyImg/glony_4_8.png)

n = 4: ABAABABA

## 4. Lista dodatkowych bibliotek

- **<stdio.h>**: Do operacji wejścia/wyjścia i tworzenia plików.
- **<stdlib.h>**: Zarządzanie pamięcią, obsługa środowiska.
- **<string.h>**: Operacje na ciągach znaków.
- **<turtle.h>**: Generowanie obrazków wizualizujących symulacje.

## 5. Opis krok po kroku, jak skompilować i uruchomić program

### Krok 1: Pobranie programu
Pobierz i wypakuj pliki programu.

### Krok 2: Kompilacja programu
Użyj kompilatora GCC do skompilowania programu:
```bash
gcc -Wall -Wextra symulacjaGlonow.c -o symulacjaGlonow
```

### Krok 3: Uruchomienie programu
Możesz już uruchomić skompilowany plik wykonywalny programu `symulacjaGlonow.exe`.

Upewnij się, że plik `config.txt` znajduje się w tym samym katalogu co plik wykonywalny programu.
