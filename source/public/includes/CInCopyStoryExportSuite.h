//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CInCopyStoryExportSuite.h $
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

#pragma once
#ifndef __CInCopyStoryExportSuite__
#define __CInCopyStoryExportSuite__

#include "CPMUnknown.h"
#include "CExportProvider.h"

class ITextModel;

//================================================================================================
//	CInCopyStoryExportSuite
//	
//	This class provides InCopy story specific export functionality.
//
//	This will do the majority of the work.  The only real thing the CSB Specific Implementations need to do is get the correct Stories to be exported.
//	NOTE: The selection architecture will not handle the layer export method.
//
//================================================================================================
class PUBLIC_DECL CInCopyStoryExportSuite : public CExportProvider
{
	public:

        //----------------------------------------------------------------------------------------
        //  Construction/Destruction
        //----------------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------------
		//  Constructor
        //----------------------------------------------------------------------------------------
		CInCopyStoryExportSuite(
			IPMUnknown* boss
			);

        //----------------------------------------------------------------------------------------
		//  Destructor
        //----------------------------------------------------------------------------------------
		~CInCopyStoryExportSuite();

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

        //----------------------------------------------------------------------------------------
		//  GetScriptIDForFormatName
        //----------------------------------------------------------------------------------------
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

	protected:

	// The only function that really needs to be overriden....
		virtual UIDList GetExportableItemList(
			IPMUnknown* targetboss
			) const;
	

	private:
	//----------------------------------------------------------------------------------------
	//  Private Member Functions
       //----------------------------------------------------------------------------------------

	typedef CExportProvider Inherited;
	
		void DoExportSequence( IPMUnknown* targetBoss, IPMStream* writeStream, const IDFile& sysFile, UIFlags uiFlags, const FileTypeInfoID& fileTypeID ) const;
	
		// export the given stories to the provided files using multiple threads.
		void DoMTExportInCopyStories(const UIDList& exportableList, const K2Vector<IDFile>& sysFiles, const FileTypeInfoID& fileTypeID, UIFlags uiFlags) const;
	
	/**
		Determine if a item (story or graphic) is locked or editable.
		@param sysFile IN. File of the exported InCopy story.
		@param itemRef IN. UIDRef of the item.
		@param isManaged OUT. Returns if file is managed.
		@return kTrue if item is locked.
	*/
		bool16 IsInCopyFileLocked( const IDFile& sysFile, const UIDRef& itemRef, UIFlags uiFlags, bool16& isManaged ) const;

	/**
		Determine if a incopy file is already in use.
		@param storyFile IN. File of the exported InCopy item.
		@return kTrue if item is already in use.
	*/
		bool16 IsItemInUse( const IDFile& sysFile, IDataBase *db, UIFlags uiFlags ) const;

		//----------------------------------------------------------------------------------------
        //  Private Data Members
        //----------------------------------------------------------------------------------------
		const ConstCString fInCopyInterchangeString;
		const ConstCString fInCopyMarkupString;

		mutable K2Vector<PMString> fListOfUsedFilenames;

};


#endif // __CInCopyStoryExportSuite__

