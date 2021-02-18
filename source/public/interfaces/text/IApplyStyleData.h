//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IApplyStyleData.h $
//  
//  Owner: EricM
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
#ifndef __IApplyStyleData__
#define __IApplyStyleData__

#include "IPMUnknown.h"
#include "TextID.h"
#include "K2SmartPtr.h"

class AttributeBossList;

/**	IApplyStyleData is the primary data interface for the commands that apply text attributes.
	This interface contains the attribute & style data that is to be applied.
	@ingroup text_style
*/
class IApplyStyleData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IAPPLYSTYLEDATA };

		/** Set  set the data about what to apply: character or paragraph styles & local overrides.
			@param whichStrand is the target to apply to: (kCharAttrStrandBoss or kParaAttrStrandBoss).
			@param style is the text style to apply -- can be kInvalidUID if this should be ignored.
			@param over is a shared pointer to an AttributeBossList containing attributes to apply.
				Can be empty if only a style is being applied.
		*/
		virtual void Set(ClassID whichStrand, UID style, const boost::shared_ptr<AttributeBossList>& over) = 0;

		/** GetStrandID is the apply command targetted towards character or paragraph style data?
			@return the ClassID of the strand in question (kCharAttrStrandBoss or kParaAttrStrandBoss)
		*/
		virtual ClassID GetStrandID() const = 0;

		/** GetStyleUID returns the UID of the style being applied. Can be kInvalidUID if only overrides are being applied.
			@return the UID of the style being applied.
		*/
		virtual UID GetStyleUID() const = 0;

		/** GrabOverrides returns the attributes being applied. Can be empty when only the style is being applied
			@return a shared pointer to an AttributeBossList containing the attributes to apply.
		*/
		virtual const boost::shared_ptr<AttributeBossList>& GrabOverrides() const = 0;


#ifdef DEBUG
		/** DataCanNoLongerBeChanged is Debug only and is used to trigger asserts when someone
			changes the AttributeBossList being handed out by GrabOverrides()
		*/
		virtual void DataCanNoLongerBeChanged() = 0;
#endif
};

#endif
