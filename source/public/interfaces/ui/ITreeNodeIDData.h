//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITreeNodeIDData.h $
//  
//  Owner: Matt Joss
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
//  Interface for storing NodeIDs for the Tree Control.
//  
//========================================================================================

#pragma once
#ifndef __ITreeNodeIDData__
#define __ITreeNodeIDData__

#include "IPMUnknown.h"
#include "NodeID.h"
#include "widgetid.h"

/** Interface for storing NodeIDs.  This interface is found on TreeNode widgets that are used inside
	the TreeView widget.  Each TreeNode widget has an ITreeNodeIDData interface which stores the NodeID
	that the widget represents
*/
class ITreeNodeIDData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITREENODEIDDATA };

	/**
		Give the interface a NodeID to hold onto
	
		@param	dataHolder is the NodeID saved in the interface
	*/
	virtual void				Set( const NodeID& dataHolder) = 0;

	/**
		Get the NodeID that the interface is holding onto
	
		@return	NodeID& returns the NodeID that the interface has saved
	*/
	virtual const NodeID&		Get() const = 0;
};



#endif // __ITreeNodeIDData__
