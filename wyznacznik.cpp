#include <iostream>
#include <iomanip>

using namespace std;

// Rekurencyjna funkcja obliczaj¹ca rozwiniêcie Laplace'a
//-------------------------------------------------------
double det(int n, int w, int * WK, double ** A)
{
  int    i,j,k,m, * KK;
  double s;

  if(n == 1)                                    // sprawdzamy warunek zakoñczenia rekurencji

    return A[w][WK[0]];                         // macierz 1 x 1, wyznacznik równy elementowi

  else
  {

    KK = new int[n - 1];                        // tworzymy dynamiczny wektor kolumn

    s = 0;                                      // zerujemy wartoœæ rozwiniêcia
    m = 1;                                      // pocz¹tkowy mno¿nik

    for(i = 0; i < n; i++)                      // pêtla obliczaj¹ca rozwiniêcie
    {

      k = 0;                                    // tworzymy wektor kolumn dla rekurencji

      for(j = 0; j < n - 1; j++)                // ma on o 1 kolumnê mniej ni¿ WK
      {
        if(k == i) k++;                         // pomijamy bie¿¹c¹ kolumnê
        KK[j] = WK[k++];                        // pozosta³e kolumny przenosimy do KK
      }

      s += m * A[w][WK[i]] * det(n - 1,w  + 1, KK, A);

      m = -m;                                   // kolejny mno¿nik

    }

    delete [] KK;                               // usuwamy zbêdn¹ ju¿ tablicê dynamiczn¹

    return s;                                   // ustalamy wartoœæ funkcji

  }
}

//*** PROGRAM G£ÓWNY ***
//----------------------

int main()
{
  int       n,i,j;                              // stopieñ macierzy
  int     * WK;                                 // wektor kolumn
  double ** A;                                  // macierz

  cout << fixed << setprecision(4);

  cin >> n;                                     // odczytujemy stopieñ macierzy

  A = new double * [n];                         // tworzymy macierz wskaŸników

  for(i = 0; i < n; i++)
  {

    A[i] = new double[n];                       // tworzymy wiersz

    for(j = 0; j < n; j++) cin >> A[i][j];      // czytamy wiersz macierzy
      
  }

  WK = new int[n];                              // tworzymy wiersz kolumn

  for(i = 0; i < n; i++)                        // wype³niamy go numerami kolumn
    WK[i] = i;

  cout << endl;

  cout << det(n, 0, WK, A) << endl; // obliczamy i wyœwietlamy wyznacznik

  delete [] WK;                                 // usuwamy tablice dynamiczne

  for(i = 0; i < n; i++) delete [] A[i];

  delete [] A;

}