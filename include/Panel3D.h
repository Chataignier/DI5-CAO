#ifndef PANEL3D_H_
#define PANEL3D_H_

#include <Config.h>
#include <Renderer.h>
#include <Engine.h>

/**Un widget graphique permettant d'afficher une zone de dessin
 * @ingroup widgets */
class Panel3D : public wxPanel
{
public:
	/** Le constructeur */
	Panel3D(wxWindow* parent, Engine * engine, Renderer::EMode mode);
	/** @internal Gestion des événements */
	DECLARE_EVENT_TABLE();
private:
	/** @internal Méthode appellée lorsque le widget est redimensionné */
	void OnSize(wxSizeEvent& event);
	/** @internal Méthode appellée lorsque le widget doit être redessiné */
	void OnPaint(wxPaintEvent& event);
	/** @internal Méthode appellée lorsque le fond de la zone de dessin du widget doit être effacé */
	void OnEraseBackGround(wxEraseEvent& event);
public:
	/** Le renderer associé au widget et s'occupant de dessiner */
	Renderer renderer;
};

#endif /*PANEL3D_H_*/
