//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IWidgetParent.h $
//  
//  Owner: Frits Habermann
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
#ifndef __IWidgetParent__
#define __IWidgetParent__

#include "IPMUnknown.h"
#include "widgetid.h"

/** Interface to allow traversing widget hierarchy.
*/
class IWidgetParent : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IWIDGETPARENT };

	/** Do QueryInterface up the hierarchy until the interfaceID is found, or 
		until the root node is reached.
		@return reference-incremented ptr to interface with given identifier, or nil if it can't be found
	*/
	virtual IPMUnknown *QueryParentFor(const PMIID& interfaceID) const = 0;
	 

	/** Accessor for parent of widget
		@return interface ptr of parent 
	*/
	virtual IPMUnknown *GetParent() const = 0;

	/** Query for parent of given widget.
		@return reference-incremented interface ptr of parent 
	*/
	virtual IPMUnknown *QueryParent() const = 0;

	/**	Specify a new parent for given widget.
		@param parent new parent
		@param invalidateTransform whether to invalidate widget transform or not. Default is true, only reason to turn it to false would be during construction or destruction.
	*/
	virtual void SetParent(IPMUnknown *parent, bool16 invalidateTransform = kTrue) = 0;
};

#endif