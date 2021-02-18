//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexport/export/InCopyStoryExportSuiteASB.cpp $
//  
//  Owner: Ben Park
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
#include "HelperInterface.h"

// ----- Interfaces -----
#include "CExportProvider.h" // Parent

// ----- Includes -----

#include "CPMUnknown.h"
#include "SelectionASBTemplates.tpp" // For CallEach

// ----- Utility files -----

// ----- ID.h files -----

#include "InCopyExportID.h"
#include "InCopyWorkflowID.h"

//================================================================================================
//	InCopyStoryExportSuiteASB
//	
//	This class provides InCopy story specific export functionality.
//
//	All this does is call through to the CSB methods.
//
//================================================================================================
class InCopyStoryExportSuiteASB : public CExportProvider
{
	typedef CExportProvider Inherited;

	public:

        //----------------------------------------------------------------------------------------
        //  Construction/Destruction
        //----------------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------------
		//  Constructor
        //----------------------------------------------------------------------------------------
		InCopyStoryExportSuiteASB(
			IPMUnknown* boss
			);

        //----------------------------------------------------------------------------------------
		//  Destructor
        //----------------------------------------------------------------------------------------
		~InCopyStoryExportSuiteASB();

        //----------------------------------------------------------------------------------------
        //  Public Member Functions
        //----------------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------------
		//  CanExportToFile
		//
		//	Always return kTrue
        //----------------------------------------------------------------------------------------
		virtual bool16 CanExportToFile() const
		{
			return kTrue;
		}

        //----------------------------------------------------------------------------------------
		//  CanExportThisFormat
		//
		//	Returns false for exporting the design format to fool the Export dialog into NOT 
		//	displaying InCopy design documents as an export type. 
		//	Users of the InCopyStoryExportProvider will need to assume that the provider can export 
		//	the design if they can acquire the format name "InCopy Design".
		//
        //----------------------------------------------------------------------------------------
		virtual bool16 CanExportThisFormat(
			IDocument* doc,
			IPMUnknown* targetboss,
			const PMString& formatName
			);

        //----------------------------------------------------------------------------------------
		//  GetNthFormatName
        //----------------------------------------------------------------------------------------
		virtual PMString GetNthFormatName(
			int32 n
			);

        //----------------------------------------------------------------------------------------
		//  CountFormats
        //----------------------------------------------------------------------------------------
		virtual int32 CountFormats() 
		{ return 2L; }

        //----------------------------------------------------------------------------------------
		//  GetExtensionForFormatName
        //----------------------------------------------------------------------------------------
		virtual PMString GetExtensionForFormatName(
			const PMString& formatName
			);

		virtual ScriptID GetScriptIDForFormatName(const PMString& formatName, const ScriptInfo::RequestContext& context) ;

		//----------------------------------------------------------------------------------------
		// Export the current selection to a file using the given filename. Generate the specified file
		// format. The calling code verifies that the file does not exist. Note: Some export providers
		// may display UI and may export more than just the current selection (i.e. PDF export, EPS export, etc.)
        //----------------------------------------------------------------------------------------
		virtual void ExportToFile(
			const IDFile& sysFile, 
			IDocument* doc,
			IPMUnknown* targetboss, 
			const PMString& formatName, 
			UIFlags uiFlags = kFullUI
			);

        //----------------------------------------------------------------------------------------
		// Export the current selection to a stream. Note: Some export providers may display UI
		// and may export more than just the current selection (i.e. PDF export, EPS export, etc.)
        //----------------------------------------------------------------------------------------
		virtual void ExportToStream(
			IPMStream* stream, 
			IDocument* doc,
			IPMUnknown* targetboss, 
			const PMString& formatName, 
			UIFlags uiFlags = kFullUI
			);

		// --- Clipboard/DragDrop Export:
	
		// The provider indicates whether it can do normal filebased exports.
		virtual bool16 CanExportForExternalize() const
		{ return kFalse; }

		// For Clip/Drag operations, what internal flavor does this exporter operate on?
		virtual PMFlavor GetInternalFlavor() const
		{ return kNoFlavor; }
		
		// For Clip/Drag operations, what external flavors can this exporter produce?
		virtual int32 CountExternalFlavors() const
		{ return 0; }

		virtual ExternalPMFlavor GetExternalFlavor(
			int32 n
			) const
		{ return kNoExternalFlavor; }

		// For Clip/Drag operations, what format type, if any, would be used to produce the desired external flavor?
		virtual bool16 CanExportThisFlavor(
			const ExternalPMFlavor& flavor, 
			PMString& outFormatName
			) const
		{ return kFalse; }
			
		// Externalize the given data to a stream.
		virtual ErrorCode ExportForExternalize(
			IDataExchangeHandler *handler, 
			const ExternalPMFlavor toWhichFlavor, 
			IPMStream* stream
			)
		{ return kFailure; }

	//----------------------------------------------------------------------------------------
        //  Private Data Members
        //----------------------------------------------------------------------------------------

};

CREATE_PMINTERFACE(InCopyStoryExportSuiteASB, kICExportSuiteASBImpl)


//================================================================================================
//  Constructor
//================================================================================================
InCopyStoryExportSuiteASB::InCopyStoryExportSuiteASB( IPMUnknown* boss ) :
	Inherited(boss)
{
}

//================================================================================================
//  Destructor
//================================================================================================
InCopyStoryExportSuiteASB::~InCopyStoryExportSuiteASB()
{
}


//================================================================================================
bool16 InCopyStoryExportSuiteASB::CanExportThisFormat(
	IDocument* doc,
	IPMUnknown* targetboss, 
	const PMString& formatName
	)
{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (IID_IINCOPYEXPORTSUITE));
	bool16 returnValue = kFalse;

	if (selectionSuites->size () == 1) // For the time being, we don't want to support multiple CSB's.  Might change in the future...
	{

		IExportProvider*  exportProvider = (IExportProvider*) ((*selectionSuites)[0].get());
		returnValue = exportProvider->CanExportThisFormat (doc, targetboss, formatName);   
	}

	return (returnValue);
}

//================================================================================================
PMString InCopyStoryExportSuiteASB::GetNthFormatName(
	int32 ndx
	)
{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (IID_IINCOPYEXPORTSUITE));
	PMString returnValue;

	if (selectionSuites->size () == 1) // For the time being, we don't want to support multiple CSB's.  Might change in the future...
	{
		IExportProvider*  exportProvider = (IExportProvider*) ((*selectionSuites)[0].get());
		returnValue = exportProvider->GetNthFormatName (ndx);   
	}

	return (returnValue);
}

//================================================================================================
PMString InCopyStoryExportSuiteASB::GetExtensionForFormatName(
	const PMString& formatName
	)
{	
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (IID_IINCOPYEXPORTSUITE));
	PMString returnValue;

	if (selectionSuites->size () == 1) // For the time being, we don't want to support multiple CSB's.  Might change in the future...
	{
		IExportProvider*  exportProvider = (IExportProvider*) ((*selectionSuites)[0].get());
		returnValue = exportProvider->GetExtensionForFormatName (formatName);   
	}

	return (returnValue);
}

ScriptID InCopyStoryExportSuiteASB::GetScriptIDForFormatName(const PMString& formatName, const ScriptInfo::RequestContext& context)
{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (IID_IINCOPYEXPORTSUITE));
	ScriptID returnValue;

	if (selectionSuites->size () == 1) // For the time being, we don't want to support multiple CSB's.  Might change in the future...
	{
		IExportProvider*  exportProvider = (IExportProvider*) ((*selectionSuites)[0].get());
		returnValue = exportProvider->GetScriptIDForFormatName (formatName, context);   
	}

	return (returnValue);
}

//================================================================================================
//	ExportToFile
//================================================================================================
void InCopyStoryExportSuiteASB::ExportToFile(
	const IDFile& sysFile, 
	IDocument* doc,
	IPMUnknown* targetboss,
	const PMString& formatName, 
	UIFlags uiFlags // = kFullUI
	)
{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (IID_IINCOPYEXPORTSUITE));

	if (selectionSuites->size () == 1) // For the time being, we don't want to support multiple CSB's.  Might change in the future...
	{

		IExportProvider*  exportProvider = (IExportProvider*) ((*selectionSuites)[0].get());
		exportProvider->ExportToFile (sysFile, doc, targetboss, formatName, uiFlags);   
	}
}

//================================================================================================
//	ExportToStream
//================================================================================================
void InCopyStoryExportSuiteASB::ExportToStream(
	IPMStream* stream, 
	IDocument* doc,
	IPMUnknown* targetboss,
	const PMString& formatName, 
	UIFlags uiFlags // = kFullUI
	)
{
	InterfacePtr<const IIntegratorTarget> 			iIntegratorTarget (this, UseDefaultIID ());
	std::auto_ptr<IIntegratorTarget::TargetSuiteCollection> selectionSuites (iIntegratorTarget->GetTarget (IID_IINCOPYEXPORTSUITE));

	if (selectionSuites->size () == 1) // For the time being, we don't want to support multiple CSB's.  Might change in the future...
	{

		IExportProvider*  exportProvider = (IExportProvider*) ((*selectionSuites)[0].get());
		exportProvider->ExportToStream (stream, doc, targetboss, formatName, uiFlags);   
	}
}

