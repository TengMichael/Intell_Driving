#include "global.h"
using namespace std;

road::road(){
    lane_num=1;
    obj_lane_no1=1;
    obj_lane_no2=1;
    lane_cur_no=1;
    cur_lane_passable=1;
}

road::road(int lane_num_input, int lane_cur_no_input, int obj_lane_no1_input, int obj_lane_no2_input, bool cur_lane_passable_input){
    lane_num=lane_num_input;
    obj_lane_no1=obj_lane_no1_input;
    obj_lane_no2=obj_lane_no2_input;
    lane_cur_no=lane_cur_no_input;
    cur_lane_passable=cur_lane_passable_input;
}

int road::cal_obj_lane_cur(bool left_lane_change_allowed, bool right_lane_change_allowed){
    int lane_change_dmnd=0;
    //dmndΪ0ʱ��������dmndΪ1ʱ���󻻵���dmndΪ2ʱ���һ���
    //left_lane_change_allowed����ʾ��೵���ڽ�ͨ�������ܷ�������������೵���Ƿ�����ϰ���Ӱ����
    //right_lane_change_allowed����ʾ�Ҳ೵���ڽ�ͨ�������ܷ������������Ҳ೵���Ƿ�����ϰ���Ӱ����
    //��������ж�Ŀ�공��
    if(cur_lane_passable & (lane_cur_no==obj_lane_no1 | lane_cur_no==obj_lane_no2)){//��ǰ��������ͨ�У��ҵ�ǰ��������Ŀ�공��
        obj_lane_no_cur=lane_cur_no;
        lane_change_dmnd=0;
    }
    else if(!cur_lane_passable){
        if (left_lane_change_allowed){
            lane_change_dmnd=1;
            obj_lane_no_cur=lane_cur_no-1;//obj_lane_no_cur�����0�ͱ�ʾԽ�����߱��
        }
        else if(right_lane_change_allowed){
            lane_change_dmnd=2;
            obj_lane_no_cur=lane_cur_no+1;
        }
        else{
            lane_change_dmnd=0;
            obj_lane_no_cur=lane_cur_no;
        }
    }
    else{
        if(lane_cur_no<obj_lane_no1&lane_cur_no<obj_lane_no2){
            lane_change_dmnd=2;
            obj_lane_no_cur=lane_cur_no+1;
        }
        else if(lane_cur_no>obj_lane_no1&lane_cur_no>obj_lane_no2){
            lane_change_dmnd=1;
            obj_lane_no_cur=lane_cur_no-1;
        }
        else{
            lane_change_dmnd=0;
            obj_lane_no_cur=lane_cur_no;
        }
    }
    return lane_change_dmnd;
}

int road::lane_change_completed(){
    if(lane_cur_no==obj_lane_no_cur){
        return 1;
    }
    else{
        return 0;
    }
}

lane lane_data_input(lane_input lane_data){

    lane_line left_in=lane_line(-lane_data.Left_Dist, lane_data.Heading,
                                lane_data.Curvature, 0, lane_data.Left_Type, true);
    lane_line right_in=lane_line(lane_data.Right_Dist, lane_data.Heading,
                                lane_data.Curvature, 0, lane_data.Right_Type, true);
    double road_speed_limit_in=30;
    lane temp=lane(left_in,  right_in, road_speed_limit_in);
    return temp;
}


obstacle obs_data_input(obs_input obs_data){
    obstacle temp=obstacle(obs_data.DistX, obs_data.DistY, obs_data.VrelX, obs_data.VrelY, obs_data.Length, obs_data.Width, 1);
    return temp;
}

void state_transfer_condition_cal(lane lane_data, vector<obstacle> obs_data, vehicle veh_data, navi navi_data,
                                  int lane_num_input, int lane_cur_no_input,
                                  int obj_lane_no1_input, int obj_lane_no2_input,
                                  bool left_lane_change_allowed, bool right_lane_change_allowed){
    //�����²�����ֵ
    E1=0;//����ָ��
    E2=0;//ͣ��ָ��
    lane_driving_C1=0;
    lane_driving_C2=0;
    lane_driving_C3=0;
    lane_driving_C4=0;
    lane_driving_E1=0;
    lane_driving_E2=0;
    lane_driving_F=0;
    //���ݵ��������Ƿ���Ҫ�����򵽴��յ�
    if(navi_data.distance_from_road_seg_end<5 & navi_data.turn==0)
    {//��ʾ����滮�յ�
      E1=0;
      E2=1;//������һ����·��turn�ͱ��0����������ǵ����յ�ͣ��ָ����뵽��·��״̬ͬʱ��1������һ��·�ھͻ�ͣ��
    }
    else{//�������
      E1=1;
      E2=0;
    }
    //�����������ǰ������
    int lane_no;
    double front_dis_left=1000;//��ǰ����
    double front_dis_right=1000;//��ǰ����
    double back_dis_left=1000;//��󳵾�
    double back_dis_right=1000;//�Һ󳵾�
    front_dis=1000;//global variable!
    double v_leading=100;
    double v_leading_low=2;//ǰ���ϰ����ٶ���ֵ�����ڴ���ֵ��Ҫ����
    double front_dis_brake=5;
    double front_dis_follow=20;
    for(int i=0;i<obs_data.size();i++){
        lane_no=lane_data.obs_in_lane(obs_data[i]);
        if(lane_no==0 | lane_no==1 | lane_no==-1 | lane_no==3){
            //ռ�м䳵��
            if(obs_data[i].pos_z>0 & front_dis>=obs_data[i].pos_z){
                front_dis=obs_data[i].pos_z;
                v_leading=obs_data[i].v_z;
            }
        }
        if(lane_no==-2 | lane_no==-1 | lane_no==3){
            //ռ��߳���
            if(obs_data[i].pos_z>0 & front_dis_left>=obs_data[i].pos_z){
                front_dis_left=obs_data[i].pos_z;
            }
            else if(obs_data[i].pos_z<0 & back_dis_left>=abs(obs_data[i].pos_z)){
                back_dis_left=abs(obs_data[i].pos_z);
            }
        }
        if(lane_no==2 | lane_no==1 | lane_no==3){
            //ռ�ұ߳���
            if(obs_data[i].pos_z>0 & front_dis_right>=obs_data[i].pos_z){
                front_dis_right=obs_data[i].pos_z;
            }
            else if(obs_data[i].pos_z<0 & back_dis_right>=abs(obs_data[i].pos_z)){
                back_dis_right=abs(obs_data[i].pos_z);
            }
        }
    }
    if(v_leading<v_leading_low){
        lane_driving_C1=1;
    }
    if(front_dis<front_dis_follow){
        lane_driving_C2=1;
    }
    if(front_dis<front_dis_brake){
        lane_driving_C3=1;
    }
    if(abs(veh_data.cur_speed)<0.5){
        lane_driving_C4=1;
    }
    road road_temp=road(lane_num_input, lane_cur_no_input, obj_lane_no1_input, obj_lane_no2_input, (1-lane_driving_C1));
    lane_driving_E1=road_temp.cal_obj_lane_cur(left_lane_change_allowed, right_lane_change_allowed);
    lane_driving_E2=road_temp.lane_change_completed();
    if((front_dis_left>20  & back_dis_left>20) | (front_dis_right>20& back_dis_right>20)){
        lane_driving_F=1;//����ܹ����������ұ��ܹ�����
    }
    //ʮ��·����صı���
    intersection_C1=0;//��ʾ·���ϰ���������ϰ���϶�ʱ��1����֪����ô�жϣ���Ĭ��Ϊ0���ˣ�RRT�滮��������ʱ��Ҳ���Զ�ͣ��
    if (navi_data.distance_from_road_seg_end<30){
      C1=1;//�ٽ���ǰ��·�յ㣬ͨ�����յ�������Ϣ���ж�
    }
    else{
      C1=0;
    }
    //C1=0;
    if (navi_data.newroad==1 || navi_data.distance_from_road_seg_end>30){//����ź�û����ʱ�����¶�ȡ��ϢƵ�ʲ�����ʱ�����������ź���1��˲�䣬����״̬���˲���·��״̬
      E3=1;//�Ѿ��������µ�·��
    }
    else{
      E3=0;
    }
}
