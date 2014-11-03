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

void Renderer::DrawFacePleine() {
	Face * currentFace;
	int indexFace;

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
