#include <App.h>
#include <MainFrame.h>
#include <Config.h>
#include <locale.h>

#include <Drawable.h>

IMPLEMENT_APP(App);

const wxString StudentsNames = wxT("Jean-Noel de la Motte-Picquet & Charles-Henris Dupont");

bool App::OnInit()
{
	//Exception::activateDebugHelper();

	// on initialise les gestionnaire de format d'images
	wxInitAllImageHandlers();
	// on initialise le générateur de nombre aléatoire
	srand( (unsigned) time(NULL));
	// on force la locale à "C" (anglais ansi)
	setlocale(LC_NUMERIC, "C");

	// on crée la fenêtre principale
	MainFrame * mf = new MainFrame(false);
	// on affiche la fenêtre principale
	mf->Show();
	// on retourne true pour indiquer que tout c'est bien déroulé
	return true;
}
