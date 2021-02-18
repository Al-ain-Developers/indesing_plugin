//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/INewHLExternPageDestCmdData.h $
//  
//  Owner: Jianlan Song
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

#include "HyperlinkID.h"
#include "IPMUnknown.h"

// ===================================================================================
//	class INewHyperlinkPageDestCmdData
// ===================================================================================
/** Command data interface, set/get the page destination data for the command kNewHyperlinkPageDestCmdBoss
*/
class INewHLExternPageDestCmdData : public IPMUnknown {

//-----------------------------------
//	Constants
//
public:
	enum {kDefaultIID = IID_INEWHLEXTERNPAGEDESTCMDDATA};

//-----------------------------------
//
public:

	/**	Get destination unique key
		@return int32 unique key
	 */
	virtual int32 GetUniqueKey() const = 0;
	/**	Set unique key value
		@param unique key
	 */
	virtual void SetUniqueKey(int32 uniqueKey) = 0;
		
};


