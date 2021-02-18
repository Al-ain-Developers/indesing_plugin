//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CusCondTxtPrintSetupProvider.cpp $
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

//Interface includes:
#include "IPrintData.h"
#include "IActiveContext.h"

// General includes:
#include "CPrintSetupProvider.h"

// Project includes:
#include "CusCondTxtID.h"
#include "CusCondTxtFacade.h"

/**	Provides a mechanism to selectively enter into the print process.

	@ingroup customconditionaltext
*/
class CusCondTxtPrintSetupProvider : public CPrintSetupProvider
{
public:
	/** Constructor
	 */
	CusCondTxtPrintSetupProvider(IPMUnknown* boss);

	/** Destructor
	 */
	~CusCondTxtPrintSetupProvider();

	/**	Called before PrintGatherCmd.
	 @param bReturn (in/out) specifies whether to process PrintGatherCmd.
	 @param iPrintData (in) specifies IPrintData containing all print settings used.
	 @param iOutputPages (in) specifies IOutputPages containing which pages to gather info for. 
	 */
	virtual void BeforePrintGatherCmd(bool16& bReturn, 
									  IPrintData* iPrintData, 
									  IOutputPages* iOutputPages);
	/**	Called to end printing.
	 */
	virtual void EndPrint(void);

	DECLARE_HELPER_METHODS()

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class to its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusCondTxtPrintSetupProvider, kCusCondTxtPrintSetupProviderImpl)
												 
DEFINE_HELPER_METHODS(CusCondTxtPrintSetupProvider)


/* Constructor
*/
CusCondTxtPrintSetupProvider::CusCondTxtPrintSetupProvider(IPMUnknown* boss)
:   HELPER_METHODS_INIT(boss)
{
}


/* Destructor
*/
CusCondTxtPrintSetupProvider::~CusCondTxtPrintSetupProvider()
{
}

/* BeforePrintGatherCmd
 */
void CusCondTxtPrintSetupProvider::BeforePrintGatherCmd(bool16& bReturn, 
														IPrintData* iPrintData, 
														IOutputPages* iOutputPages)
{
	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		IDocument* idoc = context->GetContextDocument();
		if(idoc)
			Utils<ICusCondTxtFacade>()->TurnOffConditionVisibility(idoc, CusCondTxtFacade::kPrintVisibility);
	}
}

/* EndPrint
*/
void CusCondTxtPrintSetupProvider::EndPrint(void)
{
	IActiveContext* context = GetExecutionContextSession()->GetActiveContext();
	if (context)
	{
		IDocument* idoc = context->GetContextDocument();
		if(idoc)
			Utils<ICusCondTxtFacade>()->TurnOnConditionVisibility(idoc);
	}
}

// End, CusCondTxtPrintSetupProvider.cpp