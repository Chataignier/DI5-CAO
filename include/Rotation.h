#ifndef ROTATION_H_
#define ROTATION_H_

#include <stdio.h>

/** Classe stockant une rotation
 * @ingroup dessin */
class Rotation
{
public:
	/** La matrice 3x3 contenant les coefficients de la rotation */
	double coef[3][3];
public:
	/** Le constructeur */
	Rotation()
	{ //matrice identité
		for (int i = 0; i < 3; ++i )
			for (int j = 0; j < 3; ++j )
				coef[i][j] = (i == j);
	}
	/** Le constructeur */
	Rotation(double r11, double r12, double r13, double r21, double r22,
			double r23, double r31, double r32, double r33)
	{
		coef[0][0] = r11;
		coef[0][1] = r12;
		coef[0][2] = r13;
		coef[1][0] = r21;
		coef[1][1] = r22;
		coef[1][2] = r23;
		coef[2][0] = r31;
		coef[2][1] = r32;
		coef[2][2] = r33;
	}
	/** Le produit de la rotation par un point 3D */
	Coord3D operator*(const Coord3D & c) const
	{
		return Coord3D(coef[0][0] * c.x+ coef[0][1] * c.y+ coef[0][2]*c.z,
				coef[1][0] * c.x+ coef[1][1] * c.y+ coef[1][2]*c.z, coef[2][0]
						* c.x+ coef[2][1] * c.y+ coef[2][2]*c.z);
	}
	/** Le produit de deux rotations : this * r */
	Rotation operator*(const Rotation & r) const
	{
		Rotation res;
		for (int i = 0; i < 3; ++i )
			for (int j = 0; j < 3; ++j )
			{
				double s = 0;
				for (int k = 0; k < 3; ++k)
					s += coef[i][k] * r.coef[k][j];
				res.coef[i][j] = s;
			}
		return res;
	}
	/** Calcule de la rotation transposée */
	Rotation transpose() const
	{
		return Rotation(coef[0][0], coef[1][0], coef[2][0], coef[0][1],
				coef[1][1], coef[2][1], coef[0][2], coef[1][2], coef[2][2]);
	}
	/** Affiche les coefficient de la rotation */
	void display() const
	{
		printf("[ %lf %lf %lf\n%lf %lf %lf\n%lf %lf %lf]\n", coef[0][0],
				coef[0][1], coef[0][2], coef[1][0], coef[1][1], coef[1][2],
				coef[2][0], coef[2][1], coef[2][2]);
	}
};

#endif /*ROTATION_H_*/
