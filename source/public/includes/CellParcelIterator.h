//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CellParcelIterator.h $
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
#ifndef __CellParcelIterator__
#define __CellParcelIterator__

#include <iterator>
#include <functional>
#include "TableTypes.h"
#include "K2Iterator.h"
#include "ITableLayout.h"

template <class Structure>
class CellParcelIterator
{
public:
	typedef CellParcelAddr			value_type;
	typedef std::ptrdiff_t			difference_type;
	typedef const CellParcelAddr*   pointer;
	typedef const CellParcelAddr& 	reference;

	typedef std::bidirectional_iterator_tag	iterator_category;

						CellParcelIterator(const Structure* structure,
											bool16 begin);
						CellParcelIterator(const CellParcelIterator& rhs);
						~CellParcelIterator();

	const CellParcelAddr&	operator * () const;
	const CellParcelAddr*	operator -> () const;

	CellParcelIterator&		operator ++ ();
	CellParcelIterator		operator ++ (int);
	CellParcelIterator&		operator= (const CellParcelIterator& rhs);

	CellParcelIterator&		operator -- ();
	CellParcelIterator		operator -- (int);

	bool16				operator ==(const CellParcelIterator& rhs) const;
	bool16				operator != (const CellParcelIterator& rhs) const;

private:
	void					SetupCurrent();

	ITableLayout::row_iterator		fBeginRowIter;
	ITableLayout::row_iterator		fEndRowIter;
	ITableLayout::row_iterator		fRowIter;
	int32							fParcelColIndex;
	CellParcelAddr					fCurrent;

#ifdef DEBUG
	const Structure*				fTableFrame;	// no reference held
#endif
};

#endif //__CellParcelIterator__
