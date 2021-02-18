//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPageItemFocus.h $
//  
//  Owner: Bernd Paradies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IPageItemFocus__
#define __IPageItemFocus__

#include "IPMUnknown.h"
#include "widgetid.h"

//----------------------------------------------------------------------------------------
// Interface IPageItemFocus
//----------------------------------------------------------------------------------------

/* 
	PageItemFocus manages switches between page item event handling (PageItemEventHandler) and text event handling (FrameEventHandler).
	Page items and text selection have different event handlers: i.e. arrow key left moves a page item to the left on the spread if the 
	PageItemEventHandler is active while the same key event moves the caret by one character to the left if the FrameEventHandler is activated. 
	If the user switches from page item selection to text selection or vice versa the corresponding event handler needs to be registered as 
	the current event handler. This is done via KeyFocusHandler::SetCurrentTargetEventHandler in three steps:
	- calling IEventHandler::GiveUpKeyFocus() on the current event handler. 
	- replacing the current event handler with the new one. 
	- calling IEventHandler::GetKeyFocus() on the new event handler. 

	There are several situations that require a change of event handlers and a call to KeyFocusHandler::SetCurrentTargetEventHandler: 
	- Activation of TextSelection after creating a new TextFrame 
	- Deactivation of TextSelection after switching to pointer tool. 
	- Activation of TextSelection after clicking with pointer tool into TextFrame. 

	PageItemFocus offers a convenient API for activating and deactivating. PageItemFocus is implemented in PublicLib with kPageItemFocusImpl. It is only used by kStandOffBoss. 
	FrameViewFocus is derived from PageItemFocus and is implemented in TextEditor with kFrameViewFocusImpl. It is only used by kTextEditorBoss: 
	- kStandOffBoss uses kPageItemFocusImpl 
	- kTextEditorBoss uses kFrameViewFocusImpl 

	This interface is part of the PageItem widget. It helps to differentiate between
	several cases of deactivation.
	Grant/RevokePageItemFocus is called, when the pageitem has the focus (i.e. if the user edits it).
	The selection would be visible and a TextCaret would blink.
	Suspend/ResumePageItemFocus is called when the window or the layout control view is deactivated.
	The selection would be shadowed, but a TextCaret would disappear.

	These are possible cases for Grant/Revoke and Suspend/Resume:
	1) Deactivate Window => Suspend( kTrue )
	2) Reactivate Window => Resume
	3) Change the tool => Suspend( kFalse )
	4) Change back  to the first tool => Resume
	5) Close Document => Revoke
	6) Create new PageItem => Grant
	7) Place a story => Revoke
	8) Change to an EditBox in a Panel => Suspend( kTrue )

	Call stacks:
	
	(1) Call stack: Activation of TextSelection after creating a new TextFrame 
	- CreateMultiColumnItemCmd::Do 
	- DoUIStuff 
	- SelectUtils::ProcessSelectText 
	- TextSelectionIntegratorSuite::SetTextSelection 
	- TextSelectionSuite::SetTextSelection 
	- TextSelectionNavigator::SetTextSelection 
	- TextSelectionNavigator::SetTextSelection_ 
	- CSubject::Change 
	- CChangeManager::SubjectChanged 
	- CSB_Observer::Update 
	- CSB_Observer::HandleASBSuiteMessage 
	- SelectionExt::HandleIntegratorSuiteMessage 
	- SelectionHighlighterASB::HandleIntegratorSuiteMessage 
	- CSubject::Change 
	- CChangeManager::SubjectChanged 
	- LayoutSelectionHighlightObserver::Update 
	- SelectionHighlighterASB::ChangeHighlighting 
	- TextSelectionHighlighter::ChangeHighlighting 
	- EditorToFrame::ActivateTextEditor 
	- FrameViewFocus::GrantPageItemFocus 
	- PageItemFocus::GrantPageItemFocus 
	- FrameViewFocus::Activate 
	- PageItemFocus::Activate 
	- KeyFocusHandler::SetCurrentTargetEventHandler 
	- KeyBoard::AcquireKeyFocus 
	- KeyBoard::GrabKeyFocus 
	- MFrameEventHandler::GetKeyFocus 
	- PageItemEventHandler::GetKeyFocus 
	- FrameViewFocus::GrantPageItemFocus 
	- CObserver::Release 

	(2) Call stack: Deactivation of TextSelection after switching to pointer tool. 
	- SetToolCmd::Do 
	- ToolManager::SetActiveTool 
	- PointerTool::Select 
	- CTool::Select 
	- ToolChangeSuiteASB::ToolChanged 
	- ToolChangeSuiteTextCSB::ToolChanged 
	- ToolChangeSuiteTextCSB::SelectTextFrames 
	- SelectionManager::DeselectAll 
	- ConcreteTextSelection::DeselectAll 
	- TextSelectionIntegratorSuite::SetTextSelection 
	- TextSelectionSuite::SetTextSelection 
	- TextSelectionNavigator::SetTextSelection 
	- TextSelectionNavigator::SetTextSelection_ 
	- CSubject::Change 
	- CChangeManager::SubjectChanged 
	- CSB_Observer::Update 
	- CSB_Observer::HandleASBSuiteMessage 
	- SelectionExt::HandleIntegratorSuiteMessage 
	- SelectionHighlighterASB::HandleIntegratorSuiteMessage 
	- CSubject::Change 
	- CChangeManager::SubjectChanged 
	- LayoutSelectionHighlightObserver::Update 
	- SelectionHighlighterASB::ChangeHighlighting 
	- TextSelectionHighlighter::ChangeHighlighting 
	- EditorToFrame::DeactivateTextEditor 
	- FrameViewFocus::RevokePageItemFocus 
	- PageItemFocus::RevokePageItemFocus 
	- FrameViewFocus::Deactivate 



	(3) Call stack: Activation of TextSelection after clicking with pointer tool into TextFrame. 
	- LayoutEventHandler::LButtonDn 
	- LayoutEventHandler::BeginTracking 
	- IBeamTracker::BeginTracking 
	- CTracker::BeginTracking 
	- CTextSelectTracker::DoBeginTracking 
	- TextSelectionIntegratorSuite::SelectTextInViewBegin 
	- TextSelectionSuite::SelectTextInViewBegin 
	- TextSelectionSuite::TrackSingleClickBegin 
	- TextSelectionNavigator::SetTextSelectionHmm 
	- TextSelectionNavigator::SetTextSelection 
	- TextSelectionNavigator::SetTextSelection_ 
	- CSubject::Change 
	- CChangeManager::SubjectChanged 
	- CSB_Observer::Update 
	- CSB_Observer::HandleASBSuiteMessage 
	- SelectionExt::HandleIntegratorSuiteMessage 
	- SelectionHighlighterASB::HandleIntegratorSuiteMessage 
	- CSubject::Change 
	- CChangeManager::SubjectChanged 
	- LayoutSelectionHighlightObserver::Update 
	- SelectionHighlighterASB::ChangeHighlighting 
	- TextSelectionHighlighter::ChangeHighlighting 
	- EditorToFrame::ActivateTextEditor 
	- FrameViewFocus::GrantPageItemFocus 
	- PageItemFocus::GrantPageItemFocus 
	- FrameViewFocus::Activate 
	- PageItemFocus::Activate 
	- KeyFocusHandler::SetCurrentTargetEventHandler 
	- KeyBoard::AcquireKeyFocus 
	- KeyBoard::GrabKeyFocus 
	- MFrameEventHandler::GetKeyFocus 
	- PageItemEventHandler::GetKeyFocus 
	- FrameViewFocus::GrantPageItemFocus 
	- PageItemFocus::GrantPageItemFocus

	------------------------------------------------
	
	<sheridan>:
	In looking to rework this interface, here are the current uses:

	IsPageItemFocusSuspended
	------------------------
	decl
		source/public/interfaces/ui/IPageItemFocus.h
		source/private/widgets/includes/PageItemFocus.h
	defn
		source/private/widgets/pageitems/PageItemFocus.cpp
	call
		source/private/widgets/pageitems/PageItemEventHandler.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp
		source/components/texteditor/widget/FrameEventHandler.cpp
		source/components/text/selection/TextSelectionHighlighter.cpp
		source/components/cjk/ime/IMETextObserver.cpp


	SuspendPageItemFocus
	--------------------
	decl
		source/public/interfaces/ui/IPageItemFocus.h
		source/private/widgets/includes/PageItemFocus.h
	defn
		source/private/widgets/pageitems/PageItemFocus.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp
	call
		source/private/widgets/pageitems/PageItemEventHandler.cpp
		source/components/widgets/pageitems/PageItemControlView.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp


	ResumePageItemFocus
	-------------------
	decl
		source/public/interfaces/ui/IPageItemFocus.h
		source/private/widgets/includes/PageItemFocus.h
		source/components/texteditor/widget/FrameViewFocus.cpp
	defn
		source/private/widgets/pageitems/PageItemFocus.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp
	call
		source/private/widgets/pageitems/PageItemFocus.cpp
		source/private/widgets/pageitems/PageItemEventHandler.cpp
		source/components/widgets/pageitems/PageItemControlView.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp


	RevokePageItemFocus
	-------------------
	decl
		source/public/interfaces/ui/IPageItemFocus.h
		source/private/widgets/includes/PageItemFocus.h
		source/components/texteditor/widget/FrameViewFocus.cpp
	defn
		source/private/widgets/pageitems/PageItemFocus.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp
	call
		source/public/trackers/CTracker.cpp
		source/private/widgets/pageitems/PageItemEventHandler.cpp
		source/components/widgets/pageitems/PageItemControlView.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp
		source/components/texteditor/widget/FrameItemObserver.cpp
		source/components/texteditor/widget/EditorToFrame.cpp
		source/components/testing/testlib/qaclasses/QADoc.cpp


	GrantPageItemFocus
	------------------
	decl
		source/public/interfaces/ui/IPageItemFocus.h
		source/private/widgets/includes/PageItemFocus.h
		source/components/texteditor/widget/FrameViewFocus.cpp
	defn
		source/private/widgets/pageitems/PageItemFocus.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp
	call
		source/private/widgets/pageitems/PageItemEventHandler.cpp
		source/components/texteditor/widget/FrameViewFocus.cpp
		source/components/texteditor/widget/EditorToFrame.cpp
		source/components/pageitems/standoff/PageItemStandOff.cpp


	IsPageItemFocused
	-----------------
	decl
		source/public/interfaces/ui/IPageItemFocus.h
		source/private/widgets/includes/PageItemFocus.h
	defn
		source/private/widgets/pageitems/PageItemFocus.cpp
	call
		source/private/widgets/pageitems/PageItemEventHandler.cpp
		source/components/widgets/pageitems/PageItemControlView.cpp
		source/components/texteditor/widget/FrameEventHandler.cpp
		

*/

/** 
	PageItemFocus manages switches between page item event handling (PageItemEventHandler) and text event handling (FrameEventHandler). 
	Page items and text selection have different event handlers: i.e. arrow key left moves a page item to the left on the spread if the 
	PageItemEventHandler is active while the same key event moves the caret by one character to the left if the FrameEventHandler is activated. 
	If the user switches from page item selection to text selection or vice versa the corresponding event handler needs to be registered as the current 
	event handler. This is done via KeyFocusHandler::SetCurrentTargetEventHandler in three steps: 
	- calling IEventHandler::GiveUpKeyFocus() on the current event handler. 
	- replacing the current event handler with the new one. 
	- calling IEventHandler::GetKeyFocus() on the new event handler. 

	There are several situations that require a change of event handlers and a call toKeyFocusHandler::SetCurrentTargetEventHandler: 
	- Activation of TextSelection after creating a new TextFrame 
	- Deactivation of TextSelection after switching to pointer tool. 
	- Activation of TextSelection after clicking with pointer tool into TextFrame. 

	PageItemFocus offers a convenient API for activating and deactivating. PageItemFocus is implemented in PublicLib with kPageItemFocusImpl. 
	It is only used by kStandOffBoss. FrameViewFocus is derived from PageItemFocus and is implemented in TextEditor with kFrameViewFocusImpl. 
	It is only used by kTextEditorBoss: 
	- kStandOffBoss uses kPageItemFocusImpl 
	- kTextEditorBoss uses kFrameViewFocusImpl 

	This interface is part of the PageItem widget. It helps to differentiate between several cases of deactivation.
	Grant/RevokePageItemFocus is called, when the pageitem has the focus (i.e. if the user edits it).
	The selection would be visible and a TextCaret would blink.
	Suspend/ResumePageItemFocus is called when the window or the layout control view is deactivated.
	The selection would be shadowed, but a TextCaret would disappear.

	These are possible cases for Grant/Revoke and Suspend/Resume:
	1) Deactivate Window => Suspend( kTrue )
	2) Reactivate Window => Resume
	3) Change the tool => Suspend( kFalse )
	4) Change back  to the first tool => Resume
	5) Close Document => Revoke
	6) Create new PageItem => Grant
	7) Place a story => Revoke
	8) Change to an EditBox in a Panel => Suspend( kTrue )
*/

class IPageItemFocus : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMFOCUS };

	/**
		Grants a PageItem Focus.
		This method is called by anyone who thinks this PageItem should get the focus.
	*/
	virtual void				GrantPageItemFocus() = 0;

	/**
		Revokes a PageItem Focus. 
		This method called by anyone who thinks this PageItem should lose the focus.
	*/
	virtual void				RevokePageItemFocus() = 0;

	/**
		Returns whether a PageItem Focus has been granted.
		@return the current focus state.
	*/
	virtual bool16				IsPageItemFocused() const = 0;

	/**
		Suspends a PageItem Focus. 
		This method keeps the focus but stays bKeepVisible in background.
		@param bKeepVisible IN. Determines whether the focus should stay visible in the background or not.
	*/
	virtual void				SuspendPageItemFocus( bool16 bKeepVisible ) = 0;

	/**
		Suspends a PageItem Focus. 
		This method resurrects the focus from the background.
	*/
	virtual void				ResumePageItemFocus() = 0;

	/**
		Returns whether a PageItem Focus has been suspended.
		@return the current suspend state.
	*/
	virtual bool16				IsPageItemFocusSuspended() const = 0;
};

#endif
