/***from dust i have come, dust i will be***/

#include<bits/stdc++.h>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n")
#define nl printf("\n")
#define N 64
#define N2 56
#define inf 1e8

#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d",&n,&m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d",&n,&m)

#define pf(n) printf("%d",n)
#define pff(n, m) printf("%d %d",n,m)
#define pffl(n, m) printf("%I64d %I64d",n,m)
#define pfl(n) printf("%I64d",n)
#define pfs(s) printf("%s",s)

#define pb push_back
#define pp pair<int, int>

using namespace std;

//===================================================================
// variables
//===================================================================
ll key56;
string key, plain_text, ciphered_text;
vector<string> text_chunks;
vector<ll> ciphered_chunks;

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

int SHIFT[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

//===================================================================
// helper functions
//===================================================================
void make64Bits() {
  int req = 8 - (plain_text.length() % 8);
  while (req--)
    plain_text.pb('#');
}

void groupPlainText() {
  int n = plain_text.length();
  string s = "";

  for (int i = 0; i < n; i++) {
    if ((i + 1) % 8 == 0)
      text_chunks.pb(s), s = "";
    else
      s.pb(plain_text[i]);
  }
}

void groupCipheredText(ll x) {
  string str = "";

  int p = 1, k = 0;
  for (int i = 1; i <= N; i++) {
    if(x & (1 << (i-1)))
      k += p;

    p *= 2;
    if(i % 8 == 0)
    {
      str.pb(char(k));
      p=1, k=0;
    }
  }

  reverse(str.begin(), str.end());
  ciphered_text += str;
}

ll strToLL(string s) {
  ll x = 0, p = 1;
  int n = s.length(), k;

  for (int i = n - 1; i >= 0; i--) {
    k = int(s[i]);

    //convert k into 8-bit binary and add to 'x'
    for (int j = 0; j < n; j++) {
      //the bit is 1
      if (k & (1 << j))
        x += p;

      p *= 2;
    }
  }

  return x;
}

void make56BitKey() {
  ll key64 = strToLL(key), p = 1;

  key56 = 0;
  for (int i = 0; i < N2; i++) {
    if (key64 & (1 << (CP_1[i] - 1)))
      key56 += p;

    p *= 2;
  }
}

//creates mask to extract from ath to bth bit
ll createMask(ll a, ll b) {
  ll ret = 0;
  for (ll i = a; i <= b; i++)
    ret |= 1 << i;

  return ret;
}

//===================================================================
// encryption functions
//===================================================================
void encrypt(string s) {
  ll original_data = strToLL(s), transposed_data = 0, p = 1;

  //transpose data
  for (int i = 0; i < N; i++) {
    if (original_data << (PI[i] - 1))
      transposed_data += p;

    p *= 2;
  }

  //L, R for the first iteration
  ll kL, kR;
  ll backup_key56 = key56, key56_2, stage_key, e;
  ll oldL, oldR, newL, newR;

  oldL = createMask(33, 64) & transposed_data;
  oldR = createMask(1, 32) & transposed_data;

  for (int i = 0; i < 16; i++) {
    newL = oldR;

    //divide the 56-bit key into two parts
    kL = key56 & createMask(29, 56);
    kR = key56 & createMask(1, 28);

    //shift the two parts(each of 28bits)
    //as we have 64 bits in the variable, we can't just trivially shift
    //shifting x bits means x bits from MSB will be left out
    kL = (kL & createMask(1, 28 - SHIFT[i])) << SHIFT[i];
    kR = (kR & createMask(1, 28 - SHIFT[i])) << SHIFT[i];

    key56_2 = (kL << 28) | kR;

    //transpose key for the current round
    stage_key = 0, p = 1;
    for (int j = 0; j < 48; j++) {
      if (key56_2 << (CP_2[j] - 1))
        stage_key += p;

      p *= 2;
    }

    //function at each iteration
    p = 1, e = 0;
    for (int j = 0; j < 48; j++) {
      if (oldR << (E[j] - 1))
        e += p;

      p *= 2;
    }

    ll temp = e ^stage_key;

    //make 32-bits
    p = 1, newR = 0;
    for (int j = 0; j < 32; j++) {
      if (temp << (PI_2[j] - 1))
        e += p;

      p *= 2;
    }

    //xor with old L
    newR = newR ^ oldL;

    oldL = newL;
    oldR = newR;
  }

  key56 = backup_key56;

  //swap the left-most 32bits and right-most 32bits
  ll res = oldL | (oldR << 32);

  //use PI_1 to transpose again
  ll ret = 0;

  p = 1;
  for (int i = 0; i < N; i++) {
    if (res << (PI_1[i] - 1))
      ret += p;

    p *= 2;
  }

  ciphered_chunks.pb(ret);
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

  for (string s : text_chunks)
    encrypt(s);

  ciphered_text = "";
  for (ll e : ciphered_chunks)
    groupCipheredText(e);

  cout << ciphered_text;

  return 0;
}
