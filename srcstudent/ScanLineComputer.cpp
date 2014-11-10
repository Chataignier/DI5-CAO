
#include <ScanLineComputer.h>
#include <Buffer.h>
#include <FastMath.h>
#include <limits.h>



void ScanLineComputer::AddEdge(const Coord2D p1, const Coord2D p2,
															 const int index1, const int index2)
{
	int x, y, longx, longy;
    double const2;
    double const1;
    double critere;
    int incx;
    int incy;

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

        for(int i = 1; i <= longx; i++) {
            if(y >= 0 && y < height){
                AddPoint(x, y, p1, p2, index1, index2);
            }

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
        critere = const2 - longy;

        for(int i = 1; i <= longy; i++) {

            if(y >= 0 && y < height){
                AddPoint(x, y, p1, p2, index1, index2);
            }

            if(critere > 0) {
                x = x + incx;
                critere = critere + const1;
            } else {
                critere = critere + const2;
            }

            y = y+incy;
        }
    }
}


