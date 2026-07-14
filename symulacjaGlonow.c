#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turtle.c"

// Definicja struktury Rule, która reprezentuje pojedynczą regułę przekształcenia w systemie L.
typedef struct Rule
{
    char variable;     // Zmienna, która zostanie zastąpiona.
    char *replacement; // Ciąg, który zastąpi zmienną.
} Rule;

// Definicja struktury LSystem, która reprezentuje cały system L.
typedef struct LSystem
{
    char *axiom; // Aksjom, czyli początkowy ciąg.
    Rule *rules; // Tablica reguł przekształceń.
} LSystem;

// Deklaracje funkcji
char *applyRules(LSystem *, char);
char *generateLSystem(LSystem *, int);
void load_config(int *, int *, int *, int *);
void generateImage(int, int, int, int, char *);
void saveToTxtFile(char *, int);

int main()
{
    Rule rules[] = {
        {'A', "AB"}, // Reguła 1: A -> AB
        {'B', "A"}   // Reguła 2: B -> A
    };

    LSystem algae = {"A", rules};

    int resX, resY, step, iter;
    load_config(&resX, &resY, &iter, &step);
    if (resX < 0 || resY <= 0 || iter < 0 || step <= 0)
    {
        printf("Blad wczytywania konfiguracji\n");
        system("pause");
        return 1;
    }

    printf("Dane z pliku config: resX=%d, resY=%d, iter=%d, step=%d\n", resX, resY, iter, step);

    // Zapytanie o wyświetlenie danych wyjściowych w konsoli
    printf("Czy wyswietlic dane wyjsciowe w konsoli? (t/n)\n");
    char c;
    int showOutputCmd = 1;
    scanf("%c", &c);
    if (c == 'n')
        showOutputCmd = 0;

    for (int i = 0; i <= iter; i++)
    {
        char *result = generateLSystem(&algae, i);
        generateImage(resX, resY, i, step, result);
        saveToTxtFile(result, i);

        if (showOutputCmd)
            printf("n = %d: %s\n", i, result);
        free(result);
    }
    printf("Zapisano dane do pliku glonyOutput.txt, zdjecia symulacji znajduja sie w folderze glonyImg.\n");
    system("pause");
    return 0;
}

// FUNKCJE:

// Funkcja która stosuje reguły systemu do danego znaku
char *applyRules(LSystem *system, char c)
{
    // Przejście przez reguły systemu
    for (int i = 0; i < 2; i++)
    {
        // Jeśli zmienna w regule pasuje do danego znaku
        if (system->rules[i].variable == c)
            return system->rules[i].replacement;
    }
    // Zwraca "" jeśli żadna reguła nie jest spełniona
    return "";
}

// Funkcja, która generuje ciąg systemu L dla danej liczby iteracji
char *generateLSystem(LSystem *system, int iter)
{
    // Tworzenie nowego aksjomu jako kopii aksjomu systemu
    char *newAxiom = (char *)malloc(sizeof(char) * 2);
    strcpy(newAxiom, system->axiom);

    // Wykonywanie określonej liczby iteracji.
    for (int i = 0; i < iter; i++)
    {
        // Obliczanie długości aktualnego aksjomu
        int len = strlen(newAxiom);
        // Tworzenie nowego ciągu wynikowego, który będzie dwukrotnie dłuższy niż aktualny aksjom
        char *result = (char *)malloc(sizeof(char) * (len * 2));
        result[0] = '\0';

        // Przejście przez wszystkie znaki w aktualnym aksjomie.
        for (int j = 0; j < len; j++)
        {
            // Zastosowanie reguł systemu L do danego znaku i dodanie wyniku do ciągu wynikowego.
            strcat(result, applyRules(system, newAxiom[j]));
        }

        // Zwolnienie pamięci zajmowanej przez stary aksjom.
        free(newAxiom);
        // Ustawienie nowego ciągu wynikowego jako nowego aksjomu.
        newAxiom = result;
    }

    // Zwrócenie finalnego aksjomu po wykonaniu wszystkich iteracji.
    return newAxiom;
}

// Wczytanie danych konfiguracyjnych z pliku config.txt
void load_config(int *width, int *height, int *iter, int *step)
{
    FILE *cfg = fopen("config.txt", "r");

    if (!cfg)
    {
        perror("Blad otwarcia pliku config");
        system("pause");
        exit(2);
    }

    while (feof(cfg) == 0)
    {
        fgetc(cfg);
        fscanf(cfg, "width=%d", width);
        fscanf(cfg, "height=%d", height);
        fscanf(cfg, "iter=%d", iter);
        fscanf(cfg, "step=%d", step);
    }
    fclose(cfg);
}

// Generowanie obrazka
void generateImage(int width, int height, int iter, int step, char *result)
{
    if (width == 0)
        width = strlen(result) * step + 100;

    turtle_init(width, height);

    turtle_pen_up();
    turtle_goto_real(-width / 2, 0);
    turtle_forward(width / 2 - step * strlen(result) / 2);
    turtle_pen_down();
    turtle_set_pen_color(255, 0, 0);

    if ((int)(strlen(result) * step) > width)
    {
        printf("Brak miejsca na obrazku, zmniejsz ilosc iteracji lub zwieksz szerokosc obrazu\n");
        system("pause");
        exit(4);
    }

    for (size_t i = 0; i < strlen(result); i++)
    {
        if (i % 2 == 0)
            turtle_set_pen_color(0, 255, 0);
        else
            turtle_set_pen_color(0, 0, 255);

        turtle_forward(step);
    }

    char filename[50]; // Bufor na nazwę pliku.

    // Utworzenie nazwy pliku zawierającej numer iteracji.
    sprintf(filename, "glonyImg/glony_%d_%zu.png", iter, strlen(result));

    // Zapisanie obrazu do pliku.
    turtle_save_bmp(filename);
}

void saveToTxtFile(char *result, int iter)
{
    FILE *f;

    // Jeśli 1 iteracja, to tworzymy nowy plik, jeśli nie to dopisujemy do istniejącego
    if (iter == 0)
        f = fopen("glonyOutput.txt", "w");
    else
        f = fopen("glonyOutput.txt", "a");

    if (!f)
    {
        printf("Blad utworzenia pliku wyjsciowego txt\n");
        exit(3);
    }

    fprintf(f, "n = %d: %s\n", iter, result);
    fclose(f);
}
