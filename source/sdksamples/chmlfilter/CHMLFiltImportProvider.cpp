//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltImportProvider.cpp $
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

// Interfaces includes
#include "IFileStreamData.h"
#include "IFormatType.h"
#include "IImportProvider.h"
#include "ITextModel.h"
#include "IPageList.h"

// General includes
#include "CAlert.h"
#include "CPMUnknown.h"
#include "LocaleSetting.h"
#include "WideString.h"
#include "PMRect.h"
#include "SDKDef.h"
#include "SDKFileHelper.h"
#include "SDKLayoutHelper.h"
#include "CHMLFiltTextHelper.h"

// Project includes
#include "CHMLFiltID.h"
#include "CHMLFiltTokenisor.h"
#include "CHMLFiltHelper.h"

/** Implements IImportProvider, contains the actual import filter (open provider) code. 
	ImportThis creates the document.

	The private method HandleDocLevelTags() handles the creation of page items 
	(text boxes and images), and the private method HandleParaLevelTags() 
	manages the application of styles and attributes to text.
	Also, this import provider is made to tie into the File &gt;&gt; Open 
	dialog by using the <B>kOpenServiceImpl</B> implementation 
	in the kCHMLFiltImportProviderBoss.
	
	
	@ingroup chmlfilter

 */
class CHMLFiltImportProvider : public CPMUnknown<IImportProvider>
{
public:
	/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CHMLFiltImportProvider(IPMUnknown* boss);

	/** Get the number of filetypes supported by the import provider. 
		(File types are Mac-specific.)
		@return count of file types supported
	*/
	virtual int32 CountFileTypes(void);

	/** Get the Nth filetype supported by the import provider. 
		@param n IN the index of interest.  
		@precondition n must be greater than 0, less than CountFileTypes().
		@return The Nth filetype requested
	*/
    virtual SysOSType GetFileType(int32 n);
	
	/** Get the number of file formats supported by the import provider.
		An example file format name would be "TIFF" or "MS Word 97".
	*/	
	virtual int32 CountFormats(void);

	/** Get the Nth file format supported by the import provider.
	
		@param formatIndex IN The index.  
		@precondition formatIndex Must be greater than 0, less than CountFormats().
		@return The  format name at specified index, as a PMString.
	*/	
	virtual PMString GetFormatName(int32 formatIndex);
	
	/** Get the number of extensions that correspond to each file 
		format supported by the import provider.  
		An example extension would be "DOC" or "TXT".  On the Mac,
		file extensions are only used for import provider selection
		for file of type 'TEXT', '    ', 'BINA', or null.
		Note the file extensions do not include a preceeding period '.'
		
		@param formatIndex IN 
		@precondition formatIndex Must be between 0 and CountFormats().
		@return The number of extensions supported by this import provider.
	*/
    virtual int32 CountExtensionsForFormat(int32 formatIndex);
	
	/** Get the Nth extension that corresponds to the provided format (index).
		@param formatIndex Must be between 0 and CountFormats().
		@param extensionIndex Must be between 0 and CountExtensionsForFormat().
		@return The extension for the specified format.
	*/
	virtual PMString GetExtensionForFormat(int32 formatIndex, int32 extensionIndex);

	/**	Indicates whether the import provider can import the given file type (Mac only).
		There are three possible results - 
		\li IImportProvider::kFullImport: The filter can import this format.
		\li IImportProvider::kPartialImport: The filter can import this file, but there may be a 
			better match, only use this filter if no other returns kFullImport
		\li IImportProvider::kCannotImport: This filter does not import this format.
		
		@param formatType IN The format type to test.
		@return Whether or not this import provider could import this type. 
	*/
	virtual ImportAbility CanImportThisType(IFormatType* formatType);
	
	/**	Indicates whether the import provider can import the given stream.
		In this method, we also check for the file extension, and on the Macintosh, 
		we check for the file type as well.
		There are three possible results:
		\li IImportProvider::kFullImport: The filter can import this format.
		\li IImportProvider::kPartialImport: The filter can import this file, but there may be a 
			better match, only use this filter if no other returns kFullImport
		\li IImportProvider::kCannotImport: This filter does not import this format.
		
		@param stream IN The stream to test.
		@return Whether or not this import provider could import this stream. 
	*/
	virtual ImportAbility CanImportThisStream(IPMStream* stream);

	/** This method is the main entry point of the import provider and does most of the work.
		This is where the CHML file is imported. It is responsible for creating the document, setting
	    up the new document's command processor and calling the method to import the tagged text.
		If the import fails, the global error code must be set, giving the reason why the import failed.
		To cancel an import, set the global error code to kCancel.
		Please note that the typographer's quotation marks will NOT be modified in this plug-in. 
		
		@param db	The database where the objects are created.
		@param stream	The data to be imported.
		@param uiFlags	Flags to indicate whether the import provider to display or suppress it's user interface
		@param pDataLinkUIDRef	Optional. When updating this will contain the original page item UID.  Providers should get their
						import preferences from this page item.  If the preferences are not available on this
						page item, use the default preferences.
		@param asFormat	Optional. Return parameter of the format just imported.  This string is displayed in the
						link information dialog. If the string is not filled in, the method GetFormatName(0) is
						used to get the format name.
		@param importedItem	Returns a UIDRef of the newly created imported item.  This may be a page item or a text story UID.
	*/
	virtual void ImportThis(IDataBase* db, IPMStream* stream, UIFlags uiFlags, UIDRef* importedItem, UIDRef* pDataLinkUIDRef = nil, PMString* asFormat = nil);

	/** Gets internal flavor supported by import provider. 
		(Flavors are used by clipboard/drag and drop)
		@return internal flavor supported
	*/
	virtual PMFlavor GetInternalFlavor(void);

	/** Gets the number of external flavors supported by import provider. 
		(Flavors are used by clipboard/drag and drop)
		@return count of external flavors supported
	*/
	virtual int32 CountExternalFlavors(void);
	
	/** Gets the Nth external flavor supported by import provider. 
		(Flavors are used by clipboard/drag and drop)
		@return external flavor at specified index 
	*/
	virtual ExternalPMFlavor GetExternalFlavor(int32 n);

private:
	/** Returns the first uint32 found within the PMString
		The PMString is truncated to remove this number.
		i.e. string = "12 34 56" returns 12 with string now = "34 56"
		
		@param thisstring IN/OUT The PMString to look at for a number
		@return The first uint32 found in 'thisstring'
	*/
	uint32 ConsumeNextNumber(PMString& thisstring);

	/** This level deals with document centric tags. 
		These are: end of file, image load or text frame. 
		Comments are dealt with here as well.
			
		@param fileStream IN The stream to examine.
		@return Status.  Returns kSuccess if all is well.
	*/
	ErrorCode HandleDocLevelTags(IPMStream* fileStream);

	/** This level deals with paragraph centric tags. 
		These are: newparagraph, set font, set size, set style and set alignment.
		Comments are also dealt with here.
		
		@param model IN ITextModel to examine.  Used to build various text commands. 
		@param mytokeniser  IN/OUT The tokenizer to use. 
		@return Status.  Returns kSuccess if all is well.
	*/
	ErrorCode HandleParaLevelTags(ITextModel* model, CHMLFiltTokenisor* mytokeniser);

	/** Handles the creation of a graphic page item and frame and initialises the
		picture file input stream before finding a service provider that can load
		an image of this type, and creating a command to do the actual loading.
		
		@param tokenVal IN Holds the filename and top left origin of the image.
		@return Status.  Returns kSuccess if all is well.
	*/
	ErrorCode LoadImage(const PMString& tokenVal);


	/**	Handles the creation of text frames before calling HandleParaLevelTags
		to mange the insertion of text into the frame.
		@param theCHMLFiltTokenisor IN/OUT
		@param current_value IN
		@return ErrorCode 
	 */
	ErrorCode LoadText(CHMLFiltTokenisor* theCHMLFiltTokenisor, PMString& current_value);
	

	// Later: TODO 
	// offer option to create content onto multiple doclayers/spreads/pages.
	// At the moment, we only target spread 0 and page 0
	int32 getTargetSpreadIndex() { return 0;}
	// Eventually offer option to create content on different pages in a pub.
	int32 getTargetPageIndex() { return 0;}
	// member variables
	
	/** Represents the UIDRef of the document we're creating from which IDocument can be instantiated */
    UIDRef 	fCHMLDocRef;
	/** Represents the file from which the CHML content was imported */
	IDFile fCHMLFile;

	//int16 	fFeatureSetId;
};



/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(CHMLFiltImportProvider, kCHMLFiltImportProviderImpl)


/* Constructor
*/
CHMLFiltImportProvider::CHMLFiltImportProvider(IPMUnknown* boss)
: CPMUnknown<IImportProvider>(boss) , fCHMLDocRef(UIDRef::gNull)
{
	// cache current feature set ID for selecting features 
	// in the HandleParaLevelTags() method. 
	// Ignore kInDesignJapaneseFS only features for now
//	fFeatureSetId = LocaleSetting::GetLocale().GetFeatureSetId();
}



/* CountFileTypes
*/
int32 CHMLFiltImportProvider::CountFileTypes(void)
{
	return 1;
}

/* GetFileType
*/
SysOSType CHMLFiltImportProvider::GetFileType(int32 i)
{
	ASSERT(i == 0);
	return kCHMLFiltFile_Type;
}

/* CountExtensionsForFormat
*/
int32 CHMLFiltImportProvider::CountExtensionsForFormat(int32 formatIndex)
{
	ASSERT(formatIndex == 0);
	return 1;
}

/* CountFormats
*/
int32 CHMLFiltImportProvider::CountFormats(void)
{
	return 1;
}

/* GetExtensionForFormat
*/
PMString CHMLFiltImportProvider::GetExtensionForFormat(int32 formatIndex, int32 extensionIndex)
{
	ASSERT(formatIndex == 0);
	ASSERT(extensionIndex == 0);

	PMString extension(kCHMLFiltFileExtensionKey);

	return extension;
}

/* GetFormatName
	Returns the format name 
	SDK CHML Import -> this shows up in the open dialog 
*/
PMString CHMLFiltImportProvider::GetFormatName(int32 formatIndex)
{	
	ASSERT(formatIndex == 0);

	PMString formatName(kCHMLFiltFormatNameKey, PMString::kTranslateDuringCall); // "SDK CHML format"
	return formatName;
}

/* CanImportThis
*/
IImportProvider::ImportAbility CHMLFiltImportProvider::CanImportThisType(IFormatType* formatType)
{	
	SysOSType fileType = formatType->GetSysOSType();

	// judge by filetype... 
	if (fileType == kCHMLFiltFile_Type)
	{
		return IImportProvider::kFullImport;
	}

	// or judge by extension... 
	PMString ourExtension(kCHMLFiltFileExtensionKey);
	
	PMString extension;
	formatType->GetExtension(extension);		

	if (extension == ourExtension)
	{
		return IImportProvider::kFullImport;
	}

	return IImportProvider::kCannotImport;
}

/* CanImportThisStream
*/
IImportProvider::ImportAbility CHMLFiltImportProvider::CanImportThisStream(IPMStream* stream)
{
	// This gets called when there is no format type or extension information.
	// Look at the first few bytes and determine whether this is a stream that
	// can be imported.
	if (!stream->IsReading())
	{
		return IImportProvider::kCannotImport;
	}

	// make sure we're at the beginning
	stream->Seek(0, kSeekFromStart);

	// read out the first 6 bytes - we're looking for "<CHML>"
	uchar buf[7];
	if (stream->XferByte(buf, 6))
	{
		buf[6] = '\0';

		// check for "<CHML>" at the beginning of the file 
		if (strcmp((char*)buf, TOKENHEAD.GetPlatformString().c_str()) == 0)	// isn't identical
		{
			return IImportProvider::kFullImport;
		}
	}

	return IImportProvider::kCannotImport;
}


/* ImportThis
*/
void CHMLFiltImportProvider::ImportThis(IDataBase* db, 
									IPMStream* stream, 
									UIFlags uiFlags, 
									UIDRef* pNewDocUIDRef, 
									UIDRef* pDataLinkUIDRef /* optional! */, 
									PMString* asFormat /* ditto */)
{
	ErrorCode retval = kFailure;
	do 
	{	
		fCHMLDocRef = UIDRef::gNull;
	
    	InterfacePtr<IFileStreamData> iFileStreamData(stream, IID_IFILESTREAMDATA); // UseDefaultIID());
		ASSERT(iFileStreamData);
		if(!iFileStreamData) {
			break;
		}
		fCHMLFile = iFileStreamData->GetSysFile();
		SDKLayoutHelper layoutHelper;
		fCHMLDocRef = layoutHelper.CreateDocument(uiFlags);
		ASSERT(fCHMLDocRef != UIDRef::gNull);
				
		// At the moment, as we have switched to a new document (therefore new database), there is no
		// transaction on the database. So we need to start one explicitly...
		CmdUtils::AutoUndoSequencePtr seq(fCHMLDocRef.GetDataBase());
		

		retval = HandleDocLevelTags(stream);
		if(retval != kSuccess) {
			break;
		}
		
		// ### set the new document (to be returned by address) here!
		ASSERT(pNewDocUIDRef);
		if(!pNewDocUIDRef) {
			break;
		}
		*pNewDocUIDRef = fCHMLDocRef;
		
		//xxxpSpreadOverlapMgr->Enable(); 
		///xxxpSpreadOverlapMgr->ReInitialize(); 
		
		retval = kSuccess;
	} while (false);
	
	if (retval == kFailure) 
	{
		ErrorUtils::PMSetGlobalErrorCode(kImportFailedError);
		*pNewDocUIDRef = UIDRef(nil, kInvalidUID);
	}

} // ImportThis


/* GetInternalFlavor 
*/
PMFlavor CHMLFiltImportProvider::GetInternalFlavor(void)
{
	return kNoFlavor;
}

/* CountExternalFlavors 
*/
int32 CHMLFiltImportProvider::CountExternalFlavors(void)
{
	return 0;
}

/* GetExternalFlavor
*/
ExternalPMFlavor CHMLFiltImportProvider::GetExternalFlavor(int32 n)
{
	return kNoFlavor;
}


/* ConsumeNextNumber
*/
uint32 CHMLFiltImportProvider::ConsumeNextNumber(PMString& thisstring)
{
	// irp: want this capability
	if(thisstring.WCharLength()==0) {
		return 0;
	}
	thisstring.StripWhiteSpace(PMString::kLeadingWhiteSpace);
	// find the bounds of the first int
	uint32 i = 0;

    while ((thisstring.GetWChar(i) != ' ') && (i < thisstring.WCharLength()))
    {
		i++; // find where the first space occurs
    }

    if (i < thisstring.WCharLength())
    {
		K2::scoped_ptr<PMString> tmp;

		tmp.reset(thisstring.Substring(0, i) ); // get the first number out of the value
		uint32 tmpnum = tmp->GetAsNumber(); // convert it into a number
		thisstring.Remove(0, i); // and remove the corresponding chars from the original string
		//delete tmp ;
		return tmpnum;
	}
	else
    {
    	return thisstring.GetAsNumber(); // convert it into a number
    }
} // ConsumeNextNumber

/* HandleDocLevelTags
*/
ErrorCode CHMLFiltImportProvider::HandleDocLevelTags(IPMStream* fileStream)
{
	// create the tokeniser 
	CHMLFiltTokenisor mytokeniser(fileStream);

	// we ignore stuff coming off the wire if comments are on
	bool8 comments_on = kFalse;
	
	// the value of a particular token, for example <a l> is token kTokenAlign, with value of "l"
	PMString token_value;
	
	// the actual token
	Token_t mytok = kTokenInvalid;
	
	while((mytok = mytokeniser.GetNextToken(token_value)) != kTokenEOF)
	{
		while (comments_on)
		{	// we just junk stuff coming off the wire until we get the close comments tag
			comments_on = (mytok != kTokenCommentEnd); // ordering is important here...
			mytok = mytokeniser.GetNextToken(token_value);
			if (mytok == kTokenEOF)
			{
				// the CHML file has a comment that runs to eof.
				return kSuccess; 
			}
		}		
		
		switch (mytok) 
		{
			
		// comments on
		case kTokenCommentStart:
			{
				TRACEFLOW("SDKTraceFlow","HandleDocLevelTags: Token --> kTokenCommentStart\n");
				comments_on = kTrue;
			}
			break;
		
	
		// a text box. token_value is the bounding box for the text frame
		case kTokenTbox:
			{
				TRACEFLOW("SDKTraceFlow","HandleDocLevelTags: Token --> kTokenTextBox %s %s>\n", 
					TOKENTBOX.GetUTF8String().c_str(), token_value.GetUTF8String().c_str());
				if (this->LoadText(&mytokeniser, token_value) == kFailure)
				{
					ASSERT(0);
					return kFailure;
				}
			}
			break;
		
		// An image file to be read in. token_value will be the name of the file and the top left point on the page
		case kTokenIFile:
			{ 
				TRACEFLOW("SDKTraceFlow","HandleDocLevelTags: Token --> kTokenTextBox %s %s>\n", 
					TOKENIFILE.GetUTF8String().c_str(), token_value.GetUTF8String().c_str());
				if (this->LoadImage(token_value) == kFailure)
				{
					return kFailure;
				}
			}
			break;

		// ignore the header
		case kTokenHead:
			{
				TRACEFLOW("SDKTraceFlow", "HandleDocLevelTags: Token --> kTokenHead %s \n", TOKENHEAD.GetUTF8String().c_str());
			}
			break;

		default:
			{	
				return kFailure;
			}
			break;
		}
	}
	// get here when we get the eof
	return kSuccess;
} // HandleDocLevelTags

/*
*/
ErrorCode CHMLFiltImportProvider::HandleParaLevelTags(ITextModel* model, CHMLFiltTokenisor* mytokeniser)
{
	ErrorCode retval = kSuccess;
	// For every new text box, each paragraph must have an alignment policy (for body and lastline).
	PMString tokenval; // temporary utility string
	Token_t mytoken = kTokenInvalid;
	int32 position = 0;  // always start at position 0 in the text frame
	bool8 previsword = kFalse; // we need to know if we should insert a space into the text run
	bool8 comments_on = kFalse; // the comment tag is the only one that lives at both document and para levels
	mytoken = mytokeniser->GetNextToken(tokenval); // get the next token off the wire
	
	UIDRef textModelUIDRef =  ::GetUIDRef(model);
	CHMLFiltTextHelper textHelper(textModelUIDRef);
	bool16 keepGoing=kTrue;
	while (keepGoing)
	{	
		// Assume we didn't fail until we explicitly do
		retval = kSuccess;
		while (comments_on)
		{ // discard everything until we get end of comment token
			comments_on = (mytoken != kTokenCommentEnd); 
			mytoken = mytokeniser->GetNextToken(tokenval);
			if (mytoken == kTokenEOF)
			{
				mytokeniser->PushTokenBack(); // let the layer above deal with the token.
				// One of 2 early returns in this method; see the EOF one
				return kSuccess;
			}		
		}

		switch (mytoken) 
		{
			
			
			// comment
			case kTokenCommentStart:
				{
					comments_on = kTrue;
					break;
				}
				
			// a normal word
			case kTokenText:	
				{	
					// if we are between two words insert a space
					if (previsword)
					{
						PMString aSpace;
						aSpace.AppendW(kTextChar_Space);
						WideString wStr(aSpace);
						textHelper.Reset(position);
						retval = textHelper.InsertText(wStr);
						position++;
					}
					WideString wStr(tokenval);
					textHelper.Reset(position);
					retval = textHelper.InsertText(wStr);
					ASSERT(retval == kSuccess);
					previsword = true;
					position += tokenval.WCharLength();
					}
				break;

			// a new paragraph
			case kTokenPara:	
				{	
					PMString pStr;
					pStr.AppendW(kTextChar_CR);
					pStr.AppendW(kTextChar_CR);
					WideString wStr(pStr);
					textHelper.Reset(position);
					retval = textHelper.InsertText(wStr);
					ASSERT(retval == kSuccess);
					position += 2; 
					previsword = false; // we have a new paraggraph, we do not want a space
				}
				break;

			// underline
			case kTokenUnderline:
				{	
					textHelper.Reset(position);
					textHelper.AddUnderline();	
					retval = textHelper.Apply();
					ASSERT(retval == kSuccess);			
				}
				break;

			// underline off
			case kTokenNoUnderline:	
				{				
					textHelper.Reset(position);
					textHelper.AddNonUnderline();
					retval = textHelper.Apply();
					ASSERT(retval == kSuccess);			
				}
				break;

			// bold
			case kTokenBold:	// bold
				{	
					textHelper.Reset(position);
					textHelper.AddBold();
					retval = textHelper.Apply();
					ASSERT(retval == kSuccess);			
				} 
				break;

			// no bold
			case kTokenNoBold:	// no bold
				{		
					textHelper.Reset(position);
					textHelper.AddDefaultFont();
					retval = textHelper.Apply();
					ASSERT(retval == kSuccess);			
				}
				break;

			// set font
			case kTokenFont:
				{				
					textHelper.Reset(position);
					textHelper.AddFont(tokenval);
					retval = textHelper.Apply();
					ASSERT(retval == kSuccess);			
				}
				break;

			// set character size
			case kTokenSize:	
				{	
					textHelper.Reset(position);
					textHelper.AddPointSize(tokenval.GetAsDouble());
					retval = textHelper.Apply();
				ASSERT(retval == kSuccess);			
				}
				break;

			// align
			case kTokenAlign:
				{
					textHelper.Reset(position);
					int alignmentMode = tokenval.GetWChar(0).GetValue();
					ICompositionStyle::TextAlignment textAlignment = ICompositionStyle::kTextAlignLeft;
					switch(alignmentMode) {
						case 'l': textAlignment = ICompositionStyle::kTextAlignLeft;break;
						case 'r': textAlignment = ICompositionStyle::kTextAlignRight;break;
						case 'c': textAlignment = ICompositionStyle::kTextAlignCenter;break;
						case 'j': textAlignment = ICompositionStyle::kTextAlignJustifyFull;break;
					}
					textHelper.AddAlignment(textAlignment);
					retval = textHelper.Apply();
					ASSERT(retval == kSuccess);
				}
				break;
				
			case kTokenTbox:
			case kTokenIFile:
			case kTokenEOF:
				{
					mytokeniser->PushTokenBack(); // let the layer above deal with the token.
					return kSuccess;
				}
				break;

			// TODO put back the Japanese token code.
			// ipaterso; I have no way of testing/understanding this
			// so I'd prefer to remove while I refactor
				
			default:
				// some erroneous token. We'll just ignore it...
				break; 
			
		}
		ASSERT(retval == kSuccess);
		if(retval != kSuccess) {
			// Something bad happened, somewhere down the line
			break;
		}
		// now get the next token 
		mytoken = mytokeniser->GetNextToken(tokenval);
	}

	return retval; 
} // HandleParaLevelTags



/* LoadImage
*/
ErrorCode CHMLFiltImportProvider::LoadImage(const PMString& tokenVal)
{
	ErrorCode retval = kSuccess; // Not too worried about failures?
	PMString imagePath = tokenVal;
	do 
	{
		// get the file name from the buffer.
		uint32 i = 0;
		PMString delim = " ";
		CharCounter startLoc(0);
		CharCounter endLoc(0);
		K2::scoped_ptr<PMString> tmp;

		// strip the leading white space before we extract the filename.
		imagePath.StripWhiteSpace(PMString::kLeadingWhiteSpace);

		// find the filename portion of the tag value.
		if (imagePath.Contains("\""))
		{
			// this is to allow filenames with spaces to be enclosed in quotes.
			delim = "\"";
			// find the character position immediately after the first quote
			startLoc = imagePath.IndexOfString(delim) + 1;
			// find the character position of the next quote
			endLoc = imagePath.IndexOfString(delim, startLoc);
			// get the substring
			tmp.reset(imagePath.Substring(startLoc, endLoc - startLoc));
			
			// increment the endLoc so that the last quote 
			// is eaten in the PMString::Remove() method
			++endLoc;
		}
		else
		{
			// the tag value doesn't have quotes, so break at the 
			// character righ before the first space. 
			delim = " ";
			endLoc = imagePath.IndexOfString(delim); 
			// get the substring
			tmp .reset(imagePath.Substring(startLoc, endLoc - startLoc));
		}
		// HACK fix SDKFileHelper
		SDKFileHelper baseFile(this->fCHMLFile);
		SDKFileHelper sdkFileHelper(baseFile.GetAbsoluteFromRelative(*tmp));
		TRACEFLOW("SDKTraceFlow", "Trying to place %s", tmp->GetUTF8String().c_str());
		if(sdkFileHelper.IsExisting()) {
			// remove the filename from currentValue
			imagePath.Remove(0, endLoc);      
			// convert the x and y values in the string to numbers
			uint32 x = ConsumeNextNumber(imagePath);
			uint32 y = ConsumeNextNumber(imagePath);
			// Place at indicated location
			TRACEFLOW("SDKTraceFlow", "Trying to place %s at %d , %d", tmp->GetUTF8String().c_str(), x, y);
			CHMLFiltHelper filtHelper;
			UIDRef spreadLayerUIDRef = filtHelper.GetDefaultSpreadLayerRef(this->fCHMLDocRef, this->getTargetSpreadIndex());
			SDKLayoutHelper layoutHelper;
			ASSERT(spreadLayerUIDRef != UIDRef::gNull);
			int32 pageIndex= this->getTargetPageIndex();
			InterfacePtr<IPageList> pageList(this->fCHMLDocRef, UseDefaultIID());
			ASSERT(pageList);
			if(!pageList) {
				break;
			}
			UIDRef pageUIDRef(this->fCHMLDocRef.GetDataBase(), pageList->GetNthPageUID(pageIndex));
			ASSERT(pageUIDRef.GetUID() != kInvalidUID);
			UIDRef placedUIDRef = layoutHelper.PlaceFileInFrame(
													sdkFileHelper.GetIDFile(),
													spreadLayerUIDRef, 
													// We need to ensure that we have the co-ordinates
													// in the parent co-ordinate system. The parent of
													// this new graphic frame is the spread
													layoutHelper.PageToSpread( pageUIDRef, 
																							PMRect(x, y,x+100,y+100)),
													kSuppressUI
												);
			retval = kSuccess;
		}
		else
		{
			retval = kFailure;
		}
	} while (kFalse);

	return retval;
}

/* LoadText
*/
ErrorCode CHMLFiltImportProvider::LoadText(CHMLFiltTokenisor* theCHMLFiltTokenisor, PMString& current_value)
{
	do {

		// convert into numbers
		uint32 tlx = ConsumeNextNumber(current_value);  
		uint32 tly = ConsumeNextNumber(current_value);
		uint32 brx = ConsumeNextNumber(current_value);
		uint32 bry = ConsumeNextNumber(current_value);

		UIDRef multiColUIDRef;
		ASSERT(fCHMLDocRef != UIDRef::gNull);
		if(this->fCHMLDocRef == UIDRef::gNull) {
			break;
		}
		// Create in 0th spread of (active) document layer
		int32 spreadIndex=this->getTargetSpreadIndex();
		SDKLayoutHelper layoutHelper;
		CHMLFiltHelper filtHelper;
		UIDRef spreadLayerUIDRef = filtHelper.GetDefaultSpreadLayerRef(this->fCHMLDocRef, this->getTargetSpreadIndex());	
		ASSERT(spreadLayerUIDRef != UIDRef::gNull);
		int32 pageIndex= this->getTargetPageIndex();
		InterfacePtr<IPageList> pageList(this->fCHMLDocRef, UseDefaultIID());
		ASSERT(pageList);
		if(!pageList) {
			break;
		}
		UIDRef pageUIDRef(this->fCHMLDocRef.GetDataBase(), pageList->GetNthPageUID(pageIndex));
		ASSERT(pageUIDRef != UIDRef::gNull);
		PMRect boundsRect(tlx, tly, brx, bry); // bounds
		UIDRef textModelRef;
		UIDRef frameUIDRef = layoutHelper.CreateTextFrame(spreadLayerUIDRef, // spread layer is the parent
													layoutHelper.PageToSpread(pageUIDRef, boundsRect), 
													0, kFalse, & textModelRef
												);
	
		ASSERT(frameUIDRef != UIDRef::gNull);
		InterfacePtr<ITextModel> iTextModel(textModelRef, UseDefaultIID());
		ASSERT(iTextModel);
		if(!iTextModel) {
			break;
		}
		ErrorCode errHandleParaTags =  this->HandleParaLevelTags(iTextModel, theCHMLFiltTokenisor);
		ASSERT(errHandleParaTags == kSuccess);
		if(errHandleParaTags != kSuccess) {
			break;
		}
		return kSuccess;
	} while (kFalse);

	return kFailure;
}

// End, CHMLFiltImportProvider.cpp.


