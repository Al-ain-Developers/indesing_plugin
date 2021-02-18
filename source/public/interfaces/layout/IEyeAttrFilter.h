//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IEyeAttrFilter.h $
//  
//  Owner: Dave Stephens
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
//  Class declaration for EyeAttrFilter, which is used as the parent class of
//  EyeCharAttrFilter and EyeParaAttrFilter.
//  
//========================================================================================

#pragma once
#ifndef __IEyeAttrFilter__
#define __IEyeAttrFilter__

#include "IClassIDListData.h"

//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________
#include "K2Vector.h"
typedef K2Vector<ClassID> ClassIDList;

/** This class is used as the interface for the various collections of attributes that the Eye Dropper
	cares about.  For the eye dropper, there are separate collections for character settings, paragraph
	settings, transparency settings, etc.  This interface works well for that purpose because most
	attributes are ClassID based.  For the purposes of the eye dropper, if an attribute is in the
	collection, then the attributes is 'enabled', otherwise it is 'disabled.'  This particular interface
	is a list collection.
*/
class IEyeAttrFilter : public IClassIDListData
{
	//____________________________________________________________________________________
	//	Member Functions
	//____________________________________________________________________________________
	public:
		/**
			Add the ClassID of an attribute to the collection.
			@param newClassID - IN: ClassID of an attribute.
			@param at - IN: zero based index of where in the list to add the new attribute.
		*/
	  	virtual void		AddClassID			(const ClassID& newClassID, int32 at = kEnd) = 0;

		/**
			Remove the ClassID stored at position 'index' from the collection.
			@param index - IN: zero based index of the element to remove.
		*/
		virtual void		RemoveClassID		(int32 index) = 0;

		/**
			Remove all elements from the collection.
		*/
		virtual void		Clear				(void) = 0;

		/**
			Copy all elements from 'copyFrom' to this and copy the 'GetApplyStyles' setting and
			'GetEnabled' setting.  Elements already in 'this' are preserved.
		*/
		virtual void		Copy				(const IEyeAttrFilter& copyFrom) = 0;
		/**
			Copy all elements from 'copyFrom' to this.  Elements already in 'this' are preserved.
		*/
		virtual void		AppendClassIDs		(const IEyeAttrFilter& copyFrom) = 0;

		/** Restore default attributes and SetEnabled(kTrue)
		*/
		virtual void		Initialize			(void) = 0;		

		/** 
			Returns whether or not the attributes in this collection are enabled.
			@return If kFalse, then its list of ClassIDs should be ignored.
		*/
		virtual bool8		GetEnabled			(void) const = 0;

		/** 
			Set whether or not the attributes in this collection are enabled.
			@param yesno - IN: If kFalse, then the list of ClassIDs will be ignored.
		*/
		virtual void		SetEnabled			(bool8 yesno) = 0;
		
		/**
			Returns whether the attribute for the specified classID is enabled
			@param classID - IN: The ClassID of the attribute we are interested in.
			@return kTrue if GetEnabled() is kTrue and the classID is present.
		*/
		virtual bool8		IsAttributeEnabled	(const ClassID& classID) const = 0;

		/**
			Returns whether all the attributes for the implementation are present in this collection.  
			That is, should all of the check boxes in the panel of the eye dropper settings dialog, 
			for which this implementation represents, be checked?
			@return kTrue if all the attributes for the implementation are present in this collection.
		*/
		virtual bool8		AllAttributesEnabled(void) const = 0;
		
		/** The eye dropper's Options dialog has check boxes with specific widget IDs for one or
			more attributes.  This method looks for the presence of the ClassID of the attributes
			associated with the provided widget to determine whether or not the widget should be
			enabled.  That is, this method is used to determine the state of the checkboxes in
			the eye dropper's Options dialog.
			@param widgetID - IN: Widget ID of the checkbox in the eye dropper Options dialog.
			@return kTrue if the widget should be enabled (because the attributes associated
			with the widget in the Options dialog are present in this filter/collection).
		*/
		virtual bool8		IsWidgetEnabled		(const WidgetID& widgetID) const = 0;

		/** Enable/disable the attributes associated with the given WidgetID by adding/removing
			their ClassIDs to/from this collection.
			@param widgetID - IN: Widget ID of the checkbox in the eye dropper Options dialog.
			@param enable - IN: Whether or not to add or remove the attribute's ClassIDs.
		*/
		virtual void		EnableWidgetsAttributes (const WidgetID& widgetID, bool8 enable) = 0;

		/** If this group has styles (e.g, character styles, paragraph styles, etc.) apply them
			if SetApplyStyles(kTrue) is called.  Otherwise, only look at the ClassIDs in this collection.
			@param yesno - IN: Whether or not to enable the applying of styles.
		*/
		virtual void		SetApplyStyles		(bool8 yesno) = 0;

		/** Returns whether or not to enable the applying of styles.
		*/
		virtual bool8		GetApplyStyles		(void) const = 0;
		
		/**
			Returns the ClassID of the attribute stored at the zero-based index in the collection.
			@param index - IN: zero-based index of the attribute in question.
			@return ClassID of the attribute stored at the zero-based index in the collection.
		*/
		virtual ClassID		GetClassID			(int32 index) const = 0;

		/**	Replaces the ClassID at a particular location in the collection with a new ClassID.
			@param index - IN: zero-based index of the attribute in question.
			@param replaceClassID - IN: ClassID to store at the index.
		*/
		virtual void		SetClassID			(int32 index, const ClassID& replaceClassID) = 0;

		/**	Find the ClassID associated with a particular attribute and return its zero-based index.
			If -1 is returned, then attribute is not in the collection.
			@param classID - IN: ClassID of a particular attribute.
			@return zero-based index of the classID or -1 if it is not found.
		*/
		virtual int32		GetIndex			(const ClassID& classID) const = 0;
		
		/**	
			Returns number of ClassIDs stored in the collection.
		*/
		virtual int32		Length				(void) const = 0;

};

#endif
