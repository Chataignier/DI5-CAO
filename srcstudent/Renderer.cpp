#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire() {
    Face * currentFace;

    for(int face = 0; face < drawable->faces.size; ++face){
        currentFace = &drawable->faces.data[face];

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
                             drawable->faceColors.data[face],
                             drawable->faceColors.data[face]);
            }
        }
    }

}
void Renderer::DrawFilaireCache() {
    Face * currentFace;

    for(int face = 0; face < effectiveDrawable->sortedVisibleFaces.size; ++face){
        currentFace = &drawable->faces.data[effectiveDrawable->sortedVisibleFaces.data[face].index];

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
                             drawable->faceColors.data[face],
                             drawable->faceColors.data[face]);
            }
        }
    }

}
void Renderer::DrawFacePleine()
{
	// compléter ici
}

void Renderer::DrawLambert()
{
	// compléter ici
}
void Renderer::DrawGouraud()
{
	// compléter ici
}
void Renderer::DrawPhong()
{
	// compléter ici
}
