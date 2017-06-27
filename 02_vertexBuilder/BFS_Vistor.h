//! \file BFS_Visitor.h
//! \brief breath first search visitor class for rebuilding task graph

#ifndef BFS_VISITOR_H_
#define BFS_VISITOR_H_

#include "TG_BfsDefinitions.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <queue>

namespace vc_utils
{

    /************************************************************************/
    /* forward declarations                                                 */
    /************************************************************************/
    class task_graph_vertex_visitor;
    class vertexLessSort;

    //! \typedef task_graph_visitor_t
    //! \brief pointer to visitor class for callbacks
    typedef task_graph_vertex_visitor task_graph_visitor_t;

    //! \typedef function_t
    //! \brief function description for std::function object
    typedef std::function< void(const vc_utils::vertexDesc_t, const cv_tools::TaskGraph&,
        vc_utils::task_graph_visitor_t*, bool) > function_t;

    //! \typedef visitorFuncMap_t
    //! \brief this map saves function references for graph node interpretations
    //! \details
    //! The vertex type choose a visitor function from that table.
    typedef std::map< cv_tools::TG_VertexType, function_t > visitorFuncMap_t;

    //! \typedef buffer_t
    //! \brief sorted queue with vertices in the order of their vertex ID
    typedef std::priority_queue< vertexDesc_t, std::vector<vertexDesc_t>, vertexLessSort > buffer_t;

    /*!
    * \class vertexLessSort
    *
    * \brief functor for priority queue buffer
    *
    */
    class vertexLessSort
    {
    private:
        const cv_tools::TaskGraph& m_graph;
    public:
        vertexLessSort(const cv_tools::TaskGraph& _graph) : m_graph(_graph)
        { }

    public:
        bool operator()(const vc_utils::vertexDesc_t& _lhs, const vc_utils::vertexDesc_t& _rhs) const
        {
            auto lhsId = m_graph[_lhs].vertexID;
            auto rhsId = m_graph[_rhs].vertexID;

            return lhsId > rhsId;
        }
    };


    class task_graph_vertex_visitor
    {
    public:
        //! \brief constructor
        task_graph_vertex_visitor(const visitorFuncMap_t* const _funcMap, vertexInformationMap_t* const _info) :
            m_info(_info), m_functionMap(_funcMap) {}


        //! \brief destructor
        task_graph_vertex_visitor() = delete;

    public:
        /************************************************************************/
        // main working function
        //! \brief traverse graph and extract information
        //!
        //! \details
        //! The algorithm needs to traverse the graph two times. 
        //! In the first step, the algorithm visit every vertex and 
        //! collect informations about the vertex itself and the outgoing edges.
        //! For connections between different modules
        //! all these informations have to be collect before. 
        //! While the first visiting round all vertices are ordered by their vertex number.
        //! Then the vertices are visited again and the incoming edge information are collected.
        //! This is, because sometimes vertices with smaller numbers are after their dependencies
        //! and then vertex information can't be collected.
        /************************************************************************/
        void operator()(const cv_tools::TaskGraph& _graph)
        {
            //! \typedef vertexIter_t
            //! \brief task graph vertex iterator
            typedef boost::graph_traits<cv_tools::TaskGraph>::vertex_iterator vertexIter_t;

            //! \brief sorted vertex queue to save nodes after first visit
            buffer_t sortedVertexQueue = buffer_t(vertexLessSort(_graph));

            vertexIter_t vbegin, vend;
            std::tie(vbegin, vend) = boost::vertices(_graph);

            //collect vertex and outgoing edge information
            //False at the end of the function call jump over incoming edge information
            for (auto vertex = vbegin; vertex != vend; ++vertex)
            {
                sortedVertexQueue.push(*vertex);

                m_info->insert(std::make_pair(*vertex, vertexDataStruct()));

                m_functionMap->at(_graph[*vertex].type)(*vertex, _graph, this, false);

            }

            //collect incoming edge information
            while (!sortedVertexQueue.empty())
            {
                auto desc = sortedVertexQueue.top();

                m_functionMap->at(_graph[desc].type)(desc, _graph, this, true);

                sortedVertexQueue.pop();
            }
        }

        //! \brief assign unique memory value ID
        inline unsigned int getMemoryValueId(void) { return memoryValueId++; }

        /************************************************************************/
        //!\brief collect incoming edge information
        //!
        //!\details 
        //! All incoming edges of a vertex are visited. 
        //! Thereby information about the edge sources are collected.
        //! The information are ordered by the observer ids of the
        //! current vertex _vertex.
        //!
        //!\return Return_Description
        //!\param [in] _vertex        vertex descriptor of current node
        //!\param [in] _graph         task graph reference
        //!\param [in] _data          vertex information data map
        //!\param [in] _internalObsId bool true use self generated observer id, 
        //!                           false read observer id from incoming edge
        /************************************************************************/
        template <
            typename Vertex,
            typename Graph,
            typename DataMap
        >
        void handleIncomingEdges(Vertex _vertex, const Graph& _graph, DataMap& _data, bool _internalObsId = false)
        {
            //crate as many data fields as incoming edges are at current vertex
            _data.incomingEdges.resize(boost::in_degree(_vertex, _graph));

            //self generated observer identification
            unsigned int observerId = 0u;

            //get incoming edge iterators
            auto edgeIters = boost::in_edges(_vertex, _graph);

            //collect information for every incoming edge
            for (auto edge = edgeIters.first; edge != edgeIters.second; ++edge)
            {

                if (!_internalObsId)
                    observerId = _graph[*edge].parameterPosition;

                if (observerId >= _data.incomingEdges.size())
                    throw std::out_of_range("observer ID is higher than length of incoming edge data structure");

                //get data field at observer id
                auto& tmpInput = _data.incomingEdges.at(observerId);

                //save observer identification and incoming edge data type
                tmpInput.observerId = observerId;
                tmpInput.dataType = _graph[*edge].edgeDataType;

                //get source node of current edge
                auto source = boost::source(*edge, _graph);

                //get task vertex category of source node
                auto sourceCategory = this->m_info->at(source).category;

                //collect further information by vertex class type
                switch (sourceCategory)
                {
                case vc_utils::VertexCategory::Uninitialized:
                {
                    break;
                }
                case vc_utils::VertexCategory::Literal:
                {
                    tmpInput.subject = "Memory";
                    auto key = this->m_info->at(source).outgoingEdges.begin();
                    tmpInput.subjectValueId = this->m_info->at(source).outgoingEdges.at(key->first).second;
                    break;
                }
                case vc_utils::VertexCategory::Input:
                {
                    tmpInput.subject = "Memory";
                    auto key = this->m_info->at(source).outgoingEdges.begin();
                    tmpInput.subjectValueId = this->m_info->at(source).outgoingEdges.at(key->first).second;
                    break;
                }
                case vc_utils::VertexCategory::Output:
                    break;
                case vc_utils::VertexCategory::Operation:
                {
                    tmpInput.subject = "vertex map member";
                    tmpInput.subjectId = _graph[source].vertexID;
                    tmpInput.subjectValueId = 0u;
                    break;

                }
                case vc_utils::VertexCategory::Call:
                {
                    tmpInput.subject = "vertex map member";
                    tmpInput.subjectId = _graph[source].vertexID;

                    auto valueName = _graph[*edge].description;

                    tmpInput.subjectValueId = this->m_info->at(source).outgoingEdges.at(valueName).second;
                    break;
                }
                default:
                    break;
                }

                //increase self made observer identification
                if (_internalObsId)
                    observerId++;


            }

        }

        /************************************************************************/
        //!\brief collect outgoing edge information
        //!
        //!\details information collected by outgoing edge name
        //! Collect data is transmitted value name, data type and value id.
        //!\return Return_Description
        //!\param [in] _vertex   vertex descriptor of current node
        //!\param [in] _graph    task graph reference
        //!\param [in] _data     vertex information data map
        //!\param [in] _dataType bool true use self generated observer id,
        //!                      false read observer id from incoming edge
        /************************************************************************/
        template <
            typename Vertex,
            typename Graph,
            typename DataMap
        >
        void handleOutgoingEdges(Vertex _vertex, const Graph& _graph, DataMap& _data, std::string _dataType = "")
        {
            //get iterators for all outgoing edges
            auto outEdges = boost::out_edges(_vertex, _graph);

            //value identification number
            unsigned int valueId = 0u;

            //data type of current outgoing edge
            auto dataType = _dataType;

            //collect information for every edge
            for (auto edge = outEdges.first; edge != outEdges.second; ++edge)
            {

                if (dataType.empty())
                    dataType = _graph[*edge].edgeDataType;

                auto valueName = _graph[*edge].description;
                _data.outgoingEdges.insert(std::make_pair(valueName, std::make_pair(dataType, valueId++)));
            }
        }
    
    public:
        //! \brief pointer to literal data map
        vertexInformationMap_t* const m_info;


        //! \brief pointer for function map for visitor functions
        const visitorFuncMap_t* const m_functionMap;


        //! \brief counter for unique value ID at memory
        static unsigned int memoryValueId;

    };


}

#endif // !BFS_VISITOR_H_
