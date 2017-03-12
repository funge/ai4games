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

#include "Obstacle.h"
#include "Circle.h"
#include "Side.h"
#include "Util2D.h"
#include "ControllerEvade.h"
#include "Character.h"
#include "Perception.h"

using namespace tagGame;

using namespace std;

void collideTest01()
{
   CirclePtr cs0(new Circle());
   CirclePtr cs1(new Circle());
   cs0->setRadius(2);
   cs1->setRadius(2);
   Obstacle c0(cs0), c1(cs1);
   RealVec p(Util2D::dim);
   p.set(0);
   c0.setPosition(p);
   c0.setMass(1);
   p[0] = 4;
   c1.setPosition(p);
   c1.setMass(1);
   TG_ASSERT(0 == c0.distanceTo(c1));

   p[0] = 3;
   c1.setPosition(p);
   TG_ASSERT(-1 == c0.distanceTo(c1));

   p[0] = 5;
   c1.setPosition(p);
   TG_ASSERT(1 == c0.distanceTo(c1));

   RealVec rpc1(c0.getPosition().relativeTo(c1.getPosition()));
   RealVec rpc0(c1.getPosition().relativeTo(c0.getPosition()));

   rpc0.scale(-1);
   TG_ASSERT(rpc0 == rpc1);

   Obstacle* c0p(&c0);
   Obstacle* c1p(&c1);
   TG_ASSERT(1 == c0p->distanceTo(*c1p));

   SidePtr ss0(new Side());
   RealVec normal(Util2D::dim);
   normal[0] = Real(1);
   normal[1] = Real(0);
   ss0->setNormal(normal);
   ss0->setDistance(0);

   Obstacle s0(ss0);
   Obstacle* s0p = &s0;

   cerr << c0 << s0 << endl;
   cerr << c0p->distanceTo(*s0p) << endl;
   // TG_ASSERT(-2 == c0p->distanceTo(*s0p));
   cerr << "------------\n";
   cerr << c1 << s0 << endl;
   cerr << s0p->distanceTo(c1) << endl;
   // TG_ASSERT(3 == s0p->distanceTo(c1));
   cerr << "------------\n";
   ss0->setDistance(10);
   cerr << c1 << s0 << endl;
   cerr << c1.distanceTo(*s0p) << endl;
   // TG_ASSERT(-3 == c1.distanceTo(*s0p));
   cerr << "------------\n";
   normal.scale(-1);
   ss0->setNormal(normal);
   ss0->setDistance(-10);
   cerr << c1 << s0 << endl;
   cerr << c1.distanceTo(*s0p) << endl;
   // TG_ASSERT(3 == c1.distanceTo(*s0p));
   cerr << "------------\n";

   p[0] = 4;
   c1.setPosition(p);

   cerr << c0 << endl;
   cerr << c1 << endl;

   TG_ASSERT(c0p->isTouching(c1));

   RealVec v(Util2D::dim);
   v[0] = -1;
   v[1] = 0;
   c0.setVelocity(v);
   v[0] = 1;
   c1.setVelocity(v);

   TG_ASSERT(!c0p->isColliding(c1));

   v[0] = 2;
   c0.setVelocity(v);

   TG_ASSERT(c0p->isColliding(c1));

   v[0] = 0;
   c1.setVelocity(v);

   TG_ASSERT(c0p->isColliding(c1));

   ss0->setDistance(6);
   v[0] = 1;
   c1.setVelocity(v);
   cerr << "------------\n";
   cerr << c1 << s0 << endl;
   cerr << v << endl;

   // TG_ASSERT(c1p->isColliding(s0));

   cerr << "------------\n";
   cerr << c0 << c1 << endl;
   cerr << v << endl;
   v[0] = 2;
   c0.setVelocity(v);

   TG_ASSERT(c0p->isColliding(c1));

   v[0] = 4;
   c1.setVelocity(v);
   TG_ASSERT(!c0p->isColliding(c1));
}

void collideTest02()
{
   RealVec p(Util2D::dim);
   p.set(0);
   p[0] = 1;

   RealVec v(Util2D::dim);
   v.set(0);
   v[0] = 1;

   RealVec center(Util2D::dim);
   center.set(0);
   center[0] = 4;

   Real radius = Real(2);

   CirclePtr cs(new Circle());
   Obstacle* circle = new Obstacle(cs);
   circle->setPosition(center);
   // TODO: more sensible constructors
   cs->setRadius(radius);

   RealVec q(circle->nearestIntersection(p, v));

   TG_ASSERT(2 == q[0] && 0 == q[1]);

   v[0] = -1;
   q = circle->nearestIntersection(p, v);
   TG_ASSERT(Inf == q[0] && Inf == q[1]);

   RealVec begin(Util2D::dim);
   RealVec end(Util2D::dim);

   end[1] = Real(8);

   SidePtr ss(new Side());
   Obstacle* side(new Obstacle(ss));
   ss->setBegin(begin);
   ss->setEnd(end);

   p.set(5);

   v[0] = -1;
   v[1] = 0;

   q = side->nearestIntersection(p, v);

   // TG_ASSERT(0 == q[0] && 5 == q[1]);

   v[0] = 1;

   q = side->nearestIntersection(p, v);

   // TG_ASSERT(Inf == q[0] && Inf == q[1]);

   v[0] = 0;
   v[1] = 1;

   q = side->nearestIntersection(p, v);

   // TG_ASSERT(Inf == q[0] && Inf == q[1]);

   v[0] = -0.1;

   q = side->nearestIntersection(p, v);

   // TG_ASSERT(Inf == q[0] && Inf == q[1]);
}

void collideTest03()
{
   RealVec normal(Util2D::dim);
   RealVec begin(Util2D::dim);
   RealVec end(Util2D::dim);

   SidePtr ss(new Side());

   begin.set(0);
   end.set(0);
   end[1] = 10;

   ss->setBegin(begin);
   ss->setEnd(end);
   normal.set(Real(0));
   normal[0] = Real(1);
   ss->setNormal(normal);
   ss->setDistance(0);

   CirclePtr cs(new Circle());
   RealVec w;
   GameState gs(w);
   Character* c(new Character(cs, ControllerPtr(new ControllerEvade(PerceptionPtr(new Perception(&gs))))));
   c->setMass(1);
   RealVec x(Util2D::dim);
   x.set(5);
   c->setPosition(x);
   cs->setRadius(1);
   x.set(0);
   x[0] = -1;
   x.scale(2);
   c->setVelocity(x);
   // TODO: print methods for Character and other objects

   // cerr << c->getOrientation() << "; " << c->getSpeed() << endl;
#if 0 // TODO: re-instate
   Perception perception(&gs);
   perception.setMe(c);
   // TG_ASSERT(side == perception.nextCollider());
   RealVec cp(perception.nextCollisionPoint());
   cerr << "cp: " << perception.nextCollisionPoint() << endl;
   // TG_ASSERT(cp[0] == 0 && cp[1] == 5);

   normal.set(0);
   normal[1] = 1;
   end.set(0);
   end[0] = Real(10);
   side->setNormal(normal);
   side->setEnd(end);

   x.set(0);
   x[1] = -1;
   x.scale(2);
   c->setVelocity(x);
   cerr << c->getOrientation() << "; " << c->getSpeed() << endl;
   // TG_ASSERT(side == perception.nextCollider());
   cp = perception.nextCollisionPoint();
   // cerr << "cp: " << cp << endl;
   // TG_ASSERT(cp[0] == 5 && cp[1] == 0);
#endif
}

int main(int argc, char** argv)
{
   collideTest01();
   collideTest02();
   collideTest03();

   exit(EXIT_SUCCESS);
}

