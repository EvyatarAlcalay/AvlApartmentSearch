
//
// Created by rotem on 31/10/2021.
//


#include "Stack.h"
#include <unordered_set>
#include "Find.h"
#define X_LOWER_BOUND 31.7
#define Y_LOWER_BOUND 35.1
#define X_UPPER_BOUND 31.9
#define Y_UPPER_BOUND 35.3
#include <cmath>
#include <utility>
#define X_FEEL_BOX 35.213506
#define Y_FEEL_BOX 31.772425
#include <iostream>
#include <set>
#include "AVL.h"
#include <algorithm>
#include <sstream>
#include <bits/stdc++.h>
std::pair<double, double> feel_box (X_FEEL_BOX, Y_FEEL_BOX);


double random_number (bool is_x)
{
  double f = (double) rand () / RAND_MAX;
  double fMin = is_x ? X_LOWER_BOUND : Y_LOWER_BOUND;
  double fMax = is_x ? X_UPPER_BOUND : Y_UPPER_BOUND;
  return fMin + f * (fMax - fMin);
}
std::pair<double, double> random_x_y ()
{
  return {random_number (true), random_number (false)};
}
double
calculateDistance (std::pair<double, double> &x, std::pair<double, double> &y)
{
  return sqrt (pow (x.first - y.first, 2) +
  pow (x.second - y.second, 2));
}
std::vector<std::pair<double, double>> vector_of_points (int number_of_points)
{
  std::set<double> distances;
  std::vector<std::pair<double, double>> v;
  for (int i = 0; i < number_of_points; ++i)
  {
    auto x_y = random_x_y ();
    double distance = calculateDistance (x_y, feel_box);
    while (distances.find (distance) != distances.end ())
    {
      x_y = random_x_y ();
      distance = calculateDistance (x_y, feel_box);
    }
    distances.insert (distance);
    v.push_back (x_y);
  }
  return v;
}
std::vector<Apartment>
vector_of_apartments (std::vector<std::pair<double, double>> vector)
{
  std::vector<Apartment> res;
  for (auto pair: vector) res.push_back (pair);
  return res;
}



int test3 ()
{
  srand (3);
  std::vector<std::pair<double, double>> v = vector_of_points (10);
  Stack s (v);
  std::reverse (v.begin (), v.end ());
  auto s_i = s.begin ();
  for (auto i = v.begin (); i != v.end (); ++i, s_i++)
  {
    if (!(*s_i == *i)) return 1;
  }
  return 0;
}


int test2 ()
{
  srand (2);
  Stack s1;
  if (!s1.empty ()) return 1;
  std::vector<std::pair<double, double>> pairs;
  std::vector<Apartment> apartments;

  int number_of_elements = 10;
  for (int i = 0; i < number_of_elements; ++i)
  {
    auto pair = random_x_y ();
    pairs.push_back (pair);
    s1.push (pair);
    apartments.push_back (pair);
  }
  Stack s2 (pairs);
  if (s2.size () != (size_t) number_of_elements) return 2;
  for (int i = number_of_elements - 1; i > -1; --i)
  {
    auto top1 = s1.top ();
    auto top2 = s2.top ();
    if (!(top2 == apartments[i])) return 3;
    if (!(top1 == apartments[i])) return 3;
    s2.pop ();
    s1.pop ();
  }
  return 0;
}


int test1 ()
{
  srand (1);
  double x = random_number (true), y = random_number (false);
  std::pair<double, double> pair1 (x, y);
  Apartment apartment1 (pair1);
  if (apartment1.get_x () != x) return 1;
  if (apartment1.get_y () != y) return 1;
  std::vector<std::pair<double, double>> pairs;
  std::vector<Apartment> apartments;
  for (int i = 0; i < 10; ++i)
  {
    auto pair = random_x_y ();
    pairs.push_back (pair);
    apartments.push_back (pair);
    for (int j = 0; j < i; ++j)
    {
      if (calculateDistance (pairs[i], feel_box)
      < calculateDistance (pairs[j], feel_box)
      && !(apartments[i] < apartments[j]))
      {
        return 4;
      }
      if (calculateDistance (pairs[i], feel_box)
      > calculateDistance (pairs[j], feel_box)
      && !(apartments[i] > apartments[j]))
      {
        return 4;
      }
    }
  }
  return 0;
}


int test4 ()
{
  srand (6);
  std::vector<std::pair<double, double>> vector_points = vector_of_points (3);
  auto vector_apartments = vector_of_apartments (vector_points);
  std::sort (vector_apartments.begin (), vector_apartments.end ());
  AVL avl;
  avl.insert (vector_apartments[2]);
  avl.insert (vector_apartments[1]);
  AVL::node *root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[2])) return 1;
  if (!(root->get_left ()->get_data () == vector_apartments[1])) return 1;
  avl.insert (vector_apartments[0]);
  root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[1])) return 2;
  if (!(root->get_right ()->get_data () == vector_apartments[2])) return 2;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 2;

  return 0;
}


int test5 ()
{
  srand (7);
  std::vector<std::pair<double, double>> vector_points = vector_of_points (3);
  auto vector_apartments = vector_of_apartments (vector_points);
  std::sort (vector_apartments.begin (), vector_apartments.end ());
  AVL avl;
  avl.insert (vector_apartments[2]);
  avl.insert (vector_apartments[0]);
  AVL::node *root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[2])) return 1;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 1;
  avl.insert (vector_apartments[1]);
  root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[1])) return 2;
  if (!(root->get_right ()->get_data () == vector_apartments[2])) return 2;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 2;

  return 0;
}


int test6 ()
{
  srand (8);
  std::vector<std::pair<double, double>> vector_points = vector_of_points (4);
  auto vector_apartments = vector_of_apartments (vector_points);
  std::sort (vector_apartments.begin (), vector_apartments.end ());
  AVL avl;
  avl.insert (vector_apartments[1]);
  avl.insert (vector_apartments[0]);
  avl.insert (vector_apartments[2]);
  avl.insert (vector_apartments[3]);
  AVL::node *root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[1])) return 1;
  if (!(root->get_right ()->get_data () == vector_apartments[2])) return 1;
  if (!(root->get_right ()->get_right ()->get_data ()
  == vector_apartments[3]))
    return 1;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 1;
  avl.erase (vector_apartments[0]);
  root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[2])) return 2;
  if (!(root->get_right ()->get_data () == vector_apartments[3])) return 2;
  if (!(root->get_left ()->get_data () == vector_apartments[1])) return 2;

  return 0;
}


std::vector<Apartment>
vector_of_apartments (std::vector<std::pair<double, double>> vector);
int test7 ()
{
  srand (9);
  std::vector<std::pair<double, double>> vector_points = vector_of_points (4);
  auto vector_apartments = vector_of_apartments (vector_points);
  std::sort (vector_apartments.begin (), vector_apartments.end ());
  AVL avl;
  avl.insert (vector_apartments[1]);
  avl.insert (vector_apartments[0]);
  avl.insert (vector_apartments[3]);
  avl.insert (vector_apartments[2]);
  AVL::node *root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[1])) return 1;
  if (!(root->get_right ()->get_data () == vector_apartments[3])) return 1;
  if (!(root->get_right ()->get_left ()->get_data ()
  == vector_apartments[2]))
    return 1;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 1;
  avl.erase (vector_apartments[1]);
  root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[1])) return 2;
  if (!(root->get_right ()->get_data () == vector_apartments[3])) return 2;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 2;

  return 0;
}


int test8 ()
{
  srand (9);
  std::vector<std::pair<double, double>> vector_points = vector_of_points (4);
  auto vector_apartments = vector_of_apartments (vector_points);
  std::sort (vector_apartments.begin (), vector_apartments.end ());
  AVL avl;
  avl.insert (vector_apartments[1]);
  avl.insert (vector_apartments[0]);
  avl.insert (vector_apartments[3]);
  avl.insert (vector_apartments[2]);
  AVL::node *root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[1])) return 1;
  if (!(root->get_right ()->get_data () == vector_apartments[3])) return 1;
  if (!(root->get_right ()->get_left ()->get_data ()
  == vector_apartments[2]))
    return 1;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 1;
  avl.erase (vector_apartments[1]);
  root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[2])) return 2;
  if (!(root->get_right ()->get_data () == vector_apartments[3])) return 2;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 2;

  vector_points = vector_of_points (7);
  vector_apartments = vector_of_apartments (vector_points);
  std::sort (vector_apartments.begin (), vector_apartments.end ());

  AVL avl2;
  avl2.insert (vector_apartments[2]);
  avl2.insert (vector_apartments[0]);
  avl2.insert (vector_apartments[5]);
  avl2.insert (vector_apartments[1]);
  avl2.insert (vector_apartments[4]);
  avl2.insert (vector_apartments[3]);
  avl2.insert (vector_apartments[6]);
  root = avl.get_root ();
  if (!(root->get_data () == vector_apartments[2])) return 1;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 1;
  if (!(root->get_left ()->get_right ()->get_data ()
  == vector_apartments[1]))
    return 1;
  if (!(root->get_right ()->get_data () == vector_apartments[5])) return 1;
  if (!(root->get_right ()->get_left ()->get_data ()
  == vector_apartments[3]))
    return 1;
  if (!(root->get_right ()->get_right ()->get_data ()
  == vector_apartments[6]))
    return 1;
  if (!(root->get_right ()->get_left ()->get_right ()->get_data ()
  == vector_apartments[4]))
    return 1;
  avl2.erase (vector_apartments[2]);
  root = avl2.get_root ();
  if (!(root->get_data () == vector_apartments[3])) return 3;
  if (!(root->get_left ()->get_data () == vector_apartments[0])) return 3;
  if (!(root->get_left ()->get_right ()->get_data ()
  == vector_apartments[1]))
    return 3;
  if (!(root->get_right ()->get_data () == vector_apartments[5])) return 3;
  if (!(root->get_right ()->get_left ()->get_data ()
  == vector_apartments[4]))
    return 3;
  if (!(root->get_right ()->get_right ()->get_data ()
  == vector_apartments[6]))
    return 3;
  return 0;
}


int test9 ()
{
  std::vector<std::pair<double, double>> points1 = vector_of_points (20);
  AVL avl (points1);
  for (auto point:points1)
    if (find (avl.begin (), avl.end (), {point}) == avl.end ()) return 1;
    std::vector<Apartment> vector_apartments = vector_of_apartments (points1);
    for (auto point:points1)
      if (find (vector_apartments.begin (), vector_apartments.end (), {
        point}) == vector_apartments.end ())
        return 2;
      std::pair<double, double> pair (0, 0);
      const AVL::iterator &iterator = find (avl.begin (), avl.end (), {pair});
      if (iterator != avl.end ()) return 3;
      if (find (vector_apartments.begin (), vector_apartments.end (), {pair})
      != vector_apartments.end ())
        return false;
      std::vector<std::pair<double, double>> points2 = vector_of_points (20);
      Stack s (points2);
      for (auto point:points2)
        if (find (s.begin (), s.end (), {point}) == s.end ()) return 1;
        if (find (s.begin (), s.end (), {pair}) != s.end ()) return 2;
        return 0;
}


int test10 ()
{
  std::vector<std::pair<double, double>> points1 = vector_of_points (20);
  const AVL avl2 (points1);
  //print_my_avl(avl2);
  auto end = avl2.end ();
  for (auto point:points1)
    if (avl2.find ({point}) == end) return 1;
    std::pair<double, double> pair (0, 0);
    if (avl2.find (pair) != avl2.end ()) return 2;
    return 0;

}


int test11 ()
{
  std::stringstream ss_from_operator;
  std::stringstream ss_required;
  std::vector<std::pair<double, double>> vector_points = vector_of_points (7);
  auto vector_apartments = vector_of_apartments (vector_points);
  std::sort (vector_apartments.begin (), vector_apartments.end ());
  AVL avl;
  avl.insert (vector_apartments[3]);
  avl.insert (vector_apartments[1]);
  avl.insert (vector_apartments[5]);
  avl.insert (vector_apartments[0]);
  avl.insert (vector_apartments[4]);
  avl.insert (vector_apartments[2]);
  avl.insert (vector_apartments[6]);
  std::vector<Apartment> vector_for_loop{vector_apartments[3],
                                         vector_apartments[1],
                                         vector_apartments[0],
                                         vector_apartments[2],
                                         vector_apartments[5],
                                         vector_apartments[4],
                                         vector_apartments[6]};
  ss_from_operator << avl;
  for (auto item:vector_for_loop) ss_required << item;
  if (ss_from_operator.str () != ss_required.str ())
    return 1;
  int i = 0;
  auto it = avl.begin ();
  while (i < 7 && it != avl.end ())
  {
    if (!(vector_for_loop[i] == (*it))) return 2;
    it++;
    i++;
  }
  if (it != avl.end ()) return 3;
  if (i != 7) return 3;
  return 0;

}


int main ()
{
  int failed_test = 11;
  std::cout << "Running Test 1!" << std::endl;
  if (test1 ()) return failed_test;
  failed_test--;
  std::cout << "Passed Test 1!" << std::endl;
  std::cout << "Running Test 2!" << std::endl;
  if (test2 ()) return failed_test;
  failed_test--;
  std::cout << "Passed Test 2!" << std::endl;
  std::cout << "Running Test 3!" << std::endl;
  if (test3 ())return failed_test;
  failed_test--;
  std::cout << "Passed Test 3!" << std::endl;
  std::cout << "Running Test 4!" << std::endl;
  if (test4 ()) return failed_test;
  failed_test--;
  std::cout << "Passed Test 4!" << std::endl;
  std::cout << "Running Test 5!" << std::endl;
  if (test5 ())return failed_test;
  failed_test--;
  std::cout << "Passed Test 5!" << std::endl;
  std::cout << "Running Test 6!" << std::endl;
  if (test6 ()) return failed_test;
  failed_test--;
  std::cout << "Passed Test 6!" << std::endl;
  std::cout << "Running Test 7!" << std::endl;
  test7 ();
  failed_test--;
  std::cout << "Passed Test 7!" << std::endl;
  std::cout << "Running Test 8!" << std::endl;

  test8 ();
  failed_test--;
  std::cout << "Passed Test 8!" << std::endl;
  std::cout << "Running Test 9!" << std::endl;

  test9 ();
  failed_test--;
  std::cout << "Passed Test 9!" << std::endl;
  std::cout << "Running Test 10!" << std::endl;

  test10 ();
  failed_test--;
  std::cout << "Passed Test 10!" << std::endl;
  std::cout << "Running Test 11!" << std::endl;

  test11 ();
  failed_test--;
  std::cout << "Passed Test11!" << std::endl;

}
