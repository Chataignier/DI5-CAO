#ifndef DRAWABLEINCAMERACOORDINATES_H_
#define DRAWABLEINCAMERACOORDINATES_H_

#include <Array.h>
#include <Coord3D.h>
#include <Camera.h>
#include <Rotation.h>
#include <Drawable.h>
#include <FaceDepthAccessor.h>

/** Une classe stockant les informations d'un objet dans le repère caméra
 * @ingroup data */
class DrawableInCameraCoordinates
{
public:
	/** Les points 3D de l'objet dans le repère caméra. <br>
	 * @remark <br>
	 * 		p.x correspond à l'axe de la direction de la caméra <br>
	 *		p.y correspond à la direction vers le haut/dessus de la caméra<br>
	 *		p.z correspond à la direction vers la droite de la caméra */
	Array<Coord3D> points;
	/** Les normales associées à chaque point de l'objet exprimées dans le repère caméra */
	Array<Coord3D> pointNormals;
	/** Les normales aux faces exprimées dans le repère caméra */
	Array<Coord3D> faceNormals;
	/** La profondeur des faces exprimée par rapport à l'axe dans lequel regarde la caméra i.e. 10 est plus loin de la caméra que 5. */
	Array<double> faceDepths;
	/** @internal Les coordonnées des points de l'objet exprimées dans le repère caméra mais sous une forme normalisées. <br>
	 * La profondeur du points est normalisée sur [0;1] si elle est dans [nearplan;farplan] : dmax*(p.x - nearplan) / (deltaX*p.x) avec deltaX=farplan-nearplan. <br>
	 *
	 * Coordonnées 3D	=> Coordonnées 3D normalisées : <br>
	 * x	=> depth	: dans [0;1] <br>
	 * y	=> y		: dans [0;1] <br>
	 * z	=> x		: dans [0;1] <br>
	 */
	Array<Coord3D> pointsNormalized;
	/** Booléen indiquant si une face est visible */
	Array<bool> faceVisibles;
	/** Liste des faces visibles triées par ordre de profondeur croissante (de la plus proche à la plus éloignée) */
	Array<FaceDepthAccessor> sortedVisibleFaces;
private:
	/** @internal Calcule les informations de l'objet drawable dans le repère caméra définit par camera et en appliquant
	 * la rotation drawableRotation à l'objet avant le changement de repère du repère globale vers le repère caméra.
	 *
	 * drawable ===== drawableRotation ====> drawable avec rotation ===== camera ====> drawable dans le repère caméra */
	void ComputeInCameraCoordinates(const Drawable & drawable,
			const Camera & camera, const Rotation & drawableRotation);
	/** @internal Calcule la visibilité des faces */
	void ComputeVisibilityOfFaces(const Drawable & drawable);
	/** @internal Détermine si une face est visible où non par rapport à la caméra (orientation de sa normale par rapport à l'axe de la caméra) */
	bool IsFaceVisible(const Drawable & drawable, const int face);
	/** @internal Trie les faces visibles */
	void SortVisibleFaces(const Drawable & drawable);
public:
	/** Calcule les informations de l'objet drawable dans le repère caméra définit par camera et en appliquant
	 * la rotation drawableRotation à l'objet avant le changement de repère du repère globale vers le repère caméra.
	 *
	 * drawable ===== drawableRotation ====> drawable avec rotation ===== camera ====> drawable dans le repère caméra
	 *
	 * Les normales et la visibilité des faces sont calculées. */
	void Compute(const Drawable & drawable, const Camera & camera,
			const Rotation & drawableRotation);
};

#endif /*DRAWABLEINCAMERACOORDINATES_H_*/
