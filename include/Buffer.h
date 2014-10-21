#ifndef BUFFER_H_
#define BUFFER_H_

#include <Config.h>
#include <Color.h>
#include <Coord2D.h>
#include <ScanLineComputer.h>
#include <ZBuffer.h>
#include <Light.h>

/** @defgroup dessin Les objets pour le dessin */

/** Une classe représentant une zone de dessin/matrice de pixels
 * @ingroup dessin */
class Buffer
{
private:
	/** @internal Constructeur de recopie interdit */
	Buffer(const Buffer & b);
	/** @internal Affectation interdite */
	Buffer & operator=(const Buffer & b);
private:
	/** @internal la zone de dessin native */
	wxImage data;
public:
	/** La largeur en pixel de la zone de dessin */
	int width;
	/** La hauteur en pixel de la zone de dessin */
	int height;
	/** Un objet contenant toutes les informations utiles du scan line (limites, poids, ...) */
	ScanLineComputer scanLineComputer;
	/** Un objet qui gère le Z-buffer */
	ZBuffer zbuffer;
public:
	/** constructeur */
	Buffer();
	/** @internal Permet d'accèder à l'objet dessin natif */
	wxImage & GetImage();
	/** @internal définit la taille de la zone de dessin */
	void SetSize(wxSize size);
	/** Allume le pixel de coordonnées pos avec la couleur c.
	 * la gestion du Z-buffer peut faire que la couleur d'un pixel n'est pas réellemen changé */
	void SetPoint(const Coord2D & pos, const Color & c);
	/** Efface la zone de dessin */
	void ClearBuffer();
	/** Enregistre la zone de dessin dans un fichier : utile pour faire des captures d'écran */
	bool SaveToFile(const wxString& name) const;

	/** Dessine une ligne de p1 à p2 selon la méthode de Bresenham en tenant compte de la progression de la couleur.
	 * p1 doit être de couleur c1, p2 de couleur c2.
	 * Les points intermédiaires correspondent à une interpolation linéaire entre ces deux couleurs. */
	void DrawLine(const Coord2D p1, const Coord2D p2, const Color c1,
			const Color c2);
	/** Dessine un triangle dont les sommets sont p1,p2,p3 et dont les couleurs de sommets sont respectivement c1,c2,c3.
	 * L'objet scanLineComputer doit être utilisé pour calculer les limites "scanline" du triangle et pour calculer les poids des trois
	 * points associés à chaque point de la bordure du triangle.
	 * L'interpollation des couleurs se fait horizontalement. */
	void DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
			const Coord2D p3, const Color c1, const Color c2, const Color c3);
	/** Dessine un triangle dont les sommets sont p1,p2,p3 et dont les couleurs de sommets sont c1,c2,c3.
	 * posi1,posi2,posi3 sont les coordonnées 3D dans le repère camérades sommets du triangle.
	 * normal1, normal2,normal3 sont les trois normales associées.
	 * ambientLight donne les composantes de la lumière ambiente.
	 * pointLight donne les composantes du point lumineux. */
	void DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
			const Coord2D p3, const Color c1, const Color c2, const Color c3,
			const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
			const Coord3D normal1, const Coord3D normal2,
			const Coord3D normal3, const AmbientLight & ambientLight,
			const PointLight & pointLight);
};


#endif /*BUFFER_H_*/
