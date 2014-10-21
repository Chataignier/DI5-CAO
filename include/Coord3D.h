#ifndef COORD3D_H_
#define COORD3D_H_

#include <Coord2D.h>
#include <stdio.h>
#include <FastMath.h>
#include <Memory.h>

/** Une classe stockant des coordonnées 3D d'un point
 * @ingroup dessin */
class Coord3D
{
public:
	double x; /**< la coordonnée x */
	double y; /**< la coordonnée y */
	double z; /**< la coordonnée z */
public:
	/** le constructeur */
	Coord3D() :
		x(0), y(0), z(0)
	{
		;
	}
	/** le constructeur */
	Coord3D(double _x, double _y, double _z) :
		x(_x), y(_y), z(_z)
	{
		;
	}
	/** l'opérateur d'opposition */
	Coord3D operator-() const
	{
		return Coord3D( -x, -y, -z);
	}
	/** l'opérateur de soustraction */
	Coord3D operator-(const Coord3D & c) const
	{
		return Coord3D(x - c.x, y - c.y, z - c.z);
	}
	/** l'opérateur d'addition */
	Coord3D operator+(const Coord3D & c) const
	{
		return Coord3D(x + c.x, y + c.y, z + c.z);
	}
	/** l'opérateur d'addition étendu */
	Coord3D &operator+=(const Coord3D & c)
	{
		x += c.x;
		y += c.y;
		z += c.z;
		return *this;
	}
	/** l'opérateur de multiplication par un scalaire */
	Coord3D operator*(const double c) const
	{
		return Coord3D(x*c, y*c, z*c);
	}
	/** l'oprateur de multiplication par un scalaire étendu */
	Coord3D &operator*=(const double c)
	{
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}
	/** Calcule la norme euclidienne du point/vecteur */
	double Norm() const
	{
		return FastMath::Sqrt(x*x + y*y + z*z );
	}
	/** Affiche les coordonnées du point */
	void display() const
	{
		printf("[%lf %lf %lf]\n", x, y, z);
	}
	/** l'opérateur produit vectoriel */
	Coord3D operator^(const Coord3D & v) const
	{
		return Coord3D(y * v.z- z * v.y, z * v.x- x * v.z, x * v.y- y * v.x);
	}
	/** l'opérateur produit scalaire */
	double operator*(const Coord3D & v) const
	{
		return x * v.x+ y*v.y+ z*v.z;
	}
	/** Normalise le vecteur en le divisant par sa norme */
	void Normalize()
	{
		double n = Norm();
		if (fabs(n) < 0.001)
			return;
		x /= n;
		y /= n;
		z /= n;
	}
};

#endif /*COORD3D_H_*/
