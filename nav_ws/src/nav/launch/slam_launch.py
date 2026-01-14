from launch import LaunchDescription as ld
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

import os

def generate_launch_description():

    nav_pkg = get_package_share_directory("nav")
    lidar_pkg = get_package_share_directory("rplidar_ros")

    lidar = os.path.join(lidar_pkg, 'launch', 'rplidar_a2m8_launch.py')
    slam_toolbox = os.path.join(nav_pkg, 'launch', 'online_async_launch.py')
    transform = os.path.join(nav_pkg,'launch', 'transform_remap.launch.py')

    return ld([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(lidar)
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(transform)
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(slam_toolbox)
        )
    ])

