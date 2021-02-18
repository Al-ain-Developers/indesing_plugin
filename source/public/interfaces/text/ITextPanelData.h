//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextPanelData.h $
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
#ifndef __ITextPanelData__
#define __ITextPanelData__

#include "IPMUnknown.h"
#include "IDialog.h"

//----------------------------------------------------------------------------------------
// Class ITextPanelData
//----------------------------------------------------------------------------------------

// Query for IID_ITEXTPANELDATA which is defined in TextPanelID.h.

/** 
	@ingroup text_other
*/
class ITextPanelData : public IPMUnknown
{
public:
	virtual RsrcID 				GetTextResourceID() const = 0;
	virtual void 				SetTextResourceID( RsrcID rsrcID ) = 0;
	virtual PluginID 				GetTextResourcePluginID() const = 0;
	virtual void 				SetTextResourcePluginID( const PluginID& pluginID ) = 0;

	virtual void				SetTextDialogType( IDialog::DialogType dialogType ) = 0;
	virtual IDialog::DialogType	GetTextDialogType() const = 0;
	virtual RsrcID 				GetTextSelectableID() const = 0;
	virtual void 				SetTextSelectableID( RsrcID rsrcID ) = 0;
};

//----------------------------------------------------------------------------------------
// CREATE_TEXTPANEL_DATA macro
//----------------------------------------------------------------------------------------

#define CREATE_TEXTPANEL_DATA( TheName, TheRsrcID, TheSelRsrcID, TheRsrcPluginID, TheDialogType ) \
	class TheName : public ITextPanelData \
	{ \
	public: \
		inline			TheName(IPMUnknown *boss) : HELPER_METHODS_INIT( boss ) { fRsrcID = TheRsrcID; fSelRsrcID = TheSelRsrcID; fRsrcPluginID = TheRsrcPluginID; fDlgType = TheDialogType; } \
	protected:	 \
		virtual RsrcID				GetTextResourceID() const { return fRsrcID; } \
		virtual PluginID				GetTextResourcePluginID() const { return fRsrcPluginID; } \
		virtual IDialog::DialogType	GetTextDialogType() const { return fDlgType; } \
		virtual void 				SetTextResourceID( RsrcID rsrcID ) { fRsrcID = rsrcID; } \
		virtual void 				SetTextResourcePluginID( const PluginID& pluginID ) { fRsrcPluginID = pluginID; } \
		virtual void				SetTextDialogType( IDialog::DialogType dialogType ) { fDlgType = dialogType; } \
		virtual RsrcID				GetTextSelectableID() const { return fSelRsrcID; } \
		virtual void 				SetTextSelectableID( RsrcID rsrcID ) { fSelRsrcID = rsrcID; } \
	private: \
		RsrcID			fRsrcID; \
		PluginID			fRsrcPluginID; \
		IDialog::DialogType	fDlgType; \
		RsrcID			fSelRsrcID; \
	DECLARE_HELPER_METHODS() \
	}; \
	DEFINE_HELPER_METHODS( TheName )

#endif
