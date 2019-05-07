/***from dust i have come, dust i will be***/

#include<bits/stdc++.h>

typedef long long int ll;
typedef unsigned long long int ull;

#define dbg printf("in\n")
#define nl printf("\n")
#define N 1010
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
string key, plain_text;
vector<string> text_chunks;
int PI[64] = {58, 50, 42, 34, 26, 18, 10, 2,
              60, 52, 44, 36, 28, 20, 12, 4,
              62, 54, 46, 38, 30, 22, 14, 6,
              64, 56, 48, 40, 32, 24, 16, 8,
              57, 49, 41, 33, 25, 17, 9, 1,
              59, 51, 43, 35, 27, 19, 11, 3,
              61, 53, 45, 37, 29, 21, 13, 5,
              63, 55, 47, 39, 31, 23, 15, 7};

//===================================================================
// helper functions
//===================================================================
void make64Bits() {
  int req = plain_text.length() % 8;
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

ll strToLL(string s) {
  ll x = 0, p = 1;
  int n = s.length(), k;

  for (int i = n - 1; i >= 0; i--) {
    k = int(s[i]);

    //convert k into 8-bit binary and add to 'x'
    for(int j = 0; j < n; j++)
    {
      //the bit is 1
      if(k & (1 << j))
        x += p;

      p *= 2;
    }
  }

  return x;
}


//===================================================================
// encryption functions
//===================================================================
void encrypt(string s) {
  ll x = strToLL(s);
}

int main() {
  freopen("in.txt", "r", stdin);

  int i, j, k;
  int n, m;

  /*cin >> key >> plain_text;

  make64Bits();
  groupPlainText();

  for (string s : text_chunks)
    encrypt(s);*/

  k = 18;
  for(i=8;i>0;i--){
    if((k & (1<<(i-1))))
      cout<<1;
    else
      pf(0);
  }

  return 0;
}
