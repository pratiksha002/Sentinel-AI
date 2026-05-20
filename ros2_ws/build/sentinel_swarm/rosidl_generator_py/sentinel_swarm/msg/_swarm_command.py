# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sentinel_swarm:msg/SwarmCommand.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SwarmCommand(type):
    """Metaclass of message 'SwarmCommand'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('sentinel_swarm')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'sentinel_swarm.msg.SwarmCommand')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__swarm_command
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__swarm_command
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__swarm_command
            cls._TYPE_SUPPORT = module.type_support_msg__msg__swarm_command
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__swarm_command

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SwarmCommand(metaclass=Metaclass_SwarmCommand):
    """Message class 'SwarmCommand'."""

    __slots__ = [
        '_command_id',
        '_command_type',
        '_target_point',
        '_formation_type',
        '_formation_scale',
        '_mission_timeout',
    ]

    _fields_and_field_types = {
        'command_id': 'int32',
        'command_type': 'string',
        'target_point': 'geometry_msgs/Point',
        'formation_type': 'string',
        'formation_scale': 'float',
        'mission_timeout': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.command_id = kwargs.get('command_id', int())
        self.command_type = kwargs.get('command_type', str())
        from geometry_msgs.msg import Point
        self.target_point = kwargs.get('target_point', Point())
        self.formation_type = kwargs.get('formation_type', str())
        self.formation_scale = kwargs.get('formation_scale', float())
        self.mission_timeout = kwargs.get('mission_timeout', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.command_id != other.command_id:
            return False
        if self.command_type != other.command_type:
            return False
        if self.target_point != other.target_point:
            return False
        if self.formation_type != other.formation_type:
            return False
        if self.formation_scale != other.formation_scale:
            return False
        if self.mission_timeout != other.mission_timeout:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def command_id(self):
        """Message field 'command_id'."""
        return self._command_id

    @command_id.setter
    def command_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'command_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'command_id' field must be an integer in [-2147483648, 2147483647]"
        self._command_id = value

    @builtins.property
    def command_type(self):
        """Message field 'command_type'."""
        return self._command_type

    @command_type.setter
    def command_type(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'command_type' field must be of type 'str'"
        self._command_type = value

    @builtins.property
    def target_point(self):
        """Message field 'target_point'."""
        return self._target_point

    @target_point.setter
    def target_point(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'target_point' field must be a sub message of type 'Point'"
        self._target_point = value

    @builtins.property
    def formation_type(self):
        """Message field 'formation_type'."""
        return self._formation_type

    @formation_type.setter
    def formation_type(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'formation_type' field must be of type 'str'"
        self._formation_type = value

    @builtins.property
    def formation_scale(self):
        """Message field 'formation_scale'."""
        return self._formation_scale

    @formation_scale.setter
    def formation_scale(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'formation_scale' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'formation_scale' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._formation_scale = value

    @builtins.property
    def mission_timeout(self):
        """Message field 'mission_timeout'."""
        return self._mission_timeout

    @mission_timeout.setter
    def mission_timeout(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mission_timeout' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mission_timeout' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mission_timeout = value
