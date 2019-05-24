#include "global.h"
using namespace std;

vec2d::vec2d(){
  z=0;
  x=0;
}

vec2d::vec2d(double z_in,double x_in){
  z=z_in;
  x=x_in;
}


lane_line::lane_line() {
  C0 = 0;
  C1 = 0;
  C2 = 0;
  C3 = 0;
  lane_line_type = 1;
  valid = false;
}

lane_line::lane_line(double C0_in, double C1_in, double C2_in, double C3_in, 
                     int line_type, bool line_valid) {
  C0 = C0_in;
  C1 = C1_in;
  C2 = C2_in;
  C3 = C3_in;
  lane_line_type = line_type;
  valid = line_valid;
}

double lane_line::distance_point_laneline(double z, double x){
  //x:point lateral position, z:point longitudinal position
  //������ĳһ�������ߵľ��룬����Ϊ��������Ϊ��
  double x_lane = C0 + C1 * z + C2 * z*z + C3 * z*z*z;
  return x-x_lane;//z<0ʱҲ����ͬ�ķ�����
}

double lane_line::lateral_position_line(double z) {
  //x:point lateral position, z:point longitudinal position
  //�������z�������ߺ�������
  double x_lane = C0 + C1 * z + C2 * z*z + C3 * z*z*z;
  return x_lane;
}

lane::lane() {
  lane_line left_temp = lane_line(-1.75, 0, 0, 0, 1, true);
  lane_line right_temp = lane_line(1.75, 0, 0, 0, 1, true);
  lane_line next_left_temp = lane_line(-5.25, 0, 0, 0, 1, true);
  lane_line next_right_temp = lane_line(5.25, 0, 0, 0, 1, true);
  left = left_temp;
  right = right_temp;
  next_left = next_left_temp;
  next_right = next_right_temp;
  road_speed_limit = 60;
}

lane::lane(lane_line left_in, lane_line right_in, double road_speed_limit_in){
  //�᲻����ֳ������ڼ�⵽�����ҳ�����֮������?
  if(left_in.C0>1.75 && right_in.C0>1.75){//��⵽����೵�����ڳ����ұ�
    left=left_in;
    left.C0=2*left_in.C0-right_in.C0;
    left.valid=false;
    right=left_in;
    next_right=right_in;
    next_left = lane_line(2*left.C0-right.C0, left.C1,
                          left.C2, left.C3, left.lane_line_type, false);
  }
  else if(left_in.C0<-1.75 && right_in.C0<-1.75){//��⵽���Ҳ೵�����ڳ������
    right=right_in;
    right.C0=2*left_in.C0-right_in.C0;
    right.valid=false;
    left=right_in;
    next_left=left_in;
    next_right = lane_line(2*right.C0-left.C0, right.C1,
                           right.C2, right.C3, right.lane_line_type, false);
  }
  else{//�������
    left = left_in;
    right = right_in;
    next_left = lane_line(2*left.C0-right.C0, left.C1,
                          left.C2, left.C3, left.lane_line_type, false);
    next_right = lane_line(2*right.C0-left.C0, right.C1,
                           right.C2, right.C3, right.lane_line_type, false);
  }
  road_speed_limit = road_speed_limit_in;
}

lane::lane(lane_line left_in, lane_line right_in, lane_line next_left_in, 
           lane_line next_right_in, double road_speed_limit_in) {
  //�᲻����ֳ������ڼ�⵽�����ҳ�����֮������?
  if(left_in.C0>1.75 && right_in.C0>1.75){//��⵽����೵�����ڳ����ұ�
    left=next_left_in;
    right=left_in;
    next_right=right_in;
    next_left = lane_line(2*left.C0-right.C0, left.C1,
                          left.C2, left.C3, left.lane_line_type, false);
  }
  else if(left_in.C0<-1.75 && right_in.C0<-1.75){//��⵽���Ҳ೵�����ڳ������
    right=next_right_in;
    left=right_in;
    next_left=left_in;
    next_right = lane_line(2*right.C0-left.C0, right.C1,
                           right.C2, right.C3, right.lane_line_type, false);
  }
  else{//�������
    left = left_in;
    right = right_in;
    next_left = next_left_in;
    next_right = next_right_in;
  }
  road_speed_limit = road_speed_limit_in;
}

double lane::distance_point_lane_centerline(double z, double x) {
  //x:point lateral position, z:point longitudinal position
  //���������ҳ����ߵľ���
  double distance_left=left.distance_point_laneline(z, x);
  double distance_right=right.distance_point_laneline(z, x);
  double distance_center = (distance_left + distance_right) / 2;
  return distance_center;
}

double lane::lateral_position_centerline(double z) {
  //x:point lateral position, z:point longitudinal position
  //���㳵�������ߺ���λ��
  double x_left = left.lateral_position_line(z);
  double x_right = right.lateral_position_line(z);
  double x_center = (x_left + x_right) / 2;
  return x_center;
}

double lane::lateral_position_left_centerline(double z) {
  //x:point lateral position, z:point longitudinal position
  //������೵�������ߺ���λ��
  if (next_left.valid == true) {//ֱ������೵��������
    double x_left = next_left.lateral_position_line(z);
    double x_right = left.lateral_position_line(z);
    double x_center = (x_left + x_right) / 2;
    return x_center;
  }
  else {//���ݵ�ǰ���������ߺͳ����������೵��������λ��
    double x_left = left.lateral_position_line(z);
    double x_right = right.lateral_position_line(z);
    double x_center = (x_left + x_right) / 2 - abs(x_right-x_left);
    return x_center;
  }
}

double lane::lateral_position_right_centerline(double z) {
  //x:point lateral position, z:point longitudinal position
  //�����Ҳ೵�������ߺ���λ��
  if (next_right.valid == true) {//ֱ�����Ҳ೵��������
    double x_left = right.lateral_position_line(z);
    double x_right = next_right.lateral_position_line(z);
    double x_center = (x_left + x_right) / 2;
    return x_center;
  }
  else {//���ݵ�ǰ���������ߺͳ���������Ҳ೵��������λ��
    double x_left = left.lateral_position_line(z);
    double x_right = right.lateral_position_line(z);
    double x_center = (x_left + x_right) / 2 + abs(x_right - x_left);
    return x_center;
  }
}

lane_line lane::center_line_cal(void) {//�����ǰ������û��������ô��
  lane_line center_line=lane_line(0,0,0,0,0,true);
  center_line.C0 = (left.C0 + right.C0) / 2;
  center_line.C1 = (left.C1 + right.C1) / 2;
  center_line.C2 = (left.C2 + right.C2) / 2;
  center_line.C3 = (left.C3 + right.C3) / 2;
  return center_line;
}

lane_line lane::left_center_line_cal(void) {
  lane_line center_line = lane_line(0, 0, 0, 0, 0, true);
  if (next_left.valid == true) {//ֱ������೵��������
    center_line.C0 = (left.C0 + next_left.C0) / 2;
    center_line.C1 = (left.C1 + next_left.C1) / 2;
    center_line.C2 = (left.C2 + next_left.C2) / 2;
    center_line.C3 = (left.C3 + next_left.C3) / 2;
  }
  else {//���ݳ������������೵��������
    center_line.C0 = (left.C0 + right.C0) / 2-abs(right.C0 - left.C0);
    center_line.C1 = (left.C1 + right.C1) / 2;
    center_line.C2 = (left.C2 + right.C2) / 2;
    center_line.C3 = (left.C3 + right.C3) / 2;
  }
  return center_line;
}

lane_line lane::right_center_line_cal(void) {
  lane_line center_line = lane_line(0, 0, 0, 0, 0, true);
  if (next_right.valid == true) {//ֱ�����Ҳ೵��������
    center_line.C0 = (right.C0 + next_right.C0) / 2;
    center_line.C1 = (right.C1 + next_right.C1) / 2;
    center_line.C2 = (right.C2 + next_right.C2) / 2;
    center_line.C3 = (right.C3 + next_right.C3) / 2;
  }
  else {//���ݳ�����������Ҳ೵��������
    center_line.C0 = (left.C0 + right.C0) / 2 + abs(right.C0 - left.C0);
    center_line.C1 = (left.C1 + right.C1) / 2;
    center_line.C2 = (left.C2 + right.C2) / 2;
    center_line.C3 = (left.C3 + right.C3) / 2;
  }
  return center_line;
}

double lane::lane_width() {
  //���㳵�����
  return abs(right.C0-left.C0);
}

int lane::obs_in_lane(obstacle obs){
    //�ж��ϰ�������һ��������
    //����߳���Ϊ-2��ͬʱռ��ߺ͵�ǰ����Ϊ-1���ڵ�ǰ����Ϊ0��ͬʱռ�ұߺ͵�ǰ����Ϊ1�����ұ߳���Ϊ2��ͬʱռ��������Ϊ3�������κγ�����Ϊ-3
    int lane_no=-3;
    double z = sqrt(pow(obs.pos_z,2)+pow(obs.pos_x,2));//ǰ����0,�󷽣�0
    //�����ϰ����뵱ǰ����ƫ��ĺ������
    double frenet_x = distance_point_lane_centerline(obs.pos_z,obs.pos_x);
    double lane_wid=lane_width();

    //�жϸó���Ŀ�공�����ǵ�ǰ������������������������Ӱ�쵱ǰ����ʻ
    //�����ж��ڲ��ڳ��������ж����ĸ�����
    if(frenet_x+obs.width/2<-lane_wid *3 / 2){
        lane_no=-3;
    }
    else if(frenet_x-obs.width/2>lane_wid *3 / 2){
        lane_no=-3;
    }
    else if (frenet_x >= -lane_wid / 2 && frenet_x <= lane_wid / 2 && z>0) {
        //�ϰ����������м䳵��
        lane_no=0;
        if (frenet_x+obs.width/2>lane_wid / 2+0.5){
            //ռ���ұ߳���
            lane_no=1;
            if(frenet_x-obs.width/2<-lane_wid / 2-0.5){
                //ռ����߳���
                lane_no=3;
            }
        }
    }
    else if (frenet_x >= -lane_wid*3 / 2 && frenet_x <= -lane_wid/ 2) {
        //������೵��
        lane_no=-2;
        if (frenet_x+obs.width/2>-lane_wid / 2+0.5){
            //ռ���м䳵��
            lane_no=-1;
            if(frenet_x+obs.width/2>lane_wid / 2+0.5){
                //ռ���ұ߳���
                lane_no=3;
            }
        }
    }
    else if (frenet_x >= lane_wid / 2 && frenet_x <= lane_wid *3 / 2) {
        //�����Ҳ೵��
        lane_no=-2;
        if (frenet_x-obs.width/2<lane_wid / 2-0.5){
            //ռ���м䳵��
            lane_no=1;
            if(frenet_x-obs.width/2<-lane_wid / 2-0.5){
                //ռ����߳���
                lane_no=3;
            }
        }
    }
    return lane_no;
}


#define pi  3.14159265358979323846
double EARTH_RADIUS = 6378137;

double rad(double d)
{
  return d * pi / 180.0;
}

double degree(double d)
{
  return d * 180 / pi;
}


vec2d GPS_to_local_coordinate(vec2d origin_gps, vec2d obj_gps, double veh_path_angle) {
  //��object��GPS����ת������origin_GPSΪ���ĵľֲ�����ϵ��
  //latitude��Ӧvec2d�е�z��longitude��Ӧvec2d�е�x
  //veh_path_angle�ǳ�����ʻ�����뱱���ļнǣ���Χ[0,2pi]

  //�����������
  double radLat1 = rad(origin_gps.z);
  double radLat2 = rad(obj_gps.z);
  double a = radLat1 - radLat2;
  double b = rad(origin_gps.x) - rad(obj_gps.x);
  double s = 2 * asin(sqrt(pow(sin(a / 2), 2) +
                           cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
  s = s * EARTH_RADIUS;
  s = round(s * 10000) / 10000;
  //����obj_gps�����origin_gps�����
  double x = sin(obj_gps.x - origin_gps.x) * cos(obj_gps.z);
  double y = cos(origin_gps.z)*sin(obj_gps.z)
      - sin(origin_gps.z)*cos(obj_gps.z)*cos(obj_gps.x - origin_gps.x);
  double bearing;
  if (x >=  0 && y >= 0) {
    bearing = atan2(x, y);
  }
  else if(x >=0 && y<=0){
    bearing = atan2(x, y)+pi;
  }
  else if (x <= 0 && y <= 0) {
    bearing = atan2(x, y) + pi;
  }
  else {
    bearing = atan2(x, y) + pi*2;
  }
  //���ݵ�ǰ����Ǽ����obj������
  vec2d obj_pos;
  double a1 = bearing - veh_path_angle;
  double a2 = bearing + 2 * pi - veh_path_angle;
  double a0;
  if (a1 >= 0) {
    a0 = a1;
  }
  else {
    a0 = a2;
  }
  obj_pos.x = sin(a0)*s;
  obj_pos.z = cos(a0)*s;
  return obj_pos;
}

void obstacle::calculate_speed_frenet(const double rkappa, const double l, const double veh_spd_cur) {
  //����v_z��v_x��theta
  double theta=0;
  if (v_x >= 0 && v_z >= 0) {
    theta = atan2(v_z, v_x);
  }
  else if (v_x <= 0 && v_z >= 0) {
    theta = atan2(v_z, v_x) + pi;
  }
  else if (v_x <= 0 && v_z <= 0) {
    theta = atan2(v_z, v_x) + pi;
  }
  else {
    theta = atan2(v_z, v_x) + pi * 2;
  }
  double rtheta = pi / 2;
  //����frenet����ϵ�µķֽ⳵��
  v_s=CalculateLongitudinalDerivative(rtheta, theta, l, rkappa, veh_spd_cur);
  v_l=CalculateLateralDerivative(rtheta, theta, l, rkappa);
}

obstacle::obstacle() {
  pos_z = 100;
  pos_x = 0;
  v_z = 0;
  v_x = 0;
  width = 4;
  height = 2;
  vehicle = true;
  pedestrian = false;
}

obstacle::obstacle(double z, double x, double vz, double vx, double width_in, double height_in, int type) {
  pos_z = z;
  pos_x = x;
  v_z = vz;
  v_x = vx;
  width = width_in;
  height = height_in;
  if (type == 1) {
    vehicle = true;
    pedestrian = false;
  }
  else if (type == 2) {
    vehicle = false;
    pedestrian = true;
  }
  else {
    vehicle = false;
    pedestrian = false;
  }
}

