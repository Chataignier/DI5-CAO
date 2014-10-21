#include <Drawable.h>

static const int etoile_nbpoints = 12;
static const double etoile_points[12][3] =
{
{ -247.971375, 180.161713, 0. },
{ 0.000000, 1526.358093, 0. },
{ 247.971375, 180.161713, 0. },
{ 1604.908691, 360.324280, 0. },
{ 401.226746, -291.508026, 0. },
{ 991.887207, -1526.358093, 0. },
{ 0.000000, -583.016907, 0. },
{ -991.887207, -1526.358093, 0. },
{ -401.226746, -291.508026, 0. },
{ -1604.908691, 360.324280, 0. },
{ 0., -161.141907, 253.125 },
{ 0., -161.141907, -253.125 } };
static const int etoile_nbfaces = 20;
static const int etoile_faces[20][3] =
{
{ 10, 1, 0 },
{ 10, 2, 1 },
{ 10, 3, 2 },
{ 10, 4, 3 },
{ 10, 5, 4 },
{ 10, 6, 5 },
{ 10, 7, 6 },
{ 10, 8, 7 },
{ 10, 9, 8 },
{ 10, 0, 9 },
{ 11, 0, 1 },
{ 11, 1, 2 },
{ 11, 2, 3 },
{ 11, 3, 4 },
{ 11, 4, 5 },
{ 11, 5, 6 },
{ 11, 6, 7 },
{ 11, 7, 8 },
{ 11, 8, 9 },
{ 11, 9, 0 } };
static const int etoile_nbfaceColors = 20;
static const unsigned char etoile_faceColors[20][3] =
{
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 255, 0 },
{ 0, 0, 255 },
{ 0, 0, 255 },
{ 0, 0, 255 },
{ 0, 0, 255 },
{ 0, 0, 255 },
{ 0, 0, 255 },
{ 0, 0, 255 },
{ 0, 0, 255 },
{ 0, 0, 255 },
{ 0, 0, 255 } };

void Drawable::LoadPredefinedEtoile()
{
  int i;

  colorOnFace = true;
  points.Clear();
  pointColors.Clear();
  faces.Clear();
  faceColors.Clear();
  for (i = 0; i < etoile_nbpoints; ++i )
    points.PushBack(Coord3D(etoile_points[i][0], etoile_points[i][1],
        etoile_points[i][2]) );
  for (i = 0; i < etoile_nbfaces; ++i )
    faces.PushBack(Face(etoile_faces[i][0], etoile_faces[i][1],
        etoile_faces[i][2]) );
  for (i = 0; i < etoile_nbfaceColors; ++i )
    faceColors.PushBack(Color(etoile_faceColors[i][0],
        etoile_faceColors[i][1], etoile_faceColors[i][2]) );

  CenterObjectToOrigin();

  for (i = 0; i < points.size; ++i )
    pointColors.PushBack(Color((unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256)) );
}
