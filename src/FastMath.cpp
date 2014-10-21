#include <FastMath.h>

FastMath::StaticInitializer FastMath::staticInitializer = FastMath::StaticInitializer();
double FastMath::sinVal[360];
double FastMath::cosVal[360];
double FastMath::tanVal[360];

void FastMath::Initialize()
{
	for (int i = 0; i < 360; ++i )
	{
		sinVal[i] = ::sin( 2*PI*i/360.);
		cosVal[i] = ::cos( 2*PI*i/360.);
		tanVal[i] = ::tan( 2*PI*i/360.);
	}
}
