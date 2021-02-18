//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDocMarginsCmdData.h $
//  
//  Owner: Paul Sorrick
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2018 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it. If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Data interface for set margin command.
//  
//========================================================================================

#pragma once
#ifndef __IDocMarginsCmdData__
#define __IDocMarginsCmdData__

#include "IPMUnknown.h"
#include "IDocMarginsCmdData.h"
#include "PMReal.h"
#include "IDocument.h"

class IDocMarginsCmdData : public IPMUnknown
{
public:
	/**	Set the margins for document and pages in the kSetDocMarginCmdBoss item list. 
		@param insideLeft	PMReal& IN	refers to inside (for facing pages case) or left margin.
		@param top			PMReal& IN	refers to top margin.
		@param outsideRight	PMReal& IN	refers to outside (for facing pages case) or right margin.
		@param bottom		PMReal& IN	refers to bottom margin.
	 */
	virtual void Set(const	PMReal&	insideLeft,
		const	PMReal&	top,
		const	PMReal&	outsideRight,
		const	PMReal&	bottom) = 0;

	/**	Return the margin values in the data interface.
		@param insideLeft	PMReal* OUT returns the inside or left margin. 
		@param top			PMReal* OUT returns the top margin.
		@param outsideRight	PMReal* OUT returns the outside or right margin.
		@param bottom		PMReal* OUT returns the bottom margin.
	 */
	virtual void GetMargins(PMReal* insideLeft, PMReal* top, PMReal* outsideRight, PMReal* bottom) const = 0;

	/**	Set the document for which preferences are to be operated on.
		@param doc			UIDRef	IN returns the inside or left margin.
	*/
	virtual void SetDocument(const UIDRef& doc) = 0;

	/**	Get the document for which preferences are to be operated on.
		@return document reference.
	*/
	virtual const UIDRef& GetDocument() const = 0;

	/**	Sets whether the doc margin's left, right, top, bottom will be same or not.
		@param	bUniform	bool16	refers to the flag to change the margins uniformly.
	*/
	virtual void SetUseUniformMargins(bool16 bUniform) = 0; 

	/**	Returns whether the doc margin's left, right, top, bottom will be same or not.
		@return	flag that represents whether the margins change uniformly or not.
	*/
	virtual bool16 GetUseUniformMargins() = 0;
};

#endif // __IDocsMarginsCmdData__
