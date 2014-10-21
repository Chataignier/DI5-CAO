#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <Array.h>
#include <Coord2D.h>
#include <Coord3D.h>
#include <Color.h>
#include <Face.h>
#include <Rotation.h>

/** @defgroup data Les données de l'objet à dessiner */

/** Une classe stockant les données de l'objet à dessiner dans le repère globale
 * @ingroup data */
class Drawable
{
public:
	/** les coordonnées des points 3D de l'objet */
	Array<Coord3D> points;
	/** les couleurs des points 3D de l'objet */
	Array<Color> pointColors;

	/** Les faces/triangles composant l'objet */
	Array<Face> faces;
	/** La couleur des faces */
	Array<Color> faceColors;
	/** Booléen à vrai si les couleurs de l'objet sont donnés par face ou par point */
	bool colorOnFace; // vrai si les couleurs sont sur les faces, faux si les couleurs sont sur les sommets

	/** Le rayon minimale de la sphère englobant l'objet */
	double radius; // rayon de la bounding sphère enveloppant le drawable

	/** @internal Fonction permettant de charger un fichier de modèle O3D (ancien format) */
	bool LoadFromO3DFile(char *FileName);
private:
	/** @internal Centre l'objet au centre du reprère lobale i.e. aux coordonnées (0,0,0) */
	void CenterObjectToOrigin();
public:
	/** Charge l'objet comprimé */
	void LoadPredefinedComprime();
	/** Charge l'objet canard */
	void LoadPredefinedDuck();
	/** Charge l'objet étoile */
	void LoadPredefinedEtoile();
	/** Charge l'objet noeud */
	void LoadPredefinedNoeud();
	/** Charge l'objet sphère */
	void LoadPredefinedSphere();
	/** Charge l'objet teilleire */
	void LoadPredefinedTeapot();
	/** Chare l'objet tore */
	void LoadPredefinedTore();
	/** Chare l'objet tête (crée par Joachim ALibert et Corentin Sachot) */
	void LoadPredefinedHead();
	/** Chare l'objet polytech (crée par Joachim ALibert et Corentin Sachot) */
	void LoadPredefinedPolytechLogo();


	/** @internal Fonction utile pour la conversion d'un modèle O3D en code C intégrable au programme.
	 * Utile pour éliminer les dépendances à des fichiers de données externes.  */
	void SaveAsCode(char * FileName);
};

#endif /*DRAWABLE_H_*/

