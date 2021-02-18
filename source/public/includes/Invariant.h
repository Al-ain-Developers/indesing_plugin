//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/Invariant.h $
//  
//  Owner: Jesse Jones (jejones)
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
//  ADOBE CONFIDENTIAL
//  
//  Purpose: Misc debugging features
//  
//========================================================================================

#pragma once
#ifndef __INVARIANT__H__
#define __INVARIANT__H__

// ===================================================================================
//	Design By Contract
// ===================================================================================
#ifdef DEBUG
	class InvariantCount {			// $$$ Use DECLARE_HELPER_METHODS to automate adding this when interfaces are used?
	public:
				InvariantCount()	{fNesting = 0;}
		void 	Enter()	const		{++fNesting; ASSERT(fNesting >= 1);}
		void	Exit() const		{--fNesting; ASSERT(fNesting >= 0);}
		bool16	Check() const		{return fNesting == 1;}
	private:
		mutable int32	fNesting;
	};

	template<typename T> class AutoInvariantChecker {
	public:
		explicit AutoInvariantChecker(InvariantCount& invariant, T& t) : 
			fInvariant(invariant),
			fObject(t)
		{
			fInvariant.Enter();
			if (fInvariant.Check()) 
				fObject.Invariant();
		}
		~AutoInvariantChecker()
		{
			if (fInvariant.Check())
				fObject.Invariant();
			fInvariant.Exit();
		}
	private:
		InvariantCount&	fInvariant;
		T&				fObject;
	};

	#define	PRECONDITION(p)			ASSERT(p); fInvariant.Enter(); if (fInvariant.Check()) this->Invariant()
	#define	POSTCONDITION(p)		ASSERT(p); if (fInvariant.Check()) this->Invariant(); fInvariant.Exit()

	#define CHECK_INVARIANT				this->Invariant
	#define	AUTO_INVARIANT_CHECKER(TYPE)  AutoInvariantChecker<TYPE> autoInvariantChecker(fInvariant, *this)

#else
	#define	PRECONDITION(p)					((void) 0)
	#define	POSTCONDITION(p)				((void) 0)
	#define CHECK_INVARIANT()				((void) 0)
	#define	AUTO_INVARIANT_CHECKER(TYPE)	((void) 0)
#endif	

#endif	// __INVARIANT__H__

