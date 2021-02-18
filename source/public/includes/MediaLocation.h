//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MediaLocation.h $
//  
//  Owner: wtislar
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __MediaLocation__
#define __MediaLocation__


/** 
	This class encapsulates and abstracts the location of media content. The location
	can be 	specified either as the absolute path to a local file, or as a URL. This
	class 	is useful when you need to maintain the fact that a string represents a local
	file path or a URL.
*/

class MediaLocation
{
public:
	/** Default contructor. */
	MediaLocation()
	:	fLocationIsURL(kFalse),
		fLocation(PMString("")) {}

	/** Constructs a MediaLocation object for either a local file or a URL. */
	MediaLocation( PMString locationString, bool16 isURL = kFalse )
	:	fLocationIsURL(isURL),
		fLocation(locationString) {}

	/** Copy constructor. */
	MediaLocation( const MediaLocation& orig )
	:	fLocationIsURL(orig.fLocationIsURL),
		fLocation(orig.fLocation) {}

		//----------OPERATORS---------------
	
	/** Assignment operator for MediaLocation variables. */		
	MediaLocation& operator = (const MediaLocation &copy)
		{ Set(copy); return *this; }

	/** Equivalence operator for MediaLocation variables. */
	bool16 operator == (const MediaLocation &ml) const
		{ return fLocationIsURL == ml.fLocationIsURL &&
				 fLocation == ml.fLocation; }

	/** Non-equivalence operator for MediaLocation variables. */
	inline bool16 operator != (const MediaLocation &ml) const
		{ return (!(*this == ml)); }

	/** Accesses the location string.
		@return a PMString object of a local file path or a URL.
	*/
	virtual PMString GetString() const { return fLocation; }

	/** Determines the extension of the file.
		@return a PMString containing the extension of the file or URL.
	*/
	virtual PMString GetExtensionString() const 
	{
		PMString extension("");
		PMString locStr(fLocation);
		CharCounter delimIndex = locStr.LastIndexOfCharacter('.');
		int32 extensionCharCount = delimIndex >= 0 ? locStr.CharCount() - delimIndex - 1 : 0;

		if ( extensionCharCount > 0 )
		{
			for ( CharCounter i = delimIndex + 1; i < locStr.CharCount(); i++ )
			{
				PlatformChar ch = locStr.GetChar( i );
				extension.Append( ch );
			}
		}
		return extension;
	}

	/**	Tests if the location is a file.
		@return kTrue if file; kFalse otherwise.
	*/
	virtual bool16 IsFile() const { return !fLocationIsURL; }

	/** Tests if the location is a URL.
		@return kTrue if URL, kFalse otherwise.
	*/
	virtual bool16 IsURL() const { return fLocationIsURL; }

private:
	bool16	fLocationIsURL;
	PMString fLocation; // fully-qualified location (URL or file path)

	void Set( const MediaLocation & copy )
		{ fLocationIsURL = copy.fLocationIsURL; fLocation = copy.fLocation; }
}; // end MediaLocation class


#endif // __MediaLocation__
