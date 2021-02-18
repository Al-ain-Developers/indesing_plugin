//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/AbstractTextControlData.h $
//  
//  Owner: Michael Burbidge
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __AbstractTextControlData_h__
#define __AbstractTextControlData_h__

#include "ITextControlData.h"
#include "HelperInterface.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

//========================================================================================
// CLASS AbstractTextControlData
//
// This is an abstract implementation of ITextControlData from which most other
// implementation should derive. It supports translation from the english key for the
// string it stores to a foreign string. The string value is not stored in this class. It
// is expaected that derived classes will implement classes that actually store string
// state. Other derived classes may just wrap system controls which store the state.
//
// Change is called whenever the value of the text data changes. Change by default calls
// DoNotify which sends a standard notification to observers. Change also calls
// DoInvalidate which invalidates this widget.
//
// Most subclasses should only need to override DoSetString and GetString. DoSetString is
// passed an already translated string.
//
//========================================================================================

class DV_WIDGET_DECL AbstractTextControlData : public ITextControlData
{
public:
	AbstractTextControlData(IPMUnknown *boss);
	~AbstractTextControlData();
	
	virtual void SetString(const PMString& newString, bool16 invalidate, bool16 notifyOfChange, bool16 isGoodString);

protected:
	virtual void DoSetString(const PMString& string, bool16 isGoodString) = 0;
	
	virtual void Changed(bool16 invalidate, bool16 notifyOfChange);
	virtual void DoNotify(bool16 notifyOfChange);
	virtual void DoInvalidate(bool16 invalidate);

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
