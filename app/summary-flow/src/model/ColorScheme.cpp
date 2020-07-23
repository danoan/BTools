#include "summary-flow/model/ColorScheme.h"

namespace SummaryFlow
{
    typedef ColorScheme::Color Color;

    //ColorSchemeIterator methods
    ColorSchemeIterator::ColorSchemeIterator(const Container& container)
    :container(container),
    it(container.begin()){}

    void ColorSchemeIterator::operator++()
    {
        it++;
        if(it==container.end()) it=container.begin();
    }

    void ColorSchemeIterator::operator++(int){ this->operator++(); }
    Color ColorSchemeIterator::operator*() const { return *it; }


    //ColorScheme methods
    ColorScheme::ColorScheme()
    :ColorScheme(DefaultColorSchemes::Classic){}

    ColorScheme::ColorScheme( const Color& first,
            const Color& last,
            const Color& extra,
            std::initializer_list<Color> colorList):m_first(first),
            m_last(last),
            m_extra(extra)
    {
        for(auto c:colorList) m_colorVector.push_back(c);
    }

    ColorSchemeIterator ColorScheme::begin() const
    {
        return ColorSchemeIterator(m_colorVector);
    }

    namespace DefaultColorSchemes
    {
        ColorScheme Classic( Color::Red,
                                Color::Blue,
                                Color::Green,
                                {Color(0,0,0),Color(100,100,100),Color(200,200,200)});


        ColorScheme RainyJungle( Color(206,66,235),
                                    Color(134,158,13),
                                    Color(0,0,0),
                                    {Color(33,50,66),Color(45,85,125),Color(48,19,54)});

        ColorScheme Lollipop( Color(250,105,97),
                                 Color(56,89,171),
                                 Color(0,0,0),
                                 {Color(61,76,115),Color(195,235,131),Color(134,209,13)});
    }

}

