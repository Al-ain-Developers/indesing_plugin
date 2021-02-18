//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttrIndeterminateData.h $
//  
//  Owner: Michael_Martz
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
	#ifndef _IGraphicAttribute_IndeterminateData_
	#define _IGraphicAttribute_IndeterminateData_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "IPMUnknown.h"
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________

	/**	A graphic attribute data interface for keep track of attribute indeterminate values.
	*/
	class IGraphicAttrIndeterminateData : public IPMUnknown
		{
		//___________________________________________________________________________
		//	Accessor memeber functions
		//___________________________________________________________________________
		public:

			/**	Return whether of not the attribute is indeterminate.
				@return true if attribute is indeterminate.
			*/
			virtual bool16		IsIndeterminate				(void) = 0;
			/**	Set whether of not the attribute is indeterminate.
				@param isInderminate is true if attribute is indeterminate.
			*/
			virtual void		SetIndeterminate			(bool16 isInderminate) = 0;
			
			/**	Returns the attribute's indeterminate count.
			*/
			virtual int32		GetIndeterminateCount		(void) = 0;

			/**	Set the attribute's indeterminate count.
				@param inderminateCount specifies the indeterminate count. 
			*/
			virtual void		SetIndeterminateCount		(int32 inderminateCount) = 0;
			
			/**	Increment the attribute's indeterminate count by one.
				@return the resulting indeterminate count.
			*/
			virtual int32		IncrementAttributeCount		(void) = 0;
			/**	Decrement the attribute's indeterminate count by one.
				@return the resulting indeterminate count.
			*/
			virtual int32		DecrementAttributeCount		(void) = 0;
		};
		
#endif // _IGraphicAttribute_IndeterminateData_
