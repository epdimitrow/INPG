
#include <iostream>

using namespace std;

const int MAXINT = 2147483647;


struct slistEl
{
  slistEl * next;
  int data;
};

class queue
{
  private:
    slistEl * head;
    slistEl * tail;

  public:
    queue();      // konstruktor
    ~queue();     // destruktor
    bool empty(void);
    int  front(void);
    void push(int v);
    void pop(void);
};


queue::queue()
{
  head = tail = NULL;
}

queue::~queue()
{
  while(head) pop();
}

// Sprawdza, czy kolejka jest pusta
//---------------------------------
bool queue::empty(void)
{
  return !head;
}

// Zwraca pocz¹tek kolejki.
// Wartoœæ specjalna to -MAXINT
//-----------------------------
int queue::front(void)
{
  if(head) return head->data;
  else     return -MAXINT;
}

// Zapisuje do kolejki
//--------------------
void queue::push(int v)
{
  slistEl * p = new slistEl;
  p->next = NULL;
  p->data = v;
  if(tail) tail->next = p;
  else     head = p;
  tail = p;
}

// Usuwa z kolejki
//----------------
void queue::pop(void)
{
  if(head)
  {
    slistEl * p = head;
    head = head->next;
    if(!head) tail = NULL;
    delete p;
  }
}

//---------------
// Program g³ówny
//---------------

int main()
{
  queue Q;                        // Kolejka
  int ** C;                       // Macierz przepustowoœci
  int ** F;                       // Macierz przep³ywów netto
  int * P;                        // Tablica poprzedników
  int * CFP;                      // Tablica przepustowoœci rezydualnych
  int n,m,s,t,fmax,cp,x,y,i,j;    // Zmienne proste algorytmu
  bool esc;                       // Do wychodzenia z zagnie¿d¿onych pêtli

  // Ze standardowego wejœcia odczytujemy
  // n - liczbê wierzcho³ków w grafie sieci
  // m - liczbê krawêdzi

  cin >> n >> m;

  // Tworzymy dynamicznie macierze:
  // C - przepustowoœci krawêdzi
  // F - przep³ywy w krawêdziach

  C = new int * [n];
  F = new int * [n];
  for(i = 0; i < n; i++)
  {
    C[i] = new int [n];
    F[i] = new int [n];
  }

  // Tworzymy dynamicznie tablice:
  // P   - poprzedniki na œcie¿kach tworzonych przez BFS
  // CFP - przepustowoœæ œcie¿ek

  P = new int [n];
  CFP = new int [n];

  // Zerujemy macierze przepustowoœci i przep³ywów

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) C[i][j] = F[i][j] = 0;

  // Ze standardowego wejœcia odczytujemy definicje krawêdzi.
  // Ka¿da definicja sk³ada siê z trzech liczb
  // x,y - wierzcho³ki grafu po³¹czone krawêdzi¹
  // cp  - przepustowoœæ krawêdzi
  // Odczytane dane zapamiêtujemy: C[x][y] = cp

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> cp;
    C[x][y] = cp;
  }

  // Na koniec odczytujemy numer wierzcho³ka Ÿród³a s
  // oraz numer wierzcho³ka ujœcia t

  cin >> s >> t;

  //**************************************************
  //** Tutaj rozpoczyna siê algorytm Edmondsa-Karpa **
  //**************************************************

  // Rozpoczynamy od maksymalnego przep³ywu równego zero

  fmax = 0;

  // W pêtli szukamy œcie¿ek rozszerzaj¹cych dot¹d,
  // dopóki istniej¹ w sieci rezydualnej. Ka¿da znaleziona
  // œcie¿ka zwiêksza przep³yw wzd³u¿ zawartych w niej
  // krawêdzi grafu sieci przep³ywowej

  while(true)
  {

    // Na pocz¹tku pêtli zerujemy tablicê poprzedników P

    for(i = 0; i < n; i++) P[i] = -1;

    // Ÿród³o nie posiada poprzednika. Wpisujemy tutaj -2,
    // aby BFS nie wybiera³o Ÿród³a

    P[s] = -2;

    // Do CFP[s] wpisujemy najwiêksz¹ liczbê ca³kowit¹

    CFP[s] = MAXINT;

    // Zerujemy kolejkê i umieszczamy w niej Ÿród³o s

    while(!Q.empty()) Q.pop();
    Q.push(s);

    // Zmienna esc umo¿liwia odpowiednie wychodzenie z
    // dwóch zagnie¿d¿onych pêtli - zamiast polecenie goto.

    esc = false;

    // Rozpoczynamy pêtlê wyszukuj¹c¹ œcie¿ki BFS. Pêtla koñczy
    // siê w przypadku braku dalszych wierzcho³ków w kolejce

    while(!Q.empty())
    {

      // Z pocz¹tku kolejki pobieramy element i usuwamy go z kolejki

      x = Q.front(); Q.pop();

      // Sprawdzamy wszystkich s¹siadów wierzcho³ka x przegl¹daj¹c
      // wiersz macierzy C

      for(y = 0; y < n; y++)
      {

        // Dla s¹siada y wyznaczamy przepustowoœæ rezydualn¹
        // krawêdzi x->y. Jeœli krawêdŸ nie istnieje w sieci,
        // to otrzymamy w cp wynik zero

        cp = C[x][y] - F[x][y];

        // Sprawdzamy, czy krawêdŸ istnieje oraz czy wierzcho³ek
        // y nie by³ ju¿ wczeœniej wybrany przez BFS. W takim
        // przypadku P[y] ma wartoœæ ró¿n¹ od -1.

        if(cp && (P[y] == -1))
        {

          // W P[y] zapamiêtujemy, i¿ poprzednikiem y jest x

          P[y] = x;

          // Dla wierzcho³ka y obliczamy dotychczasow¹ przepustowoœæ
          // rezydualn¹ œcie¿ki. Jest to mniejsza wartoœæ z przepustowoœci
          // œcie¿ki dla poprzednika x i bie¿¹cej przepustowoœci
          // rezydualnej krawêdzi x->y.

          CFP[y] = CFP[x] > cp ? cp : CFP[x];

          // Jeœli osi¹gnêliœmy ujœcie, to œcie¿ka jest kompletna

          if(y == t)
          {

            // Zwiêkszamy przep³yw maksymalny o przepustowoœæ rezydualn¹
            // œcie¿ki - wykorzystujemy tablicê CFP

            fmax += CFP[t];

            // Idziemy wstecz po œcie¿ce zwiêkszaj¹c przep³ywy
            // wzd³u¿ jej krawêdzi w kierunku zgodnym ze œcie¿k¹
            // oraz zmniejszaj¹c przep³ywy w kierunku przeciwnym

            i = y;
            while(i != s)
            {
              x = P[i];
              F[x][i] += CFP[t];
              F[i][x] -= CFP[t];
              i = x;
            }

            // Ustawiamy esc na true, co spowoduje wyjœcie z obu pêtli

            esc = true; break;
          }

          // Jeœli wierzcho³ek y nie jest ujœciem t, to dopisujemy
          // go na koñcu kolejki Q i kontynuujemy pêtlê BFS

          Q.push(y);
        }
      }

      // Tutaj wychodzimy z pêtli while, jeœli
      // zosta³a znaleziona œcie¿ka rozszerzaj¹ca

       if(esc) break;
    }

    // Jeœli nie znaleziono œcie¿ki rozszerzaj¹cej, to esc = false
    // i w tym miejscu nast¹pi wyjœcie z g³ównej pêtli while

    if(!esc) break;
  }

  // Prezentujemy wyniki obliczeñ. Najpierw wypisujemy
  // wartoœæ maksymalnego przep³ywu

  cout << endl << "fmax = " << fmax << endl << endl;

  // Nastêpnie wypisujemy przep³ywy netto wzd³u¿ krawêdzi

  for(x = 0; x < n; x++)
    for(y = 0; y < n; y++)
      if(C[x][y]) cout << x << " -> " << y << " " << F[x][y] << ":" << C[x][y] << endl;

  cout << endl;

  // Usuwamy zmienne dynamiczne

  for(i = 0; i < n; i++)
  {
    delete [] C[i];
    delete [] F[i];
  }

  delete [] C;
  delete [] F;
  delete [] P;
  delete [] CFP;

  return 0;
} 