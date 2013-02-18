#ifndef _COLOR_H
#define _COLOR_H

class Color
{
public:
    Color(float r, float g, float b, float a = 1.0f)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color operator+(Color color)
    {
        Color ret(r + color.r, g + color.g, b + color.b, a + color.a);
        return ret;
    }

    Color operator-(Color color)
    {
        Color ret(r - color.r, g - color.g, b - color.b, a - color.a);
        return ret;
    }

    Color operator*(Color color)
    {
        Color ret(r * color.r, g * color.g, b * color.b, a * color.a);
        return ret;
    }

    Color operator/(Color color)
    {
        Color ret(r / color.r, g / color.g, b / color.b, a / color.a);
        return ret;
    }

    Color operator+(float coef)
    {
        Color ret(r + coef, g + coef, b + coef, a + coef);
        return ret;
    }

    Color operator-(float coef)
    {
        Color ret(r - coef, g - coef, b - coef, a - coef);
        return ret;
    }

    Color operator*(float coef)
    {
        Color ret(r * coef, g * coef, b * coef, a * coef);
        return ret;
    }

    Color operator/(float coef)
    {
        Color ret(r / coef, g / coef, b / coef, a / coef);
        return ret;
    }

    void multiply(float coef)
    {
    	r *= coef;
    	g *= coef;
    	b *= coef;
    	a *= coef;
    }

    void multiply(Color * other)
    {
    	r *= other->r;
    	g *= other->g;
    	b *= other->b;
    	a *= other->a;
    }

    void add(float coef)
    {
    	r += coef;
    	g += coef;
    	b += coef;
    	a += coef;
    }

    void add(Color * other)
    {
    	r += other->r;
    	g += other->g;
    	b += other->b;
    	a += other->a;
    }

    float r;
    float g;
    float b;
    float a;
};

#endif
