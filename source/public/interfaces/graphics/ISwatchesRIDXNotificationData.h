//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISwatchesRIDXNotificationData.h $
//  
//  Owner: SusanCL
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
#ifndef __ISWATCHESRIDXNOTIFICATIONDATA__
#define __ISWATCHESRIDXNOTIFICATIONDATA__

#include "IPMUnknown.h"
#include "ColorSystemID.h"
#include "ISwatchUtils.h"

class IDataBase;
class RIDXSource;

//________________________________________________________________________________________
//	class IRIDXNotifierHandler 
//________________________________________________________________________________________
/** A data interface that specifies the data and options for each of the notification type.
	Used in conjunction with all IRIDXNotifierHandler that are interested in the swatches.
	@see IRIDXNotifierHandler.h
*/
class ISwatchesRIDXNotificationData : public IPMUnknown 
{
public:
	// ----- Constants -----
	enum {kDefaultIID = IID_ISWATCHESRIDXNOTIFICATIONDATA};

	/**	Set the swatch replacement for the swatch being deleted.
		@param replacementRef the swatch replacment. If replacment is set to UIDRef::gNull, then the swatch being deleted should
		be converted to local (unnamed) swatch.
	*/
	virtual	void	SetDeleteSwatchReplacement (const UIDRef& replacementRef) = 0;

	/**	Returns the swatch replacement for the swatch being deleted.
		@return the swatch replacment. If returned UIDRef is UIDRef::gNull, then the swatch being deleted should
		be converted to local (unnamed) swatch.
	*/
	virtual	UIDRef	GetDeleteSwatchReplacement (void) const = 0;
			
	/**	Set the list of swatches being deleted.
		@param deleteSwatchList the list of swatches being deleted. 
	*/
	virtual	void	SetDeleteSwatchList (const UIDList& deleteSwatchList) = 0;

	/**	Returns the list of swatches being deleted.
		@return the list of swatches being deleted.
	*/
	virtual	const UIDList&	GetDeleteSwatchList (void) const = 0;
	
	/**	Set the swatch referenced option. This is the option with which the swatch references are computed.
		@param usageType the swatch usage type as defined in ISwatchUtils.h
		@see ISwatchUtils.h
	*/
	virtual	void	SetSwatchReferencedOption (const ISwatchUtils::SwatchUsageType& usageType) = 0;

	/**	Return the swatch referenced option. This is the option with which the swatch references are computed.
		@return the reference option.
	*/
	virtual	ISwatchUtils::SwatchUsageType	GetSwatchReferencedOption (void) const = 0;

};

#endif

