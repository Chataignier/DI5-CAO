#ifndef MAINFRAME_H_
#define MAINFRAME_H_

#include <Config.h>
#include <Panel3D.h>
#include <Engine.h>

/** La fenêtre principale de l'application
 * @ingroup widgets */
class MainFrame : public wxFrame
{
public:
	Panel3D * panel; /**< variable pointant vers le panel d'affichage principal */
	Panel3D * miniPanels[10]; /**< variable pointant vers les mini panels d'affichage */
	Engine engine; /**< le moteur de rendu */
	/** Booléen indiquant si on est en mode démo ou non */
	bool demoMode;
public:
	/** Le constructeur */
	MainFrame(bool _demoMode);
	/** Le destructeur */
	~MainFrame();
};


#endif /*MAINFRAME_H_*/
