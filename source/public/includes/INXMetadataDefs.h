//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/INXMetadataDefs.h $
//  
//  Owner: Gang Xiao
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
#ifndef __INXMETADATADEFS__
#define __INXMETADATADEFS__

#include "ScriptingDefs.h"
#include "FormScriptingDefs.h"

#include "GenericID.h"
#include "SplineID.h"

//
// Please make sure any ids you add are unique !!!
//

enum INXMetadataKeys
{
	// This key tells the INX Core that two elements are considered
	// to be the same object if their values for the specified property
	// are equal. The associated metadata value is the PropID to compare.
	// If several properties must match, use multiple key-value pairs.
	// Example:
	//    m_INXMatchProperty, Int32Value(p_Name)
	m_INXMatchProperty =					'iMPr',

	// This key tells the INX Core that two elements are considered
	// to be the same object if their values for all properties are equal
	// and their child elements compare as equal. 
	// The associated metadata value is unused at this time.
	// Example:
	//    m_INXMatchPropertiesAndChildren, NoValue
	m_INXMatchPropertiesAndChildren =		'iMPC',

	// This key tells the INX core to use any available object when trying
	// to match the "same" object. For example, when searching for a Spread,
	// any available Spread will do.
	// There is no metadata value for this key.
	// Example:
	//    m_INXMatchAvailable, NoValue
	m_INXMatchAvailable =					'iMAv',

	// This key is used to exclude child objects of a particular type.
	// Subclasses of the specified type are also excluded. The type to
	// exclude is specified as the metadata value. So, if you exclude children
	// of type "page item", you eliminate *all* types of page items. To be more
	// descriminating, list specific page item types instead of the base class.
	// Example:
	//    m_INXExcludeChild, Int32Value(c_Text)
	m_INXExcludeChild =						'iExC',

	// This key is used to refine the effect of m_INXExcludeChild and should
	// appear after it. It is used to "put back" child types that were excluded.
	// This is useful if you want to exclude all subclasses of some base class
	// except for a few specific subclasses.
	// Example:
	//    m_INXExcludeChild, Int32Value(c_Text)
	//    m_INXIncludeChild, Int32Value(c_TextStyleRange)
	m_INXIncludeChild =						'iInC',

	// During INX export, we sometimes want to suppress all child objects that are
	// "Story children". This key is used to tell the INX Core to treat the specified
	// class as if it was a Story.
	// There is no metadata value for this key.
	// Example:
	//    m_INXTreatAsStoryChild, NoValue
	m_INXTreatAsStoryChild =				'iTaS',

	// During INX export, we sometimes want to suppress all child objects that are
	// "Story children". This key is used to tell the INX Core to treat the specified
	// class as if it was a Story.
	// There is no metadata value for this key.
	// Example:
	//    m_INXTreatAsStoryChild, EnumValue(e_RelinkRequiredLink)
	m_INXTreatAsLink =						'iTaL',
	
	// During INX import, we sometimes need to create a specialized subclass of ImportInfo
	// to handle the processing of elements with special needs. Because of nature of C++,
	// we cannot simply provide a class name as a metadata value. Instead, we specify a "token"
	// that represents the class (see the INXMetadataImportClass enum, below). This token is
	// passed via IINXImportPolicy to the client, and an object of the appropriate type
	// is returned.
	// Example:
	//     m_INXImportClass, EnumValue(e_TextContainerImportClass)
	m_INXImportClass =						'iICl',
	//	   m_INXExpandedImportClass, EnumValue(e_TextContainerImportClass)
	m_INXExpandedImportClass =			'iIEC',

	// Certain types of objects and properties cannot use the "defaults cache" when
	// initializing property values during INX import. This marker can be placed on
	// either an object (rendering the entire object type un-cachable), or on an
	// individual property.
	// Example:
	//     m_NoDefaultsCache, NoValue
	m_NoDefaultsCache =						'iNDC',

	// When properties are cached, we compare values upon import in the debug build
	// in order to make sure that caching is working as expected. Some properties
	// generate a false negative to this test.
	// Example:
	//     m_INXIgnoreDefaultValueCheck, NoValue
	m_INXIgnoreDefaultValueCheck =			'iDVC',
	
	// During INX export, we sometimes need to specify special handling for
	// certain properties. The common case is p_Contents.
	// See INXMetadataDataTreatment for details.
	// Example:
	//     m_INXDataTreatment, EnumValue(e_DataTreatmentCDATA)
	m_INXDataTreatment =					'iDTr',
	
	// During snippet import, this metadata is to tell core whether to set the attributes. 
	// The associated metadata value is the enum of INXMetadataSnippetAttributeImportState.
	// Example:
	//     m_INXSnippetAttrImportState, Int32Value(e_IgnoreElementAttributes)
	m_INXSnippetAttrImportState =			'iAIS',
	
	// In INX output, children of some object script element need to be arranged into 
	// certain order. Order reflects data dependency and is important for correct import.
	// This metadata is put the parent which need to re-order its children. Its value is
	// another metadata ID which is used to retrieve child order value. The order value 
	// is put on child object script element.
	// Example:
	//     m_INXOrderChild,			Int32Value(c_Document),
	m_INXOrderChild =						'inOC',

	// The following metadataID define specific child order for that parent 
	// Example:
	//     m_INXDocumentOrder, RealValue(kLanguageObjectScriptElementPosition),
	m_INXDocumentOrder		=				c_Document,
	m_INXPageItemOrder		=				c_PageItem,
	m_INXGraphicLineOrder	=				c_GraphicLine,
	m_INXRectangleOrder		=				c_Rectangle,
	m_INXOvalOrder			=				c_Oval,
 	m_INXTextFrameOrder		=				c_TextFrame,
 	m_INXPolygonOrder		=				c_Polygon,
	m_INXStoryOrder			=				c_Story,
	m_INXSpreadOrder		=				c_Spread,
	m_INXButtonOrder		=				c_PushButton,
	m_INXMSOStateOrder		=				c_Group,

	// Certain types of objects used as base object only.
	// These objects don't appear in an INX file.
	// One such object is c_XMLItem.
	// Example:
	//     m_INXBaseObjectOnly, NoValue
	m_INXBaseObjectOnly =					'iBOj',

	// This key can only be put on object script element. It tells the INX 
	// core not to write kSelfAttributeID for this object to INX file. When 
	// GetAttributes is called on DOM element, attribute list will not have 
	// self ID if it has this metadata. Self ID still can be accessed by calling
	// GetAttribute with kSelfAttributeID as parameter.
	// There is no metadata value for this key.
	// Example:
	//    m_INXDontOutputSelfID, NoValue
	m_INXDontOutputSelfID =					'iDOS',

	//	Some INX classes can be children of mulitple types of parents. We want to be able
	//	to control the outputting of these classes based on the class of the parent. So
	//	instead of having just 2 metadata directives (m_INXPackageSubFile_Type & m_INXPackageSubFile_Instance)
	//	we will instead follow the paradigm of INX ordering, and if, and only if, any of a parents
	//	children need to use perExport or perInstance metadata, the parent will define the keys that 
	//	the child needs to use. This will alow a child to have multipe metadata directives based on their
	//	parent node.
	// 		Parent's key for perExport sub-file type (value is the key for the child's path value)
	m_INXPackageSubFile_PerExport =					'sfPE',
	// 		Parent's key for perInstance sub-file type (value is the key for the child's path value)
	m_INXPackageSubFile_PerInstance =				'sfPI',
	
	//		Keys for Document children
	m_INXPackageSubFile_DocumentChild_PerExport =	'sDcE',
	m_INXPackageSubFile_DocumentChild_PerInstance =	'sDcI',

	// In INX export, text child objects need to be arranged into correctly nested elements.
	// Child ranks reflects which objects have the higher priority when deciding how to handle
	// objects that have overlapping ranges.
	// Lower ranked objects are broken around overlapping higher ranked objects - 
	// This metadata is put on the object.
	// Lowest value = 0 (meaning object can be arbitrarily broken to fit around any other object)
	// Example would be <Content> objects
	// Highest value = kMaxInt32 - 1 (meaning object will only be broken around XML Elements)
	// XML elements are assumed to never be broken.
	// Example:
	//     m_INXStoryChildRank,			Int32Value(1000),
	m_INXTextChildRank =						'iSCR',


	// End of list.
	enLastINXMetadataKey
};

enum INXMetadataImportClass
{
	e_DefaultContainerImportClass =			'DeCo',
	e_GenericContainerImportClass =			'GnCo',
	e_TextContainerImportClass =			'TxCo',
	e_TextStyleRangeImportClass =			'TxSR',
	e_CharacterObjectImportClass =			'ChOb',
	e_BinaryObjectImportClass =				'BiOb',
	e_LinkedBinaryObjectImportClass =		'LnBi',
	e_TextRangeObjectImportClass =			'TxRg',
	e_XMLElementObjectImportClass =			'XmOb',
	e_ChangeObjectImportClass =				'ChIc',
	e_RootStyleGroupImportClass =			'Rsgc',

	// End of list.
	enLastINXMetadataImportClass
};

enum INXMetadataDataTreatment
{
	// Wrap this property's value in CDATA.
	e_DataTreatmentCDATA =					'dtCD',
	// Preprocess this value, replacing text markers with PIs.
	e_DataTreatmentText =					'dtTx',

	// End of list.
	enLastINXMetadataDataTreatment
};

enum INXMetadataLinkType
{
	e_NoRelinkRequiredLink =				'NRRL',
	e_RelinkRequiredLink =					'RRLn',

	// End of list.
	enLastINXMetadataLinkType
};

enum INXMetadataSnippetAttributeImportState
{
	e_IgnoreElementAttributes =				'saIA',
	e_IgnoreElementAndChildAttributes =		'saIC',
	e_SetElementAndChildAttributes =		'saSC',
	e_SetElementAttributes =				'saS ',

	// End of list.
	enLastINXMetadataSnippetAttributeImportState
};


#endif	//#ifndef __INXMETADATADEFS__

