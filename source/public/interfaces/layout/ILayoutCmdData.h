//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutCmdData.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Command data interface for commands that operate on an ILayoutControlData.
//  
//========================================================================================

#pragma once
#ifndef __ILayoutCmdData__
#define __ILayoutCmdData__

#include "IPMUnknown.h"
#include "CommandID.h"

class ILayoutControlData;

/**	
	Command data interface used to pass layout data information to various commands 
 */
class ILayoutCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILAYOUTCMDDATA };
	

	/**	 Set command data
		@param doc UIDRef of the document the command will change
		@param *layoutData LayoutControlData pointer that passed into the command
							could be nil if the command don't need layout data (for example: used in scripting) 
	 */
	virtual void Set(const UIDRef& doc, ILayoutControlData *layoutData) = 0;

	/**	 Get layout control data
		@param none
		@return ILayoutControlData. Usually used in commands to fetch layoutcontroldata 
	 */
	virtual ILayoutControlData *GetLayoutControlData() = 0;

	/**	 Get document UIDRef
		@param none
		@return const UIDRef of the document
	 */
	virtual const UIDRef& GetDocument() const = 0;
};


#endif // __ILayoutCmdData__
