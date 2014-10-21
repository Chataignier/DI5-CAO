#include <ZBuffer.h>

/** Initialise le Z-Buffer (les pixels sont à une profondeur infinie initialement) */
void ZBuffer::Init()
{
    // completer ici : initialisation du buffer des profondeurs
}

/** Fonction permettant de déterminer si le pixel (p.x,p.y) peut être remplacé par le point p.
	 * @return true si p doit remplacer le point de même coordonnées (p.x,p.y) selon la règle du Z-buffer
	 * i.e. si p est plus proche de la caméra que le même pixel mais de profondeur depths[x][y]. */
bool ZBuffer::ReplaceCurrent(const Coord2D p)
{
    // completer ici : retourne true si p doit remplacer le point de même coordonnées (p.x,p.y) selon les règles du Z-buffer
    // par defaut, on remplace toujours
    return true;
}
