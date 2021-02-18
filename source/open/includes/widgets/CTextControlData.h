//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/CTextControlData.h $
//  
//  Owner: Frits Habermann, Michael Burbidge
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
#ifndef __CTextControlData_h__
#define __CTextControlData_h__

#include "AbstractTextControlData.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

//========================================================================================
// CLASS CTextControlData
//========================================================================================

class DV_WIDGET_DECL CTextControlData : public AbstractTextControlData
{
public:
	CTextControlData(IPMUnknown *boss);
	~CTextControlData();
	
	virtual void					ReadWrite(IPMStream *s, ImplementationID prop);
	virtual const PMString& 	GetString() const;

protected:
	virtual void					DoSetString(const PMString& string, bool16 isGoodString);

	//DoSetWidgetString sets the passed argument newString the DV widget control after translating it, the caller of this function 
	//has the responsibility to set the new string to fMyString, so that DV Control String and fMyString are in sync.
	virtual void					DoSetWidgetString (const PMString& newString);

protected:
	PMString	fMyString;
};

#pragma export off

#endif
