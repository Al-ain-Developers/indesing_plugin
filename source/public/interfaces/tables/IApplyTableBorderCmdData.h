//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/IApplyTableBorderCmdData.h $
//  
//  Owner: Danielle Bessette
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
#ifndef __IApplyTableBorderCmdData__
#define __IApplyTableBorderCmdData__

#include "IPMUnknown.h"
#include "TablesUIID.h"

class AttributeBossList;

/**	IApplyTableBorderCmdData is the primary data interface for the command to apply a table border to a table
	@ingroup table_ui
*/class IApplyTableBorderCmdData : public IPMUnknown
{
public:		
	enum	{ kDefaultIID = IID_IAPPLYTABLEBORDERCMDDATA };

	/** Set the data about what to apply: 
		@param attrs The attributes being applied to the table border (color, weight, stroke type, tint, overprint)
	*/
	virtual void SetApplyAttrList(const AttributeBossList& attrs) = 0;

	/** Set the data about what to apply to the left side of the board: 
		@param attrs The attributes being applied (color, weight, stroke type, tint, overprint)
	*/
	virtual void SetLeftList(const AttributeBossList& attrs) = 0;

	/** Set the data about what to apply to the top side of the board: 
		@param attrs The attributes being applied (color, weight, stroke type, tint, overprint)
	*/
	virtual void SetTopList(const AttributeBossList& attrs) = 0;

	/** Set the data about what to apply to the right side of the board: 
		@param attrs The attributes being applied (color, weight, stroke type, tint, overprint)
	*/
	virtual void SetRightList(const AttributeBossList& attrs) = 0;

	/** Set the data about what to apply to the bottom side of the board: 
		@param attrs The attributes being applied (color, weight, stroke type, tint, overprint)
	*/
	virtual void SetBottomList(const AttributeBossList& attrs) = 0;
	

	/** Get the data to apply to the table border: 
		@return AttributeBossList& The attributes being applied to the table border (color, weight, stroke type, tint, overprint)
	*/
	virtual const AttributeBossList& GetApplyAttrList(void) const= 0;	

	/** Get the data to apply to the left side of the table border: 
		@return AttributeBossList& The attributes being applied (color, weight, stroke type, tint, overprint)
	*/
	virtual const AttributeBossList& GetLeftList(void) const= 0;	

	/** Get the data to apply to the top side of the table border: 
		@return AttributeBossList& The attributes being applied (color, weight, stroke type, tint, overprint)
	*/
	virtual const AttributeBossList& GetTopList(void) const= 0;	

	/** Get the data to apply to the right side of the table border: 
		@return AttributeBossList& The attributes being applied (color, weight, stroke type, tint, overprint)
	*/
	virtual const AttributeBossList& GetRightList(void) const= 0;	

	/** Get the data to apply to the bottom side of the table border: 
		@return AttributeBossList& The attributes being applied (color, weight, stroke type, tint, overprint)
	*/
	virtual const AttributeBossList& GetBottomList(void) const= 0;	

	/** Duplicates the object passed in
		@param other* The one to duplicate
	*/
	virtual void	Duplicate(IApplyTableBorderCmdData* other) = 0;


};

#endif
