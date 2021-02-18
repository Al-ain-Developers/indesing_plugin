//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/utils/UserInterfaceUtils.h $
//  
//  Owner: Tim Wright
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
//  
//  This file contains common defines and macros for often-used functions.
//  
//  Adapted From SDKUtilities.h in the SDK
//  
//========================================================================================

#pragma once
#ifndef __UserInterfaceUtils_h__
#define __UserInterfaceUtils_h__

#include "IPMStream.h"

//------------------------------------------------------------
class IPanelControlData;
class IGraphicAttributeSuite;
class IGraphicStyleAttributeBossList;
class IDialog;
class IDialogController;

namespace UserInterfaceUtils
{
	// Pop an About box using a string and CAlert:
	void InvokePlugInAboutBox( const PMString alertStringID );
	
	//Show Modal dialog, wait till dismissal:
	void PresentModalDialog( PluginID inPluginID, RsrcID inDialogResourceID );
	
	//return dialog from resource, return (Caller can do additional action then Open, WaitForDialog)
	IDialog* GetModalDialog( PluginID inPluginID, RsrcID inDialogResourceID, bool inVisible=true );

	
	//Update various widgets based on values of Graphic attributes according
	//to graphic attribute suite (which can handle mixed/multiple selections)

	void UpdatePopupWidget(	IPanelControlData* inPanelData,
								IGraphicAttributeSuite * iGfxAttrSuite,
								bool inEnable,
								ClassID inAttrBoss,
								WidgetID inPopupWidget,
								IGraphicStyleAttributeBossList* inDefaults=0 ); //nil == default is first in list

	void UpdateStringListWidget(	IPanelControlData* inPanelData,
								IGraphicAttributeSuite * iGfxAttrSuite,
								bool inEnable,
								ClassID inAttrBoss,
								WidgetID inPopupWidget,
								const PMString& inDefault );

	void UpdateStaticWidget(	IPanelControlData* inPanelData,
								bool inEnable,
								WidgetID inStaticWidget );
	
	void UpdateCheckWidget(	IPanelControlData* inPanelData,
								IGraphicAttributeSuite * iGfxAttrSuite,
								bool inEnable,
								ClassID inAttrBoss,
								WidgetID inWidget,
								IGraphicStyleAttributeBossList* inDefaults=0 ); //nil == default is unchecked
								
	void UpdateTextWidget(	IPanelControlData* inPanelData,
								IGraphicAttributeSuite * iGfxAttrSuite,
								bool inEnable,
								ClassID inAttrBoss,
								WidgetID inEditWidget,
								IGraphicStyleAttributeBossList* inDefaults=0 ); //nil == default is ""


	void UpdateRealWidget(	IPanelControlData* inPanelData,
							IGraphicAttributeSuite * iGfxAttrSuite,
							bool inEnable,
							ClassID inAttrBoss,
							WidgetID inEditWidget,
							 IGraphicStyleAttributeBossList* inDefaults=0 ); //nil == default is 0.0

	void UpdateIntegerWidget(	IPanelControlData* inPanelData,
							IGraphicAttributeSuite * iGfxAttrSuite,
							bool inEnable,
							ClassID inAttrBoss,
							WidgetID inEditWidget,
							IGraphicStyleAttributeBossList* inDefaults=0 ); //nil == default is 0

	//Update Graphic attributes based on values of widgets:
	//(suite handles multiple and abstract selection case)
	
	void UpdatePopupAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * iGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl ); //popup index

	void UpdateCheckAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * iGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl );
								
	void UpdateTextAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * iGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl );

	void UpdateRealAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * iGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl );
	
	void UpdateIntegerAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * iGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl );

	void UpdateStringListAttribute(	const PMString& inCommandString,
								IGraphicAttributeSuite * inGfxAttrSuite,
								ClassID inAttrBoss,
								IPMUnknown* inControl );

	//Add Graphic attributes to specific attribute boss list based on values of widgets:

	void AddString(IGraphicStyleAttributeBossList * inAttrs, ClassID inAttrBoss, IControlView* inTextControlView );
	void AddBool(IGraphicStyleAttributeBossList * inAttrs, ClassID inAttrBoss, IControlView* inTriStateView );
	void AddInt32(IGraphicStyleAttributeBossList * inAttrs, ClassID inAttrBoss, IControlView* iEditView );
	void AddEnum(IGraphicStyleAttributeBossList * inAttrs, ClassID inAttrBoss, IControlView* iPopupView );

	IControlView*  GetControl(IDialogController * inDialogController, WidgetID inWidget );
}

//------------------------------------------------------------

#endif // __UserInterfaceUtils_h__


// End, UserInterfaceUtils.h.

