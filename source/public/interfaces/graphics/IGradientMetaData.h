//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGradientMetaData.h $
//  
//  Owner: Thanh Nguyen
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
//  Defines the gradient metadata interface.
//  
//========================================================================================

#pragma once
#ifndef __IGradientMetaData__
#define __IGradientMetaData__

#include "IPMUnknown.h"
#include "IColorData.h"

#include "GradientFillID.h"

/**	This interface is obsolete. This is only provided for document phase 2 conversion
	when converting from version 2.x or older documents. 
	All other usages are not supported.
*/
class IGradientMetaData : public IPMUnknown
{
public:
	
	enum {kDefaultIID = IID_IGRADIENTMETADATA_OBSOLETE};


	virtual void SetGradientFillType (const GradientType& gradType) = 0;
	virtual void SetNumberOfStop(int16 gradColorNum) = 0;
	virtual void SetNthGradientColorMetaData(int16 index, IColorData* colorData) = 0;
	virtual void SetNthStopPosition(int16 index, PMReal boundValue) = 0;
	virtual void SetNthGradientMidPoint(int16 index, PMReal midPoint) = 0;

	virtual void InsertGradientColorMetaData(int16 index, IColorData* colorData) = 0;
	virtual void ClearAll() = 0;

	virtual void GetColorData(K2Vector<IColorData*>* colorDataList) = 0;
	virtual IColorData* GetNthColorData(int16 at) = 0;
	virtual GradientType GetGradientFillType() const = 0;
	virtual int16 GetNumberOfStop() = 0;
	
	virtual PMReal GetNthStopPosition(int16  index) const = 0;
	virtual PMReal GetNthGradientMidPoint(int16 index) const = 0;

	virtual void RemoveNthColorData(int16 at) = 0;
};

#endif // __IGradientMetaData__







