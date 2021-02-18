//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMasterSpread.h $
//  
//  Owner: Brendan O'Shea
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
//  NOT FINISHED YET - MANY MORE ATTRIBUTES TO BE ADDED ****
//  
//========================================================================================

#pragma once
#ifndef __IMASTERSPREAD__
#define __IMASTERSPREAD__

#include "IPMUnknown.h"
#include "MasterPageID.h"
#include "PMRect.h"
#include "PMPoint.h"
#include "PMMatrix.h"

class PMString;
class IHierarchy;

/**
	IMasterSpread persists the name of a master and contains the incremental information (beyond what is already
	contained in a spread) that defines a master spread. This interface exists on spreads which
	happen to be master spreads (kMasterPagesBoss), and does not exist on spreads which are not masters (regular kSpreadBoss).
	The document has an IMasterSpreadList which is a list of the document's IMasterSpreads.

	@ingroup layout_spread
	@see kDocBoss
	@see kMasterPagesBoss
	@see kSpreadBoss
	@see ISpread

 */
class IMasterSpread : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IMASTERSPREAD };

	/**
		GetName - Get the name of the master spread
			the name is the combination of the
			prefix and the base name (separated by a '-')
			e.g. for the first/default master the base name will
			be 'Master', the prefix will be 'A', and the name returned
			by GetName will be 'A-Master'

		@param	OUT pName - name of this master
	*/
	virtual void GetName(PMString *pName) const = 0;

	/**
		SetBasename - Set the base name of this master spread

		@param	IN newBasename
	*/
	virtual void SetBasename(const PMString& newBasename) = 0;

	/**
		GetBasename - Get the base name of this master spread

		@param OUT pBasename
	*/
	virtual void GetBasename(PMString *pBasename) const = 0;


	/**
		SetPrefix - Set the prefix associated with this master spread

		@param IN newPrefix
	*/
	virtual void SetPrefix(const PMString& newPrefix) = 0;

	/**
		GetPrefix - Get the prefix associated with this master spread

		@param OUT pPrefix
	*/
	virtual void GetPrefix(PMString *pPrefix) const = 0;

	/**
		GetCurrentLayoutSpreadUID - Get the spread that is being drawn (i.e. the UID of
			the layout spread to which the master spread is applied).
			WARNING: This is *ONLY* valid while in the middle of drawing

		@return	UID&
	*/
	virtual UID GetCurrentLayoutSpreadUID() const = 0;

	/**
		SetCurrentLayoutSpreadUID - Set the spread that is being drawn (i.e. the UID of
			the layout spread to which the master spread is applied).
			Do NOT call this -- it is called by the
			drawing code.

		@param	newSpread
	*/
	virtual void SetCurrentLayoutSpreadUID(const UID &newSpread) = 0;

	/**
		GetCurrentSpreadOffset - Get the offset that has been applied to the view in
		order to draw the page.
			WARNING: This is *ONLY* valid while in the middle of drawing

		@return	PMPoint&
	*/
	virtual const PMMatrix& GetCurrentSpreadOffset() const = 0;

	/**
		SetCurrentSpreadOffset - Set the offset that has been applied to the view in
			order to draw the page and the current page that is drawing.
			Do NOT call this -- it is called by the drawing code.
		@param currentPage
		@param	offset
	*/
	virtual void SetCurrentSpreadOffset(const PMMatrix &offset, UID currentPage) = 0;

	/**
		GetDrawingPageUID - Get the page that is currently being drawn.
			WARNING: This is *ONLY* valid while in the middle of drawing
	*/
	virtual UID GetTopLevelPageUID() const = 0;
};

#endif
