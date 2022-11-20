#include <iostream>
using namespace std;

namespace lab0l {
int16_t a, b, c;

int main() {
  for (int i = 0; i < 16; i++)
    if (b & 1 << i) c += a << i;
  return 0;
}

}  // namespace lab0l

namespace lab0p {
int16_t a, b, c;

int main() {
  if (b & 1 << 0) c += a << 0;
  if (b & 1 << 1) c += a << 1;
  if (b & 1 << 2) c += a << 2;
  if (b & 1 << 3) c += a << 3;
  if (b & 1 << 4) c += a << 4;
  if (b & 1 << 5) c += a << 5;
  if (b & 1 << 6) c += a << 6;
  if (b & 1 << 7) c += a << 7;
  if (b & 1 << 8) c += a << 8;
  if (b & 1 << 9) c += a << 9;
  if (b & 1 << 10) c += a << 10;
  if (b & 1 << 11) c += a << 11;
  if (b & 1 << 12) c += a << 12;
  if (b & 1 << 13) c += a << 13;
  if (b & 1 << 14) c += a << 14;
  if (b & 1 << 15) c += a << 15;
  return 0;
}

}  // namespace lab0p

namespace fib {
uint16_t n, f;

int main() {
  f = n <= 1 ? 1 : 2;
  uint16_t g = 1, h = 1;
  while (n-- > 2) {
    uint16_t temp = f;
    f = (f + 2 * h) & 1023;
    h = g;
    g = temp;
  }
  return 0;
}

}  // namespace fib

namespace fib_opt {
uint16_t n, f;

const uint16_t data[148] = {
    1,   1,    2,   4,   6,   10,  18,   30,  50,  86,  146, 246, 418, 710,
    178, 1014, 386, 742, 722, 470, 930,  326, 242, 54,  706, 166, 274, 662,
    994, 518,  818, 758, 770, 358, 850,  342, 34,  710, 370, 438, 834, 550,
    402, 22,   98,  902, 946, 118, 898,  742, 978, 726, 162, 70,  498, 822,
    962, 934,  530, 406, 226, 262, 50,   502, 2,   102, 82,  86,  290, 454,
    626, 182,  66,  294, 658, 790, 354,  646, 178, 886, 130, 486, 210, 470,
    418, 838,  754, 566, 194, 678, 786,  150, 482, 6,   306, 246, 258, 870,
    338, 854,  546, 198, 882, 950, 322,  38,  914, 534, 610, 390, 434, 630,
    386, 230,  466, 214, 674, 582, 1010, 310, 450, 422, 18,  918, 738, 774,
    562, 1014, 514, 614, 594, 598, 802,  966, 114, 694, 578, 806, 146, 278,
    866, 134,  690, 374, 642, 998, 722,  982};
int main() {
  f = n < 20 ? data[n] : data[(n - 20 & 127) + 20];
  return 0;
}

}  // namespace fib_opt

namespace rec {
uint16_t r0;

uint16_t count = 5;
void sub() {
  r0++;
  if (--count) {
    sub();
  } else
    return;
}
int main() {
  r0 = 0;
  sub();
  return 0;
}
}  // namespace rec

namespace mod {
uint16_t n;

uint16_t q;
void div_8() {
  q = 0;
  for (int i = 3; i < 16; i++)
    if (n & (1 << i)) q += 1 << (i - 3);
  return;
}
int main() {
  n = 288;
  do {
    div_8();
  } while ((n = q + (n & 7)) > 7);
  if (n == 7) n -= 7;
  return 0;
}
}  // namespace mod

namespace prime {
uint16_t r0, r1;

uint16_t mul(uint16_t a, uint16_t b) {
  uint16_t c = 0;
  for (int i = 0; i < 16; i++)
    if (b & 1 << i) c += a << i;
  return c;
}
uint16_t mod(uint16_t n, uint16_t q) {
  int16_t w = 15;
  uint16_t r = 0;
  while (!(n & 1 << w)) w--;
  while (w >= 0) {
    r <<= 1;
    if (n & 1 << w) r += 1;
    if (r >= q) r -= q;
    w--;
  }
  return r;
}
uint16_t judge(uint16_t r0) {
  for (uint16_t i = 2; mul(i, i) <= r0; i++)
    if (mod(r0, i) == 0) return r1 = 0;
  return r1 = 1;
}
int main() {
  r1 = judge(r0);
  return 0;
}
}  // namespace prime

int main() {
  prime::r0 = 0;
  while (prime::r0 < 100) {
    prime::r0++;
    prime::main();
    if (prime::r1) {
      cout << prime::r0 << endl;
    }
  }
  return 0;
}