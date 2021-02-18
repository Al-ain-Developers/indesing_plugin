//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVTristateControlView.h $
//  
//  Owner: Vadim Tkachev
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __DVTristateControlView__
#define __DVTristateControlView__

#include "DVHostedWidgetView.h"
#include "ITriStateControlData.h"


// DVTriStateControlView
class DV_WIDGET_DECL DVTristateControlView : public DVHostedWidgetView
{
	typedef DVHostedWidgetView inherited;

public:
			 DVTristateControlView( IPMUnknown* boss );
	virtual ~DVTristateControlView( void );
	
	virtual void DoPostCreate( void );
	
	/** called when the underlying control implementation's value changes */
	virtual void OnValueChanged(); 
	
protected:
	/** Internal use only */
	//Subclasses should override following functions to set text and tri state to the dv control, here default impl is empty.
	virtual void SetTriStateOnDVControl(ITriStateControlData::TriState triState) { }
	virtual void SetFontOnDVControl();
	virtual void SetLabelOnDVControl(const PMString& label) {}
	virtual void SetCustomFontSizeOnDVControl(float inFontSize) {}
};

// DVCheckBoxView
class DV_WIDGET_DECL DVCheckBoxView : public DVTristateControlView
{
	typedef DVTristateControlView inherited;
	
public:
			DVCheckBoxView( IPMUnknown* boss );
	
	virtual ~DVCheckBoxView( void );
	
protected:
	virtual bool16 GetTriState();
	virtual void SetTriState(bool16 state);
	
private:
	virtual void SetTriStateOnDVControl(ITriStateControlData::TriState triState);
	virtual void SetLabelOnDVControl(const PMString& label);
	virtual void SetCustomFontSizeOnDVControl(float inFontSize);

	dvaui::controls::UI_Checkbox* Get_UI_CheckBox();
};

// DVRadioButtonView
class DV_WIDGET_DECL DVRadioButtonView : public DVTristateControlView
{
	typedef DVTristateControlView inherited;
	
public:
			 DVRadioButtonView( IPMUnknown* boss );
	
	virtual ~DVRadioButtonView( void );
	
private:
	virtual void SetTriStateOnDVControl(ITriStateControlData::TriState triState);
	virtual void SetLabelOnDVControl(const PMString& label);
	virtual void SetCustomFontSizeOnDVControl(float inFontSize);

	dvaui::controls::UI_RadioButton* Get_UI_RadioButton();
};

#endif