//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStyleUnpacker.h $
//  
//  Owner: Eric_Menninga
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
#ifndef __IStyleUnpacker__
#define __IStyleUnpacker__

#include "IPMUnknown.h"
#include "TextID.h"

class AttributeBossList;
class PMString;
class IDrawingStyle;

/** 
	@ingroup text_style
*/
class IStyleUnpacker : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTYLEUNPACKER };

		/**  Allocates an AttributeBossList and applies all atttributes available in the specified style.
		@param styleID IN UID of style to unpack.
		@precondition styleID should be the UID of an object that implements ITextAttributes/IID_ITEXTATTRIBUTES.
		@postcondition Caller is responsible for deleting returned AttributeBossList
		*/
		virtual AttributeBossList* CreateUnpackedStyle(UID styleID) = 0;


		
		/**  Applies all attributes available in the specified style to the passed in AttributeBossList.
		@param styleID IN UID of style to unpack.
		@param  INOUT DESCRIPTION.
		@precondition Callers should supply a valid AttributeBossList *.
		*/
		virtual void ApplyUnpackedStyle( UID styleID, AttributeBossList * attributeList ) = 0;

		/**  Queries or fills out a kComposeStyleBoss from the specified style and overrides.
		@param fill IN OUT The resulting IDrawingStyle.
		@param styleID IN The style to draw attributes from.
		@param overrides IN Applies these overrides after style attributes.
		@precondition fill can be nil.  If so a ref counted object is returned.  Otherwise the passed in boss is used.
		@postcondition Caller will need to release a ref counted fill.
		*/
		virtual void QueryCondensedStyle(IDrawingStyle **fill, UID styleID, const AttributeBossList *overrides) = 0;

		/**  Queries or fills out a kComposeStyleBoss from the specified story thread style, style and overrides.
		@param fill IN OUT The resulting IDrawingStyle.
		@param storyThreadStyle IN The style to draw story thread attributes from.
		@param styleID IN The style to draw attributes from.
		@param overrides IN Applies these overrides after style attributes.
		@precondition fill can be nil.  If so a ref counted object is returned.  Otherwise the passed in boss is used.
		@postcondition Caller will need to release a ref counted fill.
		*/
		virtual void QueryCondensedStyle(IDrawingStyle **fill, UID storyThreadStyle, 
											UID styleID, const AttributeBossList *overrides) = 0;

		/**  Tosses cached style data for given UID.
		@param styleID IN The UID you want to toss cached data for.
		*/
		virtual void TossCachedStyleData(UID styleID) = 0;
		
		/**  Releases some memory from Style Unpacker cache.
		@param everything IN Release entire cache.
		*/
		virtual void ReleaseSomeMemory(bool16 everything) = 0;
};


#endif
		//__IStyleUnpacker__
