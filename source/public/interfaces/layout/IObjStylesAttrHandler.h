//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IObjStylesAttrHandler.h $
//  
//  Owner: Danielle Darling
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
//  Note:	Handlers the processing of an object style target thru to the model
//  
//  Adobe Patent or Adobe Patent Pending Invention Included Within this File
//  
//========================================================================================

#pragma once

#ifndef __IObjStylesAttrHander__
#define __IObjStylesAttrHander__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "GenericID.h"
#include "IObjectAttributeList.h"	// for ObjectStyleTarget
#include "KeyValuePair.h"
#include "ISelectionExtension.h"		// for ProtocolCollection

//
// Adobe patent application tracking #B098, 
// entitled Design a flexible and extensible way to implement object style, 
// inventors: Danielle Darling, Yeming Liu 
//

typedef KeyValuePair<PMString, PMString> ObjStyleAttrNameValuePair;
typedef K2Vector<ObjStyleAttrNameValuePair> ObjStyleAttrNameValueList;
typedef K2Vector<KeyValuePair<ClassID, ObjStyleAttrNameValueList > > ObjStyleCategoryAttrMap;
typedef K2Vector<KeyValuePair<ClassID, PMString > > ObjStyleCategoryNameMap;

class IObjStylesAttrHandler : public IPMUnknown
	{
	
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IOBJSTYLESATTRHANDLER };

		enum HowToUseCategories { kApplyAllCategories, kApplyOnlyCheckedCategoriesFromSource, kApplyOnlyUncheckedCategoriesInTarget };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**
		 	GetFillStyleTargetFromSelectionTarget: Gets the attributes from the model and fills in the target
		 	@param modelTarget	The csb representing the selection
		 	@param styleTarget	The style target attribute information we are filling
		 	@param ws			The current workspce
		 */
		virtual void			GetFillStyleTargetFromSelectionTarget(const IPMUnknown *modelTarget, IPMUnknown* styleTarget, const IWorkspace *ws) const = 0;
		/**
			SetStyleAttrsInDefaultSelection: Sets the attributes in the default selection state
		 	@param styleTarget	The style target attribute information
		 	@param ws			The current workspce
		 	@param categoriesToOverride	A list of the categories to override
		 */
		virtual void			SetStyleAttrsInDefaultSelection(const IPMUnknown* styleTarget, const IWorkspace *ws, K2Vector<ClassID>& categoriesToOverride) = 0;

		/**
			SetStyleAttrsInUIDList: Sets the attributes in the model and from the target
		 	@param list	The UIDList of the pageitems to change
		 	@param styleTarget	The style target attribute information
		 	@param ws			The current workspce
		 	@param categoriesToOverride	A list of the categories to override
		 */
		virtual void			SetStyleAttrsInUIDList(const UIDList& list, const IPMUnknown* styleTarget, const IWorkspace *ws, K2Vector<ClassID>& categoriesToOverride)= 0;

		/**
			GetDefaultGraphicFrameStyleAttrs: Gets the default attribute and fills in the target for the default graphic frame style
		 	@param styleTarget	The style target attribute information we are filling
		 	@param ws			The current workspce
			@param isRootStyle  The flag indicating if the attrs are for root style or not.
		 */
		virtual void			GetDefaultGraphicFrameStyleAttrs(IPMUnknown* targetBoss, const IWorkspace *ws, const bool16 isRootStyle = kFalse) const = 0;
		/**
			GetDefaultTextFrameStyleAttrs: Gets the default attribute and fills in the target for the default text frame style
		 	@param styleTarget	The style target attribute information we are filling
		 	@param ws			The current workspce
		 */
		virtual void			GetDefaultTextFrameStyleAttrs(IPMUnknown* targetBoss, const IWorkspace *ws) const = 0;

		/**
			GetDefaultFrameGridStyleAttrs: Gets the default attribute and fills in the target for the default frame grid style
		 	@param styleTarget	The style target attribute information we are filling
		 	@param ws			The current workspce
		 */
		virtual void			GetDefaultFrameGridStyleAttrs(IPMUnknown* targetBoss, const IWorkspace *ws) const = 0;
		
		/**
			SetAttrsInTarget: Applies attributes from the first target to the second target based on the override rules
					     	     May not have a full set of attributes when done
		 	@param fillTargetBoss		The style target we are filling
		 	@param applyTargetBoss	The style target attribute information we would like to apply (that we are
		 	@param oldTargetBoss		The style target attribute information from the old style
		 	@param clearOverrides	True if we are clearing overrides (attributes which are different then the current style)
		 */
		virtual void            SetAttrsInTarget(IPMUnknown* fillTargetBoss, const IPMUnknown* applyTargetBoss, const IPMUnknown* oldTargetBoss, bool16 clearOverrides) = 0;

		/**
			GetAttrsFromObjectStyle: Get the attributes from object style and set it into targetBoss
		 	@param objectStyleUIDRef	The style we are pulling from
			@param howToUseCat	The flag indicates if we should ignore categories status when setting attributes, use only the attributes in the checked
									categories or use only the attributes in the unchecked categories (note uses SOURCE cateories)
		 */
		virtual void            GetAttrsFromObjectStyle(const UIDRef& objectStyleUIDRef, IPMUnknown* targetBoss, const HowToUseCategories howToUseCat = kApplyAllCategories) = 0;

		/**
			SetAttrsIntoObjectStyle: Get the attributes from object style and set it into targetBoss
		 	@param objectStyleUIDRef	The style we are putting the attriubtes on
		 	@param styleTarget	The style target attribute information
			@param howToUseCat	The flag indicates if we should ignore categories status when setting attributes, use only the attributes in the checked
									categories or use only the attributes in the unchecked categories (note uses SOURCE cateories)
		 */
		virtual void            SetAttrsIntoObjectStyle(const UIDRef& objectStyleUIDRef, const IPMUnknown* targetBoss, const HowToUseCategories howToUseCat = kApplyAllCategories) = 0;

		/**
			CopyAttrsBetweenObjectStyles: 	Get the attributes from object style and set it into targetBoss
										Convert them if necessary
		 	@param sourceWS			The source style workspce
		 	@param sourceObjectStyle	The source style we are pulling from
		 	@param targetWS			The target style workspce
		 	@param targetObjectStyle	The target style we are pushing the attriubtes to
		 */
		virtual void			CopyAttrsBetweenObjectStyles(const IWorkspace* sourceWS, const UID& sourceObjectStyle, 
														   const IWorkspace* targetWS, const UID& targetObjectStyle) = 0;
		/**
			MergeAttrsIntoObjectStyle: Only adds the attributes which are in the source, but not in the target
		 	@param sourceObjectStyle	The source style we are pulling from
		 	@param targetWS			The target style workspce
		 	@param targetObjectStyle	The source style we are mergring the attriubtes to
		 */
		virtual void			MergeAttrsIntoObjectStyle(const IPMUnknown* sourceObjectStyle, const IWorkspace* targetWS, 
														const UID& targetObjectStyle) = 0;
		
		/**
			IsStyleOverridenBySelection: Checks to see if its portion of the object style is overriden on the selection
		 	@param modelTarget	The csb representing the selection
		 	@param ws			The current workspce
	 		@param style		The boss with the style data
	 		@param categories	Optional parameter to indicate which categories to check for overrides -- when nil we assume all
		*/
		virtual bool16			IsStyleOverridenBySelection(const IPMUnknown* modelTargetBoss, const IWorkspace*ws, const IPMUnknown* style, const K2Vector<ClassID> *categories = nil) const = 0;

		/**
			SelectionContainsMixedOverrides: Checks to see if its portion of the object style is overriden on the selection
		 	@param modelTarget	The csb representing the selection
			@param ws			The current workspce
	 	@param categories	Optional parameter to indicate which categories to check for overrides -- when nil we assume all
		*/
		virtual bool16			SelectionContainsMixedOverrides(const IPMUnknown *modelTarget, const IWorkspace* ws, const K2Vector<ClassID> *categories) const = 0;

		/**
			FillTargetWithAllSupportedAttrCategories: Fills the target with the categories this handler supports
		 	@param styleTarget	The style target attribute information we are filling
		*/
		virtual void			FillTargetWithAllSupportedAttrCategories(IPMUnknown* targetBoss) = 0;

		/**
			Get accepted categories of this handler.
			@return K2Vector<ClassID> the categories that we support in this handler.
		*/
		virtual K2Vector<ClassID>	GetAcceptedCategories() const = 0;

		/**
		*/
		virtual ObjStyleCategoryAttrMap   GetOverrideList(const IPMUnknown* modelTargetBoss, const IWorkspace *ws, const IPMUnknown* target, 
														  const K2Vector<ClassID> *categories, ObjStyleCategoryNameMap& categoryNameMap) const  = 0;

		/**
			Get supported attribute list of the specified target in this handler.
		*/
		virtual ObjStyleCategoryAttrMap   GetAcceptedAttributeList(const IPMUnknown* target, const IWorkspace *ws, ObjStyleCategoryNameMap& categoryNameMap) const = 0;

		/**
			Returns the protocol list for attributes in this style.  This is used by observers so they know when the 
			attributes which may make the object propertes different then the object style change (example -- to observer for overrides to the style)
			@param style			The style to get the protocol list for
			@return K2Vector<PMIID>	List of protocols
		*/
		virtual ProtocolCollection   GetNotificationProtocolList() const = 0;

		/**
			Convert the UID based attributes from source db to target db.
			@param targetDB the targetDB for the new attributes.
			@param iTargetStyleAttributes the source attributes.
			@param targetWS the target workspace for the new attributes.
			@param sourceDb the sourceDB for the source attributes.
		*/
		virtual void	DoAttrConversion(IDataBase* targetDB, IPMUnknown* iTargetStyleAttributes,
				  						 const IWorkspace *targetWS, IDataBase* sourceDB) = 0;

		/**
 			Remove the attributes that are not supported anymore.
 			@param styleUIDRef  The UIDRef of the style.
 		*/
		virtual void	RemoveStyleAttributes(const UIDRef& styleUIDRef) = 0;

		/**
			Returns a list of categories supported by this handler which affect the text defaults
			@return	K2Vector<ClassID>
		*/
		virtual K2Vector<ClassID> GetCategoriesThatAffectTextFrameDefaults() const = 0;
		
		/**
			Returns a list of categories supported by this handler which affect the graphic defaults
		*/
		virtual K2Vector<ClassID> GetCategoriesThatAffectGraphicFrameDefaults() const = 0;

		/**
			Get the category ID which the given attribute belongs to.
			@param attributeID [IN] the given attribute.
			@param categoryClass [OUT] the category that the attribute belongs to.
		*/
		virtual void GetCategoryByAttribute(const ClassID& attributeID, ClassID& categoryClass) const = 0;

		/**
			Apply the attributes which need to be applied only after the page item is added to hierarchy. Relevant for size and position attributes in object styles.

			@param list	The UIDList of the pageitems to change
			@param styleTarget	The style target attribute information
			@param ws			The current workspce
			@param categoriesToOverride	A list of the categories to override
		*/

		virtual void SetStyleAttrsInUIDListPostAddToHierarchy(const UIDList& list, const IPMUnknown* styleTarget, const IWorkspace *ws, K2Vector<ClassID>& categoriesToOverride)= 0;

	};

#endif // __IObjStylesAttrHandler__

