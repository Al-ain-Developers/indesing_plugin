//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/tableattributes/TblAttQueryMutHelper.h $
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

#if !defined(_TBLATTQUERYMUTHELPER__INCLUDED_)
#define _TBLATTQUERYMUTHELPER__INCLUDED_

/**	Class TblAttQueryMutHelper to provide get/set methods for table attributes. Also contains test-helper code.
	@ingroup tableattributes
*/
class TblAttQueryMutHelper  
{
public:
	/** Constructor.
	 */
	TblAttQueryMutHelper();

	/** Destructor.
	*/
	virtual ~TblAttQueryMutHelper();

	/**	Return true if the methods are liable to perform correctly. 
		Helper for test methods.
		Called e.g. from test-harness.
		@return kTrue if in valid state, kFalse otherwise.
	*/
	bool16 IsValidCondition();

	/** Set a cell attribute with given ClassID to the specified real-number.
		@param classID IN The ClassID of the attribute to set.
		@param realParam IN The value of the attribute to set.
	*/
	void SetCellAttributeReal(const ClassID& classID, const PMReal realParam);
	
	/** Set a table-wide attribute with given ClassID to the specified real-number.
		@param classID IN The ClassID of the attribute to set.
		@param realParam IN The value of the attribute to set.
	*/
	void SetTableAttributeReal(const ClassID& classID, const PMReal realParam);

	/** Set a cell stroke attribute to the specified stroke weight.
		@param sides IN The side(s) of the cell to set.
		@param strokeWeight IN The stroke weight to set.
	*/
	void SetCellStroke(const Tables::ESelectionSides sides, const PMReal strokeWeight);

	/** Get the value of a cell attribute by ClassID.
		@param classID IN The ClassID of the attribute to get.
		@return the attribute value if unique, (-1) otherwise
	*/
	PMReal GetCellAttributeReal(const ClassID& classID);

	/** Get the value of a table-wide attribute by ClassID.
		@param classID IN The ClassID of the attribute to get.
		@return the attribute value if available, (-1) otherwise
	*/
	PMReal GetTableAttributeReal(const ClassID& classID);

	/** Get a cell stroke attribute.
		@param sides IN The side(s) of the cell to get.
		@return the attribute value if available, (-1) otherwise
	*/
	PMReal GetCellStroke(const Tables::ESelectionSides sides);
};

#endif // !defined(_TBLATTQUERYMUTHELPER__INCLUDED_)

