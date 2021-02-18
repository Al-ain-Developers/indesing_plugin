//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpSortTable.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ITableCommands.h"
#include "ITableModel.h"
#include "ITableTarget.h"
#include "ITableTextContainer.h"
#include "ITextModel.h"
#include "textiterator.h"

// General includes:
#include "K2TypeTraits.h"
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "Utils.h"
#include "WideString.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
 * 	\li	How to sort the body text in a table in different ways.
 * 
 * 	You first select if you want to sort a single body column in a table, or all columns in a table.
 *
 * 	Then you specify if you want to sort in ascending or descending order.
 * 
 * 	After that, you specify which column you want to sort by. This becomes the "key column" for 
 * 	the all-columns sorting operation, which means that if you sort all columns in a table, it is the order 
 * 	of the contents in this column that determine the row order of content in other columns.
 *
 *  For instance, say you have a table like this:
<pre>
| C | some data | some more data |
| Z | some other data | some more other data |
| A | some really different data | some more different data |
| B | some kind of data | some other kind of data |
</pre>
 * and you want to sort all columns.  If you set the "key column" to column 0 
 * and perform the sort, the end result is this:
<pre>
| A | some really different data | some more different data |
| B | some kind of data | some other kind of data |
| C | some data | some more data |
| Z | some other data | some more other data |
</pre>
 * Note that data in other columns move together by rows.
 * 
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_table
 */
class SnpSortTable 
{
public:
	/** Used to specify the type of sort. Whether to sort a single column,
		or to sort all the columns (with sort order determined by a 'key' column)
	*/
	enum eSortWhat 
	{
		/** For a single column sort. Content in other columns are not affected.  */
		eSortSingleColumn, 
		/** To specify that all the columns should be sorted but with one key column. 
		 * See comments for the SnpSortTable class about sorting with a key column. */
		eSortAllColumns
	};

	/** Constructor.
	 */
	SnpSortTable() : 	fTableModel(nil) {}

	/** Destructor.
	 */
	virtual ~SnpSortTable() { ReleaseTableModel(); }

	/** Sets the table model.
	 * 	This must be called before any of the other methods are called, so that
	 * 	the table model is set up properly.
	 * 	@param[in] iTableModel Table model to set.
	 */
	void SetTableModel(ITableModel* iTableModel);

	/** Releases the table model.
	 * 	This must be called after ALL of the other methods are called, so that
	 * 	the table model is cleaned up properly.
	 *  Doing this in the destructor of this class is too late, since
	 * 	the InDesign boss cleanup checks run before all global objects are
	 * 	deleted by the runtime engine. 
	 */
	void ReleaseTableModel(void);

	/** Performs a sort depending on the mode chosen.
		@param sortWhat
		@param isAscending
		@param keyColumn
	*/
	void ModalSort(SnpSortTable::eSortWhat sortWhat, 
				   bool16 isAscending, 
				   int32 keyColumn);

	/** Sort one column independently of the rest of the table.
		@param isAscending kTrue if the values should be sorted to ascending order, kFalse otherwise
		@param nCol identifies column to be sorted
	*/
	void SortSingleColumn(bool16 isAscending, 
						  const int32 nCol);

	/** Sort the whole table, with an order determined by that in the keyColumn.

		@param isAscending kTrue if the values should be sorted to ascending order, kFalse otherwise
		@param keyColumn specifies the column on whose ordering the whole table is sorted
		@precondition keyColumn in range of columns indicated by colRange
	*/
	void SortMultiColumns(bool16 isAscending, 
						  int32 keyColumn);

	/** Acquire the values in specified column.
		@param vec OUT parameter to hold the values from the given column
		@param nCol specifies colum of interest
	*/
	void GetValuesInColumn(K2Vector<WideString>& vec, 
						   const int32 nCol);

	/** Change the values in the specified column.
		@param[in] vec contains new values for the given column
		@param nCol specifies column of interest
	*/
	void SetValuesInColumn(const K2Vector<WideString>& vec, 
						   const int32 nCol);


	/** Acquire the values in specified row.
		@param vec OUT parameter which holds the values from the row given
		@param nRow specifies row of interest
	*/
	void GetValuesInRow(K2Vector<WideString>& vec, 
						const int32 nRow);

	/** Change the values in specified row.
		@param[in] vec contains the new text values for the row
		@param nRow specifies which row to change contents of
	*/
	void SetValuesInRow(const K2Vector<WideString>& vec, 
						const int32 nRow);

	/** Acquire the text content at specified \Ref{GridAddress}.
		@param gridAddress specifies which cell is being targeted
		@return text content at given address as \Ref{WideString} 
	*/
	WideString GetTextContent(const GridAddress& gridAddress);

	/** Change the text content at the given \Ref{GridAddress}.
		@param gridAddress specifies which cell is being targeted
		@param text specified new contents for given \Ref{GridAddress}
	*/
	void SetTextContent(const GridAddress& gridAddress, 
						const WideString& text);

	/** Data class that encapsulates a table row.
	 * 	@ingroup sdk_snippet
	 * 	@ingroup sdk_table
	*/
	class TblSortRowData 
	{
	public:
		typedef object_type data_type;
	
		/** Default constructor
		*/
		TblSortRowData(void);
	
		/** Constructor
		 * 	@param[in] rowData List of WideString objects for the row.
		 * 	@param[in] keyIndex Index of the item designated as the sort key.
		*/
		TblSortRowData(K2Vector<WideString>& rowData, int32 keyIndex); 
	
		/** Copy-constructor 
		 * 	@param[in] rhs Another TblSortRowData class.
		*/
		TblSortRowData(const TblSortRowData& rhs);
	
		/** Constructor when we have no data but want to reserve storage
		 * 	@param[in] reserveSize Reserves enough storage space for this number of items.
		*/
		TblSortRowData(int32 reserveSize);
	
		/** Destructor 
		*/
		virtual ~TblSortRowData(void);
	
		/** Operator less-than.
		 * 	@param[in] rhs Right-hand side argument to the less-than operator.
		 * 	@return true if predicate is true, false otherwise.
		 */
		bool operator < (const TblSortRowData& rhs) const;
	
		/** Operator assignment 
		 * 	@param[in] rhs Right-hand side argument to the assignment operator.
		 * 	@return Reference to this object.
		 */
		TblSortRowData& operator =(const TblSortRowData& rhs);
	
		/** Sets all row data.
		 * 	@param[in] rowData List of WideString objects for the row.
		 * 	@param[in] keyIndex Index of the item designated as the sort key.
		 */
		void SetAll(K2Vector<WideString>& rowData, int32 keyIndex);
	
		/** Returns the row data 
		 * 	@return K2Vector of WideString objects, containing row data.
		 */
		const K2Vector<WideString>& GetRowData(void);
	
		/**	Sets a specific data item in the row data. 
		 * 	@param[in] data The data to set.
		 * 	@param[in] index The index to set.
		*/
		void Set(const WideString& data, int32 index);
	
		/**	Sets the index for the sort key.
		 * 	@param[in] keyIndex The sort key index to set.
		*/
		void SetKey(int32 keyIndex);
	
		/** Returns the WideString data corresponding to the sort key.
		 * 	@return Returns WideString data of key.
		*/
		WideString GetKeyData(void) const;
	
		/** Returns the size of the row.
		 * 	@return Returns number of items in the row.
		*/
		int32 RowSize(void) const;
	
	private:
		/** Holds the row data itself */
		K2Vector<WideString> fRowData;
	
		/** Specifies which of the row-entries is really the key-column index */
		int32 fKeyIndex;
	};

	/**
		Provides a an operator () to allow a comparison function.
		Not strictly required here, but the operator () could do
		pretty much any sort of comparison. As it is the major
		part is carried out by the operator < defined on the \Ref{TblSortRowData} class. 
		@ingroup sdk_snippet
		@ingroup sdk_table
	*/
	class TblSortComparator_rows 
	{
	public:
		bool operator() (const SnpSortTable::TblSortRowData& w, const SnpSortTable::TblSortRowData& z) 
		{
			// Somewhat sterile as this could be done in the < operator implementation.
			// Just included here for illustration of how to use custom function object in std::sort
			bool16 sameColumnWidth = (w.RowSize() == z.RowSize());
			ASSERT(sameColumnWidth);
			if (sameColumnWidth)
			{
				return w  < (z);
			}
			return kFalse;
		}
	};

private:
	/** table model for this instance.
	 */
	ITableModel* fTableModel;

	/** 
		Check the class invariant. In this case, be sure that we have a valid table to sort.
	*/
	bool16 invariant(void);

	/**	Iterate over the columns in the table. When reading, collect the values into the vector
		@param vec OUT parameter when isReading = kTrue, IN parameter when isReading = kFalse. 
			Holds the input values for setting the text when isReading = kFalse. Holds the values
			read for the specified column when isReading = kTrue.
	*/
	void iterateTableColumns(K2Vector<WideString>& vec, const int32 nCol, bool16 isReading);

	/** Similar to \Ref{iterateTableColumns} but for rows.
	*/
	void iterateTableRows(K2Vector<WideString>& vec, const int32 nCol, bool16 isReading);


};




/* SetTableModel
*/
void SnpSortTable::SetTableModel(ITableModel* iTableModel)
{
	if (fTableModel == nil)
	{
		fTableModel = iTableModel;
		fTableModel->AddRef();
	}
	if (!invariant())
	{
		ASSERT(invariant());
	}
}

/* ReleaseTableModel
*/
void SnpSortTable::ReleaseTableModel(void)
{
	if (fTableModel != nil)
	{
		// Release the table model interface ptr.
		fTableModel->Release(); 
		fTableModel = nil;
	}
}

/* ModalSort
*/
void SnpSortTable::ModalSort(SnpSortTable::eSortWhat sortWhat, bool16 isAscending, int32 keyColumn)
{
	do 
	{
		if (!invariant())
		{
			ASSERT(invariant());
			break;
		}

		switch (sortWhat)
		{
		case SnpSortTable::eSortAllColumns:
			{
				// Include the whole range of columns in the table
				this->SortMultiColumns(isAscending, keyColumn); 
			} 
			break;

		case SnpSortTable::eSortSingleColumn:
			{
				// Will sort this column independently of all the others. The keyColumn in
				// this case is just specifying the column to sort (independently)
				this->SortSingleColumn(isAscending, keyColumn);
			}
			break;
		default:
			{
				// Unknown sort mode
				ASSERT_FAIL("Unknown sort mode");
			}
			break;
		}
	} while (kFalse);        
}

/* SortSingleColumn
*/
void SnpSortTable::SortSingleColumn(bool16 isAscending, const int32 nCol)
{
	do
	{
		ASSERT(invariant());
		if (!invariant())
		{
			break;
		}
		K2Vector<WideString> vec;
		this->GetValuesInColumn(vec, nCol);

		std::sort(vec.begin(), vec.end());
		if (!isAscending)
		{
			std::reverse(vec.begin(), vec.end());
		}

		this->SetValuesInColumn(vec, nCol);

	} while (kFalse);
}

/* SortMultiColumns
*/
void SnpSortTable::SortMultiColumns(bool16 isAscending, int32 keyColumn)
{
	do 
	{
		if (!invariant())
		{
			ASSERT(invariant());
			break;
		}

		K2Vector<SnpSortTable::TblSortRowData> vec;
		RowRange rowRange = fTableModel->GetBodyRows();
		int32 startRow = rowRange.start;

		// Collect the body data in the table by row
		// NOTE: This code only sorts body data. 
		// To get the header and footer rows, call 
		// ITableModel::GetHeaderRows() and ITableModelGetFooterRows().
		for (int32 i = startRow; i < rowRange.End(); i++)
		{
			K2Vector<WideString> currRow;
			this->GetValuesInRow(currRow, i);
			SnpSortTable::TblSortRowData tblRowData(currRow, keyColumn);
			vec.push_back(tblRowData);
		}

		// Order the rows by the order specified in the 'key' column once sorted
		std::sort(vec.begin(), vec.end(), TblSortComparator_rows());
		if (!isAscending)
		{
			std::reverse(vec.begin(), vec.end());
		}
		K2Vector<SnpSortTable::TblSortRowData>::const_iterator iterRows(vec.begin());
		K2Vector<SnpSortTable::TblSortRowData>::const_iterator end(vec.end());

		int atRow = rowRange.start;

		// Repopulate the table with the correctly ordered values.
		// Results will be undefined where table isn't rectangular (i.e. if there are 
		// split or merged cells.
		// A smarter implementation would check before getting this far...
		while (iterRows != end && 
			   atRow < rowRange.End())
		{
			SnpSortTable::TblSortRowData rowData = (*iterRows);
			this->SetValuesInRow(rowData.GetRowData(), atRow++);
			++iterRows;
		}
	} while (kFalse);
}

/* GetValuesInRow
*/
void SnpSortTable::GetValuesInRow(K2Vector<WideString>& vec, const int32 nRow)
{
	this->iterateTableRows(vec, nRow, kTrue);
}

/* SetValuesInRow
*/
void SnpSortTable::SetValuesInRow(const K2Vector<WideString>& vec, const int32 nCol)
{
	this->iterateTableRows(const_cast< K2Vector<WideString>& > (vec), nCol, kFalse);
}

/* GetValuesInColumn
*/
void SnpSortTable::GetValuesInColumn(K2Vector<WideString>& vec, const int32 nCol)
{
	this->iterateTableColumns(vec, nCol, kTrue);
}

/* SetValuesInColumn
*/
void SnpSortTable::SetValuesInColumn(const K2Vector<WideString>& vec, const int32 nCol)
{
	this->iterateTableColumns(const_cast< K2Vector<WideString>& > (vec), nCol, kFalse);
}

/* GetTextContent
*/
WideString SnpSortTable::GetTextContent(const GridAddress& gridAddress)
{
	WideString retval;
	do 
	{
		if (!invariant())
		{
			ASSERT(invariant());
			break;
		}
		bool16 isValidAddress = fTableModel->IsValid(gridAddress);

		if (!isValidAddress)
		{
			ASSERT(isValidAddress);
			break;
		}
		// Find the text model that contains this table
		InterfacePtr<ITableTextContainer> iTableTextContainer(fTableModel, UseDefaultIID());
		ASSERT(iTableTextContainer);
		if (iTableTextContainer==nil)
		{
			break;
		}

		InterfacePtr<ITextModel> iTextModel(iTableTextContainer->QueryTextModel());
		ASSERT(iTextModel);
		if (iTextModel == nil)
		{
			break;
		}

		const GridID gridID = fTableModel->GetGridID(gridAddress);
		// This relies on the knowledge that the gridID is 
		// the key (unique only within a table) used to identify threads
		// within the thread dictionary for an individual table
		const UIDRef tableRef(::GetUIDRef(fTableModel));
		TextIndex threadStart, threadLength;
		bool16 didFindThread = iTextModel->FindStoryThread(tableRef.GetUID(), gridID, &threadStart, &threadLength);
		ASSERT(didFindThread);
		if (!didFindThread)
		{
			break;
		}

		bool16 validStart = (threadStart >= 0 && 
							 threadStart <= iTextModel->TotalLength());
		bool16 validLength = (threadLength >= 0 && 
							  threadLength <= iTextModel->TotalLength());
		if (!validStart || !validLength)
		{
			ASSERT_FAIL("Invalid thread params");
			break;
		}
		TextIterator beginTextChunk(iTextModel, threadStart);
		TextIterator endTextChunk(iTextModel, threadStart + threadLength - 1);
		// The -1 is to drop the last CR that's in the text model for each cell
		// retval.reserve(threadLength);
		// Watson #1140943 
		// reserve no longer functional now strings do copy-on-write
		std::copy(beginTextChunk, endTextChunk, std::back_inserter(retval));
	} while (kFalse);
	return retval;
}

/* SetTextContent
*/
void SnpSortTable::SetTextContent(const GridAddress& gridAddress, const WideString& text)
{
	do
	{
		if (!invariant())
		{
			ASSERT(invariant());
			break;
		}
		bool16 isValidAddress = fTableModel->IsValid(gridAddress);
		if (!isValidAddress)
		{
			ASSERT(isValidAddress);
			break;
		}

		InterfacePtr<ITableCommands> tableCommands(fTableModel, UseDefaultIID());
		if (tableCommands == nil)
		{
			ASSERT(tableCommands);
			break;
		}

		ErrorCode retval = tableCommands->SetCellText(text, gridAddress);
		ASSERT(retval == kSuccess);
	} while (kFalse);
}

/* iterateTableRows
*/
void SnpSortTable::iterateTableRows(K2Vector<WideString>& vec, const int32 nRow, bool16 isReading)
{
	do
	{
		if (!invariant())
		{
			ASSERT(invariant());
			break;
		}
		// ITableModel::begin(void) gets the total range - 
		// so restrict to body area
		const GridArea bodyArea = fTableModel->GetBodyArea();
		ITableModel::const_iterator iterTableRows(fTableModel->begin(bodyArea));
		ITableModel::const_iterator endTable(fTableModel->end(bodyArea));
		K2Vector<WideString>::const_iterator iterVec(vec.begin());
		K2Vector<WideString>::const_iterator endVec(vec.end());
		while (iterTableRows != endTable)
		{
			GridAddress gridAddress = (*iterTableRows);         
			if (gridAddress.row == nRow)
			{
				if (isReading)
				{
					vec.push_back(this->GetTextContent(gridAddress));
				}
				else
				{
					ASSERT(iterVec != endVec);
					if (iterVec == endVec)
					{
						break; // out of inner while loop
					}
					this->SetTextContent(gridAddress, *iterVec);
					++iterVec;
				}
			}
			++iterTableRows;
		}   
	} while (kFalse);
}


/* iterateTableColumns
*/
void SnpSortTable::iterateTableColumns(K2Vector<WideString>& vec, const int32 nCol, bool16 isReading)
{
	do
	{
		if (!invariant())
		{
			ASSERT(invariant());
			break;
		}
		const GridArea bodyArea = fTableModel->GetBodyArea();
		ITableModel::const_iterator iterTableCols(fTableModel->begin(bodyArea));
		ITableModel::const_iterator endTable(fTableModel->end(bodyArea));
		K2Vector<WideString>::const_iterator iterVec(vec.begin());
		K2Vector<WideString>::const_iterator endVec(vec.end());
		while (iterTableCols != endTable)
		{
			GridAddress gridAddress = (*iterTableCols);
			if (gridAddress.col == nCol)
			{
				if (isReading)
				{
					vec.push_back(this->GetTextContent(gridAddress));
				}
				else
				{
					ASSERT(iterVec != endVec);
					if (iterVec == endVec)
					{
						break; // out of inner while loop
					}
					this->SetTextContent(gridAddress, *iterVec);
					++iterVec;
				}
			}
			++iterTableCols;
		}   
	} while (kFalse);
}

/* invariant
*/
bool16 SnpSortTable::invariant()
{
	return (fTableModel != nil);
}

// --- SnpSortTable::TblSortRowData ---
/* No argument constructor
*/   
SnpSortTable::TblSortRowData::TblSortRowData(void) 
{
	fKeyIndex = 0; 
	// fRowData.reserve(8); // Arbitrary expectation of 8 columns
	// Watson #1140943 
	// reserve no longer functional now strings do copy-on-write
}

/* Constructor
*/
SnpSortTable::TblSortRowData::TblSortRowData(K2Vector<WideString>& rowData, int32 keyIndex) 
{
	this->SetAll(rowData, keyIndex);
}

/* Constructor
*/
SnpSortTable::TblSortRowData::TblSortRowData(const TblSortRowData& rhs) 
{
	fRowData = rhs.fRowData; 
	fKeyIndex = rhs.fKeyIndex; 
}

/* Constructor
*/
//SnpSortTable::TblSortRowData::TblSortRowData(int32 reserveSize) 
//{
//	fKeyIndex = 0; 
//	fRowData.reserve(reserveSize); 
//}

/* Destructor
*/
SnpSortTable::TblSortRowData::~TblSortRowData(void)	
{
	fRowData.clear();
}

/* Operator assignment
*/
SnpSortTable::TblSortRowData& SnpSortTable::TblSortRowData::operator = (const TblSortRowData& rhs)
{
	this->fKeyIndex = rhs.fKeyIndex;
	this->fRowData = rhs.fRowData;
	return *this;
}


/* Operator less-than
*/
bool SnpSortTable::TblSortRowData::operator < (const TblSortRowData& rhs) const 
{
	WideString w = this->GetKeyData();
	WideString z = rhs.GetKeyData();

	// Check to see if this is a number, and do a numeric comparison iff
	// we can convert both strings without an error
	PMString w_pm;
	w.GetSystemString(&w_pm);

	PMString z_pm;
	z.GetSystemString(&z_pm);

	PMString::ConversionError err1, err2; 
	PMReal w_r = w_pm.GetAsDouble(&err1);   
	PMReal z_r = z_pm.GetAsDouble(&err2);

	if (err1 == PMString::kNoError && 
		err2 == PMString::kNoError)
	{
		// If both strings can be converted successfully to real numbers
		// then perform the comparison on the reals
		return w_r < z_r;
	}
	// else default to the regular string comparison
	return w < z;
}


/* SetAll
*/
void SnpSortTable::TblSortRowData::SetAll(K2Vector<WideString>& rowData, int32 keyIndex) 
{
	fRowData = rowData; 
	fKeyIndex = keyIndex;
	ASSERT(fKeyIndex >= 0 && fKeyIndex < fRowData.size());
}

/* GetRowData
*/
const K2Vector<WideString>& SnpSortTable::TblSortRowData::GetRowData(void) 
{
	return fRowData; 
}

/* Set
*/
void SnpSortTable::TblSortRowData::Set(const WideString& data, int32 index) 
{
	ASSERT(index >= 0 && index < fRowData.size());
	fRowData[index]=data;
}

/* SetKey 
*/
void SnpSortTable::TblSortRowData::SetKey(int32 keyIndex) 
{
	ASSERT(keyIndex >= 0 && keyIndex < fRowData.size());
	fKeyIndex = keyIndex;
}

/* GetKeyData
*/
WideString SnpSortTable::TblSortRowData::GetKeyData(void) const 
{
	ASSERT(fKeyIndex >= 0 && fKeyIndex < fRowData.size());
	return fRowData[fKeyIndex]; 
}

/* RowSize
*/
int32 SnpSortTable::TblSortRowData::RowSize(void) const
{
	return fRowData.size();
}



// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerSortTable : public SnpRunnable
{


public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerSortTable(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerSortTable(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTableTargetContext;}
};


/* Constructor.
*/
_SnpRunnerSortTable::_SnpRunnerSortTable() : SnpRunnable("SortTable")
{
	this->SetDescription("Sorts a table under the current selection.");
	this->SetPreconditions("A table must be selelcted");
	this->SetCategories("sdk_snippet, sdk_table");

}

/* Destructor.
*/
_SnpRunnerSortTable::~_SnpRunnerSortTable()	
{

}

/* Check if your preconditions are met.
*/
bool16  _SnpRunnerSortTable::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do 
	{
		// if we can get a table model, we can run this snippet.
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
		if (tableTarget == nil)
		{
			break;
		}

		InterfacePtr<ITableModel> tableModel(tableTarget->QueryModel());
		if (tableModel == nil)
		{
			break;
		}

		result = kTrue;
	} while (false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerSortTable::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do
	{
		SnpSortTable instance;
		ASSERT(runnableContext);
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
		if (tableTarget == nil)
		{
			SNIPLOG("You must have a table selection. Please try again.");
			break;
		}

		InterfacePtr<ITableModel> tableModel(tableTarget->QueryModel());
		if (tableModel == nil)
		{
			SNIPLOG("You must have a table selection. Please try again.");
			break;
		}
		// set the table model
		instance.SetTableModel(tableModel);


		/* get parameters */

		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.clear();
		choices.push_back("Single column"); 
		choices.push_back("All columns");
		SnpSortTable::eSortWhat sortWhat = (SnpSortTable::eSortWhat)parameterUtils->GetChoice("What do you want to sort?", choices);
		if (parameterUtils->WasDialogCancelled())
		{
			status = kCancel;
			break;
		}

		K2Vector<PMString> trueFalseChoices;
		trueFalseChoices.clear();
		trueFalseChoices.push_back("No");	// kFalse == 0
		trueFalseChoices.push_back("Yes");	// kTrue == 1

		bool16 isAscending = (bool16)parameterUtils->GetChoice("Do you want to sort ascending?", trueFalseChoices, kTrue);
		if (parameterUtils->WasDialogCancelled())
		{
			status = kCancel;
			break;
		}

		ColRange columns = tableModel->GetBodyArea().GetCols();
		int32 numColumns = columns.count;
		int32 firstColumn = columns.start;
        int32 keyColumn = parameterUtils->GetInt32("Which column do you want to sort by?", 
												   firstColumn, 
												   firstColumn, 
												   firstColumn + numColumns - 1);
		if (parameterUtils->WasDialogCancelled())
		{
			status = kCancel;
			break;
		}

		// perform the sort.
		instance.ModalSort(sortWhat, isAscending, keyColumn);
		status = kSuccess;


	} while (false);
	return(status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerSortTable instance_SnpRunnerSortTable;
DEFINE_SNIPPET(_SnpRunnerSortTable) 	

// End, SnpSortTable.cpp

