//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISVGDocPrefs.h $
//
//  Owner: Jagriti Sikka
//
//  $Author: pmbuilder $
//
//  $DateTime: 2020/11/06 13:08:29 $
//
//  $Revision: #2 $
//
//  $Change: 1088580 $
//
//  Copyright 1997-2019 Adobe Systems Incorporated. All rights reserved.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or
//  distribution of it requires the prior written permission of Adobe.
//
//
//  Purpose:
//  Stores the current EPS import preferences. These preferences should
//  be set using the kSetEPSPrefsCmdBoss command.
//
//========================================================================================

#pragma once
#ifndef __ISVGDocPrefs__
#define __ISVGDocPrefs__

#include "IPMUnknown.h"
#include "ISVGAttributes.h"

#include "PMReal.h"

/** SVG Doc Preferences - settings used on doc level for SVG items.
 */
class ISVGDocPrefs : public IPMUnknown
{
public:
    /** Default IID to be used by UseDefaultIID() */
    enum { kDefaultIID = IID_ISVGDOCPREFS };
    
    /** Set EPUB Export strategy for SVGs
		@param strategy IN strategy for SVG export i.e. as Embed Code or Object tags
     */
    virtual void SetEPUBExportStrategy(const ISVGAttributes::EPubExportSVGStrategy strategy) = 0;
    
    /** Get EPUB Export strategy for SVGs
		@return ISVGAttributes::EPubExportSVGStrategy - strategy
     */
    virtual ISVGAttributes::EPubExportSVGStrategy GetEPUBExportStrategy() const = 0;
    
    /** Set Apply On All SVGs Pref value
		@param value IN whether to set apply on all SVGs or not
     */
    virtual void SetApplyOnAllSVGsPref(const bool16 value) = 0;
    
    /** Get Apply On All SVGs Pref value
		@return bool16 - whether apply on all SVGs is set or not
     */
    virtual bool16 GetApplyOnAllSVGsPref() const = 0;
    
};

#endif
