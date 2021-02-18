//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/onboarding/EndNoteUseCaseConstants.h $
//  
//  Owner: Susmita Singh
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change $
//  ___________________
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright [first year code created] Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#ifndef __EndNoteUseCaseConstants_H__
#define __EndNoteUseCaseConstants_H__

const char* const kEndNoteIAMID = "kEndNoteIAM";

const char* const kEndNoteWorkFlow = "EndNoteWorkFlow";
const char* const kEndNoteIAMClose = "EndNoteIAMClose";
const char* const kEndNoteLearnMore = "EndNoteLearnMore";

const char* const kEndNoteIAMUrl = "./offline/EndNote/endNote.html";
const char* const kEndNoteIAMPos = "bottomleft_0_0";

const char* const kEndNoteIAMCategory				= "Endnotes";
const char* const kEndNoteIAMSubCategory			= "IAM";
const char* const kEndNoteIAMFootnoteInserted		= "seenInsertingFootnotes";
const char* const kEndnoteIAMLongDocOpened			= "seenInsertingLongDoc";
const char* const kEndnoteIAMBookDocOpened			= "seenOpeningBookDoc";
const char* const kEndnoteIAMBookDocAdded			= "seenAddingDocToBook";
const char* const kEndNoteIAMPageInserted			= "seenInserting25thPage";
const char* const kEndNoteIAMLearnMoreCLicked		= "learnMoreClicked";
const char* const kEndNoteIAMCloseButtonClicked		= "closeButtonClicked";
const char* const kEndNoteIAMDocClosed				= "DocumentClosed";
const char* const kEndNoteIAMClosedForcefully		= "EndNoteIAMClosedForcefully";
const char* const kEndNoteIAMClosedOther			= "closedOther";

#define kEndNoteIAMHeight					40

// the border color is #f0f0f0
#define kEndNoteRedBorderValue				0.0f
#define kEndNoteGreenBorderValue			0.0f
#define kEndNoteBlueBorderValue				1.0f
#define kEndNoteAlphaBorderValue			1.0f

#endif // __EndNoteUseCaseConstants_H__