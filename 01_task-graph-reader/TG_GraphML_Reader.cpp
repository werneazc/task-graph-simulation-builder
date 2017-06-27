#include "TG_GraphML_Reader.h"

#include <boost/property_map/property_map.hpp>

namespace cv_tools
{
    using namespace std;

    void TG_Reader( cv_tools::TaskGraph& inputGraph, ifstream& inFile )
    {
        if ( !inFile.good( ) )
            throw std::invalid_argument( "Could not read in graphML in file" );

        boost::dynamic_properties inputProperties;

        struct graph_name_t
        {
            typedef boost::graph_property_tag kind;
        };
        struct graph_next_vertex_id_t
        {
            typedef boost::graph_property_tag kind;
        };
        struct graph_next_edge_id_t
        {
            typedef boost::graph_property_tag kind;
        };
        struct graph_description_t
        {
            typedef boost::graph_property_tag kind;
        };

        typedef boost::property< graph_name_t, std::string > TG_NameProperty;
        typedef boost::property< graph_next_vertex_id_t, int, TG_NameProperty >
            TG_NextVertexIdProperty;
        typedef boost::property< graph_next_edge_id_t, int, TG_NextVertexIdProperty >
            TG_NextEdgeIdProperty;
        typedef boost::property< graph_description_t, std::string, TG_NextEdgeIdProperty >
            TG_GraphDescriptionProperty;

        struct vertex_id_t
        {
            typedef boost::vertex_property_tag kind;
        };
        struct vertex_type_t
        {
            typedef boost::vertex_property_tag kind;
        };
        struct vertex_is_input_t
        {
            typedef boost::vertex_property_tag kind;
        };
        struct vertex_is_output_t
        {
            typedef boost::vertex_property_tag kind;
        };
        struct vertex_computation_cost_t
        {
            typedef boost::vertex_property_tag kind;
        };
        struct vertex_output_data_type_t
        {
            typedef boost::vertex_property_tag kind;
        };
        struct vertex_description_t
        {
            typedef boost::vertex_property_tag kind;
        };

        typedef boost::property< vertex_id_t, int > VertexIdProperty;
        typedef boost::property< vertex_type_t, TG_VertexType, VertexIdProperty >
            VertexTypeProperty;
        typedef boost::property< vertex_is_input_t, bool, VertexTypeProperty >
            VertexIsInputProperty;
        typedef boost::property< vertex_is_output_t, bool, VertexIsInputProperty >
            VertexIsOutputProperty;
        typedef boost::property< vertex_computation_cost_t, int, VertexIsOutputProperty >
            VertexComputationCostProperty;
        typedef boost::property< vertex_output_data_type_t, string, VertexComputationCostProperty >
            VertexOutputDataTypeProperty;
        typedef boost::property< vertex_description_t, string, VertexOutputDataTypeProperty >
            VertexDescriptionProperty;

        struct edge_id_t
        {
            typedef boost::edge_property_tag kind;
        };
        struct edge_ctrl_flow_t
        {
            typedef boost::edge_property_tag kind;
        };
        struct edge_int_weight_t
        {
            typedef boost::edge_property_tag kind;
        };
        struct edge_ext_weight_t
        {
            typedef boost::edge_property_tag kind;
        };
        struct edge_type_t
        {
            typedef boost::edge_property_tag kind;
        };
        struct edge_data_type_t
        {
            typedef boost::edge_property_tag kind;
        };
        struct edge_parameter_position_t
        {
            typedef boost::edge_property_tag kind;
        };
        struct edge_description_t
        {
            typedef boost::edge_property_tag kind;
        };

        typedef boost::property< edge_id_t, int > EdgeIDProperty;
        typedef boost::property< edge_ctrl_flow_t, bool, EdgeIDProperty > EdgeCtrlFlowProperty;
        typedef boost::property< edge_int_weight_t, int, EdgeCtrlFlowProperty >
            EdgeIntWeightProperty;
        typedef boost::property< edge_ext_weight_t, int, EdgeIntWeightProperty >
            EdgeExtWeightProperty;
        typedef boost::property< edge_type_t, string, EdgeExtWeightProperty > EdgeTypeProperty;
        typedef boost::property< edge_data_type_t, string, EdgeTypeProperty > EdgeDataTypeProperty;
        typedef boost::property< edge_parameter_position_t, int, EdgeDataTypeProperty >
            EdgeParameterPositionProperty;
        typedef boost::property< edge_description_t, string, EdgeParameterPositionProperty >
            EdgeDescriptionProperty;

        typedef boost::adjacency_list< boost::vecS, boost::listS, boost::bidirectionalS,
            VertexDescriptionProperty, EdgeDescriptionProperty,
            TG_GraphDescriptionProperty > ImportTaskGraphT;

        ImportTaskGraphT tg;

        // creation of property maps for all graph properties
        boost::ref_property_map< cv_tools::TaskGraph*, std::string > graphName_map(
            boost::get_property( tg, graph_name_t( ) ) );
        boost::ref_property_map< cv_tools::TaskGraph*,  int > nextVertexId_map(
            boost::get_property( tg, graph_next_vertex_id_t( ) ) );
        boost::ref_property_map< cv_tools::TaskGraph*,  int > nextEdgeId_map(
            boost::get_property( tg, graph_next_edge_id_t( ) ) );
        boost::ref_property_map< cv_tools::TaskGraph*, std::string > description_map(
            boost::get_property( tg, graph_description_t( ) ) );

        // creation of property maps for all vertex properties
        auto vertexID_map = boost::get( vertex_id_t( ), tg );
        auto vertexType_map = boost::get( vertex_type_t( ), tg );
        auto isInput_map = boost::get( vertex_is_input_t( ), tg );
        auto isOutput_map = boost::get( vertex_is_output_t( ), tg );
        auto computationCost_map = boost::get( vertex_computation_cost_t( ), tg );
        auto outputDataType_map = boost::get( vertex_output_data_type_t( ), tg );
        auto vertexDescription_map = boost::get( vertex_description_t( ), tg );

        // creation of property maps for all edge properties
        auto edgeID_map = boost::get( edge_id_t( ), tg );
        auto edgeCtrlFlow_map = boost::get( edge_ctrl_flow_t( ), tg );
        auto intWeight_map = boost::get( edge_int_weight_t( ), tg );
        auto extWeight_map = boost::get( edge_ext_weight_t( ), tg );
        auto edgeType_map = boost::get( edge_type_t( ), tg );
        auto edgeDataType_map = boost::get( edge_data_type_t( ), tg );
        auto edgeParameterPosition_map = boost::get( edge_parameter_position_t( ), tg );
        auto edgeDescription_map = boost::get( edge_description_t( ), tg );

        // adding the property maps to the dynamic properties object for output
        inputProperties.property( "graphName", graphName_map );
        inputProperties.property( "nextVertexId", nextVertexId_map );
        inputProperties.property( "nextEdgeId", nextEdgeId_map );
        inputProperties.property( "description", description_map );

        inputProperties.property( "vertexID", vertexID_map );
        inputProperties.property( "vertexType", vertexType_map );
        inputProperties.property( "isInput", isInput_map );
        inputProperties.property( "isOutput", isOutput_map );
        inputProperties.property( "computationCost", computationCost_map );
        inputProperties.property( "outputDataType", outputDataType_map );
        inputProperties.property( "vertexDescription", vertexDescription_map );

        inputProperties.property( "edgeID", edgeID_map );
        inputProperties.property( "edgeCtrlFlow", edgeCtrlFlow_map );
        inputProperties.property( "intWeight", intWeight_map );
        inputProperties.property( "extWeight", extWeight_map );
        inputProperties.property( "edgeType", edgeType_map );
        inputProperties.property( "edgeDataType", edgeDataType_map );
        inputProperties.property( "parameterPosition", edgeParameterPosition_map );
        inputProperties.property( "edgeDescription", edgeDescription_map );

        boost::read_graphml( inFile, tg, inputProperties, 0u );

        inputGraph.clear( );

        inputGraph[ boost::graph_bundle ].graphName = boost::get_property( tg, graph_name_t( ) );
        inputGraph[ boost::graph_bundle ].nextVertexId =
            boost::get_property( tg, graph_next_vertex_id_t( ) );
        inputGraph[ boost::graph_bundle ].nextEdgeId =
            boost::get_property( tg, graph_next_edge_id_t( ) );
        inputGraph[ boost::graph_bundle ].description =
            boost::get_property( tg, graph_description_t( ) );

        auto tg_verts = boost::vertices( tg );

        std::map< ImportTaskGraphT::vertex_descriptor, TaskGraph::vertex_descriptor > InToOutMap;

        for ( auto vertex = tg_verts.first; vertex != tg_verts.second; ++vertex )
            {
                auto nv = boost::add_vertex( inputGraph );
                inputGraph[ nv ].vertexID = boost::get( vertexID_map, *vertex );
                inputGraph[ nv ].type = boost::get( vertexType_map, *vertex );
                ;
                inputGraph[ nv ].isInputVertex = boost::get( isInput_map, *vertex );
                inputGraph[ nv ].isOutputVertex = boost::get( isOutput_map, *vertex );
                inputGraph[ nv ].computationCost = boost::get( computationCost_map, *vertex );
                inputGraph[ nv ].outputDataType = boost::get( outputDataType_map, *vertex );
                inputGraph[ nv ].description = boost::get( vertexDescription_map, *vertex );

                InToOutMap.insert( std::make_pair( *vertex, nv ) );
            }

        // cout << "Vertices ready, and now to something completely different!\n";

        auto tg_edges = boost::edges( tg );

        for ( auto edge = tg_edges.first; edge != tg_edges.second; ++edge )
            {
                auto ne = boost::add_edge(
                    InToOutMap[ edge->m_source ], InToOutMap[ edge->m_target ], inputGraph );
                inputGraph[ ne.first ].edgeID = boost::get( edgeID_map, *edge );
                inputGraph[ ne.first ].isControlFlowEdge = boost::get( edgeCtrlFlow_map, *edge );
                inputGraph[ ne.first ].internalWeight = boost::get( intWeight_map, *edge );
                inputGraph[ ne.first ].externalWeight = boost::get( extWeight_map, *edge );
                inputGraph[ ne.first ].edgeType = boost::get( edgeType_map, *edge );
                inputGraph[ ne.first ].edgeDataType = boost::get( edgeDataType_map, *edge );
                inputGraph[ ne.first ].parameterPosition =
                    boost::get( edgeParameterPosition_map, *edge );
                inputGraph[ ne.first ].description = boost::get( edgeDescription_map, *edge );
            }

        // cout << "Edges ready, and now to something completely different!\n";
    }
}