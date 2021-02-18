//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IZeroPointPrefsCmdData.h $
//  
//  Owner: psorrick
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
//  Data interface for ZeroPoint prefs commands.
//  includes : 	ZeroPoints location relative to upper left corner of
//  spread and whether zero point is locked or unlocked. 
//  
//========================================================================================

#pragma once
#ifndef __IZeroPointPrefsCmdData__
#define __IZeroPointPrefsCmdData__

#include "IPMUnknown.h"
#include "SpreadID.h"
#include "UIDRef.h" 
#include "PMPoint.h"

class IDataBase;
/** Data interface for zero point preference-related commands.
	Used to set/get data for either the session workspace or the document workspace. 
	Session workspace values are used for future documents and document workspace values 
	are used for the current document. If UID is kInvalidUID, the session is used.

	@see SetZeroPointPrefCmd
	@see SetZeroPointLockPrefCmd
	@see ZeroPointTracker
	@see ZeroPointEventHandler
*/
class IZeroPointPrefsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IZEROPOINTPREFSCMDDATA };

	/** Set zero point location relative to upper left corner of document spread and whether zero point is locked.
		@param doc which document to affect.
		@param zeroPoint the relative location for zero point
		@param lock whether zero point is locked.
	*/
	virtual void Set(	const	UIDRef&	doc, 			/* which document to affect */
								PMPoint	zeroPoint,		/* Relative location for zero point */
								bool16	lock) = 0;		/* Zero point locked or unlocked */
	/** Accessor for document to affect.
	@return reference to UID of document to affect
	*/
	virtual const UIDRef& GetDocument() const = 0;
	/** Accessor for location of zero point relative to upper left corner of document spread.
	@return relative location for zero point
	*/
	virtual const PMPoint GetZeroPoint() const = 0;
	/** Accessor for whether zero point is locked.
	@return kTrue if zero point is locked, otherwise kFalse
	*/
	virtual const bool16 GetZeroPointLock() const = 0;
};


#endif // __IZeroPointPrefsCmdData__
