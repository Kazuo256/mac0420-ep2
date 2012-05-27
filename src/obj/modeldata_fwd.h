
#ifndef EP2_OBJ_MODELDATA_FWD_H_
#define EP2_OBJ_MODELDATA_FWD_H_

#include <tr1/memory>

namespace ep2 {
namespace obj {

typedef std::vector<unsigned> Face;

class ModelData;

typedef std::tr1::shared_ptr<ModelData> ModelDataPtr;


} // namespace obj
} // namespace ep2

#endif

