//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGraphicFrameData.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IGRAPHICFRAMEDATA__
#define __IGRAPHICFRAMEDATA__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "GraphicsID.h"

class ICommand ;
class IMultiColumnTextFrame ;

class IGraphicFrameData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGRAPHICFRAMEDATA };
	
	/** Interface on all spline page items indicating if the item is considered a frame. 
		@return bool16, Returns kTrue if item is a graphic frame (draws with an 'x'), kFalse if not.
	*/
	virtual bool16 IsGraphicFrame() const = 0;

	/** Set method for turning a non-frame into a frame. See also kSetGraphicFrameDataCmdBoss.
		@param bool16 kTrue to change to a graphic frame, kFalse to change to a non-frame.
	*/
	virtual void SetGraphicFrame(bool16 isGraphicFrame) = 0;

	/** Determines if a graphic frame has content, which is true if the frame has children 
		in its hierarchy.
		@return bool16, Returns kTrue if frame has content, kFalse if not.
	*/
	virtual bool16 HasContent() const = 0;

	/** Determines if a graphic frame has placeholder content, which is true if the frame has a
		kPlaceHolderItemBoss as its child.
		@return bool16, Returns kTrue if frame has placeholder content, kFalse if not.
	*/
	virtual bool16 HasPlaceHolderContent() const = 0;

	/** Determines if a frame is a text frame.
		This method is an alias to GetMCTextFrameUID. This method does nothing except "return GetMCTextFrameUID()".
		@return UID, Returns UID child text frame (IMultiColumnTextFrame), kInvalidUID if not a text frame.
	*/
	virtual UID GetTextContentUID() const = 0;

	/** Determines if a frame is a text frame.
		@return UID, Returns UID child text frame (IMultiColumnTextFrame), kInvalidUID if not a text frame.
	*/
	virtual UID GetMCTextFrameUID() const = 0;

	/** Determines if a frame is a text frame.
		@return IMultiColumnTextFrame*, Return the child text frame (IMultiColumnTextFrame), nil if not a text frame.
	*/
	virtual	IMultiColumnTextFrame* QueryMCTextFrame() const = 0;

	/** Determines if a frame may be split. Used by scissors and eraser tools.
		@return bool16, returns kTrue if this object's path may be split into multiple objects with the given parent, kFalse otherwise.
						If parent == nil, the object's current parent is assumed.
	*/
	virtual bool16 IsSplitAllowed( const UIDRef* parent = nil ) const = 0 ;

	/** Determines if a frame's paths may be converted to compound path during copy.
		@return bool16, returns kTrue if parts of this object's path may be combined into a compound path during a copy, kFalse otherwise.
	*/
	virtual bool16 IsCopyToCompoundPathAllowed() const = 0 ;

	/** Determines if a frame's path may be converted to a compound path.
		@return bool16, returns kTrue if this object may be incorporated into a compound path, kFalse otherwise.
	*/
	virtual bool16 IsMakeCompoundPathAllowed() const = 0 ;

	/** Determines if a frame's paths may be released from a compound path.
		@return bool16, returns kTrue if this object may be released from a compound path, kFalse otherwise.
	*/
	virtual bool16 IsReleaseCompoundPathAllowed() const = 0 ;

	/** This method gives the object an opportunity to make itself temporarily copyable when
		only a part (or parts) of an object will be copied (e.g., multiple discontiguous points
		or segments selected). If parent == nil, the object's current parent is assumed. Caveat
		emptor: One or both of these methods may legitimately return nil. Also, it's legitimate
		for the implementation to expect that these methods will be called in consecutive pairs
		@return ICommand*, returns command, may return nil.
	*/
	virtual ICommand* CreateSetupPartialCopyCommand( const UIDRef* parent = nil ) = 0 ;

	/** This method gives the object an opportunity to make itself temporarily copyable when
		only a part (or parts) of an object will be copied (e.g., multiple discontiguous points
		or segments selected). If parent == nil, the object's current parent is assumed. Caveat
		emptor: One or both of these methods may legitimately return nil. Also, it's legitimate
		for the implementation to expect that these methods will be called in consecutive pairs
		@return ICommand*, returns command, may return nil.
	*/
	virtual ICommand* CreateCleanupPartialCopyCommand( const UIDRef* parent = nil ) = 0 ;
} ;

#endif