/*!
*  \file TaskGraphDef.cpp
*  \brief Contains the implementation of helper functions for the task graph class.

*  \details
*
*
*
*  \author Florian Fricke
*
*  \date June 2015
*/

#include "TaskGraphDef.h"

const cv_tools::TG_VertexTypeNamesVector_t cv_tools::TG_VertexTypeNames
{
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::InvalidVertex, "InvalidVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::VarInputVertex, "VarInputVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::IfBeginVertex, "IfBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::IfEndVertex, "IfEndVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ThenBeginVertex, "ThenBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ElseBeginVertex, "ElseBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::SwitchBeginVertex, "SwitchBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::SwitchEndVertex, "SwitchEndVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::CaseBeginVertex, "CaseBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::DefaultBeginVertex, "DefaultBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BeginLoopBody, "BeginLoopBody"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::EndLoopBody, "EndLoopBody"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::DoBeginVertex, "DoBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::DoEndVertex, "DoEndVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::WhileBeginVertex, "WhileBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::WhileEndVertex, "WhileEndVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ForBeginVertex, "ForBeginVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ForEndVertex, "ForEndVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ReturnVertex, "ReturnVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::FunctionCallVertex, "FunctionCallVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpPtrMemDVertex, "BinOpPtrMemDVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpPtrMemIVertex, "BinOpPtrMemIVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpMulVertex, "BinOpMulVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpDivVertex, "BinOpDivVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpRemVertex, "BinOpRemVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpAddVertex, "BinOpAddVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpSubVertex, "BinOpSubVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpShlVertex, "BinOpShlVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpShrVertex, "BinOpShrVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpLTVertex, "BinOpLTVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpGTVertex, "BinOpGTVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpLEVertex, "BinOpLEVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpGEVertex, "BinOpGEVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpEQVertex, "BinOpEQVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpNEVertex, "BinOpNEVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpAndVertex, "BinOpAndVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpXorVertex, "BinOpXorVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpOrVertex, "BinOpOrVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpLAndVertex, "BinOpLAndVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpLOrVertex, "BinOpLOrVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpAssignVertex, "BinOpAssignVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::BinOpCommaVertex, "BinOpCommaVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPostIncVertex, "UnaryOpPostIncVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPostDecVertex, "UnaryOpPostDecVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPreIncVertex, "UnaryOpPreIncVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPreDecVertex, "UnaryOpPreDecVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpAddrOfVertex, "UnaryOpAddrOfVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpDerefVertex, "UnaryOpDerefVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpPlusVertex, "UnaryOpPlusVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpMinusVertex, "UnaryOpMinusVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpNotVertex, "UnaryOpNotVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::UnaryOpLNotVertex, "UnaryOpLNotVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::ConditionalOpVertex, "ConditionalOpVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::VarVertex, "VarVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::CharacterLiteralVertex, "CharacterLiteralVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::IntegerLiteralVertex, "IntegerLiteralVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::FloatingLiteralVertex, "FloatingLiteralVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::StringLiteralVertex, "StringLiteralVertex"),
	std::pair<cv_tools::TG_VertexType, std::string>(cv_tools::TG_VertexType::CastVertex, "CastVertex"),
};



std::ostream& cv_tools::operator<<(std::ostream& lhs, cv_tools::TG_VertexType& rhs)
{
	auto it = std::find_if(
		TG_VertexTypeNames.cbegin(), 
		TG_VertexTypeNames.cend(), 
		[&rhs](TG_VertexTypeNamesVector_t::value_type type)->bool { return (type.first == rhs); });
	
	lhs << it->second;

	return lhs;
}

std::istream& cv_tools::operator>>(std::istream& lhs, cv_tools::TG_VertexType& rhs)
{
	std::string tmpType;

	lhs >> tmpType;

	auto it = std::find_if(
		TG_VertexTypeNames.cbegin(),
		TG_VertexTypeNames.cend(),
		[&tmpType](TG_VertexTypeNamesVector_t::value_type type)->bool { return (type.second == tmpType); });

	if (it != TG_VertexTypeNames.cend())
		rhs = it->first;
	else
		rhs = cv_tools::TG_VertexType::InvalidVertex;

	return lhs;
}

void cv_tools::setTG_VertexProperties(const TG_VertexProperties& propertiesA, TaskGraph::vertex_descriptor vertexA, TaskGraph& taskGraphA)
{
	taskGraphA[vertexA] = propertiesA;
}

void cv_tools::setTG_EdgeProperties(const TG_EdgeProperties& propertiesA, TaskGraph::edge_descriptor edgeA, TaskGraph& taskGraphA)
{
	taskGraphA[edgeA] = propertiesA;
}

void cv_tools::setTG_VertexProperties(
	const TG_VertexType typeA,
	const bool isInputVertexA,
	const bool isOutputVertexA,
	const unsigned int computationCostA,
	const std::string outputDataTypeA,
	const std::string descriptionA,
	const TaskGraph::vertex_descriptor vertexA,
	TaskGraph& taskGraphA)
{
	setTG_VertexProperties(
		TG_VertexProperties(getNextTG_VertexId(taskGraphA), 
		typeA, isInputVertexA, isOutputVertexA, computationCostA, 
		outputDataTypeA, descriptionA), 
		vertexA, taskGraphA);
}

void cv_tools::setTG_EdgeProperties(
	const bool isControlFlowEdgeA,
	const unsigned int internalWeightA,
	const unsigned int externalWeightA,
	const std::string edgeTypeA,
	const std::string edgeDataTypeA,
	unsigned int parameterPositionA,
	const std::string descriptionA,
	const TaskGraph::edge_descriptor edgeA,
	TaskGraph& taskGraphA)
{
	setTG_EdgeProperties(
		TG_EdgeProperties(getNextTG_EdgeId(taskGraphA), 
		isControlFlowEdgeA, internalWeightA, externalWeightA, 
		edgeTypeA, edgeDataTypeA, parameterPositionA, descriptionA), 
		edgeA, taskGraphA);
}

unsigned int cv_tools::getNextTG_VertexId(cv_tools::TaskGraph& taskGraphA)
{
	return taskGraphA[boost::graph_bundle].nextVertexId++;
}

unsigned int cv_tools::getNextTG_EdgeId(cv_tools::TaskGraph& taskGraphA)
{
	return taskGraphA[boost::graph_bundle].nextEdgeId++;
}

void cv_tools::writeTaskGraphToGraphML(cv_tools::TaskGraph& taskGraphA, const std::string& filenameA)
{
	// creation of property maps for the graphs properties	
	boost::ref_property_map<cv_tools::TaskGraph*, std::string> graphName_map(taskGraphA[boost::graph_bundle].graphName);
	boost::ref_property_map<cv_tools::TaskGraph*, unsigned int> nextVertexId_map(taskGraphA[boost::graph_bundle].nextVertexId);
	boost::ref_property_map<cv_tools::TaskGraph*, unsigned int> nextEdgeId_map(taskGraphA[boost::graph_bundle].nextEdgeId);
	boost::ref_property_map<cv_tools::TaskGraph*, std::string> description_map(taskGraphA[boost::graph_bundle].description);

	// creation of property maps for all vertex properties
	auto vertexID_map = boost::get(&TG_VertexProperties::vertexID, taskGraphA);
	auto vertexType_map = boost::get(&TG_VertexProperties::type, taskGraphA);
	auto isInput_map = boost::get(&TG_VertexProperties::isInputVertex, taskGraphA);
	auto isOutput_map = boost::get(&TG_VertexProperties::isOutputVertex, taskGraphA);
	auto computationCost_map = boost::get(&TG_VertexProperties::computationCost, taskGraphA);
	auto outputDataType_map = boost::get(&TG_VertexProperties::outputDataType, taskGraphA);
	auto vertexDescription_map = boost::get(&TG_VertexProperties::description, taskGraphA);

	// creation of property maps for all edge properties
	auto edgeID_map = boost::get(&TG_EdgeProperties::edgeID, taskGraphA);
	auto edgeCtrlFlow_map = boost::get(&TG_EdgeProperties::isControlFlowEdge, taskGraphA);
	auto intWeight_map = boost::get(&TG_EdgeProperties::internalWeight, taskGraphA);
	auto extWeight_map = boost::get(&TG_EdgeProperties::externalWeight, taskGraphA);
	auto edgeType_map = boost::get(&TG_EdgeProperties::edgeType, taskGraphA);
	auto edgeDataType_map = boost::get(&TG_EdgeProperties::edgeDataType, taskGraphA);
	auto edgeParameterPosition_map = boost::get(&TG_EdgeProperties::parameterPosition, taskGraphA);
	auto edgeDescription_map = boost::get(&TG_EdgeProperties::description, taskGraphA);

	// adding the property maps to the dynamic poperties object for output
	boost::dynamic_properties TG_props;

	TG_props.property("graphName", graphName_map);
	TG_props.property("nextVertexId", nextVertexId_map);
	TG_props.property("nextEdgeId", nextEdgeId_map);
	TG_props.property("description", description_map);

	TG_props.property("vertexID", vertexID_map);
	TG_props.property("vertexType", vertexType_map);
	TG_props.property("isInput", isInput_map);
	TG_props.property("isOutput", isOutput_map);
	TG_props.property("computationCost", computationCost_map);
	TG_props.property("outputDataType", outputDataType_map);
	TG_props.property("vertexDescription", vertexDescription_map);

	TG_props.property("edgeID", edgeID_map);
	TG_props.property("edgeCtrlFlow", edgeCtrlFlow_map);
	TG_props.property("intWeight", intWeight_map);
	TG_props.property("extWeight", extWeight_map);
	TG_props.property("edgeType", edgeType_map);
	TG_props.property("edgeDataType", edgeDataType_map);
	TG_props.property("parameterPosition", edgeParameterPosition_map);
	TG_props.property("edgeDescription", edgeDescription_map);

	std::ofstream outFile(filenameA);
	boost::write_graphml(outFile, taskGraphA, vertexID_map, TG_props);
}

void cv_tools::writeTaskGraphToDot(cv_tools::TaskGraph& taskGraphA, const std::string& filenameA)
{
	// creation of property maps for all vertex properties
	auto vertexID_map = boost::get(&TG_VertexProperties::vertexID, taskGraphA);
	auto vertexType_map = boost::get(&TG_VertexProperties::type, taskGraphA);
	auto isInput_map = boost::get(&TG_VertexProperties::isInputVertex, taskGraphA);
	auto isOutput_map = boost::get(&TG_VertexProperties::isOutputVertex, taskGraphA);
	auto computationCost_map = boost::get(&TG_VertexProperties::computationCost, taskGraphA);
	auto outputDataType_map = boost::get(&TG_VertexProperties::outputDataType, taskGraphA);
	auto vertexDescription_map = boost::get(&TG_VertexProperties::description, taskGraphA);

	// creation of property maps for all edge properties
	auto edgeID_map = boost::get(&TG_EdgeProperties::edgeID, taskGraphA);
	auto edgeCtrlFlow_map = boost::get(&TG_EdgeProperties::isControlFlowEdge, taskGraphA);
	auto intWeight_map = boost::get(&TG_EdgeProperties::internalWeight, taskGraphA);
	auto extWeight_map = boost::get(&TG_EdgeProperties::externalWeight, taskGraphA);
	auto edgeType_map = boost::get(&TG_EdgeProperties::edgeType, taskGraphA);
	auto edgeDataType_map = boost::get(&TG_EdgeProperties::edgeDataType, taskGraphA);
	auto edgeDescription_map = boost::get(&TG_EdgeProperties::description, taskGraphA);

	auto vertexLblWriter = make_TaskGraph_VertLblWriter(
		vertexID_map,
		vertexType_map,
		computationCost_map,
		outputDataType_map,
		vertexDescription_map
	);

	auto edgeLblWriter = make_TaskGraph_EdgeLblWriter(
		edgeID_map,
		edgeCtrlFlow_map,
		intWeight_map,
		extWeight_map,
		edgeType_map,
		edgeDataType_map,
		edgeDescription_map
		);

	auto graphLblWriter = make_TaskGraph_GraphLabelWriter(&taskGraphA);

	std::ofstream outFile(filenameA);
	boost::write_graphviz(outFile, taskGraphA, vertexLblWriter, edgeLblWriter, graphLblWriter, vertexID_map);
}