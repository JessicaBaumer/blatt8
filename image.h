#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstdint>
#include <iostream>

class Image
{
public:
  typedef uint16_t PixelType;

private:
  int _width;
  int _height;
  std::vector<PixelType> _data;

public:
  // Standardkonstruktor: initialisiere Bild mit Groesse (0,0)
  Image()
    : _width(0), _height(0)
  {_data.push_back(0);}

  // Konstruktor: initialisiere Bild mit Groesse (width, height)
  // Alle Pixel sollen danach den Wert '0' haben.
  Image(unsigned int width, unsigned int height)
    : _width(width), _height(height)
  {
  	for(int i = 0; i <= width*height; i++)
  	{
  		_data.push_back(0);
  	}
  }

  // Breite abfragen
  int width() const 
  {
    return _width;
  }

  // Hoehe abfragen
  int height() const 
  {
    return _height;
  }

  // Gesamtzahl der Pixel abfragen
  int size() const 
  {
    return _width * _height;
  }

  // Groesse der Bildes aendern. Welche Methode der Klasse vector
  // ist hier sinnvoll?
  void resize(unsigned int new_width, unsigned int new_height) 
  {
    _width = new_width;
    _height = new_height;

    _data.resize(new_width * new_height);
  }

  // lesender Zugriff auf des Pixel an Position (x,y)
  PixelType operator()(int x, int y) const 
  { 
    if (y < 1) return _data.at(x);
    return _data.at(((_width * (y-1))+x));
  }

  // Lese/Schreib-Zugriff auf des Pixel an Position (x,y)
  PixelType & operator()(int x, int y) 
  {
    if (y < 1) return _data.at(x);
    return _data.at(((_width * (y-1))+x));			
  }
};


// Gib 'true' zurueck, wenn die gegebenen Bilder gleich sind.
// Dies ist der Fall, wenn die Bildgroessen uebereinstimmen und
// alle Pixel die gleichen Werte haben.
// Diese Funktion ist nuetzlich zum Testen der Bildklasse.
bool operator==(Image const & im0, Image const & im1) 
{
  if ( !(im0.width() == im1.width() || !(im0.height() == im1.height()) ) )
  {
  	return false;
  }
  for (int i = 0; i < im0.width(); i++)
  {
  	for (int k = 0; i < im0.height(); k++)
  	{
  		if (!(im0(i,k) == im1(i,k))) return false;
  	}
  }	
  return true;		
}

// Wandle die Pixelwerte zeilenweise in einen String.
// Fuer ein Bild der Groesse 4x3, das die Pixelwerte 0 und 1
// in Schachbrett-Anordnung enthaelt, soll z.B. der String
//         "0 1 0 1\n
//			1 0 1 0\n
//			0 1 0 1\n"
// zurueckgegeben werden (Pixelwerte sind durch Leerzeichen
// getrennt, am Ende jeder Zeile steht ein Enter-Zeichen '\n').
// Finden Sie heraus, welche Methode der C++-Standardbibliothek
// eine Variable vom Typ int in einen String umwandelt.
std::string to_string(Image const & im) 
{
  std::string res;
  for (int h = 0; h < im.height(); h++)
  {
  	for (int w = 0; w < im.width(); w++)
  	{
  		res.append(std::to_string(im(w,h)));
  		res.append(" ");
  	}
  	res.append("\n");
  }
  // IHR CODE HIER
  return res;
}

// Gib das Bild im PGM-Format in das File 'filename' aus.
//
// Die Bilddatei kann mit allen Bildbetrachtern angezeigt
// werden, die das PGM-Format unterstuetzen (unter Windows
// z.B. 'IrfanView', unter Linux z.B. 'display' aus der
// imagemagick-Installation, ueberall 'gimp').
//
// Da das PGM-Format ein Textformat ist, kann man es zum
// Debuggen auch im Editor oeffnen und ueberpruefen.
void writePGM(Image const & img, std::string const & filename) 
{
  // Filestream erzeugen
  std::ofstream pgm(filename, std::ios::binary);

  // Fehlermeldung, wenn sich das File nicht oeffnen laesst.
  if (!pgm) 
  {
    throw std::runtime_error("writePGM(): cannot open file '" + filename + "'.");
  }

  // Headerinformationen schreiben
  int max_pixelvalue = 255;
  pgm << "P2\n"
      << img.width() << " " << img.height() << "\n"
      << max_pixelvalue << "\n";

  // Bilddaten schreiben (verwendet Ihre Funktion 'to_string').
  pgm << to_string(img);
}

// Gib 'true' zurueck, wenn das File 'filename' das PGM-Format hat.
bool checkPGM(std::string const & filename) 
{
  std::ifstream pgm(filename);
  std::string line;

  // Teste, ob das File geoeffnet werden kann und
  // mindestens eine Zeile hat.
  if (!std::getline(pgm, line)) 
  {
    return false;
  }

  // Teste, dass die erste Zeile der String "P2" ist.
  return line == "P2";
}

// Lese das File 'filename' (im PGM-Format) ein und gib das resultierende
// Bild zurueck.
Image readPGM(std::string const & filename) 
{
  // Fehlermeldung, wenn sich das File nicht oeffnen laesst
  // oder kein PGM-File ist.
  if (!checkPGM(filename)) 
  {
    throw std::runtime_error("readPGM(): File '" + filename + "' is not PGM.");
  }

  // Filestream erzeugen
  std::ifstream pgm(filename);
  std::string line;

  // erste Zeile einlesen (enthaelt den String "P2")
  std::getline(pgm, line);

  // eventuelle Kommentarzeilen ueberspringen
  while (pgm.peek() == '#') 
  {
    std::getline(pgm, line);
  }

  // Breite und Hoehe einlesen
  int width, height;
  pgm >> width >> height;

  // maximalen Grauwert einlesen und Fehlermeldung ausgeben, falls zu gross
  int max_value;
  pgm >> max_value;
  if (max_value > 255) 
  {
    throw std::runtime_error("readPGM(): max value must be <= 255.");
  }

  // Ergebnisbild der gewuenschten Groesse erzeugen
  Image res(width, height);

  // Pixeldaten in einer zweifach geschachtelten Schleife ueber
  // die Zeilen und Spalten einlesen.

  for (int h = 0; h < res.height(); h++)
  {
  	for (int w = 0; w < res.width(); w++)
  	{
  		Image::PixelType cache;
  		pgm >> cache;
  		res(h,w) = cache;
  	}
  }
  return res;
}

#endif // IMAGE_H

