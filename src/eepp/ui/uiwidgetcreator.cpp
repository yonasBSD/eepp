#include <eepp/ui/uiwidgetcreator.hpp>
#include <eepp/ui/uilinearlayout.hpp>
#include <eepp/ui/uirelativelayout.hpp>
#include <eepp/ui/uitextview.hpp>
#include <eepp/ui/uipushbutton.hpp>
#include <eepp/ui/uiselectbutton.hpp>
#include <eepp/ui/uicheckbox.hpp>
#include <eepp/ui/uiradiobutton.hpp>
#include <eepp/ui/uicombobox.hpp>
#include <eepp/ui/uidropdownlist.hpp>
#include <eepp/ui/uitextureregion.hpp>
#include <eepp/ui/uilistbox.hpp>
#include <eepp/ui/uiwinmenu.hpp>
#include <eepp/ui/uiprogressbar.hpp>
#include <eepp/ui/uiscrollbar.hpp>
#include <eepp/ui/uislider.hpp>
#include <eepp/ui/uispinbox.hpp>
#include <eepp/ui/uisprite.hpp>
#include <eepp/ui/uitab.hpp>
#include <eepp/ui/uitabwidget.hpp>
#include <eepp/ui/uitable.hpp>
#include <eepp/ui/uitablecell.hpp>
#include <eepp/ui/uitextedit.hpp>
#include <eepp/ui/uitextinput.hpp>
#include <eepp/ui/uitextinputpassword.hpp>
#include <eepp/ui/uiloader.hpp>
#include <eepp/ui/uiwindow.hpp>
#include <eepp/ui/uiscrollview.hpp>
#include <eepp/ui/uiimage.hpp>
#include <eepp/ui/uitouchdragablewidget.hpp>
#include <eepp/ui/uigridlayout.hpp>

namespace  EE { namespace UI {

UIWidgetCreator::WidgetCallbackMap UIWidgetCreator::widgetCallback = UIWidgetCreator::WidgetCallbackMap();

UIWidgetCreator::RegisteredWidgetCallbackMap UIWidgetCreator::registeredWidget = UIWidgetCreator::RegisteredWidgetCallbackMap();

void UIWidgetCreator::createBaseWidgetList() {
	if ( registeredWidget.empty() ) {
		registeredWidget["widget"] = UIWidget::New;
		registeredWidget["hbox"] = UILinearLayout::NewHorizontal;
		registeredWidget["linearlayout"] = UILinearLayout::NewVertical;
		registeredWidget["vbox"] = UILinearLayout::NewVertical;
		registeredWidget["relativelayout"] = UIRelativeLayout::New;
		registeredWidget["textview"] = UITextView::New;
		registeredWidget["pushbutton"] = UIPushButton::New;
		registeredWidget["checkbox"] = UICheckBox::New;
		registeredWidget["radiobutton"] = UIRadioButton::New;
		registeredWidget["combobox"] = UIComboBox::New;
		registeredWidget["dropdownlist"] = UIDropDownList::New;
		registeredWidget["image"] = UIImage::New;
		registeredWidget["listbox"] = UIListBox::New;
		registeredWidget["winmenu"] = UIWinMenu::New;
		registeredWidget["progressbar"] = UIProgressBar::New;
		registeredWidget["scrollbar"] = UIScrollBar::New;
		registeredWidget["slider"] = UISlider::New;
		registeredWidget["spinbox"] = UISpinBox::New;
		registeredWidget["sprite"] = UISprite::New;
		registeredWidget["tab"] = UITab::New;
		registeredWidget["table"] = UITable::New;
		registeredWidget["tablecell"] = UITableCell::New;
		registeredWidget["tabwidget"] = UITabWidget::New;
		registeredWidget["textedit"] = UITextEdit::New;
		registeredWidget["textinput"] = UITextInput::New;
		registeredWidget["input"] = UITextInput::New;
		registeredWidget["textinputpassword"] = UITextInputPassword::New;
		registeredWidget["inputpassword"] = UITextInputPassword::New;
		registeredWidget["loader"] = UILoader::New;
		registeredWidget["selectbutton"] = UISelectButton::New;
		registeredWidget["window"] = UIWindow::New;
		registeredWidget["scrollview"] = UIScrollView::New;
		registeredWidget["textureregion"] = UITextureRegion::New;
		registeredWidget["touchdragable"] = UITouchDragableWidget::New;
		registeredWidget["gridlayout"] = UIGridLayout::New;
		registeredWidget["layout"] = UILayout::New;
	}
}

UIWidget * UIWidgetCreator::createFromName( std::string widgetName ) {
	createBaseWidgetList();

	String::toLowerInPlace( widgetName );

	if ( registeredWidget.find( widgetName ) != registeredWidget.end() ) {
		return registeredWidget[ widgetName ]();
	}

	if ( widgetCallback.find( widgetName ) != widgetCallback.end() ) {
		return widgetCallback[ widgetName ]( widgetName );
	}

	return NULL;
}

void UIWidgetCreator::addCustomWidgetCallback( std::string widgetName, const UIWidgetCreator::CustomWidgetCb& cb ) {
	widgetCallback[ String::toLower( widgetName ) ] = cb;
}

void UIWidgetCreator::removeCustomWidgetCallback( std::string widgetName ) {
	widgetCallback.erase( String::toLower( widgetName ) );
}

bool UIWidgetCreator::existsCustomWidgetCallback( std::string widgetName ) {
	return widgetCallback.find( String::toLower( widgetName ) ) != widgetCallback.end();
}

void UIWidgetCreator::registerWidget( std::string widgetName, const UIWidgetCreator::RegisterWidgetCb & cb ) {
	registeredWidget[ String::toLower( widgetName ) ] = cb;
}

void UIWidgetCreator::unregisterWidget( std::string widgetName ) {
	registeredWidget.erase( String::toLower( widgetName ) );
}

bool UIWidgetCreator::isWidgetRegistered( std::string widgetName ) {
	return registeredWidget.find( String::toLower( widgetName ) ) != registeredWidget.end();
}

}}
