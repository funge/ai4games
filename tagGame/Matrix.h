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

#ifndef TG_MATRIX_H
#define TG_MATRIX_H

#include "Vec.h"

namespace tagGame
{
   /// A basic templatized matrix class.
   /// See the comments in the Vec base class as they also apply to this class.
   template <class T>
   class Matrix : public std::vector< Vec<T> >
   {
   public:
      Matrix(size_t const rowCount = 0, size_t const colCount = 0);
      Matrix(std::vector< Vec<T> > const& rows);
      Matrix(Matrix const& m);
      ~Matrix();

      size_t getRowCount() const;
      size_t getColCount() const;
      void setRowColCount(size_t const rowCount, size_t const colCount);
      Vec<T> const& getRow(size_t const i) const;
      Matrix& setRow(size_t const i, Vec<T> const& v);
      Vec<T> const& getCol(size_t const j) const;
      Matrix& setCol(size_t const j, Vec<T> const& v);
      std::vector< Vec<T> > const& getRows() const;
      std::vector< Vec<T> > const& getCols() const;

      Matrix& operator=(Matrix const& m);

      bool operator==(Matrix const& m) const;
      bool isAlmostEq(Matrix const& m) const;
      bool isAlmostZero() const;

      Matrix& set(T const x);
      Matrix& add(Matrix const& m);
      Matrix& subtract(Matrix const& m);
      Matrix& scale(T const x);
      Matrix& multiply(Matrix const& m);
      Matrix& transpose();
      Matrix& invert();

      Vec<T> multiply(Vec<T> const& v) const;

      T minElement() const;
      T maxElement() const;
      size_t argMax() const;
      size_t argMin() const;

      Matrix& shuffle();
      Matrix& randomize();
   protected:
   private:
      void computeCol(size_t const j);

      // whenever column information is computed it is cached so that it can be retrieved
      // quickly whenever it is still valid
      mutable std::vector< Vec<T> > cols;
      mutable std::vector<bool> colsValid;
   };

   typedef Matrix<int> IntMatrix;
   typedef Matrix<Real> RealMatrix;

   template <class T>
   Matrix<T>::Matrix(size_t const rowCount, size_t const colCount) :
      std::vector< Vec<T> >(rowCount),
      cols(colCount),
      colsValid(colCount)
   {
      for (size_t i = 0; i < rowCount; i++)
      {
         (*this)[i].resize(colCount);
         // Note: Vec sets to 0
      }
      for (size_t j = 0; j < colCount; j++)
      {
         cols[j].resize(rowCount);
      }
   
      fill(colsValid.begin(), colsValid.end(), true);
   }
   
   template <class T>
   Matrix<T>::Matrix(std::vector< Vec<T> > const& rows) :
      std::vector< Vec<T> >::vector(rows)
   {
      int colCountPrev(0);
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         int const n((*this)[i].size());
         TG_ASSERT(colCountPrev < 0 || colCountPrev == n);
         colCountPrev = n;
      }
      cols.resize(colCountPrev);
      for (size_t j = 0; j < colCountPrev; j++)
      {
         cols[j].resize(rows.size());
      }
      colsValid.resize(colCountPrev);
      fill(colsValid.begin(), colsValid.end(), false);
   }
   
   template <class T>
   Matrix<T>::Matrix(Matrix const& m) :
      std::vector< Vec<T> >(m),
      cols(m.cols),
      colsValid(m.colsValid)
   {
   }
   
   template <class T>
   Matrix<T>::~Matrix()
   {
   }
   
   template <class T>
   size_t Matrix<T>::getRowCount() const
   {
      return this->size();
   }
   
   template <class T>
   size_t Matrix<T>::getColCount() const
   {
      return cols.size();
   }
   
   template <class T>
   void Matrix<T>::setRowColCount(size_t const rowCount, size_t const colCount)
   {
      std::vector<T>::resize(rowCount);
      for (size_t i = 0; i < rowCount; i++)
      {
         (*this)[i].resize(colCount);
         // Note: Vec sets to 0
      }
      cols.resize(colCount);
      for (size_t j = 0; j < colCount; j++)
      {
         cols[j].resize(rowCount);
      }
      colsValid.resize(colCount);
      fill(colsValid.begin(), colsValid.end(), false);
   }
   
   template <class T>
   Vec<T> const&  Matrix<T>::getRow(size_t const i) const
   {
      TG_ASSERT(0 <= i && i < getRowCount());
   
      return (*this)[i];
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::setRow(size_t const i, Vec<T> const& v)
   {
      TG_ASSERT(0 <= i && i < getRowCount());
      TG_ASSERT((*this)[i].size() == v.size());
   
      (*this)[i] = v;
   
      return *this;
   }
   
   template <class T>
   Vec<T> const& Matrix<T>::getCol(size_t const j) const
   {
      TG_ASSERT(0 <= j && j < cols.size());
      computeCol(j);
   
      return cols[j];
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::setCol(size_t const j, Vec<T> const& v)
   {
      TG_ASSERT(0 <= j && j < cols.size());
      computeCol(j);
      TG_ASSERT(cols[j].size() == v.size());
   
      TG_ASSERT(false); // not implemented
   
      return *this;
   }
   
   template <class T>
   std::vector< Vec<T> > const& Matrix<T>::getRows() const
   {
      return static_cast< std::vector< Vec<T> >const&>(*this);
   }
   
   template <class T>
   std::vector< Vec<T> > const& Matrix<T>::getCols() const
   {
      for (size_t j = 0; j < cols.size(); j++)
      {
         computeCol(j);
      }
      return cols;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::operator=(Matrix const& m)
   {
      if (this != &m)
      {
         static_cast< std::vector< Vec<T> >&>(*this) = static_cast< std::vector< Vec<T> >const&>(m);;
         cols = m.cols;
         colsValid = m.colsValid;
      }
      return *this;
   }
   
   // TODO: make the Matrix methods take advantage of <algorithm>,
   //       like the Vec class
   
   template <class T>
   bool Matrix<T>::isAlmostEq(Matrix const& m) const
   {
      for (size_t i = 0; i < this->rows.size(); i++)
      {
         if (!((*this)[i].isAlmostEq(m[i]))) { return false; }
      }
      return true;
   }
   
   template <class T>
   bool Matrix<T>::isAlmostZero() const
   {
      for (size_t i = 0; i < this->rows.size(); i++)
      {
         if (!((*this)[i].isAlmostZero())) { return false; }
      }
      return true;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::set(T const x)
   {
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         (*this)[i].set(0);
      }
      fill(colsValid.begin(), colsValid.end(), false);
   
      return *this;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::add(Matrix const& m)
   {
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         (*this)[i].add(m[i]);
      }
      fill(colsValid.begin(), colsValid.end(), false);
   
      return *this;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::subtract(Matrix const& m)
   {
      for (size_t i = 0; i < this->rows.size(); i++)
      {
         (*this)[i].subtract(m[i]);
      }
      fill(colsValid.begin(), colsValid.end(), false);
   
      return *this;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::scale(T const x)
   {
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         (*this)[i].scale(x);
      }
      fill(colsValid.begin(), colsValid.end(), false);
   
      return *this;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::multiply(Matrix const& m)
   {
      TG_ASSERT(getColCount() == m.getRowCount());
      Matrix mOld(*this);
      setRowColCount(getRowCount(), m.getColCount());
   
      for (size_t i = 0; i < getRowCount(); i++)
      {
         for (size_t j = 0; j < getColCount(); j++)
         {
            (*this)[i][j] = mOld.getRow(i).dot(m.getCol(j));
            cols[j][i] = (*this)[i][j]; // might as well update
         }
      }
      fill(colsValid.begin(), colsValid.end(), true);
   
      return *this;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::transpose()
   {
      std::vector< Vec<T> > oldRows(getRows());
      static_cast< std::vector< Vec <T> >&>(*this) = getCols();
      cols = oldRows;
      colsValid.resize(cols.size());
   
      fill(colsValid.begin(), colsValid.end(), true);
   
      return *this;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::invert()
   {
      TG_ASSERT(false); // not implemented
   
      fill(colsValid.begin(), colsValid.end(), false);
   
      return *this;
   }
   
   template <class T>
   Vec<T> Matrix<T>::multiply(Vec<T> const& v) const
   {
      TG_ASSERT(getColCount() == v.size());
      Vec<T> result(getRowCount());
   
      for (size_t i = 0; i < getRowCount(); i++)
      {
         result[i] = (*this)[i].dot(v);
      }
   
      return result;
   }
   
   template <class T>
   T Matrix<T>::minElement() const
   {
      // would like to initialize this to Inf for Real and INT_MAX for int
      // could do with appropriate specializations of some function getBottom<T>
      T x(T(0));
   
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         if (0 == i) { x = (*this)[i].min(); } // unnecessary if initialized properly
         else { x = std::min(x, (*this)[i].min()); }
      }
      return x;
   }
   
   template <class T>
   T Matrix<T>::maxElement() const
   {
      // would like to initialize this to -Inf for Real and INT_MIN for int
      // could do with appropriate specializations of some function getBottom<T>
      T x(T(0));
   
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         if (0 == i) { x = (*this)[i].max(); } // unnecessary if initialized properly
         else { x = std::max(x, (*this)[i].max()); }
      }
      return x;
   }
   
   template <class T>
   size_t Matrix<T>::argMax() const
   {
      Util::error("not implemented");
      return 0;
   /*
      // Note: only returns the row with the maximum element
      // TODO: improve the implementation
      int which(-1);
   
      T const x(getMax());
   
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         if (x == (*this)[i].max())
         {
            which = i;
            break;
         }
      }
   
      return which;
   */
   }
   
   template <class T>
   size_t Matrix<T>::argMin() const
   {
      Util::error("not implemented");
      return 0;
   
   /*
      int which(-1);
   
      T const x(getMin());
   
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         if (x == (*this)[i].min())
         {
            which = i;
            break;
         }
      }
   
      return which;
   */
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::shuffle()
   {
      // TODO: shuffle across rows, not just within rows
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         (*this)[i].shuffle();
      }
   
      return *this;
   }
   
   template <class T>
   Matrix<T>& Matrix<T>::randomize()
   {
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         (*this)[i].randomize();
      }
   
      return *this;
   }
   
   template <class T>
   void Matrix<T>::computeCol(size_t const j)
   {
      if (colsValid[j]) { return; }
   
      for (size_t i = 0; i < std::vector<T>::size(); i++)
      {
         cols[j][i] = (*this)[i][j];
      }
   
      colsValid[j] = true;
   }
}

#endif
