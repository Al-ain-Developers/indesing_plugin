//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDynamicTargetsFacade.h $
//  
//  Owner: SusanCL
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
#include "DynamicDocumentsID.h"

#include "ISpreadDynamicContentMgr.h"

#include "WideString.h"
#include "Utils.h"

class IMotionPresetMgr;
class IMotionPresetData;
class ISubject;

namespace Facade
{

class IDynamicTargetsFacade : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDYNAMICTARGETSFACADE };
		
		/**	Get the page item UIDRef for the specified target.
			Target could be an action UIDRef or a page item UIDRef.
			@param targetRef is the target to get.
			@return page item UIDRef for the target.
		*/
		virtual UIDRef GetTargetPageItemRef (const UIDRef& targetRef) const = 0;

		/**	Get name for the specified target.
			@param targetRef is the target to get.
			@return name for the target.
		*/
		virtual PMString GetTargetName (const UIDRef& targetRef) const = 0;

		/**	Return true if target is part of a MSO object.
			@param targetRef is the target to get.
			@param msoRef is the mso ref that this target belongs to.
			@return true if target is part of a MSO object.
		*/
		virtual bool IsTargetInMSO (const UIDRef& targetRef, UIDRef& msoRef) const = 0;

		/** Returns a list of targets for the given owner.
			@param ownerRef is the owner ref
			@param filterType is target type interested
			@param targetList is the list of applicable targets for this owner.
			@param includeMasterPage is true if including master page targets.
			@return true is successful.
		*/
		virtual bool GetTargetList (const UIDRef& ownerRef, const ISpreadDynamicContentMgr::DynamicContentType& filterType, std::vector<UID>& targetList, bool includeMasterPage = false) const = 0;

};

};	// namespace