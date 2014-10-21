#ifndef FACEDEPTHACCESSOR_H_
#define FACEDEPTHACCESSOR_H_

class DrawableInCameraCoordinates;

/** Classe permettant de récupérer la valeur de profondeur associée à une face.
 * Cette classe est utilisée pour le tri des faces visibles.
 * @ingroup util */
class FaceDepthAccessor
{
public:
	/** L'indice de la face par rapport à un Drawable ou DrawableInCameraCoordinates */
	int index;
public:
	/** Le constructeur */
	FaceDepthAccessor();
	/** Le constructeur */
	FaceDepthAccessor(int _index);
	/** Permet d'obtenir la profondeur associée à la face index dans le repère caméra */
	double GetValue(const DrawableInCameraCoordinates & drawable);
};

#endif /*FACEDEPTHACCESSOR_H_*/
