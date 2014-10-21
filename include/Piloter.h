#ifndef PILOTER_H_
#define PILOTER_H_

#include <Config.h>
#include <Engine.h>

/** Un widget d'affichage gérant la manipulation de la scène (déplacement, rotation, ...)
 * @ingroup widgets */
class Piloter : public wxPanel
{
public:
	/** Le constructeur */
	Piloter(wxWindow* parent, Engine * engine);

	/** @internal Fonction callback utilisée pour l'animation de la rotation. Cela permet de n'appliquer la rotation
	 * éventuelle de l'objet que si l'objet à pu déjà être dessiné une fois depuis le dernier mouvement. */
	void AutoRotateCallBack();

	/** @internal Gestion des événements */
	DECLARE_EVENT_TABLE();
public:
	/** Le moteur de rendu que l'objet doit piloter */
	Engine * engine;
	/** Des variables de règlage définissant les pas de déplacements */
	double positionStep;
	/** Des variables de règlage définissant les pas de déplacements */
	int rotationStep;
	/** Variable indiquant si on est en mode rotation automatique */
	bool autorotate;
private:
	/** @internal une zone de texte */
	wxStaticText *modele;
	/** @internal une zone de texte */
	wxStaticText *status;
	/** @internal une zone de texte */
	wxStaticText *methode;
	/** @internal le numéro du modèle en cours  */
	int idmodel;
	/** @internal l'heure de la dernière demande de redessin de la scène  */
	wxDateTime lastTime;
private:
	void OnXP(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnXM(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnYP(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnYM(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnZP(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnZM(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnCenter(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnAutoCenter(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnAutoRotate(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnRotateXP(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnRotateXM(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnRotateYP(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnRotateYM(wxCommandEvent & event);/**< @internal Méthode répondant à un événement */
	void OnRotateZP(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnRotateZM(wxCommandEvent & event); /**<@internal Méthode répondant à un événement */
	void OnNextModel(wxCommandEvent &event); /**< @internal Méthode répondant à un événement */
	void OnNextMethod(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnKaleidoscope(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void OnSave(wxCommandEvent & event); /**< @internal Méthode répondant à un événement */
	void Update(); /**< @internal Méthode répondant à un événement */
	void OnIdle(wxIdleEvent & event); /**< @internal Méthode répondant à un événement */
};

#endif /*PILOTER_H_*/
