//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ILocalFontManager.h $
//  
//  Owner: ???
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
#ifndef __ILocalFontManager__
#define __ILocalFontManager__


#include "IFontMgr.h"


//----------------------------------------------------------------------------------------
// Interface ILocalFontManager
//----------------------------------------------------------------------------------------

/**
	Manager for document-installed fonts. Acquire this interface by querying the IDocument
	for the IFontMgr, rather than querying the session. If that results in a valid
	InterfacePtr (it should), then cast to ILocalFontManager if you need one of the methods
	defined within ILocalFontManager.
	
	A document-installed font is a font that the document has installed, that is available
	only to the document, and that goes away when the document goes away.
	
	ILocalFontManager simply passes many of the methods defined in IFontMgr to the session
	IFontMgr. However, those that are specific to document fonts are handled here, notably
	AddFont, DeleteFont. Also, QueryFont finds the document-installed version if there is
	one; otherwise it defers to the session font manager.
*/


class DocumentFontGroupIteratorCallBack;


class ILocalFontManager: public IFontMgr
{
	public:
			/**
				Determine whether the supplied font has been installed by the document and is therefore local to the
				document.
				
				@param	font	The IPMFont whose status is to be queried.
			*/
			virtual
			bool
		IsDocumentInstalledFont (IPMFont *font) const
			= 0;


			/**
				Request an IPMFont given a family and face.
				
				@param	family	The native or non-native font family name (not the display name).
								(This corresponds to IPMFont::AppendFamilyName or IPMFont::AppendFamilyNameNative.)
				@param	face	The name of the font style. May be empty for a plain style.
								(This corresponds to IPMFont::AppendStyleName or IPMFont::AppendStyleNameNative.)
			**/

			virtual
			IPMFont *
		QueryDocumentFont (PMString const &family, PMString const &face)
			= 0;

			/**
				Count the number of font groups (families) installed by the document.

				@return		The count of font groups (families) installed by the document. As of this writing, there are
							no conditions under which this count would change over the life of the open document.
			*/
			virtual
			int32
		GetNumDocumentFontGroups() const
			= 0;

			/**
				Retrieve a font group by index. The font group is only for fonts installed by the document. For fonts
				installed in the session and available to all documents, use the IFontMgr you acquire from the session.

				@param	groupIndex		Index of group. Must be less than GetNumDocumentFontGroups().
				@return	IFontGroup*		Font group found. Nil if out of range.
			*/
			virtual
			IFontGroup *
		QueryDocumentFontGroup (int32 groupIndex)
			= 0;

			/**
				Retrieve a font group by name. The font group is only for fonts installed by the document. For fonts
				installed in the session and available to all documents, use the IFontMgr you acquire from the session.

				@param	groupName		Group name or family name, which can be either native or non-native. If more
										than one group with same name exists, then this returns the first one found.
										Calling IFontGroup->GetGroupsWithSameName will return other groups with same name.
				@return	IFontGroup*		Font group found. NULL if none found.
			*/
			virtual
			IFontGroup *
		QueryDocumentFontGroup (PMString const &groupName)
			= 0;

			/**
				Iterate over the document font groups. This will return only fonts installed by the document.
				
				@param callBack	The object you construct to receive notifications from this method.
			*/
			virtual
			void
		IterateDocumentFontGroups (DocumentFontGroupIteratorCallBack *callBack)
			= 0;
};


//----------------------------------------------------------------------------------------
// Class DocumentFontGroupIteratorCallBack
//----------------------------------------------------------------------------------------

/** Parameter for ILocalFontManager::IterateDocumentFontGroups()
	@ingroup text_font
*/

class DocumentFontGroupIteratorCallBack
{
	public:
			/**
				Called at the start of the iteration, as the first call. Will get called whether or not any eligible
				fonts are present.
			*/
			virtual
			void
		OnStart()
			= 0;

			/**
				Called at the end of the iteration, as the last call to this DocumentFontGroupIteratorCallBack.
			*/
			virtual
			void
		OnEnd()
			= 0;

			/**
				Called before first call to OnFontGroupStart. Only gets called if their are eligible fonts.
			*/
			virtual
			void
		OnPreiteration()
			= 0;

			/**
				Called at the start of a font group

				@param	fontGroup	Font group we are starting to iterate.
			*/
			virtual
			void
		OnFontGroupStart (IFontGroup *fontGroup)
			= 0;

			/**
				Called for each font.

				@param	pFont				Font to iterate.
				@param	fontGroup			Font group font belongs to.
				@param	displayFamilyName	Name for family as it shows in font menu.
				@param	displayStyleName	Name for font style as it shows in font menu.
			*/
			virtual
			void
		OnFont (IPMFont *pFont, IFontGroup *fontGroup, PMString const &displayFamilyName, PMString const &displayStyleName) 
			= 0;

			/**
				Called at the end of a font group

				@param	fontGroup	Font group we are done iterating
			*/
			virtual
			void
		OnFontGroupEnd (IFontGroup *fontGroup)
			= 0;

			/**
				Called after last call to OnFontGroupEnd. Only gets called if OnPreiteration got called.
			*/
			virtual
			void
		OnPostiteration()
			= 0;

			/**
				Drives the iterator to skip styles and only report families.

				@return	kTrue Direct the iterator to skip styles. kFalse: Report styles.
			 */
			virtual
			bool16
		RunFamilyOnly() const
			= 0;

			/**
				Determines the format of names returned in OnFont

				@return	Names Flag value. See enum ITextUtils::DisplayNamesFlag.
			 */
			virtual
			int16
		GetNamesFlag() const
			= 0;

			/**
				Directs the iterator to skip a font entirely.

				@param *font	Font to choose to skip
				@return bool16	kTrue directs the iterator to skip this font. kFalse: Report this font.
			 */
			virtual
			bool16
		SkipThisFont (IPMFont *font) const
			= 0;
    
			/**
				Called for each font either variable or MMFont.
     
				 @param    pFont                Font to iterate.
				 @param    sourceAxes           Design Axes of a font
				 @param    numAxes              number of design axes
			 */
			virtual
			void
		OnMMAxes (IPMFont *pFont, const Fixed *sourceAxes, int32 numAxes)
			= 0;
};


#endif
