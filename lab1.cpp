#include "ros/ros.h"
#include "gazebo_msgs/SpawnModel.h"
#include "gazebo_msgs/ModelState.h"
#include <fstream>
#include "string.h"
 
using namespace std;
 
int main(int argc, char** argv) {
    ros::init(argc, argv, "gaztest");
    ros::NodeHandle node;
    ros::service::waitForService("gazebo/spawn_sdf_model");
    ros::ServiceClient add_robot = 
             node.serviceClient<gazebo_msgs::SpawnModel>("gazebo/spawn_sdf_model");
    gazebo_msgs::SpawnModel srv;
 
    ifstream fin("/home/natasha/.gazebo/models/pioneer2dx/model.sdf");
 
    string model;
    string buf;
    while(!fin.eof()){
        getline(fin, buf);
        model += buf + "\n";
    }
    srv.request.model_xml = model;
    srv.request.model_name = "robot";
    geometry_msgs::Pose pose;
    srv.request.initial_pose = pose;
    add_robot.call(srv);
    //Spawning finished
 
    ros::Publisher pub = 
            node.advertise<gazebo_msgs::ModelState>("gazebo/set_model_state", 10);
    sleep(1.0);
 
    gazebo_msgs::ModelState msg;
    msg.model_name = "robot";
    msg.pose.position.x = 2.0;
    pub.publish(msg);
    sleep(1.0);
    ros::spinOnce();
    return 0;
}
