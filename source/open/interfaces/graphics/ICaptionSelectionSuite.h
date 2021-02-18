//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/graphics/ICaptionSelectionSuite.h $
//  
//  Owner: Michael Martz
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
	#ifndef _ICaptionSelectionSuite_
	#define _ICaptionSelectionSuite_

#include "IPMUnknown.h"
#include "LinksID.h"

/** Provides interface to return list of selected graphic frames that could be captioned.
*/
class ICaptionSelectionSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ICAPTIONSELECTIONSUITE };

		/** Get UIDs of appropriate graphic frames for captioning.
		 */
		virtual UIDList GetUIDsSuitableForCaptioning() const = 0;

		/** Check if there are selected text frames containing caption text variables
		 */
		virtual bool CanConvertCaptionVariablesInTextFrame() const = 0;

		/** convert caption text variables in selected text frames to text
		 */
		virtual ErrorCode ConvertCaptionVariablesInTextFrameToText() = 0;
	};

#endif // _ICaptionSelectionSuite_
