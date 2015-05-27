#include <iostream>
int main()
{
    int liczba;
    std::cin >> liczba;
    if( liczba >= 10 )
    {
        std::cout << "Liczba jest >= 10" << std::endl;
        if( liczba >= 50 )
        {
            std::cout << "Liczba jest >= 50" << std::endl;
            if( liczba <= 100 )
                 std::cout << "Liczba jest <= 100" << std::endl;
           
        }
    }
    std::cout << "Koniec" << std::endl;
    return 0;
}