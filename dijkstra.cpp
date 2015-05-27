
#include <iostream>

using namespace std;

const int MAX_N = 100; // maksymalna ilo�� wierzcho�k�w w grafie
const int INF = 2147483647;

struct TNode
{
  int node;            // numer wierzcho�ka
  int weight;          // waga kraw�dzi
  struct TNode * next; // nast�pny element listy
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
    d[i]  = INF;    // koszty doj�cia
    p[i]  = 0;      // poprzednik na �cie�ce
    QS[i] = false; // przynale�no�� do Q (false) lub S (true)
    L[i]  = NULL;   // lista s�siedztwa
  }
  n = 0;

// Odczytujemy dane wej�ciowe

  cin >> v0; // odczytujemy numer wierzcho�ka startowego
  cin >> m;  // odczytujemy ilo�� kraw�dzi
  for(i = 1; i <= m; i++)
  {
    cin >> x >> y >> z; // odczytujemy kraw�d�
    if(x > n) n = x;
    if(y > n) n = y;
    pw = new TNode;
    pw->next = L[x]; pw->node = y; pw->weight = z; L[x] = pw;
  }
  cout << endl;

  d[v0] = 0; // koszt doj�cia dla v0 jest zerowy
  
  for(i = 1; i <= n; i++)
  {

// szukamy wierzcho�ka w Q o najmniejszym d

    u = -1;
    for(j = 1; j <= n; j++)
      if(!QS[j] && ((u == -1) || (d[j] < d[u]))) u = j;

// znaleziony wierzcho�ek przenosimy do S

    QS[u] = true;

// Modyfikujemy odpowiednio wszystkich s�siad�w z Q

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

// Gotowe, wy�wietlamy wyniki

  int stos[MAX_N],ws;
  
  for(i = 1; i <= n; i++)
  {
    cout << i << ": ";
    ws = 0; j = i;

// Wierzcho�ki z ko�ca �cie�ki umieszczamy na stosie

    while(j)
    {
      stos[ws++] = j; j = p[j];
    }

// Wypisujemy kolejne wierzcho�ki ze szczytu stosu

    while(ws) cout << stos[--ws] << " ";
    
// Wypisujemy koszt doj�cia

    cout << "#" << d[i] << endl;    
  }        
  char s[1];
  cin.getline(s,1);
  cin.getline(s,1);
}