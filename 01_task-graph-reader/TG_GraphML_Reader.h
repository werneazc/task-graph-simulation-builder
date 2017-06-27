#ifndef TG_GRAPHML_READER_H_
#define TG_GRAPHML_READER_H_

#include "TaskGraphDef.h"

namespace cv_tools
{
	void TG_Reader(cv_tools::TaskGraph&, std::ifstream&);
}

#endif // TG_GRAPHML_READER_