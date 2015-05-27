
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

// Zwraca pocz�tek kolejki.
// Warto�� specjalna to -MAXINT
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
// Program g��wny
//---------------

int main()
{
  queue Q;                        // Kolejka
  int ** C;                       // Macierz przepustowo�ci
  int ** F;                       // Macierz przep�yw�w netto
  int * P;                        // Tablica poprzednik�w
  int * CFP;                      // Tablica przepustowo�ci rezydualnych
  int n,m,s,t,fmax,cp,x,y,i,j;    // Zmienne proste algorytmu
  bool esc;                       // Do wychodzenia z zagnie�d�onych p�tli

  // Ze standardowego wej�cia odczytujemy
  // n - liczb� wierzcho�k�w w grafie sieci
  // m - liczb� kraw�dzi

  cin >> n >> m;

  // Tworzymy dynamicznie macierze:
  // C - przepustowo�ci kraw�dzi
  // F - przep�ywy w kraw�dziach

  C = new int * [n];
  F = new int * [n];
  for(i = 0; i < n; i++)
  {
    C[i] = new int [n];
    F[i] = new int [n];
  }

  // Tworzymy dynamicznie tablice:
  // P   - poprzedniki na �cie�kach tworzonych przez BFS
  // CFP - przepustowo�� �cie�ek

  P = new int [n];
  CFP = new int [n];

  // Zerujemy macierze przepustowo�ci i przep�yw�w

  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++) C[i][j] = F[i][j] = 0;

  // Ze standardowego wej�cia odczytujemy definicje kraw�dzi.
  // Ka�da definicja sk�ada si� z trzech liczb
  // x,y - wierzcho�ki grafu po��czone kraw�dzi�
  // cp  - przepustowo�� kraw�dzi
  // Odczytane dane zapami�tujemy: C[x][y] = cp

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> cp;
    C[x][y] = cp;
  }

  // Na koniec odczytujemy numer wierzcho�ka �r�d�a s
  // oraz numer wierzcho�ka uj�cia t

  cin >> s >> t;

  //**************************************************
  //** Tutaj rozpoczyna si� algorytm Edmondsa-Karpa **
  //**************************************************

  // Rozpoczynamy od maksymalnego przep�ywu r�wnego zero

  fmax = 0;

  // W p�tli szukamy �cie�ek rozszerzaj�cych dot�d,
  // dop�ki istniej� w sieci rezydualnej. Ka�da znaleziona
  // �cie�ka zwi�ksza przep�yw wzd�u� zawartych w niej
  // kraw�dzi grafu sieci przep�ywowej

  while(true)
  {

    // Na pocz�tku p�tli zerujemy tablic� poprzednik�w P

    for(i = 0; i < n; i++) P[i] = -1;

    // �r�d�o nie posiada poprzednika. Wpisujemy tutaj -2,
    // aby BFS nie wybiera�o �r�d�a

    P[s] = -2;

    // Do CFP[s] wpisujemy najwi�ksz� liczb� ca�kowit�

    CFP[s] = MAXINT;

    // Zerujemy kolejk� i umieszczamy w niej �r�d�o s

    while(!Q.empty()) Q.pop();
    Q.push(s);

    // Zmienna esc umo�liwia odpowiednie wychodzenie z
    // dw�ch zagnie�d�onych p�tli - zamiast polecenie goto.

    esc = false;

    // Rozpoczynamy p�tl� wyszukuj�c� �cie�ki BFS. P�tla ko�czy
    // si� w przypadku braku dalszych wierzcho�k�w w kolejce

    while(!Q.empty())
    {

      // Z pocz�tku kolejki pobieramy element i usuwamy go z kolejki

      x = Q.front(); Q.pop();

      // Sprawdzamy wszystkich s�siad�w wierzcho�ka x przegl�daj�c
      // wiersz macierzy C

      for(y = 0; y < n; y++)
      {

        // Dla s�siada y wyznaczamy przepustowo�� rezydualn�
        // kraw�dzi x->y. Je�li kraw�d� nie istnieje w sieci,
        // to otrzymamy w cp wynik zero

        cp = C[x][y] - F[x][y];

        // Sprawdzamy, czy kraw�d� istnieje oraz czy wierzcho�ek
        // y nie by� ju� wcze�niej wybrany przez BFS. W takim
        // przypadku P[y] ma warto�� r�n� od -1.

        if(cp && (P[y] == -1))
        {

          // W P[y] zapami�tujemy, i� poprzednikiem y jest x

          P[y] = x;

          // Dla wierzcho�ka y obliczamy dotychczasow� przepustowo��
          // rezydualn� �cie�ki. Jest to mniejsza warto�� z przepustowo�ci
          // �cie�ki dla poprzednika x i bie��cej przepustowo�ci
          // rezydualnej kraw�dzi x->y.

          CFP[y] = CFP[x] > cp ? cp : CFP[x];

          // Je�li osi�gn�li�my uj�cie, to �cie�ka jest kompletna

          if(y == t)
          {

            // Zwi�kszamy przep�yw maksymalny o przepustowo�� rezydualn�
            // �cie�ki - wykorzystujemy tablic� CFP

            fmax += CFP[t];

            // Idziemy wstecz po �cie�ce zwi�kszaj�c przep�ywy
            // wzd�u� jej kraw�dzi w kierunku zgodnym ze �cie�k�
            // oraz zmniejszaj�c przep�ywy w kierunku przeciwnym

            i = y;
            while(i != s)
            {
              x = P[i];
              F[x][i] += CFP[t];
              F[i][x] -= CFP[t];
              i = x;
            }

            // Ustawiamy esc na true, co spowoduje wyj�cie z obu p�tli

            esc = true; break;
          }

          // Je�li wierzcho�ek y nie jest uj�ciem t, to dopisujemy
          // go na ko�cu kolejki Q i kontynuujemy p�tl� BFS

          Q.push(y);
        }
      }

      // Tutaj wychodzimy z p�tli while, je�li
      // zosta�a znaleziona �cie�ka rozszerzaj�ca

       if(esc) break;
    }

    // Je�li nie znaleziono �cie�ki rozszerzaj�cej, to esc = false
    // i w tym miejscu nast�pi wyj�cie z g��wnej p�tli while

    if(!esc) break;
  }

  // Prezentujemy wyniki oblicze�. Najpierw wypisujemy
  // warto�� maksymalnego przep�ywu

  cout << endl << "fmax = " << fmax << endl << endl;

  // Nast�pnie wypisujemy przep�ywy netto wzd�u� kraw�dzi

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