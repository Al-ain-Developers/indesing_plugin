//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpTextAttrHelper.h $
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

#ifndef __SnpTextAttrHelper_H_DEFINED__
#define __SnpTextAttrHelper_H_DEFINED__

class IAttrReport;
						  
namespace SnpTextAttrHelper {

// TODO Align with coding conventions

/**	Gets the specified text attribute from the specified text range.
 *  TextAttrType must have the following:
 * 	(1) enum kDefaultIID
 * 	(2) ValueType typedef 
 * 	(3) Get(ValueType n) method
 * 	@param textRange (in) the text range from which you want to get an 
 * 		attribute.
 * 	@param attrClassID (in) The attribute Class ID to obtain.  
 * 	@param value (out) The attribute value at the text range.
 * 	@return kSuccess on success, kFailure otherwise.
 */
template <class TextAttrType, class _Val_Type>
ErrorCode GetTextAttribute(const InDesign::TextRange& textRange, 
						   const ClassID& attrClassID, 
						   _Val_Type& value)
{
	// Assume failure.
	ErrorCode status = kFailure;
	do 
	{
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data, 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		RangeData rangeData = textRange.GetRange();
		
		// Query the compose scanner to access text attributes
		InterfacePtr<IComposeScanner> composeScanner(textModel, UseDefaultIID());
		if (composeScanner == nil) 
		{
			ASSERT(composeScanner); break;
		}
		
		// Query attribute report interface
		int32 attrLen = 0;
		InterfacePtr<const IAttrReport> attrReport(composeScanner->QueryAttributeAt(rangeData, attrClassID, &attrLen));
		if (attrReport == nil) 
		{
			SNIPLOG("Could not find text attribute with Class ID 0x%X on the selected text!", attrClassID.Get());
			break;
		}
		
		// Query the attribute interface
		InterfacePtr<TextAttrType> attr(attrReport, TextAttrType::kDefaultIID);
		if (attr == nil) 
		{
			SNIPLOG("attr is nil! (Class ID 0x%X)", attrClassID.Get()); 
			break;
		}
		
		// Get the attribute value.
		const _Val_Type tempValue = attr->Get();
		value = tempValue;
		status = kSuccess;
	} while (false);

	return status;
}

/**	Gets the specified font name attribute from the specified 
 * 		text range. This is an execption for GetTextAttribute(), 
 * 		since the ITextAttrFont interface doesn't have a Get() method. 
 * 	@param textRange (in) the text range from which you want to get 
 * 		an attribute.
 * 	@param attrClassID (in) The attribute Class ID to obtain.  
 * 	@param fontName (out) The font name value at the text range.
 * 	@return kSuccess on success, kFailure otherwise.
 */
ErrorCode GetTextFontStyleAttribute(const InDesign::TextRange& textRange, 
									const ClassID& attrClassID, 
									PMString& fontName);

/**	Gets the specified bool16 attribute from the specified 
 * 		text range. This is an execption for GetTextAttribute(), 
 * 		since the bool16 typedef makes the compiler think this is
 * 		the same as int16. 
 * 	@param textRange (in) the text range from which you want to get 
 * 		an attribute.
 * 	@param attrClassID (in) The attribute Class ID to obtain.  
 * 	@param value (out) The attribute value at the text range.
 * 	@return kSuccess on success, kFailure otherwise.
 */
ErrorCode GetTextBool16Attribute(const InDesign::TextRange& textRange, 
								 const ClassID& attrClassID, 
								 bool16& value);

/**	Creates a single specified text attribute on the specified text range.
 *  TextAttrType must have the following:
 * 	(1) enum kDefaultIID
 * 	(2) ValueType typedef 
 * 	(3) Set(ValueType n) method
 * 	@param attrClassID (in) The attribute Class ID to set. 
 * 	@param value (in) The attribute value to set at the text range.
 * 	@return IAttrReport interface, nil if failure, non-nil if success.
 */
template <class TextAttrType, class _Val_Type>
IAttrReport* CreateTextAttribute(const ClassID& attrClassID, 
								 const _Val_Type& value)
{
	IAttrReport* attrReport = nil;
	do {
		// create the text attribute boss
		InterfacePtr<TextAttrType> attr(::CreateObject2<TextAttrType>(attrClassID));
		if (attr == nil)
		{
			ASSERT_FAIL("attr is nil!");
			break;
		}
		// set the attribute value
		const _Val_Type tempValue = value;
		attr->Set(tempValue);

		InterfacePtr<IAttrReport> localAttrReport(attr, UseDefaultIID());
        attrReport = localAttrReport.forget();
	} while (false);
	ASSERT(attrReport);

	return attrReport;
}


/**	Creates the specified font name attribute on the specified text range.
 * 	This is an execption for CreateTextAttribute(), since the ITextAttrFont 
 * 	interface doesn't have a Set() method. 
 * 	@param textRange (in) the text range on which you want to set an attribute.
 * 	@param attrClassID (in) The attribute Class ID to set. 
 * 	@param fontName (in) The font name value to set at the text range.
* 	@return IAttrReport interface, nil if failure, non-nil if success.
 */
IAttrReport* CreateTextFontStyleAttribute(const ClassID& attrClassID, 
										  const PMString& fontName);

/**	Creates the specified bool16 attribute on the specified text range.
 * 	This is an execption for CreateTextAttribute(), since the 
 * 	compiler thinks that the bool16 typedef is the same as int16. 
 * 	@param textRange (in) the text range on which you want to set an attribute.
 * 	@param attrClassID (in) The attribute Class ID to set. 
 * 	@param value (in) The attribute value to set at the text range.
* 	@return IAttrReport interface, nil if failure, non-nil if success.
 */
IAttrReport* CreateTextBool16Attribute(const ClassID& attrClassID, 
									   const bool16& fontName);

/**	Sets a single bool16 text attribute on the specified text range.
 * 	@param textRange (in) the text range on which you want to set an attribute.
 * 	@param attrClassID (in) The attribute Class ID to set. 
 * 	@param value (in) The attribute value to set at the text range.
 * 	@param whichStrand (in, optional) The attribute strand on which 
 * 		you want to set the attribute. Default is kCharAttrStrandBoss.
 * 	@return kSuccess on success, kFailure otherwise.
 */
ErrorCode SetTextBool16Attribute(const InDesign::TextRange& textRange, 
						   const ClassID& attrClassID, 
						   const bool16 value,
						   const ClassID& whichStrand = kCharAttrStrandBoss);

/**	Sets a single int16 text attribute on the specified text range.
 * 	This is made a separate function from SetTextBool16Attribute() 
 * 	since bool16 is a typedef of int16, therefore the compiler doesn't make 
 * 	two separate functions based on a template. 
 * 	@param textRange (in) the text range on which you want to set an attribute.
 * 	@param attrClassID (in) The attribute Class ID to set. 
 * 	@param value (in) The attribute value to set at the text range.
 * 	@param whichStrand (in, optional) The attribute strand on which 
 * 		you want to set the attribute. Default is kCharAttrStrandBoss.
 * 	@return kSuccess on success, kFailure otherwise.
 */
ErrorCode SetTextInt16Attribute(const InDesign::TextRange& textRange, 
						   const ClassID& attrClassID, 
						   const int16 value,
						   const ClassID& whichStrand = kCharAttrStrandBoss);


}; // end namespace SnpTextAttrHelper

#endif // #define __SnpTextAttrHelper_H_DEFINED__

//End, SnpTextAttrHelper.h
