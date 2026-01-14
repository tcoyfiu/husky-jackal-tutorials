from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    parent_frame =  "base_link"
    child_frame =   "laser"
    xt =            "0.125"   #In Meters
    yt =            "0"   #In Meters
    zt =            "0.2"   #In Meters
    yaw =           "3.14159"   #In Radians
    pitch =         "0"   #In Radians
    roll =          "0"   #In Radians

#    remapper = Node(
#        package='nav',  
#        executable='tf_remapper', 
#        name='tf_remapper_node',  
#        output='screen'
#        )
    
    transform = Node(
         package='tf2_ros',
         executable='static_transform_publisher',
         name='laserscan_transform',
         arguments=[xt, yt, zt, yaw, pitch, roll, parent_frame, child_frame],
         output='screen'
     )

    return LaunchDescription([
#        remapper,
        transform
    ])
