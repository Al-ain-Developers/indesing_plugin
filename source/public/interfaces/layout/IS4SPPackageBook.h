//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IS4SPPackageBook.h $
//  
//  Owner: DaveM
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
//  
//  Package API Interface
//  
//========================================================================================

#pragma once
#ifndef __IS4SPPackageBook__
#define __IS4SPPackageBook__

#ifndef __IPMUNKNOWN__
#include "IPMUnknown.h"
#endif

#ifndef __PMTYPES__
#include "PMTypes.h"
#endif

#ifndef	__IDFile__
#include "IDFile.h"
#endif

#include "K2Vector.h"    // package file lists
#include "IBook.h"

class IJobTicket;
class IDocument;
class IPackageUI;

/**
	This interface is used to Package a book
	@see IS4SPPackage
*/
class IS4SPPackageBook : public IPMUnknown
{
public:
	
	/**
	 Identifiers that uniquely identify all packaging related messages or
	 error messgaes while packaging. Clients also use these identifiers to 
	 know the relevant state while packaging. 
	*/
	enum PackageRC { kPackageOK, kPackageCancelled, kPackageBadPreflight, 
					kPackageCantCreateFolder,
					kPackageCantCopyFonts,
					kPackageCantCopyProfiles,
					kPackageCantCopyLinks,
					kPackageCantCopyPub,
					kPackageCantUpdateLinks,
					kPackageCantRestoreLinks,
					kPackageCantDoHyphExceptions,
					kPackageUnknownError,
	                kPackageIDMLError, 
                    kPackageIDMLErrorPDFError, 
                    kPackageIDMLErrorPDFAlerts, 
                    kPackagePDFAlerts, 
                    kPackagePDFError
					};

   /**
	Used to initializes the packaging API object for the given Book.
	@param const IBook* : IN IBook pointer to be used for packaging
	@return bool16: returns KTrue,if this object is valid else kFalse
   */
   virtual bool16 Init(const IBook* f_iBook) = 0;

   /**
	This function is used to retrieve the pointer to the Book that we 
	are interested in packaging.
	@return IBook*: returns the book pointer to package
   */
   virtual IBook* GetParentBook() = 0;

	/**
	The accessor for getting the preference on copying fonts
	@return bool16: kTrue if copying of Fonts flag is set, kFalse otherwise
   */
   virtual bool16 GetCopyFontsFlag() = 0;

   /**
	The accessor for setting the preference on copying fonts
	@param bool16: IN kTrue to set the flag for copying of Fonts, kFalse otherwise
   */
   virtual void SetCopyFontsFlag(bool16 in_flag) = 0;

//   virtual bool16 GetCopyICCFlag() = 0;
//   virtual void SetCopyICCFlag(bool16 in_flag) = 0;
   
   /**
	The accessor for getting the preference on copying the links
	@return bool16: kTrue if copying of link flag is set, kFalse otherwise
   */
   virtual bool16 GetCopyGLinksFlag() = 0;
   
   /**
	The accessor for setting the preference on copying linked Graphics
	@param bool16: IN kTrue to set the flag for copying of Linked graphics, kFalse otherwise
   */
   virtual void SetCopyGLinksFlag(bool16 in_flag) = 0;
   
   /**
	The accessor for getting the preference on updating graphic links in package
	@return bool16: kTrue if the flag is set, kFalse otherwise
   */
   virtual bool16 GetUpdateGLinksFlag() = 0;
   
   /**
	The accessor for setting the preference on updating graphic links in package
	@param bool16: IN kTrue to set the flag for updating the graphic links, kFalse otherwise
   */
   virtual void SetUpdateGLinksFlag(bool16 in_flag) = 0;
   
   /**
	The accessor for getting the preference on whether to include fonts and links 
	from hidden document layers
	@return bool16: kTrue if the flag is set, kFalse otherwise
   */
   virtual bool16 GetHiddenLayersFlag() = 0;
   
   /**
	The accessor for setting the preference on whether to include fonts and links 
	from hidden document layers
	@param bool16: IN kTrue to set the flag, kFalse otherwise
   */  
   virtual void SetHiddenLayersFlag(bool16 in_flag) = 0;
   
   /**
	The accessor for getting the preference on whether to view the packaging report
	@return bool16: kTrue if the flag is set, kFalse otherwise
   */
   virtual bool16 GetViewReportFlag() = 0;
   
   /**
	The accessor for setting the preference on whether to view the packaging report
	@param bool16 :IN kTrue to set the flag, kFalse otherwise
   */
   virtual void SetViewReportFlag(bool16 in_flag) = 0;

      /**
	The accessor for getting the preference on whether to generate IDML while packaging
	@return bool16: kTrue if the flag is set, kFalse otherwise
   */
   virtual bool16 GetCreateIDMLFlag() = 0;
   
   /**
	The accessor for setting the preference on whether to generate IDML while packaging
	@param bool16 :IN kTrue to set the flag, kFalse otherwise
   */
   virtual void SetCreateIDMLFlag(bool16 in_flag) = 0;

      /**
	The accessor for getting the preference on whether to genereate PDF while packaging
	@return bool16: kTrue if the flag is set, kFalse otherwise
   */
   virtual bool16 GetCreatePDFFlag() = 0;
   
   /**
	The accessor for setting the preference on whether to generate PDF while packaging
	@param bool16 :IN kTrue to set the flag, kFalse otherwise
   */
   virtual void SetCreatePDFFlag(bool16 in_flag) = 0;
   
   /**
	The accessor for getting the preference on whether to use the document hyphenation
	exceptions only while packaging.
	@return bool16: kTrue if the flag is set, kFalse otherwise
   */
   virtual bool16 GetHyphExceptionsFlag() = 0;
  
   /**
	The accessor for setting the preference on whether to use the document hyphenation
	exceptions only while packaging.
	@param bool16: IN kTrue to set the flag, kFalse otherwise
   */
   virtual void SetHyphExceptionsFlag(bool16 in_flag) = 0;

   /**
	The accessor for getting the packaging location
	@return IDFile*, pointer to IDFile
   */
   virtual const IDFile* GetPackageLocation() = 0;

   /**
	The accessor for setting the packaging location
	@param const IDFile&: IN packaging location
   */
   virtual void SetPackageLocation(const IDFile& in_Location) = 0;
   
   /**
	The function that basically does the packaging function for a book (that basically
	has multiple documents contained in it). It creates all necessary packaging 
	directories and then copies all necessary files into the correspondent directories, 
	updates all links that have to be updated in the packaged publication, while 
	keeping links untouched in the orginal one.
	@return PackageRC: One of the packaging error messages
	@see PackageRC
   */
   virtual PackageRC PhysicalPackage() = 0;

   /**
   The function that is called when we want to the view the generated packaging report
   */
   virtual void ViewReport() = 0;
   
   /**
    This function is used get the list of font files to be packaged.
	@return K2Vector<IDFile>* : returns the font list
   */
   virtual K2Vector<IDFile>* GetFontFilePackageList() = 0;

   
   /**
    This function is used get the list of the graphic links to be packaged.
	@return K2Vector<IDFile>* : returns the graphics links list
   */
   virtual K2Vector<IDFile>* GetLinkFilePackageList() = 0;
   
   /**
    This function is used get the list of ICC Profiles to be packaged.
	@return K2Vector<IDFile>* : returns the profiles list
   */
   virtual K2Vector<IDFile>* GetProfileFilePackageList() = 0;
   
   /**
    This function is used get the list of documents (pubs) 
	in the book to be packaged.
	@return K2Vector<IDFile>* : returns the profiles list
   */
   virtual K2Vector<IDFile>* GetPubFilePackageList() = 0;

   /**
    This function is used get the size each documents in the book to be packaged.
	@return K2Vector<int32>* : returns the profiles list
   */
   virtual K2Vector<int32>* GetSizeList() = 0;
   
   /**
    This function is used in case if we want to package the entire
	book irrespective of the no. of documents selected in the Book panel.
	@return bool16 : kTrue if all the documents in the book needs to be 
					 packaged, kFalse otherwise.
   */
   virtual bool16 GetFullBookPackageFlag() const = 0;

   /**
    This setter function is used in case if we want to package the entire
	book irrespective of the no. of documents selected in the Book panel.
	@param bool16 : IN kTrue if all the documents in the book needs to be 
					 packaged, kFalse otherwise.
   */
   virtual void SetFullBookPackageFlag(bool16 in_flag) = 0; 

	/**
	 This function is used to retrieve the pointer to the document that we 
	 are currently packaging for the parent book.
	 @return IDocument*: returns the document pointer to package
	 */
	virtual IDocument* GetCurrentDocument() const = 0;
};

#endif //__IS4SPPackageBook__


/*==============================================================================
 * $Log: /shuksan/source/components/S4SP/Control/Interfaces/IS4SPPackage.h $
 * 
 * 3     7/17/98 2:34p Sdu
 * The Final Check in of the Preflight and Package plug-in by Paradigm
 * 
 * 16    7/16/98 6:32p Yurik
 * Clean up done
 * 
 * 15    03/07/98 19:33 Davem
 * changed bool to bool16
 * 
 * 14    7/02/98 3:43p Yurik
 * 
 * 13    6/30/98 9:08p Yurik
 * Package workflow revamped
 * 
 * 12    13/05/98 13:31 Davem
 * 
 * 11    4/24/98 9:38a Yurik
 * Fxing interface
 * 
 * 10    22/04/98 16:20 Davem
 * Added IDocument Accessors
 * 
 * 9     4/22/98 9:06a Yurik
 * Converting APIs from interfaces (to iDoc) to independent objects
 * 
 * 8     20/04/98 11:16 Davem
 * Fixed IDFile include
 * 
 * 7     4/15/98 5:28p Yurik
 * 
 * 6     3/16/98 7:02p Yurik
 * IPreflight and IPackage interfaces stubbed
 * 
 * 5     10/03/98 17:17 Davem
 * Updated to add gets for their descs
 * 
 * 4     10/03/98 16:30 Davem
 * removed unnecessary params
 * 
 * 3     98.3.7 0:24 PM Davem
 * Updated Interfaces
 * 
 * 2     05/03/98 18:37 Davem
 * fixed up #includes and ifdefd them for minimal compile time
 * 
 * 1     05/03/98 13:03 Davem
 * Intial Check In
 * 
 * 1     04/03/98 12:44 Davem
 * Adding subproject 'Interfaces' to '$/S4SP/Control'
 * 
 *=============================================================================
 */


