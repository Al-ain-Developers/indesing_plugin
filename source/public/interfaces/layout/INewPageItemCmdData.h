//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/INewPageItemCmdData.h $
//  
//  Owner: robin briggs
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
//  Purpose:	
//  Data interface for creating new page items. The dataBase, classID and type of 
//  default graphic attributes are mandatory settings. The point list and parent
//  are optional. Note that if the parent is not set a broadcast will not occur
//  as a result of the new page item command.
//  
//========================================================================================

#pragma once
#ifndef __INewPageItemCmdData__
#define __INewPageItemCmdData__

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "PMPoint.h"
#include "GenericID.h"

class IDataBase;

/** Data interface for the "New Page Item" command (kNewPageItemCmdBoss).
*/
class INewPageItemCmdData : public IPMUnknown {
public:
	enum {kDefaultIID = IID_INEWPAGEITEMCMDDATA};
	
	/** Type of graphic attributes to assign to new page items */
	enum GraphicAttrType
		{
		/** For special types of page items, don't copy any attributes (such as a standoff) */
		kNoGraphicAttributes		= 0,
		/** Copy the path item "defaults" to the new item */
		kDefaultGraphicAttributes,	
		/** A graphic frame which holds graphic items, use special graphic frame style */
		kGraphicFrameAttributes,
		/** A graphic frame which holds a text frame, use special text frame style */
		kTextFrameAttributes,
		/** A frame grid which is considered as a text frame plus frame grid attributes, use special frame grid style*/
		kFrameGridAttributes,
		/** A group page item that uses special graphic attributes (transparency only) */
		kGroupAttributes
		};

	/** What to do about applying object styles to the new page item */
	enum ObjectStyleApplication
		{
		/** Always apply the object style no matter what **/
		kAlwaysApplyObjectStyle,
		/**Never apply the object style no matter what **/
		kNeverApplyObjectStyle,
		/**Let the command decide whether to apply the object style or not **/
		kCommandAppliesObjectStyle
		};

	/** @name Set functions.

		Use the Set() function that corresponds to the data that you have to set. DB and ClassID are required
		Graphic attributes, parent and points are optional. Only those items that are set will be used in the
		new page item command.
	*/
	//@{
	virtual void Set(IDataBase*, const ClassID) = 0;
	virtual void Set(IDataBase*, const ClassID, const PMPointList& initialPoints) = 0;
	virtual void Set(IDataBase*, const ClassID, UID parent) = 0;
	virtual void Set(IDataBase*, const ClassID, UID parent, const PMPointList& initialPoints) = 0;

	virtual void Set(IDataBase*, const ClassID, GraphicAttrType) = 0;
	virtual void Set(IDataBase*, const ClassID, GraphicAttrType, const PMPointList& initialPoints) = 0;
	virtual void Set(IDataBase*, const ClassID, GraphicAttrType, UID parent) = 0;
	virtual void Set(IDataBase*, const ClassID, GraphicAttrType, UID parent, const PMPointList& initialPoints) = 0;
	//@}

	/** @name Get functions. 

		These return values established by the Set functions.
	*/
	//@{
	virtual IDataBase* 			GetDataBase () const = 0;
	virtual UID			 		GetParent() = 0;
	virtual ClassID 			GetItemClass() = 0;
	virtual const PMPointList& 	GetPointList() const = 0;
	virtual GraphicAttrType 	GetGraphicItemType() const = 0;
	//@}

	/** @name Other accessor functions */
	//@{

	/** Tells whether the command specified a parent.
		@return kTrue if a parent was specified.
	*/
	virtual bool16				AddToHierarchy () const = 0;

	/** Tells whether an initial point list was specified.
		@return kTrue if an initial point list was specified.
	*/
	virtual bool16				HasInitialPointList () const = 0;

	/** Tells whether a graphic attributes type was specified
		@return kTrue if a graphic attributes type was specified (other than kNoGraphicAttributes)
	*/
	virtual bool16				HasGraphicAttributes () const = 0;	

	/** Tells whether the item is a graphic frame with kGraphicFrameAttributes
		@return kTrue if the item is a graphic frame with kGraphicFrameAttributes.
	*/
	virtual bool16 				IsGraphicFrame() const = 0;	

	/** Specifies whether to allow a default standoff
		@param bAllowDefaultStandOff kTrue if using a default standoff
	*/
	virtual	void				SetAllowDefaultStandOff( bool16	bAllowDefaultStandOff ) = 0; 	// this flag is respected by StandOffNewPIResponder
	
	/** Tells whether a default standoff is allowed
		@return kTrue if a default standoff is allowed.
	*/
	virtual	bool16				AllowDefaultStandOff() const = 0; 								// this flag is respected by StandOffNewPIResponder
	//@}

	/** @name For internal use only
		These are used for copy/inflating page item surrogates -- see DocumentFramework::CopyandSwapSurrogateCmd for more info
		Don't use this if you don't know exactly what you're doing. Danger! Danger! Danger!
	*/
	//@{
	virtual UID					GetInternalPageItem() const = 0;
	virtual void				SetInternalPageItem(UID pgItem) = 0;
	//@}

	/** Sets/Gets the object style data
		@param/@return	howToApplyObjStyle	see @ObjectStyleApplication
	*/
	virtual void					SetObjectStyleApplication(ObjectStyleApplication howToApplyObjStyle) = 0;
	virtual ObjectStyleApplication	GetObjectStyleApplication() = 0;
};



#endif // __INewPageItemCmdData__
