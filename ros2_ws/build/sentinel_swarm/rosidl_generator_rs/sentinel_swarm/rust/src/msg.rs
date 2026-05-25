#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to sentinel_swarm__msg__DroneState
/// DroneState.msg - Published by each drone controller

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DroneState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub drone_id: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: geometry_msgs::msg::Point,


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity: geometry_msgs::msg::Vector3,


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
    pub flight_mode: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gps_hdop: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub connected_satellites: i32,

}



impl Default for DroneState {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DroneState::default())
  }
}

impl rosidl_runtime_rs::Message for DroneState {
  type RmwMsg = super::msg::rmw::DroneState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        drone_id: msg.drone_id,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.position)).into_owned(),
        velocity: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(msg.velocity)).into_owned(),
        battery_voltage: msg.battery_voltage,
        battery_current: msg.battery_current,
        battery_percentage: msg.battery_percentage,
        is_armed: msg.is_armed,
        is_healthy: msg.is_healthy,
        flight_mode: msg.flight_mode.as_str().into(),
        gps_hdop: msg.gps_hdop,
        connected_satellites: msg.connected_satellites,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      drone_id: msg.drone_id,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.position)).into_owned(),
        velocity: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(&msg.velocity)).into_owned(),
      battery_voltage: msg.battery_voltage,
      battery_current: msg.battery_current,
      battery_percentage: msg.battery_percentage,
      is_armed: msg.is_armed,
      is_healthy: msg.is_healthy,
        flight_mode: msg.flight_mode.as_str().into(),
      gps_hdop: msg.gps_hdop,
      connected_satellites: msg.connected_satellites,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      drone_id: msg.drone_id,
      position: geometry_msgs::msg::Point::from_rmw_message(msg.position),
      velocity: geometry_msgs::msg::Vector3::from_rmw_message(msg.velocity),
      battery_voltage: msg.battery_voltage,
      battery_current: msg.battery_current,
      battery_percentage: msg.battery_percentage,
      is_armed: msg.is_armed,
      is_healthy: msg.is_healthy,
      flight_mode: msg.flight_mode.to_string(),
      gps_hdop: msg.gps_hdop,
      connected_satellites: msg.connected_satellites,
    }
  }
}


// Corresponds to sentinel_swarm__msg__SwarmCommand
/// SwarmCommand.msg - Published by mission planner to coordinator

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SwarmCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub command_id: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub command_type: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub target_point: geometry_msgs::msg::Point,


    // This member is not documented.
    #[allow(missing_docs)]
    pub formation_type: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub formation_scale: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mission_timeout: f32,

}



impl Default for SwarmCommand {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SwarmCommand::default())
  }
}

impl rosidl_runtime_rs::Message for SwarmCommand {
  type RmwMsg = super::msg::rmw::SwarmCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        command_id: msg.command_id,
        command_type: msg.command_type.as_str().into(),
        target_point: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.target_point)).into_owned(),
        formation_type: msg.formation_type.as_str().into(),
        formation_scale: msg.formation_scale,
        mission_timeout: msg.mission_timeout,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      command_id: msg.command_id,
        command_type: msg.command_type.as_str().into(),
        target_point: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.target_point)).into_owned(),
        formation_type: msg.formation_type.as_str().into(),
      formation_scale: msg.formation_scale,
      mission_timeout: msg.mission_timeout,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      command_id: msg.command_id,
      command_type: msg.command_type.to_string(),
      target_point: geometry_msgs::msg::Point::from_rmw_message(msg.target_point),
      formation_type: msg.formation_type.to_string(),
      formation_scale: msg.formation_scale,
      mission_timeout: msg.mission_timeout,
    }
  }
}


// Corresponds to sentinel_swarm__msg__FormationReference
/// FormationReference.msg - Published by coordinator

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FormationReference {

    // This member is not documented.
    #[allow(missing_docs)]
    pub drone_ids: Vec<i32>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reference_positions: Vec<geometry_msgs::msg::Point>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reference_velocities: Vec<geometry_msgs::msg::Vector3>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub formation_error: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_formation_valid: bool,

}



impl Default for FormationReference {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::FormationReference::default())
  }
}

impl rosidl_runtime_rs::Message for FormationReference {
  type RmwMsg = super::msg::rmw::FormationReference;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        drone_ids: msg.drone_ids.into(),
        reference_positions: msg.reference_positions
          .into_iter()
          .map(|elem| geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        reference_velocities: msg.reference_velocities
          .into_iter()
          .map(|elem| geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        formation_error: msg.formation_error,
        is_formation_valid: msg.is_formation_valid,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        drone_ids: msg.drone_ids.as_slice().into(),
        reference_positions: msg.reference_positions
          .iter()
          .map(|elem| geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
        reference_velocities: msg.reference_velocities
          .iter()
          .map(|elem| geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      formation_error: msg.formation_error,
      is_formation_valid: msg.is_formation_valid,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      drone_ids: msg.drone_ids
          .into_iter()
          .collect(),
      reference_positions: msg.reference_positions
          .into_iter()
          .map(geometry_msgs::msg::Point::from_rmw_message)
          .collect(),
      reference_velocities: msg.reference_velocities
          .into_iter()
          .map(geometry_msgs::msg::Vector3::from_rmw_message)
          .collect(),
      formation_error: msg.formation_error,
      is_formation_valid: msg.is_formation_valid,
    }
  }
}


