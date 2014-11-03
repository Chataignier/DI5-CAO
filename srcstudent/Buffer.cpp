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

        for(int i = 1; i< longx; i++) {
            //Calcul de la couleur
            wA = 1 - p1.Distance(Coord2D(x,y)) / distanceP1P2;
            SetPoint(Coord2D(x, y), c1 * wA + c2 * (1 - wA));

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

        for(int i = 1; i < longy; i++) {
            wA = 1 - p1.Distance(Coord2D(x,y)) / distanceP1P2;
            SetPoint(Coord2D(x, y), c1 * wA + c2 * (1 - wA));

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

    DrawLine(p1, p2, c1, c2);
    DrawLine(p1, p3, c1, c3);
    DrawLine(p2, p3, c2, c3);

    for(int y = scanLineComputer.ymin; y < scanLineComputer.ymax; ++y){
        DrawLine(Coord2D(scanLineComputer.left.data[y], y),
                 Coord2D(scanLineComputer.right.data[y], y),
                 c1,
                 c1);
    }
}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
	// compléter ici
}

