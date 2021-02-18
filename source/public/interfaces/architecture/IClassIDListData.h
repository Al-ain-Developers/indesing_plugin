//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IClassIDListData.h $
//  
//  Owner: Michel Hutinel
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
	#ifndef _IClassIDListData_h_
	#define _IClassIDListData_h_
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "CommandID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________
/** Data interface to store a list of ClassID values.
	@ingroup arch_coredata 
*/
class IClassIDListData : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:

		enum { kDefaultIID = IID_ICLASSIDLISTDATA };

		/**	Specifies how the new data should be inserted.
		*/
        enum _Placement
				{
				kBeginning				= 0,	/**	Insert at the beginning. */
				kEnd					= -2,	/**	Insert at the end. */
				kInvalidIndex			= -1	/**	Specifies an invalid index. */
				};

	//____________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________
	public:
		/**	Add the new class ID the specified position.
			@param newClassID is the new class ID to add.
			@param at is the position to add.
		*/
	  	virtual void		AddClassID		(const ClassID& newClassID, int32 at = kEnd) = 0;
		/**	Remove the new class ID at specified position.
			@param index specifies the position to remove.
		*/
		virtual void		RemoveClassID	(int32 index) = 0;
		/**	Clear the list.
		*/
		virtual void		Clear			(void) = 0;
		/**	Return the class ID the specified position.
			@param index is the nth position.
			@return the nth class ID.
		*/
		virtual ClassID		GetClassID		(int32 index) const = 0;
		/**	Set the class ID for the specified position.
			@param index is the nth position.
			@param replaceClassID is the new class ID.
		*/
		virtual void		SetClassID		(int32 index, const ClassID& replaceClassID) = 0;

		/**	Return the position for given class ID .
			@param classID is class ID.
			@return the position for the given class ID.
		*/
		virtual int32		GetIndex		(const ClassID& classID) const = 0;
		/**	@return the number of class ID in the list.
		*/
		virtual int32		Length			(void) const = 0;
	};

#endif // _IClassIDListData_h_