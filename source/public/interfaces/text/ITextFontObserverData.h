//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextFontObserverData.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ITextFontObserverData__
#define __ITextFontObserverData__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "TextPanelID.h"

/** Data included in kTextFontFamilyObserverBoss and kTextFontStyleObserverBoss to determine
	what kind of font menu to show.
	@ingroup text_font
*/
class ITextFontObserverData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTFONTOBSERVERDATA };

	/**	Set the font family UID boss ID. The initial value is kTextAttrFontUIDBoss
		@param nClass	boss id
	 */
	virtual	void	SetFontUIDBossID( const ClassID &nClass ) = 0;

	/**	Gets the font family boss id
		@return ClassID boss id
	 */
	virtual	ClassID	GetFontUIDBossID() const = 0;


	/**	Set the font style UID boss ID. The initial value is kTextAttrFontStyleBoss. This should
		match the value set in SetFontUIDBossID. So if SetFontUIDBossID set kTextAttrFontUIDBoss
		SetFontStyleBossID should set kTextAttrFontStyleBoss.
		@param nClass	boss id
	 */
	virtual	void	SetFontStyleBossID( const ClassID &nClass ) = 0;

	/**	Gets the font style boss id
		@return ClassID boss id
	 */
	virtual	ClassID	GetFontStyleBossID() const = 0;

	/**	Set to kFalse if you do not want to include missing fonts. Initial value is kTrue.
		@param bOn	if kTrue include missing fonts
	 */
	virtual	void	SetIncludeMissingFonts( bool16 bOn ) = 0;

	/**	Returns kTrue if missing fonts are set to be included.
		@return bool16	kTrue if missing fonts are set to be included.
	 */
	virtual	bool16	IsIncludingMissingFonts() const = 0;
};

#endif
