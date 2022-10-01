#!/usr/bin/env python
from __future__ import division

import rospy
import smach
import smach_ros
from geometry_msgs.msg import Pose, Point, Quaternion
from std_msgs.msg import Float64
from tasks.task import Task, Objective

class squareSm(Task):
    name = "Square"

    def __init__(self):
        super(squareSm, self).__init__(self.name)
        self.init_objectives()
        self.link_objectives()

    def init_objectives(self):
        self.square = square(self.name) ## ????????

    def link_objectives(self):
        with self: #we are state machine?
            smach.StateMachine.add('Pre', self.square, transitions={'done':'manager'}, \
                remapping={'timout_obj':'timout_obj', 'outcome':'outcome'})

class square(Objective):
    outcomes=['done']

    def __init__(self, task_name):
        name = task_name +"/Square"
        super(square, self).__init__(self.outcomes, name)

    def execute(self, userdata):

        point1 = Point(-14.18, -1.45, -2)
        quaternion1 = Quaternion(2,2,2,2)
        pose1 = Pose()
        pose1.position = point1
        pose1.orientation=quaternion1
        self.toggle_waypoint_control(False)
        self.go_to_pose(pose1,userdata.timeout_obj)
        self.cuprint("reach 1")

        point2 = Point(-14.15,3.68,-2)
        quaternion2 = Quaternion(2,2,2,2)
        pose2 = Pose()
        pose2.position = point2
        pose2.orientation = quaternion2

        self.go_to_pose(pose2, userdata.timeout_obj)
        self.cuprint("reach 2")

        point3 = Point(-14.18, -1.45, -4)
        quaternion3 = Quaternion(2,2,2,2)
        pose3 = Pose()
        pose3.position = point3
        pose3.orientation=quaternion1
        self.toggle_waypoint_control(False)
        self.go_to_pose(pose3,userdata.timeout_obj)
        self.cuprint("reach 3")

        point4 = Point(-10, -2.3, -2)
        quaternion1 = Quaternion(2,2,2,2)
        pose4 = Pose()
        pose4.position = point1
        pose4.orientation=quaternion1
        self.toggle_waypoint_control(False)
        self.go_to_pose(pose4,userdata.timeout_obj)
        self.cuprint("reach 4")

        userdata.outcome = "success"
        return "done"