#ifndef _COLOR4_H_
#define _COLOR4_H_

class Color4
{
public:

    Color4():
    _red(1.0f),
    _green(1.0f),
    _blue(1.0f),
    _alpha(1.0f)
	{
	
	}
    
    Color4(float r, float g, float b, float a):
    _red(r),
    _green(g),
    _blue(b),
    _alpha(a)
    {
        
    }
    
    void set(float r, float g, float b, float a)
    {
        _red = r;
        _green = g;
        _blue = b;
        _alpha = a;
    }
    
public:
    
    static const Color4 WHITE;
    static const Color4 BLACK;
	
public:

    float _red;
    float _green;
    float _blue;
    float _alpha;
};

#define COLOR_ARRAY(COLOR) {COLOR._red, COLOR._green, COLOR._blue, COLOR._alpha};

#endif // _COLOR4_H_

