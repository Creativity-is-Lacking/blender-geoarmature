#include "BKE_armature.h"
#include "DNA_armature_types.h"
#include "BKE_attribute.hh"

enum class ArmatureOwnershipType {
  /* The armature is owned. This implies that it can be changed. */
  Owned = 0,
  /* The armature can be changed, but someone else is responsible for freeing it. */
  Editable = 1,
  /* The armature cannot be changed and someone else is responsible for freeing it. */
  ReadOnly = 2,
};

typedef enum ArmatureDataComponentType {
  GEO_COMPONENT_TYPE_ARMATURE = 0,
  GEO_COMPONENT_TYPE_BONE = 1,
} ArmatureDataComponentType;

namespace blender::bke {


    class ArmatureDataComponent {
      private:
      /* The reference count has two purposes. When it becomes zero, the component is freed. When it is
       * larger than one, the component becomes immutable. */
      mutable std::atomic<int> users_ = 1;
      ArmatureDataComponentType type_;

     public:
      ArmatureDataComponent(ArmatureDataComponentType type);
      virtual ~ArmatureDataComponent() = default;
      static ArmatureDataComponent *create(ArmatureDataComponentType component_type);

      int attribute_domain_size(eAttrDomain domain) const;

      /**
       * Get access to the attributes in this geometry component. May return none if the geometry does
       * not support the attribute system.
       */
      virtual std::optional<blender::bke::AttributeAccessor> attributes() const;
      virtual std::optional<blender::bke::MutableAttributeAccessor> attributes_for_write();

      /* The returned component should be of the same type as the type this is called on. */
      virtual ArmatureDataComponent *copy() const = 0;

      /* Direct data is everything except for instances of objects/collections.
       * If this returns true, the geometry set can be cached and is still valid after e.g. modifier
       * evaluation ends. Instances can only be valid as long as the data they instance is valid. */
      virtual bool owns_direct_data() const = 0;
      virtual void ensure_owns_direct_data() = 0;

      void user_add() const;
      void user_remove() const;
      bool is_mutable() const;

      ArmatureDataComponentType type() const;

      virtual bool is_empty() const;
    };

    class ArmatureComponent : public ArmatureDataComponent {
      private:
      bArmature* armature_ = nullptr;
      ArmatureOwnershipType ownership_ = ArmatureOwnershipType::Owned;

     public:
      ArmatureComponent();
      ArmatureComponent(ArmatureComponent &&);
      ~ArmatureComponent();
      ArmatureDataComponent *copy() const override;
      void replace(bArmature *armature, ArmatureOwnershipType ownership);
      bool owns_direct_data() const;
      void ensure_owns_direct_data();

      void clear();
    };

    class ArmatureDataComponent {
      private:
      /* The reference count has two purposes. When it becomes zero, the component is freed. When it is
       * larger than one, the component becomes immutable. */
      mutable std::atomic<int> users_ = 1;
      ArmatureDataComponentType type_;

     public:
      ArmatureDataComponent(ArmatureDataComponentType type);
      virtual ~ArmatureDataComponent() = default;
      static ArmatureDataComponent *create(ArmatureDataComponentType component_type);

      int attribute_domain_size(eAttrDomain domain) const;

      /**
       * Get access to the attributes in this geometry component. May return none if the geometry does
       * not support the attribute system.
       */
      virtual std::optional<blender::bke::AttributeAccessor> attributes() const;
      virtual std::optional<blender::bke::MutableAttributeAccessor> attributes_for_write();

      /* The returned component should be of the same type as the type this is called on. */
      virtual ArmatureDataComponent *copy() const = 0;

      /* Direct data is everything except for instances of objects/collections.
       * If this returns true, the geometry set can be cached and is still valid after e.g. modifier
       * evaluation ends. Instances can only be valid as long as the data they instance is valid. */
      virtual bool owns_direct_data() const = 0;
      virtual void ensure_owns_direct_data() = 0;

      void user_add() const;
      void user_remove() const;
      bool is_mutable() const;

      ArmatureDataComponentType type() const;

      virtual bool is_empty() const;
    };

    class ArmatureComponent : public ArmatureDataComponent {
      private:
      bArmature* armature_ = nullptr;
      ArmatureOwnershipType ownership_ = ArmatureOwnershipType::Owned;

     public:
      ArmatureComponent();
      ArmatureComponent(ArmatureComponent &&);
      ~ArmatureComponent();
      ArmatureDataComponent *copy() const override;
      void replace(bArmature *armature, ArmatureOwnershipType ownership);
      bool owns_direct_data() const;
      void ensure_owns_direct_data();

      void clear();
    };

}