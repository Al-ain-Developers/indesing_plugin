//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISmartDimensions.h $
//  
//  Owner: Dave Stephens
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
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
#ifndef __ISmartDimensions__
#define __ISmartDimensions__

#include "IPMUnknown.h"
#include "ISnapTo.h"

#include "SpreadUIID.h"

class ISpread;
class PMPoint;
class PMLineSeg;

class ISmartDimensions : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISMARTDIMENSIONS };
	
	/** Clear all data.
	*/
	virtual void Clear() = 0;

	/** Set the current database
		@param db [IN]: The current database that holds all UIDs passed into AddInfo.
	*/
	virtual void SetDataBase(IDataBase *db) = 0;

	/** Add bounding box and matrix info for a specific page item.
		@param pageItem [IN]: UID of the page item whose info we are recording.
		@param bbox [IN]: stroke bounding box in pasteboard coordinates.
		@param xform [IN]: Matrix used to transform the page item from inner to pasteboard coordinates.
	*/
	virtual void AddInfo(const UID& pageItem, const PBPMRect& bbox, const PMMatrix& xform) = 0;

	/** Add bounding box and matrix info from an existing ISmartDimensions interface to this interface.
		@param source [IN]: Pointer to the interface whose data we want to copy
	*/
	//virtual void AddInfo(const ISmartDimensions* source) = 0;

	/** Get and append UID's of page items whose stroke bounding box in pasteboard coordinates has a width that
		exactly matches the provided target width.
		@param targetWidth [IN]: The target width.
		@param matchingItems [OUT]: Any page items whose stroke bounding box in pasteboard coordinates 
			matches the target width
		@return the number of items appended (found).
	*/
	virtual int32 GetItemsMatchingWidth(const PMReal& targetWidth, UIDList& matchingItems) const = 0;

	/** Get and append UID's of page items whose stroke bounding box in pasteboard coordinates has a height that
		exactly matches the provided target height.
		@param targetHeight [IN]: The target height.
		@param matchingItems [OUT]: Any page items whose stroke bounding box in pasteboard coordinates 
			matches the target height
		@return the number of items appended (found).
	*/
	virtual int32 GetItemsMatchingHeight(const PMReal& targetHeight, UIDList& matchingItems) const = 0;

	/** Get and append UID's of page items whose rotation in pasteboard coordinates
		exactly matches the provided target rotation.
		@param targetRotation [IN]: The target rotation.
		@param matchingItems [OUT]: Any page items whose rotation in pasteboard coordinates
			matches the target rotation
		@return the number of items appended (found).
	*/
	virtual int32 GetItemsMatchingRotation(const PMReal& targetRotation, UIDList& matchingItems) const = 0;

	/** Get the width of the closest matching page item in pasteboard coordinates. If no matching item is found,
		return 0.0.
		@param targetWidth [IN]: the target width
		@param ignoreList [IN]: List of items to ignore. Usually the selection list.
		@return width of the closest matching item or 0.0 if one is not found.
	*/
	virtual PMReal GetClosestWidth(const PMReal& targetWidth, const UIDList& ignoreList) const = 0;

	/** Get the height of the closest matching page item in pasteboard coordinates. If no matching item is found,
		return 0.0.
		@param targetHeight [IN]: the target height
		@param ignoreList [IN]: List of items to ignore. Usually the selection list.
		@return height of the closest matching item or 0.0 if one is not found.
	*/
	virtual PMReal GetClosestHeight(const PMReal& targetHeight, const UIDList& ignoreList) const = 0;

	/** Get the height of the closest matching page item in pasteboard coordinates. If no matching item is found,
		return 0.0.
		@param targetHeight [IN]: the target height
		@param ignoreList [IN]: List of items to ignore. Usually the selection list.
		@return height of the closest matching item or 0.0 if one is not found.
	*/
	virtual PMReal GetClosestRotation(const PMReal& targetRotation, const UIDList& ignoreList) const = 0;
};

#endif
