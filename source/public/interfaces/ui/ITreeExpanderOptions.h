//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITreeExpanderOptions.h $
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
//========================================================================================

#pragma once
#ifndef __ITreeExpanderOptions__
#define __ITreeExpanderOptions__

#include "widgetid.h"
#include "IPMUnknown.h"

//========================================================================================
// CLASS ITreeExpanderOptions
//========================================================================================
/** Stores and returns expansion related options for the treeview boss upon which this interface is aggregated
*/
class ITreeExpanderOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITREEEXPANDEROPTIONS };

	
	/**
		Returns whenther a Cmd-Click on the expander will affect that nodes child nodes
	
		@return	bool16 if kTrue, when the user Cmd-clicks on the expander, all descendants of the node that was expanded will also be expanded.
			if kFalse, only the node clicked will be expanded, i.e. holding Cmd will do nothing different.
	*/
	virtual	bool16		CmdClickAffectsChildNodes() const = 0;
	
	/**
		Returns whether or not the treeview will scroll to attempt to show all children of the just expanded node
	
		@return	bool16 if kTrue, the tree view will scroll to show all children of the expanded node if there are more children than will fit in the tree view at the time, the tree view
			will scroll such that the expanded node is the top visible node in the tree.  if kFalse, the node will expand in place and no scrolling will occur
	*/
	virtual	bool16		ScrollExpandedNodeToShowChildren() const= 0;
};


#endif
