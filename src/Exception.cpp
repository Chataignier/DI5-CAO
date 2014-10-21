#include <Exception.h>
#include <signal.h>

#ifdef DEBUG
static bool debugHelper = false;
#endif

Exception::Exception()
{
	line = -1;
}

Exception::Exception(const wxString & msg)
{
	this->msg = msg;
	line = -1;
}

void Exception::setMessage(const wxString & msg)
{
	this->msg = msg;
}

wxString Exception::getMessage() const
{
	return this->msg;
}

void Exception::setLocation(const wxString & file, int line)
{
	this->file = file;
	this->line = line;
}

wxString Exception::getFile() const
{
	return this->file;
}

int Exception::getLine() const
{
	return this->line;
}

wxString Exception::what() const
{
	wxString tmp1 = msg + wxT(" (") + file;
	wxString tmp2;
	tmp2.Printf(wxT(",%d)"), line);
	return tmp1+tmp2;
}

void Exception::raiseSIGTRAP()
{
#ifdef DEBUG
#ifndef WINVER
	if (debugHelper)
	raise(SIGTRAP);
#endif
#endif

}

void Exception::activateDebugHelper()
{
#ifdef DEBUG
	debugHelper = true;
#endif

}

void Exception::desactivateDebugHelper()
{
#ifdef DEBUG
	debugHelper = false;
#endif

}

