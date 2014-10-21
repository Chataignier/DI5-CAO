#ifndef APP_H_
#define APP_H_

#include <Config.h>

extern const wxString StudentsNames;

/** @defgroup widgets Les objets wxWidgets */

/**
 *  La classe par où tout commence
 * @ingroup widgets
 */
class App : public wxApp
{
	public:
		/** La méthode où tout commence. c'est l'équivalent de la fonction main */
		virtual bool OnInit();
};

DECLARE_APP(App)

#endif /*APP_H_*/
