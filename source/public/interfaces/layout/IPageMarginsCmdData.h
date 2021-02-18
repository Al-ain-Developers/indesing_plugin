//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageMarginsCmdData.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Data interface for set margin command.
//  
//========================================================================================

#pragma once
#ifndef __IPageMarginsCmdData__
#define __IPageMarginsCmdData__

#include "IPMUnknown.h"
#include "PMReal.h"

class IDataBase;

/** Command data interface associated with commands to manipulate page margins.

	@ingroup layout_margin
	@see IMargins
	@see kSetPageMarginsCmdBoss
*/
class IPageMarginsCmdData : public IPMUnknown
{
public:
	/**	Set the margins for pages in the kSetPageMarginCmdBoss item list. 
		@param insideLeft PMReal& refers to inside (for facing pages case) or left margin.
		@param top PMReal& refers to top margin.
		@param outsideRight PMReal& refers to outside (for facing pages case) or right margin.
		@param bottom PMReal& refers to bottom margin.
		@param valid bool16 The new margin valid valid. "Valid" refers to whether the page margins are in use (kTrue), or the page should
		get its margin values from its applied master (kFalse).
	 */
	virtual void Set(	const	PMReal&	insideLeft,		
						const	PMReal&	top,			
						const	PMReal&	outsideRight,	
						const	PMReal&	bottom,			
						const	bool16 valid) = 0;		


	/**	Return the margin values in the data interface.
		@param insideLeft PMReal* OUT returns the inside (for facing pages case) or left margin. 
		@param top  PMReal* OUT returns the top margin.
		@param outsideRight  PMReal* OUT returns the outside (for facing pages case) or right margin.
		@param bottom  PMReal* OUT returnbs the bottom margin.
	 */
	virtual void GetMargins(PMReal* insideLeft, PMReal* top, PMReal* outsideRight, PMReal* bottom) const = 0;

	/**	Return the valid value in the data interface.
		@return bool16 
	 */
	virtual const bool16 GetValid() const = 0;
};



#endif // __IPageMarginsCmdData__
