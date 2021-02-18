//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/OMTypes.h $
//  
//  Owner: 
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
#ifndef __OMTypes__
#define __OMTypes__

#ifndef __AnsiBasedTypes__
#include "AnsiBasedTypes.h"
#endif

#include "K2TypeTraits.h"
// ** These classes are used in the debug build to catch **
// ** unintended typecast. For example, using a ClassID  **
// ** when we really want to use an ImplementationID.    **

struct UID_tag {};
struct ClassID_tag {};
struct PMIID_tag {};
struct ImplementationID_tag {};
struct PluginID_tag {};
struct ServiceID_tag {};
struct WidgetID_tag {};
struct KitViewID_tag {};
struct ActionID_tag {};
struct FileTypeInfoID_tag {};
struct ScriptElementID_tag {} ;
struct ProductID_tag {} ;
struct AsyncUIID_tag {} ;
struct ScriptID_tag {} ;
struct UserActionCategoryID_tag {} ;
struct InvalHandlerID_tag {};
struct PerformanceMetricID_tag {};
struct LinkClientID_tag {};
struct SnapshotID_tag {};
struct LastRevInfoID_tag {};
struct DontShowAgainID_tag {};

/** IDType is the underlying base type used for representing any type that is an 
	InDesign ID-space. An ID-space is an integer composed of a plug-in prefix, 
	plus a one-byte offset. Each identifier within the id-space is unique. We
	use IDType as a base class in order to detect mismatches between them at 
	runtime. For instance, if you pass a ClassID to something that expects an
	IID, that will cause a compile time error instead of a (relatively more costly
	to fix) runtime error.
	
	IDTypes can be used pretty much interchangeably as if they were integers. The
	exceptions to this rule are if they are being used in a switch statement, and
	when you are reading them in or out of resources. For cases where you simply 
	must have an integer, we supply the Get() function.
*/
template<class T>
class IDType
{
	public:
		typedef base_type data_type;
		typedef int32 difference_type;
		typedef uint32 value_type;

		constexpr IDType() noexcept : fIDInt(0) {}
		//~IDType() {}
    
        constexpr IDType(const IDType &) noexcept = default;
        IDType& operator=(const IDType &) noexcept = default;
        constexpr IDType(IDType &&) noexcept = default;
        IDType& operator=(IDType && ) noexcept = default;
    
		constexpr IDType(value_type sourceInt) noexcept : fIDInt(sourceInt) {}
		IDType& operator=(const value_type& sourceInt) noexcept {fIDInt = sourceInt; return *this;}

		bool operator>(const IDType& rhs) const noexcept { return fIDInt > rhs.fIDInt; }
		bool operator>(const value_type& rhs) const noexcept { return fIDInt > rhs; }
		friend bool operator>(const value_type& lhs, const IDType<T>& rhs) noexcept { return lhs > rhs.fIDInt; }

		bool operator<(const IDType& rhs) const noexcept { return fIDInt < rhs.fIDInt; }
		bool operator<(const value_type& rhs) const noexcept { return fIDInt < rhs; }
		friend bool operator<(const value_type& lhs, const IDType<T>& rhs) noexcept { return lhs < rhs.fIDInt; }

		bool operator<=(const IDType& rhs) const noexcept { return !(fIDInt > rhs.fIDInt); }
		bool operator<=(const value_type& rhs) const noexcept { return !(fIDInt > rhs); }
		friend bool operator<=(const value_type& lhs, const IDType<T>& rhs) noexcept { return !(lhs > rhs.fIDInt); }

		bool operator>=(const IDType& rhs) const noexcept { return !(fIDInt < rhs.fIDInt); }
		bool operator>=(const value_type& rhs) const noexcept { return !(fIDInt < rhs); }
		friend bool operator>=(const value_type& lhs, const IDType<T>& rhs) noexcept { return !(lhs < rhs.fIDInt); }

		bool operator==(const IDType& rhs) const noexcept { return fIDInt == rhs.fIDInt; }
		friend bool operator==(const value_type& lhs, const IDType<T>& rhs) noexcept { return lhs == rhs.fIDInt; }

		bool operator!=(const IDType& rhs) const noexcept { return !(fIDInt == rhs.fIDInt); }
		bool operator!=(const value_type& rhs) const noexcept { return !(fIDInt == rhs); }
		friend bool operator!=(const value_type& lhs, const IDType<T>& rhs) noexcept { return !(lhs == rhs.fIDInt); }

		IDType& operator+=(const difference_type& rhs) { fIDInt += rhs; return *this; }
		friend IDType<T> operator+(const IDType<T>& lhs, const difference_type& rhs) { return IDType<T>(lhs) += rhs; }
		friend IDType<T> operator+(const IDType<T>& lhs, const IDType<T>& rhs) { return IDType<T>(lhs) += rhs.fIDInt; }
		friend IDType<T> operator+(const difference_type& lhs, const IDType<T> rhs) { return IDType<T>(rhs) += lhs; }

		// prefix
		IDType& operator++() { *this += 1; return *this; }
		// postfix
		const IDType operator++(int) { IDType oldValue = *this; ++(*this); return oldValue; }

		IDType& operator-=(const IDType& rhs) { fIDInt -= rhs.fIDInt; return *this; }
		IDType& operator-=(const difference_type& rhs) { fIDInt -= rhs; return *this; }
		friend IDType<T> operator-(const difference_type& lhs, IDType<T> rhs) { return IDType<T>(rhs) -= lhs; }
		friend difference_type operator-(const IDType<T>& lhs, const difference_type& rhs) { return lhs.fIDInt - rhs; }
		friend difference_type operator-(const IDType<T>& lhs, const IDType<T>& rhs) { return lhs.fIDInt - rhs.fIDInt; }

		// prefix
		IDType& operator--() { *this -= 1; return *this; }
		// postfix
		const IDType operator--(int) { IDType oldValue = *this; --(*this); return oldValue; }

		value_type operator>>(const int& rhs) const { return fIDInt >> rhs; }
		value_type operator<<(const int& rhs) const { return fIDInt << rhs; }

		value_type operator&(const value_type& rhs) const { return fIDInt & rhs; }
		friend value_type operator&(const value_type& lhs, const IDType<T>& rhs) { return IDType<T>(rhs) & lhs; }

		value_type operator|(const value_type& rhs) { return fIDInt | rhs; }
		friend value_type operator|(const value_type& lhs, const IDType<T>& rhs) { return IDType<T>(rhs) | lhs; }

		IDType& operator|=(const value_type& rhs) { fIDInt |= rhs; return *this; }
//		friend value_type operator|=(const value_type& lhs, const IDType<T>& rhs) { lhs |= rhs.fIDInt; return lhs; }

		value_type& Get() noexcept { return fIDInt; }
		inline const value_type& Get() const noexcept { return fIDInt; }

		bool IsValid() const noexcept { return (fIDInt != 0); }

		static bool less_IDType(IDType<T>& lhs, IDType<T>& rhs)
		{
			return lhs.Get() < rhs.Get();
		}

//		operator uint32&() { return fIDInt; }
//		operator uint32() { return fIDInt; }

	private:
		value_type fIDInt;
};

// Global operators
template<class T>
inline bool operator<(const IDType<T>& lhs, const IDType<T>& rhs) noexcept
{
	return lhs.Get() < rhs.Get();
}

template<class T>
inline bool operator==(const IDType<T>& lhs, const IDType<T>& rhs) noexcept
{
	return lhs.Get() == rhs.Get();
}

template <class T>
struct CONVERSION_TO_THREADLOCALSTORAGE<IDType<T> > {
	static typename IDType<T>::value_type CONVERT(IDType<T>  arg) {return arg.Get();}
};


// typedef the ID types we need.

/** SBOSID stands for "small boss" a small boss is an boss that can be stored
	as part of a collection of other small bosses, rather than each one requiring
	its own UID. This is useful for performance reasons when you might otherwise
	have a large collection of UID-based bosses. Think of a SBOSID as similar to a
	UID. Currently this is used primary for objects in the XML hierarchy. 
*/
typedef uint32 SBOSID;
/** A "nil" value for SBOSIDs -- a valid SBOSID will never be equal to kInvalidSBOSID. */
constexpr SBOSID kInvalidSBOSID = 0;

/** UID stands for "Unique ID" and is a persistent reference to an object in a database.
*/
typedef IDType<UID_tag> UID;

/** ClassID is a reference to a boss class.
*/
typedef IDType<ClassID_tag> ClassID;

/** PMIID is a reference to an interface.
*/
typedef IDType<PMIID_tag> PMIID;

/** ImplementationID refers to the C++ class that implements an interface
*/
typedef IDType<ImplementationID_tag> ImplementationID;

/** PluginID refers to a plug-in
*/
typedef IDType<PluginID_tag> PluginID;

/** ServiceID refers to a service. See @ref IK2ServiceRegistry for more info.
*/
typedef IDType<ServiceID_tag> ServiceID;

typedef IDType<InvalHandlerID_tag> InvalHandlerID;

typedef IDType<WidgetID_tag> WidgetID;
typedef IDType<KitViewID_tag> KitViewID;
typedef IDType<ActionID_tag> ActionID;
typedef IDType<FileTypeInfoID_tag> FileTypeInfoID;
typedef IDType<ScriptElementID_tag> ScriptElementID;
typedef IDType<ProductID_tag> ProductID;
typedef IDType<AsyncUIID_tag> AsyncUIID;
typedef IDType<ScriptID_tag> ScriptID ;
typedef IDType<UserActionCategoryID_tag> UserActionCategoryID;
typedef IDType<PerformanceMetricID_tag> PerformanceMetricID;

/** LinkClientID refers to a link client that uses link and link resources.
*/
typedef IDType<LinkClientID_tag> LinkClientID;

/** SnapshotID refers to the idedentifier os a snapshot.
*/
typedef IDType<SnapshotID_tag> SnapshotID;

/** LastRevInfoID refers to the idedentifier os a snapshot.
*/
typedef IDType<LastRevInfoID_tag> LastRevInfoID;

/** DontShowAgainID refers to a "don't show again" alert identifier.
*/
typedef IDType<DontShowAgainID_tag> DontShowAgainID;


// OM constants

/** A "nil" value for UIDs -- a valid UID will never be equal to kInvalidUID. */
constexpr UID kInvalidUID;
/** A "nil" value for WidgetIDs -- a valid WidgetID will never have this value. */
constexpr WidgetID kInvalidWidgetID;
/** A "nil" value for ClassIDs -- a valid ClassID will never have this value. */
constexpr ClassID kInvalidClass;
/** A "nil" value for PluginIDs -- a valid PluginID will never have this value. */
constexpr PluginID kInvalidPlugin;
/** A "nil" value for ImplementationIDs -- a valid ImplementationID will never have this value. */
constexpr ImplementationID kInvalidImpl;
/** A "nil" value for ServiceIDs -- a valid ServiceID will never have this value. */
constexpr ServiceID kInvalidService;
/** A "nil" value for PMIIDs -- a valid PMIID will never have this value. */
constexpr PMIID kInvalidInterfaceID;
/** A "nil" value for KitViewID -- a valid KitViewID will never have this value. */
constexpr KitViewID kInvalidKitViewID;
/** A "nil" value for ActionIDs -- a valid ActionID will never have this value. */
constexpr ActionID kInvalidActionID;
/** A "nil" value for FileTypeInfoIDs -- a valid FileTypeInfoIDs will never have this value. */
constexpr FileTypeInfoID kInvalidFileTypeInfoID;
/** A "nil" value for ScriptElementIDs -- a valid ScriptElementID will never have this value. */
constexpr ScriptElementID kInvalidScriptElementID;
/** A "nil" value for ProductID -- a valid ProductID will never have this value. */
constexpr ProductID kInvalidProdcutID;
/** A "nil" value for AsyncUIIDs -- a valid AsyncUIID will never have this value. */
constexpr AsyncUIID kInvalidAsyncUIID;
/** A "nil" value for ScriptIDs -- a valid ScriptID will never have this value. */
constexpr ScriptID kInvalidScriptID;
/** A "nil" value for ScriptIDs -- a valid ScriptID will never have this value. */
constexpr UserActionCategoryID kInvalidUserActionCategoryID;
/** A "nil" value for InvalHandlerIDs -- a valid InvalHandlerIDID will never have this value. */
constexpr InvalHandlerID kInvalidInvHandID;
/** A "nil" value for LinkClientIDs -- a valid LinkClientID will never have this value. */
constexpr LinkClientID kInvalidLinkClientID;
/** Invalid value for SnapshotIDs . */
constexpr SnapshotID kInvalidSnapshotID;
/** Invalid value for LastRevInfoIDs . */
constexpr LastRevInfoID kInvalidLastRevInfoID;
/** Invalid value for DontShowAgainIDs -- a valid DontShowAgainID will never have this value. */
constexpr DontShowAgainID kInvalidDontShowAgainID;


// common defs used by interfaces
/** equivalent to "false" */
constexpr bool16 kFalse = 0;
/** equivalent to "true" */
constexpr bool16 kTrue = 1;

#ifndef nil
#define nil nullptr
#endif 

#endif // __OMTypes__
