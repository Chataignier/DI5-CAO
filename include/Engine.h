#ifndef ENGINE_H_
#define ENGINE_H_

#include <Drawable.h>
#include <Rotation.h>
#include <DrawableInCameraCoordinates.h>
#include <Camera.h>
#include <Renderer.h>
#include <FastMath.h>

class Panel3D;
class Piloter;

/** La classe principale s'occupant de gérer le dessin d'une scène
 * @ingroup dessin */
class Engine
{
private:
	/** @internal indique qu'il est nécessaire de rafraichir la scène.
	 * Ce booléen est utilisé pour éviter de recalculer la scène en permanance lorsque ce n'est pas nécessaire. */
	bool needUpdates;
public:
	/** L'objet à dessiner dans le repère global */
	Drawable drawable;
	/** La rotation à appliquer à l'objet avant de le dessiner */
	Rotation rot;
	/** L'objet à dessiner dans le repère caméra */
	DrawableInCameraCoordinates effectiveDrawable;
	/** La caméra */
	Camera camera;
	/** @internal Les objets dessinants l'objet. Il peut y en avoir plusieurs.
	 * C'est le cas dans ce programme car on souhaite dessiner plusieurs fois la même scène mais avec des techniques de rendu différentes. */
	Array<Renderer*> renderers;
	/** @internal L'objet chargé de piloter l'évolution de la scène (déplacements, ...) */
	Piloter * piloter;
private:
	/** @internal On interdit l'opérateur d'affectation */
	Engine & operator=( const Engine & e );
	/** @internal on interdit l'opérateur de recopie */
	Engine( const Engine & e );
public:
	/** le constructeur */
	Engine();
	/** le destructeur */
	~Engine();
	/** @internal Permet d'enregistrer un renderer aurpès de l'objet Engine */
	void addRenderer(Renderer * renderer);
	/** Permet d'indiquer au moteur que la scène à changer et qu'il faut donc la recalculer */
	void SetNeedUpdates();

	/** Rafraichit la scène si c'est nécessaire */
	void Refresh();
	/** @internal Calcule la nouvelle scène et demande aux renderers de dessiner la scène */
	void ReDraw();
};

#endif /*ENGINE_H_*/
