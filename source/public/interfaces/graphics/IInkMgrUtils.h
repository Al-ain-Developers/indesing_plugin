//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInkMgrUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IInkMgrUtils__
#define __IInkMgrUtils__

#include "IPMUnknown.h"
#include "Utils.h"

#include "IColorData.h"

#include "PrintID.h"
#include "ColorSystemID.h"
#include "ShuksanID.h"
#include "PMString.h"
#include "UIDList.h"
#include "IInkData.h"
#include "BravoForwardDecl.h"


class	IWorkspace;
class	ISwatchList;
class	UIDList;
class	PMReal;
class	IDataBase;
class	IInkList;
class	IPMInkBossData;


/**	This utility facilitate the mangement of InDesign inks.
*/
class IInkMgrUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINKMGRUTILS };
	
	/**	Specifies the type of process inks.
	*/
	typedef enum {
		/**	Specifies the traditional CMYK process inks.
		*/
		kPSProcess = 1,
		
		/**	Specifies the Hexachrome process ink set.
		*/
		kPSHexachrome
	} PSProcessInkType;

	/**	Query for the current active ink list in the specified active context. If active context is not specified,
		the current active context is used.
		@param activeContext the specified active context.
		@return the IInkList interface pointer if one exists or nil.
	*/
	virtual IInkList* _QueryActiveInkList (IActiveContext* = nil) = 0;

	/**	Query for the front most document's ink list
		@return the IInkList interface pointer if one exists.
	*/
	virtual IInkList* _QueryActiveDocInkList () = 0;

	/**	Query for the ink list specified by the given database.
		@param iDataBase is the database. This can be the database of the application workspace.
		@return the IInkList interface pointer if one exists or nil.
	*/
	virtual IInkList* QueryDocInkList (IDataBase* iDataBase) = 0;

	/**	Get the list of all ink UID that are ink alias for anther ink from the specified ink list. If excludeSwatchAliases is
		set to kTure, ink aliases that are results of swatch aliases are excluded from the returned list. The default is to
		return all ink aliases.
		@param iInkList is the database's ink list.
		@param excludeSwatchAliases exclude the ink aliases that resulted from swatch aliases. The default is set to kFalse.
		@return the list of ink alias UIDs.
	*/
	virtual UIDList GetInkAliasListFromInkList (IInkList* iInkList, bool16 excludeSwatchAliases = kFalse) = 0;

	/**	Get the ink's alias UID if ink is aliased.
		It returns its alias ink's name, if ink is process, plate order, alternate color space/values if spot ink.
		If ink is not aliased, it returns kInvalidUID.
		@param iInkList is the ink list the specified ink is in.
		@param inkUID is the ink whose alias ink information we want to get.
		@param aliasInkName is the alias ink's name.
		@param isProcessInk is kTrue if the alias ink is a process ink.
		@param plateOrder is the alias ink's plate order.
		@param colorValue is the alias ink's color value if alias ink is spot.
		@return the alias ink UID.
	*/
	virtual UID GetInksAliasInfo (IInkList* iInkList, UID inkUID, PMString& aliasInkName, bool16& isProcessInk, int32& plateOrder, ColorArray& colorValue) = 0;
	
	/**	Get the ink's alias UID  by name if ink is aliased.
		@param iInkList is the ink list the specified ink is in.
		@param inkName is the ink name.
		@return the alias ink UID.
	*/
	virtual UID GetInksAliasUID (IInkList* iInkList, PMString& inkName) = 0; 

	/**	Get the ink's alias UID  by ink UID if ink is aliased.
		@param iInkList is the ink list the specified ink is in.
		@param inkUID is the ink UID.
		@return the alias ink UID.
	*/
	virtual UID GetInksAliasUID (IInkList* iInkList, UID inkUID) = 0; 
	
	/**	Determined if the ink alias is caused by swatch alias.
		@param iInkList is the ink list the specified ink is in.
		@param inkRef is the ink UIDRef.
		@return kTrue if resulting ink alias is result of swatch alias.
	*/
	virtual bool16 InksSwatchIsAliased (IInkList* iInkList, const UIDRef& inkRef) = 0;

	/**	Get the specified printing ink's plate order in the given ink list.
		@param iInkList is the ink list the specified ink is in.
		@param inkUID is the ink UID.
		@return the ink's plate order.
	*/
	virtual int32 GetPrintInkPlateOrder (IInkList* iInkList, UID inkUID) = 0;
	
	/**	Get the color swatch UID which defined the spot ink.
		@param inkRef is the ink UID.
		@param iSwatchOrInkList is the IPMUnknown* to the ink list or the swatch list.
		@return the corresponding spot color swatch UIDRef.
	*/
	virtual UIDRef GetSpotInksColorSwatchUID (const UIDRef& inkRef, IPMUnknown* iSwatchOrInkList = nil) = 0;

	/**	Get the spot color in the swatch list with the given name
		@param iDB is the swatch's database.
		@param spotName is the name of the spot color swatch.
		@param type is the process ink type.
		@return kTrue if the specified spot color swatch exists in the specified data base.
	*/
	virtual bool16 GetSpotInSwatchList	(IDataBase*	iDB, const PMString& spotName, PSProcessInkType type) = 0;

	/**	Get the specified ink's color usage
		@param swatchRef is the spot color swatch UIDRef.
		@param iSwatchList is the swatch list.
		@return specified swatchRef's ink type.
	*/
	virtual IInkData::InkType GetInksColorUsageType (const UIDRef& swatchRef, ISwatchList* iSwatchList = nil) = 0;

	/**	Invoke the ink manager dialog.
		@param iInkList is the ink list to use to populate the ink manager dialog.
		@param dlgID is the dialog's resource ID.
	*/
	virtual void _InvokeInkManagerDialog (IInkList* iInkList = nil, RsrcID dlgID = 0) = 0;
	
	/**	Return the UI ink name (after translataion) from the ink name.
		@param iInkBossData is the ink's persistent data.
		@return corresponding translated ink name.
	*/
	virtual PMString GetInkUIName (IPMInkBossData* iInkBossData) = 0;
	
	/**	Return the PostScript color name from the ink name.
		@param iInkBossData is the ink's persistent data.
		@return corresponding PostScript color name.
	*/
	virtual PMString GetInkPSName (IPMInkBossData*) = 0;
	
	/**	Get a list of the inks that are visible.
		@param iInkList is the ink list.
		@param allToProcess is kTrue if all spot inks are ignored.
		@return a list of visible ink UIDs.
	*/
	virtual UIDList GetVisibleInkListFromInkList (IInkList* iInkList,  bool16 allToProcess) = 0;

	/** Support needed for the AGMColorMapper port
	*/
	
	/**	Find an ink by name
		@param iInkList is the ink list.
		@param inkName is specified ink to find.
		@return ink UID of the inkName.
	*/
	virtual UID FindInk(IInkList*, PMString inkName) = 0;
	
	/**	Find an ink by PostScript name
		@param iInkList is the ink list.
		@param inkName is specified ink to find.
		@param psInkType is specified process ink type.
		@return ink UID of the inkName.
	*/
	virtual UID FindPSInk(IInkList*, PMString inkName, PSProcessInkType psInkType) = 0;
	
	/**	Get a list of the inks that are converted to process
		@param iInkList is the ink list.
		@return list of ink UID that are converted to process.
	*/
	virtual UIDList GetInkConvertToProcessListFromInkList(IInkList* iInkList) = 0;
	
	/**	Check whether any of the colors in the list are subject to ink mapping 
		@param iInkList is the ink list.
		@param swatchUIDList is the color UID list.
		@return kTrue if at least one color in swatchUIDList is remapped.
	*/
	virtual bool16 ColorsAreModified(IInkList*, UIDList swatchUIDList) = 0;
	
	/**	Create the CAGMColorSpace of the aliasee.
		@param iInkList is the ink list.
		@param aliasee is the ink UID that is aliased.
		@param doPrint is true if currently printing.
		@return CAGMColorSpace of the aliased ink.
	*/
	virtual CAGMColorSpace CreateAliasedColorSpace(IInkList* iInkList, UID& aliasee, bool16 doPrint = kFalse) = 0;

	/**	Return kTrue if specified ink list has at least one spot ink.
		If ink list is nil, use the current active ink list.
		@param iInkList is the ink list.
		@param ignoreConvert2Process is kTrue if ignoring any convert to process setting.
		@return kTrue if ink list has spot inks.
	*/
	virtual bool16 InkListHasSpotInks (IInkList* iInkList = nil, bool16 ignoreConvert2Process = kFalse) = 0;

	/**	Get all the inks used on the spread by doing a ink resource draw order iteration.
		@param spreadRef is UIDRef of the spread.
		@param flags are used for iterating the draw order.
		@param iInkList is optional parameter. It should be the ink list for the document or the book. If not set, ink list for the document is used.
		@param pBoundsRect is optional parameter. If set, the function finds the inks used on this rect in the spread, else it uses the pasteboard bounds. It is useful if you want to know, for example, whether a given page has any inks.
		@return UIDList of inks used on the spread.
	*/
	virtual UIDList GetInksUsedOnSpread(UIDRef& spreadRef, int32 flags, IInkList* iInkList = nil, PMRect* pBoundsRect = nil) = 0;
};


#endif	// __IInkMgrUtils__
