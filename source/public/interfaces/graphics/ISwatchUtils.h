//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISwatchUtils.h $
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
#ifndef __ISwatchUtils__
#define __ISwatchUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "IColorData.h"
#include "IInkData.h"

#include "ColorSystemID.h"
#include "ShuksanID.h"
#include "GraphicTypes.h"
#include "PMString.h"
#include "K2Vector.h"
#include "UIDList.h"

class	IWorkspace;
class	ISwatchList;
class	PMReal;
class	IDataBase;
class	IRenderingObject;


/**	Helper class to facilitate processing of unique swatch names.
*/
class SwatchUtilsUniqueNameTempCache
{
public:
	SwatchUtilsUniqueNameTempCache():
		bBaseNameExists(0),
		bInitializedIndices(0) {}

public:
	K2Vector<int32> vecIndices;
	bool16          bBaseNameExists;
	bool16          bInitializedIndices;
};

/**	Swatch related utility
	@see ISwatchList for more information on requirements for swatch UIDs and UIDRefs
	@see aslo IRenderingObject
*/
class ISwatchUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISWATCHUTILS };

	/**	Use to specify the type of swatch match based on swatch name.
	*/
	enum SwatchNameMatchType {
		/**	No match in the swatch name. */
		kNoMatch = -1,		
		/**	An exact match in the swatch name is found. */
		kExactMatch = 1,
		/**	An alternate match in the swatch name is found. This is limited to PANTONE library swatches. */
		kAlternateMatch
	};

	/**	Use to specify the duplicate swatch preference.
	*/
	enum DuplicatePref {
		/** kUseDefault means don't duplicate on kSameNameSameData, do duplicate kSameNameDifferentData (except spots) */
		kUseDefault = 0,
		/** kDoDuplicate will override default in favor of duplicating */
		kDoDuplicate,
		/** kDontDuplicate overrides default in favor of not duplicating */
		kDontDuplicate,
		/** kDoReplace means don't duplicate on kSameNameDifferentData and always do override*/
		kDoReplace
	};

	/**	Use to specify the desired action resulting from CheckSwatchBeforeCopy()
		@see also CheckSwatchBeforeCopy
	*/
	enum ActionCode {
		/** kKeepOriginalSwatch indicates that the original swatch matched in the target should be used. */
		kKeepOriginalSwatch = 0,
		/** kAddThisSwatch indicates that a new swatch matching the source should be addded in the target. */
		kAddThisSwatch,
		/** kAddThisTint indicates that a new tint swatch matching the source should be added. */
		kAddThisTint,
		/** kCancelAction indicates that the specified action has been cancelled. */
		kCancelAction,
		/** kAddAndConvertThisSwatch indicates that the source profile should be added and converted in the target. */
		kAddAndConvertThisSwatch,
		/** kReplacePantoneSwatch indicates that as a result of pantone conflict, the target should be replaced. */
		kReplacePantoneSwatch,
		/** kReplaceThisSwatch indicates that the target will be replaced by the source's definition if they have same name.*/
		kReplaceThisSwatch
	};

	//	it might have been nice if all the various boolean duplicate parameters had originally
	//	been bitflags, but they weren't.  So, I am starting a new set of bitflags
	
	/** A new set of bitflags that can be be passed to the various duplicate/replace swatch functions.
	*/
	enum SwatchFlags {
		// just means none of the other flags are set.
        kNoFlags = 0,

		/** default is to notify, because that was the original behavior, but this causes
			performance problems in some cases, so this allows you to prevent notification.
		*/
		kDontNotifySwatchList = 1,
		
		/** Flatten any linked mixed ink swatch when replacing a color swatch. Default is to replace swatch as is.
		*/
		kFlattenMixedInkSwatch = (1L<<1),
		
		/**	Unlock resulting swatch. Default is to keep swatch as is.
		*/
		kUnlockSwatch = (1L<<2),
		
		/**	Don't update the graphic state if necessary. Default is to update.
		*/
		kDontUpdateGraphicState = (1L<<3),

		/**	Don't warn the user about same named spots that have different definitions. Default is to warn.
		*/
		kDontWarnUserAboutDuplicateSpot = (1L<<4),

		/**	Preserve origainal swatch lock properties when duplicate or replacing a color swatch. The default is to update.
		*/
		kPreserveLockSwatch = (1L<<5)

	};

	/**	Use to specify the swatch mathcing result from CheckSwatchBeforeCopy()
	*/
	enum CompareCode {
		/** kSwatchNotCompared indicates that the specified swatch is not compared. */
		kSwatchNotCompared = 0,
		/** kDiffName indicates that the source swatch has different name from all target swatches. */
		kDiffName,
		/** kSameNameSameData indicates that the source swatch matched the target with same same and same data. */
		kSameNameSameData,
		/** kSameNameDiffData indicates that the source swatch matched the target with same same but different data */
		kSameNameDiffData,
		/** kUnamedSwatch indicates that the source swatch is a unnamed swatch. */
		kUnamedSwatch,
		/** kSameSwatchSameTint indicates that the source matched a target with same base color and same tint value. */
		kSameSwatchSameTint,
		/** kSameSwatchDiffTint indicates that the source matched a target with same base color but different tint value. */
		kSameSwatchDiffTint,
		/** kAlternatePantoneName indicates that the source matched a target with alternate pantone name. */
		kAlternatePantoneName,
		/** kSameNameEqualMixedInks indicates that the source matched a target with same name, equivalent ink list but inks appear in different orders. */
		kSameNameEqualMixedInks
	};

	/** Use to specify the type of swatch.
	*/
	enum SwatchType {
		/** kNoneSwatch specifies swatch is a reserved [None] swatch.
		*/
		kNoneSwatch = 0,
		/** kBaseColor specifies swatch is a normal base color swatch. This is either
			a spot or a process color.
		*/
		kBaseColor,
		/**	kTintColor specifies swatch is a tint color swatch.
		*/
		kTintColor,
		/**	kMixedInkColor specifies swatch is a standalone mixed ink color.
		*/
		kMixedInkColor,
		/**	kLinkedMixedInkColor specifies swatch is a linked mixed ink color. This is
			a child mixed ink swatch of a mixed ink group.
		*/
		kLinkedMixedInkColor,
		/**	kMixedInkGroupParent speifies swatch is a mixed ink group parent swatch.
		*/
		kMixedInkParent,
		/**	kGradient specicies swatch is a gradient swatch.
		*/
		kGradient,
		/**	kAGMBlackBoxPaint specicies swatch is a AGM blackbox paint object.
		*/
		kAGMBlackBoxPaint,
		/**	kOtherSwatch specicies swatch is a non-InDesign native swatch.
		*/
		kOtherSwatch
	};
	
	/** Use to specify the type of swatch.
	*/
	enum SwatchUsageType {
		/** kAllReferences specifies all swatch references.
		*/
		kAllReferences,
		/** kAllObjectReferences specifies all swatch references by InDesign objects such as page items, text, table,
			and styles. Dependent swatches of those that are referenced are also included even if they are not directly
			referenced.
		*/
		kAllObjectReferences,
		/** kStyleReferences specifies all swatch references by text style, table style, object style, or another
			swatch.
		*/
		kStyleReferences
	};
	
	/**	Get an unique swatch name starting with "baseName". If the baseName is already unique, this
		is returned.
		@param swatchList the swatch list in which the name should be unique.
		@param baseName the base name to start with.
		@param suffixString the string to append to baseName if not empty.
		@param doAppendSuffix if set to kTrue, then suffixString is append.
		@param doTruncateNumber if set to kTrue, the existing number appended to baseName will be removed first.
		@param vecExistingSuffixes if you are calling GetUniqueSwatchName many times repeatedly for the same
		   base name, this will act as a cache and significantly improve performance.  If nil, it is ignored.
		@return an unique swatch name within the specified swatch list.
	*/
	virtual PMString GetUniqueSwatchName( ISwatchList* swatchList,
											  const PMString& baseName,
											  const PMString& suffixString,
											  bool16 doAppendSuffix = kTrue,
											  bool16 doTruncateNumber = kTrue,
											  SwatchUtilsUniqueNameTempCache* pCache = nil) = 0;

	/**	Format a swatch name from the given color space and value. For example, if the color space is CMYK and value is (0,100, 20, 0), the
		swatch name is "C=0, M=100, Y=20, K=0". If a swatch name with this string already exists, the string is appended a number starting
		with "2".
		@param swatchList the swatch list in which the swatch name should be unique.
		@param colorspace the colorspace to format swatch name with.
		@param colorValue the color value to format swatch name with.
		@param doUseComma if kTrue, the comman "," is used with a space separator.
		@return an uniquely formated swatch name.
	*/
	virtual PMString FormatSwatchNameWithColorValue (ISwatchList* swatchList, int32 colorspace, const ColorArray& colorValue, bool16 doUseComma) = 0;
	
	/** Query for the current active swatch list in the specified context. If the context is nil, the current active
		context is used.
		@param context the active context to use.
		@return a ISwatchList* associated with the context.
		@see ISwatchList
	*/
	virtual ISwatchList* QueryActiveSwatchList(IActiveContext* context = nil) = 0;
	
	/** Query for the swatch list of the given database.
		@param iDataBase the database to use
		@return a ISwatchList* associated with the iDataBase.
		@see ISwatchList
	*/
	virtual ISwatchList* QuerySwatchList(IDataBase* iDataBase) = 0;

	/** Create a new swatch matching the attributes described by the newRenderObject exactly in the given workspace or database.
		Update graphic state in the specified workspace or database to the new swatch when updateGfxState is set to kTrue.
		@param renderClassID rendering class ID of the new rendering object.
		@param newRenderObject specifies the new rendering attributes matching the renderClassID.
		@param iDataBase the target data base to create the new swatch.
		@param workspacePtr the target workspace to create the new swatch.
		@param updateGfxState if kTrue, the graphic state of the specified workspace or database is updated with this new swatch UID.
		@param nSwatchFlags a combination of SwatchFlags. See SwatchFlags above.
		@param colorGroup the UID of the parent color group for the new swatch.
		@return a new swatch UID.
	*/
	virtual UID CreateNewSwatch( ClassID renderClassID, const IPMUnknown* newRenderObject, IDataBase* iDataBase, bool16 updateGfxState = kTrue, int32 nSwatchFlags = kNoFlags, const UID& colorGroup = kInvalidUID) = 0;
	
	/** @see CreateNewSwatch above.
	*/
	virtual UID CreateNewSwatch( ClassID renderClassID, const IPMUnknown* newRenderObject, IWorkspace* workspacePtr, bool16 updateGfxState = kTrue, int32 nSwatchFlags = kNoFlags, const UID& colorGroup = kInvalidUID) = 0;

	/**	Duplicate the swatches specified by the dupList in the specified swatchList. If swatchList is nil, the source swatch list
		is used.
		@param dupList specifies a list of swatch UID to duplicate.
		@param swatchList the target swatch list to create the duplicates.
		@param makeHidden if kTrue, the resulting duplicates is converted to unnamed swatches.
		@param convertToProcess if kTrue, the resulting duplicates that are color swatches are converted to process color swatches.
		@param doCheck if kTrue, call CheckSwatchBeforeCopy() first.
		@param dupPref used by the reference converter to determine what to do if an existing swatch matches the one to be duplicated.
		@param nameSuffixString the string to append to duplicated swatch name. if string is empty, the new name will just be the duplicated name with a numeric value
		@param doConvert if kTrue color values are converted using source and destination document color profiles
		@param doUnlock if kTrue locked swatches are unlocked.
		@param nFlags a combination of SwatchFlags. See SwatchFlags above.
		@return a list of swatch UID corresponding to the UID in dupList.	
	*/
	virtual UIDList DuplicateSwatches(
		const UIDList& dupList,
		ISwatchList* swatchList,
		bool16 makeHidden,
		bool16 convertToProcess,
		bool16 doCheck,
		ISwatchUtils::DuplicatePref dupPref = kDoDuplicate,
		const PMString& nameSuffixString = PMString(""),
		bool16 doConvert = kFalse,
		bool16 doUnlock = kFalse,
		int32  nFlags = kNoFlags) = 0;

	/**	Delete all swatches in the list after replacing all references to these swatches with the replacement swatch.
		@param selectedList the list of swatch UID to delete. Reserved swatches in the lsit are not deleted.
		@param replacementUID the replacement swatch UID.
		@return kSuccess if swatches are deleted and replaced successfully. Otherwise, returns an error code.
	*/
	virtual ErrorCode ReplaceAndDeleteSwatches( UIDList* selectedList, UID replacementUID ) = 0;

	/**	Deletes all swatches in the list after replacing all references to these swatches with equivalent unnamed local swatches
		@param selectedList the list of swatch UID to delete. Reserved swatches in the lsit are not deleted.
		@return kSuccess if swatches are deleted and replaced successfully. Otherwise, returns an error code.
	*/
	virtual ErrorCode ConvertAndDeleteSwatches( UIDList* selectedList ) = 0;

	/** Convert the specified unnamed color swatch to the equivalent named with color value swatch.
		@param originalUID the unnamed color swatch to convert.
		@param newUID the converted global color swatch. This swatch is named with color values.
		@return kSuccess if swatch is converted to named swatch successfully. Otherwise, returns an error code.
	*/
	virtual bool16 ConvertToGlobalColorSwatch(ISwatchList*	iSwatchList, const UID& originalUID, UID& newUID) = 0;
	
	/**	Compile a list of swatch UIDs that are dependents of swatches in the fromList.
		@param iSwatchList the swatch list to gather information from.
		@param fromList the list of base swatch UID.
		@param dependentList the resulting list of swatch UIDs that are dependent of swatches in the fromList.
		This list can include tint swatches as well as mixed ink group swatches.
	*/
	virtual void GetAllDependentSwatches(ISwatchList* iSwatchList, const UIDList& fromList, UIDList& dependentList) = 0;

	/**	Compile a list of color swatches UIDs and tint values that are dependent of the base swatches in the fromList.
		@param iSwatchList the swatch list to gather information from.
		@param fromList the list of base color swatch UID.
		@param dependentList the resulting list of tint swatch UIDs that are tint of swatches in the fromList
		@param tintList the list of tint values corresponding to the dependentList.
	*/
	virtual void GetAllDependentColorSwatchesAndTintValues(ISwatchList* iSwatchList, const UIDList& fromList, UIDList& dependentList, K2Vector<PMReal>& tintList) = 0;

	/**	Compile a list of mixed ink parent swatches from the specified swatch list.
		@param iSwatchList the target swatch list.
		@param mixedInkParentList returns a list of mixed ink parent swatchUID.
	*/
	virtual void GetAllMixedInkParentSwatches (ISwatchList* iSwatchList, UIDList& mixedInkParentList) = 0;

	/**	Returns a list of mixed ink swatches that are linked to the specified parent swatch.
		@param iSwatchList the target swatch list.
		@param mixedInkParentRef specifies the mixed ink parent swatch UID.
		@param mixedInkList returns a list of mixed ink swatch UIDs that are linked to mixedInkParentRef. Returns an empty list if
		mixedInkParentRef is not mixed ink parent swatch.
	*/
	virtual void GetDependentMixedInkSwatches (ISwatchList* iSwatchList, const UIDRef& mixedInkParentRef, UIDList& mixedInkList) = 0;
	
	//___________________________________________________________________________________

	/**	Creates a tinted color swatch. This will return a kInvalidUID if the source swatch is not a color.
		If tint of that swatch already exists, it will return the existing tint swatch UID.
		@param srcSwatch the base swatch from which to create the new tint swatch.
		@param tintval the tint value of the new tint swatch.
		@param colorGroup the UID of the parent color group for the new tint swatch.
		@return the new tint swatch UID.
	*/
	virtual UID CreateTintedSwatch 
		(
			const UIDRef& srcSwatch,
			const PMReal& tintval,
			const UID& colorGroup = kInvalidUID
		) = 0;
		

	/**	Creates a new process CMYK color swatch in the workspacePtr using the passed in values.
		@param workspacePtr the workspace of the new process color swatch.
		@param swatchName specifies the new swatch name.
		@param cyanVal specifies the cyan component value.
		@param magentaVal specifies the magenta component value.
		@param yellowVal specifies the yellow component value.
		@param blackVal specifies the black component value.
		@param colorGroup the UID of the parent color group for the new process color swatch.
		@return the new process color swatch UID.
	*/
	virtual UID CreateProcessCMYKSwatch 
		(
			IWorkspace* workspacePtr, 
			const PMString& swatchName, 
			const PMReal& cyanVal, 
			const PMReal& magentaVal,
			const PMReal& yellowVal,
			const PMReal& blackVal,
			const UID& colorGroup = kInvalidUID
		) = 0;

	/**	Creates a new process RGB color swatch in the workspacePtr using the passed in values.
		@param workspacePtr the workspace of the new process color swatch.
		@param swatchName specifies the new swatch name.
		@param redVal specifies the red component value.
		@param greenVal specifies the green component value.
		@param blueVal specifies the blue component value.
		@param colorGroup the UID of the parent color group for the new process color swatch.
		@return the new process color swatch UID.
	*/
	virtual UID CreateProcessRGBSwatch 
		(
			IWorkspace* workspacePtr, 
			const PMString& swatchName, 
			const PMReal& redVal, 
			const PMReal& greenVal,
			const PMReal& blueVal,
			const UID& colorGroup = kInvalidUID
		) = 0;

	/**	Creates a new process Lab color swatch in the workspacePtr using the passed in values.
		@param workspacePtr the workspace of the new process color swatch.
		@param swatchName specifies the new swatch name.
		@param LVal specifies the L component value.
		@param aVal specifies the A component value.
		@param bVal specifies the B component value.
		@param colorGroup the UID of the parent color group for the new process color swatch.
		@return the new process color swatch UID.
	*/
	virtual UID CreateProcessLABSwatch 
		(
			IWorkspace* workspacePtr, 
			const PMString& swatchName, 
			const PMReal& LVal, 
			const PMReal& aVal,
			const PMReal& bVal,
			const UID& colorGroup = kInvalidUID
		) = 0;

    /**    Creates a new process HSB color swatch in the workspacePtr using the passed in values.
        @param workspacePtr the workspace of the new process color swatch.
        @param swatchName specifies the new swatch name.
        @param hueVal specifies the hue component value.
        @param satVal specifies the saturation component value.
        @param briVal specifies the brightness component value.
        @param colorGroup the UID of the parent color group for the new process color swatch.
        @return the new process color swatch UID.
    */
    virtual UID CreateProcessHSBSwatch
        (
            IWorkspace* workspacePtr,
            const PMString& swatchName,
            const PMReal& hueVal,
            const PMReal& satVal,
            const PMReal& briVal,
            const UID& colorGroup = kInvalidUID
        ) = 0;
	/**	Creates a new spot CMYK color swatch in the workspacePtr using the passed in values.
		@param workspacePtr the workspace of the new spot color swatch.
		@param swatchName specifies the new swatch name.
		@param cyanVal specifies the cyan component value.
		@param magentaVal specifies the magenta component value.
		@param yellowVal specifies the yellow component value.
		@param blackVal specifies the black component value.
		@param colorGroup the UID of the parent color group for the new spot color swatch.
		@return the new spot color swatch UID.
	*/
	virtual UID CreateSpotCMYKSwatch 
		(
			IWorkspace* workspacePtr, 
			const PMString& swatchName, 
			const PMReal& cyanVal, 
			const PMReal& magentaVal,
			const PMReal& yellowVal,
			const PMReal& blackVal,
			const UID& colorGroup = kInvalidUID
		) = 0;

	/**	Creates a new spot RGB color swatch in the workspacePtr using the passed in values.
		@param workspacePtr the workspace of the new spot color swatch.
		@param swatchName specifies the new swatch name.
		@param redVal specifies the red component value.
		@param greenVal specifies the green component value.
		@param blueVal specifies the blue component value.
		@param colorGroup the UID of the parent color group for the new spot color swatch.
		@return the new spot color swatch UID.
	*/
	virtual UID CreateSpotRGBSwatch 
		(
			IWorkspace* workspacePtr, 
			const PMString& swatchName, 
			const PMReal& redVal, 
			const PMReal& greenVal,
			const PMReal& blueVal,
			const UID& colorGroup = kInvalidUID
		) = 0;

	/**	Creates a new spot Lab color swatch in the workspacePtr using the passed in values.
		@param workspacePtr the workspace of the new spot color swatch.
		@param swatchName specifies the new swatch name.
		@param LVal specifies the L component value.
		@param aVal specifies the A component value.
		@param bVal specifies the B component value.
		@param colorGroup the UID of the parent color group for the new spot color swatch.
		@return the new spot color swatch UID.
	*/
	virtual UID CreateSpotLABSwatch 
		(
			IWorkspace* workspacePtr, 
			const PMString& swatchName, 
			const PMReal& LVal, 
			const PMReal& aVal,
			const PMReal& bVal,
			const UID& colorGroup = kInvalidUID
		) = 0;
    
    /**    Creates a new spot HSB color swatch in the workspacePtr using the passed in values.
        @param workspacePtr the workspace of the new spot color swatch.
        @param swatchName specifies the new swatch name.
        @param hueVal specifies the hue component value.
        @param satVal specifies the saturation component value.
        @param briVal specifies the brightness component value.
        @param colorGroup the UID of the parent color group for the new spot color swatch.
        @return the new spot color swatch UID.
    */
    virtual UID CreateSpotHSBSwatch
        (
            IWorkspace* workspacePtr,
            const PMString& swatchName,
            const PMReal& hueVal,
            const PMReal& satVal,
            const PMReal& briVal,
            const UID& colorGroup = kInvalidUID
        ) = 0;

	/**	Process a command to replace the definition of color swatch 1 with the definition from color swatch 2.
		Swatch 1 and 2 do not have to be in the same data base. However swatch 1 and 2
		must be of the same rendering type.
		@param swatchRef1 the UIDRef of swatch 1.
		@param swatchRef1 the UIDRef of swatch 2.
		@param nFlags a combination of SwatchFlags.
		@return kSuccess if the command is completed successfully or an error code.
		@precondition  rendering class of swatchRef1 == rendering class of swatchRef2.
		@precondition  swatchRef1 is not a mixed ink group parent and/or swatchRef2 is not a mixed ink group parent.
	*/
	virtual ErrorCode ReplaceColorSwatchDefinition (const UIDRef& swatchRef1, const UIDRef& swatchRef2, int32 nFlags = kNoFlags) = 0;
	
	/**	Process a command to replace the gradient swatch 1 with the definition from gradient swatch 2.
		Swatch 1 and 2 do not have to be in the same data base. However swatch 1 and 2
		must be of the same rendering type.
		@param swatchRef1 the UIDRef of swatch 1.
		@param swatchRef1 the UIDRef of swatch 2.
		@return kSuccess if the command is completed successfully.
		@precondition  rendering class of swatchRef1 == rendering class of swatchRef2.
		@precondition  swatchRef1 is not a mixed ink group parent and/or swatchRef2 is not a mixed ink group parent.
	*/
	virtual ErrorCode ReplaceGradientSwatchDefinition(const UIDRef&, const UIDRef&) = 0;

	/**	Reutrn true and the target's color components are sync to the same order as source
		if two rendering objects are mixed ink swatches and they are equivalent.
		They are equivalent if they are exactly equal or if their ink lists contains same inks
		though inks may not appear in the same order and ink contribution data are the same.
		Otherwise, it returns kFalse and newComponents is cleared.
		@param iSrcDB the database of the source mixed ink rendering object.
		@param iTargetDB the database of the source mixed ink rendering object.
		@param iSrcRenderObject the source mixed ink rendering object.
		@param iTargetRenderObject the target mixed ink rendering object.
		@param newComponents the color components of target in the order of source ink list.
		@return kTrue if iSrcRenderObject and iTargetRenderObject are equivalent.
	*/
	virtual bool16 SyncMixedInkSwatchesColorData (IDataBase* iSrcDB, IDataBase* iTargetDB, IRenderingObject* iSrcRenderObject, IRenderingObject* iTargetRenderObject, ColorArray& newComponents) = 0;

	//___________________________________________________________________________________
	
	/**	Reutrn true if the given swatch and tint value already exists in the swatch list.
		@param baseObjectUID the base color swatch UID.
		@param tint the tint value to check.
		@param swatchList specifies the swatch list of the baseObjectUID
		@param matchedRef if not nil, the matched tint swatch UID is returned.
		@return kTrue if a match is found in the swatchList.
	*/
	virtual bool16 TintColorSwatchAlreadyExists( const UID& baseObjectUID, const PMReal& tint, ISwatchList* swatchList = nil, UIDRef* matchedRef = nil ) = 0;

	/**	Reutrn true if the given swatch is a global swatch. A global swatch is a named and visible swatch.
		@param iDataBase the database of the swatch UID to check.
		@param swatchUID the swatch UID to check.
		@return kTrue if specified swatch is a global swatch.
	*/
	virtual bool16 SwatchIsGlobalSwatch (IDataBase* iDataBase, UID swatchUID) = 0;
	
	/**	Return true if the given swatch is visible in the list.
		@param iDataBase the database of the swatch UID to check.
		@param swatchUID the swatch UID to check.
		@return kTrue if specified swatch is a visible swatch.
	*/
	virtual bool16 SwatchIsVisible (IDataBase* iDataBase, UID swatchUID) = 0;

	/**	Return true if the given swatch is locked. A swatch is locked if it cannot be deleted.
		@param iDataBase the database of the swatch UID to check.
		@param swatchUID the swatch UID to check.
		@return kTrue if specified swatch is locked.
	*/
	virtual bool16 SwatchIsLocked (IDataBase*, UID) = 0;

	/**	Return the specified swatch's aliase swatch UID. If the swatch is not aliased, then
		kInvalidUID is returned.
		@param iDataBase the database of the swatch UID to check.
		@param swatchUID the swatch UID to check.
		@return the swatch's alias swatch UID.
	*/
	virtual UID GetSwatchAliasUID (IDataBase*, UID) = 0;

	/**	Return true if the given swatch is one of reserved Cyan, Magenta, Yellow, Paper, Black, Registration, or None.
		@param iDataBase the database of the swatch UID to check.
		@param swatchUID the swatch UID to check.
		@return kTrue if swatch is a reserved swatch.
	*/
	virtual bool16 SwatchIsReservedSwatch (IDataBase*, UID) = 0;

	/** Return true if the given swatch is a spot color swatch.
		Will also return kTrue if tint swatch is a tint of a spot.
		@param swatchRef the UIDRef of the swatch to check.
		@return kTrue if swatch is a spot color swatch.
	*/
	virtual bool16 SwatchIsSpotColorSwatch(const UIDRef& swatchRef) = 0;

	/**	Return true if the given swatch is based on another swatch. For example, a tint swatch is
		based on another swatch.
		@param swatchRef the UIDRef of the swatch to check.
		@return kTrue if swatch based on another swatch.
	*/
	virtual bool16 SwatchIsBasedOnSwatch(const UIDRef& swatchRef) = 0;

	/**	Return true if the given swatch is a tint swatch swatch.
		@param swatchRef the UIDRef of the swatch to check.
		@param pBaseUID the base color UID the tint swatch is based on.
		@return kTrue if swatch is a tint swatch.
	*/
	virtual bool16 SwatchIsTintSwatch(const UIDRef& swatchRef, UID* pBaseUID = nil) = 0;

	/**	Return true if the given swatch is a mixed ink swatch.
		@param swatchRef the UIDRef of the swatch to check.
		@param pParentUID the mixed ink group parent UID if the swatch is part of the mixed ink group.
		@return kTrue if swatch is a mixed ink swatch.
	*/
	virtual bool16 SwatchIsMixedInkSwatch(const UIDRef& swatchRef, UID* pParentUID = nil) = 0;

	/**	Return true if the given swatch is a mixed ink group parent swatch.
		@param swatchRef the UIDRef of the swatch to check.
		@return kTrue if swatch is a mixed ink group parent swatch.
	*/
	virtual bool16 SwatchIsMixedInkGroupParent(const UIDRef& swatchRef) = 0;

	/**	Return true if the given spot swatch has been converted to process. It will also return true
		if swatchRef is not spot, but a process swatch.
		@param swatchRef the UIDRef of the swatch to check.
		@return kTrue if swatch is process color swatch or converted to process color swatch.
	*/
	virtual bool16 SpotSwatchIsConvertedToProcess(const UIDRef& swatchRef) = 0;

	/**	Return the swatch type of the specified swatch. If a tint swatch is based on a
		mixed ink swatch, the swatch type returned will be kTintColor and the base UID
		will be the mixed ink swatch.
		@param swatchRef the UIDRef of the swatch to check.
		@param pBaseUID the base color UID if the swatch is based on another swatch.
		@return the swatch type.
	*/
	virtual SwatchType GetSwatchType (const UIDRef& swatchRef, UID* pBaseUID = nil) = 0;

	/**	Return swatch's base object UID. UID is kInvalidUID if swatch is not based on another swatch. 
		@param swatchRef the UIDRef of the swatch to check.
		@return swatch's base UID.
	*/
	virtual UID GetBaseObjectUIDFromSwatch(const UIDRef& swatchRef) = 0;

	/**	Return the None swatch UID of the specified database. 
		@param iDataBase the database to check.
		@return None swatch UID or kInvalidUID if does not exist.
	*/
	virtual UID GetNoneSwatchUID ( IDataBase* iDataBase ) = 0;

	/**	Return the Black swatch UID of the specified database. 
		@param iDataBase the database to check.
		@return Black swatch UID or kInvalidUID if does not exist.
	*/
	virtual UID GetBlackSwatchUID ( IDataBase* iDataBase ) = 0;

	/**	Return the Paper swatch UID of the specified database. 
		@param iDataBase the database to check.
		@return Paper swatch UID or kInvalidUID if does not exist.
	*/
	virtual UID GetPaperSwatchUID ( IDataBase* iDataBase ) = 0;

	/**	Return the Registration swatch UID of the specified database. 
		@param iDataBase the database to check.
		@return Registration swatch UID or kInvalidUID if does not exist.
	*/
	virtual UID GetRegistrationSwatchUID ( IDataBase* iDataBase ) = 0;

	/**	Get the named swatch's UID from the specified database.
		If database is nil, it returns the named swatch UID in the current active workspace.
		@param name the swatch name.
		@param iDataBase the database to check.
		@return swatch UID of the specified swatch name.
	*/
	virtual UID GetNamedSwatch(const PMString& swatchName, IDataBase* iDataBase = nil) = 0;
	
	/**	Given the UIDRef, return the swatch name.
		@param iDataBase the database to check.
		@param swatchUID the swatch UID.
		@return the swatch name of the specified swatch.
	*/
	virtual PMString	GetSwatchName (IDataBase* iDataBase, UID swatchUID) = 0;

	/** Return a list of tint swatch UID that is based on the specified color swatch UID
		@param iDataBase the database of the specified swatch UID.
		@param swatchUID specifies the swatch
		@return a list of tintg swatch UID that is based on the specified swatch.
	*/
	virtual UIDList GetAllTintSwatchUIDListOfSwatch (IDataBase* iDataBase, UID swatchUID) = 0;
	
	//___________________________________________________________________________________

	/**	Return an action code, a compare result, and a matching UIDRef if one is found based on the swatch's compare result.
		@param swatchRef the source swatch to check.
		@param swatchList the target swatch list to check.
		@param doAlertUser if kTrue, a warning alert is shown when there's conflict. 
		A conflict exists if two swatches have same name but different data.
		@param dupPref specifies the duplicate preference.
		@param matchedRef returns a UIDRef of the matching swatch found in the target swatchList.
		@param resultCode returns the compare result code.
	    @return a preferred action code.
	*/
	virtual ISwatchUtils::ActionCode CheckSwatchBeforeCopy(const UIDRef& swatchRef, ISwatchList* swatchList, bool16 doAlertUser, ISwatchUtils::DuplicatePref dupPref, UIDRef& matchedRef, ISwatchUtils::CompareCode& resultCode) = 0;

	//___________________________________________________________________________________
	//	Following are utility functions that help deal with swatch conflict resolution.
	//___________________________________________________________________________________
	/**	A utility function to synchronize tint swatches of aliased swatch from old alias to new alias.
		@param swatchList the target swatch list.
		@param swatchRef the original swatch alias UID.
		@param newUID the new swatch alias UID.
	*/
	virtual void SynchronizeTintsOfAliasedSwatchOldAndNew (ISwatchList* iSwatchList, const UIDRef& swatchRef, UID newUID) = 0;
	
	/**	A utility function to synchronize aliased swatch's ink data from old to new.
		@param swatchList the target swatch list.
		@param swatchRef the original swatch alias UID.
		@param newUID the new swatch alias UID.
	*/
	virtual void SynchronizeAliasedSwatchInkDataOldAndNew (ISwatchList* iSwatchList, const UIDRef& swatchRef, UID newUID) = 0;

	/**	Process a command to create a swatch alias
		@param swatchList the target swatch list.
		@param swatchUID the swatch to be aliased
		@param aliasSwatchUID the swatch UID that swatchUID will be aliased to.
	*/
	virtual void ProcessMakeSwatchAliasCommand (ISwatchList* iSwatchList, UID swatchUID, UID aliasSwatchUID) = 0;

	/**	Handle the user actions resulting from a pantone color swatch alternate match in the target swatch list.
		Both source and matched swatch must be a color.
		@param srcSwatchRef the source (original) panetone swatch.
		@param iSwatchList the target swatch list.
		@param altSwatchRef the matched alternate swatch UIDRef found in swatchList.
		@param actionCode the desired action code.
		@param resultCode specifies the result code. This must be kAlternatePantoneName.
		@return the new UID in the target database.
		@precondition pantone conflicts must exist, i.e. resultCode must be kAlternatePantoneName.
	*/
	virtual UID HandleAlternateSwatchMatch (const UIDRef& srcSwatchRef, ISwatchList* iSwatchList, const UIDRef& altSwatchRef, ISwatchUtils::ActionCode actionCode, ISwatchUtils::CompareCode resultCode) = 0;

	/**	Handle the user actions resulting from a pantone color swatch alternate match in the target swatch list.
		In this version, the source must be a color swatch specified by its swatch name, color space, color values, 
		ink type, and whether or not it must be locked.
		@param iSwatchList the target swatch list.
		@param altSwatchRef the matched alternate swatch UIDRef found in swatchList.
		@param swatchName the source (original) panetone swatch name.
		@param alternateSwatchName the alternate panetone swatch name.
		@param colorspace the source (original) panetone swatch color space.
		@param colorArray the source (original) panetone swatch color value.
		@param inkType the source (original) panetone swatch ink type.
		@param lockedSwatch specified if source swatch is locked.
		@param actionCode the desired action code.
		@return the new UID in the target database.
		@precondition pantone conflicts must exist.
	*/
	virtual UID HandleAlternateSwatchMatch (ISwatchList* iSwatchList, const UIDRef& altSwatchRef, const PMString& , const PMString&, int32, const ColorArray&, const IInkData::InkType&, bool16, ISwatchUtils::ActionCode) = 0;
	
	/**	Bring up a duplicate spot color swatch alert.
		@return kCancelAction if user choose to not duplicate.
	*/
	virtual ISwatchUtils::ActionCode CancelDuplicateSpotColorSwatchAlert() = 0;	//always returns kCancelAction

	/** Bring up a alert indicating duplicating a color swatch.
		@param compareResult specifies either swatch compare is kSameNameSameData or kSameNameDiffData.
		@param swatchName specifies the swatch name.
		@param isSpot is kTrue if swatch is a spot color swatch.
		@param allowCancel if kTrue, the allow the action to be cancelled.
		@param resultCode specifies the result code. This must be kAlternatePantoneName.
		@return the desired action code. This is one of kKeepOriginalSwatch, kAddThisSwatch, or kCancelAction.
		kAddThisSwatch,
	*/
	virtual ISwatchUtils::ActionCode InvokeSameSwatchAlert( const ISwatchUtils::CompareCode& compareResult, PMString swatchName, bool16 isSpot = kFalse, bool16 allowCancel = kTrue, PMString alternateName = PMString("") ) = 0;

	/** This utility encapsulates the tricky business of taking spot plates coming from placed
		content (PDF, EPS, images) and matching up to or creating new swatches in the document.
		Specifically it does one of the following depending on the name of the spot.

		*	If the spot name matches a reserved ink name it simply returns the UID of the reserved ink.
		
		*	If the spot name matches an existing spot color in the document exactly then it locks that
			spot and returns its UID.  No alert is given if the definition doesn't match, per the
			current spot functional specification.  The existing document definition always wins.
		
		*	If the spot name matches a book color *and* an existing swatch in the document also matches
			the same book color (e.g., one is PANTONE 185 CVC and the other is PANTONE 185 C) then 
			the new spot is aliased to the existing spot and the existing spot is locked.  So, again,
			the document definition always wins if it exists.
		
		*	If the spot name matches a current book color but that color (or a name variant) doesn't 
			exist in the document, the book definition is added to the swatch list and its UID is
			returned.  Note that the color space/array coming is irrelevant in this case; the book
			definition always wins (per the spot spec).  However, the name from the linked content 
			is used even if it differs from the book name (e.g., if the placed content uses PANTONE
			185 CVC, it will retain that name, but the values will come from the book).
		
		*	If the spot name doesn't match any existing document colors, nor a book color (current or
			legacy) then it's a custom spot.  A new swatch is added to the swatch list with the name
			and color values specified and that swatch is locked.  Its UID is returned.

		@param iSwatchList The swatch list to which swatches are compared and/or added.
		@param swatchName The name of the swatch as specified in the placed content.
		@param colorSpace The kPMCs* colorspace of the spot's alternate.
		@param colorArray The array of color values in spot alt space.
		@return The UID of the resulting swatch in the swatch list, per the rules described above.
	*/

	virtual UID HandlePlacedContentSpotSwatch
			(
				ISwatchList* iSwatchList,
				const PMString& colorName,
				int32 colorSpace,
				const ColorArray& colorArray
			) = 0;

	//___________________________________________________________________________________
	//	Library swatches to K2 swatches conversion
	//___________________________________________________________________________________
	/**	Convert a swatch library color swatch to an InDesign color swatch.
		@param libSwatchRef specifies the UIDRef of the library swatch.
		@param iDestinationWS specifies the target workspace to create the new InDesign swatch.
		@param doCheckForConflicts is kTrue, if CheckSwatchBeforeCopy() should be called.
		@param doUpdateGfxState is kTrue, if the graphic state should be updated with the new swatch.
		@param nSwatchFlags a combination of SwatchFlags.
		@param colorGroup the UID of the parent color group for the new InDesign color swatch.
		@return UIDRef of the new InDesign color swatch.
	*/
	virtual UIDRef	ConvertLibraryColorSwatchToK2Swatch
		(
		const UIDRef&	libSwatchRef,
		IWorkspace*		iDestinationWS,
		bool16			doCheckForConflicts,
		bool16			doUpdateGfxState,
		int32           nSwatchFlags = kNoFlags,
		const UID&      colorGroup = kInvalidUID
		) = 0;
		
	/**	Convert a swatch library gradient swatch to an InDesign gradient swatch.
		@param libSwatchRef specifies the UIDRef of the library swatch.
		@param iDestinationWS specifies the target workspace to create the new InDesign swatch.
		@param pNewColorUIDList returns the list of new color UID created for this gradient swatch.
		@param doCheckForConflicts is kTrue, if CheckSwatchBeforeCopy() should be called.
		@param doUpdateGfxState is kTrue, if the graphic state should be updated with the new swatch.
		@return UIDRef of the new InDesign gradient swatch.
	*/
	virtual UIDRef	ConvertLibraryGradientSwatchToK2Swatch
		(
		const UIDRef&	libSwatchRef,
		IWorkspace*		iDestinationWS,
		UIDList*		pNewColorUIDList,
		bool16			doCheckForConflicts,
		bool16			doUpdateGfxState
		) = 0;


	/**	Add a swatch from the Adobe swatchbook to the specified swatch list.
		@param iSwatchList is the swatch list the swatch is being added to.
		@param bookRef is the swatchbook from swatch the swatch is being added.
		@param swatchIndex is the index in the swatchbook.
		@param swatchName if not empty, set the new swatch with this name. Otherwise leave swatch name as is.
		@param doLockSwatch if set to kTrue, the new swatch is locked.
		@param colorGroup the UID of the parent color group for the new swatch.
		@return UID of the new swatch.
	*/
	virtual UID	AddBookSwatch
		(
		ISwatchList*	iSwatchList,
		const UIDRef&	bookRef,
		int32			swatchIndex,
		const PMString&	swatchName,
		bool16			doLockSwatch,
		const UID& colorGroup = kInvalidUID
		) = 0;

	//___________________________________________________________________________________
	//	Panetone library swatch name helper
	//___________________________________________________________________________________
	/**	Returns the alternate PANTONE swatch name corresponding to the specified swatch name.
		@param swatchName the PANTONE swatch name to check.
		@return the alternate PANTONE swatch name. Returns nil, if there's no alternate name.
	*/
	virtual PMString	GetAlternatePanetoneSwatchName (const PMString& swatchName) = 0;
	
	/**	Find the alternate swatch in the specified target swatch list.
		@param iSwatchList the target swatch list.
		@param swatchName the PANTONE swatch name to check.
		@param altSwatchRef returns the alternate swatch UIDRef found. This is UIDRef::gNull if no alternate found.
		@param pAlterateName returns the alternate swatch name if not nil.
	*/
	virtual ISwatchUtils::SwatchNameMatchType	FindAlternateSwatchName (ISwatchList* iSwatchList, const PMString& swatchName, UIDRef& altSwatchRef, PMString* pAlterateName = nil) = 0;
	
	/**	Get the alternate PANTONE swatch name's suffix string
		@param pantoneSuffixString specifies the PANTONE swatch name suffix string to check.
		@return the alternate PANTONE swatch name's suffix string. It is a empty string if no alternate.
	*/
	virtual PMString	GetAlternatePanetoneSwatchNameSuffix (const PMString& pantoneSuffixString) = 0;

	/**	Convert swatches' profiles. Only RGB and CMYK color spaces are converted.
		@param pSwatchList the target swatch list.
		@param listSrcColors the list of source color swatches.
		@param listDstColors the list of corresponding target color swatches.
		@param pDstDB the target database.
		@return kSuccess if successful other wise returns an error code.
	*/
	virtual ErrorCode  ConvertSwatchProfile( ISwatchList* pSwatchList, const UIDList& listSrcColors, UIDList& listDstColors, IDataBase* pDstDB ) = 0;
	
	/**	Check profile before copy to determine if swatch profiles should be converted.
		@param inActionCode the initial action code.
		@param inDoAlertUser kTrue if allow to put up an user alert dialog.
		@param inSrcSwatchRef the source swatch to check.
		@param inDstSwatchList the target swatch list.
		@param refMatched the matching swatch UIDRef found in the target swatch list.
		@param bAllowCancel kTrue if user can cancel.
		@return an ActionCode based on an action code and user choice.
	*/
	virtual ActionCode CheckProfilesBeforeCopy(ActionCode inActionCode, bool16 inDoAlertUser, const UIDRef &inSrcSwatchRef, ISwatchList *inDstSwatchList, UIDRef& refMatched, bool16 bAllowCancel = kTrue) = 0;


	/** Return kTrue if swatchUID is used in the database.
		@param iDataBase is the database.
		@param swatchUID is the swatchUID to test.
		@param usageType is the type of references wanted for this swatch.
		@return true if swatch is used in the manner specified by usageType.
	*/
	virtual bool16 SwatchIsUsed (IDataBase* iDataBase, UID swatchUID, ISwatchUtils::SwatchUsageType usageType) = 0;

	/** Return a list of swatch UIDs that are used in the database.
		@param iDataBase is the database.
		@param referencedList the list containing the used swatch UIDs.
		@param unusedList the list containing the used swatch UIDs.
		@param includeVisibleSwatches if true visible swatches are included in the referencedList and the unusedList. If false, visible
		swatches are excluded.
		@param includeUnnamedSwatches if true unnamed swatches are included in the referencedList and the unusedList. If false, unnamed
		swatches are excluded.
		If both includeVisibleSwatches and includeUnnamedSwatches are true, all swatches are included. If both are false, then nothing
		is don, i.e. both referencedList and unusedList are returned as empty lists.
		@param usageType is the type of references wanted.
		@return the list of swatch UIDs referenced.
	*/
	virtual void GetSwatchReferences (IDataBase* iDataBase, UIDList& referencedList, UIDList& unusedList, bool16 includeVisibleSwatches, bool16 includeUnnamedSwatches, ISwatchUtils::SwatchUsageType usageType) = 0;

	/** Return a list of swatch UIDs that are referenced by the specified object.
		@param objectUIDRef is the object the swatch references are being returned.
		@param referencedList the list containing the used swatch UIDs.
		@return the list of swatch UIDs referenced.
	*/
	virtual void GetSwatchReferencesByObject (const UIDRef& objectUIDRef, UIDList& referencedList) = 0;
};


#endif	// __ISwatchUtils__
