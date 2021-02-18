//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightObjectModel.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPreflightObject.h"

class IDocument;
class ISpread;
class IPage;
class IShape;
class IPreflightExpansionHelper;

/** The preflight object model interface is the application-wide access point for mapping objects
	in the preflight model. The preflight model follows the InDesign document model in many places
	but not all -- for example objects like marking operations don't exist in the InDesign model
	but rules can still check them and operate on them. The preflight object model is an attempt
	to abstract the differences via the interface mechanism.

	This interface is really the high-level access point to the model. The model is based on 
	services (see IPreflightObjectModelService) but normally you ask questions at this level,
	not an individual service level.

	A typical use of IPreflightObjectModel is to get an IPreflightObject from a PreflightObjectID,
	for example:

		InterfacePtr<IPreflightObjectModel> iModel(Utils<IPreflightUtils>()->QueryObjectModel());
		InterfacePtr<IPreflightObject> iObj(iModel->QueryObject(myObjID));

	Other uses are related to user interaction. For example, GetObjectDescription(), 
	CanBeSelected(), SelectObject(), GetPage(), and so on, are all useful for presenting
	results or other info to the user.
*/
class IPreflightObjectModel : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTOBJECTMODEL };

public:
	/** Called by the preflight manager; you shouldn't call this.
	*/
	virtual void Startup() = 0;

	/** Called by the preflight manager; you shouldn't call this.
	*/
	virtual void Shutdown() = 0;

	/** Called by the preflight manager; you shouldn't call this.
	*/
	virtual void OnCloseDocument(IDocument* iDoc) = 0;

	/** Notification that the given object is being invalidated. Note that this is not a comprehensive 
		indicator that a given object is no longer valid; it's only called to let services know that an
		invalidation took place, in case they want to monitor patterns.

		@param The object ID being invalidated.
	*/
	virtual void OnInvalidateObject(const PreflightObjectID& objID) const = 0;

	/** Indicates whether the given object may still be valid. This is primarily used by debug code
		to verify that the database is still in good shape. A return value of true is not 
		necessarily a true positive; it simply means there's no particular reason to believe it's 
		bad.

		@param The object ID to validate.
		@return kTrue if the object seems to be valid; kFalse if it's known to be bad (ie out of date, invalid)
	*/
	virtual bool IsValidObject(const PreflightObjectID& objID) const = 0;

	/** Given a preflight object (simple reference), obtain a pointer to an interface you
		can get concrete implementations from via QueryInterface, or pass on to functions
		that need it. Note that the returned interface is very short lived; any invalidation
		of the document can cause it to be out of date. DO NOT store this interface away as
		a member variable unless it will exist only over an atomic operation that does not
		modify the document.

		@param objID IN The object you want to map to an interface.
		@return A refcounted preflight object interface.
	*/
	virtual IPreflightObject* QueryObject(const PreflightObjectID& objID) const = 0;

	/** Given an object class, get the string representing that class in the scripting world.
		Returns an empty string if the class does not exist in the object model lookup tables
		(ie no service offers mapping for it).

		@param classID IN The class you want to get the string for.
		@return A WideString that can be passed to scripts, or en empty string if there is no mapping.
	*/
	virtual WideString GetClassScriptingString(PreflightObjectClassID classID) const = 0;

	/** Given an object class encoded as a string from the scripting world, get the object class ID.
		Returns kInvalidClass if there is no mapping for that string.

		@param classID IN The class you want to get the string for.
		@return A PreflightObjectClassID that maps to the passed-in string, or kInvalidClass if there is no mapping for that string.
	*/
	virtual PreflightObjectClassID GetClassFromScriptingString(const WideString& scriptString) const = 0;

	/** Provides a description of the object. 

		@param objID IN The object you want a description of.
		@return A description string, often prelocalized because it's parameterized.
	*/
	virtual PMString GetObjectDescription(const PreflightObjectID& objID) const = 0;

	/** Provide a sorting string for the object. This should be a string that can be used to determine
		the order of results so they're consistently presented in the UI and reports.

		@param objID IN The object to provide a sort-string for.
		@return A sorting string.
	*/
	virtual PMString GetObjectSortValue(const PreflightObjectID& objID) const = 0;

	/** Asks whether a given object can be selected. 

		@param objID IN The object you're interested in.
		@return True if selectable; false otherwise.
	*/
	virtual bool CanBeSelected(const PreflightObjectID& objID) const = 0;
	
	/** Select the object.

		@param objID IN The object to provide a description for.
		@return True if the object was selected; false otherwise.
	*/
	virtual bool SelectObject(const PreflightObjectID& objID) const = 0;

	/** Get the page (or pages) on which the object appears.

		@param objID IN The object to provide a description for.
		@return A string describing the page number, or an empty string if there is no page 
			associated with the object (eg if the object is a document, or a swatch). Can
			also be a page range if the object spans more than one page (eg "2-3").
	*/
	virtual PMString GetPage(const PreflightObjectID& objID) const = 0;

		/** Given a subpart ID, obtain a UI-friendly name for the subpart. For example, the subpart name
		for kPreflightOSP_NativeFill is "fill".

		@param subpartID IN The ID of the subpart.
		@return A (typically untranslated but not always) string, or empty if no service understood the subpart.
	*/
	virtual PMString GetSubpartName(ClassID subpartID) const = 0;

	/** Returns a vector of all registered object class IDs.

		@return A vector of PreflightObjectClassIDs.
	*/
	virtual PreflightObjectClassIDVector GetAllKnownClasses() const = 0;

	/** Returns whether there is a parent child relationship between the specified classes.

		@param parentClass IN The class ID of the parent.
		@param parentClass IN The class ID of the child.
		@return True if a service has declared that the parent class has children of the child class.
		@note This is not checking ancestors/descendents; it's purely a single level parent-child.
	*/
	virtual bool ParentChildRelationshipExists(PreflightObjectClassID parentClass, PreflightObjectClassID childClass) const = 0;

	/** Given a given 'child' class, return all the classes that are hierarchy ancestors of that class.
		A hierarchy parent is a class that when expanded may produce the child. A hierarchy ancestor
		is a hierarchy parent recursively.

		Typically this is used to determine which classes to expand when building search trees. For example, if you want to 
		get to objects of class X, the only nodes you want to expand are those which are ancestors of X.

		@note The results are unioned with the incoming list, ie ancestorClasses is not cleared first.

		@param childClass IN The class you want to get ancestors for (not including the child).
		@param ancestorClasses OUT The vector of ancestors. The ancestors are unioned with the incoming list state.
	*/
	virtual void GetHierarchyAncestorsOfClass
		(
		 	PreflightObjectClassID childClass, 
		 	PreflightObjectClassIDVector& ancestorClasses
		 ) const = 0;
	
	/** Given a vector of child classes, produce a vector of hierarchy ancestor classes.
		Note: the results are added to, not cleared first.

		@param childClasses IN The classes you want to get ancestors for.
		@param ancestorClasses OUT The vector of ancestors. The ancestors are unioned with the incoming list state.
	*/
	virtual void GetHierarchyAncestorsOfClass
		(
		 	const PreflightObjectClassIDVector& childClasses, 
		 	PreflightObjectClassIDVector& ancestorClasses
		 ) const = 0;	
	
	/** Given a given 'child' class, return all the classes that are hierarchy ancestors of that class.
		An expansion parent is a class that when expanded may produce the child. An expansion ancestor
		is an expansion parent recursively.

		Typically this is used to determine which classes to expand when building search trees. For example, if you want to 
		get to objects of class X, the only nodes you want to expand are those which are ancestors of X.

		@note The results are unioned with the incoming list, ie ancestorClasses is not cleared first.

		@param childClass IN The class you want to get ancestors for (not including the child).
		@param ancestorClasses OUT The vector of ancestors. The ancestors are unioned with the incoming list state.
	*/
	virtual void GetExpansionAncestorsOfClass
		(
		 	PreflightObjectClassID childClass, 
		 	PreflightObjectClassIDVector& ancestorClasses
		 ) const = 0;
	
	/** Given a vector of child classes, produce a vector of expansion ancestor classes.
		Note: the results are added to, not cleared first.

		@param childClasses IN The classes you want to get ancestors for.
		@param ancestorClasses OUT The vector of ancestors. The ancestors are unioned with the incoming list state.
	*/
	virtual void GetExpansionAncestorsOfClass
		(
		 	const PreflightObjectClassIDVector& childClasses, 
		 	PreflightObjectClassIDVector& ancestorClasses
		 ) const = 0;	
	
	/** Given a parent object, expand the children. This delegates to the object model services.
	
		@note This is typically called only by the preflight engine, although in theory if you 
			want to write your own IPreflightExpansionHelper implementation you could call it..

		@param helper IN The utility interface that provides expansion services.
	*/

	virtual void Expand(IPreflightExpansionHelper& helper) const = 0;
};

