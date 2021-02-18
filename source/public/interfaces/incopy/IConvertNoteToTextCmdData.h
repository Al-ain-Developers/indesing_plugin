//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IConvertNoteToTextCmdData.h $
//  
//  Owner: Cindy Chen
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
//  Purpose: Interface data for copying the note data
//  
//========================================================================================

#pragma once
#ifndef __IConvertNoteToTextCmdData__
#define __IConvertNoteToTextCmdData__

#include "IPMUnknown.h"
#include "NoteID.h"

/** Command data interface. Set/get data fro command kSplitNoteCmdBoss, kConvertNoteToTextCmdBoss
*/
class IConvertNoteToTextCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICONVERTNOTETOTEXTCMDDATA };
			
/**	Get method to get the current document control view.
	@param none
	@return UIDRef 
 */
		virtual UIDRef	GetDocControlViewRef() = 0;

/**	Set method to set the current document control view.
	only set this field if current doc view is galley view to suspend redraw while note converting to text)
	@param viewRef 
 */
		virtual void	SetDocControlViewRef(UIDRef viewRef) = 0;

};

#endif	// __IConvertNoteToTextCmdData__