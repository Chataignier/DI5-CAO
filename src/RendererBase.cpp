#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

// le constructeur
Renderer::Renderer(Panel3D * _owner, Engine * _engine) :
	owner(_owner), engine(_engine), drawable(&_engine->drawable),
			effectiveDrawable(&_engine->effectiveDrawable), ambientLight(Color(
					16, 16, 16)), pointLight(Coord3D(0, 0, 100), Color(255,
					255, 255))
{
	currentBuffer = 0;
	lastBufferAvailiable = -1;
	buffer = &buffers[currentBuffer];

	width = 0;
	height = 0;
	current = false;
}

Renderer::~Renderer()
{
	;
}

// pour dessiner le dernier buffer disponible sur le DC
void Renderer::DrawBufferOnDC(wxDC & dc)
{
	// si aucun buffer valide n'est disponible, on ne dessine pas
	if (lastBufferAvailiable != -1)
	{
		// on dessine le dernier buffer disponible
		wxBitmap bitmap(buffers[lastBufferAvailiable].GetImage() );
		dc.DrawBitmap(bitmap, 0, 0);
	}
}

// pour dimensionner les buffers
void Renderer::SetSize(wxSize _size)
{
	if (width != _size.GetWidth() || height != _size.GetHeight())
	{
		buffers[0].SetSize(_size);
		buffers[1].SetSize(_size);

		// reset de l'affichage
		lastBufferAvailiable = -1;
		currentBuffer = 0;
		buffer = &buffers[currentBuffer];

		width = _size.GetWidth();
		height = _size.GetHeight();
		size = _size;
	}
}

void Renderer::ReDraw()
{
	renderable.ComputeRenderable( *effectiveDrawable, size);
	Draw(); // on dessine
	// on échange les buffers
	lastBufferAvailiable = currentBuffer;
	currentBuffer = (currentBuffer + 1) % 2;
	buffer = &buffers[currentBuffer];
	owner->Refresh();
}

// Dessine la scène
void Renderer::Draw()
{
	Color red(255, 0, 0);
	Color green(0, 255, 0);
	buffer->ClearBuffer();
	if (current)
	{
		buffer->DrawLine(Coord2D(0, 0, 0), Coord2D(width, height, 0), green,
				green);
		buffer->DrawLine(Coord2D(width, 0, 0), Coord2D(0, height, 0), green,
				green);
	}
	else
	{
		buffer->DrawLine(Coord2D(0, 0, 0), Coord2D(width, height, 0), red, red);
		buffer->DrawLine(Coord2D(width, 0, 0), Coord2D(0, height, 0), red, red);
	}

	switch (mode)
	{
	case Filaire:
	{
		buffer->zbuffer.Disable();
		DrawFilaire();
		break;
	}
	case FilaireCache:
	{
		buffer->zbuffer.Disable();
		DrawFilaireCache();
		break;
	}
	case FacePleine:
	{
		buffer->zbuffer.Disable();
		DrawFacePleine();
		break;
	}
	case Lambert:
	{
		buffer->zbuffer.Disable();
		DrawLambert();
		break;
	}
	case Gouraud:
	{
		buffer->zbuffer.Disable();
		DrawGouraud();
		break;
	}
	case Phong:
	{
		buffer->zbuffer.Disable();
		DrawPhong();
		break;
	}
	case FacePleineZBuffer:
	{
		buffer->zbuffer.Enable();
		buffer->zbuffer.Init();
		DrawFacePleine();
		break;
	}
	case LambertZBuffer:
	{
		buffer->zbuffer.Enable();
		buffer->zbuffer.Init();
		DrawLambert();
		break;
	}
	case GouraudZBuffer:
	{
		buffer->zbuffer.Enable();
		buffer->zbuffer.Init();
		DrawGouraud();
		break;
	}
	case PhongZBuffer:
	{
		buffer->zbuffer.Enable();
		buffer->zbuffer.Init();
		DrawPhong();
		break;
	}

	};

}