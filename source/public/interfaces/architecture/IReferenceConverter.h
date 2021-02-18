//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IReferenceConverter.h $
//  
//  Owner: Robin Briggs
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
#ifndef __IReferenceConverter__
#define __IReferenceConverter__

#include "IPMUnknown.h"
#include "ShuksanID.h"

class IDataBase;
class ICommand;

/** This interface is used for controlling how UIDs are copied from one document or context
	into another. During a copy, when a UID is encountered, the copy code looks to see if
	the UID has already been copied within that context. If so, it uses the destination UID 
	that got generated when the object was copied earlier. Otherwise, it gets the class
	of the UID, and looks for a reference converter that can copy the object. If no reference
	converter is found, the object will not be copied, and the resulting containing object
	will have kInvalidUID.
	
	Reference converters are used for copying named colors and styles; rather than always
	generating a new color, the color reference converter looks first to see if it can find
	a color of the same name in the target document. If so, it uses that color, and otherwise
	it fires a create color command which creates the new color and adds it to the swatch
	list. This is just one example; there are lots of cases where it is useful for an object
	to be able to define how it is copied.
	
	Reference converters are services (kReferenceConverterService) and IReferenceConverter 
	is the interface used for them. 
	
	@see IXReferenceUID
*/
class IReferenceConverter : public IPMUnknown	{
	public:
		enum { kDefaultIID = IID_IREFERENCECONVERTER };

		/** Return kTrue if the converter is capable of converting objects
			of the class clsID.
			@param clsID the class of the object being copied
			@return kTrue if this reference converters handles the object type
		*/
		virtual bool16 CanConvert(ClassID clsID) = 0;
			
		/** Convert the UID from a reference to a uid in the source database,
			to a reference to a UID in the target database. This may cause changes
			to the target database.
			@param sourceDB the database we're copying from
			@param convertThis the object we're copying
			@param targetDB the database we're copying to
			@param pmobject a helper object (whatever pmobject was passed into 
			ScrapUtils::CopyObjects or whatever other calling code set up the stream)
			@return the UID of the matching object in the target database
		*/
		virtual UID ConvertReference(IDataBase *sourceDB, UID convertThis, IDataBase *targetDB, IPMUnknown* pmobject) = 0;

		/** Return kTrue if the converter should be called to convert every time.
			The default return value should be kFalse to allow K2 recognize that
			an item has already been converted and that when it encounters other references
			to the same item, it can simply use the result of the previous conversion.
		*/
		virtual bool16 ConvertAlways() const = 0;

		/** Like ConvertReference() it converts the UID from sourceDB to targetDB but
			it doesn't create a new UID in the targetDB if it couldn't convert it.
			Instead it returns kInvalidUID. This method is used i.e. by Find/Change of
			UID based text attributes (language, font, color).
		*/
		virtual UID GetReference(IDataBase *sourceDB, UID convertThis, IDataBase *targetDB ) const = 0;

		/** Returns kTrue if reference conversion is being done for the purpose of 
			mapping references (e.g. style mapping). The default return value for
			most reference converter should be kFalse. Only converters which will 
			be doing mapping of reference for the passed "convertThis" UID, should 
			return kTrue
			@param sourceDB the database we're copying from
			@param convertThis the object whose reference we intend to convert
			@param targetDB the database we're copying to.
			@return kTrue if we are mapping the object from source to target DB.
		*/
		virtual bool16 IsMappingReference(IDataBase *sourceDB, UID convertThis, IDataBase *targetDB) const = 0;

		/** Map the UID from a reference to a uid in the source database,
			to a reference to a UID in the target database. This may cause changes
			to the target database.
			@param sourceDB the database we're copying from
			@param convertThis the object we're mapping
			@param targetDB the database we're copying to
			@param pmobject a helper object (whatever pmobject was passed into 
			ScrapUtils::CopyObjects or whatever other calling code set up the stream)
			@return the UID of the mapped object in the target database
		*/
		virtual UID MapReference(IDataBase *sourceDB, UID convertThis, IDataBase *targetDB, IPMUnknown* pmobject) = 0;

		/** Like MapReference() it maps the UID from sourceDB to targetDB but
			it doesn't create a new UID in the targetDB if it couldn't convert it.
			Instead it returns kInvalidUID. 
		*/
		virtual UID GetMappedReference(IDataBase *sourceDB, UID convertThis, IDataBase *targetDB ) = 0;
};


#endif // __IReferenceConverter__
