//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IFilteredCJKGridCmdData.h $
//  
//  Owner: Heath Lynn
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
//  Purpose:  Implementations of this interface store ICJKGridData, remembering
//  which parts of it are valid.  By default when you set a field, it
//  is automatically considered valid.
//  
//========================================================================================

#pragma once
#ifndef __FilteredCJKGridCmdData__
#define __FilteredCJKGridCmdData__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "CTextEnum.h"
#include "ICJKGridData.h"
#include "IDrawingStyle.h"

class ICJKLayoutGridDefaults;


class IFilteredCJKGridCmdData  : public ICJKGridData
{
public:

	enum { kDefaultIID = IID_IFILTEREDCJKGRIDCMDDATA};
	
	enum NamedGridFieldIDs
	{
		kFontUIDValid = 1,
		kFontStyleNameValid = 2,
		kTextSizeValid = 4,
		kCharAkiValid = 8,
		kLineAkiValid = 16,
		kHScaleValid = 32,
		kVScaleValid = 64,
		kTextAlignmentValid = 128,
		kGridAlignmentValid = 512,
		kCharacterHangValid = 1024,
		
		kAllValid = 2047,
		kAllInvalid = 0
	};

	

	/**  SetFieldValid is used to mark that valid data is stored for the given field.
		@param field IN enumerated value for the field.
		@param valid IN kTrue if the field is valid.
	*/
	virtual void SetFieldValid(IFilteredCJKGridCmdData::NamedGridFieldIDs field, bool16 valid) = 0;
	
	/**  GetFieldValid is used to determine if valid data is stored in the given field.
		@param field IN enumerated value for the field.
		@return kTrue if the field has valid data.
	*/
	virtual bool16 GetFieldValid(IFilteredCJKGridCmdData::NamedGridFieldIDs field) const = 0;

};

#endif
