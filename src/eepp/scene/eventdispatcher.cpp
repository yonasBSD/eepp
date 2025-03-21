#include <eepp/scene/eventdispatcher.hpp>
#include <eepp/scene/scenenode.hpp>
#include <eepp/window/engine.hpp>
#include <eepp/window/input.hpp>
#include <eepp/window/inputevent.hpp>
#include <eepp/window/window.hpp>

namespace EE { namespace Scene {

EventDispatcher* EventDispatcher::New( SceneNode* sceneNode ) {
	return eeNew( EventDispatcher, ( sceneNode ) );
}

EventDispatcher::EventDispatcher( SceneNode* sceneNode ) :
	mWindow( sceneNode->getWindow() ),
	mInput( mWindow->getInput() ),
	mSceneNode( sceneNode ),
	mFocusNode( sceneNode ),
	mLastFocusNode( sceneNode ),
	mOverNode( NULL ),
	mDownNode( NULL ),
	mLossFocusNode( NULL ),
	mCbId( 0 ),
	mFirstPress( false ),
	mNodeWasDragging( NULL ),
	mNodeDragging( NULL ) {
	mCbId = mInput->pushCallback( [this]( InputEvent* event ) { inputCallback( event ); } );
	mIMECbId = mWindow->getIME().addTextEditingCb(
		[this]( const String& text, Int32 start, Int32 length ) {
			sendTextEditing( text, start, length );
		} );
}

EventDispatcher::~EventDispatcher() {
	if ( -1 != mCbId && NULL != Engine::existsSingleton() &&
		 Engine::instance()->existsWindow( mWindow ) ) {
		mInput->popCallback( mCbId );
	}

	if ( mIMECbId && NULL != Engine::existsSingleton() &&
		 Engine::instance()->existsWindow( mWindow ) ) {
		mWindow->getIME().removeTextEditingCb( mIMECbId );
	}
}

void EventDispatcher::inputCallback( InputEvent* event ) {
	switch ( event->Type ) {
		case InputEvent::Window: {
			if ( event->window.type == InputEvent::WindowEventType::WindowKeyboardFocusLost )
				mWindow->getIME().stop();
			break;
		}
		case InputEvent::KeyUp:
			sendKeyUp( event->key.keysym.sym, event->key.keysym.scancode, event->key.keysym.unicode,
					   event->key.keysym.mod );
			break;
		case InputEvent::KeyDown:
			sendKeyDown( event->key.keysym.sym, event->key.keysym.scancode,
						 event->key.keysym.unicode, event->key.keysym.mod );
			break;
		case InputEvent::TextInput:
			sendTextInput( event->text.text, event->text.timestamp );
			break;
		case InputEvent::TextEditing:
			sendTextEditing( event->textediting.text, event->textediting.start,
							 event->textediting.length );
			break;
		case InputEvent::MouseWheel:
			sendMouseWheel( { event->wheel.x, event->wheel.y },
							event->wheel.direction == InputEvent::WheelEvent::Normal ? true
																					 : false );
			break;
		case InputEvent::SysWM:
		case InputEvent::VideoResize:
		case InputEvent::VideoExpose: {
			if ( NULL != mSceneNode )
				mSceneNode->invalidate( NULL );
		}
	}
}

void EventDispatcher::update( const Time& time ) {
	mNodeWasDragging = mNodeDragging;
	bool nodeWasDragging = mNodeDragging;

	mElapsed = time;
	mMousePos = mInput->getMousePosFromView( mWindow->getDefaultView() );
	mMousePosi = mMousePos.asInt();

	Node* pOver = mSceneNode->overFind( mMousePos );

	if ( pOver != mOverNode ) {
		Node* oldOverNode = mOverNode;

		mOverNode = pOver;

		if ( NULL != oldOverNode ) {
			oldOverNode->onMouseLeave( mMousePosi, 0 );
			sendMsg( oldOverNode, NodeMessage::MouseLeave );
		}

		if ( NULL != mOverNode ) {
			mOverNode->onMouseOver( mMousePosi, 0 );
			sendMsg( mOverNode, NodeMessage::MouseOver );
		}
	} else {
		if ( NULL != mOverNode && mLastMousePos != mMousePos ) {
			mOverNode->onMouseMove( mMousePosi, mInput->getPressTrigger() );
			sendMsg( mOverNode, NodeMessage::MouseMove, mInput->getPressTrigger() );
		}
	}

	if ( mDisableMousePress || mJustDisabledMousePress ) {
		mJustDisabledMousePress = false;
		return;
	}

	if ( NULL != mNodeDragging )
		mNodeDragging->onCalculateDrag( mMousePos, mInput->getPressTrigger() );

	mJustPressed = false;

	if ( mInput->getPressTrigger() ) {
		if ( !mFirstPress ) {
			mDownNode = mOverNode;
			mMouseDownPos = mMousePosi;
			mFirstPress = true;
			mJustPressed = true;
		}

		if ( NULL != mOverNode ) {
			mOverNode->onMouseDown( mMousePosi, mInput->getPressTrigger() );
			sendMsg( mOverNode, NodeMessage::MouseDown, mInput->getPressTrigger() );
		}

		if ( NULL != mFocusNode && mDownNode == mOverNode &&
			 ( mInput->getPressTrigger() & ( EE_BUTTON_LMASK | EE_BUTTON_RMASK ) ) &&
			 ( !nodeWasDragging || mMousePos == mLastMousePos ) ) {
			setFocusNode( mOverNode, NodeFocusReason::Click );
		}
	} else if ( NULL != mOverNode && mInput->getReleaseTrigger() &&
				!( mInput->getPressTrigger() & mInput->getReleaseTrigger() ) &&
				!( mInput->getLastPressTrigger() & mInput->getReleaseTrigger() ) ) {
		if ( !mFirstPress ) {
			mDownNode = mOverNode;
			mMouseDownPos = mMousePosi;
			mFirstPress = true;
			mJustPressed = true;
		}
		mOverNode->onMouseDown( mMousePosi, mInput->getReleaseTrigger() );
		sendMsg( mOverNode, NodeMessage::MouseDown, mInput->getReleaseTrigger() );

		if ( NULL != mFocusNode && mDownNode == mOverNode &&
			 ( mInput->getReleaseTrigger() & ( EE_BUTTON_LMASK | EE_BUTTON_RMASK ) ) &&
			 ( !nodeWasDragging || mMousePos == mLastMousePos ) ) {
			setFocusNode( mOverNode, NodeFocusReason::Click );
		}
	}

	if ( mInput->getReleaseTrigger() ) {
		if ( NULL != mFocusNode ) {
			if ( !nodeWasDragging || mMousePos == mLastMousePos ) {
				// The focused node can change after the MouseUp ( since the node can call
				// "setFocus()" on other node And the MouseClick would be received by the new
				// focused node instead of the real one
				mLastFocusNode = mFocusNode;

				if ( NULL != mOverNode ) {
					if ( mInput->getReleaseTrigger() & EE_BUTTONS_WUWD ) {
						mOverNode->onMouseDown( mMousePosi,
												mInput->getReleaseTrigger() & EE_BUTTONS_WUWD );
						if ( NULL != mOverNode )
							sendMsg( mOverNode, NodeMessage::MouseDown,
									 mInput->getReleaseTrigger() & EE_BUTTONS_WUWD );
					}

					mOverNode->onMouseUp( mMousePosi, mInput->getReleaseTrigger() );
					if ( NULL != mOverNode )
						sendMsg( mOverNode, NodeMessage::MouseUp, mInput->getReleaseTrigger() );
				}

				if ( mInput->getClickTrigger() && mDownNode == mOverNode ) {
					mLastFocusNode->onMouseClick( mMousePosi, mInput->getClickTrigger() );
					sendMsg( mLastFocusNode, NodeMessage::MouseClick, mInput->getClickTrigger() );

					if ( mInput->getDoubleClickTrigger() &&
						 mClickPos.distance( mMousePosi ) < 10 ) {
						mLastFocusNode->onMouseDoubleClick( mMousePosi,
															mInput->getDoubleClickTrigger() );
						sendMsg( mLastFocusNode, NodeMessage::MouseDoubleClick,
								 mInput->getDoubleClickTrigger() );
					}

					mClickPos = mMousePosi;
				}
			} else {
				if ( NULL != mOverNode ) {
					mOverNode->onMouseUp( mMousePosi, mInput->getReleaseTrigger() );
					if ( NULL != mOverNode )
						sendMsg( mOverNode, NodeMessage::MouseUp, mInput->getReleaseTrigger() );
				}
			}
		}

		mFirstPress = false;
	}

	mLastMousePos = mMousePos;

	// While dragging and object we want to be able to continue dragging even if the mouse cursor
	// moves outside the window. Capturing the mouse allows this.
	if ( !nodeWasDragging && isNodeDragging() ) {
		mInput->captureMouse( true );
	} else if ( nodeWasDragging && !isNodeDragging() ) {
		mInput->captureMouse( false );
	}
}

Input* EventDispatcher::getInput() const {
	return mInput;
}

void EventDispatcher::sendTextInput( const Uint32& textChar, const Uint32& timestamp ) {
	TextInputEvent textInputEvent =
		TextInputEvent( mFocusNode, Event::TextInput, textChar, timestamp );
	Node* node = mFocusNode;
	while ( NULL != node ) {
		if ( node->isEnabled() && node->onTextInput( textInputEvent ) )
			break;
		node = node->getParent();
	}
}

void EventDispatcher::sendTextEditing( const String& text, const Int32& start,
									   const Int32& length ) {
	mWindow->getIME().onTextEditing( text, start, length );
	if ( !mWindow->getIME().isEditing() && length <= 0 )
		return;
	TextEditingEvent textEditingEvent =
		TextEditingEvent( mFocusNode, Event::TextInput, text, start, length );
	Node* node = mFocusNode;
	while ( NULL != node ) {
		if ( node->isEnabled() && node->onTextEditing( textEditingEvent ) )
			break;
		node = node->getParent();
	}
}

void EventDispatcher::sendKeyUp( const Keycode& keyCode, const Scancode& scancode,
								 const Uint32& chr, const Uint32& mod ) {
	KeyEvent keyEvent = KeyEvent( mFocusNode, Event::KeyUp, keyCode, scancode, chr, mod );
	Node* node = mFocusNode;
	while ( NULL != node ) {
		if ( node->isEnabled() && node->onKeyUp( keyEvent ) )
			break;
		node = node->getParent();
	}
}

void EventDispatcher::sendKeyDown( const Keycode& keyCode, const Scancode& scancode,
								   const Uint32& chr, const Uint32& mod ) {
	KeyEvent keyEvent = KeyEvent( mFocusNode, Event::KeyDown, keyCode, scancode, chr, mod );
	Node* node = mFocusNode;
	while ( NULL != node ) {
		if ( node->isEnabled() && node->onKeyDown( keyEvent ) )
			break;
		node = node->getParent();
	}
}

void EventDispatcher::sendMouseWheel( const Vector2f& offset, bool flipped ) {
	Node* node = mFocusNode;
	while ( NULL != node ) {
		if ( node->isEnabled() && node->onMouseWheel( offset, flipped ) )
			break;
		node = node->getParent();
	}
}

void EventDispatcher::sendMsg( Node* node, const Uint32& Msg, const Uint32& Flags ) {
	NodeMessage tMsg( node, Msg, Flags );
	node->messagePost( &tMsg );
}

void EventDispatcher::sendMouseClick( Node* toNode, const Vector2i& Pos, const Uint32 flags ) {
	sendMsg( toNode, NodeMessage::MouseClick, flags );
	toNode->onMouseClick( Pos, flags );
}

void EventDispatcher::sendMouseUp( Node* toNode, const Vector2i& Pos, const Uint32 flags ) {
	sendMsg( toNode, NodeMessage::MouseUp, flags );
	toNode->onMouseUp( Pos, flags );
}

void EventDispatcher::sendMouseDown( Node* toNode, const Vector2i& pos, const Uint32 flags ) {
	sendMsg( toNode, NodeMessage::MouseDown, flags );
	toNode->onMouseDown( pos, flags );
}

void EventDispatcher::setFocusNode( Node* node, NodeFocusReason reason ) {
	if ( NULL != mFocusNode && NULL != node && node != mFocusNode ) {
		mWindow->getIME().stop();

		mLossFocusNode = mFocusNode;

		mFocusNode = node;

		mLossFocusNode->onFocusLoss();
		sendMsg( mLossFocusNode, NodeMessage::FocusLoss );

		mFocusNode->onFocus( reason );
		sendMsg( mFocusNode, NodeMessage::Focus );

		if ( !mFocusCbs.empty() ) {
			auto focusCbs = mFocusCbs;

			for ( const auto& cb : focusCbs )
				cb.second( cb.first, mFocusNode, mLossFocusNode );
		}
	}
}

Node* EventDispatcher::getLastFocusNode() const {
	return mLastFocusNode;
}

void EventDispatcher::setLastFocusNode( Node* lastFocusNode ) {
	mLastFocusNode = lastFocusNode;
}

bool EventDispatcher::isFirstPress() const {
	return mJustPressed;
}

Node* EventDispatcher::getMouseDownNode() const {
	return mDownNode;
}

void EventDispatcher::resetMouseDownNode() {
	mDownNode = mSceneNode;
}

Node* EventDispatcher::getMouseOverNode() const {
	return mOverNode;
}

void EventDispatcher::setMouseOverNode( Node* node ) {
	mOverNode = node;
}

Node* EventDispatcher::getFocusNode() const {
	return mFocusNode;
}

Node* EventDispatcher::getLossFocusNode() const {
	return mLossFocusNode;
}

const Uint32& EventDispatcher::getPressTrigger() const {
	return mInput->getPressTrigger();
}

const Uint32& EventDispatcher::getLastPressTrigger() const {
	return mInput->getLastPressTrigger();
}

const Uint32& EventDispatcher::getClickTrigger() const {
	return mInput->getClickTrigger();
}

const Uint32& EventDispatcher::getDoubleClickTrigger() const {
	return mInput->getDoubleClickTrigger();
}

const Uint32& EventDispatcher::getReleaseTrigger() const {
	return mInput->getReleaseTrigger();
}

bool EventDispatcher::justPressTriggered( Uint32 flag ) {
	return ( getPressTrigger() & flag ) && ( 0 == ( getLastPressTrigger() & flag ) );
}

void EventDispatcher::setNodeDragging( Node* dragging ) {
	eeASSERT( mNodeDragging == nullptr || mNodeDragging == dragging || dragging == nullptr );
	mNodeDragging = dragging;
}

bool EventDispatcher::isNodeDragging() const {
	return NULL != mNodeDragging;
}

bool EventDispatcher::wasNodeDragging() const {
	return NULL != mNodeWasDragging;
}

bool EventDispatcher::isOrWasNodeDragging() const {
	return mNodeWasDragging || isNodeDragging();
}

Vector2i EventDispatcher::getMousePos() {
	return mMousePosi;
}

Vector2f EventDispatcher::getMousePosf() {
	return mMousePos;
}

Vector2i EventDispatcher::getMouseDownPos() {
	return mMouseDownPos;
}

Vector2f EventDispatcher::getLastMousePos() {
	return mLastMousePos;
}

SceneNode* EventDispatcher::getSceneNode() const {
	return mSceneNode;
}

const Time& EventDispatcher::getLastFrameTime() const {
	return mElapsed;
}

Node* EventDispatcher::getNodeDragging() const {
	return mNodeDragging;
}

Node* EventDispatcher::getNodeWasDragging() const {
	return mNodeWasDragging;
}

bool EventDispatcher::getDisableMousePress() const {
	return mDisableMousePress;
}

void EventDispatcher::setDisableMousePress( bool disableMousePress ) {
	if ( mDisableMousePress && !disableMousePress )
		mJustDisabledMousePress = true;
	mDisableMousePress = disableMousePress;
}

Uint32 EventDispatcher::addFocusEventCallback( const FocusCallback& cb ) {
	mFocusCbs[++mCurFocusId] = cb;
	return mCurFocusId;
}

bool EventDispatcher::removeFocusEventCallback( const Uint32& cbId ) {
	auto it = mFocusCbs.find( cbId );
	if ( it != mFocusCbs.end() ) {
		mFocusCbs.erase( it );
		return true;
	}
	return false;
}

}} // namespace EE::Scene
