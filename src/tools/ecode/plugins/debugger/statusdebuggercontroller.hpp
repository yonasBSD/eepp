#ifndef ECODE_STATUSDEBUGGERCONTROLLER_HPP
#define ECODE_STATUSDEBUGGERCONTROLLER_HPP

#include "../../uistatusbar.hpp"
#include <eepp/system/luapattern.hpp>
#include <eepp/ui/tools/uicodeeditorsplitter.hpp>
#include <eepp/ui/uicodeeditor.hpp>
#include <eepp/ui/uirelativelayout.hpp>
#include <eepp/ui/uiscenenode.hpp>
#include <eepp/ui/uisplitter.hpp>
#include <eepp/ui/uitableview.hpp>

using namespace EE;
using namespace EE::UI;
using namespace EE::UI::Tools;

namespace ecode {

class StatusDebuggerController : public StatusBarElement {
  public:
	StatusDebuggerController( UISplitter* mainSplitter, UISceneNode* uiSceneNode,
							  PluginContextProvider* pluginContext );

	virtual ~StatusDebuggerController() {};

	UIWidget* getWidget();

	UIWidget* createWidget();

	UITableView* getUIThreads();

	UITableView* getUIStack();

	UITableView* getUIBreakpoints();

  protected:
	UILinearLayout* mContainer{ nullptr };
	UITableView* mUIThreads{ nullptr };
	UITableView* mUIStack{ nullptr };
	UITableView* mUIBreakpoints{ nullptr };

	void createContainer();
};

} // namespace ecode

#endif // ECODE_STATUSDEBUGGERCONTROLLER_HPP
