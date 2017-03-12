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

#ifndef TG_CONTROLLERRANDOMIZE_H
#define TG_CONTROLLERRANDOMIZE_H

#include "Controller.h"
#include "Perception.h"

namespace tagGame
{
   /// Simple controller that evades the tagged character with an option to
        /// choose the evasion direction stochastically.
   class ControllerRandomize : public Controller
   {
   public:
      ControllerRandomize(PerceptionPtr perception,
                            ControllerPtr controller,
                            PerceptReal distance,
                            Real near,
                            Real far);
      virtual ~ControllerRandomize();

      inline ControllerPtr getController() const;
      inline PerceptReal getDistance() const;
      inline Real getNearDistance() const;
      inline Real getFarDistance() const;

      inline void setController(ControllerPtr controller);
      inline void setDistance(PerceptReal const distance);
      inline void setNearDistance(Real const nearDistance);
      inline void setFarDistance(Real const farDistance);

      virtual void calcAction();

   protected:
      ControllerPtr controller;
      PerceptReal distance;
      Real nearDistance;
      Real farDistance;

   private:
   };

   ControllerPtr ControllerRandomize::getController() const
   {
      return controller;
   }

   PerceptReal ControllerRandomize::getDistance() const
   {
      return distance;
   }

   Real ControllerRandomize::getNearDistance() const
   {
      return nearDistance;
   }

   Real ControllerRandomize::getFarDistance() const
   {
      return farDistance;
   }

   void ControllerRandomize::setController(ControllerPtr controller)
   {
      this->controller = controller;
   }

   void ControllerRandomize::setDistance(PerceptReal const distance)
   {
      this->distance = distance;
   }

   void ControllerRandomize::setNearDistance(Real const nearDistance)
   {
      this->nearDistance = nearDistance;
   }

   void ControllerRandomize::setFarDistance(Real const farDistance)
   {
      this->farDistance = farDistance;
   }
}

#endif
