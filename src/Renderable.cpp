#include <Renderable.h>
#include <FastMath.h>

void Renderable::ComputeRenderable(
		const DrawableInCameraCoordinates & drawable, const wxSize & screen)
{
	int width = screen.GetWidth();
	int height = screen.GetHeight();
	points2D.Clear();
	points2D.Reserve(drawable.points.size);

	for (int i = 0; i < drawable.points.size; ++i )
	{
		Coord3D p = drawable.pointsNormalized.data[i];

		// profondeur du points normalisé sur [0;1] si dans [nearplan;farplan] : dmax*(p.x - dmin) / (deltaX*p.x)
		// projection sur le plan : (x,y)
		// 3D	=>	2D
		// x	=> depth
		// y	=> y
		// z	=> x
		points2D.PushBack(Coord2D(FastMath::Round(width*p.z), FastMath::Round(height
				*p.y), p.x) );
	}
}

