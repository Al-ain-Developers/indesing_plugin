//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/ITransformSwatchesCmdData.h $
//  
//  Owner: James Jardee-Borquist
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

#ifndef __ITRANSFORMSWATCHESCMDDATA__
#define __ITRANSFORMSWATCHESCMDDATA__

#if PRAGMA_ONCE
#pragma once
#endif

#include "ICMSSettings.h"
#include "IPMUnknown.h"

#include "ACEColorMgmtID.h"

class ICMSProfile;
class ISwatchList;

//========================================================================================
// CLASS ITransformSwatchesCmdData
//========================================================================================

/**	Command data interface for transforming a color swatch from one profile to another.
*/
class ITransformSwatchesCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITRANSFORMSWATCHESCMDDATA };
	
	/**	Set up the color transform data for color transformation.
		@param pSrcDB specifies the source database.
		@param strSrcProfile specifies the name of the source profile.
		@param pDstDB specifies the destination database.
		@param strDstProfile specifies the name of the destination profile.
		@param inIntent spcifies the rendering intent of the source.
		@param inUseKPC specifies source black point compensation.
		@param inEngineCMS specifies the source color management engine.
		@param inEngineCMM specifies the source
		@param inSwatchList specifies the source swatch list corresponding to pSrcDB.
	*/
	virtual void Set(IDataBase*                    pSrcDB,
		             const PMString&               strSrcProfile,
					 IDataBase*                    pDstDB,
					 const PMString&               strDstProfile,
		             ICMSSettings::renderingIntent inIntent, 
					 bool16                        inUseKPC, 
					 uint32                        inEngineCMS, 
					 uint32                        inEngineCMM, 
					 ISwatchList*                  inSwatchList) = 0;
	
	/**	Returns the source profile.
	*/
	virtual ICMSProfile *QuerySrcProfile() = 0;
	/**	Returns the destination profile.
	*/
	virtual ICMSProfile *QueryDstProfile() = 0;
	/**	Returns the source rendering intent.
	*/
	virtual ICMSSettings::renderingIntent GetIntent() const = 0;
	/**	Returns whether or not source is using black point compensation.
	*/
	virtual bool16 GetUseKPC() const = 0;
	/**	Returns the source CMS engine.
	*/
	virtual uint32 GetEngineCMS() const = 0;
	/**	Returns the source CMM engine.
	*/
	virtual uint32 GetEngineCMM() const = 0;
	/**	Returns the source swatch list.
	*/
	virtual ISwatchList *GetSwatchList() const = 0;
};

#endif // __ITransformSwatchesCmdData__

// End, ITransformSwatchesCmdData.h.
