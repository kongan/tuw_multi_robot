#ifndef CONTROLLER_H
#define CONTROLLER_H

// ROS
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>

namespace velocity_controller
{
typedef struct Point_t
{
  float x = 0;
  float y = 0;
  float theta = 0;
} PathPoint;

typedef enum state_t
{
  run,
  stop,
  step,
  wait_step
} state;

class Controller
{

public:
  /**
   * @brief Construct a new Controller object
   * 
   */
  Controller();
  /**
   * @brief Set the path the contorler has to follow
   * 
   * @param _path the path as std::vector of points
   */
  void setPath(std::shared_ptr<std::vector<PathPoint>> _path);
  /**
   * @brief updates the controller with the current robot position
   * 
   * @param _odom  the current robot position 
   * @param _delta_t the time differenz used for the pid controlelr
   */
  void update(PathPoint _odom, float _delta_t);
  /**
   * @brief Set the Speed Params of the controller
   * 
   * @param _max_v maximal linear speed   
   * @param _max_w maximal rotational speed
   */
  void setSpeedParams(float _max_v, float _max_w);
  /**
   * @brief Returns the current speed values
   * 
   * @param _v the linear speed
   * @param _w the rotational speed
   */
  void getSpeed(float *_v, float *_w);
  /**
   * @brief Set the Goal Radius 
   * 
   * @param _r the radius which is used to marke a goal as visited
   */
  void setGoalRadius(float _r);
  /**
   * @brief sets the control parameters
   * 
   * @param _Kp the proportional part of the controller
   * @param _Ki the integration part of the controller
   * @param _Kd the differential part
   */
  void setPID(float _Kp, float _Ki, float _Kd);
  /**
   * @brief Set the State (run stop step wait_step)
   * 
   * @param s the state (run stop wait_step step)
   */
  void setState(state s);

private:
  float normalizeAngle(float _angle);
  float absolute(float _val);
  bool checkGoal(PathPoint _odom);
  std::shared_ptr<std::vector<PathPoint>> path_;
  float max_v_, max_w_;
  float v_, w_;
  std::vector<PathPoint>::iterator path_iterator_;
  bool plan_active = false;
  float e_last_ = 0;
  float e_dot_ = 0;
  float Kp_ = 5;
  float Kd_ = 1;
  float Ki_ = 0.0;
  float goal_radius_ = 0.25;

  state actual_cmd_ = run;
  
protected:   
  PathPoint current_pose_;
};

} // namespace velocity_controller

#endif // CONTROLLER_NODE_H
