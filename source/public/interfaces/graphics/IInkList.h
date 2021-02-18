//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInkList.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IInkList__
#define __IInkList__

#include "IPMUnknown.h"
#include "ColorSystemID.h"
#include "PMString.h"
#include "UIDList.h"

class IPMInkBossData;

/**	An interface for managing InDesign ink list. InDesign inks are kPMInkDataBoss objects with reqruied
	IPMInkBossData interface. Ink list consists of at least 4 process inks and
	zero of more spot inks. Inks are ref-counted.
	@see ColorSystemID.h
*/
class IInkList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINKLIST };
		
		/**	Bootstrap the ink list. This initializes the ink list with the four process inks:
			Cyan, Magenta, Yellow, and Black.
		*/
		virtual void Init() const = 0;

		/**	Find the ink with the specified IPMInkBossData.
			@param InkData the ink data to find.
			@return ink UIDRef for the ink data. If not found, returns UIDRef::gNull.
			@see IPMInkBossData
		*/
		virtual UIDRef FindInk( IPMInkBossData* inkBossData ) const = 0;
		
		/**	Find the ink with the specified inkName in the ink list.
			@param inkname the ink name to find.
			@return ink UIDRef for the ink name. If not found, returns UIDRef::gNull.
		*/
		virtual UIDRef FindInk(const PMString& inkname) const = 0;
		
		/**	Find the ink location index in the list with the specified ink UID.
			@param inkUID the ink UID to find.
			@return the index in the list starting with index 0. If no such UID is found, returns -1.
		*/
		virtual int32 FindInk(const UID& inkUID) const = 0;
		
		/**	Returns the number of inks in the list.
			@return the number of inks in the list.
		*/
		virtual int32 GetNumInks() const = 0;

		
		/**	Returns the nth ink in the list.
			@param index the nth ink starting from 0.
			@return the nth ink in the list. If index is not in the range, returns -1.
		*/
		virtual UIDRef GetNthInk(int32 index) const = 0;

		
		/**	Add the specified inkUID in the list. If the specified ink already exists, the
			ink's ref-count is incremented. 
			@param inkUID the ink to add.
		*/
		virtual void AddInk(const UID& inkUID) = 0;
		
		/**	Remove the specified inkUID in the list. If the specified ink exists, the
			ink's ref-count is decremented first. When the ref-count is 0, the ink is removed from the list.
			If ink deos not exist, it does nothing. 
			@param inkUID the ink to remove.
		*/
		virtual void RemoveInk(const UID& inkUID) = 0;
		
		/**	Defines which inks are included and how inks are ordered in the list. They are
			flag bits used in GetPlatOrderInkList.
			@see GetPlatOrderInkList
		*/
		/**	Specifies non-printing inks should be excluded from the list.
		*/
		enum { kExcludeNonPrintingInks 		= (1L<<0) };
		/**	Specifies all process inks and all converted to process inks should be excluded from the list.
		*/
		enum { kExcludeProcessInks 			= (1L<<1) }; // Note: Filters out AsProcess inks too.
		/**	Specifies all aliased inks should be excluded from the list.
		*/
		enum { kExcludeAliasedInks 			= (1L<<2) };
		/**	Specifies all converted to process inks (but not normal process inks) should be excluded from the list.
		*/
		enum { kExcludeAsProcessInks 		= (1L<<3) }; // Note: Does not filter out CMYK primaries.
		
		/**	Returns a UIDList that has been pre-sorted in plate order.
			@param flags defines how inks should be included in this list.
			@return the ink UIDList containing the requested inks in the specified order.
		*/
		virtual UIDList GetPlateOrderInkList(int32 flags) const = 0;
				
	enum {kNotFound = -1};
};

#endif
