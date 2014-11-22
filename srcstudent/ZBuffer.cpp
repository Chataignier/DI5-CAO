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
        if(p.y < depths.size && p.x < depths.data[p.y].size) {
            //On verifie sur le point est plus proche
            if(depths.data[p.y].data[p.x] >= p.depth){
                depths.data[p.y].data[p.x] = p.depth;
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}
