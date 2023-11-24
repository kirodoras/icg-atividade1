//------------------------
// Universidade Federal de Sergipe
// Departamento de Matemática
// Prof Evilson Vieira
// Gera os dados histograma de tons de cinza a partir de uma imagem PGM
// 1. Compilar: gcc pgmtohisto.c -o pgmtohisto
// 2. Executar: ./pgmtohisto wolverine.pgm
// 3. Os arquivos histograma.txt e histograma.pbm serão criados
// 4. Para visualizar: cat histograma.txt
// Aluno: Mateus Figueiredo Pereira
// Aracaju-SE
//------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TONS_DE_CINZA 256
void main(int argc, char **argv)
{
  int i, j, l, h;
  unsigned char type, cmax, caractere;
  FILE *fp;
  FILE *fp_pbm;

  fp = fopen(argv[1], "r");

  while ((caractere = getc(fp)) == '#')
    while ((caractere = getc(fp)) != '\n')
      ;
  ungetc(caractere, fp);

  fscanf(fp, "P%hhu\n", &type);

  while ((caractere = getc(fp)) == '#')
    while ((caractere = getc(fp)) != '\n')
      ;
  ungetc(caractere, fp);

  fscanf(fp, "%u %u %hhu\n", &l, &h, &cmax);

  unsigned char p[h][l];

  if (type == 2)
  {
    for (i = 0; i < h; i++)
      for (j = 0; j < l; j++)
        fscanf(fp, "%hhd", &p[i][j]);
    fclose(fp);
  }
  else if (type == 5)
  {
    for (i = 0; i < h; i++)
      for (j = 0; j < l; j++)
        fscanf(fp, "%c", &p[i][j]);
    fclose(fp);
  }
  else
  {
    printf("Formato inválido!");
    fclose(fp);
    exit(0);
  }

  unsigned int k[TONS_DE_CINZA];
  unsigned char v[TONS_DE_CINZA];
  unsigned char m[100][TONS_DE_CINZA];
  int qtd_max = 0;

  for (i = 0; i < TONS_DE_CINZA; i++)
  {
    k[i] = 0;
    v[i] = 0;
  }

  for (i = 0; i < h; i++)
    for (j = 0; j < l; j++)
    {
      k[p[i][j]] = k[p[i][j]] + 1;
    }

  for (i = 0; i < TONS_DE_CINZA; i++)
  {
    if (k[i] > qtd_max)
      qtd_max = k[i];
  }

  for (i = 0; i < TONS_DE_CINZA; i++)
  {
    v[i] = round(100 - ((k[i] * 100) / qtd_max));
  }

  for (i = 0; i < 100; i++)
    for (j = 0; j < TONS_DE_CINZA; j++)
    {
      if (v[j] > i)
        m[i][j] = 0;
      else
        m[i][j] = 1;
    }

  fp = fopen("histograma.txt", "w");
  fprintf(fp, "Criado no curso de Introdução à Computação Gráfica\n");
  fprintf(fp, "Departamento de Matemática - UFS - Prof Evilson Vieira\n");
  fprintf(fp, "Aluno: Mateus Figueiredo Pereira\n");
  fprintf(fp, "Tons, Qtde de pixels\n");
  for (i = 0; i < TONS_DE_CINZA; i++)
    fprintf(fp, "%i, %i\n", i, k[i]);
  fclose(fp);

  fp_pbm = fopen("histograma.pbm", "w");
  fprintf(fp_pbm, "P1\n");
  fprintf(fp_pbm, "%u %u\n", TONS_DE_CINZA, 100);
  for (i = 0; i < 100; i++)
    for (j = 0; j < TONS_DE_CINZA; j++)
      fprintf(fp_pbm, "%hhu ", m[i][j]);
  fclose(fp_pbm);
}