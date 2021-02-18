//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLPreferences.h $
//  
//  Owner: Ryan Gano
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
#ifndef __IXMLPreferences__
#define __IXMLPreferences__

#include "XMediaUIID.h"
#include "IPMUnknown.h"

//========================================================================================
// CLASS IXMLPreferences
//========================================================================================
/** User-interface preferences for the cross-media UI.
	Don't call mutators directly, process your own custom command if you want to change these.
*/
class IXMLPreferences : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLPREFERENCES };


	/**	Accessor for property controlling display of Tag Markers in the layout
		
		@return  kTrue if tag markers should be shown, kFalse otherwise
	 */
	virtual	bool16						GetShowTagMarkers() const = 0;

	/**	Mutator for property controlling display of Tag Markers in the layout
		@param showTagMarkers kTrue if these should be shown, kFalse otherwise
	 */
	virtual	void						SetShowTagMarkers(bool16 showTagMarkers) = 0;


	/**	Accessor for property determining whether tagged frames are highlighted in the layout
		
		@return  kTrue if taggged frames should be shown, kFalse otherwise
	 */
	virtual	bool16						GetShowTaggedFrames() const = 0;

	/**	Mutator for property determining whether tagged frames are highlighted in the layout
		@param showTagFrames kTrue if these should be shown, kFalse otherwise
	 */
	virtual	void						SetShowTaggedFrames(bool16 showTagFrames) = 0;	
	
	/**	Accessor for property determining whether to show the tagging presets dialog
		when automatically tagging parent story threads and/or tables
		
		@return  kTrue if the dialog should be shown, kFalse otherwise
	 */

	virtual bool16 GetShowTagOptions () const = 0;
	
	/**	NOT SUPPORTED: Do not Call
		Mutator for property determining whether to show the tagging presets dialog	
		when automatically tagging parent story threads and/or tables
		@param showTagOptions kTrue if the dialog should be shown, kFalse otherwise
	 */
	virtual void SetShowTagOptions (bool16 showTagOptions) = 0;

};


#endif
