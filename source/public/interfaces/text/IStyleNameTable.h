//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStyleNameTable.h $
//  
//  Owner: EricM
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
#ifndef __IStyleNameTable__
#define __IStyleNameTable__

#include "IPMUnknown.h"
#include "UIDRef.h"

class PMString;

/**	IStyleNameTable is a mapping between strings (names) and UIDs (various objects).
	Many examples exist. The most common being the paragraph text-style name table
	and the character text-style name table. 
	All of these tables rely on the existance of the IStyleInfo interface on the registered objects.
	@see IStyleInfo.
	@ingroup text_style
*/
class IStyleNameTable : public IPMUnknown
{
	public:
		/**   
		Get the UID of the object (usually a kStyleBoss) with the specified name.
		*/
		virtual UID FindByName(const PMString& name) const = 0;

		/**
		Return the number of objects in this table
		*/
		virtual int32 GetNumStyles() const = 0;

		/**   
		Add an object (usually a style) to the table. This object should have an IStyleInfo or IObjectStyleInfo interface.
		*/
		virtual void AddStyle(UID style) = 0;
 
		/**   
		Add an object (usually a style) to the table. This object should have an IStyleInfo or IObjectStyleInfointerface.
		*/
		virtual void InsertStyle(UID style, int32 position) = 0;

		/**   
		Remove the (usually a style) from the table.
		*/
		virtual void RemoveStyle(UID style) = 0;
 
		/**   
		Return an object from the table by index. Used when iterating over the table.
		*/
		virtual UID GetNthStyle(int32 id) const = 0;

		/**   
		Returns the index of an object in the table. Returns -1 if non-existant.
		*/
		virtual int32 GetStyleIndex(UID style) const = 0;

		/**   
		Returns the object considered the "default". This corresponds to the object that the user has specified
		as the default -- it does not correspond to a base or root object.  See GetRootStyleUID()
		*/
		virtual UID GetDefaultStyleUID() const = 0;

		/**   
		Sets the default, and returns the object previously considered the "default". 
		This corresponds to the object that the user has specified as the default --
		it does not correspond to a base or root object.  See GetRootStyleUID()
		*/
		virtual UID SetDefaultStyleUID(UID d) = 0;		
		
		/**   
		Many tables have an idea of a "root" object. For text style name tables, this is the [No xxx Style] object.
		You are not allowed to set the root style.
		*/
		virtual UID GetRootStyleUID() const = 0;

		/**   
		Is the selfUID object based on the otherUID parameter?  This can be through any levels of hierarchy.
		This relies on the IStyleInfo interface.
		*/
		virtual bool16 IsBasedOn(UID selfUID, UID otherUID) const = 0;

		/**   
		Sorts the table by name and returns kTrue if anything changed position.
		@param whichSort a hint about what kind of sort this is. If you think the list is almost sorted, pass kIncrementalSort. If you think it's totally unsorted, pass kIncrementalSort. Either will work, but you'll get better performance if you pass the right one.			
		*/
		enum SortHint { kIncrementalSort,kTotalSort };
		virtual bool16 ReSort(SortHint whichSort = kIncrementalSort) = 0;

		/**
		USED ONLY BY OBJECT STYLES CURRENTLY
		Sets the Default Text Style for this name table
		*/
		virtual void SetDefaultTextStyleUID(UID d) = 0;		

		/**
		USED ONLY BY OBJECT STYLES CURRENTLY
		Gets the Default Text Style for this name table
		*/
		virtual UID GetDefaultTextStyleUID() const = 0;

		/**
		USED ONLY BY OBJECT STYLES CURRENTLY
		Sets the Default Frame Grid Style for this name table
		*/
		virtual void SetDefaultFrameGridStyleUID(UID d) = 0;		

		/**
		USED ONLY BY OBJECT STYLES CURRENTLY
		Gets the Default Frame Grid Style for this name table
		*/
		virtual UID GetDefaultFrameGridStyleUID() const = 0;

		/** PRIVATE USE ONLY, DO NOT CALL THIS. this is needed for document conversion.
		*/
		virtual UID SetRootStyleUID(UID d) = 0;

};

#endif
	// __IStyleNameTable__
