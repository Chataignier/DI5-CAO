#include <Camera.h>
#include <FastMath.h>

void Camera::Set(const Coord3D & _positionInWorld,
		const Rotation & _orientationInWorld)
{
	positionInWorld = _positionInWorld;
	orientationInWorld = _orientationInWorld;
	orientation = orientationInWorld.transpose();
	position = -(orientation * positionInWorld);
}
void Camera::SetFromDrawable(const Drawable & drawable, const double scale,
		const int _upwardAngle)
{
	double d;
	aspectRatio = 4./3.; // on force un format 4/3
	upwardAngle = _upwardAngle;
	nearplan = 10;

	d = FastMath::max(scale * drawable.radius+ nearplan, FastMath::max(scale
			* drawable.radius/ FastMath::fastTan(upwardAngle), scale
			* drawable.radius* aspectRatio / FastMath::fastTan(upwardAngle) ));
	farplan = 2 * d - nearplan;

	int angle = -90; // correction de l'orientation initiale des objets
	Set(Coord3D( -d, 0, 0), Rotation( 1, 0, 0, 0, FastMath::fastCos(angle),
			FastMath::fastSin(angle), 0, -FastMath::fastSin(angle),
			FastMath::fastCos(angle)));

}
