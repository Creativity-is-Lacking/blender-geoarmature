/* SPDX-License-Identifier: GPL-2.0-or-later */
#undef rad1
#undef rad2

#include "BKE_armature.h"
#include "DNA_armature_types.h"

#include "DNA_volume_types.h"

#include "BKE_geometry_set.hh"
#include "BKE_lib_id.h"

/* -------------------------------------------------------------------- */
/** \name Geometry Component Implementation
 * \{ */

ArmatureComponent::ArmatureComponent() : ArmatureDataComponent(GEO_COMPONENT_TYPE_ARMATURE)
{
}
ArmatureComponent::ArmatureComponent(ArmatureComponent &&in) : ArmatureDataComponent(GEO_COMPONENT_TYPE_ARMATURE) {
  armature_ = in.armature_;
  ownership_ = in.ownership_;
}

ArmatureComponent::~ArmatureComponent()
{
  this->clear();
}

ArmatureDataComponent *ArmatureComponent::copy() const
{
  ArmatureComponent *new_component = new ArmatureComponent();
  if (armature_ != nullptr) {
    int flags = LIB_ID_COPY_LOCALIZE;
    bArmature *armature = (bArmature *)BKE_id_copy_ex(nullptr, &armature_->id, nullptr, flags);
    new_component->armature_ = armature;
    new_component->ownership_ = GeometryOwnershipType::Owned;
  }
  return new_component;
}

void ArmatureComponent::clear()
{
  BLI_assert(this->is_mutable());
  if (armature_ != nullptr) {
    if (ownership_ == GeometryOwnershipType::Owned) {
      BKE_id_free(nullptr, armature_);
    }
    armature_ = nullptr;
  }
}

/*bool ArmatureComponent::has_armature() const
{
  return armature_ != nullptr;
}*/

void ArmatureComponent::replace(bArmature *armature, GeometryOwnershipType ownership)
{
  BLI_assert(this->is_mutable());
  this->clear();
  armature_ = armature;
  ownership_ = ownership;
}
/*
bArmature *ArmatureComponent::release()
{
  BLI_assert(this->is_mutable());
  Volume *volume = volume_;
  volume_ = nullptr;
  return volume;
}

const bArmature *ArmatureComponent::get_for_read() const
{
  return armature_;
}

bArmature *ArmatureComponent::get_for_write()
{
  BLI_assert(this->is_mutable());
  if (ownership_ == GeometryOwnershipType::ReadOnly) {
    volume_ = BKE_volume_copy_for_eval(volume_, false);
    ownership_ = GeometryOwnershipType::Owned;
  }
  return volume_;
}*/

bool ArmatureComponent::owns_direct_data() const
{
  return ownership_ == GeometryOwnershipType::Owned;
}

void ArmatureComponent::ensure_owns_direct_data()
{
  BLI_assert(this->is_mutable());
  if (ownership_ != GeometryOwnershipType::Owned) {
    //volume_ = BKE_volume_copy_for_eval(volume_, false);
    ownership_ = GeometryOwnershipType::Owned;
  }
}

/** \} */
