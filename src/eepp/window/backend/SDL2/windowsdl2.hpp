#ifndef EE_WINDOWCWINDOWSDL2_HPP
#define EE_WINDOWCWINDOWSDL2_HPP

#include <eepp/window/backend.hpp>
#include <eepp/window/backend/SDL2/base.hpp>

#ifdef EE_BACKEND_SDL2

#include <eepp/window/backend/SDL2/wminfo.hpp>
#include <eepp/window/window.hpp>

#if EE_PLATFORM == EE_PLATFORM_WIN || EE_PLATFORM == EE_PLATFORM_MACOS || \
	defined( EE_X11_PLATFORM ) || EE_PLATFORM == EE_PLATFORM_IOS ||       \
	EE_PLATFORM == EE_PLATFORM_ANDROID
#define EE_USE_WMINFO
#endif

namespace EE { namespace Window { namespace Backend { namespace SDL2 {

class EE_API WindowSDL : public Window {
  public:
	WindowSDL( WindowSettings Settings, ContextSettings Context );

	virtual ~WindowSDL();

	bool create( WindowSettings Settings, ContextSettings Context );

	Uint32 getWindowID() const;

	void makeCurrent();

	void close();

	void setCurrent();

	void toggleFullscreen();

	void setTitle( const std::string& title );

	bool setIcon( const std::string& Path );

	bool isActive() const;

	bool isVisible() const;

	bool hasFocus() const;

	bool hasInputFocus() const;

	bool hasMouseFocus() const;

	void setSize( Uint32 width, Uint32 height, bool windowed );

	std::vector<DisplayMode> getDisplayModes() const;

	void setGamma( Float Red, Float Green, Float Blue );

	eeWindowHandle getWindowHandler() const;

	virtual void minimize();

	virtual void maximize();

	virtual bool isMaximized() const;

	virtual bool isMinimized() const;

	virtual void hide();

	virtual void raise();

	virtual void restore();

	virtual void flash( WindowFlashOperation op );

	virtual void show();

	virtual void setPosition( int Left, int Top );

	virtual Vector2i getPosition() const;

	const Sizei& getDesktopResolution() const;

	virtual Rect getBorderSize() const;

	virtual Float getScale() const;

	virtual bool hasNativeMessageBox() const;

	virtual bool showMessageBox( const MessageBoxType& type, const std::string& title,
								 const std::string& message );

	SDL_Window* getSDLWindow() const;

	void startOnScreenKeyboard();

	void stopOnScreenKeyboard();

	bool isOnScreenKeyboardActive() const;

	void startTextInput();

	bool isTextInputActive() const;

	void stopTextInput();

	void setTextInputRect( const Rect& rect );

	void clearComposition();

	bool hasScreenKeyboardSupport() const;

	bool isScreenKeyboardShown() const;

	bool isThreadedGLContext() const;

	void setGLContextThread();

	void unsetGLContextThread();

	int getCurrentDisplayIndex() const;

  protected:
	friend class ClipboardSDL;

	SDL_Window* mSDLWindow;
	SDL_GLContext mGLContext;
	SDL_GLContext mGLContextThread;
	Mutex mGLContextMutex;
	Uint32 mID{ 0 };

#ifdef EE_USE_WMINFO
	WMInfo* mWMinfo;
#endif

	Vector2i mWinPos;

	void swapBuffers();

	void setGLConfig();

	std::string getVersion();

	void updateDesktopResolution() const;

	void onWindowResize( Uint32 width, Uint32 height );
};

}}}} // namespace EE::Window::Backend::SDL2

#endif

#endif
