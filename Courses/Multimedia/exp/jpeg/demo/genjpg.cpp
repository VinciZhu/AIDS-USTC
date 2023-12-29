#include "global.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define SOI 0xffd8
#define EOI 0xffd9
#define SOF0 0xffc0
#define SOF1 0xffc1
#define SOF2 0xffc2
#define SOF3 0xffc3
#define SOF5 0xffc5
#define SOS 0xffda
#define DQT 0xffdb
#define DHT 0xffc4
#define DNL 0xffdc

using namespace std;

void WriteWordFlag(int);
void WriteByteFlag(unsigned char);
FILE *infp, *outfp;

int main(int argc, char *argv[]) {
  int x;
  long int i, j, l, k;
  unsigned char gray;
  int handle, temp;

  char *input_file = argv[1];
  char *output_file = argv[2];

  // cout << "Please input the filename of datastream :";
  // cin >> filename;
  infp = fopen(input_file, "rb");
  if (infp == NULL) {
    cout << "File open error";
    exit(0);
  }
  fseek(infp, 0, 0);
  // cout << "Please input the JPG file 's name you want to generate :";
  // cin >> filename
  outfp = fopen(output_file, "wb");
  if (outfp == NULL) {
    cout << "File open error";
    exit(0);
  }
  fseek(outfp, 0, 0);
  //---------------------------
  WriteWordFlag(SOI);
  //-----------------------
  WriteWordFlag(DQT);
  WriteWordFlag(67);
  WriteByteFlag(0x03);
  for (i = 0; i < 64; i++) {
    temp = Q_matrix[pot_x[i]][pot_y[i]];
    WriteByteFlag(temp);
  }

  WriteWordFlag(DHT);
  WriteWordFlag(31);
  WriteByteFlag(0x00); // WriteWordFlag(0x0101);
  FILE *d_table = fopen("dc.tab", "rb");
  fseek(d_table, 0, 0);
  for (i = 0; i < 28; i++) {
    fread(&temp, 1, 1, d_table);
    WriteByteFlag(temp);
  }
  fclose(d_table);

  WriteWordFlag(DHT);
  WriteWordFlag(181);
  WriteByteFlag(0x11); // WriteWordFlag(0x0101);
  FILE *a_table = fopen("ac.tab", "rb");
  fseek(a_table, 0, 0);
  for (i = 1; i <= 178; i++) {
    fread(&temp, 1, 1, a_table);
    WriteByteFlag(temp);
  }
  fclose(a_table);
  //------------------------
  WriteWordFlag(SOF0);
  WriteWordFlag(11); // lf
  WriteByteFlag(8);  // p
  WriteWordFlag(256);
  WriteWordFlag(256);  // y,x
  WriteByteFlag(1);    // nf
  WriteByteFlag(0);    // c
  WriteByteFlag(0x11); // h,v
  WriteByteFlag(3);    // tq

  //------------------------
  WriteWordFlag(SOS);
  WriteWordFlag(8); // ls
  WriteByteFlag(1); // ns
  WriteByteFlag(0);
  WriteByteFlag(0x01); // cs,td,ta
  WriteByteFlag(0);
  WriteByteFlag(63);
  WriteByteFlag(0); // ss,se,ah,al
  //-----------------------------------------------------------
  while (!feof(infp)) {
    fread(&gray, 1, 1, infp);
    fwrite(&gray, 1, 1, outfp);
  }
  //-----------------------------------------------------------
  WriteWordFlag(EOI);
  fclose(infp);
  fclose(outfp);
}

void WriteWordFlag(int val) {
  unsigned char tmp;
  unsigned int val1 = val;
  tmp = (val1 >> 8);
  fwrite(&tmp, 1, 1, outfp);
  tmp = val1;
  fwrite(&tmp, 1, 1, outfp);
}

void WriteByteFlag(unsigned char val) {
  unsigned char tmp = val;
  fwrite(&tmp, 1, 1, outfp);
}