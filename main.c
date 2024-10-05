#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *word;
  int priority;

} dictionary_entry;

dictionary_entry *init(int *n) {
  /// Citim nr. de cuvinte
  scanf("%d ", n);

  /// Declar vectorul dictionar dinamic
  dictionary_entry *dictionar;
  dictionar = calloc(*n, sizeof(dictionary_entry));

  for (int i = 0; i < *n; i++) {
    /// Salvez cuvantul in dictionar si ii setez priority-ul 0
    char cuvant[21];
    scanf("%s", cuvant);

    /// copiez cuvantul in dictionar si ii dau prioritatea 0;
    cuvant[strlen(cuvant) + 1] = '\0';
    dictionar[i].word = calloc(strlen(cuvant) + 1, sizeof(char));
    strcpy(dictionar[i].word, cuvant);
    dictionar[i].priority = 0;
  }
  return dictionar;
}

void cautare(dictionary_entry *dictionar, char *cuvant, int *n) {
  /// variabila in care tin minte prioritatea maxima intalnita;
  int prior_max = -1;
  /// Semafor care imi spune daca am gasit cuvantul in dictionar
  int ok = 0;
  /// Declar o variabila pentru a tine minte pozitia cuvantului;
  int poz_cuv_prior;

  for (int i = 0; i < *n; i++) {
    char *exista = strstr(dictionar[i].word, cuvant);
    /// Verific daca cuvantul se afla in dictionar

    if (exista - dictionar[i].word == 0) {
      /// Verific daca prioritatea cuvantului din dictionar este mai mare decat
      /// prior_max;
      if (prior_max < dictionar[i].priority) {
        /// Daca da, cresc prioritatea
        dictionar[i].priority += 1;
        prior_max = dictionar[i].priority;

        /// Am gasit un cuvant potrivit in dictionar;
        ok = 1;

        /// Salvez pozitia cuvantului din dictionar cu prioritate maxima
        /// care se potriveste cu cuvantul transmis prin parametru
        poz_cuv_prior = i;

        /// Daca prioritatea maxima este egala cu prioritatea altui cuvant,
        /// verificam care cuvant este mai mic
      } else if (prior_max == dictionar[i].priority)

        /// Verific daca cuvantul curent este mai mic dpdv lexicografic decat
        /// cuv. cu prioritate maxima
        if (strcmp(dictionar[poz_cuv_prior].word, dictionar[i].word) > 0) {
          /// Cresc prioritatea cuvantului curent, o scad pe cea a cuvantului cu
          /// "prioritate cea mai mare" si dupa actualizez poz_cuv_prior cu
          /// pozitia cuvantului curent
          dictionar[i].priority++;
          dictionar[poz_cuv_prior].priority--;
          poz_cuv_prior = i;
        }
    }
  }

  /// Verific daca s-a gasit cuvantul in dictionar.
  /// Daca nu exista, il adaug la sfarsitul dictionarului si il afisez
  if (ok == 0) {
    (*n)++;
    dictionar[*n - 1].word = calloc(strlen(cuvant), sizeof(char));
    strcpy(dictionar[*n - 1].word, cuvant);
    dictionar[*n - 1].priority = 1;
    printf("%s ", cuvant);
    /// Daca exista, il afisez;
  } else {
    printf("%s ", dictionar[poz_cuv_prior].word);
  }
}

void update_Dictionar(int n, dictionary_entry *dictionar, int *m) {
  /// Citesc nr. de cuvinte pentru updatarea dictionarului
  scanf("%d ", m);
  dictionar = realloc(dictionar, (n + *m) * sizeof(dictionary_entry));

  for (int i = 0; i < *m; i++) {
    char cuvant[21];
    scanf("%s", cuvant);
    /// Cazul "*"
    if (cuvant[strlen(cuvant) - 1] == '*') {
      cuvant[strlen(cuvant) - 1] = '\0';
      printf("%s ", cuvant);
    }

    /// Cazul "semn de puctuatie"
    else if (cuvant[0] == '.' || cuvant[0] == ',' || cuvant[0] == '?' ||
             cuvant[0] == '?' || cuvant[0] == ':')
      printf("%s ", cuvant);
    /// Cazul "cuvant"

    else
      cautare(dictionar, cuvant, &n);
  }
}

int main() {
  int n, m;
  dictionary_entry *dictionar;
  dictionar = init(&n);

  update_Dictionar(n, dictionar, &m);

  return 0;
}