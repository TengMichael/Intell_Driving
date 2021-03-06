// Generated by gencpp from file mobileye/mobileye_Obstacle.msg
// DO NOT EDIT!


#ifndef MOBILEYE_MESSAGE_MOBILEYE_OBSTACLE_H
#define MOBILEYE_MESSAGE_MOBILEYE_OBSTACLE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mobileye
{
template <class ContainerAllocator>
struct mobileye_Obstacle_
{
  typedef mobileye_Obstacle_<ContainerAllocator> Type;

  mobileye_Obstacle_()
    : ID(0)
    , timestamp(0)
    , PosX(0.0)
    , PosY(0.0)
    , Blinker(0)
    , CutState(0)
    , VrelX(0.0)
    , MType(0)
    , Status(0)
    , Brake(0)
    , Valid(0)
    , Length(0.0)
    , Width(0.0)
    , Age(0)
    , ObsLane(0)
    , CIPV(0)
    , AngleRate(0.0)
    , ScaleChange(0.0)
    , ArelX(0.0)
    , Angle(0.0)
    , Replaced(0)  {
    }
  mobileye_Obstacle_(const ContainerAllocator& _alloc)
    : ID(0)
    , timestamp(0)
    , PosX(0.0)
    , PosY(0.0)
    , Blinker(0)
    , CutState(0)
    , VrelX(0.0)
    , MType(0)
    , Status(0)
    , Brake(0)
    , Valid(0)
    , Length(0.0)
    , Width(0.0)
    , Age(0)
    , ObsLane(0)
    , CIPV(0)
    , AngleRate(0.0)
    , ScaleChange(0.0)
    , ArelX(0.0)
    , Angle(0.0)
    , Replaced(0)  {
  (void)_alloc;
    }



   typedef uint8_t _ID_type;
  _ID_type ID;

   typedef uint32_t _timestamp_type;
  _timestamp_type timestamp;

   typedef float _PosX_type;
  _PosX_type PosX;

   typedef float _PosY_type;
  _PosY_type PosY;

   typedef uint8_t _Blinker_type;
  _Blinker_type Blinker;

   typedef uint8_t _CutState_type;
  _CutState_type CutState;

   typedef float _VrelX_type;
  _VrelX_type VrelX;

   typedef uint8_t _MType_type;
  _MType_type MType;

   typedef uint8_t _Status_type;
  _Status_type Status;

   typedef uint8_t _Brake_type;
  _Brake_type Brake;

   typedef uint8_t _Valid_type;
  _Valid_type Valid;

   typedef float _Length_type;
  _Length_type Length;

   typedef float _Width_type;
  _Width_type Width;

   typedef uint8_t _Age_type;
  _Age_type Age;

   typedef uint8_t _ObsLane_type;
  _ObsLane_type ObsLane;

   typedef uint8_t _CIPV_type;
  _CIPV_type CIPV;

   typedef float _AngleRate_type;
  _AngleRate_type AngleRate;

   typedef float _ScaleChange_type;
  _ScaleChange_type ScaleChange;

   typedef float _ArelX_type;
  _ArelX_type ArelX;

   typedef float _Angle_type;
  _Angle_type Angle;

   typedef uint8_t _Replaced_type;
  _Replaced_type Replaced;




  typedef boost::shared_ptr< ::mobileye::mobileye_Obstacle_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mobileye::mobileye_Obstacle_<ContainerAllocator> const> ConstPtr;

}; // struct mobileye_Obstacle_

typedef ::mobileye::mobileye_Obstacle_<std::allocator<void> > mobileye_Obstacle;

typedef boost::shared_ptr< ::mobileye::mobileye_Obstacle > mobileye_ObstaclePtr;
typedef boost::shared_ptr< ::mobileye::mobileye_Obstacle const> mobileye_ObstacleConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mobileye::mobileye_Obstacle_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mobileye

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'mobileye': ['/home/silentroar/Desktop/ROS_Intell_Driving/src/mobileye/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mobileye::mobileye_Obstacle_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mobileye::mobileye_Obstacle_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mobileye::mobileye_Obstacle_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >
{
  static const char* value()
  {
    return "dbb37beacc85ec616b931c7ceeb03eff";
  }

  static const char* value(const ::mobileye::mobileye_Obstacle_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdbb37beacc85ec61ULL;
  static const uint64_t static_value2 = 0x6b931c7ceeb03effULL;
};

template<class ContainerAllocator>
struct DataType< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mobileye/mobileye_Obstacle";
  }

  static const char* value(const ::mobileye::mobileye_Obstacle_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 ID\n\
uint32 timestamp\n\
float32 PosX\n\
float32 PosY\n\
uint8 Blinker\n\
uint8 CutState\n\
float32 VrelX\n\
uint8 MType\n\
uint8 Status\n\
uint8 Brake\n\
uint8 Valid\n\
float32 Length\n\
float32 Width\n\
uint8 Age\n\
uint8 ObsLane\n\
uint8 CIPV\n\
float32 AngleRate\n\
float32 ScaleChange\n\
float32 ArelX\n\
float32 Angle\n\
uint8 Replaced\n\
";
  }

  static const char* value(const ::mobileye::mobileye_Obstacle_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ID);
      stream.next(m.timestamp);
      stream.next(m.PosX);
      stream.next(m.PosY);
      stream.next(m.Blinker);
      stream.next(m.CutState);
      stream.next(m.VrelX);
      stream.next(m.MType);
      stream.next(m.Status);
      stream.next(m.Brake);
      stream.next(m.Valid);
      stream.next(m.Length);
      stream.next(m.Width);
      stream.next(m.Age);
      stream.next(m.ObsLane);
      stream.next(m.CIPV);
      stream.next(m.AngleRate);
      stream.next(m.ScaleChange);
      stream.next(m.ArelX);
      stream.next(m.Angle);
      stream.next(m.Replaced);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct mobileye_Obstacle_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mobileye::mobileye_Obstacle_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mobileye::mobileye_Obstacle_<ContainerAllocator>& v)
  {
    s << indent << "ID: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ID);
    s << indent << "timestamp: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.timestamp);
    s << indent << "PosX: ";
    Printer<float>::stream(s, indent + "  ", v.PosX);
    s << indent << "PosY: ";
    Printer<float>::stream(s, indent + "  ", v.PosY);
    s << indent << "Blinker: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Blinker);
    s << indent << "CutState: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.CutState);
    s << indent << "VrelX: ";
    Printer<float>::stream(s, indent + "  ", v.VrelX);
    s << indent << "MType: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.MType);
    s << indent << "Status: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Status);
    s << indent << "Brake: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Brake);
    s << indent << "Valid: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Valid);
    s << indent << "Length: ";
    Printer<float>::stream(s, indent + "  ", v.Length);
    s << indent << "Width: ";
    Printer<float>::stream(s, indent + "  ", v.Width);
    s << indent << "Age: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Age);
    s << indent << "ObsLane: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ObsLane);
    s << indent << "CIPV: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.CIPV);
    s << indent << "AngleRate: ";
    Printer<float>::stream(s, indent + "  ", v.AngleRate);
    s << indent << "ScaleChange: ";
    Printer<float>::stream(s, indent + "  ", v.ScaleChange);
    s << indent << "ArelX: ";
    Printer<float>::stream(s, indent + "  ", v.ArelX);
    s << indent << "Angle: ";
    Printer<float>::stream(s, indent + "  ", v.Angle);
    s << indent << "Replaced: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.Replaced);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MOBILEYE_MESSAGE_MOBILEYE_OBSTACLE_H
