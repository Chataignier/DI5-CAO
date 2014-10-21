#ifndef Exception_h
#define Exception_h

#include <stdlib.h>
#include <string.h>
#include <Config.h>

/** @defgroup exception Les exceptions */

/** La classe parente de toutes les exceptions gérées
 * @ingroup exception */
class Exception
{
private:
	/** @internal Le message associé à une exception */
	wxString msg;
	/** @internal Le fichier dans lequel l'exception a été levée */
	wxString file;
	/** @internal La ligne du fichier où l'exception à été levée */
	int line;
public:
	/** Le constructeur */
	Exception();
	/** Le constructeur avec un message */
	Exception(const wxString & msg);

	/** @internal Pour définir le message associé à une exception */
	void setMessage(const wxString & msg);
	/** @internal Pour obtenir le message associé à une exception */
	wxString getMessage() const;
	/** @internal Pour définir le fichier et la ligne du fichier correspondant à l'exception */
	void setLocation(const wxString & file, int line);
	/** @internal Pour obtenir la valeur de l'attribut file */
	wxString getFile() const;
	/** @internal Pour obtenir la valeur de l'attribut line */
	int getLine() const;
	/** Donne une description de l'exception (message+fichier+ligne) */
	wxString what() const;

	/** Make a call to raise(SIGTRAP) in the debug version of the library if the debug help is enabled
	 * @see activateDebugHelper
	 * @see desactivateDebugHelper
	 * @remark This has no effect on Windows
	 */
	static void raiseSIGTRAP();

	/** Enable the use of raise(SIGTRAP) when raising an exception to help in debugging
	 * @warning This method has an effect only in the debug version of the library
	 * @remark This has no effect on Windows
	 * */
	static void activateDebugHelper();
	/** Disable the use of raise(SIGTRAP) when raising an exception to help in debugging
	 * @warning This method has an effect only in the debug version of the library.
	 * @attention By default, this debug help is desactivated.
	 * @remark This has no effect on Windows
	 * */
	static void desactivateDebugHelper();
};

/** @def RaiseException(e) Lève une exception dérivée de Exception */
#define RaiseException(_e) \
	{ \
		_e.setLocation( wxT(__FILE__), __LINE__ ); \
		Exception::raiseSIGTRAP(); \
		throw _e; \
	}

#endif
