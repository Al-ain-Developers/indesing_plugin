//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontFamilyData.h $
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
#ifndef __IFontFamilyData__
#define __IFontFamilyData__

#include "IPMUnknown.h"
#include "IFontMgr.h"		// FontNameInfo

class FontEntry;

/** Used to pass data to NewFontFamilyCmd
	@ingroup text_font
*/
class IFontFamilyData : public IPMUnknown
{
	public:		
		enum { kDefaultIID = IID_IFONTFAMILYDATA };

		/**	Gets the roman family name
			@param workspace
			@param familyName		family name of family to create
			@param makeFake			create a dysfunctional font family
		 */
		virtual void Set(const UIDRef& workspace, const PMString& familyName, bool16 makeFake) = 0;

		/**	Gets the roman family name
			@return PMString  Family Name
		 */
		virtual PMString 	GetFamilyName() const = 0;
		/**	Sets the native family name. If the font is Japanese writing script the Native name will be Japanese. 
			@param PMString  Native family name
		 */
		virtual void	 	SetFamilyNameNative(const PMString& familyNameNative) = 0;
		/**	Gets the native family name. If the font is Japanese writing script the Native name will be Japanese. 
			@return PMString  Native family name
		 */
		virtual PMString 	GetFamilyNameNative() const = 0;
		/** Get make fake variable
			@return bool16  true if creating a dysfunctional font family
		 */
		virtual bool16 		MakeFake() const = 0;
		/** Get workspace
			@return UIDRef  workspace
		 */
		virtual UIDRef		GetWorkspaceRef() const = 0;

		/**	The purpose of this is to be able to make entries in the family face table for
				missing fonts for which we have the face name and postscript name.
				@param addEntry		true if you want to make an entry in the family table.
												Also set the face name/postscript name for the font entry you want to make.
		*/
		virtual void	SetAddEntry(bool16 addEntry) = 0;
		/** Get add entry variable
			@return bool16  true if you want to make an entry in the family table.
		 */
		virtual bool16	GetAddEntry() const = 0;

		/** Set font entry 
			@param fontEntry  data for font entry
		 */
		virtual void	SetFontEntry( const FontEntry &fontEntry ) = 0;
		/** Get font entry
			@param fontEntry  data for font entry
		 */
		virtual void	GetFontEntry( FontEntry *fontEntry ) const = 0;

		/** Set missing
			@param isMissing 
		 */
		virtual void	SetMissingButFoundPSName( bool16 isMissing ) = 0;
		/** Get missing
		 */
		virtual bool16	GetMissingButFoundPSName( ) const = 0;


};

#endif
		// __IFontFamilyData__
		
