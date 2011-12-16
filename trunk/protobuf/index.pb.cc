// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "index.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* index_msg_t_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  index_msg_t_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_index_2eproto() {
  protobuf_AddDesc_index_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "index.proto");
  GOOGLE_CHECK(file != NULL);
  index_msg_t_descriptor_ = file->message_type(0);
  static const int index_msg_t_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(index_msg_t, magic_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(index_msg_t, flag_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(index_msg_t, key_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(index_msg_t, offset_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(index_msg_t, size_),
  };
  index_msg_t_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      index_msg_t_descriptor_,
      index_msg_t::default_instance_,
      index_msg_t_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(index_msg_t, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(index_msg_t, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(index_msg_t));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_index_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    index_msg_t_descriptor_, &index_msg_t::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_index_2eproto() {
  delete index_msg_t::default_instance_;
  delete index_msg_t_reflection_;
}

void protobuf_AddDesc_index_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013index.proto\"U\n\013index_msg_t\022\r\n\005magic\030\001 "
    "\002(\005\022\014\n\004flag\030\002 \002(\005\022\013\n\003key\030\003 \002(\003\022\016\n\006offset"
    "\030\004 \002(\004\022\014\n\004size\030\005 \002(\004", 100);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "index.proto", &protobuf_RegisterTypes);
  index_msg_t::default_instance_ = new index_msg_t();
  index_msg_t::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_index_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_index_2eproto {
  StaticDescriptorInitializer_index_2eproto() {
    protobuf_AddDesc_index_2eproto();
  }
} static_descriptor_initializer_index_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int index_msg_t::kMagicFieldNumber;
const int index_msg_t::kFlagFieldNumber;
const int index_msg_t::kKeyFieldNumber;
const int index_msg_t::kOffsetFieldNumber;
const int index_msg_t::kSizeFieldNumber;
#endif  // !_MSC_VER

index_msg_t::index_msg_t()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void index_msg_t::InitAsDefaultInstance() {
}

index_msg_t::index_msg_t(const index_msg_t& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void index_msg_t::SharedCtor() {
  _cached_size_ = 0;
  magic_ = 0;
  flag_ = 0;
  key_ = GOOGLE_LONGLONG(0);
  offset_ = GOOGLE_ULONGLONG(0);
  size_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

index_msg_t::~index_msg_t() {
  SharedDtor();
}

void index_msg_t::SharedDtor() {
  if (this != default_instance_) {
  }
}

void index_msg_t::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* index_msg_t::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return index_msg_t_descriptor_;
}

const index_msg_t& index_msg_t::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_index_2eproto();  return *default_instance_;
}

index_msg_t* index_msg_t::default_instance_ = NULL;

index_msg_t* index_msg_t::New() const {
  return new index_msg_t;
}

void index_msg_t::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    magic_ = 0;
    flag_ = 0;
    key_ = GOOGLE_LONGLONG(0);
    offset_ = GOOGLE_ULONGLONG(0);
    size_ = GOOGLE_ULONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool index_msg_t::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 magic = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &magic_)));
          set_has_magic();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_flag;
        break;
      }
      
      // required int32 flag = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_flag:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &flag_)));
          set_has_flag();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_key;
        break;
      }
      
      // required int64 key = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_key:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &key_)));
          set_has_key();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(32)) goto parse_offset;
        break;
      }
      
      // required uint64 offset = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_offset:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &offset_)));
          set_has_offset();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(40)) goto parse_size;
        break;
      }
      
      // required uint64 size = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &size_)));
          set_has_size();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void index_msg_t::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 magic = 1;
  if (has_magic()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->magic(), output);
  }
  
  // required int32 flag = 2;
  if (has_flag()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->flag(), output);
  }
  
  // required int64 key = 3;
  if (has_key()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->key(), output);
  }
  
  // required uint64 offset = 4;
  if (has_offset()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(4, this->offset(), output);
  }
  
  // required uint64 size = 5;
  if (has_size()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(5, this->size(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* index_msg_t::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 magic = 1;
  if (has_magic()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->magic(), target);
  }
  
  // required int32 flag = 2;
  if (has_flag()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->flag(), target);
  }
  
  // required int64 key = 3;
  if (has_key()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->key(), target);
  }
  
  // required uint64 offset = 4;
  if (has_offset()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(4, this->offset(), target);
  }
  
  // required uint64 size = 5;
  if (has_size()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(5, this->size(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int index_msg_t::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 magic = 1;
    if (has_magic()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->magic());
    }
    
    // required int32 flag = 2;
    if (has_flag()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->flag());
    }
    
    // required int64 key = 3;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->key());
    }
    
    // required uint64 offset = 4;
    if (has_offset()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->offset());
    }
    
    // required uint64 size = 5;
    if (has_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->size());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void index_msg_t::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const index_msg_t* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const index_msg_t*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void index_msg_t::MergeFrom(const index_msg_t& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_magic()) {
      set_magic(from.magic());
    }
    if (from.has_flag()) {
      set_flag(from.flag());
    }
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_offset()) {
      set_offset(from.offset());
    }
    if (from.has_size()) {
      set_size(from.size());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void index_msg_t::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void index_msg_t::CopyFrom(const index_msg_t& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool index_msg_t::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000001f) != 0x0000001f) return false;
  
  return true;
}

void index_msg_t::Swap(index_msg_t* other) {
  if (other != this) {
    std::swap(magic_, other->magic_);
    std::swap(flag_, other->flag_);
    std::swap(key_, other->key_);
    std::swap(offset_, other->offset_);
    std::swap(size_, other->size_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata index_msg_t::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = index_msg_t_descriptor_;
  metadata.reflection = index_msg_t_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
