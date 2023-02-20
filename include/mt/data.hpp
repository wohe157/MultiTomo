#include "mt/pch.hpp"
#ifndef MT_DATA_HPP
#define MT_DATA_HPP

#include "mt/definitions.hpp"

namespace mt
{

	class Data
	{
	private:
		const Size m_Size;
		std::vector<Float> m_Data;

	public:
		Data(const Size size, const Float value = 0.0f);
		Data(const Data& other);

		const Data& operator=(const Data& other);

		inline Size size() const { return m_Size; }

		Float get(const Size idx) const;

		const Data& set(const Size idx, const Float value);
	};

} // namespace mt

#endif // MT_DATA_HPP
