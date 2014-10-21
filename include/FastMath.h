
#ifndef FASTMATH_H__
#define FASTMATH_H__

#include <math.h>

/** Le nombre PI
 * @ingroup util */
#define PI 3.141592653589

/** Classe statique regroupant des fonctions mathématiques "rapides"
 * @ingroup util */
class FastMath
{
public:
	/** @internal Pré-calcule un certain nombre de valeurs */
		static void Initialize();
private:
	/** @internal Classe pour forcer l'initialisation statique */
	class StaticInitializer
	{
	public:
		/** @ internal Constructeur */
		StaticInitializer()
		{
			FastMath::Initialize();
		}
	};
	/** @internal Pour forcer l'initialisation statique de la classe */
	static StaticInitializer staticInitializer;

	/** @internal Les sinus des angles de 0° à 359° */
	static double sinVal[360];
	/** @internal Les cosinus des angles de 0° à 359° */
	static double cosVal[360];
	/** @internal Les tangente des angles de 0° à 359° */
	static double tanVal[360];
public:
	/** Calcule le sinus d'un angle en degrée (précision de l'angle = 1 degré) */
	static inline double fastSin(int angleDegree)
	{
		if (angleDegree < 0)
			return -sinVal[ ( -angleDegree) % 360 ];
		else
			return sinVal[ angleDegree % 360];
	}
	/** Calcule le cosinus d'un angle en degrée (précision de l'angle = 1 degré) */
	static inline double fastCos(int angleDegree)
	{
		if (angleDegree < 0)
			return cosVal[ ( -angleDegree) % 360];
		else
			return cosVal[ angleDegree % 360];
	}
	/** Calcule le tangente d'un angle en degrée (précision de l'angle = 1 degré) */
	static inline double fastTan(int angleDegree)
	{
		if (angleDegree < 0)
			return tanVal[ ( -angleDegree) % 360];
		else
			return tanVal[ angleDegree % 360];
	}
	/** Retourne le minimum de a et b
	 * @remark Si les types de données de a et b sont différents alors il y aura une erreur.
	 * Pour la résoudre, il suffit de préciser le type des arguments (ex: min<int>(1,0.5)) */
	template<class TData> static TData min(TData a, TData b)
	{
		if (a < b)
			return a;
		else
			return b;
	}
	/** Retourne le maximum de a et b
		 * @remark Si les types de données de a et b sont différents alors il y aura une erreur.
		 * Pour la résoudre, il suffit de préciser le type des arguments (ex: max<int>(1,0.5)) */
	template<class TData> static TData max(TData a, TData b)
	{
		if (a < b)
			return b;
		else
			return a;
	}
	/** Retourne l'entier le plus proche */
	static inline int Round(double d)
	{
		return (int) (d + 0.5);
	}
	/** Retourne la racine carée du nombre */
	static inline double Sqrt(double d)
	{
		return sqrt((double)d);
	}
};

#endif /*MATH_H_*/
