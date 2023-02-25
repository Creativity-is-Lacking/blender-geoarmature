#include "node_geometry_util.hh"

namespace blender::nodes::node_geo_get_bone_by_name_cc {

static void node_declare(NodeDeclarationBuilder &b)
{
  b.add_input<decl::ArmatureData>(N_("Armature"));
  b.add_output<decl::Object>(N_("Armature"));
}
static void node_geo_exec(GeoNodeExecParams params)
{
  GeometrySet geometry_set = params.extract_input<GeometrySet>("Geometry");
}

}  // namespace blender::nodes::node_geo_get_bone_by_name_cc

void register_node_type_geo_node_get_bone_by_name()
{
  namespace file_ns = blender::nodes::node_geo_get_bone_by_name_cc;

  static bNodeType ntype;

  geo_node_type_base(&ntype, GEO_NODE_GET_BONE_BY_NAME, "Get Bone by Name", NODE_CLASS_GEOMETRY);
  ntype.declare = file_ns::node_declare;
  ntype.geometry_node_execute = file_ns::node_geo_exec;
  nodeRegisterType(&ntype);
}
