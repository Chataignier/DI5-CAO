#include <FaceDepthAccessor.h>
#include <DrawableInCameraCoordinates.h>

FaceDepthAccessor::FaceDepthAccessor() :
	index( -1)
{
	;
}
FaceDepthAccessor::FaceDepthAccessor(int _index) :
	index(_index)
{
	;
}
double FaceDepthAccessor::GetValue(const DrawableInCameraCoordinates & drawable)
{
	return drawable.faceDepths.data[index];
}
