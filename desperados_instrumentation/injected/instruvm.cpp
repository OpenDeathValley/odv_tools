#include "instruvm.h"

BOOL isBadReadMemory(void    *ptr,
                        DWORD   size)
{
    SIZE_T                          dw;
    MEMORY_BASIC_INFORMATION        mbi;
    int                             ok;
    
    (void)size;
    dw = VirtualQuery(ptr, &mbi, sizeof(mbi));
    ok = ((mbi.Protect & PAGE_READONLY) ||
        (mbi.Protect & PAGE_READWRITE) ||
        (mbi.Protect & PAGE_WRITECOPY) ||
        (mbi.Protect & PAGE_EXECUTE_READ) ||
        (mbi.Protect & PAGE_EXECUTE_READWRITE) ||
        (mbi.Protect & PAGE_EXECUTE_WRITECOPY));
    
    // check the page is not a guard page
    
    if (mbi.Protect & PAGE_GUARD)
        ok = FALSE;
    if (mbi.Protect & PAGE_NOACCESS)
        ok = FALSE;
    
    return !ok;
}

VOID MyDD(DWORD dwVal, int nb)
{
    for (int i = 0; i < nb; i++) {
        if (i && (i % 4) == 0) {
            dbg_msg("\n");
        }
        dbg_msg("%08X ", *(DWORD*)(dwVal + i * 4));
    }
    dbg_msg("\n");
}

VOID DumpUnk(PCUNK_VM pcvm)
{
    dbg_msg("[+] f[0] : 0x%08X ; f[1] : 0x%08X ; f[2] : 0x%08X ; f[3] : 0x%08X ; f[4] : 0x%08X ; f[5] : 0x%08X ; f[6] : 0x%08X\n",
        pcvm->dwUnk_dword_00, pcvm->dwUnk_dword_01, pcvm->dwUnk_dword_02, pcvm->dwUnk_dword_03, pcvm->dwUnk_dword_04, pcvm->dwUnk_dword_05, 
        pcvm->dwUnk_dword_06);
}

VOID ScriptEntry(PPUSHED_REGS regs)
{
    (void)regs;

    //PSCRIPT_INFO psi;
    //DWORD dwReturnAddr;
    //DWORD dwTid;

    //dbg_msg("[+] eax : 0x%08X\n", regs->Eax);
    //dbg_msg("[+] ecx : 0x%08X\n", regs->Ecx);
    //dbg_msg("[+] edx : 0x%08X\n", regs->Edx);
    //dbg_msg("[+] ebx : 0x%08X\n", regs->Ebx);
    //dbg_msg("[+] esp : 0x%08X\n", regs->Esp);
    //dbg_msg("[+] ebp : 0x%08X\n", regs->Ebp);
    //dbg_msg("[+] esi : 0x%08X\n", regs->Esi);
    //dbg_msg("[+] edi : 0x%08X\n", regs->Edi);
    //dwTid = GetCurrentThreadId();
    //dwReturnAddr = *(DWORD*)(regs->Esp);
    //psi = (PSCRIPT_INFO)(*(DWORD*)(regs->Esp + 4));
    //dbg_msg("[+] ThreadId : 0x%08X, CalledFrom : 0x%08X, Name : %s\n", dwTid, dwReturnAddr, psi->pName);
    //if (!strcmp("CheckVictoryCondition", psi->pName)) {
    //    //DebugBreak();
    //}
}

typedef struct _CLol3 {
    DWORD dwUnk_dword_00;           /* + 0x00 */
    DWORD dwUnk_dword_01;           /* + 0x04 */
    DWORD dwUnk_dword_02;           /* + 0x08 */
    PBYTE pVolatile;                /* + 0x0C */
    DWORD SizeVolatile;             /* + 0x10 */
    PBYTE pTemp;                    /* + 0x14 */
    DWORD SizeTemp;                 /* + 0x18 */
} CLol3, *PCLol3;

typedef struct _CLol {
    DWORD dwUnk_dword_00;           /* + 0x00 */
    DWORD dwUnk_dword_01;           /* + 0x04 */
    PCLol3 pClol3;                  /* + 0x08 */
} CLol, *PCLol;

typedef struct _COtherUnk {
    DWORD dwUnk_dword_00;           /* + 0x00 */
    DWORD dwUnk_dword_01;           /* + 0x04 */
    DWORD dwUnk_dword_02;           /* + 0x08 */
    PCLol pClol;                    /* + 0x0C */
    DWORD dwUnk_dword_04;           /* + 0x10 */
    DWORD dwUnk_dword_05;           /* + 0x14 */
} COtherUnk, *PCOtherUnk;

typedef struct _CUNKVM {
    DWORD dwUnk_dword_00;           /* + 0x00 */
    COtherUnk COthUnk;
} CUNKVM, *PCUNKVM;

typedef struct _CFUNCUNKVM {
    DWORD dwUnk_dword_00;           /* + 0x00 */
    DWORD dwUnk_dword_01;           /* + 0x04 */
    PCHAR pFuncName;                /* + 0x08 */
    DWORD dwLengthFuncName;         /* + 0x0C */
    DWORD dwUnk_dword_04;           /* + 0x10 */
    DWORD dwPCAddress;              /* + 0x14 */
    DWORD dwNbParameters;           /* + 0x18 */
    DWORD dwSizeofRetVal;           /* + 0x1C */
    DWORD dwSizeofParams;           /* + 0x20 */
    DWORD dwSizeofVol;              /* + 0x24 */
    DWORD dwUnk_dword_10;           /* + 0x28 */
} CFUNCUNKVM, *PCFUNCUNKVM;

typedef struct _CCLASSVM {
    DWORD dwUnk_dword_00;         /* + 0x00 */
    DWORD dwUnk_dword_01;         /* + 0x04 */
    PCHAR pScriptName;            /* + 0x08 */
    DWORD dwLengthScriptName;     /* + 0x0C */
    DWORD dwUnk_dword_04;         /* + 0x10 */
    DWORD dwUnk_dword_05;         /* + 0x14 */
    PCHAR pClassName;             /* + 0x18 */
    DWORD dwLengthClassName;      /* + 0x1C */
    DWORD dwUnk_dword_08;         /* + 0x20 */
    DWORD dwUnk_dword_09;         /* + 0x24 */
    DWORD dwUnk_dword_10;         /* + 0x28 */
    DWORD dwUnk_dword_11;         /* + 0x2C */    
    DWORD dwUnk_dword_12;         /* + 0x30 */    
    DWORD dwUnk_dword_13;         /* + 0x34 */    
    DWORD dwUnk_dword_14;         /* + 0x38 */    
    DWORD dwUnk_dword_15;         /* + 0x3C */    
    DWORD dwUnk_dword_16;         /* + 0x40 */    
    DWORD dwUnk_dword_17;         /* + 0x44 */    
    DWORD dwUnk_dword_18;         /* + 0x48 */    
    DWORD dwUnk_dword_19;         /* + 0x4C */    
    DWORD dwUnk_dword_20;         /* + 0x50 */    
    DWORD dwNbFunc;               /* + 0x54 */    
    DWORD dwUnk_dword_22;         /* + 0x58 */
    DWORD dwUnk_dword_23;         /* + 0x5C */
    DWORD dwUnk_dword_24;         /* + 0x60 */
    DWORD dwUnk_dword_25;         /* + 0x64 */
    DWORD dwUnk_dword_26;         /* + 0x68 */
    DWORD dwUnk_dword_27;         /* + 0x6C */
    DWORD dwUnk_dword_28;         /* + 0x70 */
    DWORD dwUnk_dword_29;         /* + 0x74 */
    DWORD dwUnk_dword_30;         /* + 0x78 */
    DWORD dwUnk_dword_31;         /* + 0x7C */
    DWORD dwUnk_dword_32;         /* + 0x80 */
    DWORD dwUnk_dword_33;         /* + 0x84 */
    DWORD dwUnk_dword_34;         /* + 0x88 */
    DWORD dwUnk_dword_35;         /* + 0x8C */
    DWORD dwUnk_dword_36;         /* + 0x90 */
    DWORD dwUnk_dword_37;         /* + 0x94 */
    DWORD dwUnk_dword_38;         /* + 0x98 */
    DWORD dwUnk_dword_39;         /* + 0x9C */
    DWORD dwUnk_dword_40;         /* + 0xA0 */
    DWORD dwUnk_dword_41;         /* + 0xA4 */
    DWORD dwUnk_dword_42;         /* + 0xA8 */
    DWORD dwUnk_dword_43;         /* + 0xAC */
    DWORD dwUnk_dword_44;         /* + 0xB0 */
    DWORD dwUnk_dword_45;         /* + 0xB4 */
    DWORD dwUnk_dword_46;         /* + 0xB8 */
    DWORD dwUnk_dword_47;         /* + 0xBC */
    PBYTE pByteCodeBuffer;        /* + 0xC0 */
} CCLASSVM, *PCCLASSVM;

typedef struct _CSCRIPTVM {
    DWORD dwUnk_dword_00;         /* + 0x00 */
    DWORD dwUnk_dword_01;         /* + 0x04 */
    DWORD dwUnk_dword_02;         /* + 0x08 */
    CUNKVM CUnkVM;
    DWORD dwUnk_dword_10;         /* + 0x28 */
    DWORD dwUnk_dword_11;         /* + 0x2C */
    DWORD dwUnk_dword_12;         /* + 0x30 */
    DWORD dwUnk_dword_13;         /* + 0x34 */
    DWORD dwUnk_dword_14;         /* + 0x38 */
    DWORD dwPCAddress;            /* + 0x3C */
    DWORD dwPCBuffer;             /* + 0x40 */
    DWORD dwUnk_dword_17;         /* + 0x44 */
    DWORD dwUnk_dword_18;         /* + 0x48 */
    DWORD dwUnk_dword_19;         /* + 0x4C */
    DWORD dwRegResult;            /* + 0x50 */
    DWORD dwUnk_dword_21;         /* + 0x54 */
    PCCLASSVM pClassVM;           /* + 0x58 */      /* CClassUnk* */
    PCFUNCUNKVM pFuncVM;          /* + 0x5C */      /* CFuncUnk* */
    DWORD dwUnk_dword_24;         /* + 0x60 */
    DWORD dwUnk_dword_25;         /* + 0x64 */
    DWORD dwUnk_dword_26;         /* + 0x68 */
    DWORD dwUnk_dword_27;         /* + 0x6C */
    DWORD dwUnk_dword_28;         /* + 0x70 */
    DWORD dwUnk_dword_29;         /* + 0x74 */
    DWORD dwUnk_dword_30;         /* + 0x78 */
    DWORD dwUnk_dword_31;         /* + 0x7C */
    DWORD dwUnk_dword_32;         /* + 0x80 */
    DWORD dwUnk_dword_33;         /* + 0x84 */
    DWORD dwUnk_dword_34;         /* + 0x88 */
    DWORD dwUnk_dword_35;         /* + 0x8C */
    DWORD dwUnk_dword_36;         /* + 0x90 */
    DWORD dwUnk_dword_37;         /* + 0x94 */
    DWORD dwUnk_dword_38;         /* + 0x98 */
    DWORD dwUnk_dword_39;         /* + 0x9C */
    DWORD dwUnk_dword_40;         /* + 0xA0 */
    DWORD dwUnk_dword_41;         /* + 0xA4 */
    DWORD dwUnk_dword_42;         /* + 0xA8 */
    DWORD dwUnk_dword_43;         /* + 0xAC */
    DWORD dwUnk_dword_44;         /* + 0xB0 */
    DWORD dwUnk_dword_45;         /* + 0xB4 */
    DWORD dwUnk_dword_46;         /* + 0xB8 */
    DWORD dwUnk_dword_47;         /* + 0xBC */
    DWORD dwUnk_dword_48;         /* + 0xC0 */
    DWORD dwUnk_dword_49;         /* + 0xC4 */
    DWORD dwUnk_dword_50;         /* + 0xC8 */
    DWORD dwUnk_dword_51;         /* + 0xCC */
    DWORD dwUnk_dword_52;         /* + 0xD0 */
    DWORD dwUnk_dword_53;         /* + 0xD4 */
    DWORD dwUnk_dword_54;         /* + 0xD8 */
    DWORD dwUnk_dword_55;         /* + 0xDC */
    DWORD dwUnk_dword_56;         /* + 0xE0 */
    DWORD dwUnk_dword_57;         /* + 0xE4 */
    DWORD dwUnk_dword_58;         /* + 0xE8 */
    DWORD dwUnk_dword_59;         /* + 0xEC */
    DWORD dwUnk_dword_60;         /* + 0xF0 */
    DWORD dwUnk_dword_61;         /* + 0xF4 */
    DWORD dwUnk_dword_62;         /* + 0xF8 */
    DWORD dwUnk_dword_63;         /* + 0xFC */
    DWORD dwUnk_dword_64;         /* + 0x100 */
} CSCRIPTVM, *PCSCRIPTVM;

VOID PrintFuncStructInfo(PCFUNCUNKVM pFuncVM)
{
    dbg_msg("[+] + 0x00 : UNK_DWORD_00          : 0x%08x\n", pFuncVM->dwUnk_dword_00);
    dbg_msg("[+] + 0x04 : UNK_DWORD_01          : 0x%08x\n", pFuncVM->dwUnk_dword_01);
    dbg_msg("[+] + 0x08 : FunctionName          : 0x%08x [%s]\n", pFuncVM->pFuncName, pFuncVM->pFuncName);
    dbg_msg("[+] + 0x0C : strlen(FunctionName)  : 0x%08x\n", pFuncVM->dwLengthFuncName);
    dbg_msg("[+] + 0x10 : UNK_DWORD_04          : 0x%08x\n", pFuncVM->dwUnk_dword_04);
    dbg_msg("[+] + 0x14 : PC_ADDRESS            : 0x%08x\n", pFuncVM->dwPCAddress);
    dbg_msg("[+] + 0x18 : NB_PARAMETERS         : 0x%08x\n", pFuncVM->dwNbParameters);
    dbg_msg("[+] + 0x1C : SIZEOF_RETVAL         : 0x%08x\n", pFuncVM->dwSizeofRetVal);
    dbg_msg("[+] + 0x20 : SIZEOF_PARAMETERS     : 0x%08x\n", pFuncVM->dwSizeofParams);
    dbg_msg("[+] + 0x24 : SIZEOF_VOLATILE       : 0x%08x\n", pFuncVM->dwSizeofVol);
    dbg_msg("[+] + 0x28 : UNK_DWORD_10          : 0x%08x\n", pFuncVM->dwUnk_dword_10);
}

VOID PrintCUnkVMInfo(PCUNKVM pCUnkVM)
{
    dbg_msg("[+] PrintCUnkVMInfo\n");
    dbg_msg("[+] 0x%08X + 0x00 : UNK_DWORD_00          : 0x%08x\n", &pCUnkVM->dwUnk_dword_00, pCUnkVM->dwUnk_dword_00);
    dbg_msg("[+] 0x%08X + 0x04 : COthUnk.UNK_DWORD_00  : 0x%08x\n", &pCUnkVM->COthUnk.dwUnk_dword_00, pCUnkVM->COthUnk.dwUnk_dword_00);
    dbg_msg("[+] 0x%08X + 0x08 : COthUnk.UNK_DWORD_01  : 0x%08x\n", &pCUnkVM->COthUnk.dwUnk_dword_01, pCUnkVM->COthUnk.dwUnk_dword_01);
    if (pCUnkVM->COthUnk.dwUnk_dword_01) {
        dbg_msg("    [+] 0x%08X + 0x00 : *pCUnkVM->COthUnk.dwUnk_dword_01 : 0x%08X\n", pCUnkVM->COthUnk.dwUnk_dword_01, *(DWORD*)(pCUnkVM->COthUnk.dwUnk_dword_01));
    }
    dbg_msg("[+] 0x%08X + 0x0C : COthUnk.UNK_DWORD_02  : 0x%08x\n", &pCUnkVM->COthUnk.dwUnk_dword_02, pCUnkVM->COthUnk.dwUnk_dword_02);
    dbg_msg("[+] 0x%08X + 0x10 : COthUnk.pClol  : 0x%08x\n", &pCUnkVM->COthUnk.pClol, pCUnkVM->COthUnk.pClol);
    if (pCUnkVM->COthUnk.pClol && !isBadReadMemory(pCUnkVM->COthUnk.pClol, 0)) {
        dbg_msg("   [+] 0x%08X + 0x00 : UNK_DWORD_00          : 0x%08x\n", &pCUnkVM->COthUnk.pClol->dwUnk_dword_00, pCUnkVM->COthUnk.pClol->dwUnk_dword_00);
        dbg_msg("   [+] 0x%08X + 0x04 : UNK_DWORD_01          : 0x%08x\n", &pCUnkVM->COthUnk.pClol->dwUnk_dword_01, pCUnkVM->COthUnk.pClol->dwUnk_dword_01);
        dbg_msg("   [+] 0x%08X + 0x08 : pClol3                : 0x%08x\n", &pCUnkVM->COthUnk.pClol->pClol3, pCUnkVM->COthUnk.pClol->pClol3);
        if (pCUnkVM->COthUnk.pClol->pClol3 && !isBadReadMemory((void*)pCUnkVM->COthUnk.pClol->pClol3, 0)) {
            dbg_msg("       [+] Clol3.pVolatile               : 0x%08X\n", pCUnkVM->COthUnk.pClol->pClol3->pVolatile);
            dbg_msg("       [+] Clol3.SizeVolatile            : 0x%08X\n", pCUnkVM->COthUnk.pClol->pClol3->SizeVolatile);
            dbg_msg("       [+] Clol3.pTemp                   : 0x%08X\n", pCUnkVM->COthUnk.pClol->pClol3->pTemp);
            dbg_msg("       [+] Clol3.SizeTemp                : 0x%08X\n", pCUnkVM->COthUnk.pClol->pClol3->SizeTemp);
            if (pCUnkVM->COthUnk.pClol->pClol3->SizeTemp && pCUnkVM->COthUnk.pClol->pClol3->pTemp) {
                if (pCUnkVM->COthUnk.pClol->pClol3->SizeTemp > 0x1000) {
                    dbg_msg("[+] WAT SizeTemp\n");
                }
                else {
                    MyDD((DWORD)pCUnkVM->COthUnk.pClol->pClol3->pTemp, pCUnkVM->COthUnk.pClol->pClol3->SizeTemp / 4);
                }
            }
        }
    }
    dbg_msg("[+] 0x%08X + 0x14 : COthUnk.UNK_DWORD_04  : 0x%08x\n", &pCUnkVM->COthUnk.dwUnk_dword_04, pCUnkVM->COthUnk.dwUnk_dword_04);
    dbg_msg("[+] 0x%08X + 0x18 : COthUnk.UNK_DWORD_05  : 0x%08x\n", &pCUnkVM->COthUnk.dwUnk_dword_05, pCUnkVM->COthUnk.dwUnk_dword_05);
}

VOID VMEntry(PPUSHED_REGS regs)
{
    PCHAR pScriptName;
    PCHAR pClassName;
    PCHAR pFuncName;

    DWORD dwTid;
    DWORD dwVM_PC_ADDR;
    DWORD dwPoolClassVar;
    DWORD UnkStruct;
    DWORD dwRegResult;
    DWORD UnkClassStruct;
    
    DWORD dwCalledFrom;
    DWORD dwNbFunc;
    
    dwVM_PC_ADDR   = *(DWORD*)(regs->Ecx + 0x3C);
    dwPoolClassVar = *(DWORD*)(regs->Ecx + 0x34);
    UnkClassStruct = *(DWORD*)(regs->Ecx + 0x58);       // 0x08: Scriptname ; 0x0C: LengthScriptName ; 0x18: ClassName ; 0x1C: LengthClassName
    UnkStruct      = *(DWORD*)(regs->Ecx + 0x5C);       // UnkStruct + 0x08: NAME ? +0x0C: LENGTH_NAME ?
    dwRegResult    = *(DWORD*)(regs->Ecx + 0x50);
    dwCalledFrom = *(DWORD*)(regs->Esp + 0x08);
    pScriptName = (PCHAR)(*(DWORD*)(UnkClassStruct + 0x08));
    pClassName  = (PCHAR)(*(DWORD*)(UnkClassStruct + 0x18));
    pFuncName   = (PCHAR)(*(DWORD*)(UnkStruct + 0x08));    
    dwNbFunc     = *(DWORD*)(UnkClassStruct + 0x54);
    
    /* UnkStruct
    
        + 0x08 : Function Name
        + 0x0C : strlen(Function Name)
        + 0x10 : ????
        + 0x14 : Address
        + 0x18 : NumberOfParameters
        + 0x1C : sizeof (retval)
        + 0x20 : sizeof (params)
        + 0x24 : sizeof (vol)
    
        + 0x94 : sizeof (tempor)
    */
    dbg_msg("----------------------------\n");
    dwTid = GetCurrentThreadId();
    dbg_msg("[+] ThreadId : 0x%08X, CalledFrom : 0x%08X, VM_PC_ADDR : 0x%08X\n", dwTid, dwCalledFrom, dwVM_PC_ADDR);
    //dbg_msg("[+] %s::%s (%s)\n", pClassName, pFuncName, pScriptName);
    //dbg_msg("[+] Class_nbfunctions : 0x%08X\n", dwNbFunc);
    //dbg_msg("[+] ecx : 0x%08X\n", regs->Ecx);
    //dbg_msg("[+] esp : 0x%08X\n", regs->Esp);
    //dbg_msg("[+] UnkClassStruct : 0x%08X\n", UnkClassStruct);
    //dbg_msg("[+] UnkStruct : 0x%08X\n", UnkStruct);
    ////dbg_msg("[+] MyDD(UnkStruct)\n");
    ////MyDD(UnkStruct);
    ////dbg_msg("[+] MyDD(regs->Ecx)\n");
    ////MyDD(regs->Ecx);
    //dbg_msg("dwPoolClassVar   : 0x%08X\n", dwPoolClassVar);
    //dbg_msg("dwRegResult      : 0x%08X\n", dwRegResult);
    //dbg_msg("UnkStruct + 0x90 : 0x%08X\n", *(DWORD*)(UnkStruct + 0x90));
    //DumpUnk((PCUNK_VM)(regs->Ecx + 0x0C));
    //dbg_msg("---------------------------- NEW EXTRACTED INFO -----\n");
    PCSCRIPTVM pScriptVM;
    
    pScriptVM = (PCSCRIPTVM)(regs->Ecx);
    dbg_msg("[+] %s::%s (%s)\n", pScriptVM->pClassVM->pClassName, pScriptVM->pFuncVM->pFuncName, pScriptVM->pClassVM->pScriptName);
    dbg_msg("[+] Class_nbfunctions : 0x%08X\n", pScriptVM->pClassVM->dwNbFunc);
    PrintFuncStructInfo(pScriptVM->pFuncVM);
    //PrintCUnkVMInfo(&pScriptVM->CUnkVM);
    //dbg_msg("[+] MyDD(UnkClassStruct)\n");
    //MyDD(UnkClassStruct);
    //DebugBreak();
    /* 
        0:000> dd esp + 30 L1
        0018f994  005c7c21
        nb_functions: UnkClassStruct + 0x54
    */
}

VOID VMExecOpcode(PPUSHED_REGS regs)
{
    PCSCRIPTVM pScriptVM;
    
    dbg_msg("[+] VM Exec!\n");
    pScriptVM = (PCSCRIPTVM)(regs->Esi);
    dbg_msg("[+] PC_ADDR : 0x%08X, Opcode : 0x%02X\n", pScriptVM->dwPCAddress, *(BYTE*)(pScriptVM->pClassVM->pByteCodeBuffer + 0x0C * pScriptVM->dwPCAddress));
    PrintCUnkVMInfo(&pScriptVM->CUnkVM);
    //DebugBreak();
}

DWORD (__stdcall *ResumeScriptEntry)(VOID) = NULL;

DWORD __declspec (naked) HookScriptEntry(VOID)
{
    __asm
    {
        pushad
        lea     eax, [esp]
        push    eax
        call    ScriptEntry
        add     esp, 4
        popad
        jmp     ResumeScriptEntry
    }
}

DWORD (__stdcall *ResumeVMEntry)(VOID) = NULL;

DWORD __declspec (naked) HookVMEntry(VOID)
{
    __asm
    {
        pushad
        lea     eax, [esp]
        push    eax
        call    VMEntry
        add     esp, 4
        popad
        jmp     ResumeVMEntry
    }
}

DWORD (__stdcall *ResumeVMExecOpcode)(VOID) = NULL;

DWORD __declspec (naked) HookVMExecOpcode(VOID)
{
    __asm
    {
        pushad
        lea     eax, [esp]
        push    eax
        call    VMExecOpcode
        add     esp, 4
        popad
        jmp     ResumeVMExecOpcode
    }
}