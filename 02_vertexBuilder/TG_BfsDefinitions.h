//! \file TG_BfsDefinitions.h
//! \brief Data structure and Type definitions for task graph building informations

#ifndef TG_BFSDEFINITIONS_H_
#define TG_BFSDEFINITIONS_H_

#include <map>
#include <utility>
#include <string>
#include <TaskGraphDef.h>


namespace vc_utils
{
    
    /************************************************************************/
    /* structure definitions                                                */
    /************************************************************************/
    
    //! \enum VertexCategory
    //! \brief information category for vertex information
    enum class VertexCategory {
        Uninitialized,
        Literal,
        Input,
        Output,
        Operation,
        Call
    };


    //! \struct vertexDataStruct
    //! \brief data structure to save building information
    struct vertexDataStruct {
    public:
        //! \struct inputDataStruct
        //! \brief data structure to save connecting information
        struct inputDataStruct
        {
        public:
            /************************************************************************/
            /* type definitions                                                     */
            /************************************************************************/
            typedef std::string subjectType_t;
            typedef std::string dataType_t;
        public:
            unsigned int observerId;
            dataType_t dataType;
            subjectType_t subject;
            unsigned int subjectId;
            unsigned int subjectValueId;

            inputDataStruct() : 
                observerId(std::numeric_limits<unsigned int>::max()),
                dataType(""),
                subject(""),
                subjectId(std::numeric_limits<unsigned int>::max()),
                subjectValueId(std::numeric_limits<unsigned int>::max())
            {}
        };

    public:
        /************************************************************************/
        /* type definitions:                                                    */
        /************************************************************************/
        typedef std::map<std::string, std::pair<std::string, unsigned int> > outputDataMap_t;
        typedef std::vector<inputDataStruct> inputDataVec_t;
        typedef std::string value_t;
        typedef std::string observerOwneType_t;
        typedef std::string classtype_t;

        VertexCategory category;
        classtype_t kind;
        value_t value;
        observerOwneType_t owner;
        unsigned int ownerId;
        outputDataMap_t outgoingEdges;
        inputDataVec_t incomingEdges;

        vertexDataStruct() :
            category(VertexCategory::Uninitialized),
            kind(""),
            value(""),
            owner(""),
            ownerId(std::numeric_limits<unsigned int>::max())
        {}
    };


    /************************************************************************/
    /* type definitions                                                     */
    /************************************************************************/

    //! \typedef vertexDesc_t
    //! \brief vertex descriptor
    typedef boost::graph_traits< cv_tools::TaskGraph >::vertex_descriptor vertexDesc_t;

    //! \typedef vertexDesc_t
    //! \brief map that stores vertex information separated by vertex descriptor
    typedef std::map<vertexDesc_t, vertexDataStruct> vertexInformationMap_t;

}

#endif // !TG_BFSDEFINITIONS_H_
