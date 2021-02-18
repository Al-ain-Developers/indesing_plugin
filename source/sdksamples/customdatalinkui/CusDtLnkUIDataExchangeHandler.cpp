//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalinkui/CusDtLnkUIDataExchangeHandler.cpp $
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
#include "IStringData.h"
/*#include "IDataExchangeHandler.h"
#include "ICommand.h"
#include "IDocument.h"
#include "INewPageItemCmdData.h"
#include "IPMDataObject.h"
#include "IPageItemScrapData.h"
#include "IPageItemLayerData.h"
*/
// General includes:
/*#include "PMPoint.h"
#include "UIDList.h"
#include "CActionComponent.h"
#include "CAlert.h"
#include "CmdUtils.h"
#include "PageItemScrapID.h"*/
#include "CDataExchangeHandlerFor.h"

// Project includes:
#include "CusDtLnkUIID.h"


/** @ingroup customdatalinkui
	
*/
class CusDtLnkUIDataExchangeHandler : public CDataExchangeHandlerFor
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkUIDataExchangeHandler(IPMUnknown* boss) : CDataExchangeHandlerFor(boss) {}
	/**
		Destructor.
	*/
	virtual	~CusDtLnkUIDataExchangeHandler() {}

	/**
		creates storage for the scrap.
	*/
	virtual void CreateScrapStorage();

	/**
		indicates the type of object this data exchange handler can deal with.
		@return the flavor supported by the handler
	*/
	virtual	PMFlavor GetFlavor() const { return kCusDtLnkUIDragDropCustomFlavor; }


	/**
	*/
	virtual void				Clear();
	/**
		@return kTrue if  empty, kFalse otherwise.
	*/
	virtual bool16			IsEmpty() const;
			
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CusDtLnkUIDataExchangeHandler, kCusDtLnkUIDataExchangeHandlerImpl)

/*
*/
void  CusDtLnkUIDataExchangeHandler::CreateScrapStorage()
{
	// Not implemented
}


/*
*/
void  CusDtLnkUIDataExchangeHandler::Clear()
{
	do {

		InterfacePtr<IStringData> 
			uniqueKeyStrungData(this, IID_ICUSDTLNKUIUNIQUEKEYSTRINGDATA);
		ASSERT(uniqueKeyStrungData);
		if (!uniqueKeyStrungData) {
			break;
		}
		PMString emptyString("");
		uniqueKeyStrungData->Set(emptyString);
	} while(kFalse);

}

/*
*/
bool16  CusDtLnkUIDataExchangeHandler::IsEmpty() const
{
	bool16 retval = kTrue;
	do {

		InterfacePtr<IStringData> 
			uniqueKeyStrungData(this, IID_ICUSDTLNKUIUNIQUEKEYSTRINGDATA);
		ASSERT(uniqueKeyStrungData);
		if (!uniqueKeyStrungData) {
			break;
		}
		retval = uniqueKeyStrungData->GetString().empty();
	} while(kFalse);
	return retval;
}

