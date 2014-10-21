#ifndef MemoryException_h
#define MemoryException_h

#include <Exception.h>

/** Une exception levée lorsque des problèmes d'allocation mémoire surviennent
 * @ingroup exception */
class MemoryException : public Exception
{
public:
	/** Le constructeur */
	MemoryException(const wxString & msg);
};

#endif
