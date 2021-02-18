//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IConvertSwatchCmdData.h $
//  
//  Owner: Chris Jones
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
#ifndef __IConvertSwatchCmdData__
#define __IConvertSwatchCmdData__

#include "IPMUnknown.h"
#include "DocFrameworkID.h"
#include "UIDRef.h"
#include "PMPoint.h"
#include "ISwatchList.h"
#include "ICommandSequence.h"

class UIDList;

/**	A swatch color conversion command data interface. This is used for converting
	color managed swatch color data from source profile to destination profile.
*/
class IConvertSwatchCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONVERTSWATCHCMDDATA };

public:
	// Accessors and Manipulators

	/**	Returns the source swatch UIDRef.
	*/
	virtual UIDRef GetSource() = 0;
	/**	Sets the source swatch UIDRef
		@param refSource is the source swatch UIDRef
	*/
	virtual void   SetSource( UIDRef& refSource ) = 0;

	/**	Returns the target swatch UIDRef.
	*/
	virtual UIDRef GetTarget() = 0;

	/**	Sets the target swatch UIDRef
		@param refTarget is the target swatch UIDRef
	*/
	virtual void   SetTarget( UIDRef& refTarget ) = 0;

	/**	Returns the target swatch list.
	*/
	virtual ISwatchList* GetSwatchList() = 0;

	/**	Sets the target swatch list.
		@param pSwatchList is the target swatch list
	*/
	virtual void SetSwatchList( ISwatchList* pSwatchList ) = 0;

	/**	Return whether or not cancel is allowed.
		@return true if conversion can be cancelled.
	*/
	virtual bool16 GetAllowCancel() = 0;

	/**	Set whether or not conversion can be cancelled
		@param bAllow is true if conversion can be cancelled.
	*/
	virtual void SetAllowCancel( bool16 bAllow ) = 0;

};


#endif // __IConvertSwatchCmdData__
