#include <ZBuffer.h>

/** Initialise le Z-Buffer (les pixels sont à une profondeur infinie initialement) */
void ZBuffer::Init()
{
    if(enabled) {
        for(int i = 0; i < depths.size; i++) {
            for(int j = 0; j < depths.data[i].size; j++) {
                //Initialisation au nombre double maximum.
                depths.data[i].data[j] = DBL_MAX;
            }
        }
    }
}

/** Fonction permettant de déterminer si le pixel (p.x,p.y) peut être remplacé par le point p.
	 * @return true si p doit remplacer le point de même coordonnées (p.x,p.y) selon la règle du Z-buffer
	 * i.e. si p est plus proche de la caméra que le même pixel mais de profondeur depths[x][y]. */
bool ZBuffer::ReplaceCurrent(const Coord2D p)
{
    if(enabled) {
        //On vérifie si l'on sort de notre liste de liste depths
        if(p.y >= 0 && p.x >= 0 && p.x < depths.size && p.y < depths.data[p.x].size) {
            //On verifie sur le point est plus proche
            return (depths.data[p.x].data[p.y] > p.depth);
        }
    }
    return true;

}
