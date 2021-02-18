//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontGroup.h $
//  
//  Owner: Jack Kirstein
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
//  See the implementation CTPFontGroup.cpp and refer to the CoolType documentation for more information
//  
//========================================================================================

#pragma once
#ifndef __IFontGroup__
#define __IFontGroup__

#include "GRRefCountedObj.h"
#include "InterfacePtr.h"
#include "K2Vector.h"
#include "BravoForwardDecl.h"


class PMString;

/** This is a shell over the CoolType API for fontGroups.
	@ingroup text_font
*/
class IFontGroup : public grRefCountedObj
{
	public:
		/**
			Get name of the group. This is also called family name.
		
			@return	name of group
		*/
		virtual const PMString& GetGroupName() const = 0;
		/**
			Get native name of the group. This is also called native family name.
		
			@return	native name of group
		*/
		virtual const PMString& GetGroupNameNative() const = 0;

		/**	Number of CTFontDicts in this group. This number can be different
			for Roman and Japanese UI depending on the font.
			@return number of font styles in this group
		 */
		virtual int32 GetNumFonts() const = 0;

		/**
			Get the CoolType font family
		
			@return	CoolType font family (Declaration not available via public API)
		*/
		virtual CTFamily *GetCTFamily() const = 0;

		/**	Gets groups with same name.
			This will return all the groups with the same name. If fontGroups
			only has 1 value then there is only one font group with this name.
			@param fontGroups OUT vector of font group identifiers. 
		  		Call IFontManager's QueryFontGroup() with these number to get a group.
		 */
		virtual void GetGroupsWithSameName(K2Vector<int32>& fontGroups) const = 0;

		/** If more than one family has the same name this gets a unique string to append
			to the family name to get a unique name. Unique names are required currently
			for menus. Appends font type (TT) and possibly script.
			@return unique string to add to family name
		*/
		virtual PMString GetUniqueFamilyNameEnding() const = 0;

		/**	Index of group.
			@return index of group
		 */
		virtual int32 GetFontGroupIndex() const = 0;
    
        /** @param index The index of named/custom instance in font group
            @param actualIndexInDict OUT The corresponding index of named/custom instance in a font dict
            @return Index of the dictionary to which named/custom instance belongs
         */
        virtual int32 GetDictIndex(int32 index, int32& actualIndexInDict) const = 0;
    
        /**
            This method returns the CoolType returned PS name of default font in a font group.
            @param fontName [Out] CoolType PS name of default font in a font group.
         */
        virtual void GetDefaultVariableFontName(PMString& fontName) const = 0;
    
};

template <>
class InterfacePtr<IFontGroup>
{
public:
		InterfacePtr(IFontGroup * pFace)
			// Note: Constructing an InterfacePtr from an existing,
			// "real" interface pointer implies the InterfacePtr
			// now owns the reference that was held by the real pointer.
			: fFace(pFace) {}
		
		~InterfacePtr()
			{
				if (fFace != nil){
					//const_cast<IFontGroup *>(unknown)->Release();
					fFace->Release();
				}
			}
		
		operator IFontGroup*() const
		{ return fFace; }
			// We allow the cast operator to return a nil pointer
			// since it is valid to test against nil and may be valid
			// to pass a nil pointer to some methods.

		
		IFontGroup * operator ->() const
			{
			#ifdef DEBUG
				ASSERT_MSG(fFace != nil,"About to use nil interface ptr!");
			#endif
			return fFace;
			}

		// Added forget, get and reset from InterfacePtr		
		IFontGroup* forget()
			{
				IFontGroup* result = fFace;
				fFace = 0;
				return result;
			} 
		
		IFontGroup* get() const
			{
				return fFace;
			}
		
		void reset(IFontGroup* p = 0) 
			{
				if (fFace) 
					fFace->Release(); 
				fFace = p;
			}

private:
	IFontGroup * fFace;

		// If you feel you need one of these, let me know.  Thx. - Zak
		// For the sake of clarity and simplicity, they're currently not supported.

		InterfacePtr(void);
		InterfacePtr(const InterfacePtr<IFontGroup>& IFontGroupPtr);
		InterfacePtr<IFontGroup>& operator=(const InterfacePtr<IFontGroup>& IFontGroupPtr);
		InterfacePtr<IFontGroup>& operator=(IFontGroup * pFace);

};

#endif
