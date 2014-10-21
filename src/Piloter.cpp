#include <Piloter.h>
#include <Engine.h>
#include <wxid.h>
#include <MainFrame.h>

BEGIN_EVENT_TABLE(Piloter, wxPanel)
EVT_BUTTON(wx_XP, Piloter::OnXP)
EVT_BUTTON(wx_XM, Piloter::OnXM)
EVT_BUTTON(wx_YP, Piloter::OnYP)
EVT_BUTTON(wx_YM, Piloter::OnYM)
EVT_BUTTON(wx_ZP, Piloter::OnZP)
EVT_BUTTON(wx_ZM, Piloter::OnZM)
EVT_BUTTON(wx_CENTER, Piloter::OnCenter)
EVT_BUTTON(wx_AUTOCENTER, Piloter::OnAutoCenter)
EVT_BUTTON(wx_AUTOROTATE, Piloter::OnAutoRotate)
EVT_BUTTON(wx_ROTATEXP, Piloter::OnRotateXP)
EVT_BUTTON(wx_ROTATEXM, Piloter::OnRotateXM)
EVT_BUTTON(wx_ROTATEYP, Piloter::OnRotateYP)
EVT_BUTTON(wx_ROTATEYM, Piloter::OnRotateYM)
EVT_BUTTON(wx_ROTATEZP, Piloter::OnRotateZP)
EVT_BUTTON(wx_ROTATEZM, Piloter::OnRotateZM)
EVT_BUTTON(wx_NEXTMETHOD, Piloter::OnNextMethod)
EVT_BUTTON(wx_NEXTMODEL, Piloter::OnNextModel)
EVT_BUTTON(wx_KALEIDOSCOPE, Piloter::OnKaleidoscope)
EVT_BUTTON(wx_SAVE, Piloter::OnSave)
EVT_IDLE(Piloter::OnIdle)
END_EVENT_TABLE()

Piloter::Piloter(wxWindow* parent, Engine * _engine) : wxPanel(parent), engine(_engine)
{
  positionStep = 50;
  rotationStep = 1;
  idmodel = 0;
  autorotate = false;
  _engine->piloter = this;

  // Gestion du rafraichissement
  SetExtraStyle(wxWS_EX_PROCESS_IDLE);
  wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
  lastTime = wxDateTime::UNow();

  idmodel = 0;
  engine->drawable.LoadPredefinedComprime();
  engine->SetNeedUpdates();

  wxBoxSizer * vertical = new wxBoxSizer(wxVERTICAL);

  {
    wxBoxSizer * horiz = new wxBoxSizer(wxHORIZONTAL);
    {
      wxButton * btn = new wxButton( this, wx_XP, wxT("X+"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_XM, wxT("X-"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_YP, wxT("Y+"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_YM, wxT("Y-"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_ZP, wxT("Z+"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_ZM, wxT("Z-"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    vertical->Add(horiz);
  }

  {
    wxBoxSizer * horiz = new wxBoxSizer(wxHORIZONTAL);
    {
      wxButton * btn = new wxButton( this, wx_ROTATEXP, wxT("Rotation X+"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_ROTATEXM, wxT("Rotation X-"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_ROTATEYP, wxT("Rotation Y+"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_ROTATEYM, wxT("Rotation Y-"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_ROTATEZP, wxT("Rotation Z+"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_ROTATEZM, wxT("Rotation Z-"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    vertical->Add(horiz);
  }

  {
    wxBoxSizer * horiz = new wxBoxSizer(wxHORIZONTAL);
    {
      wxButton * btn = new wxButton( this, wx_CENTER, wxT("Centrer l'objet"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_AUTOCENTER, wxT("Reinitialiser"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_AUTOROTATE, wxT("Rotation automatique"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    vertical->Add(horiz);
  }

  {
    wxBoxSizer * horiz = new wxBoxSizer(wxHORIZONTAL);
    {
      wxButton * btn = new wxButton( this, wx_NEXTMETHOD, wxT("Methode suivante"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      wxButton * btn = new wxButton( this, wx_KALEIDOSCOPE, wxT("Kaleidoscope"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      methode = new wxStaticText(this, -1, wxT("methode en cours d'utilisation"));
      horiz->Add(methode,0,wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    vertical->Add(horiz);
  }

  {
    wxBoxSizer * horiz = new wxBoxSizer(wxHORIZONTAL);
    {
      wxButton * btn = new wxButton( this, wx_NEXTMODEL, wxT("Modele suivant"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      modele = new wxStaticText(this, -1, wxT("modele en cours d'utilisation"));
      horiz->Add(modele,0,wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    vertical->Add(horiz);
  }

  {
    wxBoxSizer * horiz = new wxBoxSizer(wxHORIZONTAL);
    {
      wxButton * btn = new wxButton( this, wx_SAVE, wxT("Enregistrer l'image actuelle"));
      horiz->Add(btn, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 2);
    }
    {
      status = new wxStaticText(this, -1, wxT("Statistiques d'affichage et de rendu"));
      horiz->Add(status, 0, wxALL | wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT, 2);
    }
    vertical->Add(horiz);
  }

  SetSizer(vertical);

  SetAutoLayout(TRUE); // dimensionnement automatique
  Fit(); //ajuster les dimensions de la fenêtre

  engine->camera.SetFromDrawable(engine->drawable);
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène

  Update();
}

void Piloter::OnXP(wxCommandEvent & event)
{
  engine->camera.Set(engine->camera.positionInWorld+Coord3D(positionStep,0,
      0), engine->camera.orientationInWorld);
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnXM(wxCommandEvent & event)
{
  engine->camera.Set(engine->camera.positionInWorld+Coord3D(-positionStep,0,
      0), engine->camera.orientationInWorld);
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnYP(wxCommandEvent & event)
{
  engine->camera.Set(engine->camera.positionInWorld+Coord3D(0,
      positionStep,0), engine->camera.orientationInWorld);
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnYM(wxCommandEvent & event)
{
  engine->camera.Set(engine->camera.positionInWorld+Coord3D(0,
      -positionStep,0), engine->camera.orientationInWorld);
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnZP(wxCommandEvent & event)
{
  engine->camera.Set(engine->camera.positionInWorld+Coord3D(0,0,positionStep), engine->camera.orientationInWorld);
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnZM(wxCommandEvent & event)
{
  engine->camera.Set(engine->camera.positionInWorld+Coord3D(0,0,-positionStep), engine->camera.orientationInWorld);
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnCenter(wxCommandEvent & event)
{
  Coord3D p = engine->camera.positionInWorld;
  engine->camera.SetFromDrawable(engine->drawable);
  engine->camera.Set(p, engine->camera.orientationInWorld);
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnAutoCenter(wxCommandEvent & event)
{
  engine->camera.SetFromDrawable(engine->drawable);
  engine->rot = Rotation(); // l'identité
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnAutoRotate(wxCommandEvent & event)
{
  autorotate=!autorotate;
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::AutoRotateCallBack()
{
  const double coef = PI/180.;
  static Rotation rot = Rotation( 1, 0, 0, 0, cos(1*coef), -sin(1*coef), 0, sin(1*coef),
      cos(1*coef))*Rotation(cos(2*coef), 0, sin(2*coef), 0, 1, 0, -sin(2*coef), 0, cos(2*coef))
      *Rotation(cos(3*coef), -sin(3*coef), 0, sin(3*coef), cos(3*coef), 0, 0, 0, 1);
  if (autorotate)
  {
    engine->rot = engine->rot * rot;
    engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
  }
}

void Piloter::OnRotateXP(wxCommandEvent & event)
{
  Rotation rot = Rotation( 1, 0, 0, 0, FastMath::fastCos(rotationStep),
      -FastMath::fastSin(rotationStep), 0,
      FastMath::fastSin(rotationStep), FastMath::fastCos(rotationStep));
  engine->rot = engine->rot * rot;
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnRotateXM(wxCommandEvent & event)
{
  Rotation rot = Rotation( 1, 0, 0, 0, FastMath::fastCos(-rotationStep),
      -FastMath::fastSin(-rotationStep), 0,
      FastMath::fastSin(-rotationStep), FastMath::fastCos(-rotationStep));
  engine->rot = engine->rot * rot;
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnRotateYP(wxCommandEvent & event)
{
  Rotation rot = Rotation(FastMath::fastCos(rotationStep), 0,
      FastMath::fastSin(rotationStep), 0, 1, 0,
      -FastMath::fastSin(rotationStep), 0,
      FastMath::fastCos(rotationStep));
  engine->rot = engine->rot * rot;
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnRotateYM(wxCommandEvent & event)
{
  Rotation rot = Rotation(FastMath::fastCos(-rotationStep), 0,
      FastMath::fastSin(-rotationStep), 0, 1, 0,
      -FastMath::fastSin(-rotationStep), 0,
      FastMath::fastCos(-rotationStep));
  engine->rot = engine->rot * rot;
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnRotateZP(wxCommandEvent & event)
{
  Rotation rot = Rotation(FastMath::fastCos(rotationStep),
      -FastMath::fastSin(rotationStep), 0,
      FastMath::fastSin(rotationStep), FastMath::fastCos(rotationStep),
      0, 0, 0, 1);
  engine->rot = engine->rot * rot;
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnRotateZM(wxCommandEvent & event)
{
  Rotation rot = Rotation(FastMath::fastCos(-rotationStep),
      -FastMath::fastSin(-rotationStep), 0,
      FastMath::fastSin(-rotationStep), FastMath::fastCos(-rotationStep),
      0, 0, 0, 1);
  engine->rot = engine->rot * rot;
  engine->SetNeedUpdates(); // on indique qu'il faut redessiner la scène
}

void Piloter::OnNextMethod(wxCommandEvent & event)
{
  MainFrame * mf = (MainFrame*)this->GetParent();
  int cur = (int) mf->panel->renderer.mode;
  Renderer::EMode newMode = (Renderer::EMode) ((cur + 1) % 10);

  mf->panel->renderer.mode = newMode;
  engine->SetNeedUpdates();
  Update();
}

void Piloter::OnNextModel(wxCommandEvent & event)
{
  bool tmp = engine->drawable.colorOnFace;

  idmodel = (idmodel + 1) % 9;
  switch (idmodel)
  {
  case 0:
    engine->drawable.LoadPredefinedComprime();
    break;
  case 1:
    engine->drawable.LoadPredefinedDuck();
    break;
  case 2:
    engine->drawable.LoadPredefinedEtoile();
    break;
  case 3:
    engine->drawable.LoadPredefinedNoeud();
    break;
  case 4:
    engine->drawable.LoadPredefinedSphere();
    break;
  case 5:
    engine->drawable.LoadPredefinedTeapot();
    break;
  case 6:
    engine->drawable.LoadPredefinedTore();
    break;
  case 7:
    engine->drawable.LoadPredefinedHead();
    break;
  case 8:
    engine->drawable.LoadPredefinedPolytechLogo();
    break;
  };
  engine->drawable.colorOnFace = tmp;
  engine->SetNeedUpdates();
  Update();
}

void Piloter::OnSave(wxCommandEvent & event)
{
  static int index = 0;
  MainFrame * mf = (MainFrame*)this->GetParent();
  wxString name;

  name.Printf( wxT("Screenshot-%d.bmp"),index);
  index++;

  mf->panel->renderer.ReDraw();
  mf->panel->renderer.buffer->SaveToFile(name);
}

void Piloter::OnKaleidoscope(wxCommandEvent & event)
{
  engine->drawable.colorOnFace = !engine->drawable.colorOnFace;
  engine->SetNeedUpdates();
  Update();
}

void Piloter::Update()
{
  MainFrame * mf = (MainFrame*)this->GetParent();

  switch (mf->panel->renderer.mode)
  {
  case Renderer::Filaire :
  {
    methode->SetLabel(wxT("Mode filaire") );
    break;
  }
  case Renderer::FilaireCache :
  {
    methode->SetLabel(wxT("Mode filaire avec elimination des faces cachees") );
    break;
  }
  case Renderer::FacePleine :
  {
    methode->SetLabel(wxT("Mode remplissage sans eclairage"));
    break;
  }
  case Renderer::Lambert :
  {
    methode->SetLabel(wxT("Mode remplissage avec eclairage (Lambert)"));
    break;
  }
  case Renderer::Gouraud :
  {
    methode->SetLabel(wxT("Mode remplissage avec eclairage (Gouraud)"));
    break;
  }
  case Renderer::Phong :
  {
    methode->SetLabel(wxT("Mode remplissage avec eclairage (Phong)"));
    break;
  }
  case Renderer::FacePleineZBuffer :
  {
    methode->SetLabel(wxT("Mode remplissage sans eclairage (ZBuffer)"));
    break;
  }
  case Renderer::LambertZBuffer :
  {
    methode->SetLabel(wxT("Mode remplissage avec eclairage (Lambert+ZBuffer)"));
    break;
  }
  case Renderer::GouraudZBuffer :
  {
    methode->SetLabel(wxT("Mode remplissage avec eclairage (Gouraud+ZBuffer)"));
    break;
  }
  case Renderer::PhongZBuffer :
  {
    methode->SetLabel(wxT("Mode remplissage avec eclairage (Phong+ZBuffer)"));
    break;
  }
  };

  wxString kal = (engine->drawable.colorOnFace) ? wxT(" (kaleidoscope)")
      : wxT("");

  switch (idmodel)
  {
  case 0:
    modele->SetLabel(wxT("Le comprime") +kal);
    break;
  case 1:
    modele->SetLabel(wxT("Le canard")+kal);
    break;
  case 2:
    modele->SetLabel(wxT("L'etoile") +kal );
    break;
  case 3:
    modele->SetLabel(wxT("Le noeud") +kal);
    break;
  case 4:
    modele->SetLabel(wxT("La sphere") +kal);
    break;
  case 5:
    modele->SetLabel(wxT("La teilleire") +kal);
    break;
  case 6:
    modele->SetLabel(wxT("Le tore") +kal);
    break;
  case 7:
    modele->SetLabel(wxT("La tete") +kal);
    break;
  case 8:
    modele->SetLabel(wxT("Le logo Polytech") +kal);
    break;

  };

  if (mf->demoMode)
  {
    for (int i = 0; i < 10; ++i )
      mf->miniPanels[i]->renderer.current
          = (mf->miniPanels[i]->renderer.mode
              == mf->panel->renderer.mode);
  }
  mf->panel->renderer.current = true;
}

// methode idle qui appelle engine.Refresh() au plus 25 fois/seconde
void Piloter::OnIdle(wxIdleEvent & event)
{
  static int betweenRefreshSlice = 0;
  static int betweenRefreshSliceCount = 0;
  const long timeSlice = 1000/25; // 25 img/seconde max

  wxDateTime time = wxDateTime::UNow();
  wxTimeSpan delta = time.Subtract(lastTime);
  long milli = delta.GetMilliseconds().ToLong();

  if (milli >= timeSlice)
  {
    betweenRefreshSlice += (int)milli;
    betweenRefreshSliceCount++;

    if (betweenRefreshSliceCount % 10== 0)
    {
      wxString msg;
      msg.Printf(wxT("%.2lf msec/frame   %.2lf frames/sec"),
          betweenRefreshSlice / (double)betweenRefreshSliceCount,
          1000 * betweenRefreshSliceCount
              / (double) betweenRefreshSlice );
      status->SetLabel(msg);
      betweenRefreshSlice = 0;
      betweenRefreshSliceCount = 0;
    }
    lastTime = time;
    engine->Refresh();
  }
  else
  {
    // on est trop rapide => on attend un peu
    wxMilliSleep(timeSlice - milli);
  }
  event.RequestMore(); // on demande d'autres evenements idle
}
