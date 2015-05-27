
#include <iostream>
#include <iomanip>

using namespace std;

// Typy danych

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int m,n;                        // Liczba kraw�dzi i wierzcho�k�w
slistEl **graf;                 // Tablica list s�siedztwa
int *S;                         // Tablica-stos
int sptr;                       // Wska�nik stosu
bool *visited;                  // Tablica odwiedzin

// Rekurencyjna procedura wyznaczaj�ca �cie�ki i cykle Hamiltona
// v - wierzcho�ek bie��cy
//--------------------------------------------------------------
void DFSHamilton(int v)
{
  int i;
  bool test;
  slistEl *p;

  S[sptr++] = v;                // Wierzcho�ek v na stos
  if(sptr < n)                  // Jest �cie�ka Hamiltona?
  {
    visited[v] = true;          // Nie ma, odwiedzamy v
    for(p = graf[v]; p; p = p->next) // Przegl�damy s�siad�w v
      if(!visited[p->v]) DFSHamilton(p->v); // Wywo�anie rekurencyjne
    visited[v] = false;         // Wycofujemy si� z v
  }
  else                          // Jest �cie�ka Hamiltona
  {
    test = false;               // Zak�adamy brak cyklu
    for(p = graf[v]; p; p = p->next) // Przegl�damy s�siad�w
      if(!(p->v))               // Je�li s�siadem jest wierzcho�ek 0,
      {
        test = true;            // to mamy cykl
        break;
      }

    if(test) cout << "Hamiltonian Cycle :";
    else     cout << "Hamiltonian Path  :";

    for(i = 0; i < sptr; i++)   // Wypisujemy �cie�k� Hamiltona
      cout << setw(3) << S[i];
    if(test) cout << setw(3) << 0; // Dla cyklu dopisujemy wierzcho�ek startowy
    cout << endl;
  }
  sptr--;                       // Wierzcho�ek v usuwamy ze stosu
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int i,v1,v2;
  slistEl *p,*r;

  cin >> n >> m;                // Czytamy liczb� wierzcho�k�w i kraw�dzi

  // Tworzymy tablice dynamiczne

  graf    = new slistEl * [n];
  visited = new bool [n];
  for(i = 0; i < n; i++)
  {
    graf[i]    = NULL;
    visited[i] = false;
  }
  S = new int [n];
  sptr = 0;

  // Odczytujemy definicje kraw�dzi grafu

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;
    p = new slistEl;
    p->v = v2;
    p->next = graf[v1];
    graf[v1] = p;
    p = new slistEl;
    p->v = v1;
    p->next = graf[v2];
    graf[v2] = p;
  }

  cout << endl;

  // Wy�wietlamy �cie�ki i cykle Hamiltona

  DFSHamilton(0);

  // Usuwamy zmienne dynamiczne

  delete [] visited;
  delete [] S;

  for(i = 0; i < n; i++)
  {
    p = graf[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete [] graf;

  return 0;
} 