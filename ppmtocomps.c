//------------------------
// Universidade Federal de Sergipe
// Departamento de Matemática
// Prof Evilson Vieira
// Separa uma imagem colorida .ppm em suas três componentes RGB
// 1. Compilar: gcc ppmtocomps.c -o ppmtocomps
// 2. Executar: ./ppmtocomps wolverine.ppm
// 3. Os arquivos component-red.ppm, component-green.ppm e component-blue.ppm serão criados
// 4. Para visualizar: eog component-red.ppm
// Aluno: Mateus Figueiredo Pereira
// Aracaju-SE
//------------------------
#include <stdio.h>
#include <stdlib.h>
void main(int argc, char **argv)
{
  int i, j, l, h, k;
  unsigned char type, cmax, caractere;
  FILE *fp;
  FILE *fp_red;
  FILE *fp_green;
  FILE *fp_blue;

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
  unsigned char p[h][l][3];

  if (type == 3)
  {
    for (i = 0; i < h; i++)
      for (j = 0; j < l; j++)
        fscanf(fp, "%hhd %hhd %hhd", &p[i][j][0], &p[i][j][1], &p[i][j][2]);
    fclose(fp);
  }
  else if (type == 6)
  {
    for (i = 0; i < h; i++)
      for (j = 0; j < l; j++)
        fscanf(fp, "%c%c%c", &p[i][j][0], &p[i][j][1], &p[i][j][2]);
    fclose(fp);
  }
  else
  {
    printf("Formato inválido!");
    fclose(fp);
    exit(0);
  }

  unsigned char red[h][l][3];
  unsigned char green[h][l][3];
  unsigned char blue[h][l][3];

  for (i = 0; i < h; i++)
    for (j = 0; j < l; j++)
      for (k = 0; k < 3; k++)
      {
        if (k == 0)
        {
          red[i][j][k] = p[i][j][k];
          green[i][j][k] = 0;
          blue[i][j][k] = 0;
        }
        if (k == 1)
        {
          red[i][j][k] = 0;
          green[i][j][k] = p[i][j][k];
          blue[i][j][k] = 0;
        }
        if (k == 2)
        {
          red[i][j][k] = 0;
          green[i][j][k] = 0;
          blue[i][j][k] = p[i][j][k];
        }
      }

  fp_red = fopen("component-red.ppm", "w");
  fprintf(fp_red, "P6\n");
  fprintf(fp_red, "# Criado no curso de Introdução à Computação Gráfica\n");
  fprintf(fp_red, "# Departamento de Matemática - UFS - Prof Evilson Vieira\n");
  fprintf(fp_red, "# Aluno: Mateus Figueiredo Pereira\n");
  fprintf(fp_red, "%u %u\n%hhu\n", l, h, cmax);

  fp_green = fopen("component-green.ppm", "w");
  fprintf(fp_green, "P6\n");
  fprintf(fp_green, "# Criado no curso de Introdução à Computação Gráfica\n");
  fprintf(fp_green, "# Departamento de Matemática - UFS - Prof Evilson Vieira\n");
  fprintf(fp_green, "# Aluno: Mateus Figueiredo Pereira\n");
  fprintf(fp_green, "%u %u\n%hhu\n", l, h, cmax);

  fp_blue = fopen("component-blue.ppm", "w");
  fprintf(fp_blue, "P6\n");
  fprintf(fp_blue, "# Criado no curso de Introdução à Computação Gráfica\n");
  fprintf(fp_blue, "# Departamento de Matemática - UFS - Prof Evilson Vieira\n");
  fprintf(fp_blue, "# Aluno: Mateus Figueiredo Pereira\n");
  fprintf(fp_blue, "%u %u\n%hhu\n", l, h, cmax);

  for (i = 0; i < h; i++)
    for (j = 0; j < l; j++)
    {
      fprintf(fp_red, "%c%c%c", red[i][j][0], red[i][j][1], red[i][j][2]);
      fprintf(fp_green, "%c%c%c", green[i][j][0], green[i][j][1], green[i][j][2]);
      fprintf(fp_blue, "%c%c%c", blue[i][j][0], blue[i][j][1], blue[i][j][2]);
    }

  fclose(fp_red);
  fclose(fp_green);
  fclose(fp_blue);
}
/*
Anotações:
  1. Em caso do arquivo ppm ser no formato P3
  for (i = 0; i < h; i++)
    for (j = 0; j < l; j++)
      fprintf(fp, "%hhu %hhu %hhu ", red[i][j][0], red[i][j][1], red[i][j][2]);
  2. Em caso do arquivo ppm ser no formato P6
  for (i = 0; i < h; i++)
    for (j = 0; j < l; j++)
      fprintf(fp, "%c%c%c", red[i][j][0], red[i][j][1], red[i][j][2]);
  outra opção:
  fwrite(red, sizeof(unsigned char), h * l * 3, fp);

  3.
    1. fprintf: é para dados formatados em texto
    2. fwrite: é para escrever dados em formato binário
        fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
        ptr: É o ponteiro para o bloco de memória que contém os dados a serem gravados.
        size: É o tamanho, em bytes, de cada elemento a ser gravado.
        nmemb: É o número de elementos a serem gravados.
        stream: É o ponteiro do arquivo onde os dados serão gravados.
*/