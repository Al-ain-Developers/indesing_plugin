//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInkMgrUIUtils.h $
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
#ifndef __IInkMgrUIUtils__
#define __IInkMgrUIUtils__

#include "IPMUnknown.h"
#include "Utils.h"

#include "IColorData.h"

#include "PrintuiID.h"
#include "ColorSystemID.h"
#include "ShuksanID.h"
#include "PMString.h"
#include "UIDList.h"
#include "IInkData.h"
#include "BravoForwardDecl.h"


class	IWorkspace;
class	ISwatchList;
class	UIDList;
class	PMReal;
class	IDataBase;
class	IInkList;
class	IPMInkBossData;

class IInkMgrUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINKMGRUIUTILS };

	/**	Query for the current active ink list in the specified active context. If active context is not specified,
		the current active context is used.
		@param activeContext the specified active context.
		@return the IInkList interface pointer if one exists or nil.
	*/
	virtual IInkList* QueryActiveInkList (IActiveContext* = nil) = 0;

	/**	Query for the front most document's ink list
		@return the IInkList interface pointer if one exists.
	*/
	virtual IInkList* QueryActiveDocInkList () = 0;

	/**	Invoke the ink manager dialog.
		@param iInkList is the ink list to use to populate the ink manager dialog.
		@param dlgID is the dialog's resource ID.
	*/
	virtual void InvokeInkManagerDialog (IInkList* iInkList = nil, RsrcID dlgID = 0) = 0;

};

#endif
