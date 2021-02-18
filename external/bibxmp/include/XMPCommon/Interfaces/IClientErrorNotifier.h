#ifndef IClientErrorNotifier_h__
#define IClientErrorNotifier_h__ 1

// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2014 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#if AdobePrivate
// =================================================================================================
// Change history
// ==============
//
// Writers:
//  ADC	Amandeep Chawla
//
// mm-dd-yy who Description of changes, most recent first.
//
// 02-02-15 ADC 5.6-c036 Porting C++ Based APIs of XMPCore to gcc 4.8.x on Linux Platform.
// 07-10-14 ADC 5.6-c015 Refactoring, partial documentation and bug fixes of XMPCommon and XMPCore C++ APIs.
// 05-19-14 ADC 5.6-c012 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
// 05-19-14 ADC 1.0-m020 Refactoring XMPCommon code and appropriate changes in XMPCore and XMPCompareAndMerge.
//
// =================================================================================================
#endif	// AdobePrivate

#include "XMPCommon/XMPCommonDefines.h"
#include "XMPCommon/XMPCommonFwdDeclarations.h"
#include "XMPCommon/Interfaces/BaseInterfaces/ISharedOwnership.h"
#include "XMPCommon/Interfaces/IError.h"

namespace NS_XMPCOMMON {

	//!
	//! \brief Version1 of the interface that represents an interface to be implemented by client
	//! in case he is interested in getting notifications with respect to errors/warnings encountered
	//! by library.
	//! \details In case client is interested in error notifications he can implement this interface
	//! and register the same with the #NS_XMPCOMMON::IConfigurationManager. For every warning or error
	//! encountered the NotifyError function will be called by the library. In case of warnings (indicated
	//! by the severity of the error ) the client has the option to continue ignoring the warning by returning
	//! true else he can return false and the warning will be thrown aborting the current operation.
	//! \attention Support for Multi threading is under clients hand.
	//!
	class XMP_PUBLIC IClientErrorNotifier_v1
		: public virtual ISharedOwnership_v1
	{
	public:
		//!
		//! Called by the library to notify the client about the warning/error.
		//! \param error	[in]		const shared pointer to a #NS_XMPCOMMON::IError. Client can use the information
		//! in the error to decide what should be the future course of action.
		//! \return a value of bool type that will indicate the future course of action.
		//!
		virtual bool NotifyError( const spcIError & error ) = 0;

#if !SOURCE_COMPILED
	public:
		//! \cond XMP_INTERNAL_DOCUMENTATION
		// these functions are wrapper over actual functions client needs to implement, so no implementation required from client side
		virtual UInt32 NotifyError( pcIError_base perror, pcIError_base & error ) __NOTHROW__;
		//! \endcond
#endif  // !SOURCE_COMPILED

	protected:
		virtual ~IClientErrorNotifier_v1() __NOTHROW__ = 0;

		REQ_FRIEND_CLASS_DECLARATION();
	};

	inline IClientErrorNotifier_v1::~IClientErrorNotifier_v1() __NOTHROW__ { }
};

#if !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB
//! \cond XMP_INTERNAL_DOCUMENTATION
#include "XMPCommon/Utilities/TWrapperFunctions.h"
namespace NS_XMPCOMMON {
	inline UInt32 IClientErrorNotifier_v1::NotifyError( pcIError_base perror, pcIError_base & error ) __NOTHROW__ {
		return CallUnSafeFunction< IClientErrorNotifier_v1, UInt32, bool, const spcIError & >( error, this, 1, &IClientErrorNotifier_v1::NotifyError,
			NS_XMPCOMMON::MakeSharedPointer< const IError >( perror ) );
	}
}
//! \endcond
#endif  // !SOURCE_COMPILED && !BUILDING_XMPCOMMON_LIB

#endif  // IClientErrorNotifier_h__
