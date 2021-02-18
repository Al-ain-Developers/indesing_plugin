//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IStyleInfoMapData.h $
//  
//  Owner: Yeming Liu
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
//  Comments: Data interface for storing a map between style name(key) and doc name(value).
//  
//========================================================================================

#pragma once
#ifndef __ISTYLEINFOMAPDATA__
#define __ISTYLEINFOMAPDATA__

#include "IPMUnknown.h"

#include "TOCID.h"
#include "KeyValuePair.h"
#include "K2Vector.h"

class PMString;

typedef K2Vector<KeyValuePair<PMString, PMString> >  StyleInfoMap;

/** This data interface is for accessing the map of style name and document name information 
    used for get unique para/char style names among all the documents within a book.

	@see kGetUniqueStyleNamesOfBookCmdBoss and kTOCUIDialogBoss.
*/
class IStyleInfoMapData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTYLEINFOMAPDATA };

		/**	Set the map into the data interface.
			@param newMap IN the new map to set.
		*/
		virtual void SetStyleInfoMap(const StyleInfoMap& newMap) = 0;

		/**	Get the map from the data interface.
			@param none
			@return StyleInfoMap& the map about style name and document name information.
		*/
		virtual const StyleInfoMap& GetStyleInfoMap() = 0;
};

#endif // __ISTYLEINFOMAPDATA__
