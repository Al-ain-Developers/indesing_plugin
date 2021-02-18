//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITablePageItemContent.h $
//  
//  Owner: Rahul Jain
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  ___________________
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2014 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================


#pragma once
#ifndef _ITABLEPAGEITEMCONTENT_
#define _ITABLEPAGEITEMCONTENT_

#include "TableTypes.h"

/**
 * Access the objects placed in graphic cells of table
 */


class ITablePageItemContent : public IPMUnknown {

public:
	///	kDefaultIID
	enum  { kDefaultIID = IID_ITABLEPAGEITEMCONTENT };

	/**
		Get the object placed in graphic cell
		@param	cell	The grid address of the cell to query
		@return UIDRef	UIDRef of object placed in the cell, if it is a graphic cell, otherwise an invalid UID will be returned
	*/
	virtual UIDRef		GetCellGraphicContent(const GridAddress& cell) = 0;
	
	/**
	Get the objects placed in graphic cells
	@param	area	area of cells to query
	@return UIDList	List of UIDRef of all objects placed in the graphic cells of the specified area. 
			If there are other type of cells in the area, they'll be ignored
	*/
	virtual UIDList		GetCellsGraphicContentList(const GridArea& area) = 0;
};

#endif // _ITABLEPAGEITEMCONTENT_