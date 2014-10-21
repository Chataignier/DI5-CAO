#ifndef Memory_h
#define Memory_h

#include <MemoryException.h>
#include <stdlib.h>

/** @internal Fonction pour la recopie d'objet en mémoire
 * @ingroup util */
template<class TData> inline void MemCopy(const TData * source, TData * dest,
		const int count)
{
	if (dest < source)
		for (int i = 0; i < count; ++i )
			dest[i] = source[i];
	else
		for (int i = count - 1; i >= 0; --i )
			dest[i] = source[i];
}

/** @internal Fonction pour la réallocation de tableau d'objet
 * @ingroup util */
template<class TData> inline TData * ReallocMemory(const TData * origin,
		const int oldSize, const int newSize, const bool preserveContent)
{
	TData * nouv;
	if (newSize > 0)
	{
		nouv = new TData[newSize];

		if (nouv == NULL)
		{
			MemoryException e(wxT("Error resizing array"));
			RaiseException(e);
		}

		if (preserveContent)
		{
			int commun = (oldSize < newSize) ? oldSize : newSize;
			MemCopy<TData>(origin, nouv, commun );
		}
	}
	else
		nouv = NULL;

	if (origin != NULL)
		delete[] (TData *)origin;
	return nouv;
}

/** Macro redefinissant les fonction ReallocMemory et MemCopy pour des types non objets de façon plus efficace
 * @ingroup util */
#define FASTBASICARRAY(Type) \
	template <> \
		inline Type * ReallocMemory<Type>( const Type * origin, \
																			 const int oldSize, \
																			 const int newSize, \
																			 const bool preserveContent ) \
		{ \
			Type * newp; \
			if (newSize == 0) \
			{ \
				if (origin != NULL) \
					free( (Type*) origin ); \
				newp = NULL; \
			} \
			else \
			{ \
				newp = (Type*) realloc( (Type*) origin, newSize*sizeof(Type) ); \
				\
				if (newp == NULL) \
				{ \
				 MemoryException e (wxT("Error resizing array")); \
				 RaiseException(e); \
				} \
			} \
			return newp; \
		} \
	template <> \
	 inline void MemCopy<Type>( const Type * source, Type * dest, const int count ) \
	 { \
		memmove( dest, source, count*sizeof(Type)); \
	 }

/** @internal Activation des fonctions mémoires rapides  pour les int
 * @ingroup util */
FASTBASICARRAY(int)
/** @internal Activation des fonctions mémoires rapides  pour les long
 * @ingroup util */
FASTBASICARRAY(long)
/** @internal Activation des fonctions mémoires rapides  pour les double
 * @ingroup util */
FASTBASICARRAY(double)
/** @internal Activation des fonctions mémoires rapides  pour les bool
 * @ingroup util */
FASTBASICARRAY(bool)

#endif
