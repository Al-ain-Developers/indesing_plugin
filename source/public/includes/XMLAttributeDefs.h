//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XMLAttributeDefs.h $
//  
//  Owner: Lin Xia
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
#ifndef __XMLAttributeDefs__
#define __XMLAttributeDefs__

/**
specify the table namespace prefix
*/
#define kTablePrefix "aid"

/**
specify the URI we are interested in
*/
#define k_indesign_namespaceString4 "http://ns.adobe.com/AdobeInDesign/4.0/"
#define k_indesign_namespaceString5 "http://ns.adobe.com/AdobeInDesign/5.0/"

/**
specify a table or cell element
acceptable values of this attribute are kAttrValueTabl for a table element or kAttrCellCell for a cell element
*/
#define			kTableAttr				"table"				
#define			kAttrValueTable			"table"				
#define			kAttrValueCell			"cell"

/**
specify the tag preference of the table
value of this attribute should be kTableTagByRow or kTableTagByColumn
optional attribute, default value is "none"
*/
#define			kTableTagPreferenceAttr "ttagpref"
#define			kTableTagByRow			"row"
#define			kTableTagByColumn		"column"

/**
specify the number of rows in the table
value of this attribute should be int
optional attribute, default value is 1
the value should be greater than the sum of kTableHeaderAttr and kTableFooterAttr
*/
#define			kTableHeightAttr		"trows"		

/**
specify the number of columns in the table
value of this attribute should be int
optional attribute, default value is 1
*/
#define			kTableWidthAttr			"tcols"

/**
specify a cell that is in a header row
value of this attribute is ignored
*/
#define			kTableHeaderAttr	"theader"		

/**
specify a cell that is in a footer row
value of this attribute is ignored
*/
#define			kTableFooterAttr	"tfooter"		

/**
specify the total number of rows in the table cell,
this includes header, body, and footer
value of this attribute should be int
optional attribute, default value is 1
*/
#define			kTableCellHeightAttr	"crows"

/**
specify the number of columns in the table cell
value of this attribute should be int
optional attribute, default value is 1
*/
#define			kTableCellWidthAttr		"ccols"

/**
speciy the column width of a one-column cell
optional attribute, ignored for cells with more than one columns
value of this attribute should be real number
*/
#define			kCellColumnWidthAttr	"ccolwidth"

/**
For Internal Use Only
specify the format of a table element
the only acceptable values of this attribute kAttrValueCALS 
*/
#define			kTableFormatAttr		"tformat"				
#define			kAttrValueCALS			"CALS"				


#endif //__XMLAttributeDefs__