#pragma once
#include "SilentParser.hpp"
#include <vector>
#include <unordered_map>
namespace Silent
{
    enum class SilentBytecode
    {
        Halt = 0,
        Goto,
        Sweep,

        Call,
        Return,
        LoadDll,
        LoadDllFunc,
        FreeDll,
        CallDllFunc,

        Push1,
        Push2,
        Push4,
        Push8,

        Pop1,
        Pop2,
        Pop4,
        Pop8,

        Store1,
        Store2,
        Store4,
        Store8,

        Load1,
        Load2,
        Load4,
        Load8,

        StoreGlobal1,
        StoreGlobal2,
        StoreGlobal4,
        StoreGlobal8,

        LoadGlobal1,
        LoadGlobal2,
        LoadGlobal4,
        LoadGlobal8,

        Alloc,
        LoadPtr,
        StorePtr,
        FreePtr,
        Free,
        GetPtr,
        Add,
        Sub,
        Mul,
        Div,
        Convert,
        SmallerThan,
        SmallerThanOrEqual,
        LargerThan,
        LargerThanOrEqual,
        Equal,
        NotEqual,
        If,
        IfNot,
        And,
        Or,
        Xor,
        Not
    };

    enum class SilentVMType
    {
        INT8 = 0,
        UINT8,
        INT16,
        UINT16,
        INT32,
        UINT32,
        INT64,
        UINT64,
        FLOAT32,
        FLOAT64,
        POINTER,
        POINTER_LOCATION,
        UNDEFINED,
        UNDEFINED_END
    };

    class SilentCode
    {
        public:
        void AddPush(SilentDataType dt, std::string val);
        void AddLoad(SilentDataType dt, uint64 localPos);
        void AddStore(SilentDataType dt, uint64 localPos);
        template<typename T>
        void AddNumber(T val);
        std::string GetCode();

        private:
        void AddData(SilentDataType dt, std::string val);
        SilentBytecode ToBytecode(SilentPrimitives p, SilentBytecode base);
        SilentVMType ToVMType(SilentPrimitives p);
        std::vector<char> code;
    };

    class SilentCodeGenerator
    {
        public:
        void Compile(SilentParser* parser);
        std::string GetOutput();

        private:
        std::string GenScopeName(std::string id);
        void CompileExpression(SilentOperand &expression);
        void CompileStatement(SilentStatement &statement);
        void CompileLocalScope(SilentLocalScope &scope);
        void CompileFunction(SilentFunction &func);
        void CompileNamespace(SilentNamespace &scope);
        
        std::vector<SilentNamespace*> namespaces;
        std::unordered_map<std::string, uint64> symTable;
        std::string currentFunction;
        SilentCode code;
        SilentDataType currentType;
    };
}