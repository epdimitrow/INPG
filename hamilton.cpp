
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

int m,n;                        // Liczba krawêdzi i wierzcho³ków
slistEl **graf;                 // Tablica list s¹siedztwa
int *S;                         // Tablica-stos
int sptr;                       // WskaŸnik stosu
bool *visited;                  // Tablica odwiedzin

// Rekurencyjna procedura wyznaczaj¹ca œcie¿ki i cykle Hamiltona
// v - wierzcho³ek bie¿¹cy
//--------------------------------------------------------------
void DFSHamilton(int v)
{
  int i;
  bool test;
  slistEl *p;

  S[sptr++] = v;                // Wierzcho³ek v na stos
  if(sptr < n)                  // Jest œcie¿ka Hamiltona?
  {
    visited[v] = true;          // Nie ma, odwiedzamy v
    for(p = graf[v]; p; p = p->next) // Przegl¹damy s¹siadów v
      if(!visited[p->v]) DFSHamilton(p->v); // Wywo³anie rekurencyjne
    visited[v] = false;         // Wycofujemy siê z v
  }
  else                          // Jest œcie¿ka Hamiltona
  {
    test = false;               // Zak³adamy brak cyklu
    for(p = graf[v]; p; p = p->next) // Przegl¹damy s¹siadów
      if(!(p->v))               // Jeœli s¹siadem jest wierzcho³ek 0,
      {
        test = true;            // to mamy cykl
        break;
      }

    if(test) cout << "Hamiltonian Cycle :";
    else     cout << "Hamiltonian Path  :";

    for(i = 0; i < sptr; i++)   // Wypisujemy œcie¿kê Hamiltona
      cout << setw(3) << S[i];
    if(test) cout << setw(3) << 0; // Dla cyklu dopisujemy wierzcho³ek startowy
    cout << endl;
  }
  sptr--;                       // Wierzcho³ek v usuwamy ze stosu
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int i,v1,v2;
  slistEl *p,*r;

  cin >> n >> m;                // Czytamy liczbê wierzcho³ków i krawêdzi

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

  // Odczytujemy definicje krawêdzi grafu

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

  // Wyœwietlamy œcie¿ki i cykle Hamiltona

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