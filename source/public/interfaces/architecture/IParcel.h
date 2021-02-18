//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IParcel.h $
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
//========================================================================================

#pragma once
#ifndef __IParcel__
#define __IParcel__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "PMMatrix.h"
#include "ShuksanID.h"
#include "ParcelKey.h"

class IParcelContainer;
class IParcelList;
class ITextFrameColumn;


#define kInvalidParcelIndex	-1


class IParcel : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPARCEL };

		/**
		Our ParcelList and our place in it.
		*/
		virtual IParcelList *	QueryParcelList() const = 0;
		virtual ParcelKey		GetParcelKey() const = 0;

		/**
		The ParcelContainer provides context that relates us to other Parcels.
		*/
		virtual IParcelContainer*	QueryParcelContainer() const = 0;

		/**
		Bounds are expressed in the "Content" coordinate system of the
		Parent Parcel. A child Parcel which uses the same coordinate system
		of that of the Parent Parcel Content would return the Identity
		Matrix.

		The actual shape within the Parcel is not available through this
		interface, however we give you some hints about the net content
		area. The idea here is that there could be some insets within the
		Parcel that make the actual content area smaller. Typically the
		GetBounds() and GetNetContentAreaBounds() return the same values.
		*/
		virtual PMRect			GetBounds() const = 0;

		/**
		Every Parcel is anchored at some point within a TextFrame.
		*/
		virtual UID				GetFrameUID() const = 0;
		virtual ITextFrameColumn *	QueryFrame() const = 0;
		virtual PMMatrix		GetToFrameMatrix() const = 0;

		/**
		GetAcceptingPendingInvals()

		Returns kTrue if the Parcel is accepting PendingInval rectangles,
		kFalse if not.
		*/
		virtual bool16			GetAcceptingPendingInvals() const = 0;
		virtual void			AddPendingInval(const PMRect& inval) = 0;

};

#endif	// __IParcel__
