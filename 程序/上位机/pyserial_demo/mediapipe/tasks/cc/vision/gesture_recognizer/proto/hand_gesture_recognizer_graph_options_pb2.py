# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: mediapipe/tasks/cc/vision/gesture_recognizer/proto/hand_gesture_recognizer_graph_options.proto

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
from mediapipe.tasks.cc.core.proto import base_options_pb2 as mediapipe_dot_tasks_dot_cc_dot_core_dot_proto_dot_base__options__pb2
from mediapipe.tasks.cc.vision.gesture_recognizer.proto import gesture_classifier_graph_options_pb2 as mediapipe_dot_tasks_dot_cc_dot_vision_dot_gesture__recognizer_dot_proto_dot_gesture__classifier__graph__options__pb2
from mediapipe.tasks.cc.vision.gesture_recognizer.proto import gesture_embedder_graph_options_pb2 as mediapipe_dot_tasks_dot_cc_dot_vision_dot_gesture__recognizer_dot_proto_dot_gesture__embedder__graph__options__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='mediapipe/tasks/cc/vision/gesture_recognizer/proto/hand_gesture_recognizer_graph_options.proto',
  package='mediapipe.tasks.vision.gesture_recognizer.proto',
  syntax='proto2',
  serialized_pb=_b('\n^mediapipe/tasks/cc/vision/gesture_recognizer/proto/hand_gesture_recognizer_graph_options.proto\x12/mediapipe.tasks.vision.gesture_recognizer.proto\x1a$mediapipe/framework/calculator.proto\x1a\x30mediapipe/tasks/cc/core/proto/base_options.proto\x1aYmediapipe/tasks/cc/vision/gesture_recognizer/proto/gesture_classifier_graph_options.proto\x1aWmediapipe/tasks/cc/vision/gesture_recognizer/proto/gesture_embedder_graph_options.proto\"\xde\x04\n!HandGestureRecognizerGraphOptions\x12=\n\x0c\x62\x61se_options\x18\x01 \x01(\x0b\x32\'.mediapipe.tasks.core.proto.BaseOptions\x12t\n\x1egesture_embedder_graph_options\x18\x02 \x01(\x0b\x32L.mediapipe.tasks.vision.gesture_recognizer.proto.GestureEmbedderGraphOptions\x12\x7f\n\'canned_gesture_classifier_graph_options\x18\x03 \x01(\x0b\x32N.mediapipe.tasks.vision.gesture_recognizer.proto.GestureClassifierGraphOptions\x12\x7f\n\'custom_gesture_classifier_graph_options\x18\x04 \x01(\x0b\x32N.mediapipe.tasks.vision.gesture_recognizer.proto.GestureClassifierGraphOptions2\x81\x01\n\x03\x65xt\x12\x1c.mediapipe.CalculatorOptions\x18\xd4\xf1\xf9\xdc\x01 \x01(\x0b\x32R.mediapipe.tasks.vision.gesture_recognizer.proto.HandGestureRecognizerGraphOptionsBc\n9com.google.mediapipe.tasks.vision.gesturerecognizer.protoB&HandGestureRecognizerGraphOptionsProto')
  ,
  dependencies=[mediapipe_dot_framework_dot_calculator__pb2.DESCRIPTOR,mediapipe_dot_tasks_dot_cc_dot_core_dot_proto_dot_base__options__pb2.DESCRIPTOR,mediapipe_dot_tasks_dot_cc_dot_vision_dot_gesture__recognizer_dot_proto_dot_gesture__classifier__graph__options__pb2.DESCRIPTOR,mediapipe_dot_tasks_dot_cc_dot_vision_dot_gesture__recognizer_dot_proto_dot_gesture__embedder__graph__options__pb2.DESCRIPTOR,])
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_HANDGESTURERECOGNIZERGRAPHOPTIONS = _descriptor.Descriptor(
  name='HandGestureRecognizerGraphOptions',
  full_name='mediapipe.tasks.vision.gesture_recognizer.proto.HandGestureRecognizerGraphOptions',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='base_options', full_name='mediapipe.tasks.vision.gesture_recognizer.proto.HandGestureRecognizerGraphOptions.base_options', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='gesture_embedder_graph_options', full_name='mediapipe.tasks.vision.gesture_recognizer.proto.HandGestureRecognizerGraphOptions.gesture_embedder_graph_options', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='canned_gesture_classifier_graph_options', full_name='mediapipe.tasks.vision.gesture_recognizer.proto.HandGestureRecognizerGraphOptions.canned_gesture_classifier_graph_options', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='custom_gesture_classifier_graph_options', full_name='mediapipe.tasks.vision.gesture_recognizer.proto.HandGestureRecognizerGraphOptions.custom_gesture_classifier_graph_options', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
    _descriptor.FieldDescriptor(
      name='ext', full_name='mediapipe.tasks.vision.gesture_recognizer.proto.HandGestureRecognizerGraphOptions.ext', index=0,
      number=463370452, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=True, extension_scope=None,
      options=None),
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=416,
  serialized_end=1022,
)

_HANDGESTURERECOGNIZERGRAPHOPTIONS.fields_by_name['base_options'].message_type = mediapipe_dot_tasks_dot_cc_dot_core_dot_proto_dot_base__options__pb2._BASEOPTIONS
_HANDGESTURERECOGNIZERGRAPHOPTIONS.fields_by_name['gesture_embedder_graph_options'].message_type = mediapipe_dot_tasks_dot_cc_dot_vision_dot_gesture__recognizer_dot_proto_dot_gesture__embedder__graph__options__pb2._GESTUREEMBEDDERGRAPHOPTIONS
_HANDGESTURERECOGNIZERGRAPHOPTIONS.fields_by_name['canned_gesture_classifier_graph_options'].message_type = mediapipe_dot_tasks_dot_cc_dot_vision_dot_gesture__recognizer_dot_proto_dot_gesture__classifier__graph__options__pb2._GESTURECLASSIFIERGRAPHOPTIONS
_HANDGESTURERECOGNIZERGRAPHOPTIONS.fields_by_name['custom_gesture_classifier_graph_options'].message_type = mediapipe_dot_tasks_dot_cc_dot_vision_dot_gesture__recognizer_dot_proto_dot_gesture__classifier__graph__options__pb2._GESTURECLASSIFIERGRAPHOPTIONS
DESCRIPTOR.message_types_by_name['HandGestureRecognizerGraphOptions'] = _HANDGESTURERECOGNIZERGRAPHOPTIONS

HandGestureRecognizerGraphOptions = _reflection.GeneratedProtocolMessageType('HandGestureRecognizerGraphOptions', (_message.Message,), dict(
  DESCRIPTOR = _HANDGESTURERECOGNIZERGRAPHOPTIONS,
  __module__ = 'mediapipe.tasks.cc.vision.gesture_recognizer.proto.hand_gesture_recognizer_graph_options_pb2'
  # @@protoc_insertion_point(class_scope:mediapipe.tasks.vision.gesture_recognizer.proto.HandGestureRecognizerGraphOptions)
  ))
_sym_db.RegisterMessage(HandGestureRecognizerGraphOptions)

_HANDGESTURERECOGNIZERGRAPHOPTIONS.extensions_by_name['ext'].message_type = _HANDGESTURERECOGNIZERGRAPHOPTIONS
mediapipe_dot_framework_dot_calculator__options__pb2.CalculatorOptions.RegisterExtension(_HANDGESTURERECOGNIZERGRAPHOPTIONS.extensions_by_name['ext'])

DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\n9com.google.mediapipe.tasks.vision.gesturerecognizer.protoB&HandGestureRecognizerGraphOptionsProto'))
# @@protoc_insertion_point(module_scope)
