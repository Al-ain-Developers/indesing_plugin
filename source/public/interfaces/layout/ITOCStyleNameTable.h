//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ITOCStyleNameTable.h $
//  
//  Owner: Yeming Liu
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
//  Comments: This interface keeps track of the TOC styles on Session/Doc workspace.
//  It is almost the same as IStyleNameTable except that it does not have 
//  IsBasedOn(). 
//  
//========================================================================================

#pragma once
#ifndef __ITOCSTYLENAMETABLE__
#define __ITOCSTYLENAMETABLE__

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "TOCID.h"

class PMString;

/** This interface keeps track of the table of content(TOC) styles on Session/Doc workspace.
	It is a subset of IStyleNameTable except that it does NOT have 
	information related to based on, KBSC(keyboard shortcut), import flag etc. 
*/
class ITOCStyleNameTable : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITOCSTYLENAMETABLE };

		/**	Get the total number of styles in table of content style table.
			@param none
			@return int32 total number of styles.
		*/
		virtual const int32 GetNumStyles() const = 0;

		/**	Get the default TOC style.
			@param none
			@return UID the default style.
		*/
		virtual const UID GetDefaultTOCStyleUID() const = 0;

		/**	Set the default style.
			@param uid IN the style to be set as a default style.
		*/
		virtual void SetDefaultTOCStyleUID(UID uid) = 0;

		/**	Add a new style to the style name table.
			@param style IN the style to be added in the style name table.
		*/
		virtual void AddStyle(UID style) = 0;

		/**	Remove style from style name table.
			@param style IN the style to be removed from the style name table.
		*/
		virtual void RemoveStyle(UID style) = 0;

		/**	Get the style UID with the given index(0-based).
			@param id IN the index.
			@return UID the nth style.
		*/
		virtual const UID GetNthStyle(int32 id) const = 0;

		/**	Get the style UID with the given name.
			@param name IN the style name.
			@return UID the style corresponding to the given name.
		*/
		virtual const UID FindByName(const PMString& name) const = 0;

		/**	Get the style name with the given index(0-based).
			@param index IN the index of style.
			@param pName OUT the name corresponding to the given index.
		*/
		virtual void GetNthStyleName(int32 index, PMString *pName) const = 0;

		/**	Get the style index with the given name.
			@param pName IN the style name.
			@return int32 the index of the style(0-based).
		*/
		virtual int32 GetStyleIndexByName(PMString& pName) const = 0;

		/**	Get a unique style name with the given base name. It usually uses for duplicating a style. 
			The returned string will have " copy" appended after base name. 
			If "baseName copy" exists, it will append number after copy and look like "baseName copy 1".
			@param baseName IN the base name.
			@return PMString the style name. 
		*/
		virtual PMString	GetUniqueStyleName(PMString& baseName) = 0;
};

#endif	// __ITOCSTYLENAMETABLE__