#pragma once
#include "glm.hpp"
#include "Position.h"
#include "Size.h"

namespace Engine
{
	template<class Type>
	class Rectangle
	{
	public:
		Rectangle() : m_xMin(0), m_yMin(0), m_xMax(0), m_yMax(0) { }
		Rectangle(Type xMin, Type yMin, Type xMax, Type yMax)
			: xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax) { }

		void Set(const Position<Type> &min, const Position<Type> &max)
		{
			m_xMin = min.x;
			m_yMin = min.y;
			m_xMax = max.x;
			m_yMax = max.y;
		}

		void Set(const Position<Type> &center, const Size<Type> &size)
		{
			m_xMin = center.x - size.width / 2;
			m_xMax = center.x + size.width / 2;
			m_yMin = center.y - size.height / 2;
			m_yMax = center.y + size.height / 2;
		}

		glm::detail::tvec2<Type, glm::precision::defaultp> Center() const
		{
			return glm::detail::tvec2<Type, glm::precision::defaultp>((m_xMax + m_xMin) / 2, (m_yMax + m_yMin) / 2);
		}

		Type Width() const
		{
			return m_xMax - m_xMin;
		}

		Type Height() const
		{
			return m_yMax - m_yMin;
		}


		//check if the given point is inside the rectangle
		template<class OtherType>
		bool Contains(OtherType x, OtherType y) const
		{
			return (x >= m_xMin && x < m_xMax && y >= m_yMin && y < m_yMax);
		}

		template<class OtherType>
		bool Contains(const Rectangle<OtherType> &otherRect) const
		{
			return (m_xMax >= otherRect.xMax && m_xMin <= otherRect.xMin && m_yMax >= otherRect.yMax && m_yMin <= otherRect.yMin);
		}

		template<class OtherType>
		bool Intersects(const Rectangle<OtherType> &otherRect) const
		{
			return (m_xMax >= otherRect.xMin && otherRect.xMax >= m_xMin && m_yMax >= otherRect.yMin && otherRect.yMax >= m_yMin);
		}

		template<class OtherType>
		bool Outside(const Rectangle<OtherType> &otherRect) const
		{
			return (m_xMin >= otherRect.xMax || m_yMin >= otherRect.yMax || m_xMax <= otherRect.xMin || m_yMax <= otherRect.yMin);
		}

		const Rectangle<Type>& MoveTo(Type x, Type y)
		{
			m_xMax = Width() + x;
			m_xMin = x;

			m_yMax = Height() + y;
			m_yMin = y;

			return *this;
		}

		const Rectangle<Type>& CenterOn(Type x, Type y)
		{
			const Type widthPerTwo = Width() / 2;
			m_xMax = x + widthPerTwo;
			m_xMin = x - widthPerTwo;

			const Type heightPerTwo = Height() / 2;
			m_yMax = y + heightPerTwo;
			m_yMin = y - heightPerTwo;

			return *this;
		}

// 		template< class T >
// 		T Area() const
// 		{
// 			return (xMax - xMin)*(yMax - yMin);
// 		}
// 
// 		template< class T >
// 		bool TooLittle(T SizeX, T SizeY) const
// 		{
// 			return (xMax - xMin) <= SizeX && (yMax - yMin) <= SizeY;
// 		}
// 
// 		template< class T >
// 		bool IsValid() const
// 		{
// 			return (xMin != 0 || yMin != 0 || xMax != 0 || yMax != 0);
// 		}
// 
// 		template< class T >
// 		bool IsPoint() const
// 		{
// 			return (xMin == xMax && yMin == yMax);
// 		}
// 
// 		template< class T >
// 		bool IsLine() const
// 		{
// 			return (xMin == xMax && yMin != yMax) || (xMin != xMax && yMin == yMax);
// 		}
// 
// 		template< class T >
// 		bool IsEmpty() const
// 		{
// 			return (Width() == 0 || Height() == 0);
// 		}
// 
// 		template< class T >
// 		bool IsNull() const
// 		{
// 			return (!xMin && !yMin && !xMax && !yMax);
// 		}
// 
// 		template< class T >
// 		void Inflate(T dx, T dy)
// 		{
// 			xMin -= dx;
// 			xMax += dx;
// 			yMin -= dy;
// 			yMax += dy;
// 		}
// 
// 		template< class T >
// 		void Deflate(T dx, T dy)
// 		{
// 			xMin += dx;
// 			xMax -= dx;
// 			yMin += dy;
// 			yMax -= dy;
// 		}
// 
// 		template< class T >
// 		void Deflate(const Rectangle<OtherType> &otherRect)
// 		{
// 			xMin += otherRect.xMin;
// 			xMax -= otherRect.xMax;
// 			yMin += otherRect.yMin;
// 			yMax -= otherRect.yMax;
// 		}
// 
// 
// 		template< class T >
// 		void Translate(T dx, T dy)
// 		{
// 			xMin += dx;
// 			xMax += dx;
// 			yMin += dy;
// 			yMax += dy;
// 		}

	private:
		Type m_xMin, m_yMin, m_xMax, m_yMax;
	};
}

using rectf = Engine::Rectangle<float>;