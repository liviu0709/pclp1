#include <stdio.h>
#define NMAX 100
 
int main() {
    // numele fisierului de intrare
    char input_filename[] = "bytes.bin";
    FILE *in;
 
    // incerc sa dechid pentru citire (r)
    // fisierul in mod binar (b)
    // observati alt mod de a scrie deschiderea && verificarea
    if ((in = fopen(input_filename, "rb")) == NULL) {
        fprintf(stderr, "Can't open %s", input_filename);
        return -1;
    }
 
    // numarul de elemente, vectorul, variabila de iterare
    int n, v[NMAX], i;
 
    // doresc sa citesc tinand cont de:
    // voi stoca in n (deci specific adresa lui n ca la scanf => &n)
    // valoarea citita are dimensiunea unui int => sizeof(int)
    // citesc o singura variabila => 1
    // voi citi din fisierul asociat cu variabila in
    fread(&n, sizeof(int), 1, in);
 
    // fread permite citirea unui vector printr-un singur apel
    // doresc sa citesc tinand cont de:
    // voi stoca in v (care este adresa primului element)
    // o valoare citita are dimensiunea unui int => sizeof(int)
    // citesc n valori
    // voi citi din fisierul asociat cu variabila in
    fread(v, sizeof(int), n, in);
 
    // pot inchide fisierul
    fclose(in);
 
     // dublez elementele din vector
    for (i = 0; i < n; ++i) {
        v[i] <<= 1;
    }
 
    // salvez rezultatul in fisierul out
     // numele fisierului de intrare
    char output_filename[] = "gigel_out.bin";
    FILE *out;
 
    // incerc sa dechid pentru scriere (w)
    // fisierul in mod binar (b)
    // observati alt mod de a scrie deschiderea && verificarea
    if ((out = fopen(output_filename, "wb")) == NULL) {
        fprintf(stderr, "Can't open %s", output_filename);
        return -1;
    }
 
    // doresc sa scriu tinand cont de:
    // voi scrie valoare de la adresa lui n (&n)
    // valoarea scrisa are dimensiunea unui int => sizeof(int)
    // scriu o singura variabila => 1
    // voi scrie in fisierul asociat cu variabila out
    fwrite(&n, sizeof(int), 1, out);
 
 
    // fwrite permite scrierea unui vector printr-un singur apel
    // doresc sa scriu tinand cont de:
    // voi scrie elemente incepand de la adresa indicata de v
    // o valoare scrisa are dimensiunea unui int => sizeof(int)
    // scriu n valori
    // voi scrie in fisierul asociat cu variabila out
    fwrite(v, sizeof(int), n, out);
 
    // inchid fisierul
    fclose(out);
 
    return 0;
}

