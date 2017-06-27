//! \file TG_Visitor_Functions.h
//! \brief Visitor functionalities for different node types in task graph vertex

#include "BFS_Vistor.h"
#include <iostream>
#include <functional>
#include <limits>

namespace vc_utils
{

    //! \var visitorFunctionMap
    //! \brief This map saves function references for graph node interpretations.
    extern const visitorFuncMap_t visitorFunctionMap;

    /************************************************************************/
    /* visitor function prototypes                                          */
    /************************************************************************/

    void invalidVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void literalVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void returnVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void inputVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void arithOpVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void compOpVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void unOpVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void ternaryOpVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void ifBeginVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void ifThenVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void ifElseVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void ifEndVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void varVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void castVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void shiftOpVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void notImplementedVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void logicOpVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void bitOpVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void assignVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void functionCallVertexVisitorFunc( const vertexDesc_t _vertex,
        const cv_tools::TaskGraph& _graph, task_graph_visitor_t* _visitor, bool _connect=false );

    void switchBeginVertexVisitorFunc( const vertexDesc_t _vertex,
        const cv_tools::TaskGraph& _graph, task_graph_visitor_t* _visitor, bool _connect=false );

    void switchEndVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void caseVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void defaultVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void bodyBeginVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void bodyEndVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void whileBeginVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void whileEndVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void forBeginVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void forEndVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void doBeginVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );

    void doEndVertexVisitorFunc( const vertexDesc_t _vertex, const cv_tools::TaskGraph& _graph,
        task_graph_visitor_t* _visitor, bool _connect=false );
}