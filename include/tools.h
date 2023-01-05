#pragma once

// Tools header

namespace dragonbyte_engine
{

	namespace tools
	{

		template< class T >
		class optional
		{
		public:

			optional() :
				m_containsValue{ false }
			{ }

			optional(T a_data) :
				m_containsValue{ true }, m_data{ a_data }
			{ }

			const bool& has_value() const { return m_containsValue; };
			T& value() { return m_data; };
			const T& value() const { return m_data; };

			optional<T> operator= (T a_data) noexcept
			{
				m_data = a_data;
				m_containsValue = true;

				return *this;
			}

		private:

			T m_data;
			bool m_containsValue;

		};

	} // namespace tools

} // namespace dragonbyte_engine