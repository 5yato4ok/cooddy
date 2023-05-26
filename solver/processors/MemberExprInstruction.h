/// Copyright (C) 2020-2023 Huawei Technologies Co., Ltd.
///
/// This file is part of Cooddy, distributed under the GNU GPL version 3 with a Linking Exception.
/// For full terms see https://github.com/program-analysis-team/cooddy/blob/master/LICENSE.txt.
#ifndef COODDY_ANALYZER_SOURCE_SOLVER_PROCESSORS_MEMBEREXPRINSTRUCTION_H
#define COODDY_ANALYZER_SOURCE_SOLVER_PROCESSORS_MEMBEREXPRINSTRUCTION_H

#include <ast/CxxRecordDecl.h>
#include <ast/MemberExpression.h>

namespace Processor {

class MemberExprInstruction : public InstructionProcessor {
    static constexpr uint32_t FLEX_ARRAY_MAX_NUM = 3;
    static constexpr uint32_t FLEX_ARRAY_MAX_SIZE = 28;

    struct MemberInfo {
        uint32_t fieldIndex : 30;
        uint32_t isFlexArray : 1;
        uint32_t addSizeToContext : 1;
    };

    static bool IsLastFieldInRecordOrUnion(const FieldDecl& field)
    {
        if (auto record = field.GetParentOfType<RecordDecl>(); record != nullptr) {
            if (record->GetRecordType() == RecordDecl::RecordType::UNION) {
                return true;
            }
            auto& fields = record->GetFields();
            return fields.size() > 1 && field.GetIndex() + 1 == fields.size();
        }
        return false;  // LCOV_EXCL_LINE: HCAT-2779
    }

    void Compile(const Node& node, CompileContext& context) override
    {
        auto member = Node::Cast<MemberExpression>(&node);
        context.Compile(member->GetBase());

        auto fieldNode = Node::Cast<FieldDecl>(member->GetValue());
        MemberInfo info{fieldNode != nullptr ? fieldNode->GetIndex() + 1 : 0U, 0, 0};
        uint32_t fieldSize = fieldNode != nullptr ? fieldNode->GetSizeOfType() : 0;

        if (fieldSize != 0) {
            // add field size to context if a field is a static array or an object
            if (auto type = fieldNode->GetType(); type.IsConstantArray() && !type.IsPointer()) {
                info.addSizeToContext = 1;
                info.isFlexArray = IsLastFieldInRecordOrUnion(*fieldNode) &&
                                   (fieldNode->GetNumOfElementsInArray() < FLEX_ARRAY_MAX_NUM ||
                                    fieldNode->GetSizeOfType() < FLEX_ARRAY_MAX_SIZE);
            }
        }
        context.Add<MemberInfo>(info);
        if (info.addSizeToContext) {
            context.Add<uint32_t>(!info.isFlexArray ? fieldSize : fieldNode->GetOffset());
        }
    }

    z3::expr Execute(ExecutionContext& context, SymbolId& symbolId) override
    {
        auto expr = context.Execute(&symbolId);
        auto info = context.Get<MemberInfo>();

        if (info.fieldIndex == 0) {
            return context->CreateSymbolExpr(symbolId);
        }
        if (!expr.is_const()) {
            if (auto cachedSymbolPtr = context->GetSymbolBySolverId(expr.id(), symbolId); cachedSymbolPtr != nullptr) {
                symbolId = *cachedSymbolPtr;
            }
        }
        auto objSymbolId = symbolId;
        auto result = context->GetSubSymbol(symbolId, VirtualOffset(VirtualOffset::Kind::INDEX, info.fieldIndex - 1));

        if (info.addSizeToContext) {
            auto fieldSize = context.Get<uint32_t>();
            if (info.isFlexArray) {
                auto objSizeInfo = context->FindSizeExpr(context->GetSymbol(objSymbolId));
                if (objSizeInfo == nullptr) {
                    return result;
                }
                context->SetSymbolSize(result, objSizeInfo->sizeExpr - context->CreateIntegerExpr(fieldSize / 8));
            } else {
                context->SetSymbolSize(result, context->CreateIntegerExpr(fieldSize));
            }
        }
        return result;
    }
};

};  // namespace Processor

#endif  // COODDY_ANALYZER_SOURCE_SOLVER_PROCESSORS_MEMBEREXPRINSTRUCTION_H
