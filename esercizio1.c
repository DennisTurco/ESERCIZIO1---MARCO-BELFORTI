#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// struct
struct valuta {
    char nome[3];
    float tasso;
    int giorno, mese, anno;
};

float compare(const void *arg1, const void *arg2) {
    const struct valuta *x = arg1;
    const struct valuta *y = arg2;
    printf("x->tasso = %f, y->tasso = %f\n", x->tasso, y->tasso);

    //return y->tasso - x->tasso;
    if (x->tasso > y->tasso) return y->tasso;
    else return x->tasso;
}

int main (void){

    struct valuta *array;
    array = malloc(100 * sizeof(struct valuta *)); //array allocato dinamicamente di struct di tipo "valuta"
    FILE *file;

    // ------------ PUNTO 1 ------------
    char nome_file[32];
    printf("codice ISO-4217 della valuta da gestire: ");
    scanf("%s", &nome_file);
    file = fopen(nome_file, "r"); // r sta per read //ATTENZIONE!! qui sarebbe oppurtuno fare un controllo sul successo dell'apertura del file

    // ------------ PUNTO 2 ------------
    int array_dim = 1; // contatore che tiene traccia del numero di righe del file
    char c;
    while(!feof(file)) {
        fscanf(file, "%c", &c);
        if (c == '\n') array_dim++;
    }
    printf("Il file contiene %d righe\n", array_dim);
    fclose(file); // chiusura file
    
    // ------------ PUNTO 3 ------------
    file = fopen(nome_file, "r");
    for (int i=0; i<array_dim; i++){
        fscanf(file,"%c", &array[i].nome[0]);
        fscanf(file,"%c", &array[i].nome[1]);
        fscanf(file,"%c", &array[i].nome[2]);
        array[i].nome[3] = '\0';
        fscanf(file,"%c", &c); // leggo la virgola
        
        fscanf(file,"%f", &array[i].tasso);
        fscanf(file,"%c", &c); // leggo la virgola
        
        fscanf(file,"%d", &array[i].anno);
        fscanf(file,"%c", &c); // leggo la virgola
        
        fscanf(file,"%d", &array[i].mese);
        fscanf(file,"%c", &c); // leggo la virgola
        
        fscanf(file,"%d", &array[i].giorno);

        fscanf(file,"%c", &c); // leggo a capo
    }

    fclose(file); // chiusura file

    // ------------ PUNTO 4 ------------
    int numero;
    int val;
    int anno;
    int mese;
    int giorno;
    float somma = 0;
    int n = 0;
    char nome_formato[10];
    char nuovo_nome[32];
    int index = 0;
    FILE *file2;
    
    do {
        printf("\nMenu': \n0. esci; \n1. tasso di cambiamento per mese specifico; \n2. tasso cambiamento giorno; \n3. stampa i primi 10; \n4. ordinamento per tasso; \n5. ordinamento per data; \n6. salvare il contenuto dell'array su un nuovo file;\n");
        printf("scelta: ");
        scanf("%d", &numero);
        
        switch (numero) {
            case 0:
                return 0;
                break;
            
            case 1 :
                printf("inserire anno: ");
                scanf("%d", &anno);
                printf("inserire mese: ");
                scanf("%d", &mese);

                somma = 0;
                n = 0;
                for (int i=0; i<array_dim; i++){
                    if (array[i].anno == anno && array[i].mese == mese){
                        somma = somma + array[i].tasso;
                        n++;
                    } 
                }

                if (n != 0) printf("la media e': %f", somma/n);
                else printf("la media e': 0");

                break;

            case 2 :
                printf("inserire data (gg/mm/aaaa): ");
                scanf("%d", &giorno);
                scanf("%c", &c);
                scanf("%d", &mese);
                scanf("%c", &c);
                scanf("%d", &anno);

                for (int i=0; i<array_dim; i++){
                    if (array[i].anno == anno && array[i].mese == mese){
                        if (n != 0) printf("tasso: %f", array[i].tasso);
                        break;
                    } 
                }

                break;
            
            case 3:
                if (array_dim < 10) val = array_dim;
                else val = 10;

                for(int i=0; i<val; i++){
                    printf("\nRIGA %i: \n", i+1);
                    printf("%s\n", array[i].nome);
                    printf("%f\n", array[i].tasso);
                    printf("%d\n", array[i].giorno);
                    printf("%d\n", array[i].mese);
                    printf("%d\n", array[i].anno);
                }
                break;
            
            case 4:
                qsort(array, array_dim, sizeof(array), compare);
                break;
            
            case 5:
                qsort(array, array_dim, sizeof(array), compare);
                break;
            
            case 6:
                printf("inserire nuovo formato: ");
                scanf("%s", nome_formato);

                //ottengo il nome del file eliminandone il vecchio formato
                for (int i=0; i<strlen(nome_file); i++) {
                    if (nome_file[i] == '.') break;
                    nuovo_nome[index] = nome_file[i];
                    index++;
                    nuovo_nome[index] = '\0';
                }

                // aggiungo al nome del file senza la vecchia estensione quella nuova
                strcat(nuovo_nome, nome_formato);

                //salvo tutto nel nuovo file
                file2 = fopen(nuovo_nome, "w");
                for (int i=0; i<array_dim; i++) {
                    fprintf(file2, "%s", array[i].nome);
                    fprintf(file2, "%c", ',');
                    fprintf(file2, "%f", array[i].tasso);
                    fprintf(file2, "%c", ',');
                    fprintf(file2, "%d", array[i].anno);
                    fprintf(file2, "%c", ',');
                    fprintf(file2, "%d", array[i].mese);
                    fprintf(file2, "%c", ',');
                    fprintf(file2, "%d", array[i].giorno);
                    fprintf(file2, "%c", '\n');
                }
                fclose(file2);

                break;
        }

    } while(numero != 0);

    return 0;
}