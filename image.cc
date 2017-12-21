#include <iostream>

#include "image.h"

int main(int argc, char const *argv[])
{

	//Aufgabe 2 b)
	Image aufgabe_2b(4,3);

	std::string str = "";

	std::cout << "Breite = " << aufgabe_2b.width() << std::endl;
	std::cout << "Höhe = " << aufgabe_2b.height() << std::endl;
	std::cout << "Größe = " << aufgabe_2b.size() << std::endl;
	
	str = to_string(aufgabe_2b);
	std::cout << str << std::endl;

	//Aufgabe 2c)
   /* int counter = 0;

    for (int i = 0; i < aufgabe_2b.width(); ++i)
    {
        for (int k = 0; k < aufgabe_2b.height(); ++k)
        {
            std::cout << counter << std::endl; 
            if (counter%2 == 0)
            {
                aufgabe_2b(i,k) = 255;
            }            
            else
            {
                aufgabe_2b(i,k) = 0;
            }
            counter += 1;
        }
    }

    str = to_string(aufgabe_2b);
    std::cout << str << std::endl; */


	return 0;
}