#include <Engine.h>
#include <Panel3D.h>
#include <Piloter.h>

// le constructeur
Engine::Engine() : piloter(NULL)
{
	needUpdates = true; // il faut faire la première mise à jour
}

Engine::Engine(const Engine & e)
{
	;
}

Engine::~Engine()
{
	;
}

Engine & Engine::operator=( const Engine & e )
{
	return *this;
}

void Engine::SetNeedUpdates()
{
	needUpdates = true;
}

void Engine::ReDraw()
{
	//camera.SetFromDrawable(drawable);
	effectiveDrawable.Compute(drawable, camera, rot);

	for (int i = 0; i < renderers.size; ++i )
		renderers.data[i]->ReDraw(); // on demande aux renderers de se dessiner et aux panels de s'afficher
}

void Engine::Refresh()
{
	if (needUpdates)
	{
		needUpdates = false; // on va faire la maj donc on la marque avant comme faite
		// il faut appeller SetNeedUpdates s'il faut continuer les mises à jours

		if (piloter != NULL)
			piloter->AutoRotateCallBack();

		// mise à jour
		ReDraw();
	}
}

void Engine::addRenderer(Renderer * renderer)
{
	renderers.PushBack(renderer);
}


