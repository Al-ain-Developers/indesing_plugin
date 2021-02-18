//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelData.cpp $
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

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "IPrnSelData.h"
#include "PrnSelID.h"


/** Stores non-persistent data used to print selection only.
  
	
	@ingroup printselection
*/

class PrnSelData : public CPMUnknown<IPrnSelData>
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PrnSelData(IPMUnknown*  boss);

	/** Destructor.
	*/
	virtual ~PrnSelData();

	/** Sets whether print selection checkbox was checked.
		@param bChecked Specifies whether print selection checkbox was checked.
	*/
	virtual void SetIsChecked(bool16 bChecked);

	/** Retrieves whether print selection checkbox was checked.
		@return	Returns whether print selection checkbox was checked.
	*/
	virtual bool16 GetIsChecked() { return fPrnSel; }

	/** Sets whether should suppress print selection dialog. Used by scripting.
		@param bSuppress Specifies whether should suppress print selection dialog.
	*/
	virtual void SetSuppressPrintSelectionDialog(bool16 bSuppress);

	/** Retrieves whether should suppress print selection dialog.
		@return	Returns whether should suppress print selection dialog.
	*/
	virtual bool16 GetSuppressPrintSelectionDialog() { return fSuppressPrintSelectionDialog; }

	/** Retrieves whether a page contained a selected item.
		@param	pageuid [in] specifies page uid being queried.
		@return	Returns whether specified page UID represents a page containing a selected item.
	*/
	virtual bool16 GetPageUIDHadSelection(UID pageuid);

	/** Loads page UID into custom data structure.
		@param	pageuid [in] specifies page UID being loaded.
	*/
	virtual void LoadPageUID(UID pageuid);

	/** Retrieves whether a specified UID represents a selected page item.
		@param	uid [in] specifies uid being queried.
		@return	Returns whether specified UID represents a selected page item.
	*/
	virtual bool16 GetPageItemUIDHadSelection(UID uid);

	/** Loads page item UID into a custom data structure.
		@param	uid [in] Specifies uid being loaded.
	*/
	virtual void LoadPageItemUID(UID uid);

	/** Empties custom data structures.
	*/
	virtual void FlushUIDs();

private:
	/** kTrue means print selection only */
	bool16  fPrnSel;
	/** kTrue means not bring up print selection dialog */
	bool16  fSuppressPrintSelectionDialog;

	/** contains UIDs representing selected pages*/
	K2Vector<UID> fPageUIDList;

	/** contains UIDs representing selected page items*/
	K2Vector<UID> fPageItemUIDList;
};


/* CREATE_PERSIST_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelData, kPrnSelDataImpl)


/* Constructor
*/
PrnSelData::PrnSelData(IPMUnknown* boss) : 
	CPMUnknown<IPrnSelData>(boss), fPrnSel(kFalse), fSuppressPrintSelectionDialog(kFalse)
{
}


/* Destructor */
PrnSelData::~PrnSelData()
{
}


/* SetIsChecked */
void PrnSelData::SetIsChecked(bool16 bChecked)
{
	fPrnSel = bChecked;
}

/* SetSuppressPrintSelectionDialog */
void PrnSelData::SetSuppressPrintSelectionDialog(bool16 bSuppress)
{
	fSuppressPrintSelectionDialog = bSuppress;
}


/* GetPageUIDHadSelection */
bool16 PrnSelData::GetPageUIDHadSelection(UID pageuid)
{
	K2Vector<UID>::const_iterator iter = std::find(fPageUIDList.begin(), fPageUIDList.end(), pageuid);
	return (iter != fPageUIDList.end());
}


/* LoadPageUID */
void PrnSelData::LoadPageUID(UID pageuid)
{
	fPageUIDList.push_back(pageuid);
}


/* GetPageItemUIDHadSelection */
bool16 PrnSelData::GetPageItemUIDHadSelection(UID uid)
{
	K2Vector<UID>::const_iterator iter = std::find(fPageItemUIDList.begin(), fPageItemUIDList.end(), uid);
	return (iter != fPageItemUIDList.end());
}


/* LoadPageItemUID */
void PrnSelData::LoadPageItemUID(UID uid)
{
	fPageItemUIDList.push_back(uid);
}


/* FlushUIDs */
void PrnSelData::FlushUIDs()
{
	fPageUIDList.clear();
	fPageItemUIDList.clear();
}

// End, PrnSelData.cpp.
