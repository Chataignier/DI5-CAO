#ifndef ZBUFFER_H_
#define ZBUFFER_H_

#include <Array.h>
#include <Coord2D.h>
#include <Config.h>
#include <float.h>

/** Classe implémentant un Z-buffer
 * @ingroup dessin*/
class ZBuffer
{
private:
	/** Le tableau des profondeurs associés à chaque pixel de la zone de dessin */
	Array< Array<double> > depths;
	/** Booléen indiquant si  la gestion du Z-buffer est active */
	bool enabled;
public:
	/** Le constructeur */
	ZBuffer();
	/** @internal Dimensionnement de la zone de dessin et donc du Z-buffer */
	void SetSize(wxSize size);
	/** Initialise le Z-Buffer (les pixels sont à une profondeur infinie initialement) */
	void Init();
	/** Permet d'activer la gestion du Z-buffer */
	void Enable();
	/** Permet d'activer la gestion du Z-buffer */
	void Disable();
	/** Fonction permettant de déterminer si le pixel (p.x,p.y) peut être remplacé par le point p.
	 * @return true si p doit remplacer le point de même coordonnées (p.x,p.y) selon la règle du Z-buffer
	 * i.e. si p est plus proche de la caméra que le même pixel mais de profondeur depths[x][y]. */
	bool ReplaceCurrent(const Coord2D p);
};

#endif /*ZBUFFER_H_*/
