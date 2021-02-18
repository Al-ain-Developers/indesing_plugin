//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPSetAttributesCmdData.h $
//  
//  Owner: Matt Phillips
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
#ifndef __IXPSetAttributesCmdData__
#define __IXPSetAttributesCmdData__

#include "IPMUnknown.h"
#include "XPID.h"
#include "IXPAttributeSuite.h"

/**	Data interface for setting arbitrary transparency attributes on page item(s).
*/

class IXPSetAttributesCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXPSETATTRIBUTESCMDDATA };
	
		/** Sets the list of attributes to apply to the page items.
			@param newList IN The list of attributes and values.  A copy of this list is stored.
		*/
		virtual void SetAttributeList(const IXPAttributeSuite::AttributeList& newList) = 0;
		
		/** Gets the list of attributes.
			@param list OUT A list whose contents (if any) are replaced with the list of attributes to be applied.
		*/
		virtual void GetAttributeList(IXPAttributeSuite::AttributeList& list) const = 0;

		/** When applying the command to more than one page item, it's not possible to specify
			a single value for the gradient feather length and center attributes.  This method
			specifies how to handle these attributes.  (These work for single page items too.)

			@param doInit IN	If true, the command will automatically inspect the page item(s)
								and the list of attributes being applied.  If the command is applying
								a gradient-feather-apply=true attribute, the command will check for
								corresponding center and length attributes in the attribute list.
								If these are missing and the page items for the command don't have
								length/center attributes established (or the length/center values
								are zero), the command will initialize those attributes to their
								defaults based on the page item's geometry.
								If false, no such inspection occurs.
								The default value is false.
		*/
		virtual void SetAutoInitializeGradientFeatherGeometry(bool32 doInit) = 0;

		/** Returns the auto initialize of gradient feather geometry attributes state.
			@return True if the command will auto-initialize gradient feather attrs, false otherwise.
		*/
		virtual bool32 GetAutoInitializeGradientFeatherGeometry() const = 0;

		/** When applying the command to more than one page item we need special processing
			for partial angle/distance/x/y application -- eg applying X offset only to inner
			shadow, since inner shadow represents the shadow location in terms of angle and
			distance.  So in order to apply *only* xoffset we have to process each page item
			independently.  The default is an empty list (no partial applications).

			@param partials IN The list of partial ADXY values to apply.  The list is copied.
		*/
		virtual void SetPartialADXYVector(const IXPAttributeSuite::PartialADXYVector& partials) = 0;

		/** Returns the list of partial ADXYs to apply.
			@return A const reference to the list.
		*/
		virtual const IXPAttributeSuite::PartialADXYVector& GetPartialADXYVector() const = 0;
};

#endif