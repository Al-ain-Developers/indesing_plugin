//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISpreadHistoryFlagData.h $
//  
//  Owner: tommyd
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
#ifndef __ISpreadHistoryFlagData__
#define __ISpreadHistoryFlagData__

#include "IPMUnknown.h"

/** ISpreadHistoryFlagData is an interface that lets us know if the SetSpreadCmd (kSetSpreadCmdBoss)
	or SetPageCmd (kSetPageCmdBoss) is being executed because of a Go Back or Go Forward command.
	@ingroup layout_history
*/
class ISpreadHistoryFlagData : public IPMUnknown
{
public:
	virtual bool16 GetCalledBySpreadHistory() = 0;
		//	Returns TRUE if the 'Go Back' or 'Go Forward' command 
		//	caused the SetSpreadCmd to be executed.
		
	virtual void SetCalledBySpreadHistory(bool16) = 0;
		//	Set the flag that indicates whether or not the 'Go Back' or
		//	'Go Forward' command caused the SetSpreadCmd to be executed.
};


#endif // __ISpreadHistoryFlagData__
