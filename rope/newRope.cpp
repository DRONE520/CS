#include "ros/ros.h"
#include "gazebo_msgs/SpawnModel.h"
#include "gazebo_msgs/ModelState.h"
#include <fstream>
#include "string.h"
#include <string> 
#include <sensor_msgs/JointState.h>
#include <fstream>
 
using namespace std;
 
int main(int argc, char** argv) 
{

ros::init(argc, argv, "gaztest");
    ros::NodeHandle node;
    ros::service::waitForService("gazebo/spawn_sdf_model");
    ros::ServiceClient add_robot;
    gazebo_msgs::SpawnModel srv;
    ifstream fin("/home/natasha/cop/workspace/src/lab1/model2.txt");
 
    string model;
    string buf;
    
    add_robot = 
             node.serviceClient<gazebo_msgs::SpawnModel>("gazebo/spawn_sdf_model");

    while(!fin.eof()){
        getline(fin, buf);
        model += buf + "\n";
    }
  
    srv.request.model_xml = model;
    srv.request.model_name = "ball";
    geometry_msgs::Pose pose;
    add_robot.call(srv);      

    return 0;
}
