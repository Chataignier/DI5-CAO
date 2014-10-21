#include <ZBuffer.h>

ZBuffer::ZBuffer()
{
	enabled = false;
}

void ZBuffer::SetSize(wxSize size)
{
	int height = size.GetHeight();
	int width = size.GetWidth();
	depths.Resize(height);
	for (int i = 0; i < height; ++i )
		depths.data[i].Resize(width);
}


void ZBuffer::Enable()
{
	enabled = true;
}

void ZBuffer::Disable()
{
	enabled = false;
}
