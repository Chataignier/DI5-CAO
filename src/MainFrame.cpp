#include <MainFrame.h>
#include <FrameCounter.h>
#include <wxid.h>
#include <Piloter.h>
#include <App.h>

MainFrame::MainFrame( bool _demoMode ) : wxFrame(NULL, -1, wxT("")), demoMode(_demoMode)
{
	if (demoMode)
	SetTitle( wxT("Mode demonstration - ") + StudentsNames);
	else
	SetTitle( wxT("Mode developpement - ") + StudentsNames);

	wxGridSizer * droite = NULL;
	if (demoMode)
	{
		droite = new wxGridSizer(2);
		{
			miniPanels[0] = new Panel3D(this, &engine, Renderer::Filaire);
			miniPanels[0]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[0], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[1] = new Panel3D(this, &engine, Renderer::FilaireCache);
			miniPanels[1]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[1], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[2] = new Panel3D(this, &engine, Renderer::FacePleine);
			miniPanels[2]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[2], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[3] = new Panel3D(this, &engine, Renderer::Lambert);
			miniPanels[3]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[3], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[4] = new Panel3D(this, &engine, Renderer::Gouraud);
			miniPanels[4]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[4], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[5] = new Panel3D(this, &engine, Renderer::Phong);
			miniPanels[5]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[5], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[6] = new Panel3D(this, &engine, Renderer::FacePleineZBuffer);
			miniPanels[6]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[6], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[7] = new Panel3D(this, &engine, Renderer::LambertZBuffer);
			miniPanels[7]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[7], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[8] = new Panel3D(this, &engine, Renderer::GouraudZBuffer);
			miniPanels[8]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[8], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
		{
			miniPanels[9] = new Panel3D(this, &engine, Renderer::PhongZBuffer);
			miniPanels[9]->SetSizeHints(160, 120); // taille minimale de la zone de dessin (format 4/3)
			droite->Add(miniPanels[9], 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
		}
	}

	// positionnement automatique via un flex grid sizer (1 ligne, 2 colonnes)
	wxFlexGridSizer * sizer = new wxFlexGridSizer(1, 2, 5, 5);
	sizer->AddGrowableRow(0);
	sizer->AddGrowableCol(0);
	SetSizer(sizer);

	wxBoxSizer * gauche = new wxBoxSizer(wxVERTICAL);
	{
		panel = new Panel3D(this, &engine, Renderer::Filaire);
		panel->SetSizeHints(640, 480); // taille de la zone de dessin (format 4/3)
		gauche->Add(panel, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL , 2);
	}
	{ // attention, cet objet doit être créé après les mini et le panel
		Piloter * piloter = new Piloter( this, &engine );
		gauche->Add(piloter, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
	}

	sizer->Add(gauche);
	if (demoMode)
		sizer->Add(droite);

	SetAutoLayout(TRUE); // dimensionnement automatique
	Fit(); // ajuster les dimensions de la fenêtre au contenu

	FrameCounter::IncFrameCount();
}

MainFrame::~MainFrame()
{
	FrameCounter::DecFrameCount();
}

