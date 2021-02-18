//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISetFittingOptionsCmdData.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __ISETFITTINGOPTIONSCMDDATA__
#define __ISETFITTINGOPTIONSCMDDATA__

#include "IPMUnknown.h"
#include "IReferencePointData.h"
#include "GenericID.h"

/** Command Data interface for the kSetFittingOptionsCmdBoss.  Use this interface to
	pass the fitting options to the command.
*/
class ISetFittingOptionsCmdData : public IPMUnknown
{
public:
	/**
		Define the default interface IID as IID_ITRANSFORM.
	*/
	enum { kDefaultIID = IID_ISETFITTINGOPTIONSCMDDATA };
	typedef enum { 
		kMixedFitting = -1,
		kNoFitting, 
		kFitContents, 
		kFitProportionally, 
		kFillProportionally 
	} PersistentFitOptions;

	/** Set the options
		@param refPoint (IN): one of the 9 reference point positions.
		@param cropAmounts (IN): pass kZeroRect if you do not want the graphic cropped.  Otherwise,
			the coordinates of the rect will be treated as crop amounts as opposed to an actual
			crop rect.
		@param fitting (IN): pass kNoFitting if you do not want to scale the graphic
			contents to fit the frame in any way.
		@param autoFit (IN): if kTrue, fitting options are applied when frame changes size or shape
	*/
	virtual void  SetFittingOptionsData(IReferencePointData::ReferencePointPosition refPoint, 
				const PMRect& cropAmounts,
				PersistentFitOptions fitting /*= kNoFitting*/, 
				bool16 autoFit /*= kFalse*/) = 0;

	/** Get the reference point set via the Set method
	*/
	virtual IReferencePointData::ReferencePointPosition GetReferencePoint(void) const = 0;

	/** Get the crop amounts set via the Set method. */
	virtual void GetCropAmounts(PMRect* cropAmounts) const = 0;

	/** Get the fitting option set via the Set method */
	virtual PersistentFitOptions GetFitting(void) const = 0;

	/** Get the autofit option set via the Set method */
	virtual bool16 GetAutoFit(void) const = 0;
};

#endif
