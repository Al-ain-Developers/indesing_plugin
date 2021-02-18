//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ICellCursorProvider.h $
//  
//  Owner: dwaterfa
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
//  Summary: Interface that allows Cells to create a cursor
//  
//========================================================================================

#pragma once
#ifndef __ICellCursorProvider__
#define __ICellCursorProvider__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "PMPoint.h"
#include "ParcelKey.h"

class IControlView;
class CursorSpec;


/** 
	Provides the cursor associated with the tracker which would act on the table at a given point
*/
class ICellCursorProvider : public IPMUnknown
{
public:
    enum { kDefaultIID = IID_ICELLCURSORPROVIDER };

	/**
		Returns the cursor which shows the action you can preform on the table at the point passed in

		@param parcelKey	The parcel of the cell you are over (for split rows)
		@param frontView	The view you are tracking in
		@param pt			The point in the view specified you are over in the table (in the coords of the pasteboard)
		@param spec			The cursor found
		@return bool16		Whether a cursor was found or not
	*/
    virtual bool16   GetCursor(ParcelKey parcelKey, IControlView* frontView,
								PBPMPoint &pt, CursorSpec &spec) = 0;

};

#endif
 
