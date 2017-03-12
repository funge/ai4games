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

#ifndef TG_CONTROLLERPERIODIC_RAMP_H
#define TG_CONTROLLERPERIODIC_RAMP_H

#include "Controller.h"
#include "Perception.h"

namespace tagGame
{
   /// Only calculate a new action periodically.
   class ControllerPeriodicRamp : public Controller
   {
   public:
      ControllerPeriodicRamp(PerceptionPtr perception,
                             ControllerPtr controller,
                             PerceptReal distance,
                             Real const nearDistance,
                             Real const farDistance,
                             Real const minPeriod,
                             Real const maxPeriod);
      virtual ~ControllerPeriodicRamp();

      inline void setMinPeriod(Real const minPeriod);
      inline Real getMinPeriod() const;

      inline void setMaxPeriod(Real const maxPeriod);
      inline Real getMaxPeriod() const;

      inline void setController(ControllerPtr controller);
      inline ControllerPtr getController() const;

      inline PerceptReal getDistance() const;
      inline Real getNearDistance() const;
      inline Real getFarDistance() const;

      inline void setDistance(PerceptReal const distance);
      inline void setNearDistance(Real const nearDistance);
      inline void setFarDistance(Real const farDistance);

      virtual void calcAction();

   protected:
      ControllerPtr controller;
      PerceptReal distance;
      Real nearDistance;
      Real farDistance;
      Real minPeriod;
      Real maxPeriod;
      Real timeOfLastDecision;
   private:
   };

   void ControllerPeriodicRamp::setMinPeriod(Real const minPeriod)
   {
      this->minPeriod = minPeriod;
   }

   Real ControllerPeriodicRamp::getMinPeriod() const
   {
      return minPeriod;
   }

   void ControllerPeriodicRamp::setMaxPeriod(Real const maxPeriod)
   {
      this->maxPeriod = maxPeriod;
   }

   Real ControllerPeriodicRamp::getMaxPeriod() const
   {
      return maxPeriod;
   }

   void ControllerPeriodicRamp::setController(ControllerPtr controller)
   {
      this->controller = controller;
   }

   ControllerPtr ControllerPeriodicRamp::getController() const
   {
      return controller;
   }

   PerceptReal ControllerPeriodicRamp::getDistance() const
   {
      return distance;
   }

   Real ControllerPeriodicRamp::getNearDistance() const
   {
      return nearDistance;
   }

   Real ControllerPeriodicRamp::getFarDistance() const
   {
      return farDistance;
   }

   void ControllerPeriodicRamp::setDistance(PerceptReal const distance)
   {
      this->distance = distance;
   }

   void ControllerPeriodicRamp::setNearDistance(Real const nearDistance)
   {
   this->nearDistance = nearDistance;
   }

   void ControllerPeriodicRamp::setFarDistance(Real const farDistance)
   {
      this->farDistance = farDistance;
   }
}

#endif
