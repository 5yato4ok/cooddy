/// Copyright (C) 2020-2023 Huawei Technologies Co., Ltd.
///
/// This file is part of Cooddy, distributed under the GNU GPL version 3 with a Linking Exception.
/// For full terms see https://github.com/program-analysis-team/cooddy/blob/master/LICENSE.md
#ifndef COODDY_LAMBDAEXPRESSION_H
#define COODDY_LAMBDAEXPRESSION_H

#include "Node.h"
#include "FunctionDecl.h"

namespace HCXX {

class LambdaExpression : public HCXX::CompoundNode {
public:
    LambdaExpression(Node *funcDecl) : m_operatorDecl(funcDecl) {}
    DECLARE_KIND(CompoundNode, Node::Kind::LAMBDA_EXPRESSION);
    DECLARE_SERIALIZE(LambdaExpression, m_operatorDecl);

    Node *GetOperatorDecl() const { return m_operatorDecl; }
private:
    Node* m_operatorDecl;
};

}  // namespace HCXX

#endif  // COODDY_LAMBDAEXPRESSION_H
