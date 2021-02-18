//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITOPSplineData.h $
//  
//  Owner: Michel Hutinel
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
#ifndef __ITOPSplineData__
#define __ITOPSplineData__

#include "IPMUnknown.h"
#include "TextOnPathID.h"


/** Interface for accessing the page items associated with this path.
	@ingroup text_onpath
*/
class ITOPSplineData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITOPSPLINEDATA };

	/** Set the UID of the main spline for this path.
		@param mainSplineItemUID [IN]: new spline.
	*/
	virtual void		SetMainSplineItemUID( UID mainSplineItemUID ) = 0;

	/** Get the UID of the main spline associated with this path.
		@return UID of existing spline item associated with this path
	*/
	virtual UID			GetMainSplineItemUID() const = 0;

	/** Get the UID of the frame item for this path.
		The frame item is the grand children of the main spline item. 
		The query hierarchy works as follows: kTOPSplineItemboss->kMulticolumnItemBoss->kTOPFrameItemBoss.
		@return UID of existing text on path frame item.
	*/
	virtual UID			GetTOPTextFrameColumnUID() const = 0;
} ;

#endif //__ITOPSplineData__
