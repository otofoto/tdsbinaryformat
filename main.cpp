#include <windows.h>
#include <iostream>

using namespace std;

struct TdsHeader
{
	char Magic[4];
	int SubSectionDirOffset;
};

enum SubSectTypes
{
	sstModule = 0x120,
	sstAlignSym = 0x125,
	sstSrcModule = 0x127,
	sstGlobalSym = 0x129,
	sstGlobalTypes = 0x12b,
	sstNames = 0x130,
};

#define ENUM_TO_STR(e) case e: return #e;

const char * sstToString(short sst)
{
	switch (sst)
	{
		ENUM_TO_STR(sstModule);
		ENUM_TO_STR(sstAlignSym);
		ENUM_TO_STR(sstSrcModule);
		ENUM_TO_STR(sstGlobalSym);
		ENUM_TO_STR(sstGlobalTypes);
		ENUM_TO_STR(sstNames);
	default:
		return 0;
	}
}

enum SymbolAlignType
{
	S_COMPILE = 0x01,
	S_REGISTER = 0x02,
	S_CONST = 0x03,
	S_UDT = 0x04,
	S_SSEARCH = 0x05,
	S_END = 0x06,
	S_SKIP = 0x07,
	S_CVRESERVE = 0x08,
	S_OBJNAME = 0x09,
	S_ENDARG = 0x0A,
	S_COBOLUDT = 0x0B,
	S_MANYREG = 0x0C,
	S_RETURN = 0x0D,
	S_ENTRYTHIS = 0x0E,
	/*0xF-0x1F unused */
	S_GPROCREF = 0x20, /* [Address 32][Type 32][Name 32][Browser offset 32][Offset 32][Segment 16] */
	S_GDATAREF = 0x21, /* [Address 32][Type 32][Name 32][Browser offset 32][Offset 32][Segment 16] */
	S_EDATA = 0x22, /* [Type 32][Name 32][unk 16][EI 16][Browser offset 32]*/
	S_EPROC = 0x23, /* [Type 32][Name 32][unk 16][EI 16][Browser offset 32]*/
	S_USES = 0x24,
	S_NAMESPACE = 0x25,
	S_USING = 0x26,
	S_PCONSTANT = 0x27,
};

enum SymbolAlignSizedType
{
	S_BPREL = 0x0,
	S_LDATA = 0x1,
	S_GDATA = 0x2,
	S_PUB = 0x3, /* [Offset 32][Segment 16][Flags 16][Type 32][Name 32][Browser offset 32]*/
	S_LPROC = 0x4,
	S_GPROC = 0x5,
	S_THUNK = 0x6, /*[Parent 32][End 32][Next 32][Offset 32][Segment 16][Length 16][Name 32][Ordinal 8][Some flags 8]*/
	S_BLOCK = 0x7,
	S_WITH = 0x8,
	S_LABEL = 0x9, /*[Offset 32][Segment 16][Some byte 8][Name 32]*/
	/*0x unused*/
	S_VFTPATH = 0xB,
	S_VFTREGREL = 0xC,
	S_LTHREAD = 0xD,
	S_GTHREAD = 0xE,
	/*0xF unused*/
	S_ENTRY = 0x10, /*[Offset 32][Segment 16]*/
	S_OPTVAR = 0x11,
	S_PROCRET = 0x12,
	S_SAVREGS = 0x13,
	/*0x14-2F*/
	S_SLINK = 0x30,
};


const char * symAlignTypToString(int sat)
{
	switch (sat)
	{
	ENUM_TO_STR(S_COMPILE);
	ENUM_TO_STR(S_REGISTER);
	ENUM_TO_STR(S_CONST);
	ENUM_TO_STR(S_UDT);
	ENUM_TO_STR(S_SSEARCH);
	ENUM_TO_STR(S_END);
	ENUM_TO_STR(S_GPROCREF);
	ENUM_TO_STR(S_GDATAREF);
	ENUM_TO_STR(S_USES);
	ENUM_TO_STR(S_NAMESPACE);
	ENUM_TO_STR(S_USING);
	ENUM_TO_STR(S_PCONSTANT);
	default:
		throw 0;
	}
}

const char * symAlignSizedTypToString(int sast)
{
	switch (sast)
	{
	ENUM_TO_STR(S_BPREL);
	ENUM_TO_STR(S_LDATA);
	ENUM_TO_STR(S_GDATA);
	ENUM_TO_STR(S_PUB);
	ENUM_TO_STR(S_LPROC);
	ENUM_TO_STR(S_GPROC);
	ENUM_TO_STR(S_THUNK);
	ENUM_TO_STR(S_BLOCK);
	ENUM_TO_STR(S_WITH);
	ENUM_TO_STR(S_LABEL);
	ENUM_TO_STR(S_ENTRY);
	ENUM_TO_STR(S_OPTVAR);
	ENUM_TO_STR(S_PROCRET);
	ENUM_TO_STR(S_SAVREGS);
	ENUM_TO_STR(S_SLINK);
	default:
		throw 0;
	}
}

void PrintSymAlignTyp(ostream & stm, short sat)
{
	switch (sat & 0xFF00)
	{
	case 0:
		stm << symAlignTypToString(sat & 0xFF);
		break;
	case 0x100:
		stm << symAlignSizedTypToString(sat & 0xFF);
		stm << "16";
		break;
	case 0x200:
		stm << symAlignSizedTypToString(sat & 0xFF);
		stm << "32";
		break;
	}
}


enum RegisterTypes
{
	none = 0x00,
	AL = 0x01,
	CL = 0x02,
	DL = 0x03,
	BL = 0x04,
	AH = 0x05,
	CH = 0x06,
	DH = 0x07,
	BH = 0x08,
	AX = 0x09,
	CX = 0x0A,
	DX = 0x0B,
	BX = 0x0C,
	SP = 0x0D,
	BP = 0x0E,
	SI = 0x0F,
	DI = 0x10,
	EAX = 0x11,
	ECX = 0x12,
	EDX = 0x13,
	EBX = 0x14,
	ESP = 0x15,
	EBP = 0x16,
	ESI = 0x17,
	EDI = 0x18,
};

const char * regToString(short reg)
{
	switch (reg)
	{
		ENUM_TO_STR(none);
		ENUM_TO_STR(AL);
		ENUM_TO_STR(CL);
		ENUM_TO_STR(DL);
		ENUM_TO_STR(BL);
		ENUM_TO_STR(AH);
		ENUM_TO_STR(CH);
		ENUM_TO_STR(DH);
		ENUM_TO_STR(BH);
		ENUM_TO_STR(AX);
		ENUM_TO_STR(CX);
		ENUM_TO_STR(DX);
		ENUM_TO_STR(BX);
		ENUM_TO_STR(SP);
		ENUM_TO_STR(BP);
		ENUM_TO_STR(SI);
		ENUM_TO_STR(DI);
		ENUM_TO_STR(EAX);
		ENUM_TO_STR(ECX);
		ENUM_TO_STR(EDX);
		ENUM_TO_STR(EBX);
		ENUM_TO_STR(ESP);
		ENUM_TO_STR(EBP);
		ENUM_TO_STR(ESI);
		ENUM_TO_STR(EDI);
	default:
		return 0;
	}
}

const unsigned int TD_CLASS_MASK = 0xFFFFFE00;
const unsigned int TD_TYPE_MASK = ~TD_CLASS_MASK;
const unsigned int TD_SUBTYPE_CLASS_MASK = 0x1F0 & TD_TYPE_MASK;
const unsigned int TD_SUBTYPE_MASK = ~(TD_CLASS_MASK | TD_SUBTYPE_CLASS_MASK);

// type def classes
const unsigned int TDC_ROOT = 0x000;
const unsigned int TDC_LIST = 0x200;
const unsigned int TDC_LIST_ITEM = 0x400;


// type def sub types
const unsigned int TDST_GENERIC = 0x000;
const unsigned int TDST_PASCAL = 0x030;
//const unsigned int TDST_UNKNOWN = 0x0E0;

enum TypDefRootType
{
	T_STARTYP = 0x0,
	T_MODIFIER = 0x1,
	T_POINTER = 0x2,
	T_ARRAY = 0x3, /*[Type 32][Indexer type 32][Name 32][Size 16][Num 16]*/
	T_CLASS = 0x4,
	T_STRUCT = 0x5,
	T_UNION = 0x6,
	T_ENUM = 0x7,
	T_PROCEDURE = 0x8, /*[Type 32][CallType 16][Params 16][Args 32]*/
	T_MFUNCTION = 0x9, /*[Type 32][Class 32][This 32][CallType 16][Params 16][Args 32][Adjust 32]*/
	T_VTSHAPE = 0xA, /*[NumEntries 16][Entry1 4][Entry2 4]...*/
	//COBOL0 = 0xB,
	//COBOL1 = 0xC,
	//BARRAY = 0xD,
	T_LABEL = 0xE,
	//NULL = 0xF,
	//NOTTRAN = 0x10,
	//DIMARRAY = 0x11,
	//VFTPATH = 0x12,
	// 13-2F  unused
	//3A-EE tdump reports: Not yet handled
	//T_UNKNOWN3 = 0xEF, // tdump reports: Unknown type. Could be unresolved external type reference.
};

enum TypDefPasType
{
	T_SET = 0x0,
	T_SUBRANGE = 0x1,
	T_UNKNOWN = 0x2,
	T_PSTRING = 0x3,
	T_CLOSURE = 0x4,
	T_PROPERTY = 0x5,
	T_LSTRING = 0x6,
	T_VARIANT = 0x7,
	T_CLASSREF = 0x8,
	T_UNKNOWN2 = 0x9,
};

enum TypDefListType
{
	//T_SKIP = 0x0,
	T_ARGLIST = 0x1,
	T_DEFARG = 0x2,
	T_LIST = 0x3,
	T_FIELDLIST = 0x4,
	T_DERIVED = 0x5,
	T_BITFIELD = 0x6,
	T_METHODLIST = 0x7, // [[Access/prop 16][Type 32][Browser offset 32]]... prop: 0x4 - virtual, 0x8 - static, 0xc - friend, 0x10 - introducing virtual
	T_DIMCONU = 0x8,
	T_DIMCONLU = 0x9,
	T_DIMVARU = 0xA,
	T_DIMVARLU = 0xB,
	T_REFSYM = 0xC,
};

enum TypDefLstItemType
{
	T_BCLASS = 0x0,
	T_VBCLASS = 0x1,
	T_IVBCLASS = 0x2,
	T_ENUMERATE = 0x3,
	T_INDEX = 0x5,
	T_MEMBER = 0x6,
	T_STMEMBER = 0x7,
	T_METHOD = 0x8,
	T_NESTTYPE = 0x9,
	T_VFUNCTAB = 0xA,
	T_FRIENDCLS = 0xB,
};

const char * typeToString(int type)
{
	switch (type & TD_CLASS_MASK)
	{
	case TDC_ROOT:
		switch (type & TD_SUBTYPE_CLASS_MASK)
		{
		case TDST_GENERIC:
			switch (type & TD_SUBTYPE_MASK)
			{
			ENUM_TO_STR(T_MODIFIER);
			ENUM_TO_STR(T_POINTER);
			ENUM_TO_STR(T_ARRAY);
			ENUM_TO_STR(T_CLASS);
			ENUM_TO_STR(T_STRUCT);
			ENUM_TO_STR(T_UNION);
			ENUM_TO_STR(T_ENUM);
			ENUM_TO_STR(T_PROCEDURE);
			ENUM_TO_STR(T_MFUNCTION);
			ENUM_TO_STR(T_VTSHAPE);
			ENUM_TO_STR(T_LABEL);
			default:
				return 0;
			}
			break;
		case TDST_PASCAL:
			switch (type & TD_SUBTYPE_MASK)
			{
			ENUM_TO_STR(T_SET);
			ENUM_TO_STR(T_SUBRANGE);
			ENUM_TO_STR(T_UNKNOWN);
			ENUM_TO_STR(T_PSTRING);
			ENUM_TO_STR(T_CLOSURE);
			ENUM_TO_STR(T_PROPERTY);
			ENUM_TO_STR(T_LSTRING);
			ENUM_TO_STR(T_VARIANT);
			ENUM_TO_STR(T_CLASSREF);
			ENUM_TO_STR(T_UNKNOWN2);
			default:
				throw 0;
			}
			break;
		default:
			throw 0;
		}
		break;
	case TDC_LIST:
		switch (type & TD_TYPE_MASK)
		{
		//ENUM_TO_STR(T_SKIP);
		ENUM_TO_STR(T_ARGLIST);
		ENUM_TO_STR(T_DEFARG);
		ENUM_TO_STR(T_LIST);
		ENUM_TO_STR(T_FIELDLIST);
		ENUM_TO_STR(T_DERIVED);
		ENUM_TO_STR(T_BITFIELD);
		ENUM_TO_STR(T_METHODLIST);
		ENUM_TO_STR(T_DIMCONU);
		ENUM_TO_STR(T_DIMCONLU);
		ENUM_TO_STR(T_DIMVARU);
		ENUM_TO_STR(T_DIMVARLU);
		ENUM_TO_STR(T_REFSYM);
		default:
			throw 0;
		}
		break;
	case TDC_LIST_ITEM:
		switch (type & TD_TYPE_MASK)
		{
		ENUM_TO_STR(T_BCLASS);
		ENUM_TO_STR(T_VBCLASS);
		ENUM_TO_STR(T_IVBCLASS);
		ENUM_TO_STR(T_ENUMERATE);
		ENUM_TO_STR(T_INDEX);
		ENUM_TO_STR(T_MEMBER);
		ENUM_TO_STR(T_STMEMBER);
		ENUM_TO_STR(T_METHOD);
		ENUM_TO_STR(T_NESTTYPE);
		ENUM_TO_STR(T_VFUNCTAB);
		default:
			throw 0;
		}
		break;
	default:
		throw 0;
	}
}

const unsigned int TYPE_TYPE_MASK = 0xf0;

enum SizedStdTypes
{
	SST_INT = 0x10,
	SST_UINT = 0x20,
	SST_BOOL = 0x30,
	SST_REAL = 0x40,
	SST_COMPLEX = 0x50,
};

const unsigned int TYPE_SIZE_MASK = 0x0f;

enum StdIntSizesTypes
{
	SIS_8 = 0x0,
	SIS_16 = 0x1,
	SIS_32 = 0x2,
	SIS_64 = 0x3,
};

enum StdFloatSizesTypes
{
	SFS_32 = 0x0,
	SFS_64 = 0x1,
	SFS_80 = 0x2,
	SFS_128 = 0x3,
	SFS_48 = 0x4,
};

enum StdTypes
{
	ST_NONE = 0x0,
	// ST_ABS = 0x1,
	// ST_SEGMENT = 0x2,
	ST_VOID = 0x3,
	ST_BASIC_CURRENCY = 0x4,
	ST_NEAR_BASIC_STRING = 0x5,
	ST_FAR_BASIC_STRING = 0x6,
	// ST_CV3X =0x7,
	// 0x8-0xF same as 0x0-0x7
	ST_INT8 = 0x10,
	ST_INT16 = 0x11,
	ST_INT32 = 0x12,
	ST_INT64 = 0x13,
	// 0x14-17 interpreated as *??* int, looks like garbage
	// 0x18-1F same as 10-18
	ST_UINT8 = 0x20,
	ST_UINT16 = 0x21,
	ST_UINT32 = 0x22,
	ST_UINT64 = 0x23,
	// 0x24-2F same story
	ST_BOOL8 = 0x30,
	ST_BOOL16 = 0x31,
	ST_BOOL32 = 0x32,
	ST_BOOL64 = 0x33,
	// 0x34-3F same story
	ST_REAL32 = 0x40,
	ST_REAL64 = 0x41,
	ST_REAL80 = 0x42,
	ST_REAL128 = 0x43,
	ST_REAL48 = 0x44,
	// 0x45-4F seems unused
	ST_COMPLEX32 = 0x50,
	ST_COMPLEX64 = 0x51,
	ST_COMPLEX80 = 0x52,
	ST_COMPLEX128 = 0x53,
	ST_COMPLEX48 = 0x54,
	// 0x55-57 looks unused
	// 0x58-5F copy
	ST_BIT = 0x60,
	ST_PASCHAR = 0x61,
	// ST_UNDEFEXTERNAL = 0x62,
	// 0x63-67 seems unused
	// 0x68-6F copy again
	ST_CHAR = 0x70,
	ST_WCHAR = 0x71,
	ST_RINT16 = 0x72,
	ST_RUINT16 = 0x73,
	ST_RINT32 = 0x74,
	ST_RUINT32 = 0x75,
	ST_RINT64 = 0x76,
	ST_RUINT64 = 0x77,
	// 0x78-7F copy
};

const unsigned int TYPE_POINTER_MASK = 0xF00;

enum StdPointerTypes
{
	SPT_NEAR_PTR = 0x100,
	SPT_FAR_PTR = 0x200,
	SPT_HUGE_PTR = 0x300,
	SPT_NEAR_PTR32 = 0x400,
	SPT_FAR_PTR32 = 0x500,
	SPT_NEAR_PTR64 = 0x600,
};

inline bool IsStdType(int type)
{
	return type < 0x1000;
}

void PrintType(ostream & stm, int type)
{
	if (IsStdType(type))
	{
		if (type & TYPE_POINTER_MASK)
		{
			switch (type & TYPE_POINTER_MASK)
			{
			case SPT_NEAR_PTR: stm << "near"; break;
			case SPT_FAR_PTR: stm << "near"; break;
			case SPT_HUGE_PTR: stm << "huge"; break;
			case SPT_NEAR_PTR32: stm << "near32"; break;
			case SPT_FAR_PTR32: stm << "far32"; break;
			case SPT_NEAR_PTR64: stm << "near64"; break;
			}
			stm << " *";
		}
		switch (type & 0xff)
		{
		case ST_NONE: stm << "none"; break;
		case ST_VOID: stm << "void"; break;
		case ST_BASIC_CURRENCY: stm << "BasicCurr"; break;
		case ST_NEAR_BASIC_STRING: stm << "NearBasStr"; break;
		case ST_FAR_BASIC_STRING: stm << "FarBasStr"; break;
		case ST_INT8: stm << "int8"; break;
		case ST_INT16: stm << "int16"; break;
		case ST_INT32: stm << "int32"; break;
		case ST_INT64: stm << "int64"; break;
		case ST_UINT8: stm << "uint8"; break;
		case ST_UINT16: stm << "uint16"; break;
		case ST_UINT32: stm << "uint32"; break;
		case ST_UINT64: stm << "uint64"; break;
		case ST_BOOL8: stm << "bool8"; break;
		case ST_BOOL16: stm << "bool16"; break;
		case ST_BOOL32: stm << "bool32"; break;
		case ST_BOOL64: stm << "bool64"; break;
		case ST_REAL32: stm << "real32"; break;
		case ST_REAL64: stm << "real64"; break;
		case ST_REAL80: stm << "real80"; break;
		case ST_REAL128: stm << "real128"; break;
		case ST_REAL48: stm << "real48"; break;
		case ST_COMPLEX32: stm << "complex32"; break;
		case ST_COMPLEX64: stm << "complex64"; break;
		case ST_COMPLEX80: stm << "complex80"; break;
		case ST_COMPLEX128: stm << "complex128"; break;
		case ST_COMPLEX48: stm << "complex48"; break;
		case ST_BIT: stm << "Bit"; break;
		case ST_PASCHAR: stm << "PasChar"; break;
		case ST_CHAR: stm << "char"; break;
		case ST_WCHAR: stm << "wchar"; break;
		case ST_RINT16: stm << "rint16"; break;
		case ST_RUINT16: stm << "ruint16"; break;
		case ST_RINT32: stm << "rint32"; break;
		case ST_RUINT32: stm << "ruint32"; break;
		case ST_RINT64: stm << "rint64"; break;
		case ST_RUINT64: stm << "ruint64"; break;
		default:
			throw 0;
		}
	}
	else
	{
		stm << type;
	}
}

enum CallType
{
	CT_NEAR_CDECL = 0x0,
	CT_FAR_CDECL = 0x1,
	CT_NEAR_PASCAL = 0x2,
	CT_FAR_PASCAL = 0x3,
	CT_NEAR_FASTCALL = 0x4,
	CT_FAR_FASTCALL = 0x5,
	CT_PCODE = 0x6,
	CT_NEAR_STDCALL = 0x7,
	CT_FAR_STDCALL = 0x8,
	CT_NEAR_SYSCALL = 0x9,
	CT_FAR_SYSCALL = 0xA,
	CT_THIS_CALL = 0xB,
	CT_NEAR_FASTCALL2 = 0xC,
};

const unsigned int FT_CALL_TYPE_MASK = 0x0F;

const unsigned int FT_VARARGS = 0x40;
const unsigned int FT_FAST_THIS = 0x80;
const unsigned int FT_UNKFLAG1 = 0x100;
const unsigned int FT_UNKFLAG2 = 0x200;
const unsigned int FT_UNKFLAG3 = 0x400;
const unsigned int FT_UNKFLAG4 = 0x800;
const unsigned int FT_UNKFLAG5 = 0x1000;
const unsigned int FT_UNKFLAG6 = 0x2000;
const unsigned int FT_UNKFLAG7 = 0x4000;
const unsigned int FT_UNKFLAG8 = 0x8000;
const unsigned int FT_VALID_FLAGS = FT_UNKFLAG1 | FT_VARARGS | FT_UNKFLAG2 | FT_UNKFLAG3 | FT_UNKFLAG4 | FT_UNKFLAG5 | FT_UNKFLAG6 | FT_UNKFLAG7 | FT_UNKFLAG8;

ostream & PrintCallType(ostream & stm, int type)
{
	if ((type & ~FT_CALL_TYPE_MASK) & ~FT_VALID_FLAGS)
		throw 0;
	if (type & FT_VARARGS)
		stm << "variable args ";
	if (type & FT_FAST_THIS)
		stm << "fast this ";
	switch (type & FT_CALL_TYPE_MASK)
	{
	case CT_NEAR_CDECL: stm << "near cdecl"; break;
	case CT_FAR_CDECL: stm << "far cdecl"; break;
	case CT_NEAR_PASCAL: stm << "near pascal"; break;
	case CT_FAR_PASCAL: stm << "far pascal"; break;
	case CT_NEAR_FASTCALL: stm << "near fastcall"; break;
	case CT_FAR_FASTCALL: stm << "far fastcall"; break;
	case CT_PCODE: stm << "Pcode"; break;
	case CT_NEAR_STDCALL: stm << "near stdcall"; break;
	case CT_FAR_STDCALL: stm << "far stdcall"; break;
	case CT_NEAR_SYSCALL: stm << "near syscall"; break;
	case CT_FAR_SYSCALL: stm << "far syscall"; break;
	case CT_THIS_CALL: stm << "this call"; break;
	case CT_NEAR_FASTCALL2: stm << "near fastcall2"; break;
	default:
		throw 0;
	}
	return stm;
}

enum AccessType
{
	AT_NONE = 0,
	AT_PRIVATE = 1,
	AT_PROTECTED = 2,
	AT_PUBLIC = 3,
};

const char * accessToString(int accessType)
{
	switch (accessType & 0x3)
	{
	case AT_NONE: return "none";
	case AT_PRIVATE: return "private";
	case AT_PROTECTED: return "protected";
	case AT_PUBLIC: return "public";
	default:
		return 0;
	}
}

enum ModifierFlags
{
	MOD_CONST = 0x1,
	MOD_VOLATILE = 0x2,
};

const char * modTypToString(int type)
{
	switch (type)
	{
	case MOD_CONST: return "const";
	case MOD_VOLATILE: return "volatile";
	default:
		throw 0;
	}
}

const unsigned int PTR_TYPE_MASK = 0x1F;
const unsigned int PTR_MODE_MASK = 0xE0;

// pointer modifier flags
const unsigned int PMF_16_32 = 0x0100;
const unsigned int PMF_VOLATILE = 0x0200;
const unsigned int PMF_CONST = 0x0400;
const unsigned int PMF_VALID_FLAGS = PMF_16_32 | PMF_VOLATILE | PMF_CONST;

#define PTR_TYPE_FIELD(x) ((x) & PTR_TYPE_MASK)
#define PTR_MODE_FIELD(x) (((x) & PTR_MODE_MASK) >> 5)

enum PointerTypes
{
	PT_NEAR16 = 0x0,
	PT_FAR16 = 0x1,
	PT_HUGE16 = 0x2,
	PT_BASED_ON_SEGMENT = 0x3,
	PT_BASED_ON_VALUE = 0x4,
	PT_BASED_ON_SEGMENT_OF_VALUE = 0x5,
	PT_BASED_ON_ADDRESS_OF_SYMBOL = 0x6,
	PT_BASED_ON_SEG_OF_SYMBOL = 0x7,
	PT_BASED_ON_TYPE = 0x8,
	PT_BASED_ON_SELF = 0x9,
	PT_NEAR32 = 0xA,
	PT_FAR32 = 0xB,
};

const char * ptrTypeToString(int type)
{
	switch (type)
	{
	case PT_NEAR16: return "near16";
	case PT_FAR16: return "far16";
	case PT_HUGE16: return "huge16";
	case PT_BASED_ON_SEGMENT: return "based on segment";
	case PT_BASED_ON_VALUE: return "based on value";
	case PT_BASED_ON_SEGMENT_OF_VALUE: return "based on segment value";
	case PT_BASED_ON_ADDRESS_OF_SYMBOL: return "based on address of symbol";
	case PT_BASED_ON_SEG_OF_SYMBOL: return "based on seg of symbol";
	case PT_BASED_ON_TYPE: return "based on type";
	case PT_BASED_ON_SELF: return "based on self";
	case PT_NEAR32: return "near32";
	case PT_FAR32: return "far32";
	default:
		throw 0;
	}
}

enum PointerModes
{
	PM_SIMPLE = 0,
	PM_REFERENCE = 1,
	PM_TO_DATA_MEMBER = 2,
	PM_TO_METHOD = 3,
};

const char * ptrModToString(int type)
{
	switch (type)
	{
	case PM_SIMPLE: return "";
	case PM_REFERENCE: return "&";
	case PM_TO_DATA_MEMBER: return "to data member";
	case PM_TO_METHOD: return "to method";
	default:
		throw 0;
	}
}

const int CF_PACKED = 0x1;
const int CF_CONSTRUCTORS = 0x2;
const int CF_OVERLOADED_OPERATORS = 0x4;
const int CF_IS_NESTED = 0x8;
const int CF_NESTED_CLASSES = 0x10;
const int CF_OVERLOAD_ASSIGNMENT = 0x20;
const int CF_CASTING_METHODS = 0x40;
const int CF_FORWARD_REFERENCE = 0x80;
const int CF_DESTRUCTORS = 0x100;
const int CF_VALID_FLAGS = CF_PACKED | CF_CONSTRUCTORS | CF_OVERLOADED_OPERATORS |
	CF_IS_NESTED | CF_NESTED_CLASSES | CF_OVERLOAD_ASSIGNMENT | CF_CASTING_METHODS |
	CF_FORWARD_REFERENCE | CF_DESTRUCTORS;


struct SubSectDirItem
{
	short Type; // SubSectTypes
	short Index;
	int Offset;
	int Size;
};

struct SubSectDir
{
	char Unknown[0x4];
	int Num;
	char Unknown2[0x8];
	SubSectDirItem Items[1];
};

struct ModSeg
{
	short Index;
	short Flags;
	int Start;
	int End;
};

struct ModuleSubSect
{
	short OverlayNum; // ?
	short LibIndex; // ?
	short SegCount;
	short Unknown;
	short Name;
	short Time; // ?
	char Unknown2[0x10];
	ModSeg Segs[1];
};

enum MachineTypes
{
	Intel8080 = 0x0,
	Intel8086 = 0x1,
	Intel80286 = 0x2,
	Intel80386 = 0x3,
	Intel80486 = 0x4,
	IntelPentium = 0x5,
	MIPS_R4000 = 0x10,
	MC68000 = 0x20,
	MC68010 = 0x21,
	MC68020 = 0x22,
	MC68030 = 0x23,
	MC68040 = 0x24,
	DEC_Alpha = 0x30,
};

enum LanguageTypes
{
	LANG_C = 0x0,
	LANG_CPP = 0x1,
	LANG_FORTRAN = 0x2,
	LANG_MASM = 0x3,
	LANG_PASCAL = 0x4,
	LANG_BASIC = 0x5,
	LANG_COBOL = 0x6,
};

enum MemoryModelTypes
{
	MODEL_NEAR = 0,
	MODEL_FAR = 1,
	MODEL_HUGE = 2,
};

enum FloatingTypes
{
	FPU_HARDWARE = 0,
	FPU_EMULATION = 1,
	FPU_ALTMATH = 2,
};

#pragma pack(2)
struct SCompiler
{
	int MachineAndCompilerFlags;
	unsigned char CompNameLen;
	char CompName[1];
};

struct SRegister
{
	int Type;
	short Register;
	int Name;
	int BrowserOffset;
};

struct SConst
{
	int Type;
	int Name;
	int BrowserOffset;
	char Value[1];
};

struct SUdt
{
	int Type;
	int Name;
	int BrowserOffset;
};

struct SSearch
{
	int Offset;
	short Segment;
	short CodeSymbols;
	short DataSymbols;
	int FirstData;
	short Unknown;
};

struct SGProcRef
{
	int Unk1;
	int Type;
	int Name;
	int BrowserOffset;
	int Offset;
	unsigned short Segment;
	int Unk2;
};

struct SGDataRef
{
	int Unk1;
	int Type;
	int Name;
	int BrowserOffset;
	int Offset;
	unsigned short Segment;
};

struct SPConstant
{
	int Type;
	short Property;
	int Name;
	int BrowserOffset;
	char Value[1];
};

struct SBPRel32
{
	int EbpOffset;
	short Type;
	short Unknown1;
	short Name;
	short Unknown2[3];
};

struct SData32
{
	int Offset;
	short Segment;
	short Flags;
	int Type;
	int Name;
	int BrowserOffset;
};

struct SProc32
{
	int Parent;
	int End;
	int Next;
	int Size1;
	char Unknown[0x04];
	int Size;
	int Start;
	short Segment;
	short Unknown2;
	short Type;
	short Unknown3;
	short Name;
	char Unknown4[0x6];
	// for global only
	unsigned char LinkerNameLen;
	char LinkerName[1];
};

struct SBlock32
{
	int Parent;
	int End;
	int Size;
	int Start;
	short Segment;
	int Name;
};

struct SWith32
{
	int Parent;
	int CodeLength;
	int ProcedureOffset;
	short Segment;
	short Flags;
	int Type;
	int Name;
	int VarOffset;
};

struct SEntry32
{
	int Offset;
	unsigned short Segment;
};

struct SOptVar32
{
	unsigned short Num;
	struct
	{
		int Start;
		int Size;
		short Register;
	} Items[1];
};

struct SProcRet32
{
	int Offset;
	short Lenght;
};

// Save Regs Masks
const short S_EBX = 1;
const short S_EDI = 2;
const short S_ESI = 4;

struct SSaveRegs32
{
	short Mask; // 7 = EBX EDI ESI; 1 = EBX; 6 = EDI, ESI; 5 = EBX ESI
	int EbpOffset;
};


struct Modifier
{
	unsigned short Mod;
	int Type;
};

struct Pointer
{
	unsigned short PtrTypeMod;
	int PointsTo;
	// valid only for member or method pointers
	unsigned short Format;
	int Class;
};

// T_ARRAY
struct Array
{
	int ElementType;
	int IndexerType;
	int Name;
	// Next goes variable length ArraySize and NumElements fields
};

// T_CLASS
// T_STRUCT
struct Class
{
	unsigned short NumMembers; // number of members
	int FieldIndex; // reference to FIELDLIST description of fields
	unsigned short Flags;
	int ContainingClass;
	int DerivationList;
	int VTable;
	int Name;
	// next goes variable length field Size (size of instance)
};

struct Union
{
	unsigned short NumMembers;
	int FieldIndex;
	unsigned short Flags;
	int ContainingClass;
	int Name;
	// next goes variable length field Size (size of instance)
};

struct Enum
{
	unsigned short Count;
	int Type;
	int Fields;
	int Class;
	int Name;
};

struct Procedure
{
	int Type;
	unsigned short CallType;
	unsigned short Params;
	int ArgList;
};

// T_MFUNCTION = 0x9, /*[Type 32][Class 32][This 32][CallType 16][Params 16][Args 32][Adjust 32]*/
struct MemberFunction
{
	int Type;
	int Class;
	int This;
	unsigned short CallType;
	unsigned short Params;
	int ArgList;
	int Adjust;
};


struct BClass
{
	int Index;
	unsigned short Access;
	short Offset;
};

struct VBClass
{
	int Base;
	int VirtualBase;
	short Access;
	short VirtBasePtrOffset;
	unsigned short Unknown; // 0x8001
	short VirtBaseIndex;
};

struct Enumerate
{
	unsigned short Attribs;
	int Name;
	int BrowserOffset;
};

struct Member
{
	int Type;
	unsigned short Access;
	int Name;
	int BrowserOffset;
	short Offset;
};

struct StaticMember
{
	int Type;
	unsigned short Access;
	int Name;
	int BrowserOffset;
};

struct Method
{
	unsigned short Count;
	int Index;
	int Name;
};

struct NestType
{
	int Index;
	int Name;
	int BrowserOffset;
};


const char * TdsBase = 0;
const char * NamesSection = 0;
bool DoEcho = true;


const int BYTE_SIZE = sizeof(BYTE);
const int WORD_SIZE = sizeof(WORD);
const int DWORD_SIZE = sizeof(DWORD);

inline char EatChar(const char *& pos)
{
	char result = *reinterpret_cast<const char*>(pos);
	pos += BYTE_SIZE;
	return result;
}

inline unsigned char EatUChar(const char *& pos)
{
	unsigned char result = *reinterpret_cast<const unsigned char*>(pos);
	pos += BYTE_SIZE;
	return result;
}

inline short EatShort(const char *& pos)
{
	short result = *reinterpret_cast<const short*>(pos);
	pos += WORD_SIZE;
	return result;
}

inline unsigned short EatUShort(const char *& pos)
{
	unsigned short result = *reinterpret_cast<const unsigned short*>(pos);
	pos += WORD_SIZE;
	return result;
}

inline int EatInt(const char *& pos)
{
	int result = *reinterpret_cast<const int*>(pos);
	pos += DWORD_SIZE;
	return result;
}

struct EscapedField
{
	const char * Ptr;
	size_t Size;
};

inline EscapedField EatEscapedField(const char *& pos)
{
	EscapedField result;
	int prefix = *reinterpret_cast<const short*>(pos);
	pos += WORD_SIZE;
	if (prefix >= 0)
	{
		result.Ptr = pos;
		result.Size = WORD_SIZE;
		return result;
	}
	else
	{
		switch (prefix & 0xFF)
		{
		case 1:
		case 2:
			result.Ptr = pos;
			result.Size = WORD_SIZE;
			pos += WORD_SIZE;
			return result;
		case 3:
		case 4:
			result.Ptr = pos;
			result.Size = DWORD_SIZE;
			pos += DWORD_SIZE;
			return result;
		default:
			throw 0;
		}
	}
}

void PrintEscapedField(ostream & stm, EscapedField fld)
{
	switch (fld.Size)
	{
	case 2:
		stm << *reinterpret_cast<const unsigned short*>(fld.Ptr);
		break;
	case 4:
		stm << *reinterpret_cast<const unsigned int*>(fld.Ptr);
		break;
	default:
		throw 0;
	}
}

const char * LocateName(int name)
{
	const char * pos = NamesSection;
	int num = EatInt(pos);
	if (name > num)
		return 0;
	for (int i = 0; i < name - 1; i++)
		pos += EatUChar(pos) + 1;
	return pos + 1;
}

int IdByName(const char * name)
{
	const char * pos = NamesSection;
	int num = EatInt(pos);
	for (int i = 0; i < num; i++)
	{
		int len = EatUChar(pos);
		if (strcmp(pos + 1, name) == 0)
			return i + 1;
		pos += len + 1;
	}
	return 0;
}

const char * IdByName(int name)
{
	const char * pos = NamesSection;
	int num = EatInt(pos);
	if (name > num)
		return 0;
	for (int i = 0; i < name - 1; i++)
		pos += EatChar(pos) + 1;
	return pos + 1;
}

void PrintSymbolSearch(const SSearch * ss)
{
	cout << ss->Segment << ':' << ss->Offset << "  CodeSyms: " << ss->CodeSymbols << "  DataSyms " << ss->DataSymbols << "  FirstData: " << ss->FirstData;
}

void PrintGlobalProcRef(const SGProcRef * p)
{
	cout << p->Unk1 << "  type: ";
	PrintType(cout, p->Type);
	cout << "  " << p->Segment << ":" << p->Offset << "  " << LocateName(p->Name) << " [" << p->Name << "]  Browser offset: " << p->BrowserOffset;
}

void PrintGlobalDataRef(const SGDataRef * d)
{
	cout << d->Unk1 << "  type: ";
	PrintType(cout, d->Type);
	cout << "  " << d->Segment << ":" << d->Offset << "  " << LocateName(d->Name) << " [" << d->Name << "]  Browser offset: " << d->BrowserOffset;
}

void PrintCompiler(const SCompiler * comp)
{
	cout << "Compiler: ";
	for (int i = 0; i < comp->CompNameLen; i++)
		cout << comp->CompName[i];
}

void PrintSRegister(const SRegister * r)
{
	cout << "Type: " << r->Type << "  Register: " << regToString(r->Register) << "  " << LocateName(r->Name) << " [" << r->Name << "]  Browser offset: " << r->BrowserOffset;
}

void PrintSConst(const SConst * c)
{
	cout << "Type: " << c->Type << "  Name: [" << c->Name << "]";
}

void PrintSUdt(const SUdt * u)
{
	cout << "Type: " << u->Type << " Name: [" << u->Name << "]";
}

void PrintSUsing(const char * u)
{
	short num = *reinterpret_cast<const short*>(u);
	u += 2;
	cout << endl;
	while (num--)
	{
		int name = *reinterpret_cast<const int*>(u);
		u += 4;
		cout << "  [" << name << "]" << endl;
	}
}

void PrintSPConstant(const SPConstant * c)
{
	cout << "  Type: " << c->Type << "  Name: " << LocateName(c->Name) << " [" << c->Name << "]  Property: " << c->Property << "  Browser offset: " << c->BrowserOffset;
}

void PrintSBPRel32(const SBPRel32 * bp)
{
	cout << "  type: " << bp->Type << "  [EBP+" << bp->EbpOffset << "]  Name: " << LocateName(bp->Name) << " [" << bp->Name << "]";
}

void PrintSData32(const SData32 * dat)
{
	cout << "  type: " << dat->Type << "  " << dat->Segment << ":" << dat->Offset << "  " << LocateName(dat->Name) << " [" << dat->Name << "]  Browser offset: " << dat->BrowserOffset << endl;
	cout << "    flags: " << dat->Flags << endl;
}

void PrintSProc32(const SProc32 * proc, size_t size)
{
	cout << endl << "  " << proc->Segment << ":" << proc->Start << "-" << proc->Start + proc->Size1 - 1 << "  " << LocateName(proc->Name) << " [" << proc->Name << "]" << endl;
	cout << "  Debug: " << proc->Segment << ":" << proc->Start << "-" << proc->Start + proc->Size << "  Type: " << proc->Type << endl;
	cout << "  Parent: " << proc->Parent << "  End: " << proc->End << "  Next: " << proc->Next << endl;
	if (size > (size_t)((char*)&proc->LinkerNameLen - (char*)proc))
	{
		cout << "  Linker name: '";
		for (int i = 0; i < proc->LinkerNameLen; i++)
			cout << proc->LinkerName[i];
		cout << "'";
	}
}

void PrintSBlock32(const SBlock32 * b)
{
	cout << "  Parent: " << b->Parent << "  End: " << b->End << "  " << b->Segment << ":" << b->Start << "-" << (b->Start + b->Size - 1) << "  " << LocateName(b->Name) << " [" << b->Name << "]";
}

void PrintSWith32(const SWith32 * w)
{
	cout << "Parent: " << w->Parent << "  Segment: " << w->Segment << "  Procedure Offset: " << w->ProcedureOffset << endl;
	cout << "  Code Length: " << w->CodeLength << "  Flags: " << w->Flags << endl;
	cout << "  Type: " << w->Type << "  Name: " << LocateName(w->Name) << " [" << w->Name << "]" << endl;
	cout << "  Var Offset: " << w->VarOffset << endl;
}

void PrintSEntry32(const SEntry32 * e)
{
	cout << "   " << e->Segment << ":" << e->Offset;
}

void PrintSOptVar32(const SOptVar32 * o)
{
	cout << endl;
	for (size_t i = 0; i < o->Num; i++)
		cout << "  Start: " << o->Items[i].Start << "  Len: " << o->Items[i].Size << "  Reg: " << regToString(o->Items[i].Register) << endl;
}

void ParseSymbols(const char * start, const char * end)
{
	const char * pos = start;
	const SSearch * symbolSearch;
	int codes = 0;
	int datas = 0;
	bool inProc;
	while (pos != end)
	{
		int size = EatShort(pos);
		int type = EatShort(pos);
		PrintSymAlignTyp(cout, type);
		cout << "  ";
		switch (type & 0xFF00)
		{
		case 0:
			switch (type & 0xFF)
			{
			case S_COMPILE:
				PrintCompiler(reinterpret_cast<const SCompiler *>(pos));
				break;
			case S_REGISTER:
				PrintSRegister(reinterpret_cast<const SRegister *>(pos));
				break;
			case S_CONST:
				PrintSConst(reinterpret_cast<const SConst *>(pos));
				break;
			case S_UDT:
				PrintSUdt(reinterpret_cast<const SUdt *>(pos));
				break;
			case S_SSEARCH:
				symbolSearch = reinterpret_cast<const SSearch *>(pos);
				PrintSymbolSearch(symbolSearch);
				break;
			case S_END:
				inProc = false;
				break;
			case S_GPROCREF:
				PrintGlobalProcRef(reinterpret_cast<const SGProcRef *>(pos));
				break;
			case S_GDATAREF:
				PrintGlobalDataRef(reinterpret_cast<const SGDataRef *>(pos));
				break;
			//case S_USES:
			//	break;
			//case S_NAMESPACE:
			//	break;
			case S_USING:
				PrintSUsing(pos);
				break;
			case S_PCONSTANT:
				PrintSPConstant(reinterpret_cast<const SPConstant *>(pos));
				break;
			default:
				throw 0;
			}
			break;
		case 0x100:
			throw 0;
		case 0x200:
			switch (type & 0xFF)
			{
			case S_BPREL:
				PrintSBPRel32(reinterpret_cast<const SBPRel32 *>(pos));
				break;
			case S_LDATA:
				PrintSData32(reinterpret_cast<const SData32 *>(pos));
				datas++;
				break;
			case S_GDATA:
				PrintSData32(reinterpret_cast<const SData32 *>(pos));
				datas++;
				break;
			case S_LPROC:
				PrintSProc32(reinterpret_cast<const SProc32 *>(pos), size - 2);
				inProc = true;
				codes++;
				break;
			case S_GPROC:
				PrintSProc32(reinterpret_cast<const SProc32 *>(pos), size - 2);
				inProc = true;
				codes++;
				break;
			case S_BLOCK:
				PrintSBlock32(reinterpret_cast<const SBlock32 *>(pos));
				break;
			case S_WITH:
				PrintSWith32(reinterpret_cast<const SWith32 *>(pos));
				break;
			case S_ENTRY:
				PrintSEntry32(reinterpret_cast<const SEntry32 *>(pos));
				break;
			case S_OPTVAR:
				PrintSOptVar32(reinterpret_cast<const SOptVar32 *>(pos));
				break;
			//case S_PROCRET:
			//	break;
			//case S_SAVREGS:
			//	break;
			case S_SLINK:
				cout << "Offset: " << *reinterpret_cast<const int*>(pos);
				break;
			default:
				throw 0;
			}
			break;
		default:
			throw 0;
		}
		cout << endl;
		pos += size - 2;
	}
}

void ParseAlignSym(const char * start, const char * end, int moduleIndex)
{
	const char * pos = start;
	int Unknown1 = EatInt(pos);
	ParseSymbols(pos, end);
}

struct GlobalSymHeader
{
	unsigned short SymHash;
	unsigned short AddrHash;
	unsigned int cbSymbols;
	unsigned int cbSymHash;
	unsigned int cbAddrHash;
	unsigned int cUDTs;
	unsigned int cOthers;
	unsigned int Total;
	unsigned int cNamespaces;
};

void ParseGlobalSym(const char * start)
{
	const GlobalSymHeader * hdr = reinterpret_cast<const GlobalSymHeader *>(start);
	const char * pos = start + sizeof(GlobalSymHeader);
	ParseSymbols(pos, pos + hdr->cbSymbols);
}

void ParseSrcModule(const char * start, const char * end)
{
	const char * pos = start;
	cout << "Segment ranges:" << endl;
	short numFiles = EatShort(pos);
	short numRanges = EatShort(pos);
	const int * filesOffsets = reinterpret_cast<const int*>(pos);
	const int * ranges = reinterpret_cast<const int*>(pos + 4 * numFiles);
	const short * segs = reinterpret_cast<const short*>(pos + 4 * numFiles + 8 * numRanges);
	for (int r = 0; r < numRanges; r++)
	{
		cout << "  " << segs[r] << ":" << ranges[r*2] << "-" << ranges[r*2+1] << endl;
	}
	cout << "Source files:" << endl;
	for (int f = 0; f < numFiles; f++)
	{
		pos = start + filesOffsets[f];
		int offset = pos - TdsBase;
		short numFileRanges = EatShort(pos);
		int name = EatInt(pos);
		cout << "  File: " << LocateName(name) << " [" << name << "]  Offset: " << offset << endl;
		const int* numbersOffsets = reinterpret_cast<const int*>(pos);
		const int* fileRanges = reinterpret_cast<const int*>(pos + 4 * numFileRanges);
		for (int r = 0; r < numFileRanges; r++)
		{
			pos = start + numbersOffsets[r];
			short seg = EatShort(pos);
			cout << "  Range: " << seg << ":" << fileRanges[r*2] << "-" << fileRanges[r*2 + 1] << endl;
			short linesNum = EatShort(pos);
			cout << "    Line numbers:";
			const int * offsets = reinterpret_cast<const int*>(pos);
			const short * lineNumbers = reinterpret_cast<const short*>(pos + 4 * linesNum);
			for (int l = 0; l < linesNum; l++)
			{
				if (l % 4 == 0)
				{
					cout << endl;
					cout << "    ";
				}
				cout << dec << lineNumbers[l] << ":" << hex << offsets[l] << "  ";
			}
			cout << endl;
		}
	}
}

void ParseArray(const char * start)
{
	const Array * arr = reinterpret_cast<const Array *>(start);
	const char * pos = start + sizeof(Array);
	cout << "  Type: " << arr->ElementType << "  Indexed by: " << arr->IndexerType << "  Name: " << arr->Name << endl;
	cout << "  Size: ";
	PrintEscapedField(cout, EatEscapedField(pos));
	cout << "  Elements: ";
	PrintEscapedField(cout, EatEscapedField(pos));
	cout << endl;
}


void PrintStructFlags(unsigned flags)
{
	cout << "  Packed: " << ((flags & CF_PACKED) ? "Yes" : "No") <<
		"  Constructors: " << ((flags & CF_CONSTRUCTORS) ? "Yes" : "No") <<
		"  Destructors: " << ((flags & CF_DESTRUCTORS) ? "Yes" : "No") <<
		"  Overloaded operators: " << ((flags & CF_OVERLOADED_OPERATORS) ? "Yes" : "No") << endl;
	cout << "  Is nested: " << ((flags & CF_IS_NESTED) ? "Yes" : "No") <<
		"  Nested classes: " << ((flags & CF_NESTED_CLASSES) ? "Yes" : "No") <<
		"  Overload assignments: " << ((flags & CF_NESTED_CLASSES) ? "Yes" : "No") << endl;
	cout << "  Casting methods: " << ((flags & CF_CASTING_METHODS) ? "Yes" : "No") <<
		"  Forward Ref: " << ((flags & CF_FORWARD_REFERENCE) ? "Yes" : "No") << endl;
}

void ParseStruct(const char * start, unsigned type)
{
	const char * pos = start;
	EscapedField size;
	switch (type)
	{
	case T_CLASS:
	case T_STRUCT:
		const Class * cls;
		cls = reinterpret_cast<const Class *>(pos);
		pos += sizeof cls;
		size = EatEscapedField(pos);
		if (cls->Flags & ~CF_VALID_FLAGS)
			throw 0;
		if (DoEcho)
		{
			cout << "  Fields: " << cls->NumMembers << "  FieldIdx: " << cls->FieldIndex << "  Name: " << LocateName(cls->Name) << " [" << cls->Name << "]" << endl;
			cout << "  Containing Class: " << cls->ContainingClass << "  Length: ";
			PrintEscapedField(cout, size);
			cout << endl;
			cout << "  Derivation list: " << cls->DerivationList << "  VTable: " << cls->VTable << endl;
			PrintStructFlags(cls->Flags);
		}
		break;
	case T_UNION:
		const Union * un;
		un = reinterpret_cast<const Union *>(pos);
		pos += sizeof un;
		size = EatEscapedField(pos);
		if (un->Flags & ~CF_VALID_FLAGS)
			throw 0;
		if (DoEcho)
		{
			cout << "  Fields: " << un->NumMembers << "  FieldIdx: " << un->FieldIndex << "  Name: " << LocateName(un->Name) << " [" << un->Name << "]" << endl;
			cout << "  Containing Class: " << un->ContainingClass << "  Length: ";
			PrintEscapedField(cout, size);
			cout << endl;
			PrintStructFlags(cls->Flags);
		}
		break;
	default:
		throw 0;
	}
}

enum VirtTblDesctiptorType
{
	VTDT_NEAR16 = 0x0,
	VTDT_FAR16 = 0x1,
	VTDT_THIN = 0x2,
	VTDT_ADDR_POINT_DISPLACEMENT_OUTERMOST_CLASS = 0x3,
	VTDT_FAR_PTR_METACLASS_DESCR = 0x4,
	VTDT_NEAR32 = 0x5,
	VTDT_FAR32 = 0x6,
};

void ParseVirtTblShape(const char * start)
{
	const char * pos = start;
	int num = EatUShort(pos);
	for (int i = 0; i < num; i++)
	{
		unsigned int byte = pos[i / 2];
		if (i % 2 == 1)
		{
			byte >>= 4;
		}
		byte &= 0xF;
		cout << "  Descriptor: ";
		switch (byte)
		{
		case VTDT_NEAR16: cout << "near"; break;
		case VTDT_FAR16: cout << "far"; break;
		case VTDT_THIN: cout << "thin"; break;
		case VTDT_ADDR_POINT_DISPLACEMENT_OUTERMOST_CLASS: cout << "addr point displacement to outermost class"; break;
		case VTDT_FAR_PTR_METACLASS_DESCR: cout << "far * metaclass descriptor"; break;
		case VTDT_NEAR32: cout << "near32"; break;
		case VTDT_FAR32: cout << "far32"; break;
		default:
			throw 0;
		}
		cout << endl;
	}
}

void ParseArgList(const char * start)
{
	const char * pos = start;
	int num = EatUShort(pos);
	const int * types = reinterpret_cast<const int *>(pos);
	for (int i = 0; i < num; i++)
	{
		cout << "  Type: ";
		PrintType(cout, types[i]);
		cout << endl;
	}
}

void ParseFieldList(const char * start, const char * end)
{
	const char * pos = start;
	while (pos < end)
	{
		int type = EatUShort(pos);
		if (type == 0xf1f2u)
			continue;
		const BClass * bcls;
		const VBClass * vbcls;
		const Enumerate * enumr;
		const Member * member;
		const StaticMember * stMember;
		const Method * method;
		const NestType * nestType;
		if (DoEcho)
			cout << "  " << typeToString(type);
		int vtabType;
		int vtabOffset;
		int continuationIndex;
		int enumType;
		int enumValue;
		switch (type & TD_TYPE_MASK)
		{
		case T_BCLASS:
			bcls = reinterpret_cast<const BClass *>(pos);
			if (DoEcho)
				cout << "  Type: " << bcls->Index << "  Offset: " << bcls->Offset << "  Access: " << accessToString(bcls->Access);
			pos += sizeof(BClass);
			break;
		case T_VBCLASS:
		case T_IVBCLASS:
			vbcls = reinterpret_cast<const VBClass *>(pos);
			if (vbcls->Unknown != 0x8001u)
				cout << "catch";
			if (DoEcho)
			{
				cout << "  Base: " << vbcls->Base << "  Virtual Base: " << vbcls->VirtualBase << "  Access: " << accessToString(vbcls->Access) << endl;
				cout << "    Virtual Base Pointer Offset: " << vbcls->VirtBasePtrOffset << "  Virtual Base Index: " << vbcls->VirtBaseIndex;
			}
			pos += sizeof(VBClass);
			break;
		case T_ENUMERATE:
			enumr = reinterpret_cast<const Enumerate *>(pos);
			pos += sizeof(Enumerate);
			enumType = EatUShort(pos);
			switch (enumType)
			{
			case 0x8002:
				enumValue = EatUShort(pos);
				break;
			case 0x8004:
				enumValue = EatInt(pos);
				break;
			default:
				enumValue = enumType;
			}
			if (DoEcho)
				cout << "  Attr: " << enumr->Attribs << "  Value: " << enumValue << "  Name: " << LocateName(enumr->Name) << " [" << enumr->Name << "]  Browser offset: " << enumr->BrowserOffset;
			break;
		case T_INDEX:
			continuationIndex = EatInt(pos);
			if (DoEcho)
				cout << "	 continuation index: " << continuationIndex;
			break;
		case T_MEMBER:
			member = reinterpret_cast<const Member *>(pos);
			if (DoEcho)
				cout << "  Type: " << member->Type << "  Offs: " << member->Offset << "  Access: " << accessToString(member->Access) << "  Name: " << LocateName(member->Name) << " [" << member->Name << "]  Browser offset: " << member->BrowserOffset;
			pos += sizeof(Member);
			break;
		case T_STMEMBER:
			stMember = reinterpret_cast<const StaticMember *>(pos);
			if (DoEcho)
				cout << "  Type: " << stMember->Type << "  Access: " << accessToString(stMember->Access) << "  Name: " << LocateName(stMember->Name) << " [" << stMember->Name << "]  Browser offset: " << stMember->BrowserOffset;
			pos += sizeof(StaticMember);
			break;
		case T_METHOD:
			method = reinterpret_cast<const Method *>(pos);
			if (DoEcho)
				cout << "  count: " << method->Count << "  MethodIdx: " << method->Index << "  Name: " << LocateName(method->Name) << " [" << method->Name << "]";
			pos += sizeof(Method);
			break;
		case T_NESTTYPE:
			nestType = reinterpret_cast<const NestType *>(pos);
			if (DoEcho)
				cout << "  Index: " << nestType->Index << "  Name: " << LocateName(nestType->Name) << " [" << nestType->Name << "]  Browser offset: " << nestType->BrowserOffset;
			pos += sizeof(NestType);
			break;
		case T_VFUNCTAB:
			vtabType = EatInt(pos);
			vtabOffset = EatShort(pos);
			if (DoEcho)
				cout << "  Type: " << vtabType << "  vtab offs: " << vtabOffset;
			break;
		default:
			throw 0;
		}
		if (DoEcho)
			cout << endl;
	}
}

// T_METHODLIST 0x7
struct MethodLstItem
{
	unsigned short AccessStorage;
	int Type;
	int BrowserOffset;
	int VtabOffset; // only for virtual and introducing virtual
};

#define METHOD_ACCESS_FIELD(x) ((x) & 3)
#define METHOD_STORAGE_FIELD(x) (((x) & 0x001C) >> 2)
#define METHOD_FLAGS_FIELD(x) ((x) & 0xFFE0)

const unsigned int MDF_DEFAULT1 = 0x0020;
const unsigned int MDF_OPERATOR_OVERLOAD = 0x0100;
const unsigned int MDF_CONVERSION_OPERATOR = 0x0200;
const unsigned int MDF_CONSTRUCTOR = 0x0400;
const unsigned int MDF_DESTRUCTOR = 0x0800;
const unsigned int MDF_DEFAULT2 = 0x1000;
const unsigned int MDF_VALID_FLAGS = (MDF_DEFAULT1 | MDF_OPERATOR_OVERLOAD | MDF_CONVERSION_OPERATOR | MDF_CONSTRUCTOR | MDF_DESTRUCTOR | MDF_DEFAULT2);

enum MethodStorageTypes
{
	MST_NONE = 0,
	MST_VIRTUAL = 1,
	MST_STATIC = 2,
	MST_FRIEND = 3,
	MST_INTRODUCING_VIRTUAL = 4,
	MST_PURE_VIRTUAL = 5,
	MST_PURE_INTRODUCING_VIRTUAL = 6,
};

const char * methodStorToString(int type)
{
	switch (type)
	{
	case MST_NONE: return "vanilla";
	case MST_VIRTUAL: return "virtual";
	case MST_STATIC: return "static";
	case MST_FRIEND: return "friend";
	case MST_INTRODUCING_VIRTUAL: return "introducing virtual";
	case MST_PURE_VIRTUAL: return "pure virtual";
	case MST_PURE_INTRODUCING_VIRTUAL: return "pure introducing virtual";
	default:
		throw 0;
	}
}

void ParseMethodList(const char * start, const char * end)
{
	const char * pos = start;
	while (pos != end)
	{
		const MethodLstItem * met = reinterpret_cast<const MethodLstItem *>(pos);
		cout << "  Type: " << met->Type << "  Access: " << accessToString(met->AccessStorage) << "  Prop: " <<
			methodStorToString(METHOD_STORAGE_FIELD(met->AccessStorage));
		if (METHOD_STORAGE_FIELD(met->AccessStorage) == MST_VIRTUAL || METHOD_STORAGE_FIELD(met->AccessStorage) == MST_INTRODUCING_VIRTUAL ||
			METHOD_STORAGE_FIELD(met->AccessStorage) == MST_PURE_VIRTUAL || METHOD_STORAGE_FIELD(met->AccessStorage) == MST_PURE_INTRODUCING_VIRTUAL)
		{
			cout << "  Vtab Offs: " << met->VtabOffset;
			pos += 14;
		}
		else
		{
			pos += 10;
		}
		cout << "  Browser offset: " << met->BrowserOffset << endl;
		if (METHOD_FLAGS_FIELD(met->AccessStorage) & ~MDF_VALID_FLAGS)
			throw 0;
		cout << "  Default1: " << (met->AccessStorage & MDF_DEFAULT1 ? "yes" : "no") <<
			"  Overloaded operator: " << (met->AccessStorage & MDF_OPERATOR_OVERLOAD ? "yes" : "no") <<
			"  Conversion operator: " << (met->AccessStorage & MDF_CONVERSION_OPERATOR ? "yes" : "no") << endl;
		cout << "  Constructor: " << (met->AccessStorage & MDF_CONSTRUCTOR ? "yes" : "no") <<
			"  Destructor: " << (met->AccessStorage & MDF_DESTRUCTOR ? "yes" : "no") <<
			"  Default2: " << (met->AccessStorage & MDF_DEFAULT2 ? "yes" : "no") << endl;
	}
}

void ParseGlobalTypes(const char * start)
{
	const char * pos = start;
	int unknown = EatInt(pos);
	size_t num = EatInt(pos);
	const int * offsets = reinterpret_cast<const int *>(pos);
	for (size_t i = 0; i < num; i++)
	{
		const Modifier * mod;
		const Pointer * ptr;
		const Enum * en;
		const Procedure * proc;
		const MemberFunction * mfunc;

		pos = start + offsets[i];
		int len = EatShort(pos);
		int type = EatShort(pos);
		if (DoEcho)
			cout << start + offsets[i] - TdsBase << "  Type: " << (i + 0x1000) << "  Len: " << len << "  " << typeToString(type) << endl;
		switch (type & TD_CLASS_MASK)
		{
		case TDC_ROOT:
			switch (type & TD_TYPE_MASK)
			{
			case T_MODIFIER:
				mod = reinterpret_cast<const Modifier *>(pos);
				if (DoEcho)
				{
					cout << "  Type: " << mod->Type << "  " <<
						((mod->Mod & MOD_CONST) ? "const " : "") <<
						((mod->Mod & MOD_VOLATILE) ? "volatile" : "") << endl;
				}
				break;
			case T_POINTER:
				ptr = reinterpret_cast<const Pointer *>(pos);
				ptrTypeToString(PTR_TYPE_FIELD(ptr->PtrTypeMod));
				if (DoEcho)
				{
					cout << "  " << ptrTypeToString(PTR_TYPE_FIELD(ptr->PtrTypeMod)) << " " << ptrModToString(PTR_MODE_FIELD(ptr->PtrTypeMod)) <<
						"  (PtrType: " << PTR_TYPE_FIELD(ptr->PtrTypeMod) << "  PtrMode: " << PTR_MODE_FIELD(ptr->PtrTypeMod) << ")" << endl;
					cout << "  Points to: ";
					PrintType(cout, ptr->PointsTo);
					cout << endl;
					if (PTR_MODE_FIELD(ptr->PtrTypeMod) == PM_TO_DATA_MEMBER ||
						PTR_MODE_FIELD(ptr->PtrTypeMod) == PM_TO_METHOD)
					{
						cout << "  Member/Method class: " << ptr->Class << " Format: " << ptr->Format << endl;
					}
				}
				break;
			case T_ARRAY:
				ParseArray(pos);
				break;
			case T_CLASS:
			case T_STRUCT:
			case T_UNION:
				ParseStruct(pos, type);
				break;
			case T_ENUM:
				en = reinterpret_cast<const Enum *>(pos);
				if (DoEcho)
				{
					cout << "  Count: " << en->Count << "  Type: ";
					PrintType(cout, en->Type);
					cout << "  Fields: " << en->Fields << "  Class: " << en->Class << "  Name: " << LocateName(en->Name) << " [" << en->Name << "]" << endl;
				}
				break;
			case T_PROCEDURE:
				proc = reinterpret_cast<const Procedure *>(pos);
				cout << "  ";
				PrintCallType(cout, proc->CallType);
				cout << " returns: ";
				PrintType(cout, proc->Type);
				cout << endl << "  Params: " << proc->Params << "  ArgList: " << proc->ArgList << endl;
				break;
			case T_MFUNCTION:
				mfunc = reinterpret_cast<const MemberFunction *>(pos);
				cout << "  ";
				PrintCallType(cout, mfunc->CallType);
				cout << " returns: ";
				PrintType(cout, mfunc->Type);
				cout << endl << "  Class: " << mfunc->Class << "  'this': " << mfunc->This << "  Params: " << mfunc->Params << "  Args: " << mfunc->ArgList << "  `this' adjust: " << mfunc->Adjust << endl;
				break;
			case T_VTSHAPE:
				ParseVirtTblShape(pos);
				break;
			default:
				throw 0;
			}
			break;
		case TDC_LIST:
			switch (type & TD_TYPE_MASK)
			{
			case T_ARGLIST:
				ParseArgList(pos);
				break;
			case T_FIELDLIST:
				ParseFieldList(pos, pos + len - 2);
				break;
			case T_METHODLIST:
				ParseMethodList(pos, pos + len - 2);
				break;
			default:
				throw 0;
			}
			break;
		default:
			throw 0;
		}
		if (DoEcho)
			cout << endl;
	}
}

void ParseNames(const char * start)
{
	const char * pos = start;
	int num = EatInt(pos);
	for (int i = 0; i < num; i++)
	{
		if (DoEcho)
			cout << i << ": ";
		size_t len = EatUChar(pos);
		for (size_t c = 0; c < len; c++)
		{
			if (DoEcho)
				cout << EatChar(pos);
		}
		EatChar(pos); // eat 0 terminator
		if (DoEcho)
			cout << endl;
	}
}

int wmain(int argc, const char * argv[])
{
	HANDLE hfile = CreateFile(L"test.tds", FILE_READ_DATA, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, 0);
	HANDLE hmap = CreateFileMapping(hfile, 0, PAGE_READONLY, 0, 0, 0);
	TdsBase = reinterpret_cast<const char *>(MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, 0));
	const TdsHeader * header = reinterpret_cast<const TdsHeader *>(TdsBase);
	cout << header->Magic[0] << header->Magic[1] << header->Magic[2] << header->Magic[3] << endl;
	const SubSectDir * ssdir = reinterpret_cast<const SubSectDir *>(TdsBase + header->SubSectionDirOffset);
	const SubSectDirItem * items = &ssdir->Items[0];
	for (int i = 0; i < ssdir->Num; i++)
	{
		const SubSectDirItem * curr = &items[i];
		cout << hex << "ModIndex: " << curr->Index << "  FileOffs: " << curr->Offset << "  Size: " << curr->Size << "  Type: " << sstToString(curr->Type) << endl;
		switch (curr->Type)
		{
		case sstAlignSym:
			break;
		case sstSrcModule:
			break;
		case sstGlobalSym:
			break;
		case sstGlobalTypes:
			break;
		case sstNames:
			NamesSection = TdsBase + curr->Offset;
			break;
		}
	}
	for (int i = 0; i < ssdir->Num; i++)
	{
		const SubSectDirItem * curr = &items[i];
		switch (curr->Type)
		{
		case sstAlignSym:
			ParseAlignSym(TdsBase + curr->Offset, TdsBase + curr->Offset + curr->Size, curr->Index);
			break;
		case sstSrcModule:
			ParseSrcModule(TdsBase + curr->Offset, TdsBase + curr->Offset + curr->Size);
			break;
		case sstGlobalSym:
			ParseGlobalSym(TdsBase + curr->Offset);
			break;
		case sstGlobalTypes:
			ParseGlobalTypes(TdsBase + curr->Offset);
			break;
		case sstNames:
			ParseNames(TdsBase + curr->Offset);
			break;
		}
	}
	UnmapViewOfFile(TdsBase);
	CloseHandle(hmap);
	CloseHandle(hfile);
	return 0;
}
