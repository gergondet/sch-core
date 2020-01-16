#include <sch/S_Object/S_Cone.h>

using namespace sch;

const Point3 S_Cone::origin_(0,0,0);

S_Cone::S_Cone(const Scalar& angle, const Scalar &  height) 

{

  angle_=angle;
  height_=height;
  angleTan_=tan(angle);
  baseRadius_=height*angleTan_;
  
  slices_ = 100;
  stacks_ = 4; /// we don't need many stacks to display a cone
} 

S_Cone::~S_Cone(void)
{
}


Point3 S_Cone::l_Support(const Vector3& v, int& /*lastFeature*/)const
{

  Scalar norm = sqrt(v[0] * v[0] + v[1] * v[1]);
  if (norm < sch::epsilon)
  {
    if (v[2] >= 0)    
    {
      return Point3(0, baseRadius_, height_);
    } 
    else
    {
      return origin_;
    }
  }
  else
  {
    if ( v[2] < - angleTan_ * norm)
    {
      return origin_;
    }
    else
    {
      Scalar normInverse = 1 / norm;
      return Point3(normInverse * v[0]*baseRadius_, normInverse * v[1]*baseRadius_, height_);
    }
  }

}


S_Object::S_ObjectType S_Cone::getType() const
{
  return S_Object::TCone;
}

Scalar S_Cone::getAngle() const
{
  return angle_;
}

Scalar S_Cone::getHeight() const
{
  return height_;
}