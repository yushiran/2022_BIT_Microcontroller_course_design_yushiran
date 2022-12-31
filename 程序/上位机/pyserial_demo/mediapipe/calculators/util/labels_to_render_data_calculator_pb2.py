# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: mediapipe/calculators/util/labels_to_render_data_calculator.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from mediapipe.framework import calculator_pb2 as mediapipe_dot_framework_dot_calculator__pb2
mediapipe_dot_framework_dot_calculator__options__pb2 = mediapipe_dot_framework_dot_calculator__pb2.mediapipe_dot_framework_dot_calculator__options__pb2
from mediapipe.util import color_pb2 as mediapipe_dot_util_dot_color__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='mediapipe/calculators/util/labels_to_render_data_calculator.proto',
  package='mediapipe',
  syntax='proto2',
  serialized_pb=_b('\nAmediapipe/calculators/util/labels_to_render_data_calculator.proto\x12\tmediapipe\x1a$mediapipe/framework/calculator.proto\x1a\x1amediapipe/util/color.proto\"\xda\x04\n#LabelsToRenderDataCalculatorOptions\x12\x1f\n\x05\x63olor\x18\x01 \x03(\x0b\x32\x10.mediapipe.Color\x12\x14\n\tthickness\x18\x02 \x01(\x01:\x01\x32\x12\'\n\routline_color\x18\x0c \x03(\x0b\x32\x10.mediapipe.Color\x12\x19\n\x11outline_thickness\x18\x0b \x01(\x01\x12\x1a\n\x0e\x66ont_height_px\x18\x03 \x01(\x05:\x02\x35\x30\x12\x1f\n\x14horizontal_offset_px\x18\x07 \x01(\x05:\x01\x30\x12\x1d\n\x12vertical_offset_px\x18\x08 \x01(\x05:\x01\x30\x12\x19\n\x0emax_num_labels\x18\x04 \x01(\x05:\x01\x31\x12\x14\n\tfont_face\x18\x05 \x01(\x05:\x01\x30\x12S\n\x08location\x18\x06 \x01(\x0e\x32\x37.mediapipe.LabelsToRenderDataCalculatorOptions.Location:\x08TOP_LEFT\x12\x1f\n\x10use_display_name\x18\t \x01(\x08:\x05\x66\x61lse\x12+\n\x1c\x64isplay_classification_score\x18\n \x01(\x08:\x05\x66\x61lse\")\n\x08Location\x12\x0c\n\x08TOP_LEFT\x10\x00\x12\x0f\n\x0b\x42OTTOM_LEFT\x10\x01\x32]\n\x03\x65xt\x12\x1c.mediapipe.CalculatorOptions\x18\xcc\xea\xc4\x81\x01 \x01(\x0b\x32..mediapipe.LabelsToRenderDataCalculatorOptions')
  ,
  dependencies=[mediapipe_dot_framework_dot_calculator__pb2.DESCRIPTOR,mediapipe_dot_util_dot_color__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_LABELSTORENDERDATACALCULATOROPTIONS_LOCATION = _descriptor.EnumDescriptor(
  name='Location',
  full_name='mediapipe.LabelsToRenderDataCalculatorOptions.Location',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='TOP_LEFT', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='BOTTOM_LEFT', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=613,
  serialized_end=654,
)
_sym_db.RegisterEnumDescriptor(_LABELSTORENDERDATACALCULATOROPTIONS_LOCATION)


_LABELSTORENDERDATACALCULATOROPTIONS = _descriptor.Descriptor(
  name='LabelsToRenderDataCalculatorOptions',
  full_name='mediapipe.LabelsToRenderDataCalculatorOptions',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='color', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.color', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='thickness', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.thickness', index=1,
      number=2, type=1, cpp_type=5, label=1,
      has_default_value=True, default_value=float(2),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='outline_color', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.outline_color', index=2,
      number=12, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='outline_thickness', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.outline_thickness', index=3,
      number=11, type=1, cpp_type=5, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='font_height_px', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.font_height_px', index=4,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=50,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='horizontal_offset_px', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.horizontal_offset_px', index=5,
      number=7, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='vertical_offset_px', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.vertical_offset_px', index=6,
      number=8, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='max_num_labels', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.max_num_labels', index=7,
      number=4, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=1,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='font_face', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.font_face', index=8,
      number=5, type=5, cpp_type=1, label=1,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='location', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.location', index=9,
      number=6, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='use_display_name', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.use_display_name', index=10,
      number=9, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='display_classification_score', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.display_classification_score', index=11,
      number=10, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
    _descriptor.FieldDescriptor(
      name='ext', full_name='mediapipe.LabelsToRenderDataCalculatorOptions.ext', index=0,
      number=271660364, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=True, extension_scope=None,
      options=None),
  ],
  nested_types=[],
  enum_types=[
    _LABELSTORENDERDATACALCULATOROPTIONS_LOCATION,
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=147,
  serialized_end=749,
)

_LABELSTORENDERDATACALCULATOROPTIONS.fields_by_name['color'].message_type = mediapipe_dot_util_dot_color__pb2._COLOR
_LABELSTORENDERDATACALCULATOROPTIONS.fields_by_name['outline_color'].message_type = mediapipe_dot_util_dot_color__pb2._COLOR
_LABELSTORENDERDATACALCULATOROPTIONS.fields_by_name['location'].enum_type = _LABELSTORENDERDATACALCULATOROPTIONS_LOCATION
_LABELSTORENDERDATACALCULATOROPTIONS_LOCATION.containing_type = _LABELSTORENDERDATACALCULATOROPTIONS
DESCRIPTOR.message_types_by_name['LabelsToRenderDataCalculatorOptions'] = _LABELSTORENDERDATACALCULATOROPTIONS

LabelsToRenderDataCalculatorOptions = _reflection.GeneratedProtocolMessageType('LabelsToRenderDataCalculatorOptions', (_message.Message,), dict(
  DESCRIPTOR = _LABELSTORENDERDATACALCULATOROPTIONS,
  __module__ = 'mediapipe.calculators.util.labels_to_render_data_calculator_pb2'
  # @@protoc_insertion_point(class_scope:mediapipe.LabelsToRenderDataCalculatorOptions)
  ))
_sym_db.RegisterMessage(LabelsToRenderDataCalculatorOptions)

_LABELSTORENDERDATACALCULATOROPTIONS.extensions_by_name['ext'].message_type = _LABELSTORENDERDATACALCULATOROPTIONS
mediapipe_dot_framework_dot_calculator__options__pb2.CalculatorOptions.RegisterExtension(_LABELSTORENDERDATACALCULATOROPTIONS.extensions_by_name['ext'])

# @@protoc_insertion_point(module_scope)
