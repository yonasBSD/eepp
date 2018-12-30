#include <eepp/ui/uimenuitem.hpp>
#include <eepp/ui/uimenu.hpp>

namespace EE { namespace UI {

UIMenuItem * UIMenuItem::New() {
	return eeNew( UIMenuItem, () );
}

UIMenuItem::UIMenuItem( const std::string& tag ) :
	UIPushButton( tag )
{
	applyDefaultTheme();
}

UIMenuItem::UIMenuItem() :
	UIMenuItem( "menuitem" )
{}

UIMenuItem::~UIMenuItem() {
}

Uint32 UIMenuItem::getType() const {
	return UI_TYPE_MENUITEM;
}

bool UIMenuItem::isType( const Uint32& type ) const {
	return UIMenuItem::getType() == type ? true : UIPushButton::isType( type );
}

void UIMenuItem::setTheme( UITheme * Theme ) {
	UIWidget::setTheme( Theme );
	setThemeSkin( Theme, "menuitem" );
	onThemeLoaded();
}

Uint32 UIMenuItem::onMouseEnter( const Vector2i &Pos, const Uint32 Flags ) {
	UIPushButton::onMouseEnter( Pos, Flags );

	reinterpret_cast<UIMenu*> ( getParent() )->setItemSelected( this );

	return 1;
}

}}
