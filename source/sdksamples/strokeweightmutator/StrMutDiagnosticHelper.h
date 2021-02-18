//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/strokeweightmutator/StrMutDiagnosticHelper.h $
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

#ifndef __StrMutDiagnosticHelper_h__
#define __StrMutDiagnosticHelper_h__

class ISubject;
/** Helper that dumps selection messages to trace.

	
	@ingroup strokeweightmutator
*/
class StrMutDiagnosticHelper
{
	public:
		/**	Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		StrMutDiagnosticHelper() {}

		/** Destructor.
		*/
		virtual ~StrMutDiagnosticHelper() {}

	public:
		/** Dump the given message to trace.
			@param selectionMessage IN
		 */
		virtual void	DumpSelectionMessage(const ISelectionMessage* selectionMessage) const;

		/** Dump the given message to trace.
			@param graphicAttrMessage IN
		 */
		virtual void	DumpGraphicAttrMessage(const IGraphicAttrMessage* graphicAttrMessage) const;

		/** Dump the given observer update message to trace.
			@param theChange specifies the class ID of the change to the subject. Frequently this is a command ID.
			@param theSubject points to the ISubject interface for the subject that has changed.
			@param protocol specifies the ID of the changed interface on the subject boss.
			@param changedBy points to additional data about the change. Often this pointer indicates the class ID of the command that has caused the change.
		 */
		virtual void DumpUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy );
};

#endif // __StrMutDiagnosticHelper_h__

// End, StrMutDiagnosticHelper.cpp.

