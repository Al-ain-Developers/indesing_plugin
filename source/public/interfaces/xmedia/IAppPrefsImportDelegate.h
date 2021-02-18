//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IAppPrefsImportDelegate.h $
//  
//  Owner: Matt Joss
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
#ifndef __IAppPrefsImportDelegate__
#define __IAppPrefsImportDelegate__

#include "SnippetID.h"
#include "ISnippetExport.h"
#include "IDOMElement.h"

/** This is an interface for customizing the Import of Application Preferences
	The methods in this interfaces are callbacks from the import process that allows
	the client to have a say in the import
*/
class IAppPrefsImportDelegate : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPPREFSIMPORTDELEGATE };

	/** 
		This method is called for each root object(direct child of application) read in during the import process
		to gove the delegate a chance to decide if the match found should be used or if a new element should be created.
		Returning kTrue does not always work, some objects, like regular preferences, cannot be created
		@param defaultBehavior to get default behavior, return this value
		@param importAction the current preference for reusing the existing element or replacing the element
		@param parent the IDOMElement* of the parent element of the matching element
		@param childToUse the IDOMElement* of the matching item
		@param elementName the XML element name of the element that represents the object
		@param attributes the XML attributes associated with elementName
		
		@return kTrue to create a new object instead of using the match, kFalse to use the matching object that was passed in
	*/
	virtual bool16 			ShouldCreateNewElement(bool16 defaultBehavior, IAppPrefsImportOptions::ListImportMatchAction importAction, IDOMElement *parent, IDOMElement *childToUse, const WideString &elementName, const IDOMElement::AttributeList &attributes) = 0;
	

	/** What should be done with the specified attributes */
	typedef enum { 
	/** apply the original attributes to the element */
	kApplyAttributes, 
	/** will cause the element to remain unchanged */
	kDontApplyAttributes, 
	/** apply the attributes returned in the newAttributes parameter */
	kApplyNewAttributes } AttributeAction;
	
	/** 
		When an object is imported, the attributes on the imported XML element are used to set the properties of the item
		This callback allows the delegate to change the XML attributes before they are applied to the newly created object or
		to the matching object.
		Changing the attribute list should be done very carefully as it can easily lead to problematic scenarios.  
		@param elementFragment the IDOMElement* of the item to which the attributes will be applied
		@param defaultAttributeAction this is the default behavior.  If you want default behavior, return this parameter
		@param attributes these are the attributes that were imported from the XML
		@param newAttributes this is a list of new attributes, if AttributeAction returned is kApplyNewAttributes, the attributes in this list will
		be applied instead of the original attributes
		
		@return kApplyAttributes will apply the original attributes to the element. kDontApplyAttributes will cause the element to remain unchanged, no attributes will be applied.
		kApplyNewAttributes will apply the attributes returned in the newAttributes parameter.
		return defaultAttributeAction to get default behavior
	*/
	virtual AttributeAction	ModifyAttributes(IDOMElement* elementFragment, AttributeAction defaultAttributeAction, const IDOMElement::AttributeList& attributes, IDOMElement::AttributeList& newAttributes);

	/** 
		When looking for existing items that match the item imported, we use specific properties to handle the match.  For most
		list items, the property used to "match" items is the name property.  This callback will be called when looking for a
		match of an incoming element.  The most common usage of this callback is to return 'p_Name' when a 3rd party list
		item is the elementScriptID.  If you add a list element, it won't automatically use the name as a way to match items, you 
		must use this callback to specify the property element you'd like to use as the matching property.
		@param elementScriptID the ScriptID of the element we are looking to match
		@return return the ScriptID of the property you'd like used as the matching property.  'p_Name' is the most common.  return kInvalidScriptID to get default behavior
	*/
	virtual ScriptID		CompareElementsUsingProperty( ScriptID elementScriptID );

	/** 
		When we've imported all the objects, we go thru the list of all children of the application object and call this callback to determine if the item
		should be deleted.  The default behavior is passed in defaultShouldDeleteValue and you can return that to get default behavior.  This will use the 
		DOM delete which may not work for all element types, so another use is to check defaultShouldDeleteValue and delete an element yourself, then return kFalse.
		Also, note that not all element types can be deleted, so returning kTrue for some element types may cause errors.
		@param domElement the element in question.  Should this element be deleted or not?
		@param defaultShouldDeleteValue default behavior.  This is what would normally happen if there was no delegate
		@return return kTrue to have the element deleted via the import process, kFalse to tell the import process not to delete.  To get default behavior, return defaultShouldDeleteValue
	*/
	virtual bool16			ShouldDeleteElement(IDOMElement* domElement, bool16 defaultShouldDeleteValue ) const = 0;

};

#endif //__IAppPrefsImportDelegate__
