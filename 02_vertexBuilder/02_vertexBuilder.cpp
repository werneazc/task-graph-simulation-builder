
#include <boost/program_options.hpp>
#include <TG_GraphML_Reader.h>
#include <cstdlib>
#include <fstream>
#include <exception>
#include <boost/exception/info.hpp>
#include "TG_Vertex_Builder.h"

namespace vc_utils {



}

int main(int argc, char* argv[])
{

    namespace cmdPars = boost::program_options;
    std::string inFilePath;

    cmdPars::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")(
        "file", cmdPars::value< std::string >(&inFilePath), "set graphML input file");


    cmdPars::variables_map vMap;
    cmdPars::store(cmdPars::parse_command_line(argc, argv, desc), vMap);
    cmdPars::notify(vMap);

    cv_tools::TaskGraph readTaskGraph;

    try
    {
        if (vMap.count("help"))
        {
            std::cout << desc << std::endl;
            return EXIT_SUCCESS;
        }

        if (vMap.count("file"))
        {
            std::ifstream inFile(vMap.at("file").as< std::string >());
            cv_tools::TG_Reader(readTaskGraph, inFile);
        }
        else
            throw std::invalid_argument("Please insert a valid graphML file");
    }
    catch (std::invalid_argument e)
    {
        std::cerr << "error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    vc_utils::vertexInformationMap_t vertexData;

    vc_utils::task_graph_vertex_visitor informationCrawler(&vc_utils::visitorFunctionMap, &vertexData);

    informationCrawler(readTaskGraph);

    std::cout << "collecting results: " << std::endl;

    for (auto& entry : vertexData)
    {

        auto category = entry.second.category;

        switch (category)
        {
        case vc_utils::VertexCategory::Uninitialized:
            break;
        case vc_utils::VertexCategory::Literal:
            std::cout << "\nliteral vertex: " << std::endl;
            std::cout << "module kind: " << entry.second.kind << std::endl;
            std::cout << "value name: " << entry.second.outgoingEdges.begin()->first << std::endl;
            std::cout << "\tvalue: " << entry.second.outgoingEdges.begin()->second.first;
            std::cout << " " << entry.second.value << std::endl;
            std::cout << "\tvalue ID: " << entry.second.outgoingEdges.begin()->second.second << std::endl;
            break;
        case vc_utils::VertexCategory::Input:
            std::cout << "\ninput vertex: " << std::endl;
            std::cout << "module kind: " << entry.second.kind << std::endl;
            std::cout << "value name: " << entry.second.outgoingEdges.begin()->first << std::endl;
            std::cout << "\tdata type: " << entry.second.outgoingEdges.begin()->second.first << std::endl;
            std::cout << "\tvalue ID: " << entry.second.outgoingEdges.begin()->second.second << std::endl;
            break;
        case vc_utils::VertexCategory::Output:
            std::cout << "\noutput vertex: " << std::endl;
            std::cout << "module kind: " << entry.second.kind << std::endl;
            for (auto& edge : entry.second.incomingEdges)
            {
                std::cout << "@ observer ID: " << edge.observerId << std::endl;
                std::cout << "\tdata type: " << edge.dataType << std::endl;
                std::cout << "\tsubject: " << edge.subject << std::endl;
                std::cout << "\tsubject ID: " << edge.subjectId << std::endl;
                std::cout << "\tsubject value ID: " << edge.subjectValueId << std::endl;
            }
            break;
        case vc_utils::VertexCategory::Operation:
            std::cout << "\nstandard vertex: " << std::endl;
            std::cout << "module kind: " << entry.second.kind << std::endl;
            std::cout << "observer owner type: " << entry.second.owner << std::endl;
            std::cout << "observer vertex ID: " << entry.second.ownerId << std::endl;
            for (auto& edge : entry.second.incomingEdges)
            {
                std::cout << "@ observer ID: " << edge.observerId << std::endl;
                std::cout << "\tdata type: " << edge.dataType << std::endl;
                std::cout << "\tsubject: " << edge.subject << std::endl;
                std::cout << "\tsubject ID: " << edge.subjectId << std::endl;
                std::cout << "\tsubject value ID: " << edge.subjectValueId << std::endl;
            }
            for (auto& edge : entry.second.outgoingEdges)
            {
                std::cout << "output value name: " << edge.first << std::endl;
                std::cout << "\tdata type: " << edge.second.first << std::endl;
                std::cout << "\tvalue ID: " << edge.second.second << std::endl;
            }
            break;
        case vc_utils::VertexCategory::Call:
            break;
        default:
            break;
        }
       
    }

    return EXIT_SUCCESS;
}
