//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IWidgetCreator.h $
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
#ifndef __IWidgetCreator__
#define __IWidgetCreator__

#include "IPMUnknown.h"
#include "widgetid.h"

class IControlView;

//----------------------------------------------------------------------------------------
// Interface IWidgetCreator
//----------------------------------------------------------------------------------------

/**
	IWidgetCreator is an interface that was introduced in 1996 for integrating TextFrameWidgets into LayoutWidgets.
	For more details see build notes from 6/6/1996 and 6/12/1996:

	Integration of TextFrameWidgets into LayoutWidgets
	
	1) The LayoutWidget is now derived from PanelView and PanelEH to be able to contain
	children. The TextFrameWidget (TextEditor) is hooked to the LayoutControlView as 
	a child. 
	
	2) To solve the synchronization problems with different transforms (i.e. when the user scrolls)
	the TextFrameWidget uses now Panoramas. 
	
	3) IWidgetCreator
	There is a new interface IWidgetCreator which has to be added to PageItem 
	bosses (like FramePageItem) to support the creation of widgets for paritular
	pageitems. For example the FrameWidgetCreator creates TextFrameWidgets 
	(= TextEditors as widgets). 
	
	4) TextSelectTracker creates TextFrameWidgets
	The TextSelectTracker has been modified to be able to create a TextFrameWidget. 
	In the EndTracking() it asks the pageitem (TextFrame) for an IWidgetCreator. The WidgetCreator 
	will only create a new TextFrameWidget if it does not found another at the child level of the 
	parent widget (here: LayoutControlView). This ensures that the TextFrameWidgets are shared at 
	each LayoutCV.
	
	5)  Creation of TextFrameWidgets as an option
	Now the creation of the new TextEditor as a widget is available as an option. If you want to 
	create a widget you have to out comment or remove the IID_ITEXTEDITOR from the LayoutWidget
	in Layout.r (LayoutWidget).
	There is also a debugging mode that you can activate/deactivate 
	with MacControlKey + OptionKey +  CmdKey + Click. In the debugging mode the Draw() method
	of the widget is enabled so you can see the widget.
*/

class IWidgetCreator : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWIDGETCREATOR };


	/**
		Creates a widget and adds it to the parent.
		@param pParent IN. IControlView parent.
		@return new IControlView child of pParent. Returned IControlView is addref'ed.
	*/
	virtual	IControlView *	CreateChildOf( IControlView *pParent ) = 0;	


	/**
		Scans pParent for widgets that could be created by us. 
		@param pParent IN. IControlView parent. If pParent is nil, QueryWidget takes the LayoutControlView.
		@return found IControlView widget of pParent. Returned IControlView is addref'ed.
	*/
	virtual	IControlView *	QueryWidget( IControlView *pParent = 0 ) = 0;

	/**
		Returns the class id of the widget. 
		@return the class id of the widget.
	*/
	virtual	ClassID 		GetWidgetClassID() const = 0;

	/**
		Returns the widget id of the widget. 
		@return the widget id of the widget.
	*/
	virtual	WidgetID 		GetWidgetID() const = 0;
	
	/**
		Returns QueryWidget() or creates a new via CreateChildOf(). 
		@return QueryWidget() or creates a new via CreateChildOf(). Returned IControlView is addref'ed.
	*/
	inline	IControlView *	QueryChildOf( IControlView *pParent );	

	/**
		Sends a message to the Widget's PageContextObserver for recalculating the bbox. 
	*/
	virtual	void			RecalcWidget() = 0;
};

//---------------------------------------------------------------
// inline CWidgetCreator::QueryChildOf
//---------------------------------------------------------------

inline IControlView *IWidgetCreator::QueryChildOf( IControlView *pParent )
{
	IControlView *pView = this->QueryWidget( pParent );
	if( !pView )
		pView = CreateChildOf( pParent );
	return pView;
}

#endif

