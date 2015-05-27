#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj�ca stos

  public:
    stack();       // konstruktor
    ~stack();      // destruktor
    bool empty(void);
    int  top(void);
    void push(int v);
    void pop(void);
};

//---------------------
// Metody obiektu stack
//---------------------

// Konstruktor
//------------
stack::stack()
{
  S = NULL;
}

// Destruktor - zwalnia tablic� dynamiczn�
//----------------------------------------
stack::~stack()
{
  while(S) pop();
}

// Sprawdza, czy stos jest pusty
//------------------------------
bool stack::empty(void)
{
  return !S;
}

// Zwraca szczyt stosu
//--------------------
int stack::top(void)
{
  return S->v;
}

// Zapisuje na stos
//-----------------
void stack::push(int v)
{
  slistEl * e = new slistEl;
  e->v    = v;
  e->next = S;
  S = e;
}

// Usuwa ze stosu
//---------------
void stack::pop(void)
{
  if(S)
  {
    slistEl * e = S;
    S = S->next;
    delete e;
  }
}

// Funkcja bada cykliczno�� grafu
//-------------------------------
bool isCyclic(int n, slistEl ** G)
{
  stack S;                      // Stos
  bool * visited;               // Tablica odwiedzin
  slistEl * p;                  // Wska�nik elementu listy
  int w,v,z,i;                  // Zmienne pomocnicze

  visited = new bool[n];        // Tworzymy tablic� odwiedzin

  for(i = 0; i < n; i++) visited[i] = false;  // i zerujemy j�

  S.push(0); S.push(-1);        // Na stos wierzcho�ek startowy i -1
  visited[0] = true;            // Oznaczamy wierzcho�ek jako odwiedzony
  while(!S.empty())             // W p�tli przechodzimy graf za pomoc� DFS
  {
    w = S.top(); S.pop();       // Pobieramy ze stosu wierzcho�ek z kt�rego przyszli�my
    v = S.top(); S.pop();       // oraz wierzcho�ek bie��cy
    for(p = G[v]; p; p = p->next) // Przegl�damy jego list� s�siad�w
    {
      z = p->v;                 // Numer s�siada
      if(!visited[z])
      {
        S.push(z); S.push(v);   // S�siada nieodwiedzonego umieszczamy na stosie
        visited[z] = true;      // Oznaczamy go jako odwiedzonego
      }
      else if(z != w)           // Je�li s�siad jest odwiedzony i nie jest wierzcho�kiem
      {                         // z kt�rego przyszli�my, to odkryli�my cykl
        delete [] visited;      // Usuwamy zmienne pomocnicze
        return true;            // Ko�czymy z wynikiem true
      }
    }
  }
  delete [] visited;            // W grafie nie ma cykli.
  return false;                 // Ko�czymy z wynikiem false
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int n,m,i,v1,v2;
  slistEl * p,* r,** A;

  cin >> n >> m;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n]; // Tworzymy tablic� list s�siedztwa

  // Tablice wype�niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
    A[v1] = p;
    p = new slistEl;    // Kraw�d� w drug� stron�, bo graf jest nieskierowany
    p->v = v1;
    p->next = A[v2];
    A[v2] = p;
  }

  if(isCyclic(n,A)) cout << "CYCLIC GRAPH";
  else              cout << "ACYCLIC GRAPH";

  cout << endl;

  // Usuwamy tablic� list s�siedztwa

  for(i = 0; i < n; i++)
  {
    p = A[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete [] A;

  return 0;
} 