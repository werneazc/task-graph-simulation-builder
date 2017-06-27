//! \file TG_Vertex_Builder.h
//! \brief Vertex builder helper functions

#ifndef TG_VERTEX_BUILDER_H_
#define TG_VERTEX_BUILDER_H_

#include <TaskGraphDef.h>
#include "TG_Visitor_Functions.h"
#include <vector>

namespace vc_utils
{
    
   
    void getBuildingInformation(const cv_tools::TaskGraph& _graph);

    vertexDesc_t restructGraphForBFS(cv_tools::TaskGraph& _graph);

}

#endif // !TG_VERTEX_BUILDER_H_
