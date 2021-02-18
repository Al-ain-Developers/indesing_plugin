//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDocIterationResult.h $
//  
//  Owner: Chris Jones
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
//  Purpose:
//  
//========================================================================================

#pragma once
#ifndef __IDocIterationResult__
#define __IDocIterationResult__

#include "UIDList.h"

class IInkResourceData;
class Font_Info;
class TrapZoneInfo;

class IDocIterationResult: public IPMUnknown
{
public:
	enum	
	{	
		kDefaultIID = IID_IDOCITERATIONRESULT 
	};

public:	
	// Manipulators
	virtual void SetGradientUsed( bool16 fGradient ) = 0;
	virtual void SetTransparentPages( K2Vector<int32>& vecPages ) = 0;
	virtual void InkResourceInsert( int32 nPage, IInkResourceData* pResourceData ) = 0;
	virtual void AppendFontInfo( const Font_Info* pFont ) = 0;
	/** Add the name of a missing font.
		@param fontName[IN]: Name of the missing font.
	*/
	virtual void AppendMissingFontName(const PMString& fontName) = 0;
	virtual void SetPagesWithSVGFonts(K2Vector<int32>& vecPages) = 0;

	virtual void SetImageCount( K2Vector<int32>& vecCountByPage ) = 0;
	virtual void TZPathsInsert( int32 nPage, K2Vector<TrapZoneInfo*>& vecTrapList ) = 0;

	/** Sometimes we care about the fonts that are supplied by the graphics within the document.
		For example, when placing a page from an imported INDD document, we may want to obtain a list
		of all the fonts in the document, including those within any vector graphics within said document.
		These fonts can then be stored in the IFontNames interface for the placed object.
		
		@param fontName [IN] the name of the graphic font.
	*/
	virtual void AppendGraphicSuppliedFontName(const PMString& fontName) = 0;

	// Accessors
    virtual int32			        InkRsrcLength(void) = 0;
    virtual IInkResourceData*       GetNthInkRsrcData(int32 index) const = 0;
	virtual int32                   GetImagesUsed(int32 nPage) const = 0;
	virtual int32                   NumberOfPagesWithTransparency() const = 0;
	virtual bool16			        GetTransparencyUsed(const int32 whichPage) const = 0;
	virtual int32			        NumFontInfo() const = 0;
	virtual Font_Info*			    GetNthFontInfo(int32 n) const = 0;

	/** Sometimes we care about the fonts that are supplied by the graphics within the document.
		For example, when placing a page from an imported INDD document, we may want to obtain a list
		of all the fonts in the document, including those within any vector graphics within said document.
		These fonts can then be stored in the IFontNames interface for the placed object.
		
		@return number of fonts supplied by graphics.
	*/
	virtual int32					NumGraphicSuppliedFonts() const = 0;

	/** Sometimes we care about the fonts that are supplied by the graphics within the document.
		For example, when placing a page from an imported INDD document, we may want to obtain a list
		of all the fonts in the document, including those within any vector graphics within said document.
		These fonts can then be stored in the IFontNames interface for the placed object.
		
		@param n [IN]: zero-based index of font to get
		@param fontName [OUT]: on return, will hold the name of the Nth graphic font.
	*/
	virtual void GetNthGraphicSuppliedFontName(int32 n, PMString& fontName) const = 0;

	/** Get the number of missing fonts. These fonts are NOT included in the NumFontInfo() count.
		@return number of missing fonts.
	*/
	virtual int32			NumMissingFonts() const = 0;

	/** Get the name of the Nth missing font.
		@param n [IN]: zero-based index of font to get
		@param fontName [OUT]: on return, will hold the name of the Nth missing font.
	*/
	virtual void GetNthMissingFontName(const int32 n, PMString& fontName) const = 0;

	virtual int32			        TZPathsLength(void) = 0;
    virtual K2Vector<TrapZoneInfo*> GetNthTZPathsList(int32 index) const = 0;

	// New additions
	virtual void SetGradientMeshUsed( bool16 fGradientMesh ) = 0;

	/** Append a list of page items with 1 or more data links if SetCollectLinks(true) has been called.
	
		@param links [IN]: A list of page items with links to append to the list encountered so far.
	*/

	virtual void AppendLinks(const UIDList& links) = 0;

	/** Get the list of page items with links used in this print job. Note that you will 
		need to query for the IDataLinkReference and/or IDataLinkListReference on each 
		element in the list to obtain the actual links.
		
		@return UIDList of links.
	*/
	virtual const UIDList& GetLinks() const = 0;
};

#endif

// End, IPrintData.h.
