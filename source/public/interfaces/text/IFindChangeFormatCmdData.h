//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFindChangeFormatCmdData.h $
//  
//  Owner: EricK
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
#ifndef __FindChangeFormatCmdData__
#define __FindChangeFormatCmdData__

#include "IPMUnknown.h"
#include "ITextWalker.h"
#include "WideString.h"
#include "UIDRef.h"
#include "TextWalkerServiceProviderID.h"
#include "IFindChangeOptions.h"

class AttributeBossList;

/** 
	@ingroup text_find
*/
class IFindChangeFormatCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IFINDCHANGEFORMATCMDDATA };

		/**	
			Returns target database.
			
			@return IDataBase*	Target database for command data.
		 */
		virtual IDataBase* GetTargetDB() = 0;
		/**	
			Returns Applied find attributes.
			
			@return AttributeBossList*	Applied find attributes for command data.
		 */
		virtual const AttributeBossList* GetFindAppliedAttrs() = 0;
		/**	
			Checks if clear find attributes flag is on or off.
			
			@return bool16	kTrue if clear find attributes flag is on, kFalse otherwise.
		 */
		virtual const bool16 AreFindAttrsCleared() = 0;
		/**	
			Returns a list of removed find attributes.
			
			@return K2Vector<ClassID>& 	List of removed find attributes.
		 */
		virtual K2Vector<ClassID>&  GetFindRemovedAttrs() = 0;

		/**	
			Sets target database.
			
			@param db	Target database to set to.
		 */
		virtual void SetTargetDB(IDataBase *db) = 0;
		/**	
			Sets applied find attributes.
			
			@param findList	Find attributes to set to.
		 */
		virtual void ApplyFindAttributeBossList(const AttributeBossList* findList) = 0;
		/**	
			Turns on clear find attributes flag.
		 */
		virtual void ClearFindAttributeBossList() = 0;
		/**	
			Adds the attribute to removed find attributes list.

			@param removeAttribute	Attribute to be added.
		 */
		virtual void RemoveFindAttribute(ClassID removeAttribute) = 0;


		/**	
			Gets applied change attributes list.

			@return AttributeBossList*	list of applied change attributes.
		 */
		virtual const AttributeBossList* GetChangeAppliedAttrs() = 0;
		/**	
			Checks if clear change attributes flag is set or not.

			@return bool16	kTrue if clear change attributes flag is on.
		 */
		virtual const bool16 AreChangeAttrsCleared() = 0;
		
		/**	
			Sets applied change attributes list.

			@param changeList		change attributes to set to.
		 */
		virtual void ApplyChangeAttributeBossList(const AttributeBossList* changeList) = 0;
		/**	
			Turns on clear change attributes flag.
		 */
		virtual void ClearChangeAttributeBossList() = 0;
		/**	
			Adds specified attribute to removed change attributes list.

			@param removeAttribute	Attribute to be added.
		 */
		virtual void RemoveChangeAttribute(ClassID removeAttribute) = 0;
		/**	
			Returns a list of removed change attributes.

			@return K2Vector<ClassID>&	list of removed change attributes.
		 */
		virtual K2Vector<ClassID>&  GetChangeRemovedAttrs() = 0;

		// set styles
		/**	
			Sets find character style.

			@param findCharStyleName	Find character style to set to.
		 */
		virtual void SetFindCharStyle(const UID& findCharStyleName) = 0;
		/**	
			Sets change character style.

			@param changeCharStyleName	change character style to set to.
		 */
		virtual void SetChangeCharStyle(const UID& changeCharStyleName) = 0;
		/**	
			Sets find paragraph style.

			@param findParaStyleName	Find paragraph style to set to.
		 */
		virtual void SetFindParaStyle(const UID& findParaStyleName) = 0;
		/**	
			Sets change paragraph style.

			@param changeParaStyleName	Change paragraph style to set to.
		 */
		virtual void SetChangeParaStyle(const UID& changeParaStyleName) = 0;
		/**	
			Sets find object style.

			@param findObjStyleName	Find object style to set to.
		 */
		virtual void SetObjectFindStyle(const UID& findObjStyleName) = 0;
		/**	
			Sets change object style.

			@param changeObjStyleName	Change object style to set to.
		 */
		virtual void SetObjectChangeStyle(const UID& changeObjStyleName) = 0;

		/**	
			Turns on clear find character style flag.
		 */
		virtual void ClearFindCharStyle() = 0;
		/**	
			Turns on clear change character style flag.
		 */
		virtual void ClearChangeCharStyle() = 0;
		/**	
			Turns on clear find paragraph style flag.
		 */
		virtual void ClearFindParaStyle() = 0;
		/**	
			Turns on clear change paragraph style flag.
		 */
		virtual void ClearChangeParaStyle() = 0;
		/**	
			Turns on clear find object style flag.
		 */
		virtual void ClearObjectFindStyle() = 0;
		/**	
			Turns on clear change object style flag.
		 */
		virtual void ClearObjectChangeStyle() = 0;

		/**	
			Checks if clear find character style flag is turned on.

			@return bool16	kTrue if clear find character style flag is on.
		 */
		virtual bool16 IsFindCharStyleCleared() = 0;
		/**	
			Checks if clear change character style flag is turned on.

			@return bool16	kTrue if clear change character style flag is on.
		 */
		virtual bool16 IsChangeCharStyleCleared() = 0;
		/**	
			Checks if clear find paragraph style flag is turned on.

			@return bool16	kTrue if clear find paragraph style flag is on.
		 */
		virtual bool16 IsFindParaStyleCleared() = 0;
		/**	
			Checks if clear change paragraph style flag is turned on.

			@return bool16	kTrue if clear change paragraph style flag is on.
		 */
		virtual bool16 IsChangeParaStyleCleared() = 0;
		/**	
			Checks if clear find object style flag is turned on.

			@return bool16	kTrue if clear find object style flag is on.
		 */
		virtual bool16 IsObjectFindStyleCleared() = 0;
		/**	
			Checks if clear change object style flag is turned on.

			@return bool16	kTrue if clear change object style flag is on.
		 */
		virtual bool16 IsObjectChangeStyleCleared() = 0;

		// get styles
		/**	
			Gets find character style.

			@return const UID&	Find character style returned.
		 */
		virtual const UID& GetFindCharStyle( ) = 0;
		/**	
			Gets change character style.

			@return const UID&	Change character style returned.
		 */
		virtual const UID& GetChangeCharStyle() = 0;
		/**	
			Gets find paragraph style.

			@return const UID&	Find paragraph style returned.
		 */
		virtual const UID& GetFindParaStyle() = 0;
		/**	
			Gets change paragraph style.

			@return const UID&	Change paragraph style returned.
		 */
		virtual const UID& GetChangeParaStyle() = 0;
		/**	
			Gets find object style.

			@return const UID&	Find object style returned.
		 */
		virtual const UID& GetObjectFindStyle() = 0;
		/**	
			Gets change object style.

			@return const UID&	Change object style returned.
		 */
		virtual const UID& GetObjectChangeStyle() = 0;

		/**	
			Checks if find character style is set.

			@return bool16	kTrue if find character style is set.
		 */
		virtual bool16 IsFindCharStyleSet() = 0;
		/**	
			Checks if change character style is set.

			@return bool16	kTrue if change character style is set.
		 */
		virtual bool16 IsChangeCharStyleSet() = 0;
		/**	
			Checks if find paragraph style is set.

			@return bool16	kTrue if find paragraph style is set.
		 */
		virtual bool16 IsFindParaStyleSet() = 0;
		/**	
			Checks if change paragraph style is set.

			@return bool16	kTrue if change paragraph style is set.
		 */
		virtual bool16 IsChangeParaStyleSet() = 0;
		/**	
			Checks if find object style is set.

			@return bool16	kTrue if find object style is set.
		 */
		virtual bool16 IsObjectFindStyleSet() = 0;
		/**	
			Checks if change object style is set.

			@return bool16	kTrue if change object style is set.
		 */
		virtual bool16 IsObjectChangeStyleSet() = 0;

		/**	
			Gets change XML tag.

			@return PMString&	Change XML tag string.
		 */
        	virtual const PMString& GetChangeXMLTag() = 0;
		/**	
			Sets change XML tag.

			@param changeXMLTag	Change XML tag string.
		 */
		virtual void SetChangeXMLTag(const PMString& changeXMLTag) = 0;
		/**	
			turns on clear change XML tag flag.
		 */
		virtual void ClearChangeXMLTag() = 0;
		/**	
			Checks if change XML tag is set or not.

			@return bool16	kTrue if change XML tag is set.
		 */
		virtual bool16 IsChangeXMLTagSet() = 0;
		/**	
			Checks if clear change XML tag flag is on or off.

			@return bool16	kTrue if clear change XML tag flag is on.
		 */
		virtual bool16 IsChangeXMLTagCleared() = 0;

		/**	
			Gets the change conditions mode.

			@return IFindChangeOptions::ChangeConditionsMode
		 */
        	virtual IFindChangeOptions::ChangeConditionsMode GetChangeConditionsMode() = 0;
		/**	
			Sets the change conditions mode.

			@param chgConditionsMode is of type IFindChangeOptions::ChangeConditionsMode  specifying the mode for change conditions
		 */
		virtual void SetChangeConditionsMode(IFindChangeOptions::ChangeConditionsMode chgConditionsMode) = 0;
		/**	
			Checks if the change conditions mode is set or not.

			@return bool16	kTrue if change conditions mode is set.
		 */
		virtual bool16 IsChangeConditionsModeSet() = 0;
		/**	
			turns on clear change conditions mode flag.
		 */
		virtual void ClearChangeConditionsMode() = 0;
		/**	
			Checks if clear change conditions mode flag is on or off.

			@return bool16	kTrue if clear change conditions mode flag is on.
		 */
		virtual bool16 IsChangeConditionsModeCleared() = 0;
};

#endif
