/*!
*  \file TaskGraphDef.h
*  \brief Defines the datastructures, the type and some helper functions for the task-graph class.

*  \details
*
*
*
*  \author Florian Fricke
*
*  \date June 2015
*/

#ifndef TASKGRAPHDEF_H_
#define TASKGRAPHDEF_H_

#include <string>
#include <vector>
#include <iostream>

//#include "llvm/Support/raw_ostream.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>

#include <regex>

//!<\brief Namespace for the master thesis
namespace cv_tools
{
    /*!
    *  \enum TG_VertexType
    *  \brief Defines the vertex types for the TaskGraph class defined below.
    */
    enum class TG_VertexType
    {
        InvalidVertex,
        VarInputVertex,
        IfBeginVertex,
        IfEndVertex,
        ThenBeginVertex,
        ElseBeginVertex,
        SwitchBeginVertex,
        SwitchEndVertex,
        CaseBeginVertex,
        DefaultBeginVertex,
        BeginLoopBody,
        EndLoopBody,
        DoBeginVertex,
        DoEndVertex,
        WhileBeginVertex,
        WhileEndVertex,
        ForBeginVertex,
        ForEndVertex,
        ReturnVertex,
        FunctionCallVertex,
        BinOpPtrMemDVertex,
        BinOpPtrMemIVertex,
        BinOpMulVertex,
        BinOpDivVertex,
        BinOpRemVertex,
        BinOpAddVertex,
        BinOpSubVertex,
        BinOpShlVertex,
        BinOpShrVertex,
        BinOpLTVertex,
        BinOpGTVertex,
        BinOpLEVertex,
        BinOpGEVertex,
        BinOpEQVertex,
        BinOpNEVertex,
        BinOpAndVertex,
        BinOpXorVertex,
        BinOpOrVertex,
        BinOpLAndVertex,
        BinOpLOrVertex,
        BinOpAssignVertex,
        BinOpCommaVertex,
        UnaryOpPostIncVertex,
        UnaryOpPostDecVertex,
        UnaryOpPreIncVertex,
        UnaryOpPreDecVertex,
        UnaryOpAddrOfVertex,
        UnaryOpDerefVertex,
        UnaryOpPlusVertex,
        UnaryOpMinusVertex,
        UnaryOpNotVertex,
        UnaryOpLNotVertex,
        ConditionalOpVertex,
        VarVertex,
        CharacterLiteralVertex,
        IntegerLiteralVertex,
        FloatingLiteralVertex,
        StringLiteralVertex,
        CastVertex
    };

	/*!
	*  \typedef TG_VertexTypeNamesVector_t
	*
	*  \brief Definition for a vector storing the string representation of all
	*		  TG_VertexTypes together with the type.
	*
	*  \details
	*
	*
	*/
	typedef std::vector < std::pair<cv_tools::TG_VertexType, std::string>> TG_VertexTypeNamesVector_t;

    /*!
    *  \var TG_VertexTypeNames
    *  \brief A std::vector, storing std::pair variables containing a 
	*         TG_VertexType and its string representations for all 
	*         elements of the TG_VertexType enumeration. It is used 
	*		  for reading and writing vertex types from/to streams. 
    */
	extern const TG_VertexTypeNamesVector_t TG_VertexTypeNames;
    
    /*!
    *  \class TG_EdgeProperties
    *  \brief Properties of an edge used in the TaskGraph type
    *
    *  \details
    *  This structure is used as bundled properties object for the edge
    *  properties in the TaskGraph.
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    struct TG_EdgeProperties
    {
        unsigned int edgeID;			//!<\brief The ID of an edge, unique inside one graph
        bool isControlFlowEdge;			//!<\brief true, if the edge is used to represent control flow
        unsigned int internalWeight;	//!<\brief Weight of the edge, when used for communication inside a cluster
        unsigned int externalWeight;	//!<\brief Weight of the edge, when used for communication between clusters
        std::string edgeType;			//!<\brief Type of the edge
        std::string edgeDataType;		//!<\brief Datatype transferred by the edge
        unsigned int parameterPosition;	//!<\brief Position of the parameter referenced by the edge for operators and function calls
        std::string description;		//!<\brief Short description and additional information
         
        /*!
        *  \brief Constructor
        *
        *  \details Creates an empty object, implemented for compatibility reasons
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        TG_EdgeProperties( ) = default;
        
        /*!
        *  \brief Constructor
        *
        *  \param [in] edgeIDA The ID of an edge, unique inside one graph
        *  \param [in] isControlFlowEdgeA true, if the edge is used to represent control flow
        *  \param [in] internalWeightA Weight of the edge, when used for communication inside a cluster
        *  \param [in] externalWeightA Weight of the edge, when used for communication between clusters
        *  \param [in] edgeTypeA Type of the edge
        *  \param [in] edgeDataTypeA Datatype transferred by the edge
        *  \param [in] parameterPositionA Position of the parameter referenced by the edge for operators and function calls
        *  \param [in] descriptionA Short description and additional information
        * 
        *  \details Creates an TG_EdgeProperties object, initializing all member variables
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        TG_EdgeProperties(unsigned int edgeIDA,
                          bool isControlFlowEdgeA,
                          unsigned int internalWeightA,
                          unsigned int externalWeightA,
                          std::string edgeTypeA,
                          std::string edgeDataTypeA,
                          unsigned int parameterPositionA,
                          std::string descriptionA)
            : edgeID(edgeIDA), isControlFlowEdge(isControlFlowEdgeA),
              internalWeight(internalWeightA), externalWeight(externalWeightA),
              edgeType(edgeTypeA), edgeDataType(edgeDataTypeA), 
              parameterPosition(parameterPositionA), description(descriptionA)
        {
        }

        /*!
        *  \brief Destructor
        *
        *  \details Destroys a TG_EdgePropertiesobject object, implemented for compatibility reasons
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        ~TG_EdgeProperties( ) = default;
    };

    /*!
    *  \class TG_VertexProperties
    *  \brief Properties of a vertex used in the TaskGraph type
    *
    *  \details
    *  This structure is used as bundled properties object for the vertex
    *  properties in the TaskGraph.
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    struct TG_VertexProperties
    {
        unsigned int vertexID;			//!<\brief The ID of a vertex, unique inside one graph
        TG_VertexType type;				//!<\brief The vertex type
        bool isInputVertex;				//!<\brief true, if the vertex in created from a function parameter
        bool isOutputVertex;			//!<\brief true, if the vertex is directly connected to the return vertex
        unsigned int computationCost;	//!<\brief The costs for passing the vertex
        std::string outputDataType;		//!<\brief The datatype of the vertex output
        std::string description;		//!<\brief Short description and additional information

        /*!
        *  \brief Constructor
        *
        *  \details Creates an empty object, implemented for compatibility reasons
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        TG_VertexProperties( ) = default;

        /*!
        *  \brief Constructor
        *
        *  \param [in] vertexIDA The ID of a vertex, unique inside one graph
        *  \param [in] typeA The vertex type
        *  \param [in] isInputVertexA true, if the vertex in created from a function parameter
        *  \param [in] isOutputVertexA true, if the vertex is directly connected to the return vertex
        *  \param [in] computationCostA The costs for passing the vertex
        *  \param [in] outputDataTypeA The datatype of the vertex output
        *  \param [in] descriptionA Short description and additional information
        *
        *  \details Creates an TG_VertexProperties object, initializing all member variables
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        TG_VertexProperties(unsigned int vertexIDA,
                            TG_VertexType typeA,
                            bool isInputVertexA,
                            bool isOutputVertexA,
                            unsigned int computationCostA,
                            std::string outputDataTypeA,
                            std::string descriptionA)
            : vertexID(vertexIDA), type(typeA), isInputVertex(isInputVertexA),
              isOutputVertex(isOutputVertexA),
              computationCost(computationCostA),
              outputDataType(outputDataTypeA), description(descriptionA)
        {
        }

        /*!
        *  \brief Destructor
        *
        *  \details Destroys a TG_VertexProperties object, implemented for compatibility reasons
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        ~TG_VertexProperties( ) = default;
    };

    /*!
    *  \class TG_GraphProperties
    *  \brief Properties of a graph defined by TaskGraph type
    *
    *  \details
    *  This structure is used as bundled properties object for the graph
    *  properties in the TaskGraph.
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    struct TG_GraphProperties
    {
        std::string graphName;		//!<\brief	The graphs name (name of the function the graph was created from)
        unsigned int nextVertexId;	//!<\brief	Stores the number, that should be assigned to the vertex added next as id
        unsigned int nextEdgeId;	//!<\brief	Stores the number, that should be assigned to the edge added next as id
        std::string description;	//!<\brief	Short description and additional information

        /*!
        *  \brief Constructor
        *
        *  \details Creates an empty object, implemented for compatibility reasons
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        TG_GraphProperties( )
            : graphName( ), nextVertexId(0), nextEdgeId(0), description( )
        {
        }

        /*!
        *  \brief Constructor
        *
        *  \param [in] graphNameA The graphs name (name of the function the graph was created from)
        *  \param [in] nextVertexIdA Sets number, that should be assigned to the vertex added next as ID
        *  \param [in] nextEdgeId Sets the number, that should be assigned to the edge added next as ID
        *  \param [in] descriptionA Short description and additional information
        *
        *  \details Creates an TG_GraphProperties object, initializing all member variables
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        TG_GraphProperties(std::string graphNameA,
                           unsigned int nextVertexIdA,
                           unsigned int nextEdgeId,
                           std::string descriptionA)
            : graphName(graphNameA), nextVertexId(nextVertexIdA),
              nextEdgeId(nextEdgeId), description(descriptionA)
        {
        }
        ~TG_GraphProperties( ) = default;
    };

    /*!
    *  \typedef TaskGraph
    *
    *  \brief Task graph definition based on boost::adjacency_list
    *
    *  \details 
    *  
    *
    */
    typedef boost::adjacency_list<boost::listS,
                                  boost::listS,
                                  boost::bidirectionalS,
                                  TG_VertexProperties,
                                  TG_EdgeProperties,
								  TG_GraphProperties> TaskGraph;

    /*!
    *  \typedef taskGraphVertDesc
    *  \brief Type of a vertex descriptor, used by the TaskGraph type
    */
    typedef boost::graph_traits<TaskGraph>::vertex_descriptor taskGraphVertDesc;

    /*!
    *  \typedef taskGraphEdgeDesc
    *  \brief Type of a edge descriptor, used by the TaskGraph type
    */
    typedef boost::graph_traits<TaskGraph>::edge_descriptor taskGraphEdgeDesc;

    /*!
    *  \typedef taskGraphVertIter
    *  \brief Type of a vertex iterator, used by the TaskGraph type
    */
    typedef boost::graph_traits<TaskGraph>::vertex_iterator taskGraphVertIter;

    /*!
    *  \typedef taskGraphEdgeIter
    *  \brief Type of a edge iterator, used by the TaskGraph type
    */
    typedef boost::graph_traits<TaskGraph>::edge_iterator taskGraphEdgeIter;

    /*!
    *  \fn std::ostream &operator<<(std::ostream&, TG_VertexType&)
    *
    *  \brief Writes a value from the TG_VertexType enum to an ostream
    *
    *  \param [in] lhs The ostream the VertexType shall be written to
    *  \param [in] rhs The VertexType the shall be written
    *
    *  \returns A reference to the ostream, given as the left-hand-side argument
    *
    *  \details
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    */
    std::ostream &operator<<(std::ostream& lhs, TG_VertexType& rhs);

    /*!
    *  \fn std::ostream &operator>>(std::istream&, TG_VertexType&)
    *
    *  \brief Reads a value from the TG_VertexType enum from an istream
    *
    *  \param [in] lhs The istream the VertexType shall be read from
    *  \param [in] rhs A TG_VertexType variable the value shall be written to
    *
    *  \returns A reference to the istream, given as the left-hand-side argument
    *
    *  \details
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    */
    std::istream &operator>>(std::istream& lhs, TG_VertexType& rhs);


    /*!
    *  \fn void setTG_VertexProperties(const TG_VertexProperties&, TaskGraph::vertex_descriptor, TaskGraph&)
    *
    *  \brief Sets all available internal properties of a vertex from a TG_VertexProperties object 
    *
    *  \param [in] propertiesA The properties that shall be assigned to the vertex
    *  \param [in] vertexA The vertex descriptor the properties shall be assigned to
    *  \param [in] taskGraphA The taskGraph we are working on
    *
    *  \details
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    */
    void setTG_VertexProperties(const TG_VertexProperties& propertiesA,
                                TaskGraph::vertex_descriptor vertexA,
                                TaskGraph& taskGraphA);

    /*!
    *  \fn void setTG_EdgeProperties(const TG_EdgeProperties&, TaskGraph::edge_descriptor, TaskGraph&)
    *
    *  \brief Sets all available internal properties of an edge from a TG_EdgeProperties object
    *
    *  \param [in] propertiesA The properties that shall be assigned to the edge
    *  \param [in] edgeA The edge descriptor the properties shall be assigned to
    *  \param [in] taskGraphA The taskGraph we are working on
    *
    *  \details
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    */
    void setTG_EdgeProperties(const TG_EdgeProperties& propertiesA,
                              TaskGraph::edge_descriptor edgeA,
                              TaskGraph& taskGraphA);

    /*!
    *  \fn void setTG_VertexProperties(const TG_VertexType, const bool, const bool, const unsigned int, const std::string, const std::string, const TaskGraph::vertex_descriptor, TaskGraph&)
    *
    *  \brief Sets all available internal properties of a vertex.
    *
    *  \param [in] typeA The vertex type
    *  \param [in] isInputVertexA true, if the vertex in created from a function parameter
    *  \param [in] isOutputVertexA true, if the vertex is directly connected to the return vertex
    *  \param [in] computationCostA The costs for passing the vertex
    *  \param [in] outputDataTypeA The datatype of the vertex output
    *  \param [in] descriptionA Short description and additional information
    *  \param [in] vertexA The vertex descriptor the properties shall be assigned to
    *  \param [in] taskGraphA The TaskGraph we are working on
    *
    *  \details
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    */
    void setTG_VertexProperties(const TG_VertexType typeA,
                                const bool isInputVertexA,
                                const bool isOutputVertexA,
                                const unsigned int computationCostA,
                                const std::string outputDataTypeA,
                                const std::string descriptionA,
                                const TaskGraph::vertex_descriptor vertexA,
                                TaskGraph& taskGraphA);

    /*!
    *  \fn void setTG_EdgeProperties(const bool, const unsigned int, const unsigned int, const std::string, const std::string, unsigned int, const std::string, const TaskGraph::edge_descriptor, TaskGraph&)
    *
    *  \brief Sets all available internal properties of an edge.
    *
    *  \param [in] isControlFlowEdgeA true, if the edge is used to represent control flow
    *  \param [in] internalWeightA Weight of the edge, when used for communication inside a cluster
    *  \param [in] externalWeightA Weight of the edge, when used for communication between clusters
    *  \param [in] edgeTypeA Type of the edge
    *  \param [in] edgeDataTypeA Datatype transferred by the edge
    *  \param [in] parameterPositionA Position of the parameter referenced by the edge for operators and function calls
    *  \param [in] descriptionA Short description and additional information
    *  \param [in] edgeA The edge descriptor the properties shall be assigned to
    *  \param [in] taskGraphA The taskGraph we are working on
    *
    *  \details
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    */
    void setTG_EdgeProperties(const bool isControlFlowEdgeA,
                              const unsigned int internalWeightA,
                              const unsigned int externalWeightA,
                              const std::string edgeTypeA,
                              const std::string edgeDataTypeA,
                              unsigned int parameterPositionA,
                              const std::string descriptionA,
                              const TaskGraph::edge_descriptor edgeA,
                              TaskGraph& taskGraphA);

    /*!
    *  \fn unsigned int getNextTG_VertexId(TaskGraph&)
    *
    *  \brief Returns the ID that should be assigned to the next vertex
    *
    *  \param taskGraphA The task-graph we are working on
    *
    *  \returns The vertex id that must be used for the next vertex
    *
    *  \details Gets the vertex ID that must be used for the next vertex
    *			from the task graph object.
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    */
    unsigned int getNextTG_VertexId(TaskGraph& taskGraphA);

    /*!
    *  \fn unsigned int getNextTG_EdgeId(TaskGraph&)
    *
    *  \brief Returns the ID that should be assigned to the next edge
    *
    *  \param taskGraphA The task graph we are working on
    *
    *  \returns The edge ID that must be used for the next edge
    *
    *  \details Gets the edge ID that must be used for the next edge
    *			from the task-graph object.
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    */
    unsigned int getNextTG_EdgeId(TaskGraph& taskGraphA);

    /*!
    *  \class TaskGraph_VertLblWriter
    *  \brief This class is the functor, used as label writer for vertices, when writing task graphs to dot files
    *
    *  \tparam idT Type of a property map storing the vertex id of a task-graphs vertices
    *  \tparam vertTypeT Type of a property map storing the vertex types of a task-graphs vertices
    *  \tparam computationCostT Type of a property map storing the computation cost of a task-graphs vertices
    *  \tparam outputDataTypeT Type of a property map storing the output data type of a task-graphs vertices
    *  \tparam descriptionT Type of a property map storing the description of a task-graphs vertices
    *
    *  \details
    *  
    *
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    template <class idT,
              class vertTypeT,
              class computationCostT,
              class outputDataTypeT,
              class descriptionT>
    class TaskGraph_VertLblWriter
    {
      public:
          /*!
          *  \brief Constructor
          *
          *  \param [in] idMapA The property map storing the vertex id of a task-graphs vertices
          *  \param [in] typeMapA The property map storing the vertex types of a task-graphs vertices
          *  \param [in] computationCostMapA The property map storing the computation cost of a task-graphs vertices
          *  \param [in] outputDataTypeMapA The property map storing the output data type of a task-graphs vertices
          *  \param [in] descriptionMapA The property map storing the description of a task graphs-vertices
          *
          *  \details Creates a new TaskGraph_VertLblWriter object
          *
          *  \author Florian Fricke
          *
          *  \version 2015-06-11: Initial
          */
          TaskGraph_VertLblWriter(idT idMapA,
                                vertTypeT typeMapA,
                                computationCostT computationCostMapA,
                                outputDataTypeT outputDataTypeMapA,
                                descriptionT descriptionMapA)
            : idMap(idMapA), typeMap(typeMapA),
              computationCostMap(computationCostMapA),
              outputDataTypeMap(outputDataTypeMapA),
              descriptionMap(descriptionMapA)
        {
        }
        
          /*!
          *  \fn void operator( )(std::ostream&, const Vertex&) const
          *
          *  \brief Writes the label of a vertex to a dot file
          *
          *  \tparam Vertex Type of the used vertex descriptor
          *
          *  \param out ostream, the label is written to
          *  \param v The The vertex, that is written
          *
          *  \details Writes the properties of a task graphs vertex
          *			  to a dot-file.
          *
          *  \author Florian Fricke
          *
          *  \version 2015-06-11: Initial
          */
        template <class Vertex>
        void operator( )(std::ostream& out, const Vertex& v) const
        {
            std::regex recordChars(R"([|\[\]\<\>\.])");
            
			out << "[shape=Mrecord ";
			if (get(typeMap, v) == TG_VertexType::VarInputVertex)
				out << "rank=source ";

			out << "label=\"{ ";
            out << get(typeMap, v);
			out << "|";
			//out << "VertexID: " << get(idMap, v);
			//out << "|";
			//out << "Cost: " << get(computationCostMap, v);
			//out << "|";
			out << "Type: " << get(outputDataTypeMap, v);
            out << "|" << std::regex_replace(get(descriptionMap, v), recordChars, "\\$&");
            out << "}\"]";
        }

      private:
        idT idMap;								//!<\brief The property map storing the vertex id of a task-graphs vertices
        vertTypeT typeMap;						//!<\brief The property map storing the vertex types of a task- graphs vertices
        computationCostT computationCostMap;	//!<\brief The property map storing the computation cost of a task- graphs vertices
        outputDataTypeT outputDataTypeMap;		//!<\brief The property map storing the output data type of a task- graphs vertices
        descriptionT descriptionMap;			//!<\brief The property map storing the description of a task-graphs vertices
    };

    /*!
    *  \fn inline TaskGraph_VertLblWriter<idT, vertTypeT, computationCostT, outputDataTypeT, descriptionT> make_TaskGraph_VertLblWriter(idT, vertTypeT, computationCostT, outputDataTypeT, descriptionT)
    *  \brief This function makes the creation of TaskGraph_VertLblWriter simpler
    *
    *  \tparam idT Type of a property map storing the vertex id of a task-graphs vertices
    *  \tparam vertTypeT Type of a property map storing the vertex types of a task-graphs vertices
    *  \tparam computationCostT Type of a property map storing the computation cost of a task-graphs vertices
    *  \tparam outputDataTypeT Type of a property map storing the output data type of a task-graphs vertices
    *  \tparam descriptionT Type of a property map storing the description of a task graphs-vertices
    *
    *  \param [in] idMapA The property map storing the vertex id of a task-graphs vertices
    *  \param [in] typeMapA The property map storing the vertex types of a task-graphs vertices
    *  \param [in] computationCostMapA The property map storing the computation cost of a task-graphs vertices
    *  \param [in] outputDataTypeMapA The property map storing the output data type of a task-graphs vertices
    *  \param [in] descriptionMapA The property map storing the description of a task-graphs vertices
    *
    *  \returns A TaskGraph_VertLblWriter with template parameters derived from the functions arguments
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    template <class idT,
              class vertTypeT,
              class computationCostT,
              class outputDataTypeT,
              class descriptionT>
    inline TaskGraph_VertLblWriter<idT,
                                   vertTypeT,
                                   computationCostT,
                                   outputDataTypeT,
                                   descriptionT>
    make_TaskGraph_VertLblWriter(idT idMapA,
                                 vertTypeT typeMapA,
                                 computationCostT computationCostMapA,
                                 outputDataTypeT outputDataTypeMapA,
                                 descriptionT descriptionMapA)
    {
        return TaskGraph_VertLblWriter<idT,
                                       vertTypeT,
                                       computationCostT,
                                       outputDataTypeT,
                                       descriptionT>(idMapA,
                                                     typeMapA,
                                                     computationCostMapA,
                                                     outputDataTypeMapA,
                                                     descriptionMapA);
    };


    /*!
    *  \class TaskGraph_EdgeLblWriter
    *  \brief This class is the functor, used as label writer for edges, when writing task graphs to dot files
    *
    *  \tparam idT Type of a property map storing the vertex id of a task-graphs edges
    *  \tparam isControlFlowEdgeT Type of a property map storing the isControlFlowEdge property of a task-graphs edges
    *  \tparam internalWeightT Type of a property map storing the internalWeight of a task-graphs edges
    *  \tparam externalWeightT Type of a property map storing the externalWeight of a task-graphs edges
    *  \tparam edgeTypeT Type of a property map storing the edgeType of a task-graphs edges
    *  \tparam edgeDataTypeT Type of a property map storing the edgeDataType of a task-graphs edges
    *  \tparam descriptionT Type of a property map storing the description of a task-graphs edges
    *
    *  \details
    *
    *
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    template <class idT,
              class isControlFlowEdgeT,
              class internalWeightT,
              class externalWeightT,
              class edgeTypeT,
              class edgeDataTypeT,
              class descriptionT>
    class TaskGraph_EdgeLblWriter
    {
      public:
        /*!
        *  \brief Constructor
        *
        *  \param [in] idMapA The property map storing the vertex id of a task-graphs edges
        *  \param [in] isControlFlowEdgeMapA The property map storing the isControlFlowEdge property of a task- graphs edges
        *  \param [in] internalWeightMapA The property map storing the internalWeight of a task-graphs edges
        *  \param [in] externalWeightMapA The property map storing the externalWeight of a task-graphs edges
        *  \param [in] edgeTypeMapA The property map storing the edgeThe task-graphs edges
        *  \param [in] edgeDataTypeMapA The property map storing the edgeDataThe task-graphs edges
        *  \param [in] descriptionMapA The property map storing the description of a task-graphs edges
        *
        *  \details Creates a new TaskGraph_VertLblWriter object
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        TaskGraph_EdgeLblWriter(idT idMapA,
                                isControlFlowEdgeT isControlFlowEdgeMapA,
                                internalWeightT internalWeightMapA,
                                externalWeightT externalWeightMapA,
                                edgeTypeT edgeTypeMapA,
                                edgeDataTypeT edgeDataTypeMapA,
                                descriptionT descriptionMapA)
            : idMap(idMapA), isControlFlowEdgeMap(isControlFlowEdgeMapA),
              internalWeightMap(internalWeightMapA),
              externalWeightMap(externalWeightMapA), typeMap(edgeTypeMapA),
              edgeDataTypeMap(edgeDataTypeMapA), descriptionMap(descriptionMapA)
        {
        }

        /*!
        *  \fn void operator( )(std::ostream&, const Vertex&) const
        *
        *  \brief Writes the label of an edge to a dot file
        *
        *  \tparam Edge Type of the used edge descriptor
        *
        *  \param out ostream, the label is written to
        *  \param e The The edge, that is written
        *
        *  \details Writes the properties of a task graphs edge
        *			  to a dot-file.
        *
        *  \author Florian Fricke
        *
        *  \version 2015-06-11: Initial
        */
        template <class Edge>
        void operator( )(std::ostream &out, const Edge &e) const
        {
            out << "[ label=\" ";
            out << get(descriptionMap, e);
            out << " \\[";
            out << get(edgeDataTypeMap, e);
            out << "\\]";
            out << "\"]";
        }

      private:
        idT idMap;									//!<\brief The property map storing the vertex id of a task- graphs edges
        isControlFlowEdgeT isControlFlowEdgeMap;	//!<\brief The property map storing the isControlFlowEdge property of a task graphs vertices
        internalWeightT internalWeightMap;			//!<\brief The property map storing the internalWeight of a task- graphs vertices
        externalWeightT externalWeightMap;			//!<\brief The property map storing the externalWeight of a task graphs vertices
        edgeTypeT typeMap;							//!<\brief The property map storing the edgeThe task-graphs vertices
        edgeDataTypeT edgeDataTypeMap;				//!<\brief The property map storing the edgeDataThe task-graphs vertices
        descriptionT descriptionMap;				//!<\brief The property map storing the description of a task- graphs vertices
    };

    /*!
    *  \fn  inline TaskGraph_EdgeLblWriter<idT, isControlFlowEdgeT, internalWeightT, externalWeightT, edgeTypeT, edgeDataTypeT, descriptionT> make_TaskGraph_EdgeLblWriter(idT, isControlFlowEdgeT, internalWeightT, externalWeightT, edgeTypeT, edgeDataTypeT, descriptionT)
    *  \brief  This function makes the creation of TaskGraph_EdgeLblWriter simpler
    *
    *  \tparam idT Type of a property map storing the vertex id of a task-graphs edges
    *  \tparam isControlFlowEdgeT Type of a property map storing the isControlFlowEdge property of a task-graphs edges
    *  \tparam internalWeightT Type of a property map storing the internalWeight of a task-graphs edges
    *  \tparam externalWeightT Type of a property map storing the externalWeight of a task-graphs edges
    *  \tparam edgeTypeT Type of a property map storing the edgeType of a task-graphs edges
    *  \tparam edgeDataTypeT Type of a property map storing the edgeDataType of a task-graphs edges
    *  \tparam descriptionT Type of a property map storing the description of a task-graphs edges
    *
    *  \param [in] idMapA The property map storing the vertex id of a task-graphs edges
    *  \param [in] isControlFlowEdgeMapA The property map storing the isControlFlowEdge property of a task-graphs edges
    *  \param [in] internalWeightMapA The property map storing the internalWeight of a task-graphs edges
    *  \param [in] externalWeightMapA The property map storing the externalWeight of a task-graphs edges
    *  \param [in] edgeTypeMapA The property map storing the edgeThe task-graphs edges
    *  \param [in] edgeDataTypeMapA The property map storing the edgeDataThe task-graphs edges
    *  \param [in] descriptionMapA The property map storing the description of a task-graphs edges
    *
    *   \returns A TaskGraph_EdgeLblWriter with template parameters derived from the functions arguments
    *
    *  \details
    *
    *
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    template <class idT,
              class isControlFlowEdgeT,
              class internalWeightT,
              class externalWeightT,
              class edgeTypeT,
              class edgeDataTypeT,
              class descriptionT>
    inline TaskGraph_EdgeLblWriter<idT,
                                   isControlFlowEdgeT,
                                   internalWeightT,
                                   externalWeightT,
                                   edgeTypeT,
                                   edgeDataTypeT,
                                   descriptionT>
    make_TaskGraph_EdgeLblWriter(idT idMapA,
                                 isControlFlowEdgeT isControlFlowEdgeMapA,
                                 internalWeightT internalWeightMapA,
                                 externalWeightT externalWeightMapA,
                                 edgeTypeT edgeTypeMapA,
                                 edgeDataTypeT edgeDataTypeMapA,
                                 descriptionT descriptionMapA)
    {
        return TaskGraph_EdgeLblWriter<idT,
                                       isControlFlowEdgeT,
                                       internalWeightT,
                                       externalWeightT,
                                       edgeTypeT,
                                       edgeDataTypeT,
                                       descriptionT>(idMapA,
                                                     isControlFlowEdgeMapA,
                                                     internalWeightMapA,
                                                     externalWeightMapA,
                                                     edgeTypeMapA,
                                                     edgeDataTypeMapA,
                                                     descriptionMapA);
    }


	/*!
	*  \class TaskGraph_GraphLabelWriter
	*  \brief This class is the functor, used as label writer for the graph, when writing task graphs to dot files
	*
	*  \tparam GraphTypeT Type of the Graph, this LabelWriter ist used with
	*
	*  \details
	*
	*
	*
	*  \author Florian Fricke
	*
	*  \version 2015-07-22: Initial
	*
	*/
	template <class GraphTypeT>
	class TaskGraph_GraphLabelWriter
	{
	public:
		/*!
		*  \brief Constructor
		*
		*  \param [in] graphA graphA A pointer to the graph, whos properties shall be written
		*
		*  \details Creates a new TaskGraph_GraphLabelWriter object
		*
		*  \author Florian Fricke
		*
		*  \version 2015-07-22: Initial
		*/
		TaskGraph_GraphLabelWriter(GraphTypeT * const graphA)
			: graph(graphA)
		{

		}

		/*!
		*  \fn void operator( )(std::ostream &out) const
		*
		*  \brief Writes the label of a graph to a dot file
		*

		*  \param out ostream, the label is written to
		*
		*  \details Writes the properties of a task graph
		*			  to a dot-file.
		*
		*  \author Florian Fricke
		*
		*  \version 2015-07-22: Initial
		*/
		void operator( )(std::ostream &out) const
		{
			out << "graph [label= \"" << (*graph)[boost::graph_bundle].graphName << "\"]" << std::endl;
		}

	private:
		GraphTypeT * const graph;
	};


	/*!
	*  inline TaskGraph_GraphLabelWriter<GraphTypeT> make_TaskGraph_GraphLabelWriter(GraphTypeT * const)
	*  \brief  This function makes the creation of TaskGraph_GraphLabelWriter simpler
	*
	*  \tparam GraphTypeT Type of the Graph, this LabelWriter ist used with

	*
	*  \param [in] graphA A pointer to the graph, whos properties shall be written
	*
	*   \returns A TaskGraph_GraphLabelWriter with template parameters derived from the functions arguments
	*
	*  \details
	*
	*
	*
	*  \author Florian Fricke
	*
	*  \version 2015-07-22: Initial
	*
	*/
	template <class GraphTypeT>
	inline TaskGraph_GraphLabelWriter<GraphTypeT> make_TaskGraph_GraphLabelWriter(GraphTypeT * const graphA)
	{
		return TaskGraph_GraphLabelWriter<GraphTypeT>(graphA);
	}

    /*!
    *  \fn   void writeTaskGraphToGraphML(TaskGraph&, const std::string&);
    *  \brief  This function writes a TaskGraph with all internal properties to a GraphML file
    *
    *  \param [in] taskGraphA TaskGraph that shall be written to the file
    *  \param [in] filenameA Name of the file the task graph shall be written to
    *
    *  \details Writes the task-graph to a GraphML file.
    *			This format should be used to exchange task-graphs,
    *			because it contains all properties of vertices, edges
    *			and the graph.
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    void writeTaskGraphToGraphML(TaskGraph &taskGraphA,
                                 const std::string &filenameA);

    /*!
    *  \fn   void writeTaskGraphToDot(TaskGraph&, const std::string&);
    *  \brief  This function writes a TaskGraph with to a Graphviz dot-file
    *
    *  \param [in] taskGraphA TaskGraph that shall be written to the file
    *  \param [in] filenameA Name of the file the task-graph shall be written to
    *
    *  \details Writes the task graph to a GraphViz dot file.
    *			This format should be used to print task-graphs,
    *			because dot can be easily printed using tools from
    *			the Graphviz library.
    *
    *  \author Florian Fricke
    *
    *  \version 2015-06-11: Initial
    *
    */
    void writeTaskGraphToDot(cv_tools::TaskGraph &taskGraphA,
                             const std::string &filenameA);
}

#endif // !TASKGRAPHDEF_H_
