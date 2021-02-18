//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportProvider.h $
//  
//  Owner: Zak Williamson
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
#ifndef __IImportProvider__
#define __IImportProvider__

#include "IPMUnknown.h"

#include "OpenPlaceID.h"
#include "PMString.h"
#include "PMFlavorTypes.h"

class ICommand;
class IFormatType;

/**
 IImportProvider is the main interface an import filter has to implement.
 Import filters provide import functionality from other formats to
 InDesign native formats.
 @see IImportManager
 */
class IImportProvider : public IPMUnknown
{
	public:
		/**
		 Returns the number of Mac file types supported by the import provider.
		 @return Number of Mac file types supported by the provider.
		 */
		virtual int32 CountFileTypes() = 0;

		/**
		 Returns the n'th Mac file type supported by the import provider.
		 @param n	IN Index of the Mac file type to return.
		 @return N'th Mac file type supported by the provider.
		 */
		virtual SysOSType GetFileType(int32 n) = 0;
		
		/**
		 For clipboard/drag and drop operations, returns the
		 internal flavor the import provider can operate on.
		 @return Internal flavor the provider can operate on.
		 */
		virtual PMFlavor GetInternalFlavor() = 0;

		/**
		 For clipboard/drag and drop operations, returns the number of
		 external flavors supported by the import provider.
		 @return Number of external flavors supported by the provider.
		 */
		virtual int32 CountExternalFlavors() = 0;

		/**
		 For clipboard/drag and drop operations, returns the n'th
		 external flavor supported by the import provider.
		 @param n	IN Index of the external flavor to return.
		 @return N'th external flavor supported by the provider.
		 */
		virtual ExternalPMFlavor GetExternalFlavor(int32 n) = 0;
		
		/**
		 Returns the number of file formats supported by the import provider. 
		 Examples of file format names are "TIFF" and "MS Word 97".
		 @return Number of file formats supported by the provider.
		 */
		virtual int32 CountFormats() = 0;

		/**
		 Returns the name (localized string) of the n'th file format
		 supported by the import provider.
		 @param formatIndex	IN Index of the format name to return.
		 @return Name of the n'th format supported by the provider.
		 */
		virtual PMString GetFormatName(int32 formatIndex) = 0;
		
		/**
		 Returns the number of extensions that correspond to the given file format
		 supported by the import provider. 
		 On the Mac, file extensions are only used for import provider selection
		 for files of type 'TEXT', '    ', 'BINA', or null. 
		 Examples of extensions are "DOC" and "TXT"; extensions do not include a preceeding period '.'.
		 @param formatIndex	IN Index of the format name whose n'th extension to return.
		 @return Number of extensions that correspond to the file format.
		 */
		virtual int32 CountExtensionsForFormat(int32 formatIndex) = 0;

		/**
		 Returns the n'th file extension that corresponds to the n'th file format
		 supported by the import provider.
		 @param formatIndex	IN Index of the file format whose n'th extension to return.
		 @param extensionIndex	IN Index of the extension to return.
		 @return The n'th extension that corresponds to the file format.
		 */
		virtual PMString GetExtensionForFormat(int32 formatIndex, int32 extensionIndex) = 0;
		
		/** Specifies importability */
		typedef enum { kCannotImport, kPartialImport, kFullImport } ImportAbility;

		/**
		 Returns whether the import provider can import data of the given format type.
		 @param formatType	IN Format type of the data to import.
		 @return kCannotImport: if the format type cannot be imported. 
				 kPartialImport: if the format type is of a common file type (i.e. TEXT on the Mac),
								 or if the filter cannot determine with a high degree of
								 certainty that the type is one it can support. 
				 kFullImport: if the filter can import the format type, and it is a
							  proprietary or otherwise uncommon type.

		 */
		virtual ImportAbility CanImportThisType(IFormatType *formatType) = 0;

		/**
		 Returns whether the import provider can import the data in the given stream.
		 @param stream	IN Data to import.
		 @return kCannotImport: if the data cannot be imported.
				 kPartialImport: if the data is of a common type (i.e. TEXT on the Mac),
								 or if the filter cannot determine with a high degree of certainty that
								 the data is of a type it can support.
				 kFullImport: if the filter can import the data, and it is of a
							  proprietary or otherwise uncommon type.

		 */
		virtual ImportAbility CanImportThisStream(IPMStream *stream) = 0;
		
		/**
		 Imports the the data in the given stream.
		 This method is the main entry point of the import provider. 
		 Note: If the import fails, the global error code must be set,
			   giving the reason why the import failed. To cancel an import,
			   set the global error code to kCancel.
		 @param db				IN Database where the objects are created.
		 @param stream			IN Data to import.
		 @param uiFlags			IN Flags denoting how to handle UI events. (see BaseType.h)
		 @param importedItem	OUT UIDRef of the newly created imported item.
									This may be a page item or a text story UID.
		 @param dataLink		IN When updating this will contain the original page item UID.
								   Providers should get their import preferences from this page item.
								   If the preferences are not available on this page item, use the
								   default preferences
		 @param asFormat		OUT Optional return parameter of the format just imported.
									This string is displayed in the link information dialog.
									If the string is not filled in, the method GetFormatName(0) is
									used to get the format name.
		 */
		virtual void ImportThis(IDataBase *db, IPMStream *stream, UIFlags uiFlags, UIDRef * importedItem, UIDRef * dataLink = nil, PMString * asFormat = nil) = 0;
};

#endif	//__IImportProvider__
