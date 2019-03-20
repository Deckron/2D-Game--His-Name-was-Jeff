#include "gf2d_Color.h"


Color gf2d_Color(float r, float g, float b, float a)
{
	Color Color;
	Color.r = MIN(MAX(r, -1), 1);
	Color.g = MIN(MAX(g, -1), 1);
	Color.b = MIN(MAX(b, -1), 1);
	Color.a = MIN(MAX(a, -1), 1);
	Color.ct = CT_RGBAf;
	return Color;
}

Color gf2d_Color8(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Color Color;
	Color.r = (float)r;
	Color.g = (float)g;
	Color.b = (float)b;
	Color.a = (float)a;
	Color.ct = CT_RGBA8;
	return Color;
}

Color gf2d_Color_hsl(float h, float s, float l, float a)
{
	Color Color;
	Color.r = h;
	while (Color.r < 0)Color.r += 360;
	while (Color.r >= 360)Color.r -= 360;
	Color.g = MIN(MAX(s, -1), 1);
	Color.b = MIN(MAX(l, -1), 1);
	Color.a = MIN(MAX(a, -1), 1);
	Color.ct = CT_HSL;
	return Color;
}

Color gf2d_Color_hex(Uint32 hex)
{
	Color Color;
	Color.r = (float)hex;
	Color.ct = CT_HEX;
	return Color;
}

Color gf2d_Color_to_float(Color color)
{
	Color nc;
	float C, X, m;
	float factor = 1.0 / 255.0;
	switch (color.ct)
	{
	default:
	case CT_RGBAf:
		return color;
	case CT_RGBA8:
		nc.r = color.r *factor;
		nc.g = color.r *factor;
		nc.b = color.r *factor;
		nc.a = color.r *factor;
		break;
	case CT_HSL:
		nc.a = color.a;
		C = (1 - fabs(2 * color.b - 1)) * color.g;
		X = C * (1 - fabs(fmod(color.r / 60, 2) - 1));
		m = color.b - (C * 0.5);
		if (color.r < 60)
		{
			nc.r = C + m;
			nc.g = X + m;
			nc.b = 0 + m;
		}
		else if (color.r < 120)
		{
			nc.r = X + m;
			nc.g = C + m;
			nc.b = 0 + m;
		}
		else if (color.r < 180)
		{
			nc.r = 0 + m;
			nc.g = C + m;
			nc.b = X + m;
		}
		else if (color.r < 240)
		{
			nc.r = 0 + m;
			nc.g = X + m;
			nc.b = C + m;
		}
		else if (color.r < 300)
		{
			nc.r = X + m;
			nc.g = 0 + m;
			nc.b = C + m;
		}
		else
		{
			nc.r = C + m;
			nc.g = 0 + m;
			nc.b = X + m;
		}
		break;
	case CT_HEX:
		nc.r = (((Uint32)color.r & 0xff000000) >> 24) / 0xff;
		nc.g = (((Uint32)color.r & 0x00ff0000) >> 16) / 0xff;
		nc.b = (((Uint32)color.r & 0x0000ff00) >> 8) / 0xff;
		nc.a = ((Uint32)color.r & 0x000000ff) / 0xff;
		break;
	}
	nc.ct = CT_RGBAf;
	return nc;
}

Color gf2d_Color_to_int8(Color color)
{
	Color nc;
	switch (color.ct)
	{
	case CT_HEX:
		nc.r = (((Uint32)color.r & 0xff000000) >> 24);
		nc.g = (((Uint32)color.r & 0x00ff0000) >> 16);
		nc.b = (((Uint32)color.r & 0x0000ff00) >> 8);
		nc.a = ((Uint32)color.r & 0x000000ff);
	case CT_RGBA8:
		return color;
	case CT_HSL:
		color = gf2d_Color_to_float(color);
	case CT_RGBAf:
	default:
		nc.r = color.r * 255;
		nc.g = color.g * 255;
		nc.b = color.b * 255;
		nc.a = color.a * 255;
		break;
	}
	nc.ct = CT_RGBA8;
	return nc;
}

Color gf2d_Color_to_hsla(Color color)
{
	Color nc;
	float D, Cmin, Cmax, H, S, L;
	if (color.ct == CT_HSL)
	{
		return color;
	}
	nc = gf2d_Color_to_float(color);
	Cmax = MAX(MAX(nc.r, nc.g), nc.b);
	Cmin = MIN(MIN(nc.r, nc.g), nc.b);
	D = Cmax - Cmin;
	L = (Cmax + Cmin) * 0.5;
	if (D == 0.0)
	{
		H = 0;
		S = 0;
	}
	else
	{
		S = D / (1 - fabs(Cmax + Cmin - 1));
		if (Cmax == nc.r)
		{
			H = 60 * fmod(((nc.g - nc.b) / D), 6);
		}
		else if (Cmax == nc.g)
		{
			H = 60 * (((nc.b - nc.r) / D) + 2);
		}
		else
		{
			H = 60 * (((nc.r - nc.g) / D) + 4);
		}
	}
	nc.r = H;
	nc.g = S;
	nc.b = L;
	nc.ct = CT_HSL;
	return nc;
}

Uint32 gf2d_Color_to_hex(Color color)
{
	Uint32 hex;
	Uint32 r, g, b, a;
	Color nc;
	if (color.ct == CT_HEX)
	{
		return color.r;
	}
	nc = gf2d_Color_to_int8(color);
	r = (Uint32)(nc.r) << 24;
	g = (Uint32)(nc.g) << 16;
	b = (Uint32)(nc.b) << 8;
	a = (Uint32)(nc.a);
	hex = r | g | b | a;
	return hex;
}

Color gf2d_Color_from_vector4(Vector4D vector)
{
	Color color;
	color.ct = CT_RGBA8;
	color.r = vector.x;
	color.g = vector.y;
	color.b = vector.z;
	color.a = vector.w;
	return color;
}

Vector4D gf2d_Color_to_vector4(Color Color)
{
	Vector4D vector;
	Color = gf2d_Color_to_int8(Color);
	vector.x = Color.r;
	vector.y = Color.g;
	vector.z = Color.b;
	vector.w = Color.a;
	return vector;
}

float gf2d_Color_get_hue(Color Color)
{
	Color = gf2d_Color_to_hsla(Color);
	return Color.r;
}

Color gf2d_Color_from_sdl(SDL_Color color)
{
	Color nc;
	float factor = 1.0 / 255.0;
	nc.ct = CT_RGBAf;
	nc.r = color.r *factor;
	nc.g = color.r *factor;
	nc.b = color.r *factor;
	nc.a = color.r *factor;
	return nc;
}

SDL_Color gf2d_Color_to_sdl(Color Color)
{
	SDL_Color nc;
	Color = gf2d_Color_to_int8(Color);
	nc.r = (Uint8)Color.r;
	nc.g = (Uint8)Color.g;
	nc.b = (Uint8)Color.b;
	nc.a = (Uint8)Color.a;
	return nc;
}

void gf2d_Color_set_hue(float hue, Color *color)
{
	Color temp;
	if (color->ct == CT_HSL)
	{
		color->r = hue;
		return;
	}
	temp = gf2d_Color_to_hsla(*color);
	temp.r = hue;
	switch (color->ct)
	{
	case CT_HSL:
		// case already handled
		break;
	case CT_HEX:
		color->r = gf2d_Color_to_hex(temp);
		return;
	case CT_RGBA8:
		*color = gf2d_Color_to_int8(temp);
		return;
	case CT_RGBAf:
		*color = gf2d_Color_to_float(temp);
	}
}

void gf2d_Color_blend(Color *dst, Color a, Color b)
{
	float hex;
	if (!dst)return;
	switch (a.ct)
	{
	case CT_HSL:
		b = gf2d_Color_to_hsla(b);
		*dst = gf2d_Color_hsl(
			(a.r + b.r)*0.5,
			(a.g + b.g)*0.5,
			(a.b + b.b)*0.5,
			(a.a + b.a)*0.5);
		return;
	case CT_HEX:
		a = gf2d_Color_to_int8(a);
		b = gf2d_Color_to_int8(b);
		*dst = gf2d_Color8(
			(a.r + b.r)*0.5,
			(a.g + b.g)*0.5,
			(a.b + b.b)*0.5,
			(a.a + b.a)*0.5);
		hex = gf2d_Color_to_hex(*dst);
		*dst = gf2d_Color_hex(hex);
		return;
	case CT_RGBA8:
		b = gf2d_Color_to_int8(b);
		*dst = gf2d_Color8(
			(a.r + b.r)*0.5,
			(a.g + b.g)*0.5,
			(a.b + b.b)*0.5,
			(a.a + b.a)*0.5);
		return;
	case CT_RGBAf:
		b = gf2d_Color_to_float(b);
		*dst = gf2d_Color(
			(a.r + b.r)*0.5,
			(a.g + b.g)*0.5,
			(a.b + b.b)*0.5,
			(a.a + b.a)*0.5);
		return;
	}
}

void gf2d_Color_add(Color *dst, Color a, Color b)
{
	float hex;
	if (!dst)return;
	switch (a.ct)
	{
	case CT_HSL:
		b = gf2d_Color_to_hsla(b);
		*dst = gf2d_Color_hsl(
			a.r + b.r,
			a.g + b.g,
			a.b + b.b,
			a.a + b.a);
		return;
	case CT_HEX:
		a = gf2d_Color_to_int8(a);
		b = gf2d_Color_to_int8(b);
		*dst = gf2d_Color8(
			a.r + b.r,
			a.g + b.g,
			a.b + b.b,
			a.a + b.a);
		hex = gf2d_Color_to_hex(*dst);
		*dst = gf2d_Color_hex(hex);
		return;
	case CT_RGBA8:
		b = gf2d_Color_to_int8(b);
		*dst = gf2d_Color8(
			a.r + b.r,
			a.g + b.g,
			a.b + b.b,
			a.a + b.a);
		return;
	case CT_RGBAf:
		b = gf2d_Color_to_float(b);
		*dst = gf2d_Color(
			a.r + b.r,
			a.g + b.g,
			a.b + b.b,
			a.a + b.a);
		return;
	}
}

void gf2d_Color_multiply(Color *dst, Color a, Color b)
{
	float hex;
	if (!dst)return;
	switch (a.ct)
	{
	case CT_HSL:
		b = gf2d_Color_to_hsla(b);
		*dst = gf2d_Color_hsl(
			a.r*b.r,
			a.g*b.g,
			a.b*b.b,
			a.a*b.a);
		return;
	case CT_HEX:
		a = gf2d_Color_to_int8(a);
		b = gf2d_Color_to_int8(b);
		*dst = gf2d_Color8(
			a.r*b.r,
			a.g*b.g,
			a.b*b.b,
			a.a*b.a);
		hex = gf2d_Color_to_hex(*dst);
		*dst = gf2d_Color_hex(hex);
		return;
	case CT_RGBA8:
		b = gf2d_Color_to_int8(b);
		*dst = gf2d_Color8(
			a.r*b.r,
			a.g*b.g,
			a.b*b.b,
			a.a*b.a);
		return;
	case CT_RGBAf:
		b = gf2d_Color_to_float(b);
		*dst = gf2d_Color(
			a.r*b.r,
			a.g*b.g,
			a.b*b.b,
			a.a*b.a);
		return;
	}
}

Color gf2d_Color_clamp(Color Color)
{
	switch (Color.ct)
	{
	case CT_RGBAf:
		if (Color.r < 0)Color.r = 0;
		else if (Color.r > 1)Color.r = 1;
		if (Color.g < 0)Color.g = 0;
		else if (Color.g > 1)Color.g = 1;
		if (Color.b < 0)Color.b = 0;
		else if (Color.b > 1)Color.b = 1;
		if (Color.a < 0)Color.a = 0;
		else if (Color.a > 1)Color.a = 1;
		return Color;
	case CT_RGBA8:
		if (Color.r < 0)Color.r = 0;
		else if (Color.r > 255)Color.r = 255;
		if (Color.g < 0)Color.g = 0;
		else if (Color.g > 255)Color.g = 255;
		if (Color.b < 0)Color.b = 0;
		else if (Color.b > 255)Color.b = 255;
		if (Color.a < 0)Color.a = 0;
		else if (Color.a > 255)Color.a = 255;
		return Color;
	case CT_HEX:
		return Color;
	case CT_HSL:
		while (Color.r < 0)Color.r += 360;
		while (Color.r > 360)Color.r -= 360;
		if (Color.g < 0)Color.g = 0;
		else if (Color.g > 1)Color.g = 1;
		if (Color.b < 0)Color.b = 0;
		else if (Color.b > 1)Color.b = 1;
		if (Color.a < 0)Color.a = 0;
		else if (Color.a > 1)Color.a = 1;
		return Color;
	}
	return Color;
}