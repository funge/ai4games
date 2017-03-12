// ----------------------------------------------------------------------------
//
// tagGame - Example code from the book:
//
//           Artficial Intelligence for Computer Games: An Introduction
//           by John David Funge
//
//           www.ai4games.org
//
// Source code distributed under the Copyright (c) 2003-2007, John David Funge
// Original author: John David Funge (www.jfunge.com)
//
// Licensed under the Academic Free License version 3.0 
// (for details see LICENSE.txt in this directory).
//
// ----------------------------------------------------------------------------

#ifndef TG_VEC_H
#define TG_VEC_H

#include "MathUtil.h"

#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

namespace tagGame
{
   /// A basic templatized vector class.
   /// The world probably doesn't need yet another vector class, but
   /// this one has several desirable properties:
   ///  - it uses the same code style as the rest of the game source;
   ///  - it is templatized to support integer and floating-point vectors;
   ///  - it is simple and light-weight;
   ///  - it avoids any "behind the scenes" copying of objects;
   ///  - it avoids almost all use of operator overloading (can make code hard to read)
   ///  - it allows arbiray length vectors (partial template specializations could be
   ///    written to provide faster special case implmentations for 2D, 3D and 4D vectors).
   ///  - it makes extensive use of STL to simplify and reduce the amount of code
   ///    (STL could be expanded and improved to make the code even simpler and shorter).
   ///
   /// It is not however meant to be a fully fledged linear algebra class.  If you
   /// are looking for such a library try www.boost.org, geometrictools.com, or any
   /// of a host of other libraries.
   template <class T>
   class Vec : public std::vector<T>
   {
   public:
      Vec(size_t const n = 0);
      Vec(std::vector<T> const& data);
      Vec(Vec const& v);
      // ~Vec();

      bool isAlmostEq(Vec const& v) const;
      bool isAlmostZero() const;

      std::ostream& output(std::ostream& out) const;

      Vec& set(T const x);
      Vec& add(Vec const& v);
      Vec& subtract(Vec const& v);
      Vec& scale(T const x);
      Vec& scale(Vec const& v);

      T length() const;
      T squaredLength() const;
      T minElement() const;
      T maxElement() const;
      size_t argMax() const;
      size_t argMin() const;
      T dot(Vec const& v) const;
      T sum() const;

      Vec& normalize();
      Vec& setLength(T const x);
      Vec& clampMaxLength(T const x);
      Vec& shuffle();
      Vec& randomize();
      Vec& wrap(Vec const& v);
      Vec& clamp(Vec const& lower, Vec const& upper);

      /// Make this into a probability distribution.
      Vec& probabilityDistribution();

      /// Calculate a new vector that is this vector relative to v.
      Vec relativeTo(Vec const& v) const;
   protected:
   private:
   };

   template <class T>
   std::ostream& operator<<(std::ostream& out, Vec<T> const& v);

   typedef Vec<int> IntVec;
   typedef Vec<Real> RealVec;

   template <class T>
   Vec<T>::Vec(size_t const size) :
      std::vector<T>(size)
   {
      set(T(0));
   }
   
   template <class T>
   Vec<T>::Vec(std::vector<T> const& data) :
      std::vector<T>(data)
   {
   }
   
   template <class T>
   Vec<T>::Vec(Vec const& v) :
      std::vector<T>(v) 
   {
   }
   
   // not really needed, but uncommenting this destructor causes an internal compiler error on MacOSX!
   /*
   template <class T>
   Vec<T>::~Vec()
   {
      std::vector<T>::~vector<T>();
   }
   */
   
   template <class T>
   Vec<T>& Vec<T>::set(T const x)
   {
      fill(std::vector<T>::begin(), std::vector<T>::end(), x);
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::add(Vec const& v)
   {
      TG_ASSERT(std::vector<T>::size() == v.size());
   
      transform(std::vector<T>::begin(), std::vector<T>::end(), v.begin(), std::vector<T>::begin(), std::plus<T>());
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::subtract(Vec const& v)
   {
      TG_ASSERT(std::vector<T>::size() == v.size());
   
      transform(std::vector<T>::begin(), std::vector<T>::end(), v.begin(), std::vector<T>::begin(), std::minus<T>());
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::scale(T const x)
   {
      transform(std::vector<T>::begin(), std::vector<T>::end(), std::vector<T>::begin(), std::bind1st(std::multiplies<T>(), x));
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::scale(Vec const& v)
   {
      transform(std::vector<T>::begin(), std::vector<T>::end(), v.begin(), std::vector<T>::begin(), std::multiplies<T>());
   
      return *this;
   }
   
   template <class T>
   T Vec<T>::length() const
   {
      return T(sqrt(Real(this->squaredLength())));
   }
   
   template <class T>
   T Vec<T>::squaredLength() const
   {
      return this->dot(*this);
   }
   
   template <class T>
   T Vec<T>::dot(Vec const& v) const
   {
      return inner_product(std::vector<T>::begin(), std::vector<T>::end(), v.begin(), T(0));
   }
   
   template <class T>
   class adder : public std::unary_function<T, void>
   {
   public:
      adder() :
         sum(T(0))
      {
      }
   
      T sum;
   
      void operator()(T const x)
      {
        sum += x;
      }
   };
   
   template <class T>
   T Vec<T>::sum() const
   {
      return for_each(std::vector<T>::begin(), std::vector<T>::end(), adder<T>()).sum;
   }
   
   template <class T>
   size_t Vec<T>::argMin() const
   {
      return min_element(std::vector<T>::begin(), std::vector<T>::end()) - std::vector<T>::begin();
   }
   
   template <class T>
   size_t Vec<T>::argMax() const
   {
      return max_element(std::vector<T>::begin(), std::vector<T>::end()) - std::vector<T>::begin();
   }
   
   template <class T>
   T Vec<T>::minElement() const
   {
      return (*this)[argMin()];
   }
   
   template <class T>
   T Vec<T>::maxElement() const
   {
      return (*this)[argMax()];
   }
   
   template <class T>
   Vec<T>& Vec<T>::normalize()
   {
      return setLength(T(1));
   }
   
   template <class T>
   Vec<T>& Vec<T>::clampMaxLength(T const x)
   {
      Real const l(length());
   
      if (x < l)
      {
         setLength(x);
      }
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::setLength(T const x)
   {
      Real const l(length());
      if (MathUtil::isAlmostZero(l))
      {
         set(T(0));
      }
      else
      {
         scale(x/T(l));
      }
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::shuffle()
   {
      // gcc 4 complains if you just try to pass in the reference directly.
      std::pointer_to_unary_function<int, int> p(MathUtil::uniform);
   
      std::random_shuffle(std::vector<T>::begin(), std::vector<T>::end(), p);
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::randomize()
   {
      generate(std::vector<T>::begin(), std::vector<T>::end(), MathUtil::uniform01);
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::wrap(Vec<T> const& v)
   {
      TG_ASSERT(std::vector<T>::size() == v.size());
   
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         // otherwise loops forever
         TG_ASSERT(0 < v[i]);
   
         while ((*this)[i] < 0)
         {
            (*this)[i] += v[i];
         }
         while (v[i] < (*this)[i])
         {
            (*this)[i] -= v[i];
         }
      }
   
      return *this;
   }
   
   template <class T>
   Vec<T>& Vec<T>::clamp(Vec<T> const& lower, Vec<T> const& upper)
   {
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         (*this)[i] = MathUtil::clamp((*this)[i], lower[i], upper[i]);
      }
   
      return *this;
   }
   
   template<class T>
   bool Vec<T>::isAlmostZero() const
   {
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         if (!MathUtil::isAlmostZero((*this)[i])) { return false; }
      }
      return true;
   }
   
   template<class T>
   Vec<T> Vec<T>::relativeTo(Vec<T> const& v) const
   {
      Vec<T> u(*this);
   
      return u.subtract(v);
   }
   
   template<class T>
   std::ostream& Vec<T>::output(std::ostream& out) const
   {
      copy(std::vector<T>::begin(), std::vector<T>::end(), std::ostream_iterator<T>(out, " "));
   
      return out;
   }

   template <class T>
   Vec<T>& Vec<T>::probabilityDistribution()
   {
      Real const s(sum());

      Util::warn(0 < s, "Vec::probabilityDistribution: vector is zero");

      return scale(Real(1.0)/s);
   }
   
   template <class T>
   std::ostream& operator<<(std::ostream& out, Vec<T> const& v)
   {
      return v.output(out);
   }
}

#endif
