#pragma once

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <vector>
#include <cstring>
#include <visualization_msgs/msg/marker.hpp>
#include <array>
#include <visualization_msgs/msg/marker_array.hpp>

struct Point3D
{
  float x;
  float y;
  float z;
};

struct Region
{
  double min_x, max_x;
  double min_y, max_y;
  double min_z, max_z;
  std::vector<Point3D> points;
  std::array<float, 4> color;
};

struct Voxel
{
  int x, y, z;
  Voxel() : x(0), y(0), z(0) {}
  Voxel(int x, int y, int z) : x(x), y(y), z(z) {}
};

struct VoxelCluster
{
  std::vector<Voxel> voxels;
  Point3D centroid;
  std::array<float, 4> color;
};

class BallDetector : public rclcpp::Node
{
public:
  BallDetector();

private:
  void load_parameters();
  void pointcloud_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  std::vector<Point3D> PC2_to_vector(const sensor_msgs::msg::PointCloud2 &cloud_msg);
  sensor_msgs::msg::PointCloud2 vector_to_PC2(const std::vector<Point3D> &points);
  std::vector<Point3D> filter_points(const std::vector<Point3D> &input);
  Point3D calculate_centroid(const std::vector<Point3D> &points);
  visualization_msgs::msg::Marker create_ball_marker(const Point3D &centroid, const std_msgs::msg::Header &header);
  std::vector<Voxel> create_voxel(const std::vector<Point3D> &points);
  std::vector<VoxelCluster> create_voxel_clustering(const std::vector<Point3D> &points);
  visualization_msgs::msg::MarkerArray create_voxel_markers(const std::vector<Voxel> &voxels, const std_msgs::msg::Header &header);
  visualization_msgs::msg::MarkerArray create_voxel_cluster_markers(const std::vector<VoxelCluster> &clusters, const std_msgs::msg::Header &header);
  visualization_msgs::msg::Marker create_detection_area_marker(const std_msgs::msg::Header &header);

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr subscription_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_publisher_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr filtered_cloud_publisher_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr detection_area_publisher_;

  std::string frame_id_ = "map";

  struct Parameters
  {
    double min_x, max_x, min_y, max_y, min_z, max_z;
    double voxel_size_x, voxel_size_y, voxel_size_z;
  };
  Parameters params_;


};
