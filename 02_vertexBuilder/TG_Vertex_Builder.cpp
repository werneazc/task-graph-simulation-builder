//! \file TG_Vertex_Builder.h
//! \brief Vertex builder helper functions

#include "TG_Vertex_Builder.h"



vc_utils::vertexDesc_t vc_utils::restructGraphForBFS( cv_tools::TaskGraph& _graph)
{


    // save all vertices that have no incoming edges
    std::vector<vc_utils::vertexDesc_t> incomingValues;

    auto vecIters = boost::vertices(_graph);
    unsigned int maxId = 0;

    for (auto vecIt = vecIters.first; vecIt != vecIters.second; ++vecIt)
    {
        if (boost::in_degree(*vecIt, _graph) == 0)
        {
            incomingValues.push_back(*vecIt);
        }

        maxId = (maxId < _graph[*vecIt].vertexID) ? _graph[*vecIt].vertexID : maxId;
    }
    _graph[boost::graph_bundle].nextVertexId = maxId + 1;

    auto edgeIters = boost::edges(_graph);
    maxId = 0;
    for (auto edge = edgeIters.first; edge != edgeIters.second; ++edge)
        maxId = (maxId < _graph[*edge].edgeID) ? _graph[*edge].edgeID : maxId;
    _graph[boost::graph_bundle].nextEdgeId = maxId + 1;


    // add vertex to graph
    auto startVertex = boost::add_vertex(_graph);

    // add informations to new node
    _graph[startVertex].description = "BFS start node";
    _graph[startVertex].type = cv_tools::TG_VertexType::InvalidVertex;
    _graph[startVertex].vertexID = cv_tools::getNextTG_VertexId(_graph);

    // create edges from BFS start vertex to all literals and in edges 
    for (auto descIt : incomingValues)
    {
       auto currentEdge = boost::add_edge(startVertex, descIt, _graph);
       _graph[currentEdge.first].edgeType = "BFS edge to start node";
       _graph[currentEdge.first].edgeID = cv_tools::getNextTG_EdgeId(_graph);
    }

    return startVertex;
}

