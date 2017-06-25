#pragma once
#include "glm.hpp"

namespace Engine
{
	template<class Type>
	class Rectangle
	{
	public:
		Rectangle() : xMin(0), yMin(0), xMax(0), yMax(0) { }
		Rectangle(Type xMin, Type yMin, Type xMax, Type yMax)
			: xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax) { }
		// 	Rectangle(const glm::detail::tvec2<Type> &minPoint, const glm::detail::tvec2<Type> &maxPoint) :
		// 		: xMin(minPoint.x), yMin(minPoint.y), xMax(maxPoint.x), yMax(maxPoint.y) { }

		void Set(Type xCenter, Type yCenter, Type width, Type height)
		{
			xMin = xCenter - width / 2;
			xMax = xCenter + width / 2;
			yMin = yCenter - height / 2;
			yMax = yCenter + height / 2;
		}

		glm::detail::tvec2<Type, glm::precision::defaultp> Center() const
		{
			return glm::detail::tvec2<Type, glm::precision::defaultp>((xMax + xMin) / 2, (yMax + yMin) / 2);
		}

		Type Width() const
		{
			return xMax - xMin;
		}

		Type Height() const
		{
			return yMax - yMin;
		}


		//check if the given point is inside the rectangle
		template<class OtherType>
		bool Contains(OtherType x, OtherType y) const
		{
			return (x >= xMin && x < xMax && y >= yMin && y < yMax);
		}

		template<class OtherType>
		bool Contains(const Rectangle<OtherType> &otherRect) const
		{
			return (xMax >= otherRect.xMax && xMin <= otherRect.xMin && yMax >= otherRect.yMax && yMin <= otherRect.yMin);
		}

		template<class OtherType>
		bool Intersects(const Rectangle<OtherType> &otherRect) const
		{
			return (xMax >= otherRect.xMin && otherRect.xMax >= xMin && yMax >= otherRect.yMin && otherRect.yMax >= yMin);
		}

		template<class OtherType>
		bool Outside(const Rectangle<OtherType> &otherRect) const
		{
			return (xMin >= otherRect.xMax || yMin >= otherRect.yMax || xMax <= otherRect.xMin || yMax <= otherRect.yMin);
		}

		const Rectangle<Type>& MoveTo(Type x, Type y)
		{
			xMax = Width() + x;
			xMin = x;

			yMax = Height() + y;
			yMin = y;

			return *this;
		}

		const Rectangle<Type>& CenterOn(Type x, Type y)
		{
			const Type widthPerTwo = Width() / 2;
			xMax = x + widthPerTwo;
			xMin = x - widthPerTwo;

			const Type heightPerTwo = Height() / 2;
			yMax = y + heightPerTwo;
			yMin = y - heightPerTwo;

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
		Type xMin, yMin, xMax, yMax;
	};
}

using rectf = Engine::Rectangle<float>;