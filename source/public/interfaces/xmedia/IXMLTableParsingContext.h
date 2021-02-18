//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLTableParsingContext.h $
//  
//  Owner: Lonnie Millett
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
//  An interface for keeping track of the table specific parsing information when importing
//  XML content.
//  
//========================================================================================

#pragma once
#ifndef __IXMLTableParsingContext_h__
#define __IXMLTableParsingContext_h__

#include "IPMUnknown.h"
#include "TableTypes.h"
#include "XMLID.h"

/**
Interface for tracking table specific parsing context information when importing XML content.

This interface is an addin to the kXMLParserLocatorBoss.
*/
class IXMLTableParsingContext : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXMLTABLEPARSINGCONTEXT };
		
	    /**
	    Specify the context information by copying another context.

	    @param tableContext	The table context to be copied.
	    */
		virtual void Set(IXMLTableParsingContext* tableContext) = 0;

	    /**
	    Reset the table context to its intial state.
	    */
		virtual void Reset() = 0;

		/** Returns the newly created table */
		virtual UIDRef GetTableRef() const = 0;
		
		/** Set the reference to the newly created table.
		
	    @param tableRef	A reference to a table object.
	    */
		virtual void SetTableRef(const UIDRef& tableRef) = 0;
		
		/** Returns the range of total rows that we have parsed so far. */
		virtual RowRange GetTotalRows() const = 0;

		/** Set the number of total rows that have been parsed.
		
	    @param start	The starting row number (zero based)
	    @param count	The count of rows from the start
	    */
		virtual void SetTotalRows(int32 start, int32 count) = 0;
		
		/** Returns the range of header rows that we have parsed so far. */
		virtual RowRange GetHeaderRows() const = 0;

		/** Set the number of header rows that have been parsed.
		
	    @param start	The starting row number (zero based)
	    @param count	The count of rows from the start
	    */
		virtual void SetHeaderRows(int32 start, int32 count) = 0;
		
		/** Returns the number of footer rows that we have parsed so far. */
		virtual RowRange GetFooterRows() const = 0;
		
		/** Set the number of footer rows that have been parsed.
		
	    @param start	The starting row number (zero based)
	    @param count	The count of rows from the start
	    */
		virtual void SetFooterRows(int32 start, int32 count) = 0;
	
		/** Returns the number of columns that we have parsed so far. */
		virtual GridCoord GetNumOfCols() const = 0;

		/** Set the number of columns that have been parsed.
		
	    @param numOfCols	The number of columns that have been parsed.
	    */
		virtual void SetNumOfCols(GridCoord numOfCols) = 0;
		
		/** Returns the maximum number of columns that have been added to any row. */
		virtual GridCoord GetMaxNumOfCols() const = 0;

		/** Set the maximum number of columns that have been added to any row in the table.
		
	    @param maxNumOfCols	The maximum number of columns.
	    */
		virtual void SetMaxNumOfCols(GridCoord maxNumOfCols) = 0;

		/** Returns kTrue if we are between table tags. */
		virtual bool16 InTable() const = 0;

		/** Specify whether we are between table tags or not.
		
	    @param inTable	kTrue if we are between table tags.
	    */
		virtual void SetInTable(bool16 inTable) = 0;
		
		/** Returns kTrue if we are between thead tags. */
		virtual bool16 InHeader() const = 0;
		
		/** Specify whether we are between thead tags or not.
		
	    @param inHeader	kTrue if we are between thead tags.
	    */
		virtual void SetInHeader(bool16 inHeader) = 0;
		
		/** Returns kTrue if we are between tbody tags. */
		virtual bool16 InBody() const = 0;
		
		/** Specify whether we are between tbody tags or not.
		
	    @param inBody	kTrue if we are between tbody tags.
	    */
		virtual void SetInBody(bool16 inBody) = 0;
		
		/** Returns kTrue if we are between tfoot tags. */
		virtual bool16 InFooter() const = 0;
		
		/** Specify whether we are between tfoot tags or not.
		
	    @param inFooter	kTrue if we are between tfoot tags.
	    */
		virtual void SetInFooter(bool16 inFooter) = 0;
	
		/** Returns kTrue if we are between row tags. */
		virtual bool16 InRow() const = 0;

		/** Specify whether we are between row tags or not.
		
	    @param inRow	kTrue if we are between row tags.
	    */
		virtual void SetInRow(bool16 inRow) = 0;

		/** Returns kTrue if we are between column tags. */
		virtual bool16 InCell() const = 0;

		/** Specify whether we are between column tags or not.
		
	    @param inCell	kTrue if we are between column tags.
	    */
		virtual void SetInCell(bool16 inCell) = 0;

		/** Returns the insertion position that was current before any table parsing occurred. */
		virtual TextIndex GetInsertPos() const = 0;

		/** Specify the insertion position at the beginning of table parsing.
		
	    @param insertPos	The insertion position.
	    */
		virtual void SetInsertPos(TextIndex insertPos) = 0;
		
		/** Returns kTrue if InTable, InRow, and InCell are true.  This is a more strigent test of table location.*/
		virtual bool16 InTableCell() const = 0;
};

#endif