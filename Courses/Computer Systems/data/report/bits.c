/*
 * CS:APP Data Lab
 * Yunqin Zhu 2022/03/29
 */
int bitXor(int x, int y) { return ~(x & y) & ~(~x & ~y); }

int tmin(void) { return 1 << 31; }

int isTmax(int x) {
  x = x + 1;
  return !(!x | (x + x));
}

int allOddBits(int x) {
  x = x & x >> 16;
  return !(~(x & x >> 8) & 170);
}

int negate(int x) { return ~x + 1; }

int isAsciiDigit(int x) { return (x + ~57 & ~(x + ~47)) >> 31 & 1; }

int conditional(int x, int y, int z) {
  x = !x + ~0;
  return (x & y) | (~x & z);
}

int isLessOrEqual(int x, int y) { return (x + ~((x ^ y) >> 31 | y)) >> 31 & 1; }

int logicalNeg(int x) { return ((x | (~x + 1)) >> 31) + 1; }

int howManyBits(int x) {
  int sum, tmp;
  x = x >> 31 ^ x;
  sum = !!(x >> 16) << 4, x = x >> sum;
  tmp = !!(x >> 8) << 3, sum = sum + tmp, x = x >> tmp;
  tmp = !!(x >> 4) << 2, sum = sum + tmp, x = x >> tmp;
  tmp = !!(x >> 2) << 1, sum = sum + tmp, x = x >> tmp;
  tmp = x >> 1, sum = sum + tmp, x = x >> tmp;
  return sum + x + 1;
}

unsigned floatScale2(unsigned uf) {
  int s = uf & 0x80000000;
  int e = uf & 0x7F800000;
  int m = uf & 0x007FFFFF;
  if (!e)
    return s | m << 1;
  if (e == 0x7F000000)
    m = 0;
  if (e != 0x7F800000)
    e += 0x00800000;
  return s | e | m;
}

int floatFloat2Int(unsigned uf) {
  int s = uf & 0x80000000;
  int e = (uf >> 23) & 0xFF;
  int m = uf & 0x007FFFFF;
  if (e < 127)
    return 0;
  if (e > 157)
    return 0x80000000;
  return (s | 0x40000000 | m << 7) >> 157 - e;
}

unsigned floatPower2(int x) {
  if (x > 127)
    return 0x7F800000;
  if (x >= -126)
    return x + 127 << 23;
  if (x >= -149)
    return 1 << 149 + x;
  return 0;
}
