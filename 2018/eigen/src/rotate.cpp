#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>
#define PI (3.1415926535897932346f)

int main(int argc, char **argv) 
{
    using ::std::cout;
    using ::std::endl;
    double yaw = -PI/4; // PI/6;
    double pitch = 0; // PI/6;
    double roll = 0; // PI/6 ;
    
    Eigen::Vector3d eulerAngle(roll, pitch, yaw);
    Eigen::AngleAxisd rollAngle(Eigen::AngleAxisd(eulerAngle(0),Eigen::Vector3d::UnitX()));
    Eigen::AngleAxisd pitchAngle(Eigen::AngleAxisd(eulerAngle(1),Eigen::Vector3d::UnitY()));
    Eigen::AngleAxisd yawAngle(Eigen::AngleAxisd(eulerAngle(2),Eigen::Vector3d::UnitZ()));
    Eigen::Quaterniond quaternion;
    quaternion=yawAngle*pitchAngle*rollAngle;
    
    cout << quaternion.w() << endl << endl;
    cout << quaternion.x() << endl << endl;
    cout << quaternion.y() << endl << endl;
    cout << quaternion.z() << endl << endl;
    cout << "==================================================" << endl;

    std::cin.ignore();
    return 0;
}
