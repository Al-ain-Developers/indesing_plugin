//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IPasteTextCmdData.h $
//  
//  Owner: Eric_Kenninga
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
#ifndef __IPasteTextCmdData__
#define __IPasteTextCmdData__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2SmartPtr.h"

class PasteData;

/** Used to hold the data to paste into a text story with the PasteTextCmd
	@ingroup text_story
*/
class IPasteTextCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPASTETEXTCMDDATA };
	
			// Set the data to paste. This data is difficult to generate in any manner
			// other than as a result of ITextModel::CopyRange()
			// *** The interface takes ownership of the data. DO NOT DELETE this data
			// after setting into this interface
		virtual void Set(const boost::shared_ptr<PasteData> &data) = 0;

			// grab the pointer to the data, don't edit or delete it
		virtual boost::shared_ptr<PasteData> GrabData() const = 0;
};

#endif
