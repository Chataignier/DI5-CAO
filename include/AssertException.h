#ifndef AssertException_h
#define AssertException_h

#include <Exception.h>

/** Une exception levée lorsqu'une assertion n'est pas vérifiée
 * @ingroup exception */
class AssertException : public Exception
{
public:
	/** Constructeur */
	AssertException(const wxString & msg);
};

#ifdef DEBUG
#define ASSERT_MSG( cond, msg ) \
	{ \
	 if (!(cond)) \
	 { \
		AssertException __e( msg ); \
		RaiseException( __e ); \
	 } \
	}

#define ASSERT( cond ) \
	ASSERT_MSG( cond, wxT("Assertion " #cond " not verified") )

#else

/** @def ASSERT(cond) Macro ASSERT levant en mode debug une erreur si la condition cond est fausse */
#define ASSERT( cond ) { }

/** @def ASSERT_MSG(cond,msg) Macro ASSERT levant en mode debug une erreur si la condition cond est fausse. Le message transmi à l'exception est msg */
#define ASSERT_MSG( cond, msg ) { }

#endif

#endif
