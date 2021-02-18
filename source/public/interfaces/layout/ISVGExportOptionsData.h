//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISVGExportOptionsData.h $
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
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2019 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this
//  file in accordance with the terms of the Adobe license agreement
//  accompanying it. If you have received this file from a source
//  other than Adobe, then your use, modification, or distribution of
//  it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ISVGExportOptionsData__
#define __ISVGExportOptionsData__

#include "ISVGAttributes.h"

#include "GenericID.h"

/**
	Interface for export options associated with an SVG object. Also maintains
	a state value for with each export option.
*/
class ISVGExportOptionsData : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ISVGEXPORTOPTIONSDATA};

	/** Enumerates the state of an option.
	   The option's value should not be accessed if the state is "kValueNotSet" or "kValueMixed".
	*/
	typedef enum
	{
		/* No value set - invalid (clients should treat as opaque). This is the default state. */
		kValueNotSet = 0,
		/* Valid value set. */
		kValueSet,
		/* The value is different across the selection. */
		kValueMixed
	} OptionState;

	/**
		Set SVG export type.
		@param type IN SVG export type
	*/
	virtual void SetSVGExportType(ISVGAttributes::EPubExportSVGStrategy type) = 0;

	/**
		Get SVG export type.
		@return ISVGAttributes::EPubExportSVGStrategy: SVG export type
	*/
	virtual ISVGAttributes::EPubExportSVGStrategy GetSVGExportType() const = 0;

	/**
		Get SVG export type state.
		@return OptionState: the current state of the option
	*/
	virtual OptionState GetSVGExportTypeState() const = 0;
    
    /**
        Set apply epub export svg strategy on all svgs option.
        @param value IN Tells whether the current EPUB Export Strategy should apply on all SVGs
     */
    virtual void SetApplyOnAllSVGsOption(bool16 value) = 0;
    
    /**
        Get apply epub export svg strategy on all svgs option.
        @return bool apply epub export svg strategy on all svgs option
     */
    virtual bool16 GetApplyOnAllSVGsOption() const = 0;
    
    /**
        Get apply epub export svg strategy on all svgs option state.
        @return OptionState: the current state of the option
     */
    virtual ISVGExportOptionsData::OptionState GetApplyOnAllSVGsOptionState() const = 0;
    
    /**
       Copy data from an instance of the same interface to this instance.
       @param pCopyFrom IN instance to copy from
     */
    virtual void CopyData(const ISVGExportOptionsData* pCopyFrom) = 0;
    
    /**
        Copy data from an instance of ISVGAttributes to this instance.
        @param pCopyFrom IN instance to copy from
    */
    virtual void CopyOptions(const ISVGAttributes *pCopyFrom) = 0;
    
    /**
       Resets the state of all options to kValueNotSet.
     */
    virtual void ResetState() = 0;

};

#endif
