//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/colormgmt/IColorXFormChange.h $
//  
//  Owner: Matt Phillips
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
//  Implements the IColorXFormChange interface, which is really just a pinger for use in 
//  the active context.  That is, it sits in the ActiveContext under IID_ICOLORXFORMCHANGE
//  and is used by others who might be interested in profile changes.
//  
//========================================================================================

#ifndef __IColorXFormChange__
#define __IColorXFormChange__

#if PRAGMA_ONCE
#pragma once
#endif

#include "IPMUnknown.h"
#include "ColorMgmtID.h"

class ICommand;

/**	Defines the type and scope of color transform changes
*/
#define CXFORMFLAG_AFFECTS_SCREEN			(1L<<0)	/**	Specifies changes affect screen. */
#define CXFORMFLAG_AFFECTS_PRINTER			(1L<<1)	/**	Specifies changes affect printer. */
#define CXFORMFLAG_AFFECTS_CACHEVALIDITY	(1L<<2) /** Specifies changes affect CMS cache. Discard any calibrated spaces. */

#define CXFORMFLAG_SCOPE_ITEMS			(1L<<16)	/** Changes affect specified items. */
#define CXFORMFLAG_SCOPE_DOCUMENTS		(1L<<17)	/** Changes affect entire document. */
#define CXFORMFLAG_SCOPE_GLOBAL			(1L<<18)	/** Changes affect globally. */

/**	This is the data interface which will broadcast color transform changes.
	This interface live on the session boss.
*/
class IColorXFormChange : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICOLORXFORMCHANGE };
public:
	/**	Specifies a color transform change have occurred.
		@param iDataBase is the database in which the change has targeted. If the database is the session database,
		then the scope of change is global.
		@param cmndChangedBy is the command causing the change.
		@param changeFalgs specifies the type and scope of change.
	*/
	virtual void Change(IDataBase* iDataBase, ICommand *cmdChangedBy, int32 changeFlags) = 0;

	/**	Returns the current type of change. This should be one or more of the CXFORMFLAG_XXX_XXX flags
		defained above.
	*/
	virtual int32 GetChangeFlags() const = 0;
};

#endif // __IColorXFormChange__


// End, IColorXFormChange.h.
