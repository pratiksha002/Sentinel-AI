# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sentinel_swarm:msg/FormationReference.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'drone_ids'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_FormationReference(type):
    """Metaclass of message 'FormationReference'."""

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
                'sentinel_swarm.msg.FormationReference')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__formation_reference
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__formation_reference
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__formation_reference
            cls._TYPE_SUPPORT = module.type_support_msg__msg__formation_reference
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__formation_reference

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class FormationReference(metaclass=Metaclass_FormationReference):
    """Message class 'FormationReference'."""

    __slots__ = [
        '_drone_ids',
        '_reference_positions',
        '_reference_velocities',
        '_formation_error',
        '_is_formation_valid',
    ]

    _fields_and_field_types = {
        'drone_ids': 'sequence<int32>',
        'reference_positions': 'sequence<geometry_msgs/Point>',
        'reference_velocities': 'sequence<geometry_msgs/Vector3>',
        'formation_error': 'float',
        'is_formation_valid': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3')),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.drone_ids = array.array('i', kwargs.get('drone_ids', []))
        self.reference_positions = kwargs.get('reference_positions', [])
        self.reference_velocities = kwargs.get('reference_velocities', [])
        self.formation_error = kwargs.get('formation_error', float())
        self.is_formation_valid = kwargs.get('is_formation_valid', bool())

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
        if self.drone_ids != other.drone_ids:
            return False
        if self.reference_positions != other.reference_positions:
            return False
        if self.reference_velocities != other.reference_velocities:
            return False
        if self.formation_error != other.formation_error:
            return False
        if self.is_formation_valid != other.is_formation_valid:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def drone_ids(self):
        """Message field 'drone_ids'."""
        return self._drone_ids

    @drone_ids.setter
    def drone_ids(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'i', \
                "The 'drone_ids' array.array() must have the type code of 'i'"
            self._drone_ids = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'drone_ids' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._drone_ids = array.array('i', value)

    @builtins.property
    def reference_positions(self):
        """Message field 'reference_positions'."""
        return self._reference_positions

    @reference_positions.setter
    def reference_positions(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, Point) for v in value) and
                 True), \
                "The 'reference_positions' field must be a set or sequence and each value of type 'Point'"
        self._reference_positions = value

    @builtins.property
    def reference_velocities(self):
        """Message field 'reference_velocities'."""
        return self._reference_velocities

    @reference_velocities.setter
    def reference_velocities(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, Vector3) for v in value) and
                 True), \
                "The 'reference_velocities' field must be a set or sequence and each value of type 'Vector3'"
        self._reference_velocities = value

    @builtins.property
    def formation_error(self):
        """Message field 'formation_error'."""
        return self._formation_error

    @formation_error.setter
    def formation_error(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'formation_error' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'formation_error' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._formation_error = value

    @builtins.property
    def is_formation_valid(self):
        """Message field 'is_formation_valid'."""
        return self._is_formation_valid

    @is_formation_valid.setter
    def is_formation_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_formation_valid' field must be of type 'bool'"
        self._is_formation_valid = value
