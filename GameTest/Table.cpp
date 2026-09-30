#include "stdafx.h"
#include "table.h"

CTable::CTable()
{
	m_lineDefs[eLine_Hard] = CLineDefinition("Hard", .8f, .6f, .2f);
	m_lineDefs[eLine_Soft] = CLineDefinition("Soft", .4f, .3f, .1f);
	m_lineDefs[eLine_Power] = CLineDefinition("Power", .2f, .2f, .6f);
	m_lineDefs[eLine_Flipper] = CLineDefinition("Flipper", .5f, .9f, .1f);
	m_lineDefs[eLine_Fail] = CLineDefinition("Fail", .8f, .3f, .9f);

	m_lineDefs[eLine_Gaurd] = CLineDefinition("Gaurd", .5f, .9f, .1f);
	m_lineDefs[eLine_Ball] = CLineDefinition("Ball", 1.0f, 1.0f, 1.0f);
	m_lineDefs[eLine_Mushroom] = CLineDefinition("Mushroom", .5f, .9f, .1f);
	m_lineDefs[eLine_Teleporter] = CLineDefinition("Teleport", 1.0f, 1.0f, 1.0f);
	m_lineDefs[eLine_Spinner] = CLineDefinition("Spinner", .8f, .6f, .2f);
	m_lineDefs[eLine_Target] = CLineDefinition("Target", .5f, .9f, .1f);


}

CPoint CPoint::Normalize()
{
	CPoint p;
	p.m_x = m_x / sqrt(m_x * m_x + m_y * m_y);
	p.m_y = m_y / sqrt(m_x * m_x + m_y * m_y);
	p.m_selected = false;
	return p;
}

CPoint CPoint::operator+(const CPoint& b)
{
	CPoint p;
	p.m_x = this->m_x + b.m_x;
	p.m_y = this->m_y + b.m_y;
	p.m_selected = false;
	return p;
}

CPoint CPoint::operator-(const CPoint& b)
{
	CPoint p;
	p.m_x = b.m_x - this->m_x;
	p.m_y = b.m_y - this->m_y;
	p.m_selected = false;
	return p;
}

CPoint CPoint::operator*(const float num)
{
	CPoint p;
	p.m_x = this->m_x * num;
	p.m_y = this->m_y * num;
	p.m_selected = false;
	return p;
}

CPoint CPoint::operator/(const float num)
{
	CPoint p;
	p.m_x = this->m_x / num;
	p.m_y = this->m_y / num;
	p.m_selected = false;
	return p;
}

CLineSegment::CLineSegment() : CLineSegment(0.0f, 0.0f, 0.0f, 0.0f, eLine_Fail)
{
}

CLineSegment::CLineSegment(float x1, float y1, float x2, float y2, LineType type)
{
	m_start.m_x = x1;
	m_start.m_y = y1;
	m_start.m_selected = false;
	m_end.m_x = x2;
	m_end.m_y = y2;
	m_end.m_selected = false;
	m_type = type;
	m_selected = false;
}


float CLineSegment::DistanceToLine(float x, float y)
{
	const float x0 = m_start.m_x;
	const float x1 = m_end.m_x;
	const float y0 = m_start.m_y;
	const float y1 = m_end.m_y;

	float dx = x1 - x0;
	float dy = y1 - y0;

	float linelengthSquared = dx * dx + dy * dy;
	float param = ((x - x0)*dx + (y - y0)*dy) / linelengthSquared;
	if (param > 1)
		param = 1;
	if (param < 0)
		param = 0;

	float nearestX = x0 + param * dx;
	float nearestY = y0 + param * dy;

	float distX = x - nearestX;
	float distY = y - nearestY;
	float distance = sqrt((distX*distX) + (distY*distY));
	return distance;
}

CPoint CLineSegment::NormalAwayFromLine(float x, float y)
{
	const float x0 = m_start.m_x;
	const float x1 = m_end.m_x;
	const float y0 = m_start.m_y;
	const float y1 = m_end.m_y;

	float dx = x1 - x0;
	float dy = y1 - y0;

	float linelengthSquared = dx * dx + dy * dy;
	float param = ((x - x0)*dx + (y - y0)*dy) / linelengthSquared;
	if (param > 1)
		param = 1;
	if (param < 0)
		param = 0;

	float nearestX = x0 + param * dx;
	float nearestY = y0 + param * dy;

	CPoint p;
	p.m_x = x - nearestX;
	p.m_y = y - nearestY;
	p.m_selected = false;
	p = p.Normalize();
	return p;
}

/* float CLineSegment::DistanceToInfiniteLine(float x, float y)
{
// See https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
const float x0 = m_start.m_x;
const float x1 = m_end.m_x;
const float y0 = m_start.m_y;
const float y1 = m_end.m_y;

float numerator = abs((y1 - y0)*x - (x1 - x0)*y + x1*y0 - y1*x0);
float denomenator = sqrt((y1 - y0)*(y1 - y0) + (x1 - x0)*(x1 - x0));
float distance = numerator / denomenator;

return distance;
} */

bool CLineSegment::IsOnLine(float x, float y, float tolerance)
{
	return DistanceToLine(x, y) < tolerance;
}

float CPoint::DistanceToPoint(float x, float y)
{
	float dX = x - m_x;
	float dY = y - m_y;
	float distance = sqrt(dX*dX + dY * dY);

	return distance;
}

bool CPoint::IsOnPoint(float x, float y, float tolerance)
{
	return DistanceToPoint(x, y) < tolerance;
}

CLineDefinition::CLineDefinition(const char * name, float r, float g, float b)
{
	m_name = name;
	m_Red = r;
	m_Green = g;
	m_Red = b;
}

