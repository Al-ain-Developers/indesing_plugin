//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGalleySwitch.h $
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
#ifndef __IGalleySwitch__
#define __IGalleySwitch__

#include "IPMUnknown.h"
#include "WritingModeUIID2.h"
#include "WritingModeID2.h"
#include "PMPoint.h"
#include "UIDList.h"

const ClassID kSwitchedToGalley = 'SwGl';	// these are broadcast by IGalleySwitch after it switches
const ClassID kSwitchedToLayout = 'SwLy';
const ClassID kSwitchingToGalley = 'SwGb';	// these are broadcast by IGalleySwitch before it switches
const ClassID kSwitchingToLayout = 'SwLb';
const ClassID kPreSwitchGalleyStory = 'BSGS'; // Broadcast before story switch in galley
const ClassID kPostSwitchGalleyStory = 'ASGS'; // Broadcast after story switch in galley

class IControlView;
class IFocusCache;
class ITextModel;
class IWaxRun;
class IDocument;

#define kMinPrintGalleyHeight 500

/** 
	Don't recommend using this interface now. IGalleyUtils provides everything available in this interface and
	more. Some of this plain won't work in this interface
*/
class IGalleySwitch : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IGALLEYSWITCH};
	
	/** 
		Used as a invalid id number in ILayoutViewLineData
	*/
	enum {kInvalidUniqueID = 0};

	/**	Obsolete don't use.
		@param stories - don't use
		@return don't use
	*/
	virtual ErrorCode OpenNewGalleyWindow(const UIDList &stories) = 0;

	/**	Obsolete don't use.
		@return kFalse
	*/
	virtual bool IsInGalley() = 0;
				
	/**	Obsolete don't use.
		@param index - dont use
		@return none
	*/
	virtual void SetGalleyStoryIndex(int32 index) = 0;
	
	/**	Obsolete don't use.
		@return -1
	*/
	virtual int32 GetGalleyStoryIndex() = 0;
	
	/**	Obsolete don't use.
		@return current active story index
	*/
	virtual UIDRef GetCurrentStoryRef() = 0;
	
	/**	Best to use Galley Utils now.
		@return control view of galley or story view for the front window
	*/
	virtual IControlView *GetGalleyView() = 0;
	
	/**	Just a unique number everytime you ask. Simply increments a number
		@return id
	*/
	virtual uint32 GetUniqueSessionID() = 0;
};

#endif 		// __IGalleySwitch__
