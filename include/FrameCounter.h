#ifndef FRAMECOUNTER_H_
#define FRAMECOUNTER_H_

/** @internal Classe utilitaire permettant de compter le nombre de fenêtre ouverte
 * et de terminer l'application si toutes les fenêtres sont fermées
 * @ingroup widgets */
class FrameCounter
{
private:
	/** @internal Le compteur de fenêtre */
	static int frameCount;
public:
	/** @internal Incrémente le compteur de fenêtre */
	static void IncFrameCount();
	/** @internal Décrémente le comtpeur de fenêtre */
	static void DecFrameCount();
};

#endif /*FRAMECOUNTER_H_*/
