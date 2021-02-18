//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAlignAndDistributeSuite.h $
//  
//  Owner: Paul Sorrick
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
#ifndef __IAlignAndDistributeSuite__
#define __IAlignAndDistributeSuite__

#include "IPMUnknown.h"
#include "IAlignCmdData.h"
#include "IDistributeCmdData.h"
#include "UIDRef.h"
#include "ShuksanID.h"

/**
	@ingroup layout_suite
*/
class IAlignAndDistributeSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IALIGNANDDISTRIBUTESUITE };

	
// ----- Abilities
	
	/**	Returns kTrue if DoAlign() can be called, kFalse otherwise..
		@param alignHow - how to align the objects, see IAlignCmdData
		@return bool16 
	 */
	virtual bool16 CanAlign (AlignType alignHow) const = 0;

	/**	Returns kTrue if DoDistribute() can be called, kFalse otherwise..
		@param distributeHow - how to distribute the objects, see IDistributeCmdData
		@param spacingValue - spacing value for between objects
		@param useValue - use the spacingValue or not
		@return bool16 
	 */
	virtual bool16 CanDistribute (DistributeType distributeHow, const PMReal& spacingValue, UseDistributeValue useValue) const = 0;

	/**	Returns kTrue if the key object can be called, kFalse otherwise.
	 */
	virtual bool16	CanSetKeyObject() const = 0;

	/**	Returns kTrue if the key object can be cleared, kFalse otherwise (i.e. it is not set)
	 */
	virtual bool16	CanCancelKeyObject() const = 0;

	/**	Returns kTrue if the key object can be cleared or set.
	 */
	virtual bool16	CanToggleKeyObject() const = 0;

	/**	Returns kTrue if the key object is selected.
	 */
	virtual bool16	IsKeyObjectSelected() const = 0;

// ----- Manipulators

	/**	Process commands to align the items in the selection with the specified type of alignment.
		@param alignHow - how to align the objects, see IAlignCmdData
		@return ErrorCode 
	 */
	virtual ErrorCode DoAlign (AlignType alignHow) = 0;

	/**	Process commands to distribute the items in the selection with the specified type of distribution.
		Depending on the value of useValue, optionally use the spacing value in distribution.
		@param distributeHow - how to distribute the objects, see IDistributeCmdData
		@param spacingValue - spacing value for between objects
		@param useValue - use the spacingValue or not
		@return ErrorCode 
	 */
	virtual ErrorCode DoDistribute (DistributeType distributeHow, const PMReal& spacingValue, UseDistributeValue useValue) = 0;

	/** Set the key object. If default value (kInvalidUIDRef) is used, one of the objects in the selection will be used,
		or a particular object may be chosen.
		@param item - the UIDRef of the item in the selection to use as the "key" object.
		@return ErrorCode
	 */
	virtual ErrorCode	DoSetKeyObject(const UIDRef& item = kInvalidUIDRef) = 0;
	
	/** Clear any key object that has been set.
		@return ErrorCode
	 */
	virtual ErrorCode	DoCancelKeyObject() = 0;

	/** If indicated object is key object, clear it, if not, set it.
		@param item - the UIDRef of the item in the selection to toggle as the "key" object.
		@return ErrorCode
	 */
	virtual ErrorCode	DoToggleKeyObject(const UIDRef& item) = 0;
};

#endif // __IAlignAndDistributeSuite__
