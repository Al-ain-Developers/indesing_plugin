//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICreateTFCData.h $
//  
//  Owner: eric_menninga
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
#ifndef __ICreateTFCData__
#define __ICreateTFCData__

#include "IPMUnknown.h"
#include "TextID.h"


/** This data interface is used when creating a TextFrameColumn. To create a
	MultiColumnTextFrame, see ICreateMCFrameData.h.
	@ingroup text_layout
*/
class ICreateTFCData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICREATETFCDATA };

		/**	SetFrameList is used when creating a new TextFrameColumn
		@param framelist the UID of the frameList to insert into. Must be valid
		@param insertAt the index of the new TextFrameColumn to create within the frameList or IFrameList::kAtEnd
		 */
		virtual void	SetFrameListData(const UIDRef& framelist,
										int32 insertAt) = 0;

		/**	Get the FrameList passed nto SetFrameList().
		@return the UID of the frame list.
		 */
		virtual UIDRef	GetFrameListRef() const = 0;

		/**	
		This is the index to insert the new frame at.
		@return the index to use in the frame list.
		 */
		virtual int32	GetInsertIndex() const = 0;

};

#endif
