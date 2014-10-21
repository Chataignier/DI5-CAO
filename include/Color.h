#ifndef COLOR_H_
#define COLOR_H_

#include <FastMath.h>

/** Une classe stockant une couleur RVB
 * @ingroup dessin */
class Color
{
public:
  unsigned char red; /**< la couleur rouge codée sur [0;255] */
  unsigned char green; /**< la couleur verte codée sur [0;255] */
  unsigned char blue; /**< la couleur bleue codée sur [0;255] */
public:
  /** le constructeur */
  Color() :
    red(0), green(0), blue(0)
  {
    ;
  }
  /** le constructeur */
  Color(unsigned char _red, unsigned char _green, unsigned char _blue) :
    red(_red), green(_green), blue(_blue)
  {
    ;
  }
  /** opérateur d'addition de couleur */
  Color operator+(const Color & c) const
  {
    return Color((unsigned char)FastMath::min(255, red+c.red), (unsigned char)FastMath::min(255, green+c.green),
            (unsigned char)FastMath::min(255, blue+c.blue));
  }
  /** opérateur de multiplication par un scalaire */
  Color operator*(const double c) const
  {
    return Color((unsigned char)FastMath::min(255, FastMath::Round(c*red)), (unsigned char)FastMath::min(255,
        FastMath::Round(c*green)), (unsigned char)FastMath::min(255, FastMath::Round(c*blue)) );

  }
  /** opérateur de composition de deux couleurs */
  Color operator*(const Color & c) const
  {
    return Color((unsigned char)FastMath::min(255, (red * c.red)/255), (unsigned char)FastMath::min(255, (green
        *c.green)/255), (unsigned char)FastMath::min(255, (blue * c.blue)/255) );
  }
  /** opérateur de test d'égalité */
  bool operator==(const Color & c) const
  {
    return (red == c.red) && (blue == c.blue)&& (green == c.green);
  }
};

#endif /*COLOR_H_*/
