#include <DrawableInCameraCoordinates.h>
#include <FastMath.h>
#include <QuickSort.h>

void DrawableInCameraCoordinates::Compute(const Drawable & drawable,
		const Camera & camera, const Rotation & drawableRotation)
{
	points.Clear();
	pointNormals.Clear();
	faceNormals.Clear();
	faceDepths.Clear(); // profondeur i.e. Z en coord caméra
	pointsNormalized.Clear();
	faceVisibles.Clear(); // indique si une face est visible
	sortedVisibleFaces.Clear();

	ComputeInCameraCoordinates(drawable, camera, drawableRotation);
	ComputeVisibilityOfFaces(drawable);
	SortVisibleFaces(drawable);
}

void DrawableInCameraCoordinates::ComputeInCameraCoordinates(
		const Drawable & drawable, const Camera & camera,
		const Rotation & drawableRotation)
{
	int i, j;
	Rotation rot = camera.orientation * drawableRotation;
	Coord3D pos = camera.position;

	// projection / normalisation des points
	double dmin = camera.nearplan;
	double dmax = camera.farplan;
	double deltaY = dmin * FastMath::fastTan(camera.upwardAngle);
	double deltaZ = camera.aspectRatio * deltaY;
	Coord3D p;

	points.Reserve(drawable.points.size);
	pointsNormalized.Reserve(drawable.points.size);
	pointNormals.Reserve(drawable.points.size);

	faceNormals.Reserve(drawable.faces.size);
	faceDepths.Reserve(drawable.faces.size);

	for (i = 0; i < drawable.points.size; ++i)
	{
		p = pos + rot * drawable.points.data[i];
		points.PushBack(p);

		// profondeur du points normalisé sur [0;1] si dans [nearplan;farplan] : dmax*(p.x - dmin) / (deltaX*p.x)
		// projection sur le plan : (y,z), profondeur originale x
		// 3D	=>	2D
		// x	=> depth	: dans [0;1]
		// y	=> y		: dans [0;1]
		// z	=> x		: dans [0;1]
		pointsNormalized.PushBack(Coord3D(dmax*(p.x - dmin) / ((dmax - dmin)
				*p.x), (1.0 - dmin*p.y/ (p.x*deltaY)) / 2., (1.0 + dmin*p.z
				/ (p.x*deltaZ)) / 2.) );
	}

	for (i = 0; i < drawable.faces.size; ++i)
	{
		// la camera regarde dans la direction X
		faceDepths.PushBack(points.data[ drawable.faces.data[i].index1].x
				+points.data[ drawable.faces.data[i].index2].x
				+points.data[ drawable.faces.data[i].index3].x);
	}

	// calculs des normales
	for (i = 0; i < drawable.faces.size; i++)
	{
		Face f = drawable.faces.data[ i ];
		Coord3D normal = (points.data[ f.index2 ] - points.data[ f.index1 ])
				^ (points.data[ f.index3 ] - points.data[ f.index1 ]);
		normal.Normalize();
		faceNormals.PushBack(normal);
	}

	// ----- Calcul de la pseudo-normale pour chaque sommet ( Gouraud )
	pointNormals.Resize(points.size);
	pointNormals.Fill(Coord3D(0, 0, 0));

	for (j = 0; j < drawable.faces.size; j++)
	{
		Face f = drawable.faces.data[ j ];
		pointNormals.data[f.index1] += faceNormals.data[j];
		pointNormals.data[f.index2] += faceNormals.data[j];
		pointNormals.data[f.index3] += faceNormals.data[j];
	}

	for (i = 0; i < points.size; i++)
		pointNormals.data[i].Normalize();
}

// attention : le test doit se faire sur (x,y) après projection i.e. en utilisant (z,y) de pointsNormalized et faisant attention au changement d'orientation du repère
bool DrawableInCameraCoordinates::IsFaceVisible(const Drawable & drawable,
		const int face)
{
	// attention : il faut calculer la visibilité par rapport au triangle projeté et non pas par rapport au point dans l'espace pour avoir une précision suffisante
	Face f = drawable.faces.data[face];
	Coord3D AB = pointsNormalized.data[f.index2]
			- pointsNormalized.data[f.index1];
	Coord3D AC = pointsNormalized.data[f.index3]
			- pointsNormalized.data[f.index1];

	double x1 = AB.z;
	double y1 = AB.y;
	double x2 = AC.z;
	double y2 = AC.y;

	// composante Z de (x1,y1)^(x2,y2) : x1 * y2 - y1 * x2
	// le produit scalaire avec (1,0,0) doit être négativ ou nul pour que la face soit visible
	return (x1*y2 - y1*x2 <= 0);

	// de façon équilavente, en prenant en compte l'inversion du rôle de (y,z) de pointsNormalized en (y,x) d'un vecteur
	// return Coord3D(1, 0, 0) * (AB ^ AC) >= 0;
	return true;
}

void DrawableInCameraCoordinates::ComputeVisibilityOfFaces(
		const Drawable & drawable)
{
	faceVisibles.Clear();
	for (int i = 0; i < drawable.faces.size; ++i)
		faceVisibles.PushBack(IsFaceVisible(drawable, i));
}

void DrawableInCameraCoordinates::SortVisibleFaces(const Drawable & drawable)
{
	sortedVisibleFaces.Clear();
	for (int i = 0; i < drawable.faces.size; ++i)
		if (faceVisibles.data[i])
			sortedVisibleFaces.PushBack(FaceDepthAccessor(i) );
	Sort(sortedVisibleFaces, *this);

}

