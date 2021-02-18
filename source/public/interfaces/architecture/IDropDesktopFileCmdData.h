//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDropDesktopFileCmdData.h $
//  
//  Owner: Dave Burnard
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
//  Data interface for import/placing when a desktop file is dragged over a pub.
//  
//========================================================================================

#pragma once
#ifndef __IDropDesktopFileCmdData__
#define __IDropDesktopFileCmdData__

#include "IPMUnknown.h"
#include "DragDropID.h"
#include "UIDRef.h"
#include "PMPoint.h"

class IPlaceBehavior;
class IHierarchy;

/** Data interface used on command boss used when a desktop file is dropped on a layout window.

*/
class IDropDesktopFileCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDROPDESKTOPFILECMDDATA };

	/** Specify what to do with file once it is placed. */
	enum eDropBehavior { 
	/** standard ProcessPlace. */
		kPlace, 
	/** ProcessReplace. */
		kReplace, 
	/** importing file as is (simulates Place dialog) */
		kImport ,
	/** loads place gun */
		kLoadPlaceGun 
	};

	/** Put the IPlaceBehavior version of the data into the interface

		@param where IN where di the drop occur in pasteboard coordinates
		@param parent IN object (if any) to be used as the parent for pageitems created by the drop
		@param file IN the file that was dropped
		@param flags IN flags indicating whether UI should be suppressed
		@param targetDoc IN document that the drop occured over
		@param targetBehavior IN Pointer to target place behavior object 
		@param dropBehavior IN what type of drop to perform
	*/
	virtual void Set(const PMPoint& where, const UIDRef& parent, IDFile &file, UIFlags flags, const UIDRef& targetDoc, IPlaceBehavior* targetBehavior, const eDropBehavior dropBehavior = kPlace ) = 0;

	/** Put the IHierarchy version of the data into the interface (special for XML)

		@param where IN where di the drop occur in pasteboard coordinates
		@param parent IN object (if any) to be used as the parent for pageitems created by the drop
		@param file IN the file that was dropped
		@param flags IN flags indicating whether UI should be suppressed
		@param targetDoc IN document that the drop occured over
		@param targetHier IN Pointer to IHierarchy object 
		@param dropBehavior IN what type of drop to perform
	*/
	virtual void Set(const PMPoint& where, const UIDRef& parent, IDFile &file, UIFlags flags, const UIDRef& targetDoc, IHierarchy* targetHier, const eDropBehavior dropBehavior = kPlace ) = 0;
	/** Get the location where the file was dropped */
	virtual const PMPoint& 	GetDropPoint() const = 0;
	/** Get the parent pageitem to use for the drop */
	virtual const UIDRef& 		GetParent() const = 0;
	/** Get the file that was dropped */
	virtual const IDFile&		GetSysFile() const = 0;
	/** Get the UIFlags for the drop */
	virtual UIFlags 			GetUIFlags() const = 0;
	/** Get the document the drop occurred over for the drop */
	virtual const UIDRef& 		GetTargetDocument() const = 0;
	/** Get the place behavior of the target */
	virtual IPlaceBehavior* 	GetTargetBehavior() const = 0;
	/** Get the spread layer of the target */
	virtual IHierarchy* 		GetTargetHierarchy() const = 0;
	/** Get the drop behavior for the drop */
	virtual const eDropBehavior	GetDropBehavior() const = 0;
};

#endif // __IDropDesktopFileCmdData__
