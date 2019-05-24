#pragma once
#include<iostream>
#include <vector>
#include "cartesian_frenet_conversion.h"
using namespace std;

class vec2d {//���ڱ�ʾ������λ��
public:
    vec2d();
    vec2d(double z_in,double x_in);
	double z;//longitudinal
	double x;//lateral
};


class lane_line {//������
public:
	double C0;//lane position
	double C1;//heading angle
	double C2;//lane curvature 
	double C3;//lane curvature derivative	
	int lane_line_type;//���ͣ����ߡ�ʵ�ߵ�
    //type definition: 0-dashed,1-solid,2-none,3-road edge,4-double lane mark,5-bott's dots,6-invalid
	bool valid;//�Ƿ��⵽�˳����ߣ�����Ӧ���е�û�м�⵽�ĳ����ߣ��ͽ����ֵ��Ϊfalse

public:
	lane_line();//Ĭ�Ϲ��캯��
	lane_line(double C0_in, double C1_in, double C2_in, double C3_in, int line_type, bool line_valid);
    double distance_point_laneline(double z, double x);//������ĳһ�������ߵľ���
    double lateral_position_line(double z);//�������z�������ߺ�������
};

class obstacle {//�ϰ���
public:
    bool pedestrian;
    bool vehicle;
    double pos_z;//longitudinal position����ڵ�ǰ���������λ�õĵѿ�������ϵ
    double pos_x;//lateral position����ڵ�ǰ���������λ�õĵѿ�������ϵ
    double pos_s;//longitudinal position-frenet����ϵ
    double pos_l;//lateral position-frenet����ϵ
    double height;
    double width;
    double v_z;//longitudinal speed����ڵ�ǰ���������λ�õĵѿ�������ϵ
    double v_x;//lateral speed����ڵ�ǰ���������λ�õĵѿ�������ϵ
    double v_s;//�ع켣���˶��ٶ�frenet����ϵ
    double v_l;//��ֱ�ڹ켣���˶��ٶ�frenet����ϵ
    //ȱ���ϰ����ٶ�����ת���ĳ���

public:
    obstacle();//Ĭ�Ϲ��캯��
    obstacle(double z, double x, double vz, double vx, double width_in, double height_in, int type);
    void calculate_speed_frenet(const double rkappa, const double l, const double veh_spd_cur);//����v_z��v_x����v_s��v_l
};

class lane {//����
public:
	lane_line left;
	lane_line right;
	lane_line next_left;
	lane_line next_right;
	double road_speed_limit;//��·����m/s

public:
	lane();//Ĭ�Ϲ��캯��
	lane(lane_line left_in, lane_line right_in, double road_speed_limit_in);//ֻ��⵽�����������
	lane(lane_line left_in, lane_line right_in, lane_line next_left_in, lane_line next_right_in, double road_speed_limit_in);//��⵽������ĳ���
	double distance_point_lane_centerline(double z, double x);//�����ϰ����������߾���
	double lateral_position_centerline(double z);//�������������봦���������ߵĺ�������
	double lateral_position_left_centerline(double z);//�������������봦��೵�������ߵĺ�������
	double lateral_position_right_centerline(double z);//�������������봦�Ҳ೵�������ߵĺ�������
	lane_line center_line_cal();//���㵱ǰ���������߷���
	lane_line left_center_line_cal();//������೵�������߷���
	lane_line right_center_line_cal();//�����Ҳ೵�������߷���
	double lane_width();//���㵱ǰ�������
    int obs_in_lane(obstacle obs);//�ж��ϰ����Ƿ��ڳ�����
};


vec2d GPS_to_local_coordinate(vec2d origin_gps, vec2d obj_gps, double veh_path_angle);//��object��GPS����ת������origin_GPSΪ���ĵľֲ�����ϵ��
