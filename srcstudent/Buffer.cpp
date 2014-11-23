#include <Buffer.h>
#include <FastMath.h>

void Buffer::DrawLine(const Coord2D p1, const Coord2D p2, const Color c1, const Color c2)
{
    int x, y, longx, longy;
    double const2;
    double const1;
    double critere;
    int incx;
    int incy;
    double wA;

    // Mise en place de l'algorithme de Bresenham

    double distanceP1P2 = p1.Distance(p2);

    longx = p2.x - p1.x;
    longy = p2.y - p1.y;

    x = p1.x;
    y = p1.y;

    if(longx >= 0) {
        incx = 1;
    } else {
        incx = -1;
        longx = -longx;
    }

    if(longy >= 0) {
        incy = 1;
    } else {
        incy = -1;
        longy = -longy;
    }

    if(longy < longx) {
        const1 = 2*(longy - longx);
        const2 = 2*longy;
        critere = const2 - longx;

        for(int i = 1; i<= longx; i++) {
            //Calcul de la couleur
            Coord2D currentPoint(x,y);
            wA = 1.0 - p1.Distance(currentPoint) / distanceP1P2;
            currentPoint.depth = p1.depth * wA + p2.depth * (1.0 - wA);
            SetPoint(currentPoint, c1 * wA + c2 * (1.0 - wA));

            if(critere > 0) {
                y = y + incy;
                critere = critere + const1;
            } else {
                critere = critere + const2;
            }

            x = x + incx;
        }
    } else {
        const1 = 2*(longx - longy);
        const2 = 2*longx;
        critere = const2- longy;

        for(int i = 1; i <= longy; i++) {
            Coord2D currentPoint(x,y);
            wA = 1.0 - p1.Distance(currentPoint) / distanceP1P2;
            currentPoint.depth = p1.depth * wA + p2.depth * (1.0 - wA);
            SetPoint(currentPoint, c1 * wA + c2 * (1.0 - wA));

            if(critere > 0) {
                x = x + incx;
                critere = critere+const1;
            }else{
                critere = critere + const2;
            }
            y = y+incy;
        }
    }
}

void Buffer::DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3)
{
    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);
    int x1, x2;

    // On dessine les bords du triangle
    DrawLine(p2, p1, c2, c1);
    DrawLine(p1, p3, c1, c3);
    DrawLine(p3, p2, c3, c2);

    // On parcourt la face de bas en haut
    for(int y = scanLineComputer.ymin; y <= scanLineComputer.ymax; ++y){

        x1 = scanLineComputer.left.data[y];
        x2 = scanLineComputer.right.data[y];

        Array<double> * leftWeight = &scanLineComputer.leftweight.data[y];
        Array<double> * rightWeight = &scanLineComputer.rightweight.data[y];

        // On dessine la ligne courante
        DrawLine(Coord2D(x1, y, p1.depth*leftWeight->data[0] + p2.depth*leftWeight->data[1] + p3.depth*leftWeight->data[2]),
                 Coord2D(x2, y, p1.depth*rightWeight->data[0] + p2.depth*rightWeight->data[1] + p3.depth*rightWeight->data[2]),
                 (c1*leftWeight->data[0] + c2*leftWeight->data[1] + c3*leftWeight->data[2])*(1/(leftWeight->data[0]+leftWeight->data[1]+leftWeight->data[2])),
                 (c1*rightWeight->data[0] + c2*rightWeight->data[1] + c3*rightWeight->data[2])*(1/(rightWeight->data[0]+rightWeight->data[1]+rightWeight->data[2])));
    }
}


void Buffer::DrawPhongTriangle(const Coord2D p1,
                               const Coord2D p2,
                               const Coord2D p3,
                               const Color c1,
                               const Color c2,
                               const Color c3,
                               const Coord3D posi1,
                               const Coord3D posi2,
                               const Coord3D posi3,
                               const Coord3D normal1,
                               const Coord3D normal2,
                               const Coord3D normal3,
                               const AmbientLight & ambientLight,
                               const PointLight & pointLight)
{
    Color colors[3] = {c1, c2, c3};
    Coord3D positions3D[3] = {posi1, posi2, posi3};
    Coord3D normals[3] = {normal1, normal2, normal3};
    double depths[3] = {p1.depth, p2.depth, p3.depth};
    Coord2D pointLeft, pointRight;

    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);

    // On parcourt la face de bas en haut
    for(int y = scanLineComputer.ymin; y <= scanLineComputer.ymax; ++y){
        Coord3D normalLeft, normalRight;
        Color colorLeft, colorRight;
        Coord3D positionLeft, positionRight;
        double distanceRightLeft;
        double depthLeft = 0, depthRight = 0;

        pointLeft.y = pointRight.y = y;
        pointLeft.x = scanLineComputer.left.data[y];
        pointRight.x = scanLineComputer.right.data[y];

        distanceRightLeft = pointLeft.Distance(pointRight);

        // Si nous ne sommes pas su un unique point
        if(distanceRightLeft > 0){

            // Réalisation de toutes les interpolations
            for(int i = 0; i < 3; ++i){
                double currentLeftWeight = scanLineComputer.leftweight.data[y].data[i];
                double currentRightWeight = scanLineComputer.rightweight.data[y].data[i];

                colorRight = colorRight + (colors[i] * currentRightWeight);
                colorLeft = colorLeft + (colors[i] * currentLeftWeight);
                normalRight = normalRight + (normals[i] * currentRightWeight);
                normalLeft = normalLeft + (normals[i] * currentLeftWeight);
                positionRight = positionRight + (positions3D[i] * currentRightWeight);
                positionLeft = positionLeft + (positions3D[i] * currentLeftWeight);
                depthRight += depths[i] * currentRightWeight;
                depthLeft += depths[i] * currentLeftWeight;
            }

            // Pour chacun des points du segments
            for(int x = pointLeft.x; x <= pointRight.x; ++x){

                // Interpolation
                Coord2D currentPoint(x, y);
                double w1 = 1 - (pointLeft.Distance(currentPoint) / distanceRightLeft), w2 = 1 - w1;
                currentPoint.depth = depthLeft * w1 + depthRight * w2;

                // Affichage du point
                SetPoint(currentPoint,
                         (colorLeft * w1 + colorRight * w2) *
                         (ambientLight.ambientColor + pointLight.GetColor(
                                                             (positionLeft * w1) + (positionRight * w2),
                                                             (normalLeft * w1) + (normalRight * w2))));
            }
        }
    }
}
