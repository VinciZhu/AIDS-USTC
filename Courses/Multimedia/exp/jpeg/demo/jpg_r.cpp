#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const double pi = atan(1.0) * 4;

ofstream text_data("jpg_code.txt", ios::out);
ofstream result_data("lady_pre.dat", ios_base::binary);

void print_binary(int value, char *str) {
  int i = 0;
  while (value != 0) {
    str[i] = value % 2 + '0';
    value /= 2;
    i++;
  }
  str[i] = '\0';
  int len = strlen(str);
  for (int j = 0; j < len / 2; j++) {
    char temp = str[j];
    str[j] = str[len - j - 1];
    str[len - j - 1] = temp;
  }
}

void matmul(double td[8], double mat[8][8], double fd[8]) { // 矩阵相乘函数
  int i, j;                                                 // 辅助变量
  double temp = 0;                                          // 辅助变量
  for (i = 0; i < 8; i++) {
    temp = 0;
    for (j = 0; j < 8; j++) {
      temp = temp + td[j] * mat[i][j];
    }
    fd[i] = temp;
  }
}

void dct(double origin[8][8], double dct_r[8][8]) { // DCT变换
  double dct_mat[8][8];                             // 一维DCT变换矩阵
  double td[8];             // 时域（变换前）的数组
  double fd[8];             // 频域（变换后）的数组
  double dct_temp[8 * 8];   // 做一次一维DCT变换后的暂存矩阵
  double result[8 * 8];     // 二维DCT变换结果矩阵
  int i, j;                 // 辅助变量
  for (i = 0; i < 8; i++) { // 生成一维DCT变换矩阵直流部分
    dct_mat[0][i] = 1 / sqrt(2.0) / 2.0;
  }
  for (i = 1; i < 8; i++) { // 生成一维DCT变换矩阵交流部分
    for (j = 1; j <= 8; j++) {
      dct_mat[i][j - 1] = cos(i * pi * (2 * j - 1) / (2 * 8)) / 2.0;
    }
  }
  for (i = 0; i < 8; i++) { // 一次一维DCT变换
    for (j = 0; j < 8; j++) {
      td[j] = (double)(origin[i][j]);
    }
    matmul(td, dct_mat, fd);
    for (j = 0; j < 8; j++) {
      dct_temp[i * 8 + j] = fd[j];
    }
  }
  for (j = 0; j < 8; j++) { // 第二次一维DCT变换
    for (i = 0; i < 8; i++) {
      td[i] = dct_temp[i * 8 + j];
    }
    matmul(td, dct_mat, fd);
    i = 0;
    for (i = 0; i < 8; i++) {
      result[i * 8 + j] = fd[i];
    }
  }
  for (i = 0; i < 8; i++) { // 将DCT变换结果输出到所需数组中
    for (j = 0; j < 8; j++) {
      dct_r[i][j] = result[i * 8 + j];
    }
  }
}

void quant(double dct_r[8][8], int quant_r[8][8]) { // 量化
  int i, j;                                         // 辅助变量
  int Q_matrix[8][8] = {
      {16, 11, 10, 16, 24, 40, 51, 61}, // 量化矩阵
      {12, 12, 14, 19, 26, 58, 60, 55},   {14, 13, 16, 24, 40, 57, 69, 56},
      {14, 17, 22, 29, 51, 87, 80, 62},   {18, 22, 37, 56, 68, 109, 103, 77},
      {24, 35, 55, 64, 81, 104, 113, 92}, {49, 64, 78, 87, 103, 121, 120, 101},
      {72, 92, 95, 98, 112, 100, 103, 99}};
  double temp;              // 辅助变量
  for (i = 0; i < 8; i++) { // 对每一个DCT变换后的结果进行量化
    for (j = 0; j < 8; j++) {
      temp = dct_r[i][j] / Q_matrix[i][j];
      if (dct_r[i][j] > 0) {
        quant_r[i][j] = (int)(temp + 0.5);
      } else if (dct_r[i][j] < 0) {
        quant_r[i][j] = (int)(temp - 0.5);
      } else {
        quant_r[i][j] = (int)(temp);
      }
    }
  }
}

void dc_entro(int *dc_entro_len_p, char *dc_entro_series, int pre_dc_quant_r,
              int dc_quant_r) { // DC熵编码
  char dc_table[12]
               [10] = {
                   "00",       "010",      "011",   "100",    "101",
                   "110",      "1110",     "11110", "111110", "1111110",
                   "11111110", "111111110"}; // DC熵编码符号1（尺寸）对应的表
  int dc_entro_value = 0;                    // DC熵编码的待编码值
  int dc_entro_size = 0;                     // 待编码值应使用的位数
  char dc_entro_val_a[20];                   // 幅值的变长整数码
  int i, j, k;                               // 辅助变量
  int dc_entro_len = 0;                      // 存放编码结果的长度
  int dc_table_len[12]; // dc_table_len与dc_table对应使用，表示各可选码的长度
  int str_a = 0;             // 存放幅值编码结果的长度
  for (i = 0; i < 20; i++) { // 幅值的变长整数码清零
    dc_entro_val_a[i] = 0;
  }
  for (i = 0; i < 12; i++) { // 生成dc_table_len，表示各可选码的长度
    dc_table_len[i] = strlen(dc_table[i]);
  }
  dc_entro_value = dc_quant_r - pre_dc_quant_r; // 计算待编码值
  if (dc_entro_value == 0) // 计算待编码值应使用的位数
  {
    dc_entro_size = 0;
  } else {
    dc_entro_size =
        (int)(log((double)((abs(dc_entro_value)))) / (log((double)2))) + 1;
  }
  strcat(dc_entro_series,
         dc_table
             [dc_entro_size]); // 在DC编码结果字符串后拼接dc_table中的对应字符串
  dc_entro_len = dc_table_len[dc_entro_size]; // DC编码结果的码长存储
  if (dc_entro_value >
      0) // 幅值编码，只分大于零小于零两种情况，等于零时不需拼接码字
  {
    // itoa(dc_entro_value, dc_entro_val_a, 2); // 若幅值大于0，直接转换为字符串
    print_binary(dc_entro_value, dc_entro_val_a);
    strcat(dc_entro_series, dc_entro_val_a);              // 拼接
    dc_entro_len = dc_entro_len + strlen(dc_entro_val_a); // 码长增加
    str_a = strlen(dc_entro_val_a);
    for (i = 0; i < str_a; i++) { // 临时存储字符串的dc_entro_val_a清零
      dc_entro_val_a[i] = 0;
    }
  } else if (dc_entro_value < 0) {
    // itoa(abs(dc_entro_value), dc_entro_val_a,
    //      2); // 若幅值小于0，先算其绝对值对应的字符串
    print_binary(abs(dc_entro_value), dc_entro_val_a);
    for (i = 0; i < strlen(dc_entro_val_a); i++) // 对得到的字符串“取反”
    {
      if (dc_entro_val_a[i] == '0')
        dc_entro_val_a[i] = '1';
      else if (dc_entro_val_a[i] == '1')
        dc_entro_val_a[i] = '0';
    }
    strcat(dc_entro_series, dc_entro_val_a); // 拼接至DC编码结果字符串
    dc_entro_len = dc_entro_len + strlen(dc_entro_val_a); // DC编码码长增加
    str_a = strlen(dc_entro_val_a);
    for (i = 0; i < str_a; i++) { // 临时存储字符串的dc_entro_val_a清零
      dc_entro_val_a[i] = 0;
    }
  }
  (*dc_entro_len_p) = dc_entro_len; // 码长输出
}

void zigzag(int quant_r[8][8], int zigzag_r[8 * 8]) { // zigzag扫描
  int i;                                              // 辅助变量
  int pot_x[8 * 8] = {0, 0, 1, 2, 1, 0, 0, 1, 2, 3, 4, 3, 2, 1, 0, 0, 1,
                      2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5,
                      6, 7, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 7, 6,
                      5, 4, 3, 4, 5, 6, 7, 7, 6, 5, 6, 7, 7}; // 扫描的横坐标值
  int pot_y[8 * 8] = {0, 1, 0, 0, 1, 2, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 4,
                      3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2,
                      1, 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 3, 4,
                      5, 6, 7, 7, 6, 5, 4, 5, 6, 7, 7, 6, 7}; // 扫描的纵坐标值
  for (i = 0; i < 8 * 8; i++)                                 // 扫描过程
  {
    zigzag_r[i] = quant_r[pot_x[i]][pot_y[i]];
  }
}

void act_ac_entro(int *ac_entro_len_one_p, char *ac_entro_series_one,
                  int zero_num, int nonzero_val) { // 一次AC编码过程
  int i, j, k;                                     // 辅助变量
  int non_zero_level = 0;                          // 幅值对应的阶
  char nonzero_val_a[20]; // 存放幅值对应的字符串
  int str_a = 0;          // 存放幅值编码的长度
  char ac_table[16][11][20] = {
      {"1010", "00", "01", "100", "1011", "11010", "1111000", "11111000",
       "1111110110", "1111111110000010", "1111111110000011"},
      {"", "1100", "11011", "1111001", "111110110", "11111110110",
       "1111111110000100", "1111111110000101", "1111111110000110",
       "1111111110000111", "1111111110001000"},
      {"", "11100", "11111001", "1111110111", "111111110100",
       "1111111110001001", "1111111110001010", "1111111110001011",
       "1111111110001100", "1111111110001101", "1111111110001110"},
      {"", "111010", "111110111", "111111110101", "1111111110001111",
       "1111111110010000", "1111111110010001", "1111111110010010",
       "1111111110010011", "1111111110010100", "1111111110010101"},
      {"", "111011", "1111111000", "1111111110010110", "1111111110010111",
       "1111111110011000", "1111111110011001", "1111111110011010",
       "1111111110011011", "1111111110011100", "1111111110011101"},
      {"", "1111010", "11111110111", "1111111110011110", "1111111110011111",
       "1111111110100000", "1111111110100001", "1111111110100010",
       "1111111110100011", "1111111110100100", "1111111110100001"},
      {"", "1111011", "111111110110", "1111111110100110", "1111111110100111",
       "1111111110101000", "1111111110101001", "1111111110101010",
       "1111111110101011", "1111111110101100", "1111111110101101"},
      {"", "11111010", "111111110111", "1111111110101110", "1111111110101111",
       "1111111110110000", "1111111110110001", "1111111110110010",
       "1111111110110011", "1111111110110100", "1111111110110101"},
      {"", "111111000", "111111111000000", "1111111110110110",
       "1111111110110111", "1111111110111000", "1111111110111001",
       "1111111110111010", "1111111110111011", "1111111110111100",
       "1111111110111101"},
      {"", "111111001", "1111111110111110", "1111111110111111",
       "1111111111000000", "1111111111000001", "1111111111000010",
       "1111111111000011", "1111111111000100", "1111111111000101",
       "1111111111000110"},
      {"", "111111010", "1111111111000111", "1111111111001000",
       "1111111111001001", "1111111111001010", "1111111111001011",
       "1111111111001100", "1111111111001101", "1111111111001110",
       "1111111111001111"},
      {"", "1111111001", "1111111111010000", "1111111111010001",
       "1111111111010010", "1111111111010011", "1111111111010100",
       "1111111111010101", "1111111111010110", "1111111111010111",
       "1111111111011000"},
      {"", "1111111010", "1111111111011001", "1111111111011010",
       "1111111111011011", "1111111111011100", "1111111111011101",
       "1111111111011110", "1111111111011111", "1111111111100000",
       "1111111111100001"},
      {"", "11111111000", "1111111111100010", "1111111111100011",
       "1111111111100100", "1111111111100101", "1111111111100110",
       "1111111111100111", "1111111111101000", "1111111111101001",
       "1111111111101010"},
      {"", "1111111111101011", "1111111111101100", "1111111111101101",
       "1111111111101110", "1111111111101111", "1111111111110000",
       "1111111111110001", "1111111111110010", "1111111111110011",
       "1111111111110100"},
      {"11111111001", "1111111111110101", "1111111111110110",
       "1111111111110111", "1111111111111000", "1111111111111001",
       "1111111111111010", "1111111111111011", "1111111111111100",
       "1111111111111101", "1111111111111110"}}; // AC码表
  int ac_table_len[16][11]; // ac_table_len与ac_table对应使用，表示各码字的长度
  int ac_entro_len_one = 0;  // 存放码长
  for (i = 0; i < 20; i++) { // 幅值对应的二进制字符串清零
    nonzero_val_a[i] = 0;
  }
  for (i = 0; i < 16; i++) { // 生成ac_table_len表，表示各码字的长度
    for (j = 0; j < 11; j++) {
      ac_table_len[i][j] = strlen(ac_table[i][j]);
    }
  }
  if (nonzero_val == 0) // 计算幅值对应的阶
  {
    non_zero_level = 0;
  } else {
    non_zero_level =
        (int)(log((double)((abs(nonzero_val)))) / (log((double)2))) + 1;
  }
  strcat(ac_entro_series_one,
         ac_table[zero_num]
                 [non_zero_level]); // 将AC码表中的对应结果拼接至编码字符串后
  ac_entro_len_one = ac_table_len[zero_num][non_zero_level]; // 编码长度增加
  if (nonzero_val >
      0) // 幅值编码，只分大于零小于零两种情况，等于零时不需拼接码字
  {
    // itoa(nonzero_val, nonzero_val_a, 2); // 若幅值大于0，直接转换为字符串
    print_binary(nonzero_val, nonzero_val_a);
    strcat(ac_entro_series_one, nonzero_val_a); // 拼接
    ac_entro_len_one += strlen(nonzero_val_a);  // 码长增加
    str_a = strlen(nonzero_val_a);
    for (i = 0; i < str_a; i++) { // 临时存储字符串的nonzero_val_a清零
      nonzero_val_a[i] = 0;
    }
  } else if (nonzero_val < 0) // 若幅值小于0，先算其绝对值对应的字符串
  {
    // itoa(abs(nonzero_val), nonzero_val_a,
    //      2); // 先计算其绝对值对应的二进制字符串
    print_binary(abs(nonzero_val), nonzero_val_a);
    for (i = 0; i < strlen(nonzero_val_a); i++) // 对得到的字符串“取反”
    {
      if (nonzero_val_a[i] == '0')
        nonzero_val_a[i] = '1';
      else if (nonzero_val_a[i] == '1')
        nonzero_val_a[i] = '0';
    }
    strcat(ac_entro_series_one, nonzero_val_a); // 拼接
    ac_entro_len_one += strlen(nonzero_val_a);  // 码长增加
    str_a = strlen(nonzero_val_a);
    for (i = 0; i < str_a; i++) { // 临时存储字符串的nonzero_val_a清零
      nonzero_val_a[i] = 0;
    }
  }
  (*ac_entro_len_one_p) = ac_entro_len_one; // 码长输出
}

void ac_entro(int *ac_entro_len_p, char *ac_entro_series, int quant_r[8][8]) {
  int zero_num = 0;    // 存放连续0的个数
  int nonzero_val = 0; // 存放非零值
  int ac_entro_len_one =
      0; // 存放一次编码的码长（每有一个非零值或连续的'0'的个数大于等于15，就调用函数进行一次编码）
  int ac_entro_len = 0; // 存放AC编码的总码长（一个block块）
  char ac_entro_series_one[200]; // 存放一次编码的结果
  int i, j;                      // 辅助变量
  int zigzag_r[8 * 8];           // zigzag结果
  int last_nonzero = 0; // 在zigzag结果中最后一个非0值对应的下标
  for (i = 0; i < 200; i++) { // 一次编码结果清零
    ac_entro_series_one[i] = 0;
  }
  zigzag(quant_r, zigzag_r);         // zigzag操作
  for (i = 8 * 8 - 1; i >= 0; i--) { // 寻找最后一个非零值对应的下标
    if (zigzag_r[i] != 0) {
      last_nonzero = i;
      break;
    }
  }
  for (i = 1; i <= last_nonzero;
       i++) // 对所有最后非零值以前的数(含该非零值）的编码过程
  {
    if ((zigzag_r[i] == 0) && (zero_num < 15)) // 记录0的个数
    {
      zero_num++;
    } else // 若遇到非0值或连续16个0，则进行编码
    {
      nonzero_val = zigzag_r[i]; // 存储非零值
      if (nonzero_val ==
          0) { // 当nonzero_val等于0（15个0后接的仍然是0）时，使用扩展符号1（15,0）
        act_ac_entro(&ac_entro_len_one, ac_entro_series_one, 15, 0);
        zero_num = 0; // 对0的个数的计数器归零
      } else { // 当nonzero_val不等于0时，使用零的个数和非零值大小进行编码
        act_ac_entro(&ac_entro_len_one, ac_entro_series_one, zero_num,
                     nonzero_val);
        zero_num = 0; // 对0的个数的计数器归零
      }
      strcat(ac_entro_series, ac_entro_series_one); // 拼接至AC编码结果
      ac_entro_len += ac_entro_len_one;             // AC编码的码长增加
      for (j = 0; j < ac_entro_len_one; j++) { // 对存放一次编码结果的数组归零
        ac_entro_series_one[j] = 0;
      }
      ac_entro_len_one = 0; // 对一次编码码长归零
    }
  }
  if ((last_nonzero < 63) && (last_nonzero >= 0)) { // 添加块结束标识
    act_ac_entro(&ac_entro_len_one, ac_entro_series_one, 0,
                 0);                              // 计算结束标识（EOB）
    strcat(ac_entro_series, ac_entro_series_one); // 拼接结束标识
    ac_entro_len += ac_entro_len_one;             // 总码长增加
  }
  (*ac_entro_len_p) = ac_entro_len; // 总码长数值输出
}

char total_entro_series[5000000]; // 存放DC和AC熵编码后的总结果
char dc_entro_series[1000000];    // 存放一个块的DC编码结果
char ac_entro_series[4000000];    // 存放一个块的DC编码结果
char jpeg_r_series[5000000];      // 存放JPEG编码的最终编码结果

int main() {
  FILE *prev_data;                  // lady.dat的文件指针
  unsigned char temp_origin[65536]; // 存放lady.dat中原始数据的数组
  int dc_entro_len = 0;             // DC编码长度（每块）
  int ac_entro_len = 0;             // AC编码长度（每块）
  int total_len = 0;                // 总编码长度
  int jpeg_len = 0;                 // 总编码结果的长度
  int p[256][256];                  // 在数组中存放原始数据
  int target = 0;                   // 辅助变量
  char target_r = 0;                // 辅助变量
  double block[8][8];               // 存放每一块数据
  double dct_r[8][8];               // 存放DCT结果
  int quant_r[8][8];                // 存放量化结果
  int dc_quant_r = 0;               // DC编码输入，即DCT的直流分量
  int pre_dc_quant_r = 0;           // 存放上一个块中的直流分量
  int i, j, m, n, k, l;             // 辅助变量
  char str_src[100];                // 存放输入文件位置字符串
  char str_tar[100];                // 存放输出文件位置字符串
  unsigned char target_tmp = 0;     // 辅助变量
  int count = 0;                    // 辅助变量
  for (i = 0; i < 5000000; i++) {   // 清0操作
    total_entro_series[i] = 0;
    jpeg_r_series[i] = 0;
  }
  for (i = 0; i < 1000000; i++) {
    dc_entro_series[i] = 0;
  }
  for (i = 0; i < 4000000; i++) {
    ac_entro_series[i] = 0;
  }
  strcpy(str_src, "lady.dat");     // 将文件位置存至变量
  prev_data = fopen(str_src, "r"); // 打开文件
  if (prev_data == NULL)           // 检测文件是否未正常打开
  {
    printf("prev file loading error! --WPD\n");
    getchar();
    exit(0);
  } else {
    fread(temp_origin, 65536, 1, prev_data); // 读入数据
    for (i = 0; i < 256; i++) { // 整理数据，使其成为8×8的数组
      for (j = 0; j < 256; j++) {
        p[i][j] = (int)temp_origin[i * 256 + j];
      }
    }
    fclose(prev_data);
    for (m = 0; m < (256 / 8); m++) { // 分块进行循环
      for (n = 0; n < (256 / 8); n++) {
        for (i = 0; i < 8; i++) { // 给每个块赋值
          for (j = 0; j < 8; j++) {
            block[i][j] = p[m * 8 + i][n * 8 + j] - 128;
          }
        }
        dct(block, dct_r);     // DCT变换
        quant(dct_r, quant_r); // 量化
        dc_quant_r = quant_r[0][0]; // 直流分量赋给DC编码的输入变量
        if ((m == 0) &&
            (n ==
             0)) { // 若此前无直流分量值，设为128，又因为此前已做过减128的处理，故此处变为赋0操作
          pre_dc_quant_r = 0;
        }
        dc_entro(&dc_entro_len, dc_entro_series, pre_dc_quant_r,
                 dc_quant_r);                              // DC编码
        ac_entro(&ac_entro_len, ac_entro_series, quant_r); // AC编码
        total_len += dc_entro_len + ac_entro_len; // 总长度为AC与DC之和
        strcat(total_entro_series, dc_entro_series); // 总字符串中拼接DC部分
        strcat(total_entro_series, ac_entro_series); // 总字符串中拼接AC部分
        for (k = 0; k < dc_entro_len; k++) { // 对DC/AC字符串及其对应长度的清零
          dc_entro_series[k] = 0;
        }
        for (k = 0; k < ac_entro_len; k++) {
          ac_entro_series[k] = 0;
        }
        dc_entro_len = 0;
        ac_entro_len = 0;
        pre_dc_quant_r = dc_quant_r; // 给下一次循环的DC分量赋值
      }
    }
  }

  jpeg_len = 0; // 最终编码长度清0
  count = 0;    // 计数器清0
  for (k = 0; k < total_len;
       k++) { // 当编码结果中存在连续的8个'1'时，插入8个'0'，生成最终编码结果
    jpeg_r_series[jpeg_len] =
        total_entro_series[k]; // 将总编码结果赋给最终编码结果
    jpeg_len++;                // 最终编码结果的计数加1
    if (total_entro_series[k] == '0') { // 计数过程中遇到'0'时，计数器归零
      count = 0;
    } else if (total_entro_series[k] == '1') { // 当遇到连续的'1'时，计数器加1
      count++;
    }
    if ((count >= 8) &&
        (jpeg_len % 8 == 0)) { // 当计数器加至8时，在最终编码结果中插入8个'0'
      for (l = 0; l < 8; l++) {
        jpeg_r_series[jpeg_len++] = '0';
      }
      count = 0; // 计数器归零
    }
  }

  // save as text
  for (k = 0; k < jpeg_len; k++) {
    text_data << jpeg_r_series[k];
  }
  text_data.close();

  for (k = 0; k < jpeg_len / 8; k++) // 每8个字符变为一个字节的8位
  {
    target = 0;             // 辅助变量清零
    for (l = 0; l < 8; l++) // 求所需的字节
    {
      target_tmp = (jpeg_r_series[k * 8 + l] - '0');
      target += (target_tmp << (7 - l));
    }
    target_r = (char)target;
    result_data << target_r; // 存入编码结果文件中
  }
  if (jpeg_len !=
      (jpeg_len / 8 *
       8)) // 当最终编码长度非8的整数倍时，将剩余部分单独转换为一个字节
  {
    target = 0;                                         // 辅助变量清零
    for (l = 0; l < jpeg_len - (jpeg_len / 8 * 8); l++) // 求所需的字节
    {
      target_tmp = (jpeg_r_series[(jpeg_len / 8 * 8) + l] - '0');
      target += (target_tmp << (7 - l));
    }
    target_r = (char)target;
    result_data << target_r; // 存入编码结果文件中
  }
}