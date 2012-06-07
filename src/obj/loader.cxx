
#include <cstdlib>
#include <vector>

#include "obj/loader.h"
#include "obj/parser.h"
#include "obj/model.h"
#include "obj/modeldata.h"
#include "obj/modelrenderer.h"
#include "obj/texture.h"

namespace ep2 {
namespace obj {

using std::string;
using std::vector;
using std::tr1::bind;
using std::tr1::unordered_map;
using namespace std::tr1::placeholders;

typedef void (Loader::*Handler) (ModelData::Ptr, const Command&);

#define OBJ_HANDLERTABLE_SIZE 6
#define MTL_HANDLERTABLE_SIZE 8
#define GET_HANDLER(name) &Loader::handle_##name

struct RawHandlerTable {
  const char* tag;
  Handler     handler;
};

static RawHandlerTable obj_handlers_table[OBJ_HANDLERTABLE_SIZE] = {
  {"o", GET_HANDLER(objname) },
  {"v", GET_HANDLER(vertex) },
  {"f", GET_HANDLER(face) },
  {"mtllib", GET_HANDLER(materialimport) },
  {"usemtl", GET_HANDLER(materialusage) },
  {"vt", GET_HANDLER(texcoord) }
};

static RawHandlerTable mtl_handlers_table[MTL_HANDLERTABLE_SIZE] = {
  {"newmtl", GET_HANDLER(newmaterial) },
  {"Ka", GET_HANDLER(ambient) },
  {"Kd", GET_HANDLER(diffuse) },
  {"Ks", GET_HANDLER(specular) },
  {"Tf", GET_HANDLER(emission) },
  {"Ns", GET_HANDLER(shininess) },
  {"d", GET_HANDLER(dissolve) },
  {"map_Kd", GET_HANDLER(texture) }
};

Loader::Loader () {
  for (unsigned i = 0; i < OBJ_HANDLERTABLE_SIZE; i++)
    obj_handlers_[obj_handlers_table[i].tag] =
      bind(obj_handlers_table[i].handler, this, _1, _2);
  for (unsigned i = 0; i < MTL_HANDLERTABLE_SIZE; i++)
    mtl_handlers_[mtl_handlers_table[i].tag] =
      bind(mtl_handlers_table[i].handler, this, _1, _2);
}

Model Loader::load_model (const string& modelname) {
  Parser parser("models/"+modelname+".obj");
  ModelData::Ptr data = ModelData::create();
  while (true) {
    Command cmd;
    if (!parser.parse_command(cmd)) break;
    HandlerTable::iterator handler = obj_handlers_.find(cmd.front());
    if (handler != obj_handlers_.end())
      handler->second(data, cmd);
    else
      printf("Ignoring unsuported OBJ instruction '%s'.\n",
             cmd.front().c_str());
  }
  return Model(ModelRenderer(data));
}

void Loader::load_materiallib (ModelData::Ptr& data, const string& libname) {
  Parser parser("models/"+libname);
  while (true) {
    Command cmd;
    if (!parser.parse_command(cmd)) break;
    HandlerTable::iterator handler = mtl_handlers_.find(cmd.front());
    if (handler != mtl_handlers_.end())
      handler->second(data, cmd);
    else
      printf("Ignoring unsuported MTL instruction '%s'.\n",
             cmd.front().c_str());
  }
}

#define DEFINE_HANDLER(name) \
  void Loader::handle_##name (ModelData::Ptr data, \
                              const Command& cmd)

// OBJ handlers

DEFINE_HANDLER(objname) {
  // TODO: fix?
  if (cmd.size() >= 2)
    data->set_name(cmd[1]);
}

DEFINE_HANDLER(vertex) {
  double raw_vertex[4] = { 0.0, 0.0, 0.0, 1.0 };
  for (unsigned i = 0; i < 4 && i+1 < cmd.size(); i++)
    raw_vertex[i] = atof(cmd[i+1].c_str());
  data->add_vertex(Base4D(raw_vertex));
}

DEFINE_HANDLER(texcoord) {
  double raw_vertex[4] = { 0.0, 0.0, 0.0, 0.0 };
  for (unsigned i = 0; i < 3 && i+1 < cmd.size(); i++)
    raw_vertex[i] = atof(cmd[i+1].c_str());
  data->add_texcoord(Base4D(raw_vertex));
}

static void parse_vtx (Face& face, const string& vtx) {
  size_t begin = 0, pos;
  VertexData vtxdata = VertexData(0, 0, 0);
  pos = vtx.find("/", begin);
  if (pos == string::npos) {
    vtxdata.vtx = strtoul(vtx.c_str(), NULL, 0);
  } else {
    vtxdata.vtx =
      strtoul(vtx.substr(begin, pos-begin).c_str(), NULL, 0);
    vtxdata.tex = strtoul(vtx.substr(pos+1).c_str(), NULL, 0);
  }
  face.push_back(vtxdata);
  // TODO: cleanup + normals?
}

DEFINE_HANDLER(face) {
  Face                    face;
  Command::const_iterator it;
  for (it = cmd.begin()+1; it != cmd.end(); it++)
    parse_vtx(face, *it);
  data->add_face(face);
}

DEFINE_HANDLER(materialimport) {
  string libname = cmd[1];
  load_materiallib(data, libname);
  if (!current_mtlname_.empty()) {
    data->add_material(current_mtlname_, current_material_);
    current_mtlname_.clear();
    current_material_.clear();
  }
}

DEFINE_HANDLER(materialusage) {
  data->add_material_index(cmd[1]);
}

// MTL handlers

DEFINE_HANDLER(newmaterial) {
  if (!current_mtlname_.empty())
    data->add_material(current_mtlname_, current_material_);
  current_material_.clear();
  current_mtlname_ = cmd[1];
}

#define MATERIAL_COLORS(action) \
  action(ambient) \
  action(diffuse) \
  action(specular) \
  action(emission)

#define DEFINE_COLORHANDLER(color) \
  DEFINE_HANDLER(color) { \
    if (current_mtlname_.empty()) \
      return; /* TODO: warning */ \
    for (unsigned i = 1; i < cmd.size() && i <= 4; ++i) \
      current_material_.color[i-1] = atof(cmd[i].c_str()); \
  }

MATERIAL_COLORS(DEFINE_COLORHANDLER)

#undef DEFINE_COLORHANDLER
#undef MATERIAL_COLORS

DEFINE_HANDLER(shininess) {
  if (current_mtlname_.empty())
    return; /* TODO: warning */
  current_material_.spec_exponent = atof(cmd[1].c_str());
}

DEFINE_HANDLER(dissolve) {
  if (current_mtlname_.empty())
    return; /* TODO: warning */
  current_material_.opacy = atof(cmd[1].c_str());
}

DEFINE_HANDLER(texture) {
  if (current_mtlname_.empty())
    return; /* TODO: warning */
  current_material_.texture = Texture::get(cmd[1]);
}

#undef DEFINE_HANDLER

} // namespace obj
} // namespace ep2


