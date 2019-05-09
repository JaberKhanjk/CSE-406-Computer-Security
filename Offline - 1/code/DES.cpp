/***from dust i have come, dust i will be***/

#include<bits/stdc++.h>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n")
#define nl printf("\n")
#define N 64
#define N2 56

#define pb push_back

using namespace std;

//===================================================================
// variables
//===================================================================
bitset<56> key56;
bitset<N> bset;

string key, plain_text, ciphered_text;
vector<string> text_chunks;

int PI[N] = {58, 50, 42, 34, 26, 18, 10, 2,
             60, 52, 44, 36, 28, 20, 12, 4,
             62, 54, 46, 38, 30, 22, 14, 6,
             64, 56, 48, 40, 32, 24, 16, 8,
             57, 49, 41, 33, 25, 17, 9, 1,
             59, 51, 43, 35, 27, 19, 11, 3,
             61, 53, 45, 37, 29, 21, 13, 5,
             63, 55, 47, 39, 31, 23, 15, 7};

int CP_1[N2] = {57, 49, 41, 33, 25, 17, 9,
                1, 58, 50, 42, 34, 26, 18,
                10, 2, 59, 51, 43, 35, 27,
                19, 11, 3, 60, 52, 44, 36,
                63, 55, 47, 39, 31, 23, 15,
                7, 62, 54, 46, 38, 30, 22,
                14, 6, 61, 53, 45, 37, 29,
                21, 13, 5, 28, 20, 12, 4};

int CP_2[48] = {14, 17, 11, 24, 1, 5, 3, 28,
                15, 6, 21, 10, 23, 19, 12, 4,
                26, 8, 16, 7, 27, 20, 13, 2,
                41, 52, 31, 37, 47, 55, 30, 40,
                51, 45, 33, 48, 44, 49, 39, 56,
                34, 53, 46, 42, 50, 36, 29, 32};

int E[48] = {32, 1, 2, 3, 4, 5,
             4, 5, 6, 7, 8, 9,
             8, 9, 10, 11, 12, 13,
             12, 13, 14, 15, 16, 17,
             16, 17, 18, 19, 20, 21,
             20, 21, 22, 23, 24, 25,
             24, 25, 26, 27, 28, 29,
             28, 29, 30, 31, 32, 1};

int PI_2[32] = {35, 38, 46, 6, 43, 40, 14, 45,
                33, 19, 26, 15, 23, 8, 22, 10,
                12, 11, 5, 25, 27, 21, 16, 31,
                28, 32, 34, 24, 9, 37, 2, 1};

int PI_1[N] = {40, 8, 48, 16, 56, 24, 64, 32,
               39, 7, 47, 15, 55, 23, 63, 31,
               38, 6, 46, 14, 54, 22, 62, 30,
               37, 5, 45, 13, 53, 21, 61, 29,
               36, 4, 44, 12, 52, 20, 60, 28,
               35, 3, 43, 11, 51, 19, 59, 27,
               34, 2, 42, 10, 50, 18, 58, 26,
               33, 1, 41, 9, 49, 17, 57, 25};

int P[32] = {16, 7, 20, 21, 29, 12, 28, 17,
           1, 15, 23, 26, 5, 18, 31, 10,
           2, 8, 24, 14, 32, 27, 3, 9,
           19, 13, 30, 6, 22, 11, 4, 25};

int SHIFT[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

//===================================================================
// helper functions
//===================================================================
void make64Bits() {
  int req = 8 - (plain_text.length() % 8);
  while (req--)
    plain_text.pb('0');
}

void groupPlainText() {
  int n = plain_text.length();
  string s = "";

  for (int i = 0; i < n; i++) {
    s.pb(plain_text[i]);

    if ((i + 1) % 8 == 0)
      text_chunks.pb(s), s = "";
  }
}

void strToBitset(string s) {
  bset.reset();
  int n = s.length(), k, p = 0;

  for (int i = n - 1; i >= 0; i--) {
    k = int(s[i]);

    while (k) {
      if (k % 2)
        bset[p] = 1;

      p++, k /= 2;
    }

    while (p % 8)
      p++;
  }
}

void make56BitKey() {
  strToBitset(key);

  for (int i = 0; i < N2; i++) {
    key56[i] = bset[CP_1[i] - 1];
  }
}

//===================================================================
// encryption functions
//===================================================================
void encrypt(string s) {
  bitset<N> transposed_data;
  strToBitset(s);

  //transpose data
  for (int i = 0; i < N; i++)
    transposed_data[i] = bset[PI[i] - 1];

  //L, R for the first iteration
  bitset<28> kL, kR;
  bitset<56> key56_2;
  bitset<32> oldL, oldR, newL, newR;

  for (int i = 0; i < 32; i++)
    oldR[i] = transposed_data[i], oldL[i] = transposed_data[i + 32];

  for (int i = 0; i < 56; i++)
    key56_2[i] = key56[i];

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 32; j++)
      newL[j] = oldR[j];

    //---------------------------------------------------------------
    //keys at each round
    //divide the 56-bit key into two parts
    for (int j = 0; j < 28; j++)
      kR[j] = key56_2[j], kL[j] = key56_2[j + 28];

    //shift the two parts(each of 28bits)
    kR <<= SHIFT[i];
    kL <<= SHIFT[i];

    //using the 28bits make 56bit again
    for (int j = 0; j < 28; j++)
      key56_2[j] = kR[j];

    for (int j = 28; j < 56; j++)
      key56_2[j] = kL[j - 28];

    //transpose key for the current round
    bitset<48> current_round_key;
    for (int j = 0; j < 48; j++)
      current_round_key[j] = key56_2[CP_2[j] - 1];
    //---------------------------------------------------------------

    //---------------------------------------------------------------
    //function at each iteration
    bitset<48> e;
    for (int j = 0; j < 48; j++)
      e[j] = oldR[E[j] - 1];

    //xor of key and e
    for (int j = 0; j < 48; j++)
      e[j] = e[j] ^ current_round_key[j];

    for (int j = 0; j < 32; j++)
      newR[j] = e[PI_2[j] - 1] ^ oldL[j];
    //---------------------------------------------------------------

    for (int j = 0; j < 32; j++)
      oldL[j] = newL[j], oldR[j] = newL[j];
  }

  bitset<N> res;
  for (int j = 0; j < 32; j++)
    res[j] = oldR[j];

  for (int j = 32; j < N; j++)
    res[j] = oldL[j - 28];

  //transpose
  bitset<N> ret;
  for (int i = 0; i < N; i++)
    ret[i] = res[PI_1[i] - 1];

  int p = 0, sum = 0;
  string str = "";

  for (int i = 0; i < N; i += 8) {
    sum = 0, p = 1;
    for (int j = i; j < i + 8; j++) {
      if (ret[j])
        sum += p;

      p *= 2;
    }

    str.pb(char(sum));
  }

  reverse(str.begin(), str.end());
  ciphered_text += str;
}

int main() {
  freopen("in.txt", "r", stdin);

  int i, j, k;
  int n, m;

  cin >> key;
  getline(cin, plain_text);
  getline(cin, plain_text);

  make64Bits();
  make56BitKey();
  groupPlainText();

  ciphered_text = "";
  for (string s : text_chunks)
    encrypt(s);

  cout << ciphered_text;

  return 0;
}

// http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm