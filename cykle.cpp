#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj¹ca stos

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

// Destruktor - zwalnia tablicê dynamiczn¹
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

// Funkcja bada cyklicznoœæ grafu
//-------------------------------
bool isCyclic(int n, slistEl ** G)
{
  stack S;                      // Stos
  bool * visited;               // Tablica odwiedzin
  slistEl * p;                  // WskaŸnik elementu listy
  int w,v,z,i;                  // Zmienne pomocnicze

  visited = new bool[n];        // Tworzymy tablicê odwiedzin

  for(i = 0; i < n; i++) visited[i] = false;  // i zerujemy j¹

  S.push(0); S.push(-1);        // Na stos wierzcho³ek startowy i -1
  visited[0] = true;            // Oznaczamy wierzcho³ek jako odwiedzony
  while(!S.empty())             // W pêtli przechodzimy graf za pomoc¹ DFS
  {
    w = S.top(); S.pop();       // Pobieramy ze stosu wierzcho³ek z którego przyszliœmy
    v = S.top(); S.pop();       // oraz wierzcho³ek bie¿¹cy
    for(p = G[v]; p; p = p->next) // Przegl¹damy jego listê s¹siadów
    {
      z = p->v;                 // Numer s¹siada
      if(!visited[z])
      {
        S.push(z); S.push(v);   // S¹siada nieodwiedzonego umieszczamy na stosie
        visited[z] = true;      // Oznaczamy go jako odwiedzonego
      }
      else if(z != w)           // Jeœli s¹siad jest odwiedzony i nie jest wierzcho³kiem
      {                         // z którego przyszliœmy, to odkryliœmy cykl
        delete [] visited;      // Usuwamy zmienne pomocnicze
        return true;            // Koñczymy z wynikiem true
      }
    }
  }
  delete [] visited;            // W grafie nie ma cykli.
  return false;                 // Koñczymy z wynikiem false
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int n,m,i,v1,v2;
  slistEl * p,* r,** A;

  cin >> n >> m;         // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n]; // Tworzymy tablicê list s¹siedztwa

  // Tablice wype³niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz¹tek listy A[v1]
    A[v1] = p;
    p = new slistEl;    // KrawêdŸ w drug¹ stronê, bo graf jest nieskierowany
    p->v = v1;
    p->next = A[v2];
    A[v2] = p;
  }

  if(isCyclic(n,A)) cout << "CYCLIC GRAPH";
  else              cout << "ACYCLIC GRAPH";

  cout << endl;

  // Usuwamy tablicê list s¹siedztwa

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