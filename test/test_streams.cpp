#include <gtest/gtest.h>

#include "units.h"

#include <sstream>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

using namespace distance_literals;

using testing::Test;
using testing::Types;

namespace TestStreamOutput
{
	namespace
	{
		std::unordered_map<std::type_index, std::string> literal_to_string_lookup = {
		    // Distance Units
		    // Metric
		    {std::type_index{typeid(units::nanometres)}, "nm"},
		    {std::type_index{typeid(units::micrometres)}, "um"},
		    {std::type_index{typeid(units::millimetres)}, "mm"},
		    {std::type_index{typeid(units::centimetres)}, "cm"},
		    {std::type_index{typeid(units::decimeters)}, "dm"},
		    {std::type_index{typeid(units::metres)}, "m"},
		    {std::type_index{typeid(units::kilometres)}, "km"},

		    // Imperial
		    {std::type_index{typeid(units::thous)}, "th"},
		    {std::type_index{typeid(units::inches)}, "in"},
		    {std::type_index{typeid(units::links)}, "li"},
		    {std::type_index{typeid(units::feet)}, "ft"},
		    {std::type_index{typeid(units::yards)}, "yd"},
		    {std::type_index{typeid(units::rods)}, "rd"},
		    {std::type_index{typeid(units::chains)}, "ch"},
		    {std::type_index{typeid(units::furlongs)}, "fur"},
		    {std::type_index{typeid(units::miles)}, "mi"},
		    {std::type_index{typeid(units::leagues)}, "lea"},

		    // Maritime
		    {std::type_index{typeid(units::fathoms)}, "ftm"},
		    {std::type_index{typeid(units::cables)}, "cb"},
		    {std::type_index{typeid(units::nautical_miles)}, "nmi"},

		    // Astronimical
		    {std::type_index{typeid(units::earth_radii)}, "R"},
		    {std::type_index{typeid(units::lunar_distances)}, "LD"},
		    {std::type_index{typeid(units::astronimical_units)}, "AU"},
		    {std::type_index{typeid(units::light_years)}, "ly"},
		    {std::type_index{typeid(units::parsecs)}, "pc"},
		
			// Mass Units
			// Metric
		    { std::type_index{ typeid(units::picograms) }, "pg" },
			{ std::type_index{ typeid(units::nanograms) }, "ng" },
			{ std::type_index{ typeid(units::micrograms) }, "ug" },
			{ std::type_index{ typeid(units::milligrams) }, "mg" },
			{ std::type_index{ typeid(units::grams) }, "g" },
			{ std::type_index{ typeid(units::kilograms) }, "kg" },

			// Imperial
			{ std::type_index{ typeid(units::grains) }, "gr" },
			{ std::type_index{ typeid(units::drams) }, "dr" },
			{ std::type_index{ typeid(units::ounces) }, "oz" },
			{ std::type_index{ typeid(units::pounds) }, "lb" },
			{ std::type_index{ typeid(units::us_hundredweight) }, "cwt" }
		};
	}

	template <typename T>
	class StreamOutputTest : public Test
	{
	};

	TYPED_TEST_CASE_P(StreamOutputTest);

	TYPED_TEST_P(StreamOutputTest, StreamInsertionOperator_WillFormatStringCorrectly)
	{
		std::stringstream buffer{ "" };
		buffer << TypeParam{ 1 };

		std::string expected {"1" + literal_to_string_lookup[std::type_index{typeid(TypeParam)}]};
		EXPECT_EQ(expected, buffer.str());
	}

	using DistanceTuple = Types<units::nanometres,
	                            units::micrometres,
	                            units::millimetres,
	                            units::centimetres,
	                            units::decimetres,
	                            units::metres,
	                            units::kilometres,
	                            units::thous,
	                            units::inches,
	                            units::links,
	                            units::feet,
	                            units::yards,
	                            units::rods,
	                            units::chains,
	                            units::furlongs,
	                            units::miles,
	                            units::leagues,
	                            units::fathoms,
	                            units::cables,
	                            units::nautical_miles,
	                            units::earth_radii,
	                            units::lunar_distances,
	                            units::astronimical_units,
	                            units::light_years,
	                            units::parsecs>;

	using MassTuple = Types<units::picograms,
	                        units::nanograms,
	                        units::micrograms,
	                        units::milligrams,
	                        units::grams,
	                        units::kilograms,
	                        units::grains,
	                        units::drams,
	                        units::ounces,
	                        units::pounds,
	                        units::us_hundredweight>;

	REGISTER_TYPED_TEST_CASE_P(StreamOutputTest, StreamInsertionOperator_WillFormatStringCorrectly);
	INSTANTIATE_TYPED_TEST_CASE_P(Distance, StreamOutputTest, DistanceTuple);
	INSTANTIATE_TYPED_TEST_CASE_P(Mass, StreamOutputTest, MassTuple);
}
