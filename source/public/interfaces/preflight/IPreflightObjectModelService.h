//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightObjectModelService.h $
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
//  
//  This service provides the DOM and mapping to real (or derived) InDesign elements.
//  
//  TBD: Split this up into separate services for mapping vs hierarchy? Seems like
//  overkill since in most cases the two will be tightly bound
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"

#include "IPreflightObject.h"

class IDocument;
class IPreflightExpansionHelper;

/** This service provides the DOM and mapping to real InDesign elements and/or derived data
	from those elements (eg artwork). You'd normally implement one of these services only
	if you want to expand the preflight object model from what is supported natively. Having
	said that, this is still somewhat common because you may want to inspect and/or 
	invalidate objects in the model in a way that isn't useful for a rule you want to
	implement.

	In order to extend the model you need to:
	- Indicate which object classes your service supports (GetMappedClasses) 
	- Indicate which objects your object is related to in the hierarchy (GetHierarchyClasses et al)
		(the preflight hierarchy, which may or may not match the natural document hierarchy)
	- Expand (ie create child nodes for) your object classes when handed a parent you say
		your nodes are children of.

	The preflight object model as a whole (ie IPreflightObjectModel) takes care of pulling
	together the composite response of all service providers and builds master trees of all
	of the relationships. All of the native objects are implemented using this same public
	interface.

	@see IPreflightObjectModel
*/
class IPreflightObjectModelService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTOBJECTMODELSERVICE };

public:
	//-----------------------
	// MAPPING

	/** Return a vector of object classes this service provides mapping for. By 'mapping' we mean
		it answers the QueryObject, GetClassScriptingString, and GetObjectDescription methods.

		@return A vector of object classes. Can be empty if this service only provides hierarchy.
	*/
	virtual PreflightObjectClassIDVector GetMappedClasses() const = 0;

	/** Indicates whether the given object may still be valid. This is primarily used by debug code
		to verify that the database is still in good shape. A return value of true is not 
		necessarily a true positive; it simply means there's no particular reason to believe it's 
		bad.

		@note The database associated with objID must be in memory when this is called. The 
			PreflightObjectModel ensures this.
		@param The object ID to validate.
		@return kTrue if the object seems to be valid; kFalse if it's known to be bad (ie out of date, invalid)
	*/
	virtual bool IsValidObject(const PreflightObjectID& objID) const = 0;

	/** Map an object ID into a 'live' object that can be inspected.
		@note The database associated with objID must be in memory when this is called. The 
			PreflightObjectModel ensures this.
		@param The object ID to map.
		@return A refcounted interface. Note that this does not have to be a 'true' boss based
			interface, although it must inherit from IPreflightObject, which inherits from
			IPMUnknown.
	*/
	virtual IPreflightObject* QueryObject(const PreflightObjectID& objID) const = 0;

	/**	Get the scripting-domain string used to identify the class. At the C++ level 
		everything is ClassID based for efficiency but at scripting level it's not feasible
		to maintain a giant enum.

		@param classID IN The class you're interested in.
		@return The scripting string for the class. For example, kPreflightOM_PageItem maps
			to the scripting string "OTPageItem." The string is arbitrary but must be unique
			and of course must be a consistent mapping.
	*/
	virtual WideString GetClassScriptingString(PreflightObjectClassID classID) const = 0;

	//-----------------------
	// HIERARCHY

	/** Return the classes for which this service provides hierarchy. By 'provides hierarchy' we
		mean that it implements the GetChildClasses and GetParentClasses methods. Note that more than one
		service can provide hierarchy for the same class.

		@return A vector of object classes.
	*/
	virtual PreflightObjectClassIDVector GetHierarchyClasses() const = 0;

	/** Given a class you say you provide hierarchy information for, indicate what classes are
		its children. Since multiple services may provide hierarchy for the same class,
		this isn't an exhaustive list; it's only the list you intend to expand. 
		
		Also, you only need to declare one side of the parent-child relationship. Eg if 'B' is a 
		child of 'A' then A can declare B a child, or B can declare A a parent; but either one 
		is sufficient. No harm is done by declaring them both.

		@note You should only list children that are one generation deep from the class; we want
			children and not all descendents (the object model compiles that list automatically).

		@param parentClass IN The class ID of interest.
		@return The vector of child class IDs.
	*/
	virtual PreflightObjectClassIDVector GetChildClasses(PreflightObjectClassID parentClass) const = 0;
	
	/** Given a class you say you provide hierarchy information for, indicate what classes are
		its parents. Since multiple services may provide hierarchy for the same class,
		this isn't an exhaustive list; it's only the list you intend to expand.

		Also, you only need to declare one side of the parent-child relationship. Eg if 'B' is a 
		child of 'A' then A can declare B a child, or B can declare A a parent; but either one 
		is sufficient. No harm is done by declaring them both.

		@note You should only list parents that are one generation deep from the class; we want
			parents and not all ancestors (the object model compiles that list automatically).

		@param parentClass IN The class ID of interest.
		@return The vector of child class IDs.
	*/
	virtual PreflightObjectClassIDVector GetParentClasses(PreflightObjectClassID childClass) const = 0;
	
	//-----------------------
	// EXPANSION

	/** Return the classes for which this service provides expansion services. By 'provides expansion
		services' we mean that it implements the GetExpandsIntoClasses and Expand methods. Note that 
		more than one service can provide expansion services for the same class.

		@return A vector of object classes this service provides expansion services for.
	*/
	virtual PreflightObjectClassIDVector GetExpansionClasses() const = 0;

	/** Given a class you say you provide hierarchy information for, indicate what classes can be
		discovered by calling Expand() on an object of the specified class. In simple cases this
		is no different than GetChildClasses().

		@note You should only list children that are one generation deep from the parent, we want
			children and not all descendents.

		@param parentClass IN The class ID of interest.
		@return The vector of child class IDs.
	*/
	virtual PreflightObjectClassIDVector GetExpandsIntoClasses(PreflightObjectClassID parentClass) const = 0;
	
	/** Given an object whose class you say you provide hierarchy information for, return the
		actual children of that object.

		@see PreflightExpansionHelper
		@note Via the expansion helper you can expand in multiple places in the tree; you don't
			have to expand only the children. This is for the convenience of services which can
			expand an entire subtree at once.
		@param helper IN A helper object which provides interfaces for expansion
	*/
	virtual void Expand(IPreflightExpansionHelper& helper) const = 0;

	//-----------------------
	// NOTIFICATION (to update caches etc)

	/** Called when a document is closed. Many services will maintain separate data for the objects
		they track, and rather than those services all observe the document list, we'll do it for them.

		@param iDoc IN The document that is about to close.
	*/
	virtual void OnCloseDocument(IDocument* iDoc) = 0;
	
	/** Called when an object is about to be invalidated. Note that this isn't a comprehensive notification;
		it doesn't tell you about every single invalidation, only when an object is being invalidated via
		a process that's tracking the object. The children are usually deleted, but you don't get notification
		for those.

		@param iDoc IN The document that is about to close.
	*/
	virtual void OnInvalidateObject(const PreflightObjectID& objID) = 0;

	//-----------------------
	// UTILITY

	/** Provide a description of the object.

		@param objID IN The object to provide a description for.
		@return A description string.
	*/
	virtual PMString GetObjectDescription(const PreflightObjectID& objID) const = 0;
	
	/** Provide a sorting string for the object. This should be a string that can be used to determine
		the order of results so they're consistently presented in the UI and reports.

		@param objID IN The object to provide a sort-string for.
		@return A sorting string.
	*/
	virtual PMString GetObjectSortValue(const PreflightObjectID& objID) const = 0;

	/** Return whether the object can be selected.

		@param objID IN The object to provide a description for.
		@return True if the object can be selected; false otherwise.
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

	/** Given a subpart ID, obtain a UI-friendly name for the subpart.
		@param subpartID IN The ID of the subpart.
		@return A (typically untranslated but not always) string, or empty if this service 
			doesn't map that subpart.
	*/
	virtual PMString GetSubpartName(ClassID subpartID) const = 0;
};

