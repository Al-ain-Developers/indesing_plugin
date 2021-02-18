//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDocFontMgr.h $
//  
//  Owner: ekenning
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
#ifndef __IDocFontMgr__
#define __IDocFontMgr__

#include "IPMUnknown.h"
#include "FontMgrID.h"
#include "IFontMgr.h"		// FontNameInfo
#include "IFontFamily.h"

class IFontGroupId;
class PMString;

/** Provides a way to get IFontFamily UIDs. We used to use Family names to do this however Family names
	are no longer unique for different IFontFamily. Now we need to use fontGroupIDs to correctly get a
	IFontFamliy UID. Note that in this file GetFontGroupUID is the same as GetFontFamilyUID.
	@ingroup text_font
*/
class IDocFontMgr : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDOCFONTMGR };


        //---------GET FONT FAMILY UID-----------------

		/**	Get IFontFamily UID from a IFontGroupId
			@param *fontGroupIDPtr 
			@param makeOneIfNecessary	If kTrue and the IFontGroupId does not exist in the
				document the UID is created.
			@return UID		font family UID
		 */
		virtual UID GetFontFamilyUID(const IFontGroupId *fontGroupIDPtr, bool16 makeOneIfNecessary = kTrue) = 0;

		/** You may need to create a group with a particular state.  For instance, the font exists in 
			on document, but not another.  In the case that makeOneIfNecessary is set to kTrue.  If the
			font does not exist in this document, it is copied from the supplied font.  If it already 
			exists, the copy is skipped and the UID	is simply returned.  (Note: No state is taken form
			the object if the group was	found to be previously created.)

			@param sourceFontFamily 
			@param makeOneIfNecessary	If kTrue and the IFontGroupId does not exist in the
				document the UID is created.
			@return UID		font family UID
		 */
		virtual UID GetFontGroupUID(IFontFamily * sourceFontFamily, bool16 makeOneIfNecessary = kTrue) = 0;
		
		
		/**	Get IFontFamily UID from a font
			@param *font  Uses postscript name and font type to find the IFontFamily
			@param makeOneIfNecessary	If kTrue and the font family does not exist in the
				document the UID is created.
			@return UID		font family UID
		 */
		virtual UID GetFontFamilyUID(const IPMFont *font, bool16 makeOneIfNecessary = kTrue) = 0;
		
		/**	Get IFontFamily UID from a familyname and optionally a style name
			@param	displayFamilyName	name of family as it appears in the menu to users. This can be
										a native or non native name. it can also have a font type
										appended such as (TT). This call will try and find the font
										family that matches the font type.
			@param	fontStyle			passing a fontStyle will help if there are 2 groups with the
										same name and the style name only exists in one of the groups.
										Passing an empty string causes style name not to be used. OUT
										on exit style name is updated to the non native style name as
										that is what we use in the text model. This value should
										be the empty string if you do not know it.
			@param makeOneIfNecessary	If kTrue and the font family does not exist in the
										document the UID is created.
			@return	UID
		*/
		virtual UID GetFontFamilyUID(const PMString &displayFamilyName, PMString &fontStyle, bool16 makeOneIfNecessary = kTrue) = 0;

		/**
			Used to create fonts from non Adobe applications like Word.
		
			@param	groupName
			@param	FontFaceMappingInfo
			@return UID		font family UID
		*/
		virtual UID GetFontGroupUIDWithFontFaceMappingInfo(const PMString& groupName,
													IFontFamily::FontFaceMappingInfo& FontFaceMappingInfo) = 0;

		/**
			This should not normally be called. The face entries are usually made automatically if the
			fonts are installed on the system.
			The purpose of GetFontFamilyUIDWithPostscriptName is to be able to make entries in the family
			face table for missing fonts for which we postscript name and font type. This is used by
			INX code to create font family entries for missing fonts.
		
			@param	familyName	family name of font to find or add
			@param	fontEntry	data of font to find or add. this is the data that will be added to the font family if this font face is not found.
			@return UID		font family UID
		*/
		virtual UID GetFontFamilyUIDWithPostscriptName(const PMString& familyName, const FontEntry &fontEntry) = 0;

		/**
			Similar to GetFontGroupUID but returns a IFontFamily. Not recommended to use this call. It
			does not support more than one group with the same family name.		
			@param	groupName
			@param	makeOneIfNecessary
			@return	IFontFamily*
		*/
		virtual IFontFamily* QueryFontGroup(const PMString& groupName, bool16 makeOneIfNecessary = kTrue) = 0;
		
		/**
			Using the default font name from the font manager gets the font family UID
		
			@return UID		font family UID
		*/
		virtual UID GetDefaultFamilyUID() = 0;


        //---------ADD/REMOVE UID-----------------

		/**
			Adds font family UID to doc font manager
		
			@param	groupUID	font family UID to add
		*/
		virtual void Append(UID groupUID) = 0;
		/**
			Removes font family UID to doc font manager
		
			@param	groupUID	font family UID to remove
		*/
		virtual void Remove(UID groupUID) = 0;	


        //---------ACCESS ROUTINES-----------------

		/**
			Gets count of font families in doc font manager
		
			@return	int32	count of font families
		*/
		virtual int32 GetFontGroupCount() const = 0;
		/**
			Gets the Nth font family in the doc font manger. Use with GetFontGroupCount to
			iterate thru all font families.
		
			@param	i	index of font family to retrieve
			@return UID		font family UID
		*/
		virtual UID GetNthFontGroupUID( int32 i) const = 0;


        //---------UPDATE-----------------

		/**
			Called when font on system change to update the font families in doc font manager
		*/
		virtual void FontSystemChanged(void) = 0;

		typedef enum { 
						kDoNotUpdateDysfunctionalFamilies,
						kUpdateOnlyDysfunctionalFamilies
				} UpdateFlags;
					
		/**	Update the fontGroupIDs that are cached and used to find UIDs. Also updates
			IFontFamily which has cached a IFontGroup. Need to update dysfunctional families separtely
			because they can modify IDocFontMgr.
			@param	usedFontList	fonts used in the document
			@param	updateFlag	whether to update dysfunctional families
			@return bool16 indicates whether any update occurred
		*/
		virtual bool16 UpdateCache(IUsedFontList *usedFontList, UpdateFlags updateFlag = kDoNotUpdateDysfunctionalFamilies) = 0;


        //----------DISCOURAGED ROUTINES---------------
        // 
		/** DISCOURAGED. This does not support more than one group with the same family name.
			GetFontGroupUID returns a UID for the named group.

            RECOMMENDATION -
            Use GetFontFamilyUID with IFontGroupId.

			@param groupName			family name. if 2 groups with family name first group is used.
			@param makeOneIfNecessary	If kTrue and the named group does not exist in the document
				the UID is created.
			@return UID		font family UID
		 */
		virtual UID GetFontGroupUID(const PMString& groupName, bool16 makeOneIfNecessary = kTrue) = 0;
		
		/** DISCOURAGED. THIS ROUTINE DOES NOT SUPPORT FONT TYPE. We can have 2 postscript names
			with different font types.
			The purpose of GetFontGroupUIDWithFontEntry is to be able to make entries in the family
			face table for missing fonts for which we have the face name and postscript name.
			The face entries are usually made automatically if the fonts are installed on the system.
			FontNameInfo is defined in IFontMgr.h .
		
            RECOMMENDATION -
            Use GetFontFamilyUIDWithPostscriptName

			@param	fontNames
			@return UID		font family UID
		*/
		virtual UID GetFontGroupUIDWithFontEntry( const IFontMgr::FontNameInfo& fontNames ) = 0;

		/*
		*/
		virtual PMString GetTypekitFontID(const PMString& familyName, const PMString& styleName) = 0;
};

#endif
		// __IDocFontMgr__
		
		