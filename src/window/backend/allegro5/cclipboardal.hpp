#ifndef EE_WINDOWCCLIPBOARDAl_HPP
#define EE_WINDOWCCLIPBOARDAl_HPP

#include "../../cbackend.hpp"

#ifdef EE_BACKEND_ALLEGRO_ACTIVE

#include "../../base.hpp"
#include "../../cclipboard.hpp"

namespace EE { namespace Window { namespace Backend { namespace Al {

class EE_API cClipboardAl : public cClipboard {
	public:
		virtual ~cClipboardAl();

		std::string GetText();

		std::wstring GetTextWStr();
		
		void SetText( const std::string& Text );
		
		void SetText( const std::wstring& Text );
	protected:
		friend class cWindowAl;

		cClipboardAl( cWindow * window );

		void Init();
};

}}}}

#endif

#endif
