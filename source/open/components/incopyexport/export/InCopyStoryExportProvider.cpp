//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyexport/export/InCopyStoryExportProvider.cpp $
//  
//  Owner: craig rainwater
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

#include "CExportProvider.h"
// ----- Interfaces -----

#include "ISelectionUtils.h"
#include "ISelectionManager.h"

// ----- Includes -----

#include "CPMUnknown.h"
#include "InCopyImportExportDefs.h"
#include "FileTypeRegistry.h"

// ----- Utility files -----

// ----- ID.h files -----

#include "InCopyExportID.h"
#include "InCopyWorkflowID.h"

//================================================================================================
//	InCopyStoryExportProvider
//	
//	This class provides InCopy story specific export functionality.
//
//================================================================================================
class InCopyStoryExportProvider : public CExportProvider
{
	typedef CExportProvider Inherited;

	public:

        //----------------------------------------------------------------------------------------
        //  Construction/Destruction
        //----------------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------------
		//  Constructor
        //----------------------------------------------------------------------------------------
		InCopyStoryExportProvider(
			IPMUnknown* boss
			);

        //----------------------------------------------------------------------------------------
		//  Destructor
        //----------------------------------------------------------------------------------------
		~InCopyStoryExportProvider();

        //----------------------------------------------------------------------------------------
        //  Public Member Functions
        //----------------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------------
		//  CanExportToFile
		//
		//	Always return kTrue
        //----------------------------------------------------------------------------------------
		virtual bool16 CanExportToFile() const;

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
		virtual int32 CountFormats();

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
		virtual bool16 CanExportForExternalize() const;

		// For Clip/Drag operations, what internal flavor does this exporter operate on?
		virtual PMFlavor GetInternalFlavor() const;
		
		// For Clip/Drag operations, what external flavors can this exporter produce?
		virtual int32 CountExternalFlavors() const;

		virtual ExternalPMFlavor GetExternalFlavor(
			int32 n
			) const;

		// For Clip/Drag operations, what format type, if any, would be used to produce the desired external flavor?
		virtual bool16 CanExportThisFlavor(
			const ExternalPMFlavor& flavor, 
			PMString& outFormatName
			) const;
			
		// Externalize the given data to a stream.
		virtual ErrorCode ExportForExternalize(
			IDataExchangeHandler *handler, 
			const ExternalPMFlavor toWhichFlavor, 
			IPMStream* stream
			);

	private:
		const ConstCString fInCopyInterchangeString;
		const ConstCString fInCopyMarkupString;

};

CREATE_PMINTERFACE(InCopyStoryExportProvider, kInCopyStoryExportProviderImpl)

//================================================================================================
// CLASS InCopyStoryExportProvider
//================================================================================================


//================================================================================================
//  Constructor
//================================================================================================
InCopyStoryExportProvider::InCopyStoryExportProvider(
	IPMUnknown* boss
	) :
	Inherited(boss),
	fInCopyInterchangeString( InCopy::kInCopyInterchangeFormatName ),
	fInCopyMarkupString( InCopy::kInCopyMarkupFormatName )
{
}

//================================================================================================
//  Destructor
//================================================================================================
InCopyStoryExportProvider::~InCopyStoryExportProvider()
{
}


//================================================================================================
bool16 InCopyStoryExportProvider::CanExportThisFormat(
	IDocument* doc,
	IPMUnknown* targetboss, 
	const PMString& formatName
	)
{
	InterfacePtr<IExportProvider> inCopyExportProvider (targetboss, IID_IINCOPYEXPORTSUITE);
	if (inCopyExportProvider)
	{
		return inCopyExportProvider->CanExportThisFormat(doc, targetboss, formatName);
	}

	return kFalse;
}

//================================================================================================
PMString InCopyStoryExportProvider::GetNthFormatName(
	int32 ndx
	)
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->GetNthFormatName(ndx);
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	ASSERT_MSG(ndx == 0 || ndx == 1, "InCopyStoryExportProvider::GetNthFormatName - index out of range");

	return (ndx == 0 ? fInCopyInterchangeString : fInCopyMarkupString) ;
}

//================================================================================================
int32 InCopyStoryExportProvider::CountFormats() 
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->CountFormats();
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	return 2L;	/* InCopyInterchange and InCopyMarkup */
}


//================================================================================================
PMString InCopyStoryExportProvider::GetExtensionForFormatName(
	const PMString& formatName
	)
{	
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->GetExtensionForFormatName(formatName);
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	if (formatName == fInCopyInterchangeString)
	{
		PMString string(FileTypeRegistry::GetCurrentFileExtension(kInCopyXMLInterchangeFileTypeInfoID));
		return string;
	}

	if (formatName == fInCopyMarkupString)
	{
		PMString string(FileTypeRegistry::GetCurrentFileExtension(kInCopyXMLMarkupFileTypeInfoID));
		return string;
	}

	return PMString ("");
}

ScriptID InCopyStoryExportProvider::GetScriptIDForFormatName(const PMString& formatName, const ScriptInfo::RequestContext& context)
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->GetScriptIDForFormatName(formatName, context);
	}

	if ( context.GetVersion() < ScriptInfo::kCS4ScriptVersion)
	{
		if (formatName == fInCopyInterchangeString)
		{
			if ( context.GetVersion() < ScriptInfo::kCS3ScriptVersion )
				return en_InCopyInterchange ;
			else
				return en_InCopyDocument ;
		}
	}
	else
	{
		if (formatName == fInCopyInterchangeString)
			return en_InCopyDocument ;
		else if (formatName == fInCopyMarkupString)
			return en_InCopyMarkup ;			
	}

	return kInvalidScriptID ;
}

//================================================================================================
//	ExportToFile
//================================================================================================
void InCopyStoryExportProvider::ExportToFile(
	const IDFile& sysFile, 
	IDocument* doc,
	IPMUnknown* targetBoss,
	const PMString& formatName, 
	UIFlags uiFlags // = kFullUI
	)
{
	InterfacePtr<IExportProvider> inCopyExportProvider (targetBoss, IID_IINCOPYEXPORTSUITE);
	if (inCopyExportProvider)
	{
		inCopyExportProvider->ExportToFile(sysFile, doc, targetBoss, formatName, uiFlags);
	}
}

//================================================================================================
//	ExportToStream
//================================================================================================
void InCopyStoryExportProvider::ExportToStream(
	IPMStream* stream, 
	IDocument* doc,
	IPMUnknown* targetBoss,
	const PMString& formatName, 
	UIFlags uiFlags // = kFullUI
	)
{
	InterfacePtr<IExportProvider> inCopyExportProvider (targetBoss, IID_IINCOPYEXPORTSUITE);
	if (inCopyExportProvider)
	{
		inCopyExportProvider->ExportToStream(stream, doc, targetBoss, formatName, uiFlags);
	}

}

//---------------------------------------------------------------
// InCopyStoryExportProvider::CanExportToFile
//---------------------------------------------------------------

bool16 InCopyStoryExportProvider::CanExportToFile() const
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->CanExportToFile();
	}
	
	// if we get this far, there is no selection manager (e.g. bishop)
	return kTrue;
}


//================================================================================================
bool16 InCopyStoryExportProvider::CanExportForExternalize() const
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->CanExportForExternalize();
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	return kFalse;
}

//================================================================================================
PMFlavor InCopyStoryExportProvider::GetInternalFlavor() const
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->GetInternalFlavor();
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	return kNoFlavor;
}
		
//================================================================================================
int32 InCopyStoryExportProvider::CountExternalFlavors() const
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->CountExternalFlavors();
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	return 0;
}

//================================================================================================
ExternalPMFlavor InCopyStoryExportProvider::GetExternalFlavor(int32 n) const
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->GetExternalFlavor(n);
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	return kNoExternalFlavor;
}

//================================================================================================
bool16 InCopyStoryExportProvider::CanExportThisFlavor(const ExternalPMFlavor& flavor, PMString& outFormatName) const
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->CanExportThisFlavor(flavor, outFormatName);
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	return kFalse;
}
			
		// Externalize the given data to a stream.
ErrorCode InCopyStoryExportProvider::ExportForExternalize(
			IDataExchangeHandler *handler, 
			const ExternalPMFlavor toWhichFlavor, 
			IPMStream* stream
			)
{
	InterfacePtr<ISelectionManager> selMgr (Utils<ISelectionUtils>()->QueryActiveSelection());
	InterfacePtr<IExportProvider> inCopyExportProvider (selMgr, IID_IINCOPYEXPORTSUITE);

	if (inCopyExportProvider)
	{
		return inCopyExportProvider->ExportForExternalize(handler, toWhichFlavor, stream);
	}

	// if we get this far, there is no selection manager (e.g. bishop)
	return kFailure;
}
