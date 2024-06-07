// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: vehicletelemetry.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_vehicletelemetry_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_vehicletelemetry_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include "common.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_vehicletelemetry_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_vehicletelemetry_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
namespace com {
namespace bosch {
namespace itrams_gen2e {
class TelemetryPayload;
class TelemetryPayloadDefaultTypeInternal;
extern TelemetryPayloadDefaultTypeInternal _TelemetryPayload_default_instance_;
}  // namespace itrams_gen2e
}  // namespace bosch
}  // namespace com
PROTOBUF_NAMESPACE_OPEN
template<> ::com::bosch::itrams_gen2e::TelemetryPayload* Arena::CreateMaybeMessage<::com::bosch::itrams_gen2e::TelemetryPayload>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace com {
namespace bosch {
namespace itrams_gen2e {

// ===================================================================

class TelemetryPayload PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::MessageLite /* @@protoc_insertion_point(class_definition:com.bosch.itrams_gen2e.TelemetryPayload) */ {
 public:
  inline TelemetryPayload() : TelemetryPayload(nullptr) {};
  virtual ~TelemetryPayload();

  TelemetryPayload(const TelemetryPayload& from);
  TelemetryPayload(TelemetryPayload&& from) noexcept
    : TelemetryPayload() {
    *this = ::std::move(from);
  }

  inline TelemetryPayload& operator=(const TelemetryPayload& from) {
    CopyFrom(from);
    return *this;
  }
  inline TelemetryPayload& operator=(TelemetryPayload&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const TelemetryPayload& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const TelemetryPayload* internal_default_instance() {
    return reinterpret_cast<const TelemetryPayload*>(
               &_TelemetryPayload_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(TelemetryPayload& a, TelemetryPayload& b) {
    a.Swap(&b);
  }
  inline void Swap(TelemetryPayload* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TelemetryPayload* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline TelemetryPayload* New() const final {
    return CreateMaybeMessage<TelemetryPayload>(nullptr);
  }

  TelemetryPayload* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<TelemetryPayload>(arena);
  }
  void CheckTypeAndMergeFrom(const ::PROTOBUF_NAMESPACE_ID::MessageLite& from)
    final;
  void CopyFrom(const TelemetryPayload& from);
  void MergeFrom(const TelemetryPayload& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  void DiscardUnknownFields();
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(TelemetryPayload* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "com.bosch.itrams_gen2e.TelemetryPayload";
  }
  protected:
  explicit TelemetryPayload(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMeasuresFieldNumber = 1,
  };
  // repeated .com.bosch.itrams_gen2e.TelemetryReading measures = 1[json_name = "measures"];
  int measures_size() const;
  private:
  int _internal_measures_size() const;
  public:
  void clear_measures();
  ::com::bosch::itrams_gen2e::TelemetryReading* mutable_measures(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::bosch::itrams_gen2e::TelemetryReading >*
      mutable_measures();
  private:
  const ::com::bosch::itrams_gen2e::TelemetryReading& _internal_measures(int index) const;
  ::com::bosch::itrams_gen2e::TelemetryReading* _internal_add_measures();
  public:
  const ::com::bosch::itrams_gen2e::TelemetryReading& measures(int index) const;
  ::com::bosch::itrams_gen2e::TelemetryReading* add_measures();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::bosch::itrams_gen2e::TelemetryReading >&
      measures() const;

  // @@protoc_insertion_point(class_scope:com.bosch.itrams_gen2e.TelemetryPayload)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::bosch::itrams_gen2e::TelemetryReading > measures_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_vehicletelemetry_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TelemetryPayload

// repeated .com.bosch.itrams_gen2e.TelemetryReading measures = 1[json_name = "measures"];
inline int TelemetryPayload::_internal_measures_size() const {
  return measures_.size();
}
inline int TelemetryPayload::measures_size() const {
  return _internal_measures_size();
}
inline ::com::bosch::itrams_gen2e::TelemetryReading* TelemetryPayload::mutable_measures(int index) {
  // @@protoc_insertion_point(field_mutable:com.bosch.itrams_gen2e.TelemetryPayload.measures)
  return measures_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::bosch::itrams_gen2e::TelemetryReading >*
TelemetryPayload::mutable_measures() {
  // @@protoc_insertion_point(field_mutable_list:com.bosch.itrams_gen2e.TelemetryPayload.measures)
  return &measures_;
}
inline const ::com::bosch::itrams_gen2e::TelemetryReading& TelemetryPayload::_internal_measures(int index) const {
  return measures_.Get(index);
}
inline const ::com::bosch::itrams_gen2e::TelemetryReading& TelemetryPayload::measures(int index) const {
  // @@protoc_insertion_point(field_get:com.bosch.itrams_gen2e.TelemetryPayload.measures)
  return _internal_measures(index);
}
inline ::com::bosch::itrams_gen2e::TelemetryReading* TelemetryPayload::_internal_add_measures() {
  return measures_.Add();
}
inline ::com::bosch::itrams_gen2e::TelemetryReading* TelemetryPayload::add_measures() {
  // @@protoc_insertion_point(field_add:com.bosch.itrams_gen2e.TelemetryPayload.measures)
  return _internal_add_measures();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::com::bosch::itrams_gen2e::TelemetryReading >&
TelemetryPayload::measures() const {
  // @@protoc_insertion_point(field_list:com.bosch.itrams_gen2e.TelemetryPayload.measures)
  return measures_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace itrams_gen2e
}  // namespace bosch
}  // namespace com

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_vehicletelemetry_2eproto
