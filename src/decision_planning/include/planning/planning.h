#pragma once

#include <vector>
#include "environment/environment.h"
#include "planning/astar.hpp"
#include "planning/rrt/utils.hpp"
#include "planning/rrt/RRT.hpp"
//#include "planning/rrt/RRT_implementation.hpp"
using namespace std;
using namespace AStar;

class navi {//��������
public:
  double BD_lon;//����
  double BD_lat;//γ��
  int distance_from_road_seg_end;//·���յ����
  int direction_road;//·����ڱ����ĽǶ�
  int turn;//ת����Ϣ
  int turn_for_intersection;//����·�ڵ�ת����Ϣ
  vector<double> RelX;//��ǰ·������㴮x
  vector<double> RelY;//��ǰ·������㴮y
  int newroad;//�Ƿ�����µĵ�·����1��ʾ����

public:
  navi();//Ĭ�Ϲ��캯��
};

struct path_point{
    double t;
    double v;
    double z;
    double x;
};

class vehicle {//���ڶ��峵����������
public:
  double veh_len;//������
  double veh_width;//����
  double cur_speed;//��ǰ����m/s
  double yaw_angle;//�����
  double veh_preferred_speed;//ƫ�õĳ���m/s
  double max_acc;//��߼��ٶ�m/s2
  double max_dec;//��߼��ٶ�m/s2(����ֵ)
  double max_steering_angle;//���ת���rad
  double lon;//����
  double lat;//γ��

public:
  vehicle();//Ĭ�Ϲ��캯��
  vehicle(double len,double width, double cur_spd,double preferred_speed, double max_a,double max_d,
          double max_angle, double yaw_ang, double lon_in, double lat_in);//���캯��
  double safety_steering_angle_cal(void);//���ص�λΪrad�ĽǶ�
};

class path_segment {//���ڶ���ֱ�ߺ�Բ�������Ƕ��ڳ����ߵȲ��������ߣ�����Ҫ��������
public:
  vec2d init_point;//���
  vec2d end_point;//�յ�
  double init_speed;//��㳵��
  double end_speed;//�յ㳵��
  double kappa;//��㵽�յ�Ĺ���Բ������ //������180���Բ�������򲻺��ж�
  int direction;//���ڼ���Բ��λ�ã�left-0,right-1��
  int is_lane_driving;//�Ƿ����ڳ���������ʻ�����ǣ���ʹ�ó����߷��̣������ǣ���ʹ�����涨�����ֹ�������
  double C0, C1, C2, C3;//�����߷���
  double path_segment_length;//Ƭ�γ��ȣ�m��
public:
  bool path_segment_collision(obstacle obs);
  double path_segment_distance_with_obstacle(obstacle obs);//ò����÷���һ���������ŵ�ֵ�����ⲻ��ɵ��ϰ���Ӱ���г�·��
  double path_segment_length_cal(void);//���س���
};


class path
{
public:
  vector<path_segment> path_series;//�滮Ƭ������
  vec2d GPS_pos_init;//��ʼ���GPSλ��
  double path_angle_init;//��ʼ�����

public:
  bool path_collision(obstacle obs);//�����ص�ǰ·����ʻ�Ƿ�����ϰ�����ײ�������ھ�ֹ�ϰ��
};

class shortrange_planning {
public:
  lane lane_info;//������Ϣ
  vehicle veh_info;//������Ϣ
  vector<obstacle> obstacle_info;//�ϰ�����ϸ��Ϣ
  int driving_intention;//�̳̼�ʻ��ͼ���б�0-ֱ�У�1-������2-�ұ���ȵȣ�
  path previous_path;
  vec2d GPS_position_cur;
  double veh_path_angle;
  int obstacle_map_temporal_spatio[100][100];//�ϰ���ʱ��դ���ͼ��ʱ��*�ռ䣩����Ԥ����һ�������С
  //��ͼ�ĵ�λ��s*m
  path planned_path;
  vector<path_point> out_path;

public:
  shortrange_planning();
  shortrange_planning(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                      int driving_intention_in,vec2d GPS_cur, double path_angle);
  void planned_path_cal();//���ݳ����Ĺ滮�õ���ֵ��
  void obstacle_path_temporal_spatio_figure(void);//�����ϰ�����STͼ�ϵķֲ�
};

class straight : public shortrange_planning {
public:
  straight():shortrange_planning(){;}
  straight(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
           int driving_intention_in,vec2d GPS_cur, double path_angle);
  path generate_path_free_driving();
  path generate_path_following();
  path generate_path_braking(int brake_distance);

  //path speed_planning(void);
  //CoordinateList speed_planning_astar(void);
};

class change_lane : public shortrange_planning {
public:
  int change_lane_direction;//0-�������1-������2-�ұ��
  change_lane():shortrange_planning(){change_lane_direction=0;}
  change_lane(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
              int driving_intention_in,vec2d GPS_cur, double path_angle, int change_lane_direction_in);
  path generate_path(void);
  //CoordinateList speed_planning_astar(void);
};

class intersection : public shortrange_planning {
public:
  int intersection_type;//0-·��ֱ�У�1-·����ת��2-·����ת
  vec2d GPS_in_road_section;//��һ·����ڴ�GPSλ�ã�������ת�����Գ����꣩
  vec2d GPS_out_road_section;//��ǰ·�γ���GPSλ�ã�������ת�����Գ����꣩
  intersection():shortrange_planning(){intersection_type=0;}
  int traffic_light_state;//���̵�״̬��1-�̵ƣ�2-�Ƶƣ�3-���
  int traffic_light_time_remaining;//��ǰ״̬ʣ��ʱ��

public:
  intersection(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
               int driving_intention_in, vec2d GPS_cur, double path_angle,
               int intersection_type_in, vec2d gps_out, vec2d gps_in, int traffic_light_state_in,
               int traffic_light_time_remaining_in);
  //path generate_path(void);
  //path speed_planning(void);
  //CoordinateList generate_path_astar(void);
  vector<path_point> generate_path_rrt(void);//rrt�滮
  vector<path_point> generate_path_brake(void);
};

vec2d circle_center(vec2d init_point,vec2d end_point,double kappa,int direction);
