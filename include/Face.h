#ifndef FACE_H_
#define FACE_H_

/** Une face/un triangle
 * @ingroup data */
class Face
{
public:
	/** L'indice du premier sommet (par rapport à la liste des points d'un Drawable, DrawableInCameraCoordinates, Renderable */
	unsigned int index1;
	/** L'indice du deuxième sommet (par rapport à la liste des points d'un Drawable, DrawableInCameraCoordinates, Renderable */
	unsigned int index2;
	/** L'indice du troisième sommet (par rapport à la liste des points d'un Drawable, DrawableInCameraCoordinates, Renderable */
	unsigned int index3;
public:
	/** Le constructeur */
	Face() :
		index1( 0), index2( 0), index3( 0)
	{
		;
	}
	/** Le constructeur */
	Face(unsigned int _index1, unsigned int _index2, unsigned int _index3) :
		index1(_index1), index2(_index2), index3(_index3)
	{
		;
	}
};

#endif /*FACE_H_*/
