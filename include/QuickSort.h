#ifndef QUICKSORT_H_
#define QUICKSORT_H_

/** @internal Implémentation d'un QuickSort avec transmission de param à chaque élément du tableau pour obtenir sa valeur
 * @ingroup util */
template<class TElement, class TParam> void Sort(Array<TElement> & array,
		const TParam & param)
{
	Sort(array, param, 0, array.size - 1);
}
/** @internal Implémentation d'un QuickSort avec transmission de param à chaque élément du tableau pour obtenir sa valeur
 * @ingroup util */
template<class TElement, class TParam> void Sort(Array<TElement> & array,
		const TParam & param, int debut, int fin)
{
	int i = debut;
	int j = fin;
	double milieu = array.data[ ( debut + fin ) / 2 ].GetValue(param);
	TElement temp;

	while (i <= j )
	{
		while (array.data[ i ].GetValue(param) > milieu )
			i++;

		while (array.data[ j ].GetValue(param) < milieu )
			j--;

		if (i <= j )
		{
			temp = array.data[i];
			array.data[ i ] = array.data[ j ];
			array.data[ j ] = temp;
			i++;
			j--;
		}
	}

	if (i < fin )
		Sort(array, param, i, fin );

	if (debut < j )
		Sort(array, param, debut, j );
}

#endif /*QUICKSORT_H_*/
