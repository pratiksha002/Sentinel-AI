# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sentinel_swarm:msg/DroneState.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DroneState(type):
    """Metaclass of message 'DroneState'."""

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
                'sentinel_swarm.msg.DroneState')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__drone_state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__drone_state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__drone_state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__drone_state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__drone_state

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


class DroneState(metaclass=Metaclass_DroneState):
    """Message class 'DroneState'."""

    __slots__ = [
        '_drone_id',
        '_position',
        '_velocity',
        '_battery_voltage',
        '_battery_current',
        '_battery_percentage',
        '_is_armed',
        '_is_healthy',
        '_flight_mode',
        '_gps_hdop',
        '_connected_satellites',
    ]

    _fields_and_field_types = {
        'drone_id': 'int32',
        'position': 'geometry_msgs/Point',
        'velocity': 'geometry_msgs/Vector3',
        'battery_voltage': 'float',
        'battery_current': 'float',
        'battery_percentage': 'float',
        'is_armed': 'boolean',
        'is_healthy': 'boolean',
        'flight_mode': 'string',
        'gps_hdop': 'float',
        'connected_satellites': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.drone_id = kwargs.get('drone_id', int())
        from geometry_msgs.msg import Point
        self.position = kwargs.get('position', Point())
        from geometry_msgs.msg import Vector3
        self.velocity = kwargs.get('velocity', Vector3())
        self.battery_voltage = kwargs.get('battery_voltage', float())
        self.battery_current = kwargs.get('battery_current', float())
        self.battery_percentage = kwargs.get('battery_percentage', float())
        self.is_armed = kwargs.get('is_armed', bool())
        self.is_healthy = kwargs.get('is_healthy', bool())
        self.flight_mode = kwargs.get('flight_mode', str())
        self.gps_hdop = kwargs.get('gps_hdop', float())
        self.connected_satellites = kwargs.get('connected_satellites', int())

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
        if self.drone_id != other.drone_id:
            return False
        if self.position != other.position:
            return False
        if self.velocity != other.velocity:
            return False
        if self.battery_voltage != other.battery_voltage:
            return False
        if self.battery_current != other.battery_current:
            return False
        if self.battery_percentage != other.battery_percentage:
            return False
        if self.is_armed != other.is_armed:
            return False
        if self.is_healthy != other.is_healthy:
            return False
        if self.flight_mode != other.flight_mode:
            return False
        if self.gps_hdop != other.gps_hdop:
            return False
        if self.connected_satellites != other.connected_satellites:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def drone_id(self):
        """Message field 'drone_id'."""
        return self._drone_id

    @drone_id.setter
    def drone_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'drone_id' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'drone_id' field must be an integer in [-2147483648, 2147483647]"
        self._drone_id = value

    @builtins.property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'position' field must be a sub message of type 'Point'"
        self._position = value

    @builtins.property
    def velocity(self):
        """Message field 'velocity'."""
        return self._velocity

    @velocity.setter
    def velocity(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'velocity' field must be a sub message of type 'Vector3'"
        self._velocity = value

    @builtins.property
    def battery_voltage(self):
        """Message field 'battery_voltage'."""
        return self._battery_voltage

    @battery_voltage.setter
    def battery_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_voltage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'battery_voltage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._battery_voltage = value

    @builtins.property
    def battery_current(self):
        """Message field 'battery_current'."""
        return self._battery_current

    @battery_current.setter
    def battery_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_current' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'battery_current' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._battery_current = value

    @builtins.property
    def battery_percentage(self):
        """Message field 'battery_percentage'."""
        return self._battery_percentage

    @battery_percentage.setter
    def battery_percentage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'battery_percentage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'battery_percentage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._battery_percentage = value

    @builtins.property
    def is_armed(self):
        """Message field 'is_armed'."""
        return self._is_armed

    @is_armed.setter
    def is_armed(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_armed' field must be of type 'bool'"
        self._is_armed = value

    @builtins.property
    def is_healthy(self):
        """Message field 'is_healthy'."""
        return self._is_healthy

    @is_healthy.setter
    def is_healthy(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_healthy' field must be of type 'bool'"
        self._is_healthy = value

    @builtins.property
    def flight_mode(self):
        """Message field 'flight_mode'."""
        return self._flight_mode

    @flight_mode.setter
    def flight_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'flight_mode' field must be of type 'str'"
        self._flight_mode = value

    @builtins.property
    def gps_hdop(self):
        """Message field 'gps_hdop'."""
        return self._gps_hdop

    @gps_hdop.setter
    def gps_hdop(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'gps_hdop' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'gps_hdop' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._gps_hdop = value

    @builtins.property
    def connected_satellites(self):
        """Message field 'connected_satellites'."""
        return self._connected_satellites

    @connected_satellites.setter
    def connected_satellites(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'connected_satellites' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'connected_satellites' field must be an integer in [-2147483648, 2147483647]"
        self._connected_satellites = value
