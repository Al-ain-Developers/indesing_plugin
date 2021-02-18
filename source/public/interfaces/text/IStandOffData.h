//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStandOffData.h $
//  
//  Owner: Bernd Paradies, Nick Nussbaum
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
#ifndef __IStandOffData__
#define __IStandOffData__

#include "IPMUnknown.h"
#include "IStandOff.h"
#include "PMRect.h"
#include "StandOffID.h"			

class IGeometry;

//---------------------------------------------------------------
// interface IStandOffData
//---------------------------------------------------------------

/** Holds the standoff information which is used to cause text  
	in text frames to wrap around the "standoffs of pageitems". 
	This first implementation only implements bounding boxes.
	@ingroup text_wrap
*/
class IStandOffData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTANDOFFDATA };

	virtual  bool16			IsActive() const = 0;			// usually: GetMode() != kNone
					
	virtual IStandOff::mode	GetMode() const = 0;
	virtual void			SetMode(IStandOff::mode Mode, bool16 newUserPointList = kFalse) = 0;
	
	virtual IStandOff::form	GetForm() const = 0;
	virtual void			SetForm(IStandOff::form Form) = 0;

	virtual void			SetMargin(PMRect::PointIndex, PMReal nMargin) = 0;
	virtual PMReal			GetMargin(PMRect::PointIndex, bool16 bConvertIfInverted = kTrue) const = 0;

	/**
	StandOffs on MasterSpreads can affect TextWrapTargets on Layout Spreads.
	@return kTrue if wrap can affect other spreads if on a master spread
	*/
	virtual bool16			GetActiveFromMaster() const = 0;

	/**
	StandOffs on MasterSpreads can affect TextWrapTargets on Layout Spreads.
	@param v If kTrue, wrap will affect other spreads if on a master spread
	*/
	virtual void			SetActiveFromMaster(bool16 v) = 0;

	virtual IStandOff::side	GetSide() const = 0;
	virtual void			SetSide(IStandOff::side Side) = 0;

	virtual UID				GetStandOffUID() const = 0;
	virtual void			SetStandOffUID(UID nNewUID ) = 0;
	virtual IGeometry *		QueryStandOffGeometry() const = 0;

	virtual bool16			HasOnlyOneDistance() const = 0;
	
	virtual void			CopyTo(IStandOffData *pCopyTo) const = 0;
		// returns kTrue if it has a rectangular standoff
};

#endif
