#include "ros/ros.h"
#include "gazebo_msgs/SpawnModel.h"
#include "gazebo_msgs/ModelState.h"
#include <fstream>
#include "string.h"
#include <string> 

 
using namespace std;
 
int main(int argc, char** argv) 
{
ros::init(argc, argv, "gaztest");
    ros::NodeHandle node;
    ros::service::waitForService("gazebo/spawn_sdf_model");
    ros::ServiceClient add_robot;
    gazebo_msgs::SpawnModel srv;
    ifstream fin("/home/natasha/model_editor_models/ball/model.sdf");
    
    ros::Publisher pub = 
            node.advertise<gazebo_msgs::ModelState>("gazebo/set_model_state", 10);
 
    string model;
    string buf;
    
    add_robot = 
             node.serviceClient<gazebo_msgs::SpawnModel>("gazebo/spawn_sdf_model");

    while(!fin.eof()){
        getline(fin, buf);
        model += buf + "\n";
    }
    double radius=0.003, length=2;
    int kol=length/(2*radius);
    
    for(int i=0;i<kol;i++)
    {    
    srv.request.model_xml = model;
    std::string s = std::to_string(i);
    srv.request.model_name = "ball"+s;
    geometry_msgs::Pose pose;
    add_robot.call(srv);
      sleep(1.0);
      
      if(i>0) 
      {
       gazebo_msgs::ModelState msg;
       msg.model_name = "ball"+s;
       msg.pose.position.z = 2*i*radius;
       pub.publish(msg);
       //sleep(1.0);
      }
    }
    
   
 
    
    //Spawning finished
 
    //gazebo_msgs::ModelState msg;
    //msg.model_name = "ball";
    //msg.pose.position.x = 2.0;
    //pub.publish(msg);
    //sleep(1.0);
    //ros::spinOnce();
    return 0;
}
