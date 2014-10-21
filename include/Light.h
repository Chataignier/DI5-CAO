#ifndef LIGHT_H_
#define LIGHT_H_

#include <FastMath.h>
#include <Color.h>
#include <Coord3D.h>

/** @defgroup light La gestion de la lumière : le modèle d'éclairage.
 *
 * On trouve habituellement quatre types de sources lumineuses : les lumières directionnelles, les points lumineux, les spots lumineux et la lumière ambiante.
 * On se restreint ici à deux types de sources : le point lumineux et la lumière ambiante.
 *
 * Une source lumineuse est caractérisée par différentes composantes de couleurs interagissant différemment avec les objets touchés par les rayons lumineux :
 * ce sont les composantes ambiante, diffuse et spéculaire. Pour simplifier, on va considérer que les objets n'émettent pas de lumière et qu'ils sont mattes.
 * Dans ce cas, seule les composantes ambiantes et diffuses sont nécessaires. De plus, on va supposer que l'on a une unique source de lumière ambiante
 * n'ayant qu'une composante ambiante et que l'on a un unique point lumineux n'ayant qu'une composante diffuse.
 * Toujours pour simplifier, on ne considère pas que la lumière s'atténue en fonction des distances.
 *
 * @remark Il ne faut pas confondre modèle d'éclairage et modèle d'illumination. Le modèle d'éclairage ne se préoccupe que des sources lumineuses alors
 * que le modèle d'illumination prend en compte l'effet d'un rayon lumineux sur une surface et son impact sur le reste de la suface (Modèle simple, Gouraud ou Phong).
 * Par exemple, prenons le modèle simple d'illumination. Dans ce modèle, pour chaque triangle, on calcule via le modèle d'éclairage la quantité et la couleur de la lumière
 * touchant le triangle. Le modèle simple d'illumination dit alors que la quantité et la couleur de la lumière touchant chaque point du triangle est égale à la valeur obtenue précédemment.
 * Dans le modèle de Gouraud, le modèle d'éclairage fournit une quantité/couleur de lumière par sommet du triangle et ces informations sont interpollés pour les autres points du triangle.
 * Dans le modèle de Phong, le modèle d'éclairage fournit une quantité/couleur de lumière pour chaque point du triangle.
 *
 * Dans le modèle d'éclairage, deux rayons lumineux qui touchent une surface s'ajoute i.e. les composantes des couleurs s'ajoutent.
 * Lorsqu'un rayon lumineux touche une surface alors les deux couleurs se composent (multiplicaton composante par composante).
 *
 * L'impact d'une source limineuse ambiante est identique quelque soit l'objet : tout point de l'espace reçoit la même quantité/couleur de lumière ambiante.
 *
 * L'impact d'un point lumineux (éclairage omnidirectionnel) sur un point de l'espace (de couleur matte) est régi par la loi de Lambert "Pour une surface matte, l'intensité de la lumière réfléchie est
 * déterminée par le cosinus de l'angle formé par la normale à la surface N et par le vecteur de direction de la lumière D. De plus, l'intensité est nulle lorsque l'angle
 * entre N et D est inférieur ou égale à PI/2". Si S est la position du point lumineux et C la couleur du point lumineux, alors la quantité/couleur de reçue par le point P est
 * m*C avec m=max{ -<N|D>, 0 } et D=(P-S)/||P-S||.
 *
 * @ingroup dessin
 * */

/** Une source de lumière ponctuelle omnidirectionnelle (soleil, ampoule de plafonier, ...)
 * @ingroup light */
class PointLight
{
public:
  /** La position de la source lumineuse dans l'espace */
  Coord3D position;
  /** La couleur diffuse de la source lumineuse */
  Color diffuseColor; // composante diffuse de la source lumineuse
public:
  /** Le constructeur */
  PointLight(const Coord3D & _position, const Color & _diffuseColor) :
    position(_position), diffuseColor(_diffuseColor)
  {
    ;
  }
  /** On calcule la couleur de la lumière reçue par le point p de normal spécifiée */
  Color GetColor(const Coord3D p, const Coord3D normal) const
  {
    Coord3D d = p - position;
    double n = d.Norm();
    double mu = FastMath::max( -normal * d / n, 0.0);
    Color c = Color((unsigned char)(FastMath::Round(diffuseColor.red*mu)),
            (unsigned char)(FastMath::Round(diffuseColor.green*mu)),
                    (unsigned char)(FastMath::Round(diffuseColor.blue*mu)) );
    return c;
  }
};

/** Une source de lumière ambiante
 * @ingroup light  */
class AmbientLight
{
public:
  /** La couleur de la lumière ambiante */
  Color ambientColor;
public:
  /** Le constructeur */
  AmbientLight(const Color & _ambientColor) :
    ambientColor(_ambientColor)
  {
    ;
  }
};

#endif /*LIGHT_H_*/
