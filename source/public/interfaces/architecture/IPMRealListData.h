//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPMRealListData.h $
//  
//  Owner: Abhay Sibal
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
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#pragma once
	#ifndef _IPMRealListData_h_
	#define _IPMRealListData_h_
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "CommandID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________
/** Data interface to store a list of PMReal values.
	@ingroup arch_coredata 
*/
class IPMRealListData : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:

		enum { kDefaultIID = IID_IPMREALLISTDATA };

		/**	Specifies where the new data should be inserted.
		*/
        enum _Placement
				{
				kBeginning				= 0,	/**	Insert at the beginning. */
				kEnd					= -2,	/**	Insert at the end. */
				};

	//____________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________
	public:
		/**	Add the new PMReal the specified position.
			@param newPMReal is the new PMReal to add.
			@param at is the position to add. Either kBeginning or kEnd or a valid location in the list. If an invalid index is provided, the value will be appended at the end of the list.
		*/
	  	virtual void		AddRealNumber		(const PMReal& newPMReal, int32 at = kEnd) = 0;
		/**	Remove the new PMReal at specified position.
			@param index specifies the position to remove. A valid index must be provided, else this will be a no-op.
		*/
		virtual void		RemoveRealNumber	(int32 index) = 0;
		/**	Clear the list.
		*/
		virtual void		Clear			(void) = 0;
		/**	Return the PMReal the specified position. A valid index must be provided, else this will return 0.0.
			@param index is the nth position.
			@return the nth PMReal.
		*/
		virtual PMReal		GetRealNumber		(int32 index) const = 0;
		/**	Set the PMReal for the specified position.
			@param index is the nth position. A valid index must be provided, else this will be a no-op.
			@param replacePMReal is the new PMReal.
		*/
		virtual void		SetRealNumber		(int32 index, const PMReal& replacePMReal) = 0;

		/**	Return the position for given PMReal .
			@param PMReal is PMReal.
			@return the position for the given PMReal or -1 if it is not found.
		*/
		virtual int32		GetIndex		(const PMReal& PMReal) const = 0;
		/**	@return the number of PMReal in the list.
		*/
		virtual int32		Length			(void) const = 0;
	};

#endif // _IPMRealListData_h_