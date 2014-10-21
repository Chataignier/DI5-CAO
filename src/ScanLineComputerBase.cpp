
#include <ScanLineComputer.h>
#include <Buffer.h>
#include <FastMath.h>
#include <limits.h>

/* ---------------------------------------------------------------------------------------------------
   Implementation inline pour ne garder dans le CPP que ce qui est à modifier
   ---------------------------------------------------------------------------------------------------*/


ScanLineComputer::ScanLineComputer()
{}

void ScanLineComputer::SetSize(wxSize size)
{
	Array<double> tmp;
	tmp.Resize(3);

	height = size.GetHeight();
	width = size.GetWidth();
	left.Resize(height);
	right.Resize(height);
	leftweight.Resize(height);
	rightweight.Resize(height);
	leftweight.Fill(tmp);
	rightweight.Fill(tmp);
}

void ScanLineComputer::Init()
{
	ymin = INT_MAX;
	ymax = INT_MIN;
	left.Fill(INT_MAX);
	right.Fill(INT_MIN);
	for (int i = 0; i < height; ++i)
	{
		leftweight.data[i].Fill(0);
		rightweight.data[i].Fill(0);
	}
}

void ScanLineComputer::Compute(const Coord2D p1, const Coord2D p2,
															 const Coord2D p3)
{
	// on transmet les numéros de sommets associés aux bordures afin que AddPoint puisse calculer les poids correctement
	AddEdge(p1, p2, 0, 1);
	AddEdge(p2, p3, 1, 2);
	AddEdge(p3, p1, 2, 0);

	// au final, pour chaque point délimitant la zone du scan line, on a :
	// limite gauche (x,y)=leftweight.data[y].data[0]*p1 + leftweight.data[y].data[1]*p2 + leftweight.data[y].data[2]*p3
	// limite droite (x,y)=rightweight.data[y].data[0]*p1 + rightweight.data[y].data[1]*p2 + rightweight.data[y].data[2]*p3
}

// ATTENTION : y doit être dans l'intervalle [0;height[ pour que cela fonctionne
// ATTENTION : il n'y a pas de contrainte particulière sur le domaine de valeur de x
void ScanLineComputer::AddPoint(const int x, const int y, const Coord2D p1,
																const Coord2D p2, const int index1, const int index2)
{
	// y est la ligne
	// si le point est plus à gauche que celui que l'on connait pour la ligne y
	if (x <= left.data[y])
	{
		left.data[y] = x; // on remplace la limite gauche
		leftweight.data[y].data[0] = 0; // on fixe initialement les poids à 0
		leftweight.data[y].data[1] = 0; // on fixe initialement les poids à 0
		leftweight.data[y].data[2] = 0; // on fixe initialement les poids à 0

		// On calcule les poids associés à ce nouveau point de manière à ce que (x,y)=w1*p1+w2*p2
		leftweight.data[y].data[index1] = 1 - p1.Distance(Coord2D(x, y))
																			/ p1.Distance(p2);
		leftweight.data[y].data[index2] = 1 - leftweight.data[y].data[index1];
	}
	// si le point est plus à droite que celui que l'on connait pour la ligne y
	if (x >= right.data[y])
	{
		right.data[y] = x; // on remplace la limite droite
		rightweight.data[y].data[0] = 0; // on fixe initialement les poids à 0
		rightweight.data[y].data[1] = 0; // on fixe initialement les poids à 0
		rightweight.data[y].data[2] = 0; // on fixe initialement les poids à 0

		// On calcule les poids associés à ce nouveau point de manière à ce que (x,y)=w1*p1+w2*p2
		rightweight.data[y].data[index1] = 1 - p1.Distance(Coord2D(x, y))
																			 / p1.Distance(p2);
		rightweight.data[y].data[index2] = 1 - rightweight.data[y].data[index1];
	}
	// on met a jours les limites haut/bas
	if (y < ymin)
		ymin = y;
	if (y > ymax)
		ymax = y;
}
