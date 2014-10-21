#include <Panel3D.h>
#include <Renderer.h>

BEGIN_EVENT_TABLE(Panel3D, wxPanel)
EVT_PAINT(Panel3D::OnPaint)
EVT_SIZE(Panel3D::OnSize)
EVT_ERASE_BACKGROUND(Panel3D::OnEraseBackGround)
END_EVENT_TABLE()

Panel3D::Panel3D(wxWindow* parent, Engine * engine, Renderer::EMode mode) : wxPanel(parent), renderer(this, engine)
{
	SetAutoLayout(TRUE); // dimensionnement automatique
	Fit(); //ajuster les dimensions de la fenêtre
	engine->addRenderer(&renderer);
	renderer.mode = mode;
}

void Panel3D::OnSize(wxSizeEvent& event)
{
	wxSize s = this->GetSize();
	renderer.SetSize(s);
}

void Panel3D::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	renderer.DrawBufferOnDC(dc);
}

void Panel3D::OnEraseBackGround(wxEraseEvent& event)
{
	// nothing to do : disable flickering
}
