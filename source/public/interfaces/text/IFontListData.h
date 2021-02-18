//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontListData.h $
//  
//  Owner: lance bushore
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
#ifndef __IFontListData_h__
#define __IFontListData_h__

#include "IPMUnknown.h"
#include "PMString.h"
#include "FontMgrID.h"

//========================================================================================
// CLASS IFontListData
//========================================================================================

/** Used to contain a list of font family names and font styles. Currently only used
	internaly by scripting code.
	@ingroup text_font
*/
class IFontListData : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IFONTLISTDATA };	// for UseDefaultIID()

	/**	Append a font family name and font style name to the list
		@param familyName	family name to append.
		@param styleName	style name to append
	 */
	virtual void			AppendEntry(const PMString& familyName, const PMString& styleName) = 0;

	/**	Empty the list
	 */
	virtual void			Clear() = 0;
	

	/**	Get nth font family name.
		@param index		index to get name. 0 based index.
		@return PMString	font family name
	 */
	virtual PMString		GetFamilyName(int32 index) const = 0;

	/**	Get nth font style name.
		@param index		index to get name. 0 based index.
		@return PMString	font style name
	 */
	virtual PMString		GetStyleName(int32 index) const = 0;

	/**	Length of list
		@return int32	length of font list
	 */
	virtual int32			Length() const = 0;
};

#endif