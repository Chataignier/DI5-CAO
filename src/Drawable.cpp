#include <Drawable.h>
#include <FastMath.h>

bool Drawable::LoadFromO3DFile(char *FileName)
{
  FILE *Fichier;
  char Chaine[ 100 ];
  char *Fin;
  int i;
  float x, y, z;
  int a, b, c;
  int Red, Green, Blue;
  int NbSommets, NbFaces;

  if ( (Fichier = fopen(FileName, "rt") ) == NULL )
    return false;

  points.Clear();
  pointColors.Clear();
  faces.Clear();
  faceColors.Clear();

  colorOnFace = true;

  do
  {
    Chaine[ 0 ] = 0;

    // ----- Lecture d'une ligne du fichier
    Fin = fgets(Chaine, 100, Fichier );
    i = 1;

    switch (Chaine[ 0 ])
    {
    case '[':
    {
      // ----- Lecture du nombre de sommets
      while (Chaine[ i ] == ' ')
        i++;
      sscanf(Chaine + i, "%d", &NbSommets );

      // ----- Lecture du nombre de faces
      while (Chaine[ i ] != ',')
        i++;
      while (Chaine[ i ] == ' ')
        i++;
      i++;
      sscanf(Chaine + i, "%d", &NbFaces );
      break;
    }
    case '(':
    {
      // ----- Lecture de la coordonnï¿½e X
      while (Chaine[ i ] == ' ')
        i++;
      sscanf(Chaine + i, "%f", &x );

      // ----- Lecture de la coordonnï¿½e Y
      while (Chaine[ i ] != ',')
        i++;
      while (Chaine[ i ] == ' ')
        i++;
      i++;
      sscanf(Chaine + i, "%f", &y );

      // ----- Lecture de la coordonnï¿½e Z
      while (Chaine[ i ] != ',')
        i++;
      while (Chaine[ i ] == ' ')
        i++;
      i++;

      sscanf(Chaine + i, "%f", &z );
      points.PushBack(Coord3D(x, y, z));

      break;
    }
    case '{':
    {
      // ----- Lecture du sommet a
      while (Chaine[ i ] == ' ')
        i++;
      sscanf(Chaine + i, "%d", &a );

      // ----- Lecture du sommet b
      while (Chaine[ i ] != ',')
        i++;
      while (Chaine[ i ] == ' ')
        i++;
      i++;
      sscanf(Chaine + i, "%d", &b );

      // ----- Lecture du sommet c
      while (Chaine[ i ] != ',')
        i++;
      while (Chaine[ i ] == ' ')
        i++;
      i++;
      sscanf(Chaine + i, "%d", &c );

      // ----- Lecture de la composante Rouge
      while (Chaine[ i ] != '(')
        i++;
      while (Chaine[ i ] == ' ')
        i++;
      i++;
      sscanf(Chaine + i, "%d", &Red );

      // ----- Lecture de la composante Verte
      while (Chaine[ i ] != ',')
        i++;
      while (Chaine[ i ] == ' ')
        i++;
      i++;
      sscanf(Chaine + i, "%d", &Green );

      // ----- Lecture de la composante Bleue
      while (Chaine[ i ] != ',')
        i++;
      while (Chaine[ i ] == ' ')
        i++;
      i++;
      sscanf(Chaine + i, "%d", &Blue );

      faces.PushBack(Face(a, b, c));
      faceColors.PushBack(Color((unsigned char)Red, (unsigned char)Green, (unsigned char)Blue));
      break;
    }
    }

  } while (Fin != NULL );

  // ----- On ferme le fichier
  fclose(Fichier );

  CenterObjectToOrigin();

  for (i = 0; i < points.size; ++i )
    pointColors.PushBack(Color((unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256)));

  return true;
}

void Drawable::CenterObjectToOrigin()
{
  int i;
  double xmin = INT_MAX, xmax = INT_MIN;
  double ymin = INT_MAX, ymax = INT_MIN;
  double zmin = INT_MAX, zmax = INT_MIN;

  for (i = points.size - 1; i >= 0; --i )
  {
    xmin = FastMath::min(xmin, points.data[i].x);
    xmax = FastMath::max(xmax, points.data[i].x);
    ymin = FastMath::min(ymin, points.data[i].y);
    ymax = FastMath::max(ymax, points.data[i].y);
    zmin = FastMath::min(zmin, points.data[i].z);
    zmax = FastMath::max(zmax, points.data[i].z);
  }
  for (i = points.size - 1; i >= 0; --i )
  {
    points.data[i].x -= (xmax + xmin) / 2;
    points.data[i].y -= (ymax + ymin) / 2;
    points.data[i].z -= (zmax + zmin) / 2;
  }
  radius = FastMath::max((xmax - xmin) / 2, FastMath::max((ymax - ymin) / 2, (zmax
      - zmin) / 2));
}

void Drawable::SaveAsCode(char * FileName)
{
  int i;
  FILE * file = fopen(FileName, "w");

  fprintf(
      file,
      "points.Clear();\npointColors.Clear();\nfaces.Clear();\nfaceColors.Clear();\n\n");

  for (i = 0; i < points.size; ++i )
    fprintf(file, "points.PushBack( Coord3D(%lf,%lf,%lf) );\n",
        points.data[i].x, points.data[i].y, points.data[i].z);
  for (i = 0; i < faces.size; ++i )
    fprintf(file, "faces.PushBack( Face(%d,%d,%d) );\n",
        faces.data[i].index1, faces.data[i].index2,
        faces.data[i].index3);
  for (i = 0; i < faceColors.size; ++i )
    fprintf(file, "faceColors.PushBack( Color(%d,%d,%d) );\n",
        faceColors.data[i].red, faceColors.data[i].green,
        faceColors.data[i].blue);
  fprintf(file, "colorOnFace = true;\n");
  fclose(file);
}

