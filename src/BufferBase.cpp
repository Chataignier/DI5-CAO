#include <Buffer.h>
#include <FastMath.h>

Buffer::Buffer()
{
	;
}

Buffer::Buffer(const Buffer & b)
{
	;
}

Buffer & Buffer::operator=(const Buffer & b)
{
	return * this;
}

wxImage & Buffer::GetImage()
{
	return data;
}

void Buffer::SetPoint(const Coord2D & pos, const Color & c)
{
	if (pos.x < 0 || pos.x >= width)
		return;
	if (pos.y < 0 || pos.y >= height)
		return;
	// S'il faut remplacer le pixel de coordonnées (pos.x,pos.y) alors on le dessine
	if (zbuffer.ReplaceCurrent(pos))
		data.SetRGB(pos.x, pos.y, c.red, c.green, c.blue);
}

void Buffer::ClearBuffer()
{
	data.SetRGB(wxRect(0, 0, width, height), 0, 64, 64);
}

void Buffer::SetSize(wxSize size)
{
	data.Destroy();
	data.Create(size.GetWidth(), size.GetHeight(), false);
	width = size.GetWidth();
	height = size.GetHeight();
	scanLineComputer.SetSize(size);
	zbuffer.SetSize(size);
}

bool Buffer::SaveToFile(const wxString& name) const
{
	return data.SaveFile(name);
}