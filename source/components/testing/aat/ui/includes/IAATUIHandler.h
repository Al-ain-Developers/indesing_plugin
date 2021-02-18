//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/ui/includes/IAATUIHandler.h $
//  
//  Owner: robin briggs
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
//  
//  Interface for storing UIDs.
//  
//========================================================================================

#pragma once
#ifndef __IAATUIHandler__
#define __IAATUIHandler__

#include "IPMUnknown.h"

class IControlView;
class IPanelControlData;
class VAcquisitionElement;

class  IAATUIHandler : public IPMUnknown
{
public:
	virtual ~IAATUIHandler(void) {}
	
	virtual void	GetWidgetUIString(PMString &str) = 0;
	
	virtual bool16	IsSupportedToken(const PMString &token) = 0;
	virtual void	GetSupportedTokens(K2Vector<PMString> &ids) = 0;
	virtual void	GetSupportedClassIDs(K2Vector<ClassID> &idVector) = 0;
	virtual void	GetSupportedWidgetIDs(K2Vector<WidgetID> &idVector) = 0;
	
	virtual VAcquisitionElement*	AcquireView(IControlView *cntrl, bool16 *acquireSubView) = 0;
	
	virtual void	SetName(VAcquisitionElement *elem, IControlView *view) = 0;
	
	virtual void	SetValue(VAcquisitionElement *elem, IControlView *view) = 0;
	virtual void	GetValueAsString(IControlView *view, PMString *value) = 0;
};



#endif // __IAATUIHandler__
