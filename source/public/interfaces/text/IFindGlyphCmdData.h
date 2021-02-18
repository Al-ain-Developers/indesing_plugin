//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFindGlyphCmdData.h $
//  
//  Owner: Heath Horton
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
#ifndef __IFINDGLYPHCMDDATA__
#define __IFINDGLYPHCMDDATA__

#ifndef __IPMUnknown__
#include "IPMUnknown.h"
#endif

#include "CTextEnum.h" // Text::GlyphID
#include "TextWalkerServiceProviderID.h"

class AttributeBossList;

/**
	Command data interface, set/get the glyph data for find/change glyph related commands.
	@see kFindGlyphCmdBoss
	@see kReplaceGlyphCmdBoss
*/

class IFindGlyphCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFINDGLYPHCMDDATA };

	/**
	Sets the GID/CID of the glyph.
	@param glyphID is of type Text::GlyphID
	@see IFindGlyphCmdData::GetGlyphID
	 */
	virtual void SetGlyphID(const Text::GlyphID glyphID) = 0;

	/**
	Sets the font attributes of the glyph
	@param findList is a pointer to AttributeBossList 
	@see IFindGlyphCmdData::GetFindAppliedAttrs
	 */
	virtual void ApplyFindAttributeBossList(const AttributeBossList* findList) = 0;

	/**
	Sets the database for the font attributes
	@param targetDB is a pointer to IDataBase
	*/
	virtual void SetTargetDB(IDataBase* db) = 0;

	/**
	Sets the registry and ordering of a ROS(Registry Ordered Supplement) font group.
	@param registry is of type PMString
	@param ordering is of type PMString
	 */
	virtual void SetROSFontGroup(const PMString& registry,const PMString& ordering) = 0; 

	/**
	Set whether the glyph search is for a specific font or a ROS group. 
	@param bUseROSFontGroup is of type bool16
	@see IFindGlyphCmdData::ApplyFindAttributeBossList
	@see IFindGlyphCmdData::SetROSFontGroup
	*/
	virtual void SetUseROSFontGroup(const bool16 bUseROSFontGroup) = 0; 

	/**
	Gets the GID/CID of the glyph.
	@return value is of type Text::GlyphID
	@see IFindGlyphCmdData::SetGlyphID
	 */
	virtual Text::GlyphID 	GetGlyphID() const = 0;

	/**
	Gets the font attributes of the glyph
	@return value is a pointer to AttributeBossList
	@see IFindGlyphCmdData::ApplyFindAttributeBossList
	 */
	virtual const AttributeBossList* GetFindAppliedAttrs() const = 0;

	/**
	Gets the database for the font attributes
	@return value is a pointer to IDataBase specifying the database of the font attributes
	*/
	virtual IDataBase*		GetTargetDB() const = 0;

	/**
	Gets the registry and ordering of font group.
	@return registry is of type PMString
	@return ordering is of type PMString
	*/
	virtual void GetROSFontGroup(PMString& registry, PMString& ordering) const = 0;

	/**
	Get whether the glyph search is for a specific font or a ROS group. 
	@return value is of type bool16
	@see IFindGlyphCmdData::ApplyFindAttributeBossList
	*/
	virtual const bool16 GetUseROSFontGroup() const = 0; 
};

#endif

