#ifndef COORD2D_H_
#define COORD2D_H_

#include <FastMath.h>

/** Une classe stockant les coordonnées 2D d'un point ainsi que la profondeur du point d'origine normalisé par rapport au repère caméra
 * @ingroup dessin */
class Coord2D
{
public:
	int x; /**< l'abscisse 2D */
	int y; /**< l'ordonnée 2D */
	double depth; /**< la profondeur normalisée du point 3D associé dans le repère caméra */
public:
	/** constructeur */
	Coord2D() :
		x(0), y(0), depth(0)
	{
		;
	}
	/** constructeur */
	Coord2D(int _x, int _y, double _depth = 0) :
		x(_x), y(_y), depth(_depth)
	{
		;
	}
	/** la distance entre deux points 2D (ne tient pas compte de la profondeur depth) */
	double Distance(const Coord2D & c) const
	{
		return FastMath::Sqrt( (x-c.x)*(x-c.x)+ (y-c.y)*(y-c.y));
	}
};

#endif /*COORD2D_H_*/
