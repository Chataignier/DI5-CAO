#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire() {
    Face * currentFace;

    // Pour chacune des faces de la formes à représenter
    for(int face = 0; face < drawable->faces.size; ++face){
        // On récupère la face courante
        currentFace = &drawable->faces.data[face];

        // On récupère les indices des trois points du triangles dans la grande liste de points
        unsigned int indexFace[3] = {currentFace->index1,
                                     currentFace->index2,
                                     currentFace->index3};

        // Pour chacun des côtés du triangle
        for(int point = 0; point < 3; ++point){
            if(!drawable->colorOnFace){ // Si la couleur est sur les points
                buffer->DrawLine(
                             renderable.points2D.data[indexFace[point]], // Le point courant
                             renderable.points2D.data[indexFace[(point + 1) % 3]], // Le suivant
                             drawable->pointColors.data[indexFace[point]],
                             drawable->pointColors.data[indexFace[(point + 1) % 3]]);
            } else {
                buffer->DrawLine(
                             renderable.points2D.data[indexFace[point]],
                             renderable.points2D.data[indexFace[(point + 1) % 3]],
                             drawable->faceColors.data[face],
                             drawable->faceColors.data[face]);
            }
        }
    }

}

void Renderer::DrawFilaireCache() {
    Face * currentFace;

    // Pour chacune des faces
    for(int face = 0; face < effectiveDrawable->sortedVisibleFaces.size; ++face){

        // On rcupère l'index de la face
        int index = effectiveDrawable->sortedVisibleFaces.data[face].index;
        currentFace = &drawable->faces.data[index];

        // On effectue la même chose que pour la méthode précédente
        unsigned int indexFace[3] = {currentFace->index1,
                                     currentFace->index2,
                                     currentFace->index3};

        for(int point = 0; point < 3; ++point){
            if(!drawable->colorOnFace){
                buffer->DrawLine(
                             renderable.points2D.data[indexFace[point]],
                             renderable.points2D.data[indexFace[(point + 1) % 3]],
                             drawable->pointColors.data[indexFace[point]],
                             drawable->pointColors.data[indexFace[(point + 1) % 3]]);
            } else {
                buffer->DrawLine(
                             renderable.points2D.data[indexFace[point]],
                             renderable.points2D.data[indexFace[(point + 1) % 3]],
                             drawable->faceColors.data[index],
                             drawable->faceColors.data[index]);
            }
        }
    }
}

void Renderer::DrawFacePleine() {
	Face * currentFace;
	int indexFace;
    // On effectue la même chose que dans la méthode précédente sauf qu'on appelle la méthode drawFilled triangle sur la face courante

    for(int face = 0; face < effectiveDrawable->sortedVisibleFaces.size; ++face){
        indexFace = effectiveDrawable->sortedVisibleFaces.data[face].index;
        currentFace = &drawable->faces.data[indexFace];

        if(!drawable->colorOnFace){
            buffer->DrawFilledTriangle(renderable.points2D.data[currentFace->index1],
                                   renderable.points2D.data[currentFace->index2],
                                   renderable.points2D.data[currentFace->index3],
                                   drawable->pointColors.data[currentFace->index1],
                                   drawable->pointColors.data[currentFace->index2],
                                   drawable->pointColors.data[currentFace->index3]);
        } else {
            buffer->DrawFilledTriangle(renderable.points2D.data[currentFace->index1],
                                   renderable.points2D.data[currentFace->index2],
                                   renderable.points2D.data[currentFace->index3],
                                   drawable->faceColors.data[indexFace],
                                   drawable->faceColors.data[indexFace],
                                   drawable->faceColors.data[indexFace]);
        }
    }
}

void Renderer::DrawLambert()
{
    Face * currentFace;
    int indexFace;

    for(int face = 0; face < effectiveDrawable->sortedVisibleFaces.size; ++face){
        //Index de la liste des faces visibles
        indexFace = effectiveDrawable->sortedVisibleFaces.data[face].index;

        //La face visible
        currentFace = &drawable->faces.data[indexFace];

        //On calcul le point central de la face
        Coord3D * p1 = &effectiveDrawable->points.data[currentFace->index1];
        Coord3D * p2 = &effectiveDrawable->points.data[currentFace->index2];
        Coord3D * p3 = &effectiveDrawable->points.data[currentFace->index3];

        Coord3D meanPoint((p1->x + p2->x + p3->x)/3, (p1->y + p2->y + p3->y)/3, (p1->z + p2->z + p3->z)/3);

        //Calcul de la couleur de la face par rapport a l'eclairage
        Color c = pointLight.GetColor(meanPoint, effectiveDrawable->faceNormals.data[indexFace]) + ambientLight.ambientColor;

         if(!drawable->colorOnFace){
                //Mode kaleidoscope
                buffer->DrawFilledTriangle(renderable.points2D.data[currentFace->index1],
                                   renderable.points2D.data[currentFace->index2],
                                   renderable.points2D.data[currentFace->index3],
                                   c * drawable->pointColors.data[currentFace->index1],
                                   c * drawable->pointColors.data[currentFace->index2],
                                   c * drawable->pointColors.data[currentFace->index3]);

         } else {
            c = drawable->faceColors.data[indexFace] * c;

            buffer->DrawFilledTriangle(renderable.points2D.data[currentFace->index1],
                                   renderable.points2D.data[currentFace->index2],
                                   renderable.points2D.data[currentFace->index3],
                                   c,
                                   c,
                                   c);
         }
    }
}
void Renderer::DrawGouraud()
{
    Face * currentFace;
	int indexFace;

    for(int face = 0; face < effectiveDrawable->sortedVisibleFaces.size; ++face){
        indexFace = effectiveDrawable->sortedVisibleFaces.data[face].index;
        currentFace = &drawable->faces.data[indexFace];

        // Récupération des couleurs selon les normales
        Color c1 = pointLight.GetColor(effectiveDrawable->points.data[currentFace->index1],
                                       effectiveDrawable->pointNormals.data[currentFace->index1]) + ambientLight.ambientColor;
        Color c2 = pointLight.GetColor(effectiveDrawable->points.data[currentFace->index2],
                                       effectiveDrawable->pointNormals.data[currentFace->index2]) + ambientLight.ambientColor;
        Color c3 = pointLight.GetColor(effectiveDrawable->points.data[currentFace->index3],
                                       effectiveDrawable->pointNormals.data[currentFace->index3]) + ambientLight.ambientColor;

        // On calcule les couleurs effectives
        if(!drawable->colorOnFace){
            c1 = drawable->pointColors.data[currentFace->index1] * c1;
            c2 = drawable->pointColors.data[currentFace->index2] * c2;
            c3 = drawable->pointColors.data[currentFace->index3] * c3;
        } else {
            c1 = drawable->faceColors.data[indexFace] * c1;
            c2 = drawable->faceColors.data[indexFace] * c2;
            c3 = drawable->faceColors.data[indexFace] * c3;
        }

        // Affichage du triangle
        buffer->DrawFilledTriangle(renderable.points2D.data[currentFace->index1],
                                   renderable.points2D.data[currentFace->index2],
                                   renderable.points2D.data[currentFace->index3],
                                   c1,
                                   c2,
                                   c3);
    }
}
void Renderer::DrawPhong()
{
    Face * currentFace;
	int indexFace;

    // Pour chacune des faces
    for(int face = 0; face < effectiveDrawable->sortedVisibleFaces.size; ++face){
        indexFace = effectiveDrawable->sortedVisibleFaces.data[face].index;
        currentFace = &drawable->faces.data[indexFace];

        if(!drawable->colorOnFace){
            buffer->DrawPhongTriangle(renderable.points2D.data[currentFace->index1],
                                   renderable.points2D.data[currentFace->index2],
                                   renderable.points2D.data[currentFace->index3],
                                   drawable->pointColors.data[currentFace->index1],
                                   drawable->pointColors.data[currentFace->index2],
                                   drawable->pointColors.data[currentFace->index3],
                                   effectiveDrawable->points.data[currentFace->index1],
                                   effectiveDrawable->points.data[currentFace->index2],
                                   effectiveDrawable->points.data[currentFace->index3],
                                   effectiveDrawable->pointNormals.data[currentFace->index1],
                                   effectiveDrawable->pointNormals.data[currentFace->index2],
                                   effectiveDrawable->pointNormals.data[currentFace->index3],
                                   ambientLight,
                                   pointLight
                                   );
        } else {
            buffer->DrawPhongTriangle(renderable.points2D.data[currentFace->index1],
                                   renderable.points2D.data[currentFace->index2],
                                   renderable.points2D.data[currentFace->index3],
                                   drawable->faceColors.data[indexFace],
                                   drawable->faceColors.data[indexFace],
                                   drawable->faceColors.data[indexFace],
                                   effectiveDrawable->points.data[currentFace->index1],
                                   effectiveDrawable->points.data[currentFace->index2],
                                   effectiveDrawable->points.data[currentFace->index3],
                                   effectiveDrawable->pointNormals.data[currentFace->index1],
                                   effectiveDrawable->pointNormals.data[currentFace->index2],
                                   effectiveDrawable->pointNormals.data[currentFace->index3],
                                   ambientLight,
                                   pointLight
                                   );
        }
    }
}
