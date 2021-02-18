//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFFormXObjectData.h $
//  
//  Owner: DBerggren
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

#ifndef __IPDFFormXObjectData__
#define __IPDFFormXObjectData__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "KeyValuePair.h"
#include "PDFID.h"

#define FormID uint32

/** Data to be used to create Form XObject constructs when exporting to PDF.
	There are two lists maintained, a Forms List and a Pages List. The Forms list contains
	consecutive UIDs in the draw order (i.e. use IterateDrawOrder to
	initialize the lists). The Form is uniquely identified by a FormID.
	The Pages list is a list of pages in which the forms are used. The forms used
	on a page are identified by their FormID. 
*/
class IPDFFormXObjectData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPDFFORMXOBJECTDATA } ;

	typedef KeyValuePair< FormID, K2Vector< UID > > Forms;
	typedef KeyValuePair< int32, K2Vector< FormID > > Pages;

	typedef K2Vector< Forms > FormList;
	typedef K2Vector< Pages > PageList;

	/** Copy all the information from the given interface into this interface.
		@param otherData IN the data which to copy from.
	*/
	virtual void CopyData(IPDFFormXObjectData const* otherData) = 0;

	/** Set the information regarding the repeatability of the static data. For example, for 
		data merge, if merging a single record per page, the number of definition pages will be
		the number of pages in the pub, the total number of pages will be the number of pages in 
		the pub times the number of records. Since the forms are page based, it may be necessary 
		to suppress the form on the final page.
		@param numberDefinitionPages IN number of pages defining the static and variable parts.
					For example, if doing multiple records per page, this would be set to 1. If
					doing a single record per page, it would be the number of pages in the pub.
		@param totalNumberPages IN the total number of pages being output.
		@param bSuppressOnLastPage IN whether to suppress the form on the last page or not. This
					is necessary if doing multiple records per page, yet the last page lacks 
					enough record data to be completely filled out.
	*/
	virtual void SetRepeatInfo(int32 numberDefinitionPages, int32 totalNumberPages, bool16 bSuppressOnLastPage) = 0;

	/** Get the number of definition pages. This should be greater than or equal to the largest 
		page number defined in the page list. For multiple records per page, this will be 1. For
		single record per page, this will be the number of pages in the pub.
		@return int32 the number of definition pages.
	*/
	virtual int32 GetNumberDefinitionPages() const = 0;

	/** Get the total number of pages being exported. For multiple records per page, this should be
		the number of records divided by the number of records per page. For single records per page
		this will be then number of pages in the pub times the number of records.
		@return int32 the total number of pages being output.
	*/
	virtual int32 GetTotalNumberPages() const = 0;

	/** Determine whether the Form XObject should be suppressed for the last page. This situation
		will occur if the form is defined for multiple records per page, but there is not an even
		number of records to fill out the form on the last page.
		@return bool16 kTrue if the form should be suppressed on the last page, kFalse otherwise.
	*/
	virtual bool16 GetSuppressFormOnLastPage() const = 0;

	/** Add a vector of UIDs to the Form list for the given form ID. The UIDs are
		consecutively drawn page items that make up a static portion of the page.
		The list of UIDs will be used to determine the bounding box for the Form XObject.
		Also, the first UID in the list will be used to determine when the form starts.
		@param formID IN a unique form ID to which to list refers.
		@param uidList IN the vector of UIDs which represent the static page items.
	*/
	virtual void AddToFormList(FormID formID, K2Vector<UID> uidList) = 0;

	/** Add a vector of form IDs to the Page list for the given page number. The form IDs are
		all the forms that are drawn on that given page.
		@param pageNum IN the page number (zero based) which to list refers.
		@param formIDList IN the vector of FormIDs which are used on the page.
	*/
	virtual void AddToPageList(int32 pageNum, K2Vector<FormID> formIDList) = 0;

	/** Remove a vector of UIDs from the Form list for the given form ID. 
		@param formID IN which vector to remove.
	*/
	virtual void RemoveFromFormList(FormID formID) = 0;

	/** Remove a vector of FormIDs from the Page list for the given page number. 
		@param pageNum IN which vector to remove.
	*/
	virtual void RemoveFromPageList(int32 pageNum) = 0;

	/** Remove (clear) all the vectors of UIDs from the Form list. 
	*/
	virtual void ClearFormList() = 0;

	/** Remove (clear) all the vectors of FormIDs from the Page list. 
	*/
	virtual void ClearPageList() = 0;

	/** Retrieve the vector of UID for the given form ID from the Form list. The UIDs are 
		the page items that will be drawn into a Form XObject PDF construct.
		@param formID IN which vector to retrieve.
		@return K2Vector of UIDs representing consecutively drawn page items that make up the form.
	*/
	virtual K2Vector<UID> GetPageItemUIDsForFormID(FormID id) const = 0;

	/** Retrieve the vector of FormIDs for the given page number. These are the forms that
		are defined and used for the given page.
		@param pageNum IN which page to retrieve.
		@return K2Vector of FormIDs that are used on the page.
	*/
	virtual K2Vector<FormID> GetFormIDsForPageNum(int32 pageNum) const = 0;

	/** Retrieve the Form list. This is a vector of key/value pairs which are the unique FormIDs (key),
		and a vector of the page items (value) that will be drawn into a Form XObject PDF construct.
		@return FormList which is a vector of Forms key/value pairs.
	*/
	virtual FormList GetFormList() const = 0;

	/** Retrieve the Page list. This is a vector of key/value pairs which are page numbers (key) and
		a vector of FormIDs (value) that are used on the page.
		@return PageList which is a vector of Pages key/value pairs.
	*/
	virtual PageList GetPageList() const = 0;
};

#endif // __IPDFFormXObjectData__

