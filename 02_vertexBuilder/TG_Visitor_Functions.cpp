#include "TG_Visitor_Functions.h"

unsigned int vc_utils::task_graph_vertex_visitor::memoryValueId = 0u;

#pragma region visitorMap

const vc_utils::visitorFuncMap_t vc_utils::visitorFunctionMap = {
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::InvalidVertex, vc_utils::invalidVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::VarInputVertex, vc_utils::inputVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::IfBeginVertex, vc_utils::ifBeginVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::IfEndVertex, vc_utils::ifEndVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::ThenBeginVertex, vc_utils::ifThenVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::ElseBeginVertex, vc_utils::ifElseVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::SwitchBeginVertex, vc_utils::switchBeginVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::SwitchEndVertex, vc_utils::switchEndVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::CaseBeginVertex, vc_utils::caseVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::DefaultBeginVertex, vc_utils::defaultVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BeginLoopBody, vc_utils::bodyBeginVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::EndLoopBody, vc_utils::bodyEndVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::DoBeginVertex, vc_utils::doBeginVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::DoEndVertex, vc_utils::doEndVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::WhileBeginVertex, vc_utils::whileBeginVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::WhileEndVertex, vc_utils::whileEndVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::ForBeginVertex, vc_utils::forBeginVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::ForEndVertex, vc_utils::forEndVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::ReturnVertex, vc_utils::returnVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::FunctionCallVertex, vc_utils::functionCallVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpPtrMemDVertex, vc_utils::notImplementedVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpPtrMemIVertex, vc_utils::notImplementedVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpMulVertex, vc_utils::arithOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpDivVertex, vc_utils::arithOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpRemVertex, vc_utils::arithOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpAddVertex, vc_utils::arithOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpSubVertex, vc_utils::arithOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpShlVertex, vc_utils::shiftOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpShrVertex, vc_utils::shiftOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpLTVertex, vc_utils::compOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpGTVertex, vc_utils::compOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpLEVertex, vc_utils::compOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpGEVertex, vc_utils::compOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpEQVertex, vc_utils::compOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpNEVertex, vc_utils::compOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpAndVertex, vc_utils::bitOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpXorVertex, vc_utils::bitOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpOrVertex, vc_utils::bitOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpLAndVertex, vc_utils::logicOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpLOrVertex, vc_utils::logicOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpAssignVertex, vc_utils::assignVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::BinOpCommaVertex, vc_utils::notImplementedVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpPostIncVertex, vc_utils::unOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpPostDecVertex, vc_utils::unOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpPreIncVertex, vc_utils::unOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpPreDecVertex, vc_utils::unOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpAddrOfVertex, vc_utils::notImplementedVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpDerefVertex, vc_utils::notImplementedVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpPlusVertex, vc_utils::notImplementedVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpMinusVertex, vc_utils::notImplementedVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpNotVertex, vc_utils::unOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::UnaryOpLNotVertex, vc_utils::unOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::ConditionalOpVertex, vc_utils::ternaryOpVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::VarVertex, vc_utils::varVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::CharacterLiteralVertex, vc_utils::literalVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::IntegerLiteralVertex, vc_utils::literalVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::FloatingLiteralVertex, vc_utils::literalVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::StringLiteralVertex, vc_utils::literalVertexVisitorFunc ),
    std::pair< cv_tools::TG_VertexType, vc_utils::function_t >(
        cv_tools::TG_VertexType::CastVertex, vc_utils::castVertexVisitorFunc )};

#pragma endregion

#pragma region VertexClassMap

        static const std::map< cv_tools::TG_VertexType, std::string> vertexClassMap = {
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::InvalidVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::VarInputVertex, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::IfBeginVertex, "IfVertex"),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::IfEndVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ThenBeginVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ElseBeginVertex, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::SwitchBeginVertex, "SwitchVertex"),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::SwitchEndVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::CaseBeginVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::DefaultBeginVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BeginLoopBody, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::EndLoopBody, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::DoBeginVertex, "DoWhileVertex"),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::DoEndVertex, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::WhileBeginVertex, "WhileVertex"),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::WhileEndVertex, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ForBeginVertex, "ForVertex"),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ForEndVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ReturnVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::FunctionCallVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpPtrMemDVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpPtrMemIVertex, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpMulVertex, "MulVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpDivVertex, "DivVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpRemVertex, "ModVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpAddVertex, "AddVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpSubVertex, "SubVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpShlVertex, "LShiftVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpShrVertex, "RShiftVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpLTVertex, "LowerVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpGTVertex, "GreaterVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpLEVertex, "LEqualVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpGEVertex, "GEqualVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpEQVertex, "EqualVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpNEVertex, "NotEqualVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpAndVertex, "BitAndVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpXorVertex, "BitXorVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpOrVertex, "BitOrVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpLAndVertex, "LogicAndVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpLOrVertex, "LogicOrVertex"),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpAssignVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpCommaVertex, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPostIncVertex, "PostIncVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPostDecVertex, "PostDecVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPreIncVertex, "PreIncVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPreDecVertex, "PreDecVertex"),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpAddrOfVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpDerefVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPlusVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpMinusVertex, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpNotVertex, "BitNotVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpLNotVertex, "NotVertex"),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ConditionalOpVertex, "TernaryVertex"),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::VarVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::CharacterLiteralVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::IntegerLiteralVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::FloatingLiteralVertex, ),
            //std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::StringLiteralVertex, ),
            std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::CastVertex, "CastVertex")
        };

#pragma endregion 

void vc_utils::invalidVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    auto desc = _graph[ _vertex ].description;

    if ( desc == "BFS start node" )
        {
            std::cout << "BFS start vertex found" << std::endl;
        }
    else
        std::cout << "unknown vertex type found!" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::literalVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "Literal Vertex with id "<< _graph[_vertex].vertexID << " visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Literal;
    tmpData.kind = "Memory";

    auto dataType = _graph[_vertex].outputDataType;
    auto valueId = _visitor->getMemoryValueId();
    auto tmpValue = _graph[_vertex].description;

    auto length = tmpValue.find(' ');

    if (length == tmpValue.npos)
        throw std::out_of_range("search character to get literal value not found in string");

    tmpValue.erase(tmpValue.begin(), tmpValue.begin() + length + 1);
    tmpData.value = tmpValue;

    auto valueName = _graph[*boost::out_edges(_vertex, _graph).first].description;
    //length = valueName.find(' ');

    //if (length == valueName.npos)
    //    throw std::out_of_range("search character to build output map key not found in string");
  
    //valueName.erase(valueName.begin() + length, valueName.end());
    tmpData.outgoingEdges.insert(std::make_pair(valueName, std::make_pair(dataType, valueId)));
    
    return;
}

void vc_utils::returnVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "return vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Output;
    tmpData.kind = "Memory";
    tmpData.owner = "Memory";

    _visitor->handleIncomingEdges(_vertex, _graph, tmpData, true);

    return;
}

void vc_utils::inputVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "input vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Input;
    tmpData.kind = "Memory";

    auto dataType = _graph[_vertex].outputDataType;
    auto valueId = _visitor->getMemoryValueId();

    auto valueName = _graph[*boost::out_edges(_vertex, _graph).first].description;
    //auto length = valueName.find(' ');

    //if (length == valueName.npos)
    //    throw std::out_of_range("search character to build output map key not found in string");

    //valueName.erase(valueName.begin() + length, valueName.end());
    tmpData.outgoingEdges.insert(std::make_pair(valueName, std::make_pair(dataType, valueId)));

    return;
}

void vc_utils::arithOpVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "arithmetic binary operation vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);
    
    tmpData.category = vc_utils::VertexCategory::Operation;
    tmpData.kind = vertexClassMap.at(_graph[_vertex].type);
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;


	_visitor->handleOutgoingEdges(_vertex, _graph, tmpData);

    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);
    

    return;
}

void vc_utils::compOpVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "comparison operator vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Operation;
    tmpData.kind = vertexClassMap.at(_graph[_vertex].type);
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;

    _visitor->handleOutgoingEdges(_vertex, _graph, tmpData, "bool");

    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);

    return;
}

void vc_utils::unOpVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "unary operator vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Operation;
    tmpData.kind = vertexClassMap.at(_graph[_vertex].type);
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;

    _visitor->handleOutgoingEdges(_vertex, _graph, tmpData);

    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);

    return;
}

void vc_utils::ternaryOpVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "ternary operator vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Operation;
    tmpData.kind = vertexClassMap.at(_graph[_vertex].type);
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;

    _visitor->handleOutgoingEdges(_vertex, _graph, tmpData);

    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);

    return;

}

void vc_utils::ifBeginVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "if begin vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::ifThenVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "if then vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::ifElseVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "if else vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::ifEndVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "if end vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::varVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "variable vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::castVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "cast vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Operation;
    tmpData.kind = vertexClassMap.at(_graph[_vertex].type);
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;

    _visitor->handleOutgoingEdges(_vertex, _graph, tmpData);

    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);

    return;
}

void vc_utils::shiftOpVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "shift operator vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Operation;
    tmpData.kind = vertexClassMap.at(_graph[_vertex].type);
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;

    _visitor->handleOutgoingEdges(_vertex, _graph, tmpData);

    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);

    return;
}

void vc_utils::notImplementedVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "a vertex visit which is not interpreted yet" << std::endl;
#endif // _DEBUG

    throw std::runtime_error("Vertex kind not implemented for rebuilding.");

    return;
}

void vc_utils::logicOpVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "logical operator vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Operation;
    tmpData.kind = vertexClassMap.at(_graph[_vertex].type);
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;

    _visitor->handleOutgoingEdges(_vertex, _graph, tmpData, "bool");


    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);

    return;
}

void vc_utils::bitOpVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "bitwise operator vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Operation;
    tmpData.kind = vertexClassMap.at(_graph[_vertex].type);
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;

    _visitor->handleOutgoingEdges(_vertex, _graph, tmpData);


    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);

    return;
}

void vc_utils::assignVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "assign operator vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::functionCallVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "function call vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    auto& tmpData = _visitor->m_info->at(_vertex);

    tmpData.category = vc_utils::VertexCategory::Call;
    tmpData.kind = _graph[_vertex].description;
    tmpData.owner = "Task_Base";
    tmpData.ownerId = _graph[_vertex].vertexID;

    _visitor->handleOutgoingEdges(_vertex, _graph, tmpData);

    if (_connect)
        _visitor->handleIncomingEdges(_vertex, _graph, tmpData);

    return;
}

void vc_utils::switchBeginVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "switch begin vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::switchEndVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "switch end vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::caseVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "case vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::defaultVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "default vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::bodyBeginVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "loop body begin vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::bodyEndVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "loop body end vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::whileBeginVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "while begin vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::whileEndVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "while end vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::forBeginVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "for begin vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::forEndVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "for end vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::doBeginVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "do begin vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}

void vc_utils::doEndVertexVisitorFunc( const vc_utils::vertexDesc_t _vertex,
    const cv_tools::TaskGraph& _graph, vc_utils::task_graph_visitor_t* _visitor, bool _connect/*=false*/ )
{
#ifdef _DEBUG
    std::cout << "do end vertex with id " << _graph[_vertex].vertexID << "  visit" << std::endl;
#endif // _DEBUG

    return;
}
