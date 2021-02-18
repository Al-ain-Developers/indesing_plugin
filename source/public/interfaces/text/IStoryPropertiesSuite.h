//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStoryPropertiesSuite.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IStoryPropertiesSuite__
#define __IStoryPropertiesSuite__

#include "IPMUnknown.h"
#include "ITextOptions.h"	// for WritingDirection enum
#include "K2Vector.h"
#include "ShuksanID.h"

//========================================================================================
// Forward declarations
//========================================================================================


//========================================================================================
// CLASS IStoryPropertiesSuite
//========================================================================================

/**
	@ingroup text_story
	@ingroup text_suite
*/
class IStoryPropertiesSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTORYPROPERTIESSUITE };

	enum GenericBooleanState { kStateUnknown, kStateOff, kStateOn, kStateMixed };

	/** Whether the optical margin alignment widget should be enabled in the Story panel
	@return kTrue if widget should be enabled
	*/
	virtual bool16 ShouldEnableOpticalMarginAlignment() const = 0;
	/** Gets the optical margin alignment story attribute on or off
	@return kStateOn if on
	*/
	virtual GenericBooleanState GetOpticalMarginAlignment() const = 0;
	/** Sets the optical margin alignment story attribute on or off
	@param bAlign the state of the alignment of selected stories
	@return error if operation failed
	*/
	virtual ErrorCode SetOpticalMarginAlignment(GenericBooleanState bAlign) = 0;

	/** Whether the optical margin alignment size widget should be enabled in the Story panel
	@return kTrue if widget should be enabled
	*/
	virtual bool16 ShouldEnableOpticalMarginAlignmentSize() const = 0;
	/** Gets the optical margin alignment size story attribute
	@return ptr to array of sizes
	*/
	virtual K2Vector<PMReal> *GetOpticalMarginAlignmentSize() const = 0;
	/** Sets the optical margin alignment size story attribute
	@param alignmentSize [IN] size, in points, of the average body text in the story
	@return error if operation failed
	*/
	virtual ErrorCode SetOpticalMarginAlignmentSize(PMReal alignmentSize) = 0;

	//-----------------------------------------------------------------------------------------------
	enum TextDirection { kDirUnknown, kDirHorizontal, kDirVertical, kDirMixed };
	/** Whether the text direction widget should be enabled in the Story panel (Japanese featureset)
	@return kTrue if widget should be enabled
	*/
	virtual bool16 ShouldEnableTextDirection() const = 0;
	/** Gets the text direction of the story (Japanese featureset)
	@return text direction (enum)
	*/
	virtual TextDirection GetTextDirection() const = 0;
	/** Sets the text direction of the story (Japanese featureset)
	@param dir [IN] text direction to be set
	@return error if operation failed
	*/
	virtual ErrorCode SetTextDirection(TextDirection dir) = 0;

	//-----------------------------------------------------------------------------------------------
	enum StoryDir { kLTRDirection = 0, kRTLDirection = 1, kUnknownDirection = 2, kMixedDirection = 3 };

	// Abilities
	virtual bool16 ShouldEnableStoryDirection() const = 0;
	virtual StoryDir GetStoryDirection() const = 0;

	// Manipulators
	virtual ErrorCode SetStoryDirection(StoryDir dir) = 0;

	//-----------------------------------------------------------------------------------------------
	enum FrameType { kFrameTypeUnknown, kFrameTypePlain, kFrameTypeCJKGrid, kFrameTypeMixed };
	/** Whether the frame type widget should be enabled in the Story panel (Japanese featureset)
	@return kTrue if widget should be enabled
	*/
	virtual bool16 ShouldEnableFrameType() const = 0;
	/** Gets the frame type of the story (Japanese featureset)
	@return frame type (enum)
	*/
	virtual FrameType GetFrameType() const = 0;
	/** Sets the frame type of the story (Japanese featureset)
	@param dir [IN] frame type to be set
	@return error if operation failed
	*/
	virtual ErrorCode SetFrameType(FrameType frameType) = 0;

	/** Whether the story attribute lock can be set
	@return kTrue if it can be set
	*/
	virtual bool16 CanSetStoryAttributeLock() const = 0;
	/** Whether the story insert lock can be set
	@return kTrue if it can be set
	*/
	virtual bool16 CanSetStoryInsertLock() const = 0;

	/** Gets the story attribute lock
	@return kStateOn if on
	*/
	virtual GenericBooleanState GetStoryAttributeLock() const = 0;
	/** Gets the story insert lock
	@return kStateOn if on
	*/
	virtual GenericBooleanState GetStoryInsertLock() const = 0;

	/** Sets the story attribute lock
	@param locked kStateOn if on
	@return error if operation failed
	*/
	virtual ErrorCode SetStoryAttributeLock(GenericBooleanState locked) = 0;
	/** Sets the story insert lock
	@param locked kStateOn if on
	@return error if operation failed
	*/
	virtual ErrorCode SetStoryInsertLock(GenericBooleanState locked) = 0;
};

#endif
