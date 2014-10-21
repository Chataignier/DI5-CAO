#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <DrawableInCameraCoordinates.h>

/** Classe contenant toutes les données spécifiques à l'objet  pour une zone de dessin
 * @ingroup data */
class Renderable
{
public:
	/** Les points 2D (x,y,profondeur) des sommets de l'objet par rapport à la zone de dessin */
	Array<Coord2D> points2D;
public:
	/** Calcule des informations spécifiques à une zone de dessin à partir des informations de l'objet dans le repère caméra */
	void ComputeRenderable(const DrawableInCameraCoordinates & drawable,
			const wxSize & screen);
};

#endif /*RENDERABLE_H_*/
