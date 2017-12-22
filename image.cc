#include <iostream>

#include "image.h"


// Aufgabe 2 e)
Image chessboard (unsigned int width, unsigned int height, 
                  unsigned int square_size)
{
  Image result(width,height);
  uint8_t white_col = 255;
  uint8_t black_col = 0;
  for (unsigned int x = 0; x < result.width(); x++)
  {
    for (unsigned int y = 0; y < result.height(); y++)
    {
      bool flip_switch = false;  // true weiß | false schwarz
      if ((y+1)%(square_size+1) == 0)
      {
        if((x+1)%(square_size+2) == 0){flip_switch = !flip_switch;}
        if(flip_switch){result(x,y) = white_col;}
        else{result(x,y) = black_col;}
      }

      else
      {
        if((x+1)%(square_size+2) != 0 ){flip_switch = !flip_switch;}
        if(flip_switch){result(x,y) = white_col;}
        else{result(x,y) = black_col;}
      }
    }
  }
  return result;
}


// Aufgabe 2 c)
void schachbrettern(Image& imago)
{
  for (unsigned int w = 0; w < imago.width(); ++w) 
  {
    for (unsigned int h = 0; h < imago.height(); ++h)
    {      
      if (h % 2 == 0) {
        if (imago.getPlace(w, h) % 2 == 0) 
        {
          imago(w, h) = 255;
        } else imago(w, h) = 0;
      }
      if ( h % 2 != 0) 
      {
        if (imago.getPlace(w, h) % 2 != 0) 
        {
          imago(w, h) = 255;
        } else imago(w, h) = 0;
      }
    }
  }
}

int main(int argc, char const *argv[])
{
    
    //Aufgabe 2 b)
	Image aufgabe_2b(4,3);

	std::string str = "";

	std::cout << "Breite = " << aufgabe_2b.width() << std::endl;
	std::cout << "Höhe = " << aufgabe_2b.height() << std::endl;
	std::cout << "Größe = " << aufgabe_2b.size() << std::endl;
	std::cout << std::endl;


	str = to_string(aufgabe_2b);
	std::cout << str << std::endl;

    // Aufgabe 2 c)
    Image board4x3_pre(4, 3);
    schachbrettern(board4x3_pre);
    str = to_string(board4x3_pre);
    std::cout << str << std::endl;

    // Aufgabe 2 d)
    writePGM(board4x3_pre,"board4x3.pgm");
    Image board4x3 = readPGM("board4x3.pgm");

    if (board4x3_pre  == board4x3)
    {
        std::cout << "Die Images board4x3_pre und board4x3 sind gleich!" << std::endl;
    }
    else{
        std::cout << "Die Images board4x3_pre sind board4x3 nicht gleich!" << std::endl;
    }

    // Aufgabe 2 e)
    Image chessboard_pre = chessboard(4,3,1);
    writePGM(chessboard_pre,"chessboard_post.pgm");
    Image chessboard_post = readPGM("chessboard_post.pgm");

    if (chessboard_pre  == chessboard_post)
    {
        std::cout << "Die Images chessboard_pre und chessboard_post sind gleich!" << std::endl;
    }
    else
    {
        std::cout << "Die Images chessboard_pre sind chessboard_post nicht gleich!" << std::endl;
    }


	return 0;
}