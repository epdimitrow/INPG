
#include <iostream>

using namespace std;

const int MAX_N = 100; // maksymalna iloœæ wierzcho³ków w grafie
const int INF = 2147483647;

struct TNode
{
  int node;            // numer wierzcho³ka
  int weight;          // waga krawêdzi
  struct TNode * next; // nastêpny element listy
};

main()
{
  int i,j,u,n,m,x,y,z,v0;
  int d[MAX_N+1],p[MAX_N+1];
  bool QS[MAX_N+1];
  struct TNode *L[MAX_N+1],*pw;
  
// Inicjujemy struktury danych

  for(i = 1; i <= MAX_N; i++)
  {
    d[i]  = INF;    // koszty dojœcia
    p[i]  = 0;      // poprzednik na œcie¿ce
    QS[i] = false; // przynale¿noœæ do Q (false) lub S (true)
    L[i]  = NULL;   // lista s¹siedztwa
  }
  n = 0;

// Odczytujemy dane wejœciowe

  cin >> v0; // odczytujemy numer wierzcho³ka startowego
  cin >> m;  // odczytujemy iloœæ krawêdzi
  for(i = 1; i <= m; i++)
  {
    cin >> x >> y >> z; // odczytujemy krawêdŸ
    if(x > n) n = x;
    if(y > n) n = y;
    pw = new TNode;
    pw->next = L[x]; pw->node = y; pw->weight = z; L[x] = pw;
  }
  cout << endl;

  d[v0] = 0; // koszt dojœcia dla v0 jest zerowy
  
  for(i = 1; i <= n; i++)
  {

// szukamy wierzcho³ka w Q o najmniejszym d

    u = -1;
    for(j = 1; j <= n; j++)
      if(!QS[j] && ((u == -1) || (d[j] < d[u]))) u = j;

// znaleziony wierzcho³ek przenosimy do S

    QS[u] = true;

// Modyfikujemy odpowiednio wszystkich s¹siadów z Q

    pw = L[u];
    while(pw)
    {
      if(!QS[pw->node] && (d[pw->node] > d[u] + pw->weight))
      {
        d[pw->node] = d[u] + pw->weight;
        p[pw->node] = u;
      }
      pw = pw->next;
    }
  }

// Gotowe, wyœwietlamy wyniki

  int stos[MAX_N],ws;
  
  for(i = 1; i <= n; i++)
  {
    cout << i << ": ";
    ws = 0; j = i;

// Wierzcho³ki z koñca œcie¿ki umieszczamy na stosie

    while(j)
    {
      stos[ws++] = j; j = p[j];
    }

// Wypisujemy kolejne wierzcho³ki ze szczytu stosu

    while(ws) cout << stos[--ws] << " ";
    
// Wypisujemy koszt dojœcia

    cout << "#" << d[i] << endl;    
  }        
  char s[1];
  cin.getline(s,1);
  cin.getline(s,1);
}