#ifndef IndexOutOfBoundsException_h
#define IndexOutOfBoundsException_h

#include <Exception.h>

/** Une classe levée lorsqu'un paramètre est hors de son domaine valide de valeur
 * @ingroup exception  */
class IndexOutOfBoundsException : public Exception
{
private:
	/** L'index qui a levée une exception */
	int index;
	/** La valeur minimum que peut prendre l'index */
	int min;
	/** La valeur maximum que peut prendre l'index */
	int max;
public:
	/** Le constructeur */
	IndexOutOfBoundsException(int index, int min, int max);
	/** Accesseur */
	int getIndex() const;
	/** Accesseur */
	int getMin() const;
	/** Accesseur */
	int getMax() const;
};

/** @def CheckBounds_Always(index,min,max) Vérifie que index in [min;max] et lève une exception IndexOutOfBoundsException en cas d'échec */
#define CheckBounds_Always( Index, Min, Max ) \
	if (((Index) < (Min)) || ((Max) < (Index))) \
	{ \
		IndexOutOfBoundsException __e((Index), (Min), (Max)); \
		RaiseException(__e); \
	}


#ifdef DEBUG
#define CheckBounds_Debug( Index, Min, Max ) \
		if (((Index) < (Min)) || ((Max) < (Index))) \
		{ \
			IndexOutOfBoundsException __e((Index), (Min), (Max)); \
			RaiseException(__e); \
		}
#else
/** @def CheckBounds_Debut(index,min,max) Idem que CheckBounds_Always mais ne s'applique qu'en mode DEBUG */
#define CheckBounds_Debug( Index, Min, Max )
#endif

#endif
