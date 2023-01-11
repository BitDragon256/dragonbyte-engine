#pragma once

#include <iostream>

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

			bool operator== (const optional& a_krOther)
			{
				if (!a_krOther.has_value() || !has_value())
					return false;
				return a_krOther.value() == value();
			}

			bool operator!= (const optional& a_krOther)
			{
				return !(*this == a_krOther);
			}

		private:

			T m_data;
			bool m_containsValue;

		};

		inline void print_error(const std::exception& e)
		{
			std::cerr << "\n" << "\033[31m" << "Error occured:\n\t" << e.what() << "\033[0m" << "\n\n";
		}

	} // namespace tools

} // namespace dragonbyte_engine