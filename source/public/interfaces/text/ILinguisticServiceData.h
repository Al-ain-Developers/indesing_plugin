//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ILinguisticServiceData.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ILinguisticServiceData__
#define __ILinguisticServiceData__

#include "IPMUnknown.h"
#include "LinguisticID.h"

class PMString;

//----------------------------------------------------------------------------------------
// Interface ILinguisticServiceData
//----------------------------------------------------------------------------------------

/**
	@ingroup text_ling
*/
class ILinguisticServiceData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINGUISTICDATA };

	/**	
		Gets service name.

		@return const PMString&	Service name returned.
	 */
	virtual const PMString& GetServiceName() const = 0;
	/**	
		Sets service name.

		@param rName	Service name to set to.
	 */
	virtual	void			SetServiceName( const PMString &rName ) = 0;

	/**	
		Gets service path.

		@return const PMString&	Service path returned.
	 */
	virtual const PMString& GetPath() const = 0;
	/**	
		Sets service path.

		@param rName	Service path to set to.
	 */
	virtual	void			SetPath( const PMString &rName ) = 0;
};

#endif
