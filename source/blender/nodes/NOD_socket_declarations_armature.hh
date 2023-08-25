#pragma once

#include "NOD_socket_declarations.hh"
#include "BKE_armature_set.hh"

namespace blender::nodes::decl {

    class ArmatureDataBuilder;

    class ArmatureData : public SocketDeclaration {
     private:
      blender::Vector<ArmatureDataComponentType> supported_types__;

      friend ArmatureDataBuilder;

     public:
      using Builder = ArmatureDataBuilder;
      bNodeSocket &build(bNodeTree &ntree, bNode &node) const override;
      bool matches(const bNodeSocket &socket) const override;
      bool can_connect(const bNodeSocket &socket) const override;

      Span<ArmatureDataComponentType> supported_types() const;
    };

    class ArmatureDataBuilder : public SocketDeclarationBuilder<ArmatureData> {
     public:
      ArmatureDataBuilder &supported_type(ArmatureDataComponentType supported_type);
      ArmatureDataBuilder &supported_type(blender::Vector<ArmatureDataComponentType> supported_types);
    };

}  // namespace blender::nodes::decl