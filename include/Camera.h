#ifndef CAMERA_H_
#define CAMERA_H_

#include <Coord3D.h>
#include <Rotation.h>
#include <Drawable.h>
#include <Config.h>

/** Une classe contenant toutes les informations liées à la caméra.
 * @verbatim
Convention utilisée pour la caméra :
Y
 ^
 |
 |   / X
 |  /
 | /
 |/
 *---------> Z
(X,Y,Z) orthonormé direct
X est la direction vers laquelle la caméra regarde
Y est la direction vers le haut
Z est la direction vers la droite
@endverbatim
@ingroup dessin
 */
class Camera
{
public:
	Coord3D positionInWorld; /**< position de la camera dans le repère du monde */
	Rotation orientationInWorld; /**< rotation de la camera dans le repère du monde */
	Rotation orientation; /**< rotation du repère du monde dans le repère caméra */
	Coord3D position; /**< position du monde dans le repère camera */
	double nearplan; /**< la position du plan near sur l'axe X */
	double farplan; /**< la position du plan far sur l'axe X */
	double aspectRatio; /**< aspect ratio horizontal/vertical Z = ratio * Y */
	int upwardAngle; /**< demi angle vertical du champ de vision en degré */
public:
	/** Calcule les données caméra en fonction de la position et de l'orientation de la caméra dans le repère global */
	void Set(const Coord3D & _positionInWorld,
			const Rotation & _orientationInWorld);
	/** Calcul la position et l'orientation de la caméra pour que l'objet drawable exprimé dans le repère global soit entièrement visible */
	void SetFromDrawable(const Drawable & drawable, const double scale = 1.2,
			const int _upwardAngle = 40);
};

#endif /*CAMERA_H_*/
