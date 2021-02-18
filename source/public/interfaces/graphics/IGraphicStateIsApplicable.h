//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStateIsApplicable.h $
//  
//  Owner: Michael Martz
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
//  Note:			This interface is intended to be used on page items so that the page
//  item (or its type) can determine which attribute types can be applied to
//  it. For example, an image page item can only have a fill color and 
//  overprint fill attribute.
//  
//========================================================================================

#pragma once
	#ifndef _IGraphicStateIsApplicable_
	#define _IGraphicStateIsApplicable_
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________

/**	A graphic attribute interface on the page item to indicate which attributes are
	applicable and which are not.
*/
class IGraphicStateIsApplicable : public IPMUnknown
	{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IGRAPHICSTYLE_IS_APPLICABLE };

	//____________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________
	public:
		//................................................................................
		//	Prevent an internal attribute/rendering type from being applied to the page item
		//................................................................................

		/**	Prevent the specified attribute class ID from being applied to the page item.
			@param attrClassID speciifes the attribute class ID.
		*/
	  	virtual void		PreventAttributeApplication			(const ClassID& attrClassID) = 0;
		/**	Prevent the specified rendering object class ID from being applied to the page item's
			fill rendering attribute.
			@param newClassID speciifes the rendering object class ID.
		*/
	  	virtual void		PreventFillRenderingApplication		(const ClassID& newClassID) = 0;
		/**	Prevent the specified rendering object class ID from being applied to the page item's
			stroke rendering attribute.
			@param newClassID speciifes the rendering object class ID.
		*/
	  	virtual void		PreventStrokeRenderingApplication	(const ClassID& newClassID) = 0;

		//................................................................................
		//	Allow an internal attribute/rendering type to be applied to the page item.
		//	Returns whether or not the attribute/rendering type class was removed from 
		//	the list.
		//................................................................................

		/**	Allow the specified attribute class type to be applied to the page item.
			@param attrClassID speciifes the attribute class ID.
			@return true if attribute class was removed from the list of excluded attribute list.
		*/
		virtual bool16		AllowAttributeApplication			(const ClassID& attrClassID) = 0;
		/**	Allow the specified rendering class type to be applied to the page item's
			fill rendering attribute.
			@param newClassID speciifes the rendering object class ID.
			@return true if rendering class was removed from the list of excluded fill list.
		*/
		virtual bool16		AllowFillRenderingApplication		(const ClassID& newClassID) = 0;
		/**	Allow the specified rendering class type to be applied to the page item's
			stroke rendering attribute.
			@param newClassID speciifes the rendering object class ID.
			@return true if rendering class was removed from the list of excluded stroke list.
		*/
		virtual bool16		AllowStrokeRenderingApplication		(const ClassID& newClassID) = 0;

		/**	Clear all entries in the page item's excluded attribute list.
		*/
		virtual void		ClearAttributeList					(void) = 0;
		/**	Clear all entries in the page item's excluded rendering fill list.
		*/
		virtual void		ClearFillRenderingList				(void) = 0;
		/**	Clear all entries in the page item's excluded rendering stroke list.
		*/
		virtual void		ClearStrokeRenderingList			(void) = 0;

		//................................................................................
		//	Can the attribute/rendering type be applied to the page item?
		//................................................................................

		/**	Return whether or not the specified attribute class ID can be applied to the page item.
			@param attrClassID specifies the attribute class ID.
			@return true if specified attribute class can be applied.
		*/
		virtual bool16		IsAttributeApplicable				(const ClassID& attrClassID) const = 0;
		/**	Return whether or not the specified rendering object class ID can be applied to the 
			page item's fill renderint attribute.
			@param classID specifies the rendering object class ID.
			@return true if specified rendering object class can be applied.
		*/
		virtual bool16		IsFillRenderingTypeApplicable		(const ClassID& classID) const = 0;
		/**	Return whether or not the specified rendering object class ID can be applied to the 
			page item's stroke renderint attribute.
			@param classID specifies the rendering object class ID.
			@return true if specified rendering object class can be applied.
		*/
		virtual bool16		IsStrokeRenderingTypeApplicable		(const ClassID& classID) const = 0;
	
		//................................................................................
		//	How many attribute/rendering type are prevented on the page item?
		//................................................................................

		/**	Returns the number of attributes that are excluded.
		*/
		virtual uint32		AttributeClassCount					(void) const = 0;
		/**	Returns the number of rendering types that are excluded from the fill rendering attribute.
		*/
		virtual uint32		FillRenderingTypeClassCount			(void) const = 0;
		/**	Returns the number of rendering types that are excluded from the stroke rendering attribute.
		*/
		virtual uint32		StrokeRenderingTypeClassCount		(void) const = 0;

		//................................................................................
		//	Return the classID of the Nth item in the list.
		//................................................................................

		/**	Returns the nth excluded attribute class ID.
			@param index is the nth item in the excluded list.
			@return the nth attribute class ID.
		*/
		virtual ClassID		GetAttributeClassID					(uint32 index) const = 0;
		/**	Returns the nth excluded fill rendering object class ID.
			@param index is the nth item in the excluded list.
			@return the nth rendering object class ID.
		*/
		virtual ClassID		GetFillRenderingTypeClassID			(uint32 index) const = 0;
		/**	Returns the nth excluded stroke rendering object class ID.
			@param index is the nth item in the excluded list.
			@return the nth rendering object class ID.
		*/
		virtual ClassID		GetStrokeRenderingTypeClassID		(uint32 index) const = 0;
	};

#endif // _IGraphicStateIsApplicable_