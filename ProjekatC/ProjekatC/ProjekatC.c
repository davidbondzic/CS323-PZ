#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CURRENCY_NAME_LENGTH 50
#define MAX_CURRENCY_CODE_LENGTH 5

// Struktura za valutu
typedef struct {
    char name[MAX_CURRENCY_NAME_LENGTH];
    char code[MAX_CURRENCY_CODE_LENGTH];
    double rate;
} Currency;

// Funkcija za dodavanje valute
void addCurrency(Currency** currencies, int* size) {
    Currency* newCurrencies = realloc(*currencies, (*size + 1) * sizeof(Currency));
    if (newCurrencies == NULL) {
        printf("Alokacija memorije neuspesna!\n");
        exit(1);
    }

    *currencies = newCurrencies;
    *size += 1;

    printf("Unesite ime valute: ");
    if (scanf_s("%49s", (*currencies)[*size - 1].name, (unsigned int)MAX_CURRENCY_NAME_LENGTH) != 1) {
        printf("Error.\n");
        return;
    }
    printf("Unesite sifru valute: ");
    if (scanf_s("%4s", (*currencies)[*size - 1].code, (unsigned int)MAX_CURRENCY_CODE_LENGTH) != 1) {
        printf("Error.\n");
        return;
    }
    printf("Unesite odnos valute prema USD: ");
    if (scanf_s("%lf", &(*currencies)[*size - 1].rate) != 1) {
        printf("Error.\n");
        return;
    }
}

// Funkcija za prikazivanje valuta
void displayCurrencies(Currency* currencies, int size) {
    for (int i = 0; i < size; i++) {
        printf("Valuta %d:\n", i + 1);
        printf("Ime: %s\n", currencies[i].name);
        printf("Sifra: %s\n", currencies[i].code);
        printf("Odnos prema USD: %.2f\n", currencies[i].rate);
        printf("\n");
    }
}

// Funkcija za konverziju iz jedne valute u drugu
void convertCurrency(Currency* currencies, int size) {
    char fromCode[MAX_CURRENCY_CODE_LENGTH];
    char toCode[MAX_CURRENCY_CODE_LENGTH];
    double amount;
    int fromIndex = -1, toIndex = -1;

    printf("Unesite sifru valute iz koje konvertujete: ");
    if (scanf_s("%4s", fromCode, (unsigned int)MAX_CURRENCY_CODE_LENGTH) != 1) {
        printf("Error.\n");
        return;
    }
    printf("Unesite sifru valute u koju konvertujete: ");
    if (scanf_s("%4s", toCode, (unsigned int)MAX_CURRENCY_CODE_LENGTH) != 1) {
        printf("Error reading input.\n");
        return;
    }
    printf("Unesite iznos: ");
    if (scanf_s("%lf", &amount) != 1) {
        printf("Error.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (strcmp(currencies[i].code, fromCode) == 0) {
            fromIndex = i;
        }
        if (strcmp(currencies[i].code, toCode) == 0) {
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1) {
        printf("Uneta pogresna sifra.\n");
        return;
    }

    double amountInUSD = amount / currencies[fromIndex].rate;
    double convertedAmount = amountInUSD * currencies[toIndex].rate;

    printf("%.2f %s je jednako %.2f %s\n", amount, fromCode, convertedAmount, toCode);
}

// Funkcija za cuvanje valuta u tekstualni fajl
void saveCurrenciesToFile(Currency* currencies, int size, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Nije moguce otvoriti fajl.\n");
        return;
    }
    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %s %.2f\n", currencies[i].name, currencies[i].code, currencies[i].rate);
    }
    fclose(file);
}

// Funkcija za ucitavanje valuta iz tekstualnog fajla
void loadCurrenciesFromFile(Currency** currencies, int* size, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Nije moguce otvoriti fajl.\n");
        *size = 0; // Ensure size is set to 0 if file cannot be opened
        return;
    }
    fscanf_s(file, "%d\n", size);
    *currencies = malloc(*size * sizeof(Currency));
    if (*currencies == NULL) {
        printf("Alokacija memorije neuspesna!\n");
        exit(1);
    }
    for (int i = 0; i < *size; i++) {
        if (fscanf_s(file, "%49s %4s %lf\n", (*currencies)[i].name, (*currencies)[i].code, &(*currencies)[i].rate) != 3) {
            printf("Error.\n");
            fclose(file);
            free(*currencies);
            *currencies = NULL;
            *size = 0;
            return;
        }
    }
    fclose(file);
}

int main() {
    Currency* currencies = NULL;
    int size = 0;
    int choice;
    const char* filename = "currencies.txt";

    loadCurrenciesFromFile(&currencies, &size, filename);

    do {
        printf("Menjacnica:\n");
        printf("1. Dodaj valutu\n");
        printf("2. Prikaz valuta\n");
        printf("3. Konvertuj valutu\n");
        printf("4. Save and Exit\n");
        printf("Unesite vas izbor: ");
        if (scanf_s("%d", &choice) != 1) {
            printf("Error.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
        case 1:
            addCurrency(&currencies, &size);
            break;
        case 2:
            displayCurrencies(currencies, size);
            break;
        case 3:
            convertCurrency(currencies, size);
            break;
        case 4:
            saveCurrenciesToFile(currencies, size, filename);
            printf("Valute sacuvane. Exiting...\n");
            break;
        default:
            printf("Nepravilan unos. Pokusajte ponovo.\n");
        }
    } while (choice != 4);

    free(currencies);
}
