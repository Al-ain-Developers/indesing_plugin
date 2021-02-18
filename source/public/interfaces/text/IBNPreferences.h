//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IBNPreferences.h $
//  
//  Owner: Amit Batra
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

#ifndef __IBNPreferences__
#define __IBNPreferences__

#include "BNCoreID.h"
#include "BulletGlyph.h"

#include "IPMUnknown.h"

/**
    IBNPreferences manages the Bullets and Numbering preferences, which consist of the set of default bullets.
 */
class IBNPreferences: public IPMUnknown
{
public:

    enum
    {
        kDefaultIID = IID_IBNPREFERENCES
    };

	/**
		For internal use only: Gets whether the preferences have been initialized or not.
		@return True if initialized, false otherwise.
	*/
    virtual bool16 IsInitialized() const = 0;

	/**
		For internal use only: Sets the preferences to initialized or not initialized.
		@param bInitialized specifies whether to mark preferences as initialized or not. The default value is true.
	*/
	virtual void   SetInitialized(const bool16 bInitialized = kTrue) = 0;

	/**
		Gets the set of default bullets. 
		@return The set of default bullets.
	*/
    virtual const BulletGlyphSet& GetGlyphSet() const = 0;

	/**
		Sets the set of default bullets and marks the preferences as initialized.
		@param glyphSet specifies the set of default bullets.
	*/
	virtual void  SetGlyphSet(const BulletGlyphSet& glyphSet) = 0;
};

#endif // __IBNPreferences__
