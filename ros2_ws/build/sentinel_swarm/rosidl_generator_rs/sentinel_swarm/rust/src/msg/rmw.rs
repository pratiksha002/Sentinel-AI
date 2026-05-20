#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "sentinel_swarm__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__sentinel_swarm__msg__DroneState() -> *const std::ffi::c_void;
}

#[link(name = "sentinel_swarm__rosidl_generator_c")]
extern "C" {
    fn sentinel_swarm__msg__DroneState__init(msg: *mut DroneState) -> bool;
    fn sentinel_swarm__msg__DroneState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DroneState>, size: usize) -> bool;
    fn sentinel_swarm__msg__DroneState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DroneState>);
    fn sentinel_swarm__msg__DroneState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DroneState>, out_seq: *mut rosidl_runtime_rs::Sequence<DroneState>) -> bool;
}

// Corresponds to sentinel_swarm__msg__DroneState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// DroneState.msg - Published by each drone controller

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DroneState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub drone_id: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: geometry_msgs::msg::rmw::Point,


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity: geometry_msgs::msg::rmw::Vector3,


    // This member is not documented.
    #[allow(missing_docs)]
    pub battery_voltage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub battery_current: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub battery_percentage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_armed: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_healthy: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub flight_mode: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gps_hdop: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub connected_satellites: i32,

}



impl Default for DroneState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !sentinel_swarm__msg__DroneState__init(&mut msg as *mut _) {
        panic!("Call to sentinel_swarm__msg__DroneState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DroneState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__DroneState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__DroneState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__DroneState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DroneState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DroneState where Self: Sized {
  const TYPE_NAME: &'static str = "sentinel_swarm/msg/DroneState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__sentinel_swarm__msg__DroneState() }
  }
}


#[link(name = "sentinel_swarm__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__sentinel_swarm__msg__SwarmCommand() -> *const std::ffi::c_void;
}

#[link(name = "sentinel_swarm__rosidl_generator_c")]
extern "C" {
    fn sentinel_swarm__msg__SwarmCommand__init(msg: *mut SwarmCommand) -> bool;
    fn sentinel_swarm__msg__SwarmCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SwarmCommand>, size: usize) -> bool;
    fn sentinel_swarm__msg__SwarmCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SwarmCommand>);
    fn sentinel_swarm__msg__SwarmCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SwarmCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<SwarmCommand>) -> bool;
}

// Corresponds to sentinel_swarm__msg__SwarmCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// SwarmCommand.msg - Published by mission planner to coordinator

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SwarmCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub command_id: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub command_type: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub target_point: geometry_msgs::msg::rmw::Point,


    // This member is not documented.
    #[allow(missing_docs)]
    pub formation_type: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub formation_scale: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_timeout: f32,

}



impl Default for SwarmCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !sentinel_swarm__msg__SwarmCommand__init(&mut msg as *mut _) {
        panic!("Call to sentinel_swarm__msg__SwarmCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SwarmCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__SwarmCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__SwarmCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__SwarmCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SwarmCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SwarmCommand where Self: Sized {
  const TYPE_NAME: &'static str = "sentinel_swarm/msg/SwarmCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__sentinel_swarm__msg__SwarmCommand() }
  }
}


#[link(name = "sentinel_swarm__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__sentinel_swarm__msg__FormationReference() -> *const std::ffi::c_void;
}

#[link(name = "sentinel_swarm__rosidl_generator_c")]
extern "C" {
    fn sentinel_swarm__msg__FormationReference__init(msg: *mut FormationReference) -> bool;
    fn sentinel_swarm__msg__FormationReference__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<FormationReference>, size: usize) -> bool;
    fn sentinel_swarm__msg__FormationReference__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<FormationReference>);
    fn sentinel_swarm__msg__FormationReference__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<FormationReference>, out_seq: *mut rosidl_runtime_rs::Sequence<FormationReference>) -> bool;
}

// Corresponds to sentinel_swarm__msg__FormationReference
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// FormationReference.msg - Published by coordinator

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FormationReference {

    // This member is not documented.
    #[allow(missing_docs)]
    pub drone_ids: rosidl_runtime_rs::Sequence<i32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reference_positions: rosidl_runtime_rs::Sequence<geometry_msgs::msg::rmw::Point>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reference_velocities: rosidl_runtime_rs::Sequence<geometry_msgs::msg::rmw::Vector3>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub formation_error: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_formation_valid: bool,

}



impl Default for FormationReference {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !sentinel_swarm__msg__FormationReference__init(&mut msg as *mut _) {
        panic!("Call to sentinel_swarm__msg__FormationReference__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for FormationReference {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__FormationReference__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__FormationReference__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { sentinel_swarm__msg__FormationReference__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for FormationReference {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for FormationReference where Self: Sized {
  const TYPE_NAME: &'static str = "sentinel_swarm/msg/FormationReference";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__sentinel_swarm__msg__FormationReference() }
  }
}


