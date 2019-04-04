# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from mobileye/mobileye_Lane.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class mobileye_Lane(genpy.Message):
  _md5sum = "e250089b833df5ee2a8ae64f26afe8d3"
  _type = "mobileye/mobileye_Lane"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """float32 Curvature
float32 Heading
float32 Left_Dist
float32 Right_Dist
uint8 Left_Type
uint8 Right_Type
uint8 Left_Conf
uint8 Right_Conf
uint8 Left_LDW_avai
uint8 Right_LDW_avai
uint8 Constr_Area
float32 YawAngle
float32 PitchAngle

"""
  __slots__ = ['Curvature','Heading','Left_Dist','Right_Dist','Left_Type','Right_Type','Left_Conf','Right_Conf','Left_LDW_avai','Right_LDW_avai','Constr_Area','YawAngle','PitchAngle']
  _slot_types = ['float32','float32','float32','float32','uint8','uint8','uint8','uint8','uint8','uint8','uint8','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       Curvature,Heading,Left_Dist,Right_Dist,Left_Type,Right_Type,Left_Conf,Right_Conf,Left_LDW_avai,Right_LDW_avai,Constr_Area,YawAngle,PitchAngle

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(mobileye_Lane, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.Curvature is None:
        self.Curvature = 0.
      if self.Heading is None:
        self.Heading = 0.
      if self.Left_Dist is None:
        self.Left_Dist = 0.
      if self.Right_Dist is None:
        self.Right_Dist = 0.
      if self.Left_Type is None:
        self.Left_Type = 0
      if self.Right_Type is None:
        self.Right_Type = 0
      if self.Left_Conf is None:
        self.Left_Conf = 0
      if self.Right_Conf is None:
        self.Right_Conf = 0
      if self.Left_LDW_avai is None:
        self.Left_LDW_avai = 0
      if self.Right_LDW_avai is None:
        self.Right_LDW_avai = 0
      if self.Constr_Area is None:
        self.Constr_Area = 0
      if self.YawAngle is None:
        self.YawAngle = 0.
      if self.PitchAngle is None:
        self.PitchAngle = 0.
    else:
      self.Curvature = 0.
      self.Heading = 0.
      self.Left_Dist = 0.
      self.Right_Dist = 0.
      self.Left_Type = 0
      self.Right_Type = 0
      self.Left_Conf = 0
      self.Right_Conf = 0
      self.Left_LDW_avai = 0
      self.Right_LDW_avai = 0
      self.Constr_Area = 0
      self.YawAngle = 0.
      self.PitchAngle = 0.

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
      _x = self
      buff.write(_struct_4f7B2f.pack(_x.Curvature, _x.Heading, _x.Left_Dist, _x.Right_Dist, _x.Left_Type, _x.Right_Type, _x.Left_Conf, _x.Right_Conf, _x.Left_LDW_avai, _x.Right_LDW_avai, _x.Constr_Area, _x.YawAngle, _x.PitchAngle))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 31
      (_x.Curvature, _x.Heading, _x.Left_Dist, _x.Right_Dist, _x.Left_Type, _x.Right_Type, _x.Left_Conf, _x.Right_Conf, _x.Left_LDW_avai, _x.Right_LDW_avai, _x.Constr_Area, _x.YawAngle, _x.PitchAngle,) = _struct_4f7B2f.unpack(str[start:end])
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
      _x = self
      buff.write(_struct_4f7B2f.pack(_x.Curvature, _x.Heading, _x.Left_Dist, _x.Right_Dist, _x.Left_Type, _x.Right_Type, _x.Left_Conf, _x.Right_Conf, _x.Left_LDW_avai, _x.Right_LDW_avai, _x.Constr_Area, _x.YawAngle, _x.PitchAngle))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 31
      (_x.Curvature, _x.Heading, _x.Left_Dist, _x.Right_Dist, _x.Left_Type, _x.Right_Type, _x.Left_Conf, _x.Right_Conf, _x.Left_LDW_avai, _x.Right_LDW_avai, _x.Constr_Area, _x.YawAngle, _x.PitchAngle,) = _struct_4f7B2f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_4f7B2f = struct.Struct("<4f7B2f")