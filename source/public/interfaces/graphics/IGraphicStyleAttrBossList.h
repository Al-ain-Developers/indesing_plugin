//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicStyleAttrBossList.h $
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
//  
//  NOTE:
//  When a consumer of this interface changes an attribute owned by this 
//  boss list, it is responsible for calling AttributeChanged(). This is 
//  necessary so that this object can dirty itself when one of the attributes
//  it manages changes. (The attribute boss list is responsible for the 
//  persistence of its attributes.)
//  
//========================================================================================

#pragma once
	#ifndef _IGraphicStyle_AttributeBossList_
	#define _IGraphicStyle_AttributeBossList_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "IPMUnknown.h"
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATIONS
//___________________________________________________________________________________
/** This class manages a collection of graphic attribute objects. Graphic attribute
	objects are devrived from kGraphicsAttrBoss and must implement IGraphicAttributeInfo interface.
	Each attribute is assumed to have a unique attribute object classID. Attributes can be access
	either by the class ID or an index into the collection. All objects are ref-counted.
	
	@see GraphicStylesID.h for definitions of persistent data interface IID and
	basic graphic attribute classes.
	@see IGraphicAttributeInfo
*/

	class IGraphicStyleAttributeBossList : public IPMUnknown
		{
		//___________________________________________________________________________
		//	Data Types
		//___________________________________________________________________________
		public:
			/**	Used to indicate how attributes are duplicated.
			*/
			typedef enum _DuplicateKind
				{
				/**	attributes are duplicated by reference.
				*/
				kReferenceAttributes		= 0,
				
				/**	attributes are copied.
				*/
				kDuplicateAttributes		= 1
				}
				DuplicateKind;
		
		//___________________________________________________________________________
		//	Object Maintainance
		//___________________________________________________________________________
			/** Mark the persistent data dirty given the implementation ID.
				@param impleID this implementation ID.
				@param markDirty kTrue if to mark dirty. Ignored if implementation is not persistent.
			*/
			virtual void	 MarkPreDirty	(ImplementationID impleID = kInvalidImpl, bool16 markDirty = kTrue) = 0;
			
		//___________________________________________________________________________
		//	Attribute Utilities
		//___________________________________________________________________________
		public:
			/** Returns the specified attribute.
				@param attrClass the attribute class. This is a graphic attribute ClassID.
				@param interfaceID the specified IID. 
				Typically this is IID_IGRAPHICATTR_INFO or the persistent data interface IID
				of the attribute.
				@return Interface pointer (as IPMUnknown*) to the specified IID of the requested attribute or nil.
				This can be cast to the type of requested IID.
			*/
			virtual IPMUnknown*		QueryAttribute				(ClassID attrClass, const PMIID& interfaceID) const = 0;

			/** Returns the nth attribute.
				@param whichAttribute the nth attribute index starting from 0.
				@param interfaceID the specified IID.
				Typically this is IID_IGRAPHICATTR_INFO or the persistent data interface IID
				of the attribute.
				@return Interface pointer (as IPMUnknown*) to the specified IID of the requested attribute or nil.
				This can be cast to the type of requested IID.
			*/
			virtual IPMUnknown*		QueryAttributeN				(uint32 whichAttribute, const PMIID& interfaceID) const = 0;

			/** Create a copy of the specified attribute.
				@param attrClass the attribute class. This is a graphic attribute ClassID.
				@param interfaceID the specified IID.
				Typically this is IID_IGRAPHICATTR_INFO or the persistent data interface IID
				of the attribute.
				@return Interface pointer (as IPMUnknown*) to the specified IID of the attribute copy or nil.
				This can be cast to the type of requested IID.
			*/
			virtual IPMUnknown*		CreateAttributeCopy			(ClassID attrClass, const PMIID& interfaceID) const = 0;

			/** Create a copy of the nth attribute.
				@param whichAttribute the nth attribute index starting from 0.
				@param interfaceID the specified IID.
				Typically this is IID_IGRAPHICATTR_INFO or the persistent data interface IID
				of the attribute.
				@return Interface pointer (as IPMUnknown*) to the specified IID of the attribute copy or nil.
				This an be cast to the type of requested IID.
			*/
			virtual IPMUnknown*		CreateAttributeNCopy		(uint32 whichAttribute, const PMIID& interfaceID) const = 0;

			/** Returns the number of attributes in the list.
				@return the number of attributes in the list.
			*/
			virtual uint32			GetAttributeCount			(void) const = 0;

			/** Duplicate the attributes and returns the duplicate in iAttrListCopy.
				The attributes are either copied or referenced in the new list depending on whichDupKind.
				@param iAttrListCopy the list of attribute copies.
				@param whichDupKind indicate how the attributes should be duplicated.
			*/
			virtual ErrorCode		DuplicateAttributes			(IGraphicStyleAttributeBossList* iAttrListCopy, DuplicateKind whichDupKind) const = 0;

			/** Add the specified attribute to the list. Nothing is added if the same attribute 
				already exist in the list.
				@param iAttrbute the graphic attribute to add.
				IPMUnknown* is typically IGraphicAttributeInfo* or the persistent data interface
				of the attribute.
				@return kSuccess if successfull otherwise returns an error code.
			*/
			virtual ErrorCode		AddAttribute				(IPMUnknown* iAttrbute) = 0;

			/** Copy the content of the specified graphic attribute to the same attribute in list.
				Returns an error if the attribute does not exist in the list.
				@param iAttrbute the graphic attribute to copy.
				IPMUnknown* is typically IGraphicAttributeInfo* or the persistent data interface
				of the attribute.
				@return kSuccess if successfull otherwise returns an error code.
			*/
			virtual ErrorCode		CopyIntoAttribute			(IPMUnknown* iAttrbute) = 0;

			/** This is to indicate that an attribute owned by this attribute boss 
				list has changed. Returns an error code if attribute does not exist.
				@param attrClass the attribute class. This is a graphic attribute ClassID.
				@return kSuccess if successfull otherwise returns an error code.
			*/
			virtual ErrorCode		AttributeChanged			(ClassID attrClass) = 0;

			/** Remove the specified graphic attribute from the list.
				Returns an error if the attribute does not exist in the list.
				@param iAttrbute the graphic attribute to remove.
				IPMUnknown* is typically IGraphicAttributeInfo* or the persistent data interface
				of the attribute.
				@return kSuccess if successfull otherwise returns an error code.
			*/
			virtual ErrorCode		RemoveAttribute				(IPMUnknown* iAttrbute) = 0;

			/** Remove the attribute specified by attribute class from the list.
				Returns an error if the attribute does not exist in the list.
				@param attrClass the attribute class. This is a graphic attribute ClassID.
				@return kSuccess if successfull otherwise returns an error code.
			*/
			virtual ErrorCode		RemoveAttribute				(ClassID attrClass) = 0;

			/** Remove every attribut from the list.
			*/
			virtual void			RemoveEveryAttribute		(void) = 0;

			/** Compare iAttribute2 with the attribute of the same class in the list.
				@param pAttrIsEquivalent is set to kTrue if two attributes are equivalent.
				@param pAttrInList is set to kTrue if same attribute exists in the list.
			*/
			virtual void 			CompareAttribute			(IPMUnknown* iAttrbute2, bool16* pAttrIsEquivalent, bool16* pAttrInList = nil) const = 0;

			/** Return kTrue if specified attribute class exists in the list.
				@param attrClass the attribute class. This is a graphic attribute ClassID.
				@return kTrue if attribute class exists otherwise returns kFalse.
			*/
			virtual bool16			AttributeExists				(ClassID attrClass) const = 0;

			/** For internal use only.
			*/
			virtual void			BeginUpdate					(void) = 0;
			virtual void			EndUpdate					(void) = 0;
		};

#endif // _IGraphicStyle_AttributeBossList_
