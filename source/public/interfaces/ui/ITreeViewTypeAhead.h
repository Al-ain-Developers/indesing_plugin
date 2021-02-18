//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITreeViewTypeAhead.h $
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
#ifndef __ITreeViewTypeAhead__
#define __ITreeViewTypeAhead__

#include "IPMUnknown.h"
#include "widgetid.h"
#include "NodeID.h"

//----------------------------------------------------------------------------------------
// ITreeViewTypeAhead
//----------------------------------------------------------------------------------------

/** Interface that enables a treeview to handle typeahead to select a node that correlates
	to a keystroke typed when TreeView has focus.  This interface provides the mapping between
	a nodeID and a string associated with the node.

	Client code wishing to allow typeahead in their Tree should implement this interface
*/
class ITreeViewTypeAhead : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITREEVIEWTYPEAHEAD };
	
	/** Given a node, this method returns a string associated with the text content
		of that node.  This string will be used to compare against for type ahead behavior 
		@return PMString that represents the nodes text content
	*/
	virtual PMString	GetStringForNode( const NodeID& node ) const = 0;

};	

#endif // __ITreeViewTypeAhead__
