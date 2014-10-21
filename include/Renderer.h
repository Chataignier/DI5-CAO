#ifndef RENDERER_H_
#define RENDERER_H_

#include <Buffer.h>
#include <Renderable.h>
#include <Config.h>
#include <Light.h>
#include <ZBuffer.h>

class Panel3D;
class Engine;

/** Une classe dessinant une scène sur un buffer de pixel
 * @ingroup dessin */
class Renderer
{
private:
	/** @internal Les deux buffers permettant de gérer un double buffering */
	Buffer buffers[2];
	/** @internal Le buffer sur lequel on peut dessiner */
	int currentBuffer;
	/** @internal Le dernier buffer qui a été dessiné et que l'on peut afficher à tous moments */
	int lastBufferAvailiable;
	/** @internal L'objet widget propriétaire */
	Panel3D * owner;
	/** Le moteur de rendu associé */
	Engine * engine;
	/** @internal La taille en pixel de la zone de dessin */
	wxSize size;
public:
	/** La largeur en pixel de la zone de dessin */
	int width;
	/** La hauteur en pixel de la zone de dessin */
	int height;

	/** Le renderable à dessiner */
	Renderable renderable;
	/** Le drawable à dessiner */
	Drawable * drawable; // pointe vers le Drawable de l'engine associé
	/** Le drawable dans le repère caméra à dessiner */
	DrawableInCameraCoordinates * effectiveDrawable; // pointe vers le DrawableInCameraCoordinates de l'engine associé
	/** Le buffer sur lequel on doit dessiner */
	Buffer * buffer;
public:
	/** Les type de rendu */
	enum EMode
	{
		Filaire,
		FilaireCache,
		FacePleine,
		Lambert,
		Gouraud,
		Phong,
		FacePleineZBuffer,
		LambertZBuffer,
		GouraudZBuffer,
		PhongZBuffer
	};
public:
	EMode mode; /**< Le mode de rendu à effectuer */
	AmbientLight ambientLight; /**< La lumière ambiante */
	PointLight pointLight; /**< Le point lumineux */
	bool current; /**< @internal Booléen indiquant si le mode courant de rendu est le rendu principale et donc dessine une croix verte */
public:
public:
	/** Le constructeur */
	Renderer(Panel3D * _owner, Engine * _engine);
	/** Le destructeur */
	~Renderer();
	/** @internal Dessine le dernier buffer disponible sur le DC (Device context) */
	void DrawBufferOnDC(wxDC & dc);
	/** @internal Définit les dimension des buffers */
	void SetSize(wxSize _size);
	/** Effectue les calculs nécessaire au dessin de la scène puis appele la méthode Draw pour dessiner */
	void ReDraw();

	/** Dessine la scène en appellant une des méthodes DrawXX */
	void Draw();
	/** Dessine la scène en mode filaire */
	void DrawFilaire();
	/** Dessine la scène en mode filaire mais en éliminant les faces cachées */
	void DrawFilaireCache();
	/** Dessine la scène en remplissant les triangles en ayant éliminé les faces cachées mais en ne tenant pas compte de l'éclairage */
	void DrawFacePleine();
	/** Idem DrawFacePleine sauf que l'on considère maintenant le modèle d'illumination simple
	 * @see light
	 * @ingroup light */
	void DrawLambert();
	/** Idem DrawFacePleine sauf que l'on considère maintenant le modèle d'illumination de Gouraud
	 * @see light
	 * @ingroup light */
	void DrawGouraud();
	/** Idem DrawFacePleine sauf que l'on considère maintenant le modèle d'illumination de Phong
	 * @see light
	 * @ingroup light */
	void DrawPhong();
};

#endif /*RENDERER_H_*/
