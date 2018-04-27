#ifndef __SERIALIZE_HPP__
#define __SERIALIZE_HPP__

namespace uc
{

    /**
     * A templated abstract class which describes something which can be
     * deserialized FROM a type and serialized TO a type.
     */
    template< typename FROM, typename TO >
    class Serializeable
    {
        /**
         * Purely virutal method which will update this class
         * by reading values from its corresponding FROM type.
         */
        virtual void from( FROM f ) = 0;

        /**
         * Purely virtual method which will serialize this class
         * into its corresponding TO type.
         */
        virtual TO to() const = 0;
    };

}

#endif // __SERIALIZE_HPP__
