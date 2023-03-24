/* SPDX-License-Identifier: GPL-2.0-or-later */
#undef rad1
#undef rad2

#include "BKE_armature.h"
#include "DNA_armature_types.h"
#include "node_geometry_util.hh"


    namespace blender::nodes::node_geo_unpack_armature_cc
{

  static void node_declare(NodeDeclarationBuilder & b)
  {
    b.add_input<decl::Object>(N_("Armature")).hide_label();
    b.add_output<decl::ArmatureData>(N_("Armature"));
    //b.add_output<decl::Float>(N_("Temp output"));
  }
  static void node_geo_exec(GeoNodeExecParams params)
  {
    printf("unpack started\n");
    Object *object = params.get_input<Object *>("Armature");
    bArmature *armature = BKE_armature_from_object(object);
    if(armature != NULL){
      printf("set output\n");
      printf("type: %s", typeid(std::remove_cv<std::remove_reference<ArmatureComponent>::type>::type).name());
      ArmatureComponent *out = new ArmatureComponent();
      out->replace(armature, GeometryOwnershipType::Editable);
      printf("copy complete\n");
      params.set_output<ArmatureComponent>("Armature", std::move(*out));
    } else {
      params.error_message_add(NodeWarningType::Error, TIP_("Input must be an Armature object"));
    }
    printf("unpack finished\n");
  }
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


