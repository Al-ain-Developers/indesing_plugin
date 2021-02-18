//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightRuleUI.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightUIID.h"
#include "IPreflightRuleData.h"
#include <map>

class IControlView;
class IDataBase;

/**	This interface sits on a rule boss and provides rule-specific UI entry points.
	If the rule does not have any data parameters, then no implementation is needed.

	If the rule wants to provide its own custom UI to be included in the InDesign preflight profile 
	rule definition dialog, the following methods require implementation. These three methods allows 
	the profile rule definition UI to embed the rule's custom UI, apply data to the UI, and retrieve 
	data from the UI.
		@see CreateCustomUI
		@see ApplyDataToCustomUI
		@see GetDataFromCustomUI

	Note that if custom UI is used then there's no need to implement any of the methods for creating auto generated UI.

	If the rule has simple data parameters and wants the InDesign preflight profile rule definition UI
	to construct automatically InDesign's UI widgets to represent the rule's data parameters, the remaining
	methods described in this class should have some implementation. To auto-generate the UI, we use these data
	and widget mapping:
		boolean data						=> checkbox
		PMReal, longint, shortint, string	=> edit boxes
			within this mapping, the data's UI UnitType specifies the edit box details.
		enumerator, longint, shortint, boolean	can be mapped to a dropdown list.
		kCoordinateGroupWithConstrain & kCoordinateGroupNoConstrain will generate a special group control
			containing n editboxes either with a lock or without a lock contrain. The lock constrain
			will affect all edit units in the group alike.


*/
class IPreflightRuleUI : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRULEUI };

public:
	/** @return whether the rule has any UI, either custom or auto-generated. By "UI" we mean that 
		there are widgets to be shown under the on/off checkbox. The on/off checkbox is always 
		present. If you return true to this method you'll get a triangle next to your rule; if
		not, you won't.
	*/
	virtual bool HasUI() const = 0;

	/**	Get the cutom UI for this rule
		@return The custom IControlView.
	*/
	virtual IControlView* CreateCustomUI (IDataBase* iUIDataBase) const = 0;

	/**	Apply specified rule data to the cutom UI. The custom UI view passed is the same IControlView*
		initially created from CreateCustomUI ().
		@param iCustomUI is the custom UI control view to apply the data to.
		@param iRuleDataToApply is the rule data to apply to the custome UI widget.
		@return true if custom UI handled the data; otherwise false.
	*/
	virtual bool ApplyDataToCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleDataToApply) const = 0;

	/**	Retrieve rule data from the specified cutom UI. The custom UI view passed is the same IControlView*
		initially created from CreateCustomUI ().
		This is called when the main profile rule definition dialog is notified there're rule data changes.
		The custom UI notifies this change by broadcasting on the profile dialog's IDialogController's subject with
		the following arguments:
			theChange = kProfileCustomRuleDataChangeMessage
			protocol IID = IID_IPROFILEDLGUTILS
			changedBy = the custom UI controlview
		In turn, the main rule definition UI will ask for rule data from custom UI with this call.

		@param iCustomUI is the custom UI control view to retrieve the data from. This should match the controlview
		which it originally broadcasted the data change.
		@param iRuleData is the rule data to which the custome UI widget should set the resulting rule data.
		@return true if custom UI handled the data; otherwise false.
	*/

	virtual bool GetDataFromCustomUI (IControlView* iCustomUI, IPreflightRuleData* iRuleData) const = 0;

	/**	Get the description of the specified data key for this rule.
		@param key is the specified data key
		@return the description string.
	*/
	virtual PMString GetDataParemeterDescription (const IPreflightRuleData::Key& key) const = 0;

	/**	This is the UI unit/value type for the data parameters.
		Use kDefaultUnit to indicate that the data value can be represented with
		default type.
	*/
	enum UnitType
	{
		/**	Value is InDesign default type.
		*/
		kDefaultUnit = -1,
		/** Value is in XUnitOfMeasure
		*/
		kXCoordinate,
		/** Value is in XUnitOfMeasure
		*/
		kYCoordinate,
		/** Value is in YUnitOfMeasure
		*/
		kPoints,
		/** Value is in points
		*/
		kTextUnits,
		/** Value is in TextSizeUnitOfMeasure
		*/
		kTextSizeUnits,
		/** Value is in LineUnitOfMeasure
		*/
		kLineUnits,
		
		/**	The followings are special units to help auto generate more complicated UI.
		*/
		/** Value is in percentage
		*/
		kPercent,
		/** Group of coordinate values with contrain
		*/
		kCoordinateGroupWithConstrain,
		/** Group of coordinate values without contrain
		*/
		kCoordinateGroupNoConstrain,
						
		/** Value is a custom enumerator-style type.
			Use GetDataParemeterMapping to provide/access detail about data.
		*/
		kEnumerator,

		/** No value; the parameter is just a static text item.
		*/
		kStaticText
	};
	/**	Get the data parameter unit type. It can be one of type, UnitType defined above.
		@param key is the specified data key
		@return the enum for the unit type.
	*/
	virtual UnitType GetDataParemeterUnitType (const IPreflightRuleData::Key& key) const = 0;

	/**	Get the maximum and minimum range for this data paramete.
		@param key is the specified data key
		@param maxData is the upper limit for this data key
		@param minData is the lower limit for this data key
		@return kTrue is data key has max and min limits; otherwise returns kFalse.
	*/
	virtual bool GetDataParemeterRange (const IPreflightRuleData::Key& key, ScriptData& maxData, ScriptData& minData) const = 0;

	/**	Validate new data value for the specified data key.
		This is needed if data requires more than just validating between max and min range specified by
		method GetDataParemeterRange.
			@see GetDataparameterRange
		@param key is the specified data key
		@param newData is the new data value for this key to validate.
		@param errorString is the error alert string to be shown if there's an error with this new value.
		If the errorString is a custom error string, it should be translated first.
		errorString is empty if there's no error or if alert is not needed.
		@return true if the data value is good.
	*/
	virtual bool ValidateParameterData (const IPreflightRuleData::Key& key, const ScriptData& newData, PMString& errorString) const = 0;

	/**	Get the data value mapping for this data parameter.
		This is used when specifying the data parameter as a dropdown list.
		This mapping allows mapping of integer values to a string for the dropdown list.
		@param key is the specified data key
		@param enumData is the list of enum values for this data key
		@param stringData is the list of strings mapped to the corresponding enum values for this data key
		@return kTrue is data key has mapping; otherwise returns kFalse.
	*/
	virtual bool GetDataParemeterMapping (const IPreflightRuleData::Key& key, ScriptListData& enumData, ScriptListData& stringData) const = 0;
	
	/**	@return the data parameter's root
		This is usually the rule itself.
	*/
	virtual IPreflightRuleData::Key GetDataParamRoot () const = 0;

	/**	Get the specified parameter key's parent. If the rule has a flat list of data parameters, then the parent
		is the root.
		@param key is the parameter key.
		@param keyParent is the parameter's parent.
	*/
	virtual void GetDataParamParent (const IPreflightRuleData::Key& key, IPreflightRuleData::Key& keyParent) const = 0;
	
	/**	Get the specified parameter key's direct child parameter keys.
		@param key is the parameter key.
		@param keyList is the parameter's list of child parameter keys.
		@return true if the specified key has children.
	*/
	virtual bool GetDataParamDirectChildren (const IPreflightRuleData::Key& key, std::vector<IPreflightRuleData::Key>& keyList) const = 0;

};

