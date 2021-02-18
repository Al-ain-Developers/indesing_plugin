//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/objectmodel/DestroyInterfacePtr.cpp $
//  
//  Owner: Robin_Briggs
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

#include "InterfacePtr.h"

extern "C" void  __dl__FPv();
extern "C" void  __ptr_glue();

#pragma export off

#if 0
asm void DestroyInterfacePtr() 
{ 
nofralloc
mflr       r0
stw        r31,-4(SP)
mr         r31,r4
stw        r30,-8(SP)
mr.        r30,r3
stw        r0,8(SP)
stwu       SP,-64(SP)
beq        @00000050 //*+52                    //; $00000050
//	Release_(fFace);
lwz        r3,0(r30)
cmplwi     r3,0x0000
beq        @0000003C//*+20                    //; $0000003C
lwz        r12,0(r3)
lwz        r12,12(r12)
bl         __ptr_glue
nop
@0000003C: extsh.     r0,r31
ble        @00000050 //*+16                    //; $00000050
mr         r3,r30
bl         __dl__FPv
nop
@00000050: mr         r3,r30
lwz        r0,72(SP)
addi       SP,SP,64
mtlr       r0
lwz        r31,-4(SP)
lwz        r30,-8(SP)
blr
}
#endif
