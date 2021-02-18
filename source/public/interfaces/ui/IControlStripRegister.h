//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IControlStripRegister.h $
//  
//  Owner: Paul Sorrick
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
//  Note:
//  
//========================================================================================

#pragma once
#ifndef __ICONTROLSTRIPREGISTER__
#define __ICONTROLSTRIPREGISTER__

#include "IPMUnknown.h"
#include "ControlStripID.h"
#include "ControlStripWidgetInfo.h"
#include "K2Vector.h"

class IControlStripRegister : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONTROLSTRIPREGISTER };
	
	/**	Get the list of IIDs and names of control sets for IControlStripWidgetSuite interfaces that this plug-in provides.
		When a selection change message occurs, an attempt will be made to instantiate
		an IControlStripWidgetSuite interface with this IID in the active CSB. 
		If it exists, its GetEnabledWidgets function will be called.
		The ControlSetList is used to allow user-customizability of which control sets appear in the control strip.
		User may turn them off as desired, though all are visible initially. Suite should add all the control sets
		that it can provide in its GetEnabledWidgets function.
		See IControlStripWidgetSuite.h, GetEnabledWidgets.

		@param IIDList list of suite IIDs.
	 */
	virtual void		GetRegisteredControlStripWidgetSuites (K2Vector<PMIID>& IIDList, K2Vector<ControlStripWidgetInfo>& controlSetList) const = 0;

};

#endif // __IControlStripWidgetSuite__
