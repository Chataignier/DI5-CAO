#include <IndexOutOfBoundsException.h>

IndexOutOfBoundsException::IndexOutOfBoundsException(int index, int min, int max) :
	index(index), min(min), max(max)
{
	wxString buf;
	buf.Printf(wxT("Index %d out of bounds [%d;%d]"), index, min, max);
	setMessage(buf);
}

int IndexOutOfBoundsException::getIndex() const
{
	return index;
}

int IndexOutOfBoundsException::getMin() const
{
	return min;
}

int IndexOutOfBoundsException::getMax() const
{
	return max;
}
