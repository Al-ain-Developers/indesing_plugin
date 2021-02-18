//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICompositionType.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __ICompositionType__
#define __ICompositionType__

#include "IPMUnknown.h"

#ifdef ID_DEPRECATED // no longer use and will dissappear from future versions of InDesign

/** 
	Don't use this interface no longer works and will be removed (obsolete)
*/
class ICompositionType : public IPMUnknown
{
	public:
		enum TypeComposition {perParagraph, perPublication};

		virtual void SetCompositionType(TypeComposition compType) = 0;
		virtual TypeComposition GetCompositionType() = 0;
		
		virtual void SetPubComposer(ClassID composerID) = 0;
		virtual ClassID GetPubComposer() = 0;
		
		// Used for switching to the layout view normal paragraph composers temporarily.
		virtual void SetTempOverride(bool8 tempOverride) = 0;
		virtual bool8 GetTempOverride() = 0;		
};
#endif

#endif __ICompositionType__