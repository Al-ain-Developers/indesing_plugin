//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjStylesAttrCategoriesList.h $
//  
//  Owner: Danielle Darling
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
//  Adobe Patent or Adobe Patent Pending Invention Included Within this File
//  
//========================================================================================

#ifndef _IOBJSTYLESATTRCATEGORIESLIST_
#define _IOBJSTYLESATTRCATEGORIESLIST_

// ----- Interface files -----

#include "IPMUnknown.h"

// ----- ID files -----

#include "GenericID.h"

//
// Adobe patent application tracking #B098, 
// entitled Design a flexible and extensible way to implement object style, 
// inventors: Danielle Darling, Yeming Liu 
//

/** An interface to get object style's name and based on information.
*/
class IObjStylesAttrCategoriesList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IOBJSTYLESATTRCATEGORIESLIST };

		/**	Get the list of applying categories.
			@return K2Vector<CategoryID> the list of attribute categories that we apply to object.
		*/
		virtual const 	K2Vector<ClassID>& GetApplyCategories() const = 0;

		/**	Set the apply categories.
			@param category the list of attribute categories that we apply to object.
		*/
		virtual void 	SetApplyCategories(const K2Vector<ClassID>& category) = 0;

		/**	Adds a category to the list
			@param classID the category to add
		*/
		virtual void 	AddCategory(ClassID classID) = 0;

		/**	Removes a category to the list
			@param classID the category to add
		*/
		virtual void 	RemoveCategory(ClassID classID) = 0;
		
		/**	returns true if the category is in the list
			@param classID the category to check
		*/
		virtual bool16 	SupportsCategory(ClassID classID) const = 0;

		/**	Clears the list
		*/
		virtual void 	Clear() = 0;
};

#endif // _IOBJSTYLESATTRCATEGORIESLIST_
