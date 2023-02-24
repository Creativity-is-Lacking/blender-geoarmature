/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "../../../makesdna/DNA_modifier_types.h"

#include "node_geometry_util.hh"


    namespace blender::nodes::node_geo_unpack_armature_cc
{

  static void node_declare(NodeDeclarationBuilder & b)
  {
    b.add_input<decl::Object>(N_("Armature")).hide_label();
    b.add_output<decl::ArmatureData>(N_("Armature"));
  }
  static void node_geo_exec(GeoNodeExecParams params)
  {
    Object *object = params.get_input<Object *>("Armature");
    BLI_findlink(&object->modifiers, 0);
    for (int i = 0; i < BLI_listbase_count(&object->modifiers); i++) {
      ModifierData* modifier = (ModifierData*)BLI_findlink(&object->modifiers, i);
      printf("modifier name: %.*s\n", 32, modifier->name);
    }
  }
  /*static void node_geo_exec(GeoNodeExecParams params)
  {
    GeometrySet geometry_set = params.extract_input<GeometrySet>("Geometry");
  }*/

}  // namespace blender::nodes::node_geo_unpack_armature_cc

void register_node_type_geo_unpack_armature()
{
  namespace file_ns = blender::nodes::node_geo_unpack_armature_cc;

  static bNodeType ntype;

  geo_node_type_base(&ntype, GEO_NODE_UNPACK_ARMATURE, "Unpack Armature", NODE_CLASS_GEOMETRY);
  ntype.declare = file_ns::node_declare;
  ntype.geometry_node_execute = file_ns::node_geo_exec;
  nodeRegisterType(&ntype);
}


