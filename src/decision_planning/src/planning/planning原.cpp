#include "planning.h"
#include "environment.h"
#include "astar.hpp"
#include <vector>
#include <cmath>
using namespace AStar;
using namespace std;

vec2d circle_center(vec2d init_point,vec2d end_point,double kappa,int direction){
    double c1 = 0, c2 = 0, A = 0, B = 0, C = 0, z01 = 0, x01 = 0, x02 = 0, z02 = 0;
    c1 = (pow(end_point.x, 2) - pow(init_point.x, 2) + pow(end_point.z, 2)
          - pow(init_point.z, 2)) / 2 / (end_point.x - init_point.x);
    c2 = (end_point.z - init_point.z) / (end_point.x - init_point.x);
    A = 1.0 + pow(c2, 2);
    B = 2 * (init_point.x - c1) * c2 - 2 * init_point.z;
    C = pow((init_point.x - c1), 2) + pow(init_point.z, 2) - pow(1 / kappa, 2);
    z01 = (-B + sqrt(B*B - 4 * A * C)) / 2 / A;
    x01 = c1 - c2 * z01;
    z02 = (-B - sqrt(B*B - 4 * A * C)) / 2 / A;
    x02 = c1 - c2 * z02;
    cout << "circle center coordinates 1: (" << x01 << ", " << z01 << ")" << endl;
    cout << "circle center coordinates 2: (" << x02 << ", " << z02 << ")" << endl;
    double x0, z0;
    if (direction == 0) {//left
        if (x01 < x02) {
            x0 = x01;
            z0 = z01;
        }
        else {
            x0 = x02;
            z0 = z02;
        }
    }
    else {//right
        if (x01 > x02) {
            x0 = x01;
            z0 = z01;
        }
        else {
            x0 = x02;
            z0 = z02;
        }
    }
    vec2d center=vec2d(z0,x0);
    return center;
}


vehicle::vehicle() {
    veh_len = 3;
    veh_width =2;
    cur_speed = 0;
    veh_preferred_speed = 10;
    max_acc = 1;
    max_dec = 1;
    max_steering_angle = pi/4;
}

vehicle::vehicle(double len, double width, double cur_spd, double preferred_speed, double max_a,
                 double max_d, double max_angle) {
    veh_len = len;
    veh_width = width;
    cur_speed = cur_spd;
    veh_preferred_speed = preferred_speed;
    max_acc = max_a;
    max_dec = max_d;
    max_steering_angle = max_angle;
}

double vehicle::safety_steering_angle_cal(void){
    //���ص�λΪrad�ĽǶ�
    //Ŀǰ�ǲο�ֵ,����Ҫ��������
    if(cur_speed>20){
        return (double)2/180*pi;
    }
    else if(cur_speed>15){
        return (double)4/180*pi;//����20m/sʱ���ת���2��
    }
    else if(cur_speed>10){
        return (double)10/180*pi;//����15m/sʱ���ת���10��
    }
    else if(cur_speed>5){
        return (double)15/180*pi;
    }
    else if(cur_speed>2){
        return (double)20/180*pi;
    }
    else{
        return (double)45/180*pi;
    }
}

bool path_segment::path_segment_collision(obstacle obs) {
    double distance;
    if (is_lane_driving) {//����
        distance = abs(C0 + C1 * obs.pos_z + C2 * obs.pos_z*obs.pos_z
                       + C3 * obs.pos_z*obs.pos_z*obs.pos_z - obs.pos_x);
        if (distance < obs.width) {
            return true;//����
        }
    }
    else {//�ǳ���

        if (kappa == 0) {//�ǳ�����ֱ��
            //��㵽ֱ�ߵľ���
            double A, B, C;//Ax+Bz+C=0;
            A = (end_point.z - init_point.z) / (end_point.x - init_point.x);
            B = -1;
            C = init_point.z - init_point.x * A;
            distance = abs(A * obs.pos_x + B * obs.pos_z + C) / sqrt(A * A + B * B);
            if (distance < obs.width) {
                return true;//����
            }
        }
        else {//�ǳ�����Բ��
            //��㵽Բ�ĵľ��룬��Բ�뾶֮����ǵ㵽Բ���ľ���
            //��Բ��
            vec2d center=circle_center(init_point,end_point,kappa,direction);
            double x0,z0,A,B,C;
            x0=center.x;
            z0=center.z;
            distance = 1000;
            //�ж��ڲ��ڻ��߽Ƕȷ�Χ��
            double k1[2], k2[2], k3[2], k4[2];
            k1[0] = (init_point.z + end_point.z - 2 * z0);//����������
            k1[1] = (init_point.x + end_point.x - 2 * x0);
            k2[0] = (init_point.z - z0);//������ʼ��
            k2[1] = (init_point.x - x0);
            k3[0] = (end_point.z - z0);//������ֹ��
            k3[1] = (end_point.x - x0);
            k4[0] = (obs.pos_z - z0);
            k4[1] = (obs.pos_x - x0);
            A = k1[0] * k4[0] + k1[1] * k4[1];//A>0��ʾ�������ߵļн�Ϊ��ǣ��������0
            B = k2[0] * k4[0] + k2[1] * k4[1];
            C = k3[0] * k4[0] + k3[1] * k4[1];
            if (A > 0) {//�ж�������ߵļн��Ƿ������
                if (B > 0 || C > 0) {
                    //�������(��Բ�ĵľ���-�뾶)
                    distance = abs(sqrt(pow(obs.pos_x - x0, 2) + pow(obs.pos_z - z0, 2)) - 1 / kappa);
                }
            }
            if (distance < obs.width) {
                return true;//����
            }
        }
    }
    return false;
}

double path_segment::path_segment_distance_with_obstacle(obstacle obs) {
    double distance;
    if (is_lane_driving) {//����
        distance = abs(C0 + C1 * obs.pos_z + C2 * obs.pos_z*obs.pos_z
                       + C3 * obs.pos_z*obs.pos_z*obs.pos_z - obs.pos_x);
        return distance;
    }
    else {//�ǳ���
        if (kappa == 0) {//�ǳ�����ֱ��
            //��㵽ֱ�ߵľ���
            double A, B, C;//Ax+Bz+C=0;
            A = (end_point.z - init_point.z) / (end_point.x - init_point.x);
            B = -1;
            C = init_point.z - init_point.x * A;
            distance = abs(A * obs.pos_x + B * obs.pos_z + C) / sqrt(A * A + B * B);
            return distance;
        }
        else {//�ǳ�����Բ��
            //��㵽Բ�ĵľ��룬��Բ�뾶֮����ǵ㵽Բ���ľ���
            //��Բ��
            double c1 = 0, c2 = 0, A = 0, B = 0, C = 0, z01 = 0, x01 = 0, x02 = 0, z02 = 0;
            c1 = (pow(end_point.x, 2) - pow(init_point.x, 2) + pow(end_point.z, 2)
                  - pow(init_point.z, 2)) / 2 / (end_point.x - init_point.x);
            c2 = (end_point.z - init_point.z) / (end_point.x - init_point.x);
            A = 1.0 + pow(c2, 2);
            B = 2 * (init_point.x - c1) * c2 - 2 * init_point.z;
            C = pow((init_point.x - c1), 2) + pow(init_point.z, 2) - pow(1 / kappa, 2);
            z01 = (-B + sqrt(B*B - 4 * A * C)) / 2 / A;
            x01 = c1 - c2 * z01;
            z02 = (-B - sqrt(B*B - 4 * A * C)) / 2 / A;
            x02 = c1 - c2 * z02;
            cout << "circle center coordinates 1: (" << x01 << ", " << z01 << ")" << endl;
            cout << "circle center coordinates 2: (" << x02 << ", " << z02 << ")" << endl;
            double x0, z0;
            if (direction == 0) {//left
                if (x01 < x02) {
                    x0 = x01;
                    z0 = z01;
                }
                else {
                    x0 = x02;
                    z0 = z02;
                }
            }
            else {//right
                if (x01 > x02) {
                    x0 = x01;
                    z0 = z01;
                }
                else {
                    x0 = x02;
                    z0 = z02;
                }
            }
            distance = 1000;
            //�ж��ڲ��ڻ��߽Ƕȷ�Χ��
            double k1[2], k2[2], k3[2], k4[2];
            k1[0] = (init_point.z + end_point.z - 2 * z0);//����������
            k1[1] = (init_point.x + end_point.x - 2 * x0);
            k2[0] = (init_point.z - z0);//������ʼ��
            k2[1] = (init_point.x - x0);
            k3[0] = (end_point.z - z0);//������ֹ��
            k3[1] = (end_point.x - x0);
            k4[0] = (obs.pos_z - z0);
            k4[1] = (obs.pos_x - x0);
            A = k1[0] * k4[0] + k1[1] * k4[1];//A>0��ʾ�������ߵļн�Ϊ��ǣ��������0
            B = k2[0] * k4[0] + k2[1] * k4[1];
            C = k3[0] * k4[0] + k3[1] * k4[1];
            if (A > 0) {//�ж�������ߵļн��Ƿ������
                if (B > 0 || C > 0) {
                    //�������(��Բ�ĵľ���-�뾶)
                    distance = abs(sqrt(pow(obs.pos_x - x0, 2) + pow(obs.pos_z - z0, 2)) - 1 / kappa);
                }
            }
            return distance;
        }
    }
    return distance;
}

double path_segment::path_segment_length_cal(void) {
    //����((1+f'(x)^2))^0.5dx
    if (is_lane_driving) {//����
        double z1 = init_point.z;
        double z2 = end_point.z;
        double temp1 = C1 + 2 * C2*z1 + 3 * C3*z1*z1;
        double temp2 = C1 + 2 * C2*z2 + 3 * C3*z2*z2;
        path_segment_length = 0.5*temp2*sqrt(1 + temp2 * temp2)
                + 0.5*log(abs(temp2 + sqrt(1 + temp2 * temp2)))
                - 0.5*temp1*sqrt(1 + temp1 * temp1) + 0.5*log(abs(temp1 + sqrt(1 + temp1 * temp1)));
    }
    else if (kappa == 0) {//ֱ��
        path_segment_length = sqrt(pow(init_point.z - end_point.z, 2)
                                   + pow(init_point.x - end_point.x, 2));
    }
    else {//Բ��
        //������Ƕ�������һ�°�,�͵���90����
        path_segment_length = (3.1415/2/1.414)*sqrt(pow(init_point.z - end_point.z, 2)
                                                    + pow(init_point.x - end_point.x, 2));
    }
    return path_segment_length;
}

bool path::path_collision(obstacle obs) {
    for (int i = 0; i < path_series.size(); i++) {
        if (path_series[i].path_segment_collision(obs)) {
            return true;
            break;
        }
    }
}

path straight::generate_path(void) {
    //�����Ч�͸��¹滮�㣬��Ч������֮ǰ�Ĺ滮�켣
    if (lane_info.left.valid == true && lane_info.right.valid == true) {
        //����·���滮��ʼGPS�ͺ����
        path straight_path;
        straight_path.GPS_pos_init = GPS_position_cur;
        straight_path.path_angle_init = veh_path_angle;
        //�����복�������ߵĺ������
        double dis_center=lane_info.distance_point_lane_centerline(0, 0);
        double z_temp1 = 10;//�滮��1������λ��
        double z_temp2 = 80;//�滮��2������λ��
        if(abs(dis_center)>0.1){//ƫ���һ����ֵʱ��Ҫ����ת��Ƕ�
            z_temp1=abs(dis_center)/tan(veh_info.safety_steering_angle_cal())+2;
        }
        //���س�������ʻ��ֱ��
        path_segment path_segment_temp;
        path_segment_temp.init_point.z = 0;
        path_segment_temp.init_point.x = 0;
        path_segment_temp.end_point.z = z_temp1;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp1);
        path_segment_temp.is_lane_driving = 0;
        path_segment_temp.kappa = 0;
        straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
        //�س�������ʻ����������
        path_segment_temp.init_point.z = z_temp1;
        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(z_temp1);
        path_segment_temp.end_point.z = z_temp2;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp2);
        path_segment_temp.is_lane_driving = 1;
        path_segment_temp.C0 = lane_info.center_line_cal().C0;
        path_segment_temp.C1 = lane_info.center_line_cal().C1;
        path_segment_temp.C2 = lane_info.center_line_cal().C2;
        path_segment_temp.C3 = lane_info.center_line_cal().C3;
        straight_path.path_series.insert(straight_path.path_series.begin()+1, path_segment_temp);
        planned_path= straight_path;
        return straight_path;
    }
    else {
        planned_path = previous_path;
        return previous_path;
    }
}

path straight::speed_planning(void) {//����ģ�ʹ��Ż�
    double car_follow_gap=200;//�������루��ʼ��Ϊ200m��
    double lead_veh_speed = 0;//m/s
    //����������롢ǰ�����ٵ�
    for (int i = 0; i < obstacle_info.size(); i++) {
        if (abs(obstacle_info[i].pos_x) < lane_info.lane_width()/2
                && obstacle_info[i].pos_z>0) {//���ڵ�ǰ�����ڣ����ڱ���ǰ��
            if (car_follow_gap > obstacle_info[i].pos_z) {
                car_follow_gap = obstacle_info[i].pos_z;
                lead_veh_speed = obstacle_info[i].v_z;
            }
        }
    }
    if (car_follow_gap > 150) {//������ʻ
        planned_path.path_series[0].init_speed = veh_info.cur_speed;
        planned_path.path_series[0].end_speed = veh_info.cur_speed;
        planned_path.path_series[1].init_speed = veh_info.cur_speed;
        planned_path.path_series[1].end_speed
                = min(lane_info.road_speed_limit, veh_info.veh_preferred_speed);
    }
    else if (lead_veh_speed <= 1 && car_follow_gap<veh_info.cur_speed*10) {//ͣ��
        planned_path.path_series.erase(planned_path.path_series.begin() + 1);
        planned_path.path_series[0].end_point.z
                = max(car_follow_gap - veh_info.veh_len - 2,(double)0);
        planned_path.path_series[0].end_point.x = 0;
        planned_path.path_series[0].is_lane_driving = 0;
        planned_path.path_series[0].kappa = 0;
        planned_path.path_series[0].init_speed = veh_info.cur_speed;
        planned_path.path_series[0].end_speed = 0;
    }
    else {//����
        double car_follow_speed=0;//���ݸ������롢��ǰ���ټ�������복��
        //ʹ�ø���ģ�ͼ������ĸ�������IDM
        double car_follow_gap_des = 0;//����ĸ�������
        car_follow_gap_des = max(veh_info.cur_speed * 5
                                 + veh_info.cur_speed*(lead_veh_speed - veh_info.cur_speed)
                                 / sqrt(2 * veh_info.max_acc*veh_info.max_dec), (double)0) + 10;
        car_follow_speed = car_follow_speed + veh_info.max_acc*
                (1 - pow(veh_info.cur_speed / veh_info.veh_preferred_speed, 1)
                 - pow(car_follow_gap_des / car_follow_gap, 2));
        //��·��߳���lane_info.road_speed_limit
        //��ʻԱĿ�공��veh_info.veh_preferred_speed
        planned_path.path_series[0].init_speed = veh_info.cur_speed;
        planned_path.path_series[0].end_speed = min(min(car_follow_speed,
                                                        lane_info.road_speed_limit), veh_info.veh_preferred_speed);
        planned_path.path_series[1].init_speed = planned_path.path_series[0].end_speed;
        planned_path.path_series[1].end_speed = min(min(lead_veh_speed,
                                                        lane_info.road_speed_limit), veh_info.veh_preferred_speed);
    }
    return planned_path;
}

CoordinateList straight::generate_path_astar(void){
    //ת�����������������A*���й滮�����⳵�������ų�����ʻ
    AStar::Generator generator;
    //set environment
    generator.setWorldSize({-lane_info.lane_width()*2, 0},{lane_info.lane_width()*2, 150});//���½������Ͻ�����
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);
    generator.clearCollisions();
    for(int i=0;i<obstacle_info.size();i++){
        int x_c=obstacle_info[i].pos_x
                -lane_info.lateral_position_centerline(obstacle_info[i].pos_z);//frenet coordinate x
        int z_c=obstacle_info[i].pos_z;// cartesian coordinate z
        int w=obstacle_info[i].width;
        int h=obstacle_info[i].width*1.5;
        int w_v=veh_info.veh_width;//vehicle width
        for(int x=x_c-(w+w_v)/2-1;x<x_c+(w+w_v)/2+2;x++){
            for(int y=z_c-(h+w_v)/2-1;y<z_c+(h+w_v)/2+2;y++){
                generator.addCollision({x,y});
            }
        }
    }
    CoordinateList path = generator.findPath({-lane_info.lateral_position_centerline(0),0}, {0,100});
    for(int i=0;i<path.size();i++) {
        path[i].x=path[i].x+lane_info.lateral_position_centerline(path[i].y);
    }

    //����ĳ���������ԭ�������������A*�滮�����ھ���������
    //  CoordinateList path;
    //  for(int p=0;p<planned_path.path_series.size();p++){
    //    //set the start and end point of astar path planning according to the planned path
    //    path_segment path_origin=planned_path.path_series[p];
    //    Vec2i sp={path_origin.init_point.x,path_origin.init_point.z};
    //    Vec2i ep={path_origin.end_point.x,path_origin.end_point.z};
    //    //find path
    //    CoordinateList path_temp = generator.findPath(sp, ep);
    //    for(int i=path_temp.size()-1;i>=0;i--) {
    //      path.push_back(path_temp[i]);
    //    }
    //    //set the cost map of astar according to the planned path, closer point corresponds to low cost
    //    //modify : uint totalCost = current->G + ((i < 4) ? 10 : 14);
    //    //add a function to calculate the cost
    //    //astar path planning
    //  }
    return path;
}


CoordinateList straight::speed_planning_astar(void){
    //ת�����������������A*���й滮�����⳵�������ų�����ʻ
    AStar::Generator generator;
    //set environment
    generator.setWorldSize({0, 0},{100, 100});//���½������Ͻ�����
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);
    generator.clearCollisions();
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            if(obstacle_map_temporal_spatio[i][j]==1){
                generator.addCollision({i,j});
            }
        }
    }
    CoordinateList path = generator.speed_plan({0,0}, {100,100});//��������յ㼴��
    return path;
}


path change_lane::generate_path(void) {
    if (change_lane_direction == 1) {//����
        //���ȸ����ϰ����ͼȷ���ܷ����������ܣ����ȼ����س�����ʻ��ͬstraight
        double lane_width = lane_info.lane_width();
        double lead_veh_time_gap=100, left_lead_veh_time_gap=100, left_follow_veh_time_gap=100;
        for (int i = 0; i < obstacle_info.size(); i++) {
            //�����ϰ����뵱ǰ���ľ���
            double z = sqrt(pow(obstacle_info[i].pos_z,2)+pow(obstacle_info[i].pos_x,2));//ǰ����0,�󷽣�0
            //�����ϰ����뵱ǰ����ƫ��ĺ������
            double frenet_x = lane_info.distance_point_lane_centerline(obstacle_info[i].pos_z,
                                                                       obstacle_info[i].pos_x);
            double v_s = max(abs(obstacle_info[i].v_s),abs(veh_info.cur_speed));//��ǰ��ʻ��0�������ʻ��0
            if (v_s == 0) {
                v_s = 1;
            }
            //�жϸó���Ŀ�공�����ǵ�ǰ������������������������Ӱ�쵱ǰ����ʻ
            if (frenet_x >= -lane_width / 2 && frenet_x <= lane_width / 2 && z>0) {
                //���ڵ�ǰ���������㵱ǰ������ǰ��������ʱ��
                lead_veh_time_gap = min(lead_veh_time_gap, abs(z / v_s));
            }
            else if (frenet_x >= -lane_width*3 / 2 && frenet_x <= -lane_width / 2) {
                //������೵�������㵱ǰ���������ǰ�����󷽳�������Сʱ��
                if (z >= 0) {
                    left_lead_veh_time_gap = min(left_lead_veh_time_gap, abs(z / v_s));
                }
                else {
                    left_follow_veh_time_gap = min(left_follow_veh_time_gap, abs(z / v_s));
                }
            }
            cout<<"obstacle_vs="<<obstacle_info[i].v_s<<endl;
        }
        cout<<"lead_veh_time_gap="<<lead_veh_time_gap<<endl;
        cout<<"left_follow_veh_time_gap="<<left_follow_veh_time_gap<<endl;
        cout<<"left_lead_veh_time_gap="<<left_lead_veh_time_gap<<endl;
        //�ж��Ƿ����㰲ȫ���룬��ֵ���޸ģ��ҳ��������ͱ�������������������滮���·��
        if (left_follow_veh_time_gap > 5 && left_lead_veh_time_gap > 5 && lead_veh_time_gap > 5
                && lane_info.left.lane_line_type!=1 &&lane_info.left.lane_line_type!=3
                &&lane_info.left.lane_line_type!=4 ) {
            //����·���滮��ʼGPS�ͺ����
            path change_lane_path;
            change_lane_path.GPS_pos_init = GPS_position_cur;
            change_lane_path.path_angle_init = veh_path_angle;
            //�滮��1��2
            double z_temp1 = 20;//�滮��1������λ�ó�ʼ��
            double z_temp2 = 100;//�滮��2������λ�ó�ʼ��
            //��1������λ�û���Ҫ���ǳ���
            z_temp1=abs(lane_info.lane_width())/tan(veh_info.safety_steering_angle_cal())+2;
            //���س�������ʻ��ֱ�ߣ��������
            path_segment path_segment_temp;
            path_segment_temp.init_point.z = 0;
            path_segment_temp.init_point.x = 0;
            path_segment_temp.end_point.z = z_temp1;
            path_segment_temp.end_point.x = lane_info.lateral_position_left_centerline(z_temp1);
            path_segment_temp.is_lane_driving = 0;
            path_segment_temp.kappa = 0;
            change_lane_path.path_series.insert(change_lane_path.path_series.begin(),
                                                path_segment_temp);
            //�س�������ʻ����೵������
            path_segment_temp.init_point.z = z_temp1;
            path_segment_temp.init_point.x = lane_info.lateral_position_left_centerline(z_temp1);
            path_segment_temp.end_point.z = z_temp2;
            path_segment_temp.end_point.x = lane_info.lateral_position_left_centerline(z_temp2);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.left_center_line_cal().C0;
            path_segment_temp.C1 = lane_info.left_center_line_cal().C1;
            path_segment_temp.C2 = lane_info.left_center_line_cal().C2;
            path_segment_temp.C3 = lane_info.left_center_line_cal().C3;
            change_lane_path.path_series.insert(change_lane_path.path_series.begin() + 1,
                                                path_segment_temp);
            planned_path = change_lane_path;
            return change_lane_path;
        }
        else {//��Ȼ�ص�ǰ������ʻ
            path straight_path;
            straight_path.GPS_pos_init = GPS_position_cur;
            straight_path.path_angle_init = veh_path_angle;
            //�滮��1��2
            double z_temp1 = 20;//�滮��1������λ��
            double z_temp2 = 100;//�滮��2������λ��
            //����λ�û���Ҫ���ǳ��ٰɣ�
            //���س�������ʻ��ֱ��
            path_segment path_segment_temp;
            path_segment_temp.init_point.z = 0;
            path_segment_temp.init_point.x = 0;
            path_segment_temp.end_point.z = z_temp1;
            path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp1);
            path_segment_temp.is_lane_driving = 0;
            path_segment_temp.kappa = 0;
            straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
            //�س�������ʻ����������
            path_segment_temp.init_point.z = z_temp1;
            path_segment_temp.init_point.x = lane_info.lateral_position_centerline(z_temp1);
            path_segment_temp.end_point.z = z_temp2;
            path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp2);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.center_line_cal().C0;
            path_segment_temp.C1 = lane_info.center_line_cal().C1;
            path_segment_temp.C2 = lane_info.center_line_cal().C2;
            path_segment_temp.C3 = lane_info.center_line_cal().C3;
            straight_path.path_series.insert(straight_path.path_series.begin() + 1, path_segment_temp);
            planned_path = straight_path;
            return straight_path;
        }
    }
    else if (change_lane_direction == 2) {//�ұ��
        //���ȸ����ϰ����ͼȷ���ܷ����������ܣ����ȼ����س�����ʻ��ͬstraight
        double lane_width = lane_info.lane_width();
        double lead_veh_time_gap = 100, right_lead_veh_time_gap = 100,
                right_follow_veh_time_gap = 100;
        for (int i = 0; i < obstacle_info.size(); i++) {
            double z = obstacle_info[i].pos_z;//ǰ����0,�󷽣�0
            //�����ϰ����뵱ǰ����ƫ��ĺ������
            double frenet_x = lane_info.distance_point_lane_centerline(obstacle_info[i].pos_z,
                                                                       obstacle_info[i].pos_x);
            double v_s = obstacle_info[i].v_s;//��ǰ��ʻ��0�������ʻ��0
            if (v_s == 0) {
                v_s = 1;
            }
            //�жϸó���Ŀ�공�����ǵ�ǰ������������������������Ӱ�쵱ǰ����ʻ
            if (frenet_x >= -lane_width / 2 && frenet_x <= lane_width / 2 && z>0) {
                //���ڵ�ǰ���������㵱ǰ������ǰ��������ʱ��
                lead_veh_time_gap = min(lead_veh_time_gap, abs(z / v_s));
            }
            else if (frenet_x >= lane_width / 2 && frenet_x <= lane_width * 3 / 2) {
                //�����Ҳ೵�������㵱ǰ�������Ҳ�ǰ�����󷽳�������Сʱ��
                if (z >= 0) {
                    right_lead_veh_time_gap = min(right_lead_veh_time_gap, abs(z / v_s));
                }
                else {
                    right_follow_veh_time_gap = min(right_follow_veh_time_gap, abs(z / v_s));
                }
            }
        }
        //�ж��Ƿ����㰲ȫ���룬��ֵ���޸ģ��ҳ��������ͱ�������������������滮���·��
        if (right_follow_veh_time_gap > 5 && right_lead_veh_time_gap > 5
                && lead_veh_time_gap > 5 && lane_info.right.lane_line_type!=1 &&lane_info.right.lane_line_type!=3
                &&lane_info.right.lane_line_type!=4) {
            //����·���滮��ʼGPS�ͺ����
            path change_lane_path;
            change_lane_path.GPS_pos_init = GPS_position_cur;
            change_lane_path.path_angle_init = veh_path_angle;
            //�滮��1��2
            double z_temp1 = 20;//�滮��1������λ��
            double z_temp2 = 100;//�滮��2������λ��
            //��1������λ�û���Ҫ���ǳ���
            z_temp1=abs(lane_info.lane_width())/tan(veh_info.safety_steering_angle_cal())+2;
            //���س�������ʻ��ֱ�ߣ��������
            path_segment path_segment_temp;
            path_segment_temp.init_point.z = 0;
            path_segment_temp.init_point.x = 0;
            path_segment_temp.end_point.z = z_temp1;
            path_segment_temp.end_point.x = lane_info.lateral_position_right_centerline(z_temp1);
            path_segment_temp.is_lane_driving = 0;
            path_segment_temp.kappa = 0;
            change_lane_path.path_series.insert(change_lane_path.path_series.begin(),
                                                path_segment_temp);
            //�س�������ʻ���Ҳ೵������
            path_segment_temp.init_point.z = z_temp1;
            path_segment_temp.init_point.x = lane_info.lateral_position_right_centerline(z_temp1);
            path_segment_temp.end_point.z = z_temp2;
            path_segment_temp.end_point.x = lane_info.lateral_position_right_centerline(z_temp2);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.right_center_line_cal().C0;
            path_segment_temp.C1 = lane_info.right_center_line_cal().C1;
            path_segment_temp.C2 = lane_info.right_center_line_cal().C2;
            path_segment_temp.C3 = lane_info.right_center_line_cal().C3;
            change_lane_path.path_series.insert(change_lane_path.path_series.begin() + 1,
                                                path_segment_temp);
            planned_path = change_lane_path;
            return change_lane_path;
        }
        else {//��Ȼ�ص�ǰ������ʻ
            path straight_path;
            straight_path.GPS_pos_init = GPS_position_cur;
            straight_path.path_angle_init = veh_path_angle;
            //�滮��1��2
            double z_temp1 = 20;//�滮��1������λ��
            double z_temp2 = 100;//�滮��2������λ��
            //����λ�û���Ҫ���ǳ��ٰɣ�
            //���س�������ʻ��ֱ��
            path_segment path_segment_temp;
            path_segment_temp.init_point.z = 0;
            path_segment_temp.init_point.x = 0;
            path_segment_temp.end_point.z = z_temp1;
            path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp1);
            path_segment_temp.is_lane_driving = 0;
            path_segment_temp.kappa = 0;
            straight_path.path_series.insert(straight_path.path_series.begin(), path_segment_temp);
            //�س�������ʻ����������
            path_segment_temp.init_point.z = z_temp1;
            path_segment_temp.init_point.x = lane_info.lateral_position_centerline(z_temp1);
            path_segment_temp.end_point.z = z_temp2;
            path_segment_temp.end_point.x = lane_info.lateral_position_centerline(z_temp2);
            path_segment_temp.is_lane_driving = 1;
            path_segment_temp.C0 = lane_info.center_line_cal().C0;
            path_segment_temp.C1 = lane_info.center_line_cal().C1;
            path_segment_temp.C2 = lane_info.center_line_cal().C2;
            path_segment_temp.C3 = lane_info.center_line_cal().C3;
            straight_path.path_series.insert(straight_path.path_series.begin() + 1, path_segment_temp);
            planned_path = straight_path;
            return straight_path;
        }
    }
}

path change_lane::speed_planning(void) {//��֪�������ǰ���������ٶ�
    planned_path.path_series[0].init_speed = veh_info.cur_speed;
    planned_path.path_series[0].end_speed = veh_info.cur_speed;
    planned_path.path_series[1].init_speed = veh_info.cur_speed;
    planned_path.path_series[1].end_speed = min(min(veh_info.cur_speed,
                                                    lane_info.road_speed_limit), veh_info.veh_preferred_speed);
    //��·��߳���lane_info.road_speed_limit
    //��ʻԱĿ�공��veh_info.veh_preferred_speed
    return planned_path;
}

CoordinateList change_lane::generate_path_astar(void){
    //ת�����������������A*���й滮�����⳵�������ų�����ʻ
    AStar::Generator generator;
    //set environment
    generator.setWorldSize({-lane_info.lane_width()*2,0},{lane_info.lane_width()*2, 150});//���½������Ͻ�����
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);

    if (change_lane_direction == 1) {//����
        //change_lane_left
        //set environment
        generator.clearCollisions();
        for(int i=0;i<obstacle_info.size();i++){
            int x_c=obstacle_info[i].pos_x
                    -lane_info.lateral_position_centerline(obstacle_info[i].pos_z);//frenet coordinate x
            x_c=x_c+abs(lane_info.lane_width());//ת���������������ϵ
            int z_c=obstacle_info[i].pos_z;// cartesian coordinate z
            int w=obstacle_info[i].width;
            int h=obstacle_info[i].width*1.5;
            int w_v=veh_info.veh_width;//vehicle width
            for(int x=x_c-(w+w_v)/2-1;x<x_c+(w+w_v)/2+2;x++){
                for(int y=z_c-(h+w_v)/2-1;y<z_c+(h+w_v)/2+2;y++){
                    generator.addCollision({x,y});
                }
            }
            //ע���ʱ������ϵ���뻻���󳵵����������Ӧ������ϵ
            //generate path
            CoordinateList path;
            int init_veh_pos_x=-lane_info.lateral_position_centerline(0)+lane_info.lane_width();
            int init_veh_pos_z=0;
            int end_veh_pos_x=0;
            int end_veh_pos_z=80;
            path = generator.findPath({init_veh_pos_x,init_veh_pos_z},
            {end_veh_pos_x,end_veh_pos_z});
            for(int i=path.size()-1;i>=0;i--) {
                path[i].x=path[i].x+lane_info.lateral_position_centerline(path[i].y)
                        -lane_info.lane_width();
            }
            return path;
        }
    }
    else{//change lane right
        //�ұ��
        //set environment
        generator.clearCollisions();
        for(int i=0;i<obstacle_info.size();i++){
            int x_c=obstacle_info[i].pos_x
                    -lane_info.lateral_position_centerline(obstacle_info[i].pos_z);//frenet coordinate x
            x_c=x_c-abs(lane_info.lane_width());//ת���������������ϵ
            int z_c=obstacle_info[i].pos_z;// cartesian coordinate z
            int w=obstacle_info[i].width;
            int h=obstacle_info[i].width*1.5;
            int w_v=veh_info.veh_width;//vehicle width
            for(int x=x_c-(w+w_v)/2-1;x<x_c+(w+w_v)/2+2;x++){
                for(int y=z_c-(h+w_v)/2-1;y<z_c+(h+w_v)/2+2;y++){
                    generator.addCollision({x,y});
                }
            }
        }
        //ע���ʱ������ϵ���뻻���󳵵����������Ӧ������ϵ
        //generate path
        CoordinateList path;
        int init_veh_pos_x=-lane_info.lateral_position_centerline(0)-lane_info.lane_width();
        int init_veh_pos_z=0;
        int end_veh_pos_x=0;
        int end_veh_pos_z=80;
        path = generator.findPath({init_veh_pos_x,init_veh_pos_z},
        {end_veh_pos_x,end_veh_pos_z});
        for(int i=path.size()-1;i>=0;i--) {
            path[i].x=path[i].x+lane_info.lateral_position_centerline(path[i].y)
                    +lane_info.lane_width();
        }
        return path;
    }
}

CoordinateList change_lane::speed_planning_astar(void){
    //ת�����������������A*���й滮�����⳵�������ų�����ʻ
    AStar::Generator generator;
    //set environment
    generator.setWorldSize({0, 0},{100, 100});//���½������Ͻ�����
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);
    generator.clearCollisions();
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            if(obstacle_map_temporal_spatio[i][j]==1){
                generator.addCollision({i,j});
            }
        }
    }
    CoordinateList path = generator.speed_plan({0,0}, {100,100});//��������յ㼴��
    return path;
}


path intersection::generate_path(void) {
    path intersection_path;
    //����·���滮��ʼGPS�ͺ����
    intersection_path.GPS_pos_init = GPS_position_cur;
    intersection_path.path_angle_init = veh_path_angle;
    vec2d point_temp1, point_temp2;
    point_temp1 = GPS_to_local_coordinate(GPS_position_cur, GPS_out_road_section,
                                          veh_path_angle);
    point_temp2 = GPS_to_local_coordinate(GPS_position_cur, GPS_in_road_section,
                                          veh_path_angle);

    if (intersection_type == 0) {//ֱ��ͨ��·��
        //�س�������ʻ
        path_segment path_segment_temp;
        path_segment_temp.init_point.z = 0;
        path_segment_temp.init_point.x = 0;
        path_segment_temp.end_point.z = point_temp1.z;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(point_temp1.z);
        path_segment_temp.is_lane_driving = 1;
        path_segment_temp.C0 = lane_info.center_line_cal().C0;
        path_segment_temp.C1 = lane_info.center_line_cal().C1;
        path_segment_temp.C2 = lane_info.center_line_cal().C2;
        path_segment_temp.C3 = lane_info.center_line_cal().C3;
        intersection_path.path_series.insert(intersection_path.path_series.begin(), path_segment_temp);
        //·�������ߣ�ֱ��
        path_segment_temp.init_point.z = point_temp1.z;
        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(point_temp1.z);
        path_segment_temp.end_point.z = point_temp2.z;
        path_segment_temp.end_point.x = point_temp2.x;
        path_segment_temp.is_lane_driving = 0;
        path_segment_temp.kappa = 0;
        intersection_path.path_series.insert(intersection_path.path_series.begin() + 1,
                                             path_segment_temp);
        //��Ϊʶ�𲻳���һ��·�ĳ����ߣ������ֱ�ߴ��棬����ʶ��������ٸ���
        path_segment_temp.init_point.z = point_temp2.z;
        path_segment_temp.init_point.x = point_temp2.x;
        path_segment_temp.end_point.z = point_temp2.z+ 100;
        path_segment_temp.end_point.x = point_temp2.x
                + lane_info.center_line_cal().C1*100;//Ԥ��б���뵱ǰ������ͬ
        path_segment_temp.is_lane_driving = 0;//Ӧ��ʶ�𲻳���ת���ĳ����ߣ����԰���ֱ�߹滮
        path_segment_temp.kappa = 0;
        intersection_path.path_series.insert(intersection_path.path_series.begin() + 2,
                                             path_segment_temp);
    }
    else if (intersection_type == 1) {//��ת
        //�س�������ʻ
        path_segment path_segment_temp;
        path_segment_temp.init_point.z = 0;
        path_segment_temp.init_point.x = 0;
        path_segment_temp.end_point.z = point_temp1.z;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(point_temp1.z);
        path_segment_temp.is_lane_driving = 1;
        path_segment_temp.C0 = lane_info.center_line_cal().C0;
        path_segment_temp.C1 = lane_info.center_line_cal().C1;
        path_segment_temp.C2 = lane_info.center_line_cal().C2;
        path_segment_temp.C3 = lane_info.center_line_cal().C3;
        intersection_path.path_series.insert(intersection_path.path_series.begin(), path_segment_temp);
        //·�������ߣ�Բ��
        path_segment_temp.init_point.z = point_temp1.z;
        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(point_temp1.z);
        path_segment_temp.end_point.z = point_temp2.z;
        path_segment_temp.end_point.x = point_temp2.x;
        path_segment_temp.is_lane_driving = 0;
        path_segment_temp.direction = 0;//��תԲ��
        double dev_z = abs(path_segment_temp.init_point.z - path_segment_temp.end_point.z);
        double dev_x = abs(path_segment_temp.init_point.x - path_segment_temp.end_point.x);
        double R;//������ʵİ뾶���뾶���㷽�����޸�
        if( dev_z/dev_x > 1 ) {
            R = dev_z * dev_z / dev_x;
        }
        else {
            R = dev_x * dev_x / dev_z;
        }
        path_segment_temp.kappa = 1/R;
        intersection_path.path_series.insert(intersection_path.path_series.begin() + 1,
                                             path_segment_temp);
        //��Ϊʶ�𲻳���һ��·�ĳ����ߣ������ֱ�ߴ��棬����ʶ��������ٸ���
        path_segment_temp.init_point.z = point_temp2.z;
        path_segment_temp.init_point.x = point_temp2.x;
        path_segment_temp.end_point.z = point_temp2.z;
        path_segment_temp.end_point.x = point_temp2.x -100;//Ԥ����ֱ��
        path_segment_temp.is_lane_driving = 0;//Ӧ��ʶ�𲻳���ת���ĳ����ߣ����԰���ֱ�߹滮
        path_segment_temp.kappa = 0;
        intersection_path.path_series.insert(intersection_path.path_series.begin() + 2,
                                             path_segment_temp);
    }
    else{//��ת
        //�س�������ʻ
        path_segment path_segment_temp;
        path_segment_temp.init_point.z = 0;
        path_segment_temp.init_point.x = 0;
        path_segment_temp.end_point.z = point_temp1.z;
        path_segment_temp.end_point.x = lane_info.lateral_position_centerline(point_temp1.z);
        path_segment_temp.is_lane_driving = 1;
        path_segment_temp.C0 = lane_info.center_line_cal().C0;
        path_segment_temp.C1 = lane_info.center_line_cal().C1;
        path_segment_temp.C2 = lane_info.center_line_cal().C2;
        path_segment_temp.C3 = lane_info.center_line_cal().C3;
        intersection_path.path_series.insert(intersection_path.path_series.begin(), path_segment_temp);
        //·�������ߣ�Բ��
        path_segment_temp.init_point.z = point_temp1.z;
        path_segment_temp.init_point.x = lane_info.lateral_position_centerline(point_temp1.z);
        path_segment_temp.end_point.z = point_temp2.z;
        path_segment_temp.end_point.x = point_temp2.x;
        path_segment_temp.is_lane_driving = 0;
        path_segment_temp.direction = 1;//��תԲ��
        double dev_z = abs(path_segment_temp.init_point.z - path_segment_temp.end_point.z);
        double dev_x = abs(path_segment_temp.init_point.x - path_segment_temp.end_point.x);
        double R;//������ʵİ뾶���뾶���㷽�����޸�
        if (dev_z / dev_x > 1) {
            R = dev_z * dev_z / dev_x;
        }
        else {
            R = dev_x * dev_x / dev_z;
        }
        path_segment_temp.kappa = 1 / R;
        intersection_path.path_series.insert(intersection_path.path_series.begin() + 1,
                                             path_segment_temp);
        //��Ϊʶ�𲻳���һ��·�ĳ����ߣ������ֱ�ߴ��棬����ʶ��������ٸ���
        path_segment_temp.init_point.z = point_temp2.z;
        path_segment_temp.init_point.x = point_temp2.x;
        path_segment_temp.end_point.z = point_temp2.z;
        path_segment_temp.end_point.x = point_temp2.x + 100;//Ԥ����ֱ��
        path_segment_temp.is_lane_driving = 0;//Ӧ��ʶ�𲻳���ת���ĳ����ߣ����԰���ֱ�߹滮
        path_segment_temp.kappa = 0;
        intersection_path.path_series.insert(intersection_path.path_series.begin() + 2,
                                             path_segment_temp);
    }
    planned_path = intersection_path;
    return intersection_path;
}

path intersection::speed_planning(void) {//��֪�������ǰ���������ٶ�
    //�ж��ܷ����̵�ʱ�����Ե�ǰ����ͨ��·��
    bool pass = false;
    if (traffic_light_state == 1
            && traffic_light_time_remaining > planned_path.path_series[0].path_segment_length_cal() / veh_info.cur_speed) {
        pass = true;
    }
    else {
        pass = false;
    }
    double turn_speed_limit = 6;//m/s ת�䳵������
    if (pass) {
        //��ǰ����
        planned_path.path_series[0].init_speed = veh_info.cur_speed;
        //ת�䳵������
        planned_path.path_series[0].end_speed = min(min(veh_info.cur_speed,
                                                        turn_speed_limit), veh_info.veh_preferred_speed);
        planned_path.path_series[1].init_speed = min(min(veh_info.cur_speed,
                                                         turn_speed_limit), veh_info.veh_preferred_speed);
        //ת�䳵������
        planned_path.path_series[1].end_speed = min(min(veh_info.cur_speed,
                                                        turn_speed_limit), veh_info.veh_preferred_speed);
        planned_path.path_series[2].init_speed = min(min(veh_info.cur_speed,
                                                         turn_speed_limit), veh_info.veh_preferred_speed);
        //��·��������
        planned_path.path_series[2].end_speed= min(min(veh_info.cur_speed,
                                                       lane_info.road_speed_limit), veh_info.veh_preferred_speed);
        //��·��߳���lane_info.road_speed_limit
        //��ʻԱĿ�공��veh_info.veh_preferred_speed
    }
    else {//ͣ��
        planned_path.path_series.erase(planned_path.path_series.begin() + 2);
        planned_path.path_series.erase(planned_path.path_series.begin() + 1);
        planned_path.path_series[0].init_speed = veh_info.cur_speed;
        planned_path.path_series[0].end_speed = 0;
    }
    return planned_path;
}


CoordinateList intersection::generate_path_astar(void){
    path intersection_path;
    //����·���滮��ʼGPS�ͺ����
    intersection_path.GPS_pos_init = GPS_position_cur;
    intersection_path.path_angle_init = veh_path_angle;
    vec2d point_temp1, point_temp2;
    point_temp1 = GPS_to_local_coordinate(GPS_position_cur, GPS_out_road_section,
                                          veh_path_angle);
    point_temp2 = GPS_to_local_coordinate(GPS_position_cur, GPS_in_road_section,
                                          veh_path_angle);
    //ת�����������������A*���й滮�����⳵�������ų�����ʻ
    AStar::Generator generator;
    //set environment
    generator.setWorldSize({-20,0},{20, 150});//���½������Ͻ�����
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);
    generator.clearCollisions();
    for(int i=0;i<obstacle_info.size();i++){
        int x_c=obstacle_info[i].pos_x
                -lane_info.lateral_position_centerline(obstacle_info[i].pos_z);//frenet coordinate x
        int z_c=obstacle_info[i].pos_z;// cartesian coordinate z
        int w=obstacle_info[i].width;
        int h=obstacle_info[i].width*1.5;
        int w_v=veh_info.veh_width;//vehicle width
        for(int x=x_c-(w+w_v)/2-1;x<x_c+(w+w_v)/2+2;x++){
            for(int y=z_c-(h+w_v)/2-1;y<z_c+(h+w_v)/2+2;y++){
                generator.addCollision({x,y});
            }
        }
    }

    //ע���ʱ������ϵ���뻻���󳵵����������Ӧ������ϵ
    //generate path
    CoordinateList path;
    int init_veh_pos_x=-lane_info.lateral_position_centerline(0);
    int init_veh_pos_z=0;
    int end_veh_pos_x=0;
    int end_veh_pos_z=point_temp1.z;
    for(int i=0;i<end_veh_pos_z;i++) {
        path.push_back({lane_info.lateral_position_centerline(i),i});
    }
    init_veh_pos_x=end_veh_pos_x;
    init_veh_pos_z=end_veh_pos_z;
    end_veh_pos_x=point_temp2.x-lane_info.lateral_position_centerline(point_temp2.z);
    end_veh_pos_z=point_temp2.z;
    CoordinateList path_temp2 = generator.findPath({init_veh_pos_x,init_veh_pos_z},
    {end_veh_pos_x,end_veh_pos_z});
    for(int i=path_temp2.size()-1;i>=0;i--) {
        path_temp2[i].x=path_temp2[i].x+lane_info.lateral_position_centerline(path_temp2[i].y);
        path.push_back(path_temp2[i]);
    }
    return path;

}

CoordinateList intersection::speed_planning_astar(void){
    //ת�����������������A*���й滮�����⳵�������ų�����ʻ
    AStar::Generator generator;
    //set environment
    generator.setWorldSize({0, 0},{100, 100});//���½������Ͻ�����
    generator.setHeuristic(AStar::Heuristic::euclidean);
    generator.setDiagonalMovement(true);
    generator.clearCollisions();
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            if(obstacle_map_temporal_spatio[i][j]==1){
                generator.addCollision({i,j});
            }
        }
    }
    CoordinateList path = generator.speed_plan({0,0}, {100,100});//��������յ㼴��
    return path;
}


void shortrange_planning::obstacle_path_temporal_spatio_figure(void) {//�����ϰ�����STͼ�ϵķֲ�
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            obstacle_map_temporal_spatio[i][j] = 0;//����ֵΪ0����ʾû���ϰ���
        }
    }
    for (int i = 0; i < obstacle_info.size(); i++) {
        //���ȸ���path�����Լ�obs��pos_x��pos_z������obs��pos_s��pos_l
        double length_temp=0;
        double pos_l_temp=1000;
        double pos_s_temp=1000;
        obstacle_info[i].pos_l = 1000;
        for (int j = 0; j < planned_path.path_series.size(); j++) {
            if(obstacle_info[i].pos_z>=planned_path.path_series[j].init_point.z
                    && obstacle_info[i].pos_z<=planned_path.path_series[j].end_point.z){
                pos_l_temp
                        = planned_path.path_series[j].path_segment_distance_with_obstacle(obstacle_info[i]);
                if (pos_l_temp < obstacle_info[i].pos_l) {
                    obstacle_info[i].pos_l = pos_l_temp;
                    obstacle_info[i].pos_s = obstacle_info[i].pos_z + length_temp;//����Ȼ�ǲ��Եģ����˼�
                    obstacle_info[i].calculate_speed_frenet(0, pos_l_temp,
                                                            sqrt(obstacle_info[i].v_x*obstacle_info[i].v_x
                                                            +obstacle_info[i].v_z*obstacle_info[i].v_z));
                }
            }
            length_temp = length_temp + planned_path.path_series[j].path_segment_length_cal();
        }//��i���ϰ������j���켣,ѡ����ӽ���һ���켣
        //����pos_l��v_l������ϰ�����켣�Ľ���
        if (abs(obstacle_info[i].v_l) <= 0.3) {//��Ϊ���򲻶�
            if (abs(obstacle_info[i].pos_l) < obstacle_info[i].width * 2) {
                for (int t = 0; t < 100; t++) {
                    int pos_temp = round(obstacle_info[i].pos_s + obstacle_info[i].v_s * t);
                    //          pos_temp = max(1, pos_temp);
                    //          pos_temp = min(99, pos_temp);
                    int speed=1+obstacle_info[i].v_s;
                    if(pos_temp>=1 && pos_temp<=98){
                      for(int i=-speed; i<=speed; i++){
                        obstacle_map_temporal_spatio[t][pos_temp+i]=1;
                      }
                    }
                }
            }
        }
        else{//��켣�н��㣬������һֱ�ڹ켣��
            int t_temp = obstacle_info[i].pos_l / obstacle_info[i].v_l;
            int s_temp = obstacle_info[i].pos_s + obstacle_info[i].v_s * t_temp;
            if(s_temp>=0 && s_temp<99){
                obstacle_map_temporal_spatio[t_temp][s_temp] = 1;
                obstacle_map_temporal_spatio[t_temp][s_temp - 1] = 1;
                obstacle_map_temporal_spatio[t_temp][s_temp + 1] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp - 1] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp + 1] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp - 2] = 1;
                obstacle_map_temporal_spatio[t_temp - 1][s_temp + 2] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp - 1] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp + 1] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp - 2] = 1;
                obstacle_map_temporal_spatio[t_temp + 1][s_temp + 2] = 1;
            }
        }
        //��դ���ͼ��ֵ
    }
}

shortrange_planning::shortrange_planning(){
    lane lane_temp;
    lane_info=lane_temp;//������Ϣ
    vehicle veh_temp;
    veh_info=veh_temp;//������Ϣ
    vector<obstacle> obstacle_temp;
    obstacle obs_temp;
    obstacle_temp.insert(obstacle_temp.begin(),obs_temp);
    obstacle_info=obstacle_temp;//�ϰ�����ϸ��Ϣ
    driving_intention=0;//�̳̼�ʻ��ͼ���б�0-ֱ�У�1-������2-�ұ���ȵȣ�
    GPS_position_cur=vec2d(31.0,121.0);
    veh_path_angle=0;
}

shortrange_planning::shortrange_planning(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                                         int driving_intention_in,vec2d GPS_cur, double path_angle){
    lane_info=lane_info_in;
    veh_info=veh_info_in;
    obstacle_info=obstacle_info_in;
    driving_intention=driving_intention_in;
    GPS_position_cur=GPS_cur;
    veh_path_angle=path_angle;
}

straight::straight(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                   int driving_intention_in,vec2d GPS_cur, double path_angle){
    lane_info=lane_info_in;
    veh_info=veh_info_in;
    obstacle_info=obstacle_info_in;
    driving_intention=driving_intention_in;
    GPS_position_cur=GPS_cur;
    veh_path_angle=path_angle;
}

change_lane::change_lane(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                         int driving_intention_in,vec2d GPS_cur, double path_angle,int change_lane_direction_in){
    lane_info=lane_info_in;
    veh_info=veh_info_in;
    obstacle_info=obstacle_info_in;
    driving_intention=driving_intention_in;
    GPS_position_cur=GPS_cur;
    veh_path_angle=path_angle;
    change_lane_direction=change_lane_direction_in;
}

intersection::intersection(lane lane_info_in,vehicle veh_info_in, vector<obstacle> obstacle_info_in,
                           int driving_intention_in,vec2d GPS_cur, double path_angle,
                           int intersection_type_in, vec2d gps_out, vec2d gps_in
                           ,int traffic_light_state_in, int traffic_light_time_remaining_in){
    lane_info=lane_info_in;
    veh_info=veh_info_in;
    obstacle_info=obstacle_info_in;
    driving_intention=driving_intention_in;
    GPS_position_cur=GPS_cur;
    veh_path_angle=path_angle;
    intersection_type=intersection_type_in;
    GPS_in_road_section=gps_in;
    GPS_out_road_section=gps_out;
    traffic_light_state=traffic_light_state_in;
    traffic_light_time_remaining=traffic_light_time_remaining_in;
}
