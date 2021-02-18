//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IChangePIIsApplicableCmdData.h $
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
	#ifndef _IChangePageItemIsApplicableCmdData_
	#define _IChangePageItemIsApplicableCmdData_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________

/**	A command data interface for changing the page item's attributes applicability.
*/
class IChangePIIsApplicableCmdData : public IPMUnknown
	{
	public:
		//................................................................................
		//	Accessors/Mutators for the allow attribute class ID.
		//		This list will enable the specified attributes on the page items in the
		//		command's list.
		//................................................................................

		/**	Add an attribute class to the allowed attribute list.
			@param allowedAttrClassID specifies the new attribute class ID to add.
		*/
		virtual void		AddAllowAttributeClassID			(const ClassID& allowedAttrClassID) = 0;
		/**	Returns the number of attributes in the allowed attribute list.
		*/
		virtual int32		GetAllowAttributeCount				(void) = 0;
		/**	Return the nth allowed attribute class ID in the list.
			@param index specifies the nth item in the allowed list.
			@return the nth attribute class ID.
		*/
		virtual ClassID		GetAllowAttributeClassID			(int32 index) = 0;

		//................................................................................
		//	Accessors/Mutators for the prevent attribute class ID.
		//		This list will disable the specified attributes on the page items in the
		//		command's list.
		//................................................................................

		/**	Add an attribute class ID to the page item's excluded attribute list.
			@param preventAttrClassID specifies the attribute class ID to exclude.
		*/
		virtual void		AddPreventAttributeClassID			(const ClassID& preventAttrClassID) = 0;
		/**	Returns the number of attributes in the excluded attribute list.
		*/
		virtual int32		GetPreventAttributeCount			(void) = 0;
		/**	Return the nth excluded attribute class ID in the list.
			@param index specifies the nth item in the excluded list.
			@return the nth attribute class ID.
		*/
		virtual ClassID		GetPreventAttributeClassID			(int32 index) = 0;

		//................................................................................
		//	Accessors/Mutators for the allow fill rendering type.
		//		This list will disable the specified rendering types on the page items in 
		//		the command's list.
		//................................................................................

		/**	Add an rendering object class ID to the page item's allowed fill rendering type list.
			@param renderClassID specifies the rendering class ID to allowed fill list.
		*/
		virtual void		AddAllowFillRenderingType			(const ClassID& renderClassID) = 0;
		/**	Returns the number of rendering types in the allowed fill list.
		*/
		virtual int32		GetAllowFillRenderingTypeCount		(void) = 0;
		/**	Return the nth allowed rendering class ID in the allowed fill list.
			@param index specifies the nth item in the allowed fill list.
			@return the nth rendering class ID.
		*/
		virtual ClassID		GetAllowFillRenderingType			(int32 index) = 0;

		//................................................................................
		//	Accessors/Mutators for the prevent fill rendering type.
		//		This list will disable the specified rendering types on the page items in 
		//		the command's list.
		//................................................................................

		/**	Add an rendering class ID to the page item's excluded fill rendering type list.
			@param preventRenderClassID specifies the rendering class ID to exclude.
		*/
		virtual void		AddPreventFillRenderingType			(const ClassID& preventRenderClassID) = 0;
		/**	Returns the number of rendering types in the excluded fill list.
		*/
		virtual int32		GetPreventFillRenderingTypeCount	(void) = 0;
		/**	Return the nth excluded rendering class ID in the excluded fill list.
			@param index specifies the nth item in the excluded fill list.
			@return the nth rendering class ID.
		*/
		virtual ClassID		GetPreventFillRenderingType			(int32 index) = 0;

		//................................................................................
		//	Accessors/Mutators for the allow stroke rendering type.
		//		This list will disable the specified rendering types on the page items in 
		//		the command's list.
		//................................................................................

		/**	Add an rendering object class ID to the page item's allowed stroke rendering type list.
			@param renderClassID specifies the rendering class ID to allowed stroke list.
		*/
		virtual void		AddAllowStrokeRenderingType			(const ClassID& renderClassID) = 0;
		/**	Returns the number of rendering types in the allowed stroke list.
		*/
		virtual int32		GetAllowStrokeRenderingTypeCount	(void) = 0;
		/**	Return the nth allowed rendering class ID in the stroke list.
			@param index specifies the nth item in the allowed stroke list.
			@return the nth rendering class ID.
		*/
		virtual ClassID		GetAllowStrokeRenderingType			(int32 index) = 0;

		//................................................................................
		//	Accessors/Mutators for the prevent stroke rendering type.
		//		This list will disable the specified rendering types on the page items in 
		//		the command's list.
		//................................................................................

		/**	Add an rendering class ID to the page item's excluded stroke rendering type list.
			@param preventRenderClassID specifies the rendering class ID to exclude.
		*/
		virtual void		AddPreventStrokeRenderingType		(const ClassID& preventRenderClassID) = 0;
		/**	Returns the number of rendering types excluded stroke list.
		*/
		virtual int32		GetPreventStrokeRenderingTypeCount	(void) = 0;
		/**	Return the nth excluded rendering class ID in the excluded stroke list.
			@param index specifies the nth item in the excluded stroke list.
			@return the nth rendering class ID.
		*/
		virtual ClassID		GetPreventStrokeRenderingType		(int32 index) = 0;
	};
		
#endif // _IChangePageItemIsApplicableCmdData_
