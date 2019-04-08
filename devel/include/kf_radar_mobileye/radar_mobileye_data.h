// Generated by gencpp from file kf_radar_mobileye/radar_mobileye_data.msg
// DO NOT EDIT!


#ifndef KF_RADAR_MOBILEYE_MESSAGE_RADAR_MOBILEYE_DATA_H
#define KF_RADAR_MOBILEYE_MESSAGE_RADAR_MOBILEYE_DATA_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace kf_radar_mobileye
{
template <class ContainerAllocator>
struct radar_mobileye_data_
{
  typedef radar_mobileye_data_<ContainerAllocator> Type;

  radar_mobileye_data_()
    : timestamp(0)
    , ID(0)
    , radar_DistX(0.0)
    , radar_DistY(0.0)
    , radar_VrelX(0.0)
    , radar_VrelY(0.0)
    , radar_ArelX(0.0)
    , radar_ArelY(0.0)
    , mobileye_DistX(0.0)
    , mobileye_DistY(0.0)
    , mobileye_VrelX(0.0)
    , mobileye_ArelX(0.0)  {
    }
  radar_mobileye_data_(const ContainerAllocator& _alloc)
    : timestamp(0)
    , ID(0)
    , radar_DistX(0.0)
    , radar_DistY(0.0)
    , radar_VrelX(0.0)
    , radar_VrelY(0.0)
    , radar_ArelX(0.0)
    , radar_ArelY(0.0)
    , mobileye_DistX(0.0)
    , mobileye_DistY(0.0)
    , mobileye_VrelX(0.0)
    , mobileye_ArelX(0.0)  {
  (void)_alloc;
    }



   typedef uint32_t _timestamp_type;
  _timestamp_type timestamp;

   typedef uint8_t _ID_type;
  _ID_type ID;

   typedef float _radar_DistX_type;
  _radar_DistX_type radar_DistX;

   typedef float _radar_DistY_type;
  _radar_DistY_type radar_DistY;

   typedef float _radar_VrelX_type;
  _radar_VrelX_type radar_VrelX;

   typedef float _radar_VrelY_type;
  _radar_VrelY_type radar_VrelY;

   typedef float _radar_ArelX_type;
  _radar_ArelX_type radar_ArelX;

   typedef float _radar_ArelY_type;
  _radar_ArelY_type radar_ArelY;

   typedef float _mobileye_DistX_type;
  _mobileye_DistX_type mobileye_DistX;

   typedef float _mobileye_DistY_type;
  _mobileye_DistY_type mobileye_DistY;

   typedef float _mobileye_VrelX_type;
  _mobileye_VrelX_type mobileye_VrelX;

   typedef float _mobileye_ArelX_type;
  _mobileye_ArelX_type mobileye_ArelX;




  typedef boost::shared_ptr< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> const> ConstPtr;

}; // struct radar_mobileye_data_

typedef ::kf_radar_mobileye::radar_mobileye_data_<std::allocator<void> > radar_mobileye_data;

typedef boost::shared_ptr< ::kf_radar_mobileye::radar_mobileye_data > radar_mobileye_dataPtr;
typedef boost::shared_ptr< ::kf_radar_mobileye::radar_mobileye_data const> radar_mobileye_dataConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace kf_radar_mobileye

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'kf_radar_mobileye': ['/home/michael/Desktop/Intell_driving/ROS_Intell_Driving/src/kf_radar_mobileye/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ce92474b70167fa88c94e831ca031fe2";
  }

  static const char* value(const ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xce92474b70167fa8ULL;
  static const uint64_t static_value2 = 0x8c94e831ca031fe2ULL;
};

template<class ContainerAllocator>
struct DataType< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "kf_radar_mobileye/radar_mobileye_data";
  }

  static const char* value(const ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint32 timestamp\n\
uint8 ID\n\
float32 radar_DistX\n\
float32 radar_DistY\n\
float32 radar_VrelX\n\
float32 radar_VrelY\n\
float32 radar_ArelX\n\
float32 radar_ArelY\n\
float32 mobileye_DistX\n\
float32 mobileye_DistY\n\
float32 mobileye_VrelX\n\
float32 mobileye_ArelX\n\
";
  }

  static const char* value(const ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.timestamp);
      stream.next(m.ID);
      stream.next(m.radar_DistX);
      stream.next(m.radar_DistY);
      stream.next(m.radar_VrelX);
      stream.next(m.radar_VrelY);
      stream.next(m.radar_ArelX);
      stream.next(m.radar_ArelY);
      stream.next(m.mobileye_DistX);
      stream.next(m.mobileye_DistY);
      stream.next(m.mobileye_VrelX);
      stream.next(m.mobileye_ArelX);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct radar_mobileye_data_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::kf_radar_mobileye::radar_mobileye_data_<ContainerAllocator>& v)
  {
    s << indent << "timestamp: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.timestamp);
    s << indent << "ID: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ID);
    s << indent << "radar_DistX: ";
    Printer<float>::stream(s, indent + "  ", v.radar_DistX);
    s << indent << "radar_DistY: ";
    Printer<float>::stream(s, indent + "  ", v.radar_DistY);
    s << indent << "radar_VrelX: ";
    Printer<float>::stream(s, indent + "  ", v.radar_VrelX);
    s << indent << "radar_VrelY: ";
    Printer<float>::stream(s, indent + "  ", v.radar_VrelY);
    s << indent << "radar_ArelX: ";
    Printer<float>::stream(s, indent + "  ", v.radar_ArelX);
    s << indent << "radar_ArelY: ";
    Printer<float>::stream(s, indent + "  ", v.radar_ArelY);
    s << indent << "mobileye_DistX: ";
    Printer<float>::stream(s, indent + "  ", v.mobileye_DistX);
    s << indent << "mobileye_DistY: ";
    Printer<float>::stream(s, indent + "  ", v.mobileye_DistY);
    s << indent << "mobileye_VrelX: ";
    Printer<float>::stream(s, indent + "  ", v.mobileye_VrelX);
    s << indent << "mobileye_ArelX: ";
    Printer<float>::stream(s, indent + "  ", v.mobileye_ArelX);
  }
};

} // namespace message_operations
} // namespace ros

#endif // KF_RADAR_MOBILEYE_MESSAGE_RADAR_MOBILEYE_DATA_H
