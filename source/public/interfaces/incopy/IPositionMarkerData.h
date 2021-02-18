//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IPositionMarkerData.h $
//  
//  Owner: Michele Goodwin
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
#ifndef __IPositionMarkerData__
#define __IPositionMarkerData__

#include "PMString.h"
#include "EditorHelperID.h"

class IPositionMarkerData : public IPMUnknown
{

public:

	enum	{kDefaultIID = IID_IPOSITIONMARKERDATA};

	/** These are direct non-command based methods. */

	/**	
	Set position marker.
	@param textModelRef the model the new position marker is within
	@param textIndex position of the new marker
	*/
	virtual void SetPositionMarker(const UIDRef& textModelRef, TextIndex textIndex) = 0;

	/**	
	Clear existing position marker.	
	*/
	virtual void ClearPositionMarker() = 0;

	/**
	Returns the text model ref for the current position marker.
	@return UIDRef of the model the position marker is within
	*/
	virtual UIDRef GetTextModel() = 0;

	/**
	Returns the text index for the position of the current marker.
	@return TextIndex of the position of the current marker
	*/
	virtual TextIndex GetTextIndex() = 0;

	/**
	Returns kTrue if TextModelRef is not UIDRef::gNull and TextIndex is not kInvalidTextIndex.
	@return bool16
	*/
	virtual bool16 PositionMarkerExists() = 0;

	/**
	Returns kTrue if TextModelRef is a valid TextModel and TextIndex is within that model.
	@return bool16
	*/
	virtual bool16 PositionMarkerValid() = 0;
};

#endif // __IPositionMarkerData__
