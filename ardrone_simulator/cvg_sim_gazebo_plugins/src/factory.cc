#include "gazebo/physics/physics.hh"
#include "gazebo/common/common.hh"
#include "gazebo/gazebo.hh"
#include <string>
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>


using  std::string;
using namespace std;

namespace gazebo
{
class Factory : public WorldPlugin
{

  public: void Load(physics::WorldPtr _parent, sdf::ElementPtr /*_sdf*/)
  {

    {  
      // Create a new transport node
      transport::NodePtr node(new transport::Node());
      // Initialize the node with the world name
      node->Init(_parent->GetName());
      // Create a publisher on the ~/factory topic
      transport::PublisherPtr factoryPub =
      node->Advertise<msgs::Factory>("~/factory");
      // Create the message
      msgs::Factory msg;

       //initialize  white background

       
        msg.set_sdf_filename("model://white");
        msgs::Set(msg.mutable_pose(),
           math::Pose(math::Vector3(0, 0, 0), math::Quaternion(0, 0, 0)));
        factoryPub->Publish(msg); 
     
       
       
       string home = getenv("HOME");
       string path = home+"/model.json";
       ifstream in(path.data(), ios::binary); 

       Json::Reader reader;  
       Json::Value root;  
       if( !in.is_open() )    
        {   
        cout << "Error opening file\n"<<endl;   
        return;   
         } 
       if(reader.parse(in,root))  
      {  
       //set home pose 
       int home_x = root["home"]["pose_x"].asInt();
       int home_y = root["home"]["pose_y"].asInt();
        msg.set_sdf_filename("model://home");
        msgs::Set(msg.mutable_pose(),
           math::Pose(math::Vector3(0.2*home_x-4+0.1, 0.2*home_y-4+0.1, 0), math::Quaternion(0, 0, 0)));
        factoryPub->Publish(msg); 
        
        //set end pose 
       int end_x = root["end"]["pose_x"].asInt();
       int end_y = root["end"]["pose_y"].asInt();

        msg.set_sdf_filename("model://end");
        msgs::Set(msg.mutable_pose(),
           math::Pose(math::Vector3(0.2*end_x-4+0.1, 0.2*end_y-4+0.1, 0), math::Quaternion(0, 0, 0)));
        factoryPub->Publish(msg); 
       
         //set house
       int house_x = root["house"]["pose_x"].asInt();
       int house_y = root["house"]["pose_y"].asInt();

        msg.set_sdf_filename("model://house");
        msgs::Set(msg.mutable_pose(),
           math::Pose(math::Vector3(0.2*house_x-4+0.1, 0.2*house_y-4+0.1, 0), math::Quaternion(0, 0, 1.57)));
        factoryPub->Publish(msg); 


       //set tower
       int tower_x = root["tower"]["pose_x"].asInt();
       int tower_y = root["tower"]["pose_y"].asInt();

        msg.set_sdf_filename("model://tower");
        msgs::Set(msg.mutable_pose(),
           math::Pose(math::Vector3(0.2*tower_x-4+0.1, 0.2*tower_y-4+0.1, 0), math::Quaternion(0, 0, 0)));
        factoryPub->Publish(msg); 

        //set tower_code _v
       int  tower_code_v_size = root["tower_code_v"].size();
       for(int i=0;i<tower_code_v_size;i++)
       {
              int tower_code_v_x=root["tower_code_v"][i]["pose_x"].asInt();
              int tower_code_v_y=root["tower_code_v"][i]["pose_y"].asInt();
              msg.set_sdf_filename("model://qr_code");
              msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*tower_code_v_x-4+0.1, 0.2*tower_code_v_y-4, 1.9), math::Quaternion(0,0, 0)));
              factoryPub->Publish(msg); 
       }

       //set tower_code _h
       int  tower_code_h_size = root["tower_code_h"].size();
       for(int i=0;i<tower_code_h_size;i++)
       {
              int tower_code_h_x=root["tower_code_h"][i]["pose_x"].asInt();
              int tower_code_h_y=root["tower_code_h"][i]["pose_y"].asInt();
              int tower_code_h_z=root["tower_code_h"][i]["pose_z"].asInt();
              msg.set_sdf_filename("model://qr_code");
              if(i <2 )
                    msgs::Set(msg.mutable_pose(),
                           math::Pose(math::Vector3(0.2*tower_code_h_x-4, 0.2*tower_code_h_y-4, 0.1*tower_code_h_z), math::Quaternion(0,1.57, 0)));
              else  if(i==2)
                    msgs::Set(msg.mutable_pose(),
                           math::Pose(math::Vector3(0.2*tower_code_h_x-4+0.1, 0.2*tower_code_h_y-4+0.1, 0.1*tower_code_h_z), math::Quaternion(1.57,1.57, 0)));
              else  if(i<5)
                    msgs::Set(msg.mutable_pose(),
                           math::Pose(math::Vector3(0.2*tower_code_h_x-4+0.1, 0.2*tower_code_h_y-4+0.15, 0.1*tower_code_h_z), math::Quaternion(1.57,1.57, 0)));
              else
                    msgs::Set(msg.mutable_pose(),
                           math::Pose(math::Vector3(0.2*tower_code_h_x-4-0.1, 0.2*tower_code_h_y-4+0.1, 0.1*tower_code_h_z), math::Quaternion(0,1.57, 0)));

              factoryPub->Publish(msg); 
       }
        

       //set obstacle_v
        int obstacle_size_v=root["obstacle_v"].size();
        for (int i=0;i<obstacle_size_v;i++)
        {
              int obstacle_x=root["obstacle_v"][i]["pose_x"].asInt();
              int obstacle_y=root["obstacle_v"][i]["pose_y"].asInt();
              msg.set_sdf_filename("model://road_obstacle");
              msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*obstacle_x, 0.2*obstacle_y, 0), math::Quaternion(0, 0, 0)));
              factoryPub->Publish(msg); 
        }

        //set obstacle_h
       int obstacle_size_h=root["obstacle_h"].size();
        for (int i=0;i<obstacle_size_h;i++)
        {
              int obstacle_x=root["obstacle_h"][i]["pose_x"].asInt();
              int obstacle_y=root["obstacle_h"][i]["pose_y"].asInt();
              msg.set_sdf_filename("model://road_obstacle");
              msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*obstacle_x, 0.2*obstacle_y, 0), math::Quaternion(0, 0, 1.57)));
              factoryPub->Publish(msg); 
        }

        
       

       //set road-v  
       int road_size = root["road-v"].size();
       for(int i=0;i<road_size;i++){
          int pose_x_min = root["road-v"][i]["pose_x_min"].asInt();
          int pose_y_min = root["road-v"][i]["pose_y_min"].asInt();
          int pose_x_max = root["road-v"][i]["pose_x_max"].asInt();
          int pose_y_max = root["road-v"][i]["pose_y_max"].asInt();

          for(int j=pose_x_min;j<=pose_x_max;j++)
          for(int k=pose_y_min;k<=pose_y_max;k++)
          {
          msg.set_sdf_filename("model://roadline");
          msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*j-4+0.1, 0.2*k-4+0.1, 0), math::Quaternion(0, 0, 0)));
          factoryPub->Publish(msg); 
          }
       }
       
       //set road-h
       int road_h_size = root["road-h"].size();
       for(int i=0;i<road_h_size;i++){
          int pose_x_min = root["road-h"][i]["pose_x_min"].asInt();
          int pose_y_min = root["road-h"][i]["pose_y_min"].asInt();
          int pose_x_max = root["road-h"][i]["pose_x_max"].asInt();
          int pose_y_max = root["road-h"][i]["pose_y_max"].asInt();

          for(int j=pose_x_min;j<=pose_x_max;j++)
          for(int k=pose_y_min;k<=pose_y_max;k++)
          {
          msg.set_sdf_filename("model://roadline");
          msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*j-4+0.1, 0.2*k-4+0.1, 0), math::Quaternion(0, 0, 1.57)));
          factoryPub->Publish(msg); 
          }
       }  
       //set qr_s
       int qr_s_size = root["qr_s"].size();
       for (int i=0;i< qr_s_size;i++){
         int pose_x =root["qr_s"][i]["pose_x"].asInt();
         int pose_y =root["qr_s"][i]["pose_y"].asInt();
          msg.set_sdf_filename("model://qr_s");
          msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*pose_x-4+0.1, 0.2*pose_y-4+0.1, 0), math::Quaternion(0, 0, 0)));
          factoryPub->Publish(msg); 
       }
       //set qr_w
      int qr_w_size = root["qr_w"].size();
       for (int i=0;i< qr_w_size;i++){
         int pose_x =root["qr_w"][i]["pose_x"].asInt();
         int pose_y =root["qr_w"][i]["pose_y"].asInt();
          msg.set_sdf_filename("model://qr_w");
          msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*pose_x-4+0.1, 0.2*pose_y-4+0.1, 0), math::Quaternion(0, 0, 0)));
          factoryPub->Publish(msg); 
       }

        int qr_e_size = root["qr_e"].size();
       for (int i=0;i< qr_e_size;i++){
         int pose_x =root["qr_e"][i]["pose_x"].asInt();
         int pose_y =root["qr_e"][i]["pose_y"].asInt();
          msg.set_sdf_filename("model://qr_e");
          msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*pose_x-4+0.1, 0.2*pose_y-4+0.1, 0), math::Quaternion(0, 0, 0)));
          factoryPub->Publish(msg); 
       }
       
       int qr_n_size = root["qr_n"].size();
       for (int i=0;i< qr_n_size;i++){
         int pose_x =root["qr_n"][i]["pose_x"].asInt();
         int pose_y =root["qr_n"][i]["pose_y"].asInt();
          msg.set_sdf_filename("model://qr_n");
          msgs::Set(msg.mutable_pose(),
                    math::Pose(math::Vector3(0.2*pose_x-4+0.1, 0.2*pose_y-4+0.1, 0), math::Quaternion(0, 0, 0)));
          factoryPub->Publish(msg); 
       }
       

      }   


      
    }

  }
};

// Register this plugin with the simulator
GZ_REGISTER_WORLD_PLUGIN(Factory)
}
