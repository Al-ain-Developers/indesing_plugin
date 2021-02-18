//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITOPOptionsCmdData.h $
//  
//  Owner: Yves Carbonneaux
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
#ifndef __ITOPOptionsCmdData__
#define __ITOPOptionsCmdData__

#include "IPMUnknown.h"

#include "TextOnPathID.h"

#include "TOPOptionsType.h"


//This class is an interface of the		kAddTextOnPathCmdBoss,
//										kPickUpTOPAttributesCmdBoss,
//										kApplyTOPAttributesCmdBoss

// The kAddTextOnPathCmdBoss:
//		IID_IBOOLDATA,			kBoolDataImpl,			//Default creation
//		IID_IPOINTLISTDATA,		kPointListDataImpl,		//Brackets points
//		IID_ITOPOPTIONSCMDDATA,	kTOPOptionsCmdDataImpl,	//Options: unique for all selected items
// If default creation is kTrue, the last 2 interfaces are not used. A TOP is created from beginning
// to end of the path using all default values for the options.

// The kPickUpTOPAttributesCmdBoss and kApplyTOPAttributesCmdBoss:
//		IID_ITOPOPTIONSCMDDATA,	kTOPOptionsCmdDataImpl,	//Options

/** 
	@ingroup text_onpath
*/
class ITOPOptionsCmdData : public IPMUnknown
{
	public:

		enum { kDefaultIID = IID_ITOPOPTIONSCMDDATA };


		virtual	void	SetTypeEffect( const EffectType typeEffect ) = 0;
		virtual	const	EffectType	GetTypeEffect() const = 0;

		virtual	void	SetTextAlign( const TextAlignType textAlign ) = 0;
		virtual const	TextAlignType	GetTextAlign() const = 0;

		virtual	void	SetPathAlign( const PathAlignType pathAlign ) = 0;
		virtual	const	PathAlignType	GetPathAlign() const = 0;

		// The overlap offset is a value (int) between -800 and 800
		// Default value is 0
		virtual	void	SetOverlapOffset( const int16  overlapOffset ) = 0;
		virtual	const	int16	GetOverlapOffset() const = 0;

		// Default value is kFalse
		virtual	void	SetFlip( const bool16  flip ) = 0;
		virtual const	bool16	GetFlip() const = 0;

		virtual void	Set( const TextAlignType  textAlign, const PathAlignType  pathAlign,
						const EffectType  typeEffect, const int16  overlapOffset,
						const bool16  flip ) = 0;
};

#endif //__ITOPOptionsCmdData__
