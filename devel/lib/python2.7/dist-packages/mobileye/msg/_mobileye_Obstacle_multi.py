# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from mobileye/mobileye_Obstacle_multi.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import mobileye.msg

class mobileye_Obstacle_multi(genpy.Message):
  _md5sum = "c479281d4bb2f90247873463e2b6b9d8"
  _type = "mobileye/mobileye_Obstacle_multi"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """mobileye_Obstacle[] Obstacles

================================================================================
MSG: mobileye/mobileye_Obstacle
uint8 ID
uint32 timestamp
float32 PosX
float32 PosY
uint8 Blinker
uint8 CutState
float32 VrelX
uint8 MType
uint8 Status
uint8 Brake
uint8 Valid
float32 Length
float32 Width
uint8 Age
uint8 ObsLane
uint8 CIPV
float32 AngleRate
float32 ScaleChange
float32 ArelX
float32 Angle
uint8 Replaced
"""
  __slots__ = ['Obstacles']
  _slot_types = ['mobileye/mobileye_Obstacle[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       Obstacles

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(mobileye_Obstacle_multi, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.Obstacles is None:
        self.Obstacles = []
    else:
      self.Obstacles = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      length = len(self.Obstacles)
      buff.write(_struct_I.pack(length))
      for val1 in self.Obstacles:
        _x = val1
        buff.write(_struct_BI2f2Bf4B2f3B4fB.pack(_x.ID, _x.timestamp, _x.PosX, _x.PosY, _x.Blinker, _x.CutState, _x.VrelX, _x.MType, _x.Status, _x.Brake, _x.Valid, _x.Length, _x.Width, _x.Age, _x.ObsLane, _x.CIPV, _x.AngleRate, _x.ScaleChange, _x.ArelX, _x.Angle, _x.Replaced))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.Obstacles is None:
        self.Obstacles = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.Obstacles = []
      for i in range(0, length):
        val1 = mobileye.msg.mobileye_Obstacle()
        _x = val1
        start = end
        end += 51
        (_x.ID, _x.timestamp, _x.PosX, _x.PosY, _x.Blinker, _x.CutState, _x.VrelX, _x.MType, _x.Status, _x.Brake, _x.Valid, _x.Length, _x.Width, _x.Age, _x.ObsLane, _x.CIPV, _x.AngleRate, _x.ScaleChange, _x.ArelX, _x.Angle, _x.Replaced,) = _struct_BI2f2Bf4B2f3B4fB.unpack(str[start:end])
        self.Obstacles.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      length = len(self.Obstacles)
      buff.write(_struct_I.pack(length))
      for val1 in self.Obstacles:
        _x = val1
        buff.write(_struct_BI2f2Bf4B2f3B4fB.pack(_x.ID, _x.timestamp, _x.PosX, _x.PosY, _x.Blinker, _x.CutState, _x.VrelX, _x.MType, _x.Status, _x.Brake, _x.Valid, _x.Length, _x.Width, _x.Age, _x.ObsLane, _x.CIPV, _x.AngleRate, _x.ScaleChange, _x.ArelX, _x.Angle, _x.Replaced))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.Obstacles is None:
        self.Obstacles = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.Obstacles = []
      for i in range(0, length):
        val1 = mobileye.msg.mobileye_Obstacle()
        _x = val1
        start = end
        end += 51
        (_x.ID, _x.timestamp, _x.PosX, _x.PosY, _x.Blinker, _x.CutState, _x.VrelX, _x.MType, _x.Status, _x.Brake, _x.Valid, _x.Length, _x.Width, _x.Age, _x.ObsLane, _x.CIPV, _x.AngleRate, _x.ScaleChange, _x.ArelX, _x.Angle, _x.Replaced,) = _struct_BI2f2Bf4B2f3B4fB.unpack(str[start:end])
        self.Obstacles.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_BI2f2Bf4B2f3B4fB = struct.Struct("<BI2f2Bf4B2f3B4fB")
