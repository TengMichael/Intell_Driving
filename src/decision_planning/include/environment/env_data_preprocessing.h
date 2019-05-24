#ifndef ENV_DATA_PREPROCESSING_H
#define ENV_DATA_PREPROCESSING_H
#include "environment.h"
#include "env_data_preprocessing.h"
using namespace std;

struct lane_input{
    double Curvature;
    double Heading;
    double Left_Dist;
    double Right_Dist;
    int Left_Type;
    int Right_Type;
    int Left_Conf;
    int Right_Conf;
    int Left_LDW_avai;
    int Right_LDW_avai;
    int Constr_Area;
    double YawAngle;
    double PitchAngle;
};

struct obs_input{
    int ID;
    double DistX;
    double DistY;
    double VrelX;
    double VrelY;
    double RCS;
    int DynProp;
    int Orientation_rms;
    int MeasState;
    int ProbOfExist;
    double ArelX;
    double ArelY;
    int Class;
    double OrientationAngel;
    double Length;
    double Width;
};

class road {//���ڱ�ʾ������λ��
public:
    int lane_num;//·���м�������
    int lane_cur_no;//��ǰ���ڵĳ�����ţ�������������
    //��������������������Ҫ��������ֻ��һ����ת����ʱ��obj_lane_no2=obj_lane_no1;
    int obj_lane_no1;//����·��ת�����������ȷ����Ŀ�공��1��������ǰ���ϰ��
    int obj_lane_no2;//����·��ת�����������ȷ����Ŀ�공��2��������ǰ���ϰ��
    int obj_lane_no_cur;//��ǰʱ�̵�Ŀ�공�����ۺϿ����ϰ����·��ת������
    bool cur_lane_passable;//��ǰ�����Ƿ��ͨ�е�

public:
    road();//Ĭ�Ϲ��캯��
    road(int lane_num_input, int lane_cur_no_input, int obj_lane_no1_input, int obj_lane_no2_input, bool cur_lane_passable_input);//���캯��
    int cal_obj_lane_cur(bool left_lane_change_allowed, bool right_lane_change_allowed);
    int lane_change_completed();
};


void state_transfer_condition_cal(lane lane_data, vector<obstacle> obs_data, vehicle veh_data, navi navi_data,
                                  int lane_num_input, int lane_cur_no_input,
                                  int obj_lane_no1_input, int obj_lane_no2_input,
                                  bool left_lane_change_allowed, bool right_lane_change_allowed);


#endif // ENV_DATA_PREPROCESSING_H
