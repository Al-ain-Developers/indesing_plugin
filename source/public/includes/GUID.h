//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/GUID.h $
//  
//  Owner: Jonathan W. Brown
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
//  Note: Run 'guidgen.exe' on Windows if you need to generate GUIDs
//  
//========================================================================================

#pragma once
#ifndef __GUIDTypes__
#define __GUIDTypes__

	#ifdef __ODFRC__

		type GuidType
		{
			longint ;
			integer ;
			integer ;
			array [8]
			{
				byte ;
			} ;
		} ;

		#define DECLARE_GUID( guid, kguid )

	#else	//__ODFRC__

		#ifdef MACINTOSH

			#ifndef GUID_DEFINED
			#define GUID_DEFINED

			struct GUID {
				uint32 Data1;
				uint16 Data2;
				uint16 Data3;
				uchar  Data4[8];
				bool16 operator==( const GUID& guid ) const
					{ return ( Data1 == guid.Data1 && Data2 == guid.Data2 && 
					Data3 == guid.Data3 && 0 == memcmp( Data4, guid.Data4, sizeof( Data4 ) ) ) ; }
				bool16 operator!=( const GUID& guid ) const
					{ return !( *this == guid ) ; }
			} ;

			#endif // !GUID_DEFINED

		#endif	//MACINTOSH

		#define DECLARE_GUID( guid, kguid ) \
			static const GUID guid = kguid

		class IPMStream ;
		void PUBLIC_DECL ReadWriteGUID( IPMStream* s, GUID& guid ) ;

	#endif	//!__ODFRC__

	#define kInvalid_CLSID { 0x0, 0x0, 0x0, { 0x0, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0 } }
	DECLARE_GUID( k_invalid_CLSID, kInvalid_CLSID ) ;		//Use DECLARE_GUID for any GUID that is referenced in C++ code

#endif	//__GUIDTypes__
