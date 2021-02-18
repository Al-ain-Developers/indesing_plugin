//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IGuidePreferencesFacade.h $
//  
//  Owner: nmccully
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
#ifndef __IGuidePreferencesFacade__
#define __IGuidePreferencesFacade__

// ----- Interfaces -----

#include "IPMUnknown.h"
#include "SpreadUIID.h"

// ----- Includes -----


/**   A high level API for dealing with guide options/prefs.  Please use the IGuidePreferencesFacade 
	directly via the UtilsBoss if possible, see Utils.h:
	i.e. Utils<Facade::IGuidePreferencesFacade>()->ShowSmartGuides(...);
	  @author Dave Stephens
   */
namespace Facade
{
	class IGuidePreferencesFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IGUIDEPREFERENCESFACADE };
		
		//------------------------------------------------------
		//	Smart Guide Options
		//------------------------------------------------------
		/**     Return whether or not Smart Guides are enabled.
			@return true if the Smart Guides feature is enabled. false otherwise.
		*/
		virtual bool GetShowSmartGuides() const = 0;

		/**     Set whether or not the Smart Guides feature is enabled.
			@param bShow [IN]: true to enable, false to disable
			@return kSuccess if successful.  Otherwise, an error code.
		*/
		virtual ErrorCode ShowSmartGuides(bool bShow) const = 0;

		/**     Return whether or not Smart Guides will snap to the center of objects.
			@return true if Smart Guides will snap to the center of objects. false otherwise.
		*/
		virtual bool GetSmartAlignToObjectCenter() const = 0;

		/**     Set whether or not Smart Guides will snap to the center of objects.
			@param bEnable [IN]: true to enable, false to disable
			@return kSuccess if successful.  Otherwise, an error code.
		*/
		virtual ErrorCode SetSmartAlignToObjectCenter(bool bEnable) const = 0;

		/**     Return whether or not Smart Guides will snap to the edges of objects.
			@return true if Smart Guides will snap to the edges of objects. false otherwise.
		*/
		virtual bool GetSmartAlignToObjectEdges() const = 0;

		/**     Set whether or not Smart Guides will snap to the edges of objects.
			@param bEnable [IN]: true to enable, false to disable
			@return kSuccess if successful.  Otherwise, an error code.
		*/
		virtual ErrorCode SetSmartAlignToObjectEdges(bool bEnable) const = 0;

		/**     Return whether or not Smart Dimension guides are enabled.
			@return true if Smart Dimension guides are enabled.. false otherwise.
		*/
		virtual bool GetSmartDimensionsEnabled() const = 0;

		/**     Set whether or not Smart Dimension guides are enabled.
			@param bEnable [IN]: true to enable, false to disable
			@return kSuccess if successful.  Otherwise, an error code.
		*/
		virtual ErrorCode SetSmartDimensionsEnabled (bool bEnable) const = 0;

		/**     Return whether or not Smart Spacing guides are enabled.
			@return true if Smart Spacing guides are enabled. false otherwise.
		*/
		virtual bool GetSmartSpacingEnabled() const = 0;

		/**     Set whether or not to enable Smart Spacing guides.
			@param bEnable [IN]: true to enable, false to disable
			@return kSuccess if successful.  Otherwise, an error code.
		*/
		virtual ErrorCode SetSmartSpacingEnabled(bool bEnable) const = 0;

		/**     Return UIDRef of the Smart Guides' UI color. The result can be
			passed to Utils<IUIColorUtils>()->GetRGBColorValue() to obtain a ColorArray
			representing the RGB color components.

			@return UIDRef of the Smart Guides' UI color.
		*/
		virtual UIDRef GetSmartGuidesColor() const = 0;

		/**     Set Smart Guides color.
			@param color [IN]: UID of the UI color to set.
			@return kSuccess if successful.  Otherwise, an error code.
		*/
		virtual ErrorCode SetSmartGuidesColor(UID color) const = 0;

		//------------------------------------------------------
		//	Standard Guide Options
		//------------------------------------------------------

	};
}
#endif	// __IGuidePreferencesFacade__
